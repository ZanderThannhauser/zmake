
#include "FILE.h"

GDBM_FILE gdbm_open(
    const char *path,
    int a,
    int b,
    int c,
    void (*errorhandler)(const char *));
