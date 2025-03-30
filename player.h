#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    int hp;
    int att;
    int def;
    int agl;
    struct Inventory * inventory;
    char * name;
} Player;

void freePlayer(Player *player);
Player *createPlayer(int hp, int att, int def, int agl, int gold, char* name);
void *equipStartingPlayer(Player *player);
void heal(Player *player, int hpRegained);
void isPlayerDead(Player *player, int damage);
void adjustStats(Player *player);
#endif