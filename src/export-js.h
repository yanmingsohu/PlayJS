#pragma once

#include "vm.h"

void installConsole(VM*);
void installFileSystem(VM*);
void installUtf(VM*);
void installThread(VM*);
void installEvents(VM* vm);
void destoryEvents(VM* vm);