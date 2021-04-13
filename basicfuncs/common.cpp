#include "common.h"


int Common::CommonGetRandomData(void) {
    const char *filename = "/dev/urandom";
    int data;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        return data;
    }
    fread(&data, sizeof(data), 1, fp);
    fclose(fp);
    return data;
}
