//
// https://github.com/pmandin/reevengi-tools/wiki/.ADT-%28Resident-Evil-2-PC%29
//
#include "pch.h"
//#include "adt.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
/* Load file in mem from filename, return buffer, update length */

#define _max(a,b) (((a) > (b)) ? (a) : (b))
#define _min(a,b) (((a) < (b)) ? (a) : (b))

static char *loadFile(const char *filename, int *length)
{
    FILE* handle;
    char *buffer;

    /* Load file */
    if (fopen_s(&handle, filename, "rb")) {
        fprintf(stderr, "Unable to open %s\n", filename);
        return NULL;
    }

    fseek(handle, 0, SEEK_END);
    *length = ftell(handle);
    fseek(handle, 0, SEEK_SET);
    if (*length == 0) {
        printf("file zero length\n");
        return NULL;
    }

    buffer = (char *)malloc(*length);
    if (buffer == NULL) {
        fprintf(stderr, "Unable to allocate %d bytes\n", length);
        return NULL;
    }

    //fread(handle, buffer, *length);
    fread(buffer, 1, *length, handle);
    fclose(handle);

    return buffer;
}

/* Uncompressed data */

/* Note: the game allocates 32KB, then allocate more 32KB */
/* if the dstOffset reach the 32KB limit */

static unsigned char dstPointer[512 << 10]; /* Allocate 512KB, should be enough */
static int dstOffset;	 /* Position where to write data in the dstPointer buffer */

/* Source data */

static unsigned char *srcPointer;	/* pointer to source file */
static int srcOffset;			/* position in source file */
static int srcLength;			/* length of source file */
static int srcNumBit;			/* current bit in source file */
static unsigned char srcByte;		/* Current byte read from file */

/* Unpack structure */

typedef struct {
    long start;
    long length;
} unpackArray8_t;

typedef struct {
    unsigned long start;
    unsigned long length;
    unsigned long *ptr4;
    unpackArray8_t *ptr8;
    unsigned long *ptr16;
} unpackArray_t;

static unpackArray_t array1, array2, array3;

static unsigned char tmp32k[32768];	/* Temporary 32KB buffer */
static unsigned long tmp32kOffset;	/* Position in temp buffer */

static unsigned char tmp16k[16384];	/* Temporary 16KB buffer */
static int tmp16kOffset;

static unsigned short freqArray[17];

static void initTmpArray(unpackArray_t *array, int start, int length)
{
    array->start = start;

    array->length = length;

    array->ptr16 = (unsigned long *)&tmp32k[tmp32kOffset];
    tmp32kOffset += length << 5;

    array->ptr8 = (unpackArray8_t *)&tmp32k[tmp32kOffset];
    tmp32kOffset += length << 3;

    array->ptr4 = (unsigned long *)&tmp32k[tmp32kOffset];
    tmp32kOffset += length << 2;
}

static void initTmpArrayData(unpackArray_t *array)
{
    int i;

    for (i = 0; i < array->length; i++) {
        array->ptr4[i] =
            array->ptr8[i].start =
            array->ptr8[i].length =
            array->ptr16[(i << 2)] = 0;
        array->ptr16[(i << 2) + 1] =
            array->ptr16[(i << 2) + 2] =
            array->ptr16[(i << 2) + 3] = 0xffffffff;
    }

    while (i < array->length << 1) {
        array->ptr16[(i << 2)] = 0;
        array->ptr16[(i << 2) + 1] =
            array->ptr16[(i << 2) + 2] =
            array->ptr16[(i << 2) + 3] = 0xffffffff;
        i++;
    }
}

static int readSrcBits(int numBits)
{
    int orMask = 0, andMask;
    int finalValue;

    finalValue = srcByte;

    while (numBits > srcNumBit) {
        numBits -= srcNumBit;
        andMask = (1 << srcNumBit) - 1;
        andMask &= finalValue;
        andMask <<= numBits;
        if (srcOffset < srcLength) {
            finalValue = srcByte = (char)srcPointer[srcOffset++];
        }
        else {
            finalValue = srcByte = 0;
        }
        /*finalValue = srcByte = (char) srcPointer[srcOffset++];*/
        srcNumBit = 8;
        orMask |= andMask;
    }

    srcNumBit -= numBits;
    finalValue >>= srcNumBit;
    finalValue = (finalValue & ((1 << numBits) - 1)) | orMask;
    return finalValue;
}

static int readSrcOneBit(void)
{
    srcNumBit--;
    if (srcNumBit < 0) {
        srcNumBit = 7;
        if (srcOffset < srcLength) {
            srcByte = (char)srcPointer[srcOffset++];
        }
        else {
            srcByte = 0;
        }
    }

    return (srcByte >> srcNumBit) & 1;
}

