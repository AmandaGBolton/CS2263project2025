#ifndef MONSTER_H
#define MONSTER_H
#include "item.h"
#include "player.h"

typedef struct {
    int hp;
    int att;
    int def;
    struct Inventory * inventory;
    char* name;
    int dead;
} Monster;

// Method signatures go here
void freeMonster(Monster *monster);
Monster * createMonster(int hp, int att, int def, Item * rewards, char* name);
Monster * generateMonster(char monsterType);
Monster * pickRandomMonster();
void fightOrFlight(Monster * monster, Player * player);
void fightMonster(Monster * monster, Player * player);
Monster * createSnake();
Monster * createSpider();
Monster * createTroll();
Monster * createGnome();
Monster * createGhost();
Monster * createArmor();
Monster *createSkeleton();
Monster *createMimic();
Monster *createMist();
Monster *createDog();
#endif