#ifndef TRAP_H
#define TRAP_H 
#include "item.h"

typedef struct Trap {
    // Story prompts.
    char * prompt;
    char * failStory;
    char * successStory;

    // Damage dealt by the trap & how to avoid.
    int damage;
    char * damageType;
    int savingThrowReq;

    // Reward for successfully avoiding the trap if applicable
    Item * reward;

} Trap;

Trap * createTrap(char* prompt, char* failStory, char* successStory, int damage, char* damageType, int savingThrowReq);
void freeTrap(Trap * trap);

#endif