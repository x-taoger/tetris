#ifndef __MINE_KEYBOARD_H
#define __MINE_KEYBOARD_H

#include <termios.h>

class Keyboard {
private:
    Keyboard();
    static bool IsHit(void);
    static void* GetKeyboardThread(void *arg);

    static Keyboard* keyboard;
    static bool running;
    pthread_t pid;
    termios *terSetting;

public:
    ~Keyboard();
    static Keyboard* GetInstance();
    int GetInput(void);
};

#endif
