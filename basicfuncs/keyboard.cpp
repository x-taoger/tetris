#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <termio.h>
#include <sys/select.h>
#include "common.h"
#include "keyboard.h"


/* class static value */
Keyboard* Keyboard::keyboard = nullptr;
bool Keyboard::running = true;


/* static value */
static int s_getChar = 0;


/* private function */

Keyboard::Keyboard() {
    pthread_t pid = -1;
    this->terSetting = new termios();

    /* set keyboard not echo and don't need enter */
    tcgetattr(STDIN_FILENO, this->terSetting);
    tcflag_t flag = this->terSetting->c_lflag;
    this->terSetting->c_lflag &= ~ICANON;
    this->terSetting->c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, this->terSetting);
    this->terSetting->c_lflag = flag;

    if (pthread_create(&this->pid, nullptr, Keyboard::GetKeyboardThread, nullptr) != 0) {
        std::cout << __FUNCTION__ << " exec error!" << std::endl;
        delete this->terSetting;
        exit(0);
    }
}

bool Keyboard::IsHit(void) {
    fd_set rfds;
    struct timeval tv;
    int retVal;
    
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    tv.tv_sec = 0;
    tv.tv_usec = 1000 * 10;

    retVal = select(1, &rfds, NULL, NULL, &tv);
    if (retVal < 0) return false;
    else if (retVal == 0) return false; /* timeout */
    else return true;
}

/* todo : set direction key by user */
void* Keyboard::GetKeyboardThread(void *arg) {
    while (Keyboard::running) {
        if (!Keyboard::IsHit()) continue;
        switch (getchar()) {
            case 'w' : s_getChar = UP; break;
            case 's' : s_getChar = DOWN; break;
            case 'a' : s_getChar = LEFT; break;
            case 'd' : s_getChar = RIGHT; break;
            default : s_getChar = KEEP; break;
        }
    }
}


/* public function */

Keyboard::~Keyboard() {
    running = false;
    pthread_join(this->pid, NULL);
    tcsetattr(STDIN_FILENO, TCSANOW, this->terSetting);
    delete this->terSetting;
    keyboard = nullptr;
}

Keyboard* Keyboard::GetInstance() {
    if (keyboard == nullptr) keyboard = new Keyboard;
    return keyboard;
}

int Keyboard::GetInput(void) {
    int ret = s_getChar;
    s_getChar = KEEP;
    return ret;
}