static int readSrcBitfieldArray(unpackArray_t *array, int curIndex)
{
    do {
        if (readSrcOneBit()) {
            curIndex = array->ptr16[(curIndex << 2) + 3];
        }
        else {
            curIndex = array->ptr16[(curIndex << 2) + 2];
        }
    } while (curIndex >= array->length);

    return curIndex;
}

static int readSrcBitfield(void)
{
    int numZeroBits = 0;
    int bitfieldValue = 1;

    while (readSrcOneBit() == 0) {
        numZeroBits++;
    }

    while (numZeroBits > 0) {
        bitfieldValue = readSrcOneBit() + (bitfieldValue << 1);
        numZeroBits--;
    }

    return bitfieldValue;
}

static void initUnpackBlockArray(unpackArray_t *array)
{
    unsigned short tmp[18];
    int i, j;

    memset(tmp, 0, sizeof(tmp));

    for (i = 0; i < 16; i++) {
        tmp[i + 2] = (tmp[i + 1] + freqArray[i + 1]) << 1;
    }

    for (i = 0; i < 18; i++) {
        int startTmp = tmp[i];
        for (j = 0; j < array->length; j++) {
            if (array->ptr8[j].length == i) {
                array->ptr8[j].start = tmp[i]++ & 0xffff;
            }
        }
    }
}

static int initUnpackBlockArray2(unpackArray_t *array)
{
    int i, j;
    int curLength = array->length;
    int curArrayIndex = curLength + 1;
    array->ptr16[(curLength << 2) + 2] = 0xffffffff;
    array->ptr16[(curLength << 2) + 3] = 0xffffffff;
    array->ptr16[(curArrayIndex << 2) + 2] = 0xffffffff;
    array->ptr16[(curArrayIndex << 2) + 3] = 0xffffffff;

    for (i = 0; i < array->length; i++) {
        curLength = array->length;

        int curPtr8Start = array->ptr8[i].start;
        int curPtr8Length = array->ptr8[i].length;

        for (j = 0; j < curPtr8Length; j++) {
            int curMask = 1 << (curPtr8Length - j - 1);
            int arrayOffset;

            if ((curMask & curPtr8Start) != 0) {
                arrayOffset = 3;
            }
            else {
                arrayOffset = 2;
            }

            if (j + 1 == curPtr8Length) {
                array->ptr16[(curLength << 2) + arrayOffset] = i;
                break;
            }

            if (array->ptr16[(curLength << 2) + arrayOffset] == -1) {
                array->ptr16[(curLength << 2) + arrayOffset] = curArrayIndex;
                array->ptr16[(curArrayIndex << 2) + 2] =
                    array->ptr16[(curArrayIndex << 2) + 3] = -1;
                curLength = curArrayIndex++;
            }
            else {
                curLength = array->ptr16[(curLength << 2) + arrayOffset];
            }
        }
    }

    return array->length;
}

static void initUnpackBlock(void)
{
    int i, j, prevValue, curBit, curBitfield;
    int numValues;
    unsigned short tmp[512];
    unsigned long tmpBufLen;

    /* Initialize array 1 to unpack block */

    prevValue = 0;
    for (i = 0; i < array1.length; i++) {
        if (readSrcOneBit()) {
            array1.ptr8[i].length = readSrcBitfield() ^ prevValue;
        }
        else {
            array1.ptr8[i].length = prevValue;
        }
        prevValue = array1.ptr8[i].length;
    }

    /* Count frequency of values in array 1 */
    memset(freqArray, 0, sizeof(freqArray));

    for (i = 0; i < array1.length; i++) {
        numValues = array1.ptr8[i].length;
        if (numValues <= 16) {
            freqArray[numValues]++;
        }
    }

    initUnpackBlockArray(&array1);
    tmpBufLen = initUnpackBlockArray2(&array1);

    /* Initialize array 2 to unpack block */

    if (array2.length > 0) {
        memset(tmp, 0, array2.length);
    }

    curBit = readSrcOneBit();
    j = 0;
    while (j < array2.length) {
        if (curBit) {
            curBitfield = readSrcBitfield();
            for (i = 0; i < curBitfield; i++) {
                tmp[j + i] = readSrcBitfieldArray(&array1, tmpBufLen);
            }
            j += curBitfield;
            curBit = 0;
            continue;
        }

        curBitfield = readSrcBitfield();
        if (curBitfield > 0) {
            memset(&tmp[j], 0, curBitfield * sizeof(unsigned short));
            j += curBitfield;
        }
        curBit = 1;
    }

    j = 0;
    for (i = 0; i < array2.length; i++) {
        j = j ^ tmp[i];
        array2.ptr8[i].length = j;
    }

    /* Count frequency of values in array 2 */
    memset(freqArray, 0, sizeof(freqArray));

    for (i = 0; i < array2.length; i++) {
        numValues = array2.ptr8[i].length;
        if (numValues <= 16) {
            freqArray[numValues]++;
        }
    }

    initUnpackBlockArray(&array2);

    /* Initialize array 3 to unpack block */

    prevValue = 0;
    for (i = 0; i < array3.length; i++) {
        if (readSrcOneBit()) {
            array3.ptr8[i].length = readSrcBitfield() ^ prevValue;
        }
        else {
            array3.ptr8[i].length = prevValue;
        }
        prevValue = array3.ptr8[i].length;
    }

    /* Count frequency of values in array 3 */
    memset(freqArray, 0, sizeof(freqArray));

    for (i = 0; i < array3.length; i++) {
        numValues = array3.ptr8[i].length;
        if (numValues <= 16) {
            freqArray[numValues]++;
        }
    }

    initUnpackBlockArray(&array3);
}

