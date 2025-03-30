#ifndef MONSTER_H
#define MONSTER_H
#include "inventory.h"

typedef struct {
    int hp;
    int att;
    int def;
    struct Inventory ** inventory;
    char* name;
} Monster;
#endif

// Method signatures go here
void freeMonster(Monster *monster);
Monster *createMonster(int hp, int att, int def, Item * rewards, char* name);
Monster * generateMonster(char monsterType);


