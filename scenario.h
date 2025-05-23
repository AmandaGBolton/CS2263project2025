#ifndef SCENARIO_H
#define SCENARIO_H
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "trap.h"
#include "monster.h"

// Forward declaration of Encounter
struct Encounter;
typedef struct Encounter Encounter;

typedef struct Scenario {
    Encounter * encounter;
    Trap * trap;
    Monster * monster;
} Scenario;

Scenario * createScenario(Trap * trap, Encounter * encounter, Monster * monster);
void freeScenario(Scenario * scenario);
Scenario * pickScenario();
void triggerScenario(Scenario * scenario, Player * player);
Scenario * createQuestRoom();
Scenario * createExitRoom();
void startStory(Player * player);
void initializeRandom();
int getRandomNumber();
int getRandomNumber20();
int rollDice(int sides);
#endif