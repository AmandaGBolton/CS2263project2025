#ifndef ENCOUNTER_H
#define ENCOUNTER_H
#include "player.h"
#include "item.h"
#include "inventory.h"

typedef struct Encounter {
    // Story prompt. Includes NPCs.
    char * prompt;
    Inventory ** inventory;
    char * thanksMsg;
    
} Encounter;


#endif