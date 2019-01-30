#include <iostream>

#include "vm.h"
#include "fs.h"
#include "export-js.h"


int main() {
    std::string filename = "boot/index.js";
    std::string code;
    if (FAILED == readTxtFile(filename, code)) {
        std::cout << "Read boot file error" << std::endl;
        return 1;
    }

	VM vm;
    installConsole(&vm);
    installFileSystem(&vm);
    installUtf(&vm);

    JsErrorCode r = vm.loadModule(0, filename, code);
    if (r) {
        std::cout << "Load Module failed " << r << std::endl;
    }

    LocalVal err = vm.checkError();
    if (err.notNull()) {
        LocalVal st = err.get("stack");
        if (st.notNull()) {
            std::cout <<"Exit on failed "<< st << std::endl;
        } else {
            std::cout <<"Exit on failed "<< err << std::endl;
        }
    }
    return r;
}
