#pragma once


class PlyElement {
protected:
    int count;

    virtual void push(char *str, int countOfLine) {}
    virtual void newLine() {}

public:
    PlyElement() : count(0) {}
    PlyElement(int c) : count(c) {}
    virtual ~PlyElement() {}

    virtual void addProp(char *type, char *name) {}
    virtual void end() {}
    // 将内部缓冲区数据复制到 buf
    virtual void buffer(char* buf) {}
    // 获取内部缓冲区长度, 用于复制数据
    virtual int bufferSize() { return -1; }

    void pushLine(char* buf, int begin, int end) {
        int countOfLine = 0;
        for (int i=begin; i < end; ++i) {
            if (buf[i] == ' ') {
                buf[i] = 0;
                push(buf + begin, countOfLine);
                ++countOfLine;
                begin = i+1;
            }
        }
        if (begin < end) {
            buf[end-1] = 0;
            push(buf + begin, countOfLine);
        }
        newLine();
    }

    int size() {
        return count;
    }
};


class VertexEle : public PlyElement {
private:
    static const int MAX_MAPPER_SIZE = 6;
    static const int X=0, Y=1, Z=2, R=3, G=4, B=5;

    int property_count;
    int mapper[MAX_MAPPER_SIZE];
    float *buf;

public:
    VertexEle(int c) : PlyElement(c), mapper{ X,Y,Z,R,G,B }, buf(0) {}

    ~VertexEle() {
        if (buf) {
            delete[] buf;
            buf = 0;
        }
    }

    virtual void addProp(char *type, char *name) {
        if (property_count >= MAX_MAPPER_SIZE) 
            return;

        if (0 == strcmp(name, "x")) {
            mapper[property_count++] = X;
        }
        else if (0 == strcmp(name, "y")) {
            mapper[property_count++] = Y;
        }
        else if (0 == strcmp(name, "z")) {
            mapper[property_count++] = Z;
        }
        else if (0 == strcmp(name, "red")) {
            mapper[property_count++] = R;
        }
        else if (0 == strcmp(name, "green")) {
            mapper[property_count++] = G;
        }
        else if (0 == strcmp(name, "blue")) {
            mapper[property_count++] = B;
        }
    }

    virtual void end() {
        buf = new float[MAX_MAPPER_SIZE*count];
    }

    virtual void buffer(char* tbuf) {
        memcpy(tbuf, buf, bufferSize());
    }

    virtual int bufferSize() {
        return MAX_MAPPER_SIZE * count * sizeof(float);
    }

protected:
    int pushIndex = 0;

    void push(char *str, int countOfLine) {
        if (countOfLine >= MAX_MAPPER_SIZE) return;
        buf[pushIndex + mapper[countOfLine]] = std::stof(str);
    }

    void newLine() {
        pushIndex += MAX_MAPPER_SIZE;
    }
};


struct PlyTriangleIdx {
   int a, b, c;
   PlyTriangleIdx(int *v) 
   : a(v[0]), b(v[1]), c(v[2]) {}
   PlyTriangleIdx(int q, int w, int e)
   : a(q), b(w), c(e) {}
};


class FaceEle : public PlyElement {
private:
    static const int MAX_V_SIZE = 10;
    std::list<PlyTriangleIdx> triangles;

public:
    FaceEle(int c) : PlyElement(c) {}

protected:
    int vertex[MAX_V_SIZE];
    int index = 0;

    virtual void push(char *str, int countOfLine) {
        if (countOfLine >= MAX_V_SIZE) return;
        vertex[countOfLine] = std::stoi(str);
    }

    void newLine() {
        switch (vertex[0]) {
            case 3:
                triangles.push_back(PlyTriangleIdx(vertex + 1));
                break;

            case 4:
                triangles.push_back(PlyTriangleIdx(vertex[1], vertex[2], vertex[4]));
                triangles.push_back(PlyTriangleIdx(vertex + 2));
                break;
        }
    }

    virtual int bufferSize() {
        return triangles.size() * sizeof(float) * 3;
    }

