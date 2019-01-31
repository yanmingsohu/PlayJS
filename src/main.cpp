#include "vm.h"
#include "fs.h"
#include "util.h"
#include "threads.h"

static std::string bootscript = "boot/index.js";

int main() {
    Welcome w;
    loadScript(bootscript);
    joinAll();
    return 0;
}