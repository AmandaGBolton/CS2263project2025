#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "encounter.h"
#include "trap.h"
#include "scenario.h"

// Scenario attaches to a room, Player also attaches to a room separately
// It holds whatever NPC encounter, monster, or trap is present
// Normally only ONE of those will be present, the others will be NULL
Encounter * createScenario(Trap * trap, Encounter * encounter, Monster * monster){
    Scenario * scenario = (Scenario *)malloc(sizeof(Scenario));
    if (!scenario) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    scenario->trap = trap;
    scenario->encounter = encounter;
    scenario->monster = monster;
    return scenario;    
}

void freeScenario(Scenario * scenario){
    free(scenario);
}

// TRIGGER THIS ON ROOM CREATION
Scenario * pickScenario(){
    // Randomly pick a scenario
    int r = getRandomNumber();
    if (r < 20){
        // Traps
        return createScenario(createRandomTrap(), NULL, NULL);
    } else if (r < 66){
        // Encounters
        return createScenario(NULL, pickRandomEncounter(), NULL);
    } else {
        // Monsters
        return createScenario(NULL, NULL, pickRandomMonster());
    }
}

// THEN TRIGGER THIS USING THE CREATED SCENARIO
// This function triggers the scenario, which will then trigger the appropriate sub-scenario
void triggerScenario(Scenario * scenario, Player * player){
    if (scenario->trap != NULL){
        attemptTrap(player, scenario->trap);
    } else if (scenario->encounter != NULL){
        describeShop(scenario->encounter->inventory);
        purchaseDialog(player, scenario->encounter->inventory);
    } else if (scenario->monster != NULL){
        fightMonster(player, scenario->monster);
    } else {
        printf("You have found an empty room.\n");
    }
}

Scenario * createQuestRoom(){
    return createScenario(NULL, createQuestEncounter(), NULL);
}