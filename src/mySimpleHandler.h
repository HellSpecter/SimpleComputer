#ifndef ARCHITECT_MYSIMPLEHANDLER_H
#define ARCHITECT_MYSIMPLEHANDLER_H
#include "mySimpleComputer.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <array>
#include <sys/ioctl.h>
#include <unistd.h>
#include <csignal>
#include <sys/time.h>

void sh_reset();
void sh_run();
void setTimer(long interval);
void signalReset(int signal);
void signalHandler(int signal);
int printAll();
int mainLogic();

#endif //ARCHITECT_MYSIMPLEHANDLER_H