    virtual void buffer(char* bbuf) {
        int *buf = (int*) bbuf;
        int bi = 0;
        for (auto it = triangles.begin(); it != triangles.end(); ++it) {
            buf[bi++] = it->a;
            buf[bi++] = it->b;
            buf[bi++] = it->c;
        }
    }
};


class PlyParser {
private:
    static const int MAX_ELE_SIZE = 3;

    PlyElement *elements[5];
    int state = 0;
    int curr_element;
    int ei = 0;
    int ec = 0;
    int vertexEleIdx = -1;
    int faceEleIdx = -1;

public:
    PlyParser(char* buf, const size_t len) : curr_element(-1) {
        int ls = 0;
        for (int i = 0; i < len; ++i) {
            if (buf[i] == '\n') {
                _state(ls, i, buf);
                ls = i + 1;
            }
        }
    }

    ~PlyParser() {
        for (int i = 0; i < curr_element; ++i) {
            delete elements[i];
        }
    }

    // 返回的指针需要自行释放
    char* vertexBuf(int& len) {
        if (vertexEleIdx < 0) {
            len = 0;
            return 0;
        }
        len = elements[vertexEleIdx]->bufferSize();
        char *buf = new char[ len ];
        elements[vertexEleIdx]->buffer(buf);
        return buf;
    }

    // 返回的指针需要自行释放
    char* indexBuf(int& len) {
        if (faceEleIdx < 0) {
            len = 0;
            return 0;
        }
        len = elements[faceEleIdx]->bufferSize();
        char *buf = new char[ len ];
        elements[faceEleIdx]->buffer(buf);
        return buf;
    }

    void parseHeader(int begin, int end, char* buf) {
        char *arg[MAX_ELE_SIZE] = {0};
        int ai = 0;

        for (int i = begin; i < end && ai < MAX_ELE_SIZE; ++i) {
            if (buf[i] == ' ') {
                buf[i] = 0;
                arg[ai++] = buf + begin;
                begin = i + 1;
            }
        }
        if (begin < end && ai < MAX_ELE_SIZE) {
            buf[end - 1] = 0;
            arg[ai] = buf + begin;
        }

        if (0== strcmp(arg[0], "element")) {
            if (curr_element >= 0) elements[curr_element]->end();
            ++curr_element;
            int count = std::stoi(arg[2]);

            if (0== strcmp(arg[1], "vertex")) {
                elements[curr_element] = new VertexEle(count);
                vertexEleIdx = curr_element;
            }
            else if (0== strcmp(arg[1], "face")) {
                elements[curr_element] = new FaceEle(count);
                faceEleIdx = curr_element;
            }
        }
        else if (0== strcmp(arg[0], "property")) {
            elements[curr_element]->addProp(arg[1], arg[2]);
        }
        else if (0== strcmp(arg[0], "end_header")) {
            elements[curr_element]->end();
            ++curr_element;
            if (curr_element < 1) {
                throw std::runtime_error("No more elements in ply");
            }
            state = 2;
        }
        else if (0== strcmp(arg[0], "format")) {
            if (0!= strcmp(arg[1], "ascii")) {
                throw std::runtime_error("Only support ascii");
            }
        }
    }

    void _state(int begin, int end, char* buf) {
        while (buf[end-1] == ' ') --end;
        while (buf[begin] == ' ') ++begin;
        //printf("[%x]", begin);

        if (state == 0) {
            if (buf[begin] == 'p' && buf[begin+1] == 'l' 
                    && buf[begin+2] == 'y') {
                state = 1;
                return;
            }
            else {
                throw std::runtime_error("bad ply file");
            }
        }

        if (state == 1) {
            parseHeader(begin, end, buf);
            return;
        }

        if (state == 2) {
            elements[ei]->pushLine(buf, begin, end);
            if (++ec >= elements[ei]->size()) {
                ec = 0;
                if (++ei >= curr_element) {
                    state = 3;
                }
            }
            return;
        }

        if (state == 3) {
            throw std::runtime_error("file end.");
        }
    }
};