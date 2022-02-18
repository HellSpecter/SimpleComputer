#include "myReadKey.h"

termios oldSettings;

int rk_readKey(KEYS &key) {
    rk_myTermSave();
    rk_myTermRegime(false, false, false, 0, 1);

    char buffer[8] {};
    read(fileno(stdin), buffer, 8);

    if(strcmp(buffer, "\E[A") == 0)
        key = KEYS::up;
    else if(strcmp(buffer, "\E[B") == 0)
        key = KEYS::down;
    else if(strcmp(buffer, "\E[C") == 0)
        key = KEYS::right;
    else if(strcmp(buffer, "\E[D") == 0)
        key = KEYS::left;
    else if(strcmp(buffer, "\E[15~") == 0)
        key = KEYS::accumulator;
    else if(strcmp(buffer, "\E[17~") == 0)
        key = KEYS::instructionCounter;
    else if(buffer[0] == 'l')
        key = KEYS::load;
    else if(buffer[0] == 's')
        key = KEYS::save;
    else if(buffer[0] == 'r')
        key = KEYS::run;
    else if(buffer[0] == 't')
        key = KEYS::step;
    else if(buffer[0] == 'i')
        key = KEYS::reset;
    else if(buffer[0] == 'q')
        key = KEYS::closeApp;
    else
        key = KEYS::none;

    rk_myTermRestore();
    return 0;
};
// Результатом вызова tcgetattr() и tcsetattr() будет либо 0,
// если параметры получены успешно, либо –1, если возникла какая-то ошибка.
int rk_myTermSave() {
    return tcgetattr(fileno(stdin), &oldSettings);
};

int rk_myTermRestore() {
    return tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
};

int rk_myTermRegime(bool setCanonRegime, bool setEcho, bool setSigint, int vtime, int vmin) {
    rk_myTermSave();
    termios newSettings = oldSettings;

    if(setCanonRegime){
        newSettings.c_lflag |= ICANON;
    } else {
        newSettings.c_lflag &= ~ICANON;
        setEcho ? newSettings.c_lflag |= ECHO : newSettings.c_lflag &= ~ECHO;
        setSigint ? newSettings.c_lflag |= ISIG : newSettings.c_lflag &= ~ISIG;

        newSettings.c_cc[VTIME] = vtime;
        newSettings.c_cc[VMIN] = vmin;
    }

    return tcsetattr(fileno(stdin), TCSANOW, &newSettings);
};