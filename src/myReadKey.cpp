#include "myReadKey.h"

termios oldSettings;

int rk_readKey(KEYS *key) {

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