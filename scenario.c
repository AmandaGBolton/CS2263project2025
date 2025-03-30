#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "encounter.h"
#include "trap.h"
#include "monster.h"
#include "scenario.h"

// Scenario attaches to a room, Player also attaches to a room separately
// It holds whatever NPC encounter, monster, or trap is present
// Normally only ONE of those will be present, the others will be NULL
Scenario * createScenario(Trap * trap, Encounter * encounter, Monster * monster){
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
// FROM ROOM, if it is time for quest room, return quest room
    //If quest room is already done, return exit room
    // Otherwise, cal this method to get a random room
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
        fightOrFlight(scenario->monster, player);
    } else {
        printf("You have found an empty room.\n");
    }
}

Scenario * createQuestRoom(){
    return createScenario(NULL, createQuestEncounter(), NULL);
}

Scenario * createExitRoom(){
    return createScenario(NULL, createExitEncounter(), NULL);
}

void startStory(Player * player){
    printf("***************@***************\n");
    printf("Welcome, %s\n!", player->name);
    printf("The village elder has call on you to retrieve a magical goblet that is hidden in the dungeon.\n");
    printf("The goblet is said to have the power to heal the sick and wounded.\n");
    printf("You must find the goblet and return it to the village before it is too late.\n");
    printf("-------------------------------\n");
    printf("But beware, the dungeon is full of traps, monsters, and other dangers.\n");
    printf("And you realize the way out is NOT the way in as they drop you into a hole.");
    printf("-------------------------------\n");
    printf("You have been given a sword and armor, one health potion, and 5 gold to start.\n");
    printf("You have 20 HP, and healing potions will heal 5 HP.");
    printf("Good luck!\n");
    printf("***************@***************\n");
}

// Random number between 1 and 100
int getRandomNumber() {
    srand((unsigned int)time(NULL));
    int num = rand()%100 + 1;
    return num;
}

// Random number between 1 and 20
int getRandomNumber20() {
    srand((unsigned int)time(NULL));
    int num = rand()%20 + 1;
    return num;
}

// Random number between 1 and sides
int rollDice(int sides) {
    srand((unsigned int)time(NULL));
    int num = rand()%sides + 1;
    return num;
}