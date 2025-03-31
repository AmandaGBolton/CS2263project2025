#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "item.h"  
#include "inventory.h"
#include "trap.h"
#include "encounter.h"
#include "scenario.h"

Trap * createTrap(char* prompt, char* failStory, char* successStory, int damage, char* damageType, int savingThrowReq, Item * reward){
    Trap * trap = (Trap *)malloc(sizeof(Trap));
    if (!trap) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    trap->prompt = strdup(prompt);
    if (!trap->prompt) {
        printf("Memory allocation for prompt failed!\n");
        free(trap);
        exit(1);
    }

    trap->failStory = strdup(failStory);
    if (!trap->failStory) {
        printf("Memory allocation for failStory failed!\n");
        free(trap->prompt);
        free(trap);
        exit(1);
    }

    trap->successStory = strdup(successStory);
    if (!trap->successStory) {
        printf("Memory allocation for successStory failed!\n");
        free(trap->failStory);
        free(trap->prompt);
        free(trap);
        exit(1);
    }

// Copy the damageType string
    trap->damageType = strdup(damageType);
    if (!trap->damageType) {
        printf("Memory allocation for damageType failed!\n");
        free(trap->successStory);
        free(trap->failStory);
        free(trap->prompt);
        free(trap);
        exit(1);
    }

    trap->damage = damage;
    trap->savingThrowReq = savingThrowReq;
    trap->reward = reward;
    return trap;    
}

void freeTrap(Trap * trap){
    free(trap->reward);
    free(trap->damageType);
    free(trap->successStory);
    free(trap->failStory);
    free(trap->prompt);
    free(trap);
}

// This runs the trap scenario and handles the die roll and outcome
void attemptTrap(Player * player, Trap * trap){
    printf("%s\n", trap->prompt);
    int savingThrowMod = 0;
    if (strcmp(trap->damageType, "AGILITY") == 0){
        savingThrowMod = player->agl;
    } else if (strcmp(trap->damageType, "ENDURANCE") == 0){
        savingThrowMod = player->def;
    } else if (strcmp(trap->damageType, "STRENGTH") == 0){
        savingThrowMod = player->att;
    } else {
        savingThrowMod = 0;
    }

    int savingThrow = rollDice(20) + savingThrowMod;
    
    printf("You rolled a %d including your +%d modifier.\n", savingThrow, savingThrowMod);

    if (savingThrow >= trap->savingThrowReq){
        printf("%s\n", trap->successStory);
        if (trap->reward != NULL){
            pickUpItem(player, trap->reward);
            adjustStats(player);
        }
        
    } else {
        printf("%s\n", trap->failStory);
        isPlayerDead(player, trap->damage);
    }
}

Trap * createSpikeTrap(){
    Trap * spikeTrap = createTrap("As you enter the room, you accidentally stop onto a pressure plate. Quick, get out of the way!", "You stumble as you try to move quickly. Spikes shoot out of the walls, dealing 2 damage.", "You manage to quickly jump ahead and avoid the spikes that shoot suddenly out from the wall.", 2, "AGILITY", 10, NULL);
    return spikeTrap;
}

Trap * createRockTrap() {
    Item * reward = getLowItem();
    Trap * rockTrap = createTrap("You hear a click as you step into the room. You look up to see a large rock swinging down from the ceiling.", "You try to dodge the rock, but it hits you for 3 damage.", "You manage to dodge the rock as it swings down from the ceiling, avoiding the damage.", 3, "AGILITY", 12, reward);
    return rockTrap;
}

Trap * createHarpyTrap() {
    Trap * harpyTrap = createTrap("You hear a loud screech as you enter the room. You look up to see a harpy staring at you with mezmerizing eyes.", "The harpy screams loudly, causing you to recoil. 1 damage.", "You manage to ignore the screaming harpy and avoid its gaze.", 1, "ENDURANCE", 10, NULL);
    return harpyTrap;
}

Trap * createGravityTrap() {
    Trap * gravityTrap = createTrap("You step into the room and suddenly you feel extremely heavy and collapse to the floor.", "You slowly crawl across the floor, scraping your body on sharp rocks. Take 2 damage.", "You manage to stand, slowly making your way safely across the room.", 2, "STRENGTH", 10, NULL);
    return gravityTrap;
}

Trap * rotatingRoomTrap() {
    Item * reward = getMidItem();
    Trap * rotatingRoom = createTrap("You enter the room and see a large stone door close behind you. You hear a loud grinding noise as the room begins to rotate.", "You stumble as the room rotates, but manage to make it out safely.", "You manage to keep your balance as the room rotates, and even spot something glittering near the doorway.", 0, "AGILITY", 10, reward);
    return rotatingRoom;
}

// These are the not-traps but it is easier to just lump this together.
Trap * emptyRoom() {
    Item * reward = createItem("GOLD", 5, "coin purse");
    Trap * empty = createTrap("You enter the room and see nothing but dust and cobwebs.", "You sneeze loudly.", "You look around the room and manage to find one gold.", 0, "NONE", 5, reward);
    return empty;
}

Trap * treasureRoom() {
    Item * reward = getMidItem();
    Trap * treasure = createTrap("You enter the room and see a large chest in the center of the room. You open it an discover some nice loot!", NULL, NULL, 0, "NONE", 10, reward);
    return treasure;
}

Trap * skullRoom() {
    Item * reward = createItem("ATT", 2, "strength amulet");
    Trap * skull = createTrap("You enter the room and see a large skull in the center of the room. You look inside and find an unusual amulet.", NULL, NULL, 0, "NONE", 1, reward);
    return skull;
}

Trap * createRandomTrap(){
    int r = getRandomNumber();
    if (r < 15){
        return createSpikeTrap();
    } else if (r < 25){
        return createRockTrap();
    } else if (r < 35){
        return createHarpyTrap();
    } else if (r < 45){
        return createGravityTrap();
    } else if (r < 55){
        return rotatingRoomTrap();
    } else if (r < 65){
        return skullRoom();
    } else if (r < 75){ 
        return treasureRoom();
    } else {
        return emptyRoom();
    }
}