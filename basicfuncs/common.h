#ifndef __MINE_COMMON_H
#define __MINE_COMMON_H

#include <cstdio>

enum e_direction {
    KEEP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};


#define debug do {printf("%s %d\n", __FUNCTION__, __LINE__); fflush(stdout);} while (0)



class Common {
public:
    static int CommonGetRandomData(void);
};


#endif
