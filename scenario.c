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
        // printf("Generate a trap\n");
        // Traps
        return createScenario(createRandomTrap(), NULL, NULL);
    } else if (r < 66){
        // Encounters
        // printf("Generate an encounter\n");
        return createScenario(NULL, pickRandomEncounter(), NULL);
    } else {
        // Monsters
        // printf("Generate a monster\n");
        return createScenario(NULL, NULL, pickRandomMonster());
    }
}

// THEN TRIGGER THIS USING THE CREATED SCENARIO
// This function triggers the scenario, which will then trigger the appropriate sub-scenario
void triggerScenario(Scenario * scenario, Player * player){
    if (scenario->trap != NULL){
        attemptTrap(player, scenario->trap);
    } else if (scenario->encounter != NULL){
        printf("%s", scenario->encounter->prompt);
         // Check if the prompt contains "5 gold"
        if (strstr(scenario->encounter->prompt, "5 gold") != NULL) {
            if (scenario->encounter->inventory != NULL) {
                describeShop(scenario->encounter->inventory);
                purchaseDialog(player, scenario->encounter->inventory, scenario);
            } else {
                printf("You have found a shop that is out of inventory.\n");
            }
        }
        printf("%s", scenario->encounter->thanksMsg);
    } else if (scenario->monster != NULL){
        if(scenario->monster->dead == 0){
            fightOrFlight(scenario->monster, player);
        } else {
            printf("You have found a room with a dead monster.\n");
        }
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
    printf("\n***************@***************\n");
    printf("Welcome, %s!\n", player->name);
    printf("The village elder has call on you to retrieve a magical goblet that is hidden in the dungeon.\n");
    printf("The goblet is said to have the power to heal the sick and wounded.\n");
    printf("You must find the goblet and return it to the village before it is too late.\n");
    printf("\n");
    printf("But beware, the dungeon is full of traps, monsters, and other dangers.\n");
    printf("And you realize the way out is NOT the way in as they drop you into a hole.\n");
    printf("\n");
    printf("You have been given a sword and armor, one health potion, and 5 gold to start.\n");
    printf("You have 20 HP, and healing potions will heal 5 HP.");
    printf("Good luck!\n");
    printf("***************@***************\n\n");
}

void initializeRandom() {
    srand((unsigned int)time(NULL)); // Seed the random number generator
}

// Random number between 1 and 100
int getRandomNumber() {
    int num = rand()%100 + 1;
    // printf("Generated random number: %d", num);
    return num;
}

// Random number between 1 and 20
int getRandomNumber20() {
    int num = rand()%20 + 1;
    // printf("Generated random number: %d", num);
    return num;
}

// Random number between 1 and sides
// This could replace the other two but I don't want to search and change them
int rollDice(int sides) {
    int num = rand()%sides + 1;
    // printf("Generated random number: %d", num);
    return num;
}