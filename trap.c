#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "item.h"  
#include "inventory.h"
#include "monsters.h"
#include "trap.h"
#include "encounter.h"

Trap * createTrap(char* prompt, char* failStory, char* successStory, int damage, char* damageType, int savingThrowReq, Item * reward){
    Trap * trap = (Trap *)malloc(sizeof(Trap));
    if (!trap) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    trap->prompt = prompt;
    trap->failStory = failStory;
    trap->successStory = successStory;
    trap->damage = damage;
    trap->damageType = damageType;
    trap->savingThrowReq = savingThrowReq;
    trap->reward = reward;
    return trap;    
}

void freeTrap(Trap * trap){
    free(trap->prompt);
    free(trap->failStory);
    free(trap->successStory);
    free(trap);
}

void attemptTrap(Player * player, Trap * trap){
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

    int savingThrow = getRandomNumber() + savingThrowMod;
    if (savingThrow >= trap->savingThrowReq){
        printf("%s\n", trap->successStory);
        if (trap->reward != NULL){
            pickUpItem(player->inventory, trap->reward);
            adjustStats(player);
        }
        
    } else {
        printf("%s\n", trap->failStory);
        player->hp -= trap->damage;
        checkIfPlayerDead(player, trap);
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
}

Trap * rotatingRoomTrap() {
    Item * reward = getMidItem();
    Trap * rotatingRoom = createTrap("You enter the room and see a large stone door close behind you. You hear a loud grinding noise as the room begins to rotate.", "You stumble as the room rotates, but manage to make it out safely.", "You manage to keep your balance as the room rotates, and even spot something glittering near the doorway.", 0, "AGILITY", 10, reward);
    return rotatingRoom;
}
// These are the not-traps but it is easier to just lump this together.
Trap * emptyRoom() {
    Item * reward = createCoinPurse(1);
    Trap * empty = createTrap("You enter the room and see nothing but dust and cobwebs.", "You sneeze loudly.", "You look around the room and manage to find one gold.", 0, "NONE", 5, reward);
    return empty;
}

Trap * treasureRoom() {
    Item * reward = getMidItem();
    Trap * treasure = createTrap("You enter the room and see a large chest in the center of the room. You open it an discover some nice loot!", NULL, NULL, 0, "NONE", 10, reward);
    return treasure;
}

Trap * skullRoom() {
    Item * reward = createStrengthAmulet();
    Trap * skull = createTrap("You enter the room and see a large skull in the center of the room. You look inside and find an unusual amulet.", NULL, NULL, 0, "NONE", 1, reward);
    return skull;
}