void unpackImage(unsigned char *source, int length, unsigned char** out, int *outlen)
{
    int blockLength, curBlockLength;
    int tmpBufLen, tmpBufLen1;
    int i;

    srcPointer = source;
    srcOffset = 0;
    srcLength = length;

    /*dstPointer = NULL; should malloc */
    dstOffset = 0;

    srcNumBit = 0;
    srcByte = 0;

    tmp16kOffset = 0;
    tmp32kOffset = 0;

    initTmpArray(&array1, 8, 16);
    initTmpArray(&array2, 8, 512);
    initTmpArray(&array3, 8, 16);

    initTmpArrayData(&array1);
    initTmpArrayData(&array2);
    initTmpArrayData(&array3);

    memset(tmp16k, 0, sizeof(tmp16k));

    blockLength = readSrcBits(8);
    blockLength |= readSrcBits(8) << 8;
    //printf("LEN %d\n", blockLength);
    while (blockLength > 0) {
        initUnpackBlock();

        tmpBufLen = initUnpackBlockArray2(&array2);
        tmpBufLen1 = initUnpackBlockArray2(&array3);

        curBlockLength = 0;
        while (curBlockLength < blockLength) {
            int curBitfield = readSrcBitfieldArray(&array2, tmpBufLen);

            if (curBitfield < 256) {
                dstPointer[dstOffset++] =
                    tmp16k[tmp16kOffset++] = curBitfield;
                tmp16kOffset &= 0x3fff;
            }
            else {
                int i;
                int numValues = curBitfield - 0xfd;
                int startOffset;
                curBitfield = readSrcBitfieldArray(&array3, tmpBufLen1);
                if (curBitfield != 0) {
                    int numBits = curBitfield - 1;
                    curBitfield = readSrcBits(numBits) & 0xffff;
                    curBitfield += 1 << numBits;
                }

                startOffset = (tmp16kOffset - curBitfield - 1) & 0x3fff;
                for (i = 0; i < numValues; i++) {
                    dstPointer[dstOffset++] = tmp16k[tmp16kOffset++] =
                        tmp16k[startOffset++];
                    startOffset &= 0x3fff;
                    tmp16kOffset &= 0x3fff;
                }
            }

            curBlockLength++;
        }

        blockLength = readSrcBits(8);
        blockLength |= readSrcBits(8) << 8;
    }
    *out = dstPointer;
    *outlen = dstOffset;
}

static void hex(unsigned char* p, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%02x ", p[i]);
        if (i % 16 == 15) printf("\n");
    }
}

int main0(int argc, char **argv)
{
    int length;
    unsigned char *fileInMem;
    const char* fileName;

    if (argc < 2) {
        printf("no args, use default file\n");
        //return 1;
        fileName = "out.txt";
    }
    else {
        fileName = argv[1];
    }

    fileInMem = (unsigned char*) loadFile(fileName, &length);
    if (fileInMem == NULL) {
        printf("Mem null\n");
        return 1;
    }

    printf("Source %d\n", length);
    hex(fileInMem, _min(100, length));

    unsigned char *out;
    int outlen;
    printf("Unpacking...\n");
    unpackImage(&fileInMem[4], length - 4, &out, &outlen);
    /* Unpacked data is in dstPointer array, with length = dstOffset bytes
       If this length is 163840
         we have a 320x240 image in A1B5G5R5 format
         The image is organized this way in the buffer:
          block 1: 256*256, which is the 0,0,256x240 top left block
          block 2: 128x128, which holds the right part in 2 64x128 blocks
           one will be at 256,0,64x128, the other at 256,128,64x120
       else
         this is a TIM image
    */

    free(fileInMem);

    printf("Dst %d\n", outlen);
    hex(out, _min(100, outlen));

    return 0;
}

