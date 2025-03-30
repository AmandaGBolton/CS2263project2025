#ifndef ENCOUNTER_H
#define ENCOUNTER_H
#include "player.h"
#include "item.h"
#include "inventory.h"

typedef struct Encounter {
    // Story prompt. Includes NPCs.
    char * prompt;
    Inventory * inventory;
    char * thanksMsg;
    
} Encounter;

void freeEncounter(Encounter * encounter);
Encounter * createEncounter(char* prompt, Inventory * inventory, char * thanksMsg);
void describeShop(Inventory * inventory);
void purchaseDialog(Player * player, Inventory * shop);
void purchaseItem(Player * player, Inventory * shop, char * itemName);  
#endif