#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "vm.h"
#include "js.h"


void freeImage(void *data) {
    stbi_image_free(data);
}


JSS_FUNC(load, args, ac) {
    JSS_CHK_ARG(1, load(filename));
    std::string fn = stringValue(args[1]);
    int x, y, channels;
    unsigned char *data = stbi_load(fn.c_str(), &x, &y, &channels, 0);
    if (! data) {
        pushException("cannot load image");
        return 0;
    }
    JsValueRef jsbuf = 0;
    JsCreateExternalArrayBuffer(data, x*y*channels, freeImage, data, &jsbuf);

    LocalVal ret = JVM->createObject();
    ret.put("data", jsbuf);
    ret.put("x", wrapJs(x));
    ret.put("y", wrapJs(y));
    ret.put("channels", wrapJs(channels));
    return ret;
}


JSS_INIT_MODULE(installImage) {
    JSS_MOD(image);
    JSS_BIND(load);
}