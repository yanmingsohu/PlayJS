#include "vm.h"
#include "fs.h"
#include "util.h"
#include "threads.h"

static std::string bootscript = "boot/index.js";
static const threadId ROOT_THREAD_ID = 0;

int main() {
    Welcome w;
    loadScript(bootscript, ROOT_THREAD_ID);
    joinAll();
    return 0;
}