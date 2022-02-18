#ifndef ARCHITECT_MYREADKEY_H
#define ARCHITECT_MYREADKEY_H

#include <termios.h>
#include <cstdio>
#include <cstring>
//#include <fcntl.h>
#include <unistd.h>


enum KEYS {
    none,
    load,
    save,
    run,
    step,
    reset,
    accumulator,        // F5
    instructionCounter, // F6
    up,
    down,
    left,
    right,
    closeApp,
};

int rk_readKey(KEYS &key);
int rk_myTermSave();
int rk_myTermRestore();
int rk_myTermRegime(bool setCanonRegime, bool setEcho, bool setSigint, int vtime, int vmin);

#endif //ARCHITECT_MYREADKEY_H
