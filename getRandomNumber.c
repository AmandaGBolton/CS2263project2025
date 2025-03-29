#include <stdlib.h>
#include <time.h>

// Random number between 1 and 100
int getRandomNumber() {
    srand(time(NULL));
    int num = rand()%100 + 1;
    return num;
}

int getRandomNumber20() {
    srand(time(NULL));
    int num = rand()%20 + 1;
    return num;
}