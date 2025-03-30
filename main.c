#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "encounter.h"
#include "trap.h"
#include "scenario.h"
#include "monster.h"
#include "dungeon.h"

//Initalize the main function
int main(int argc, char **argv) {
    // Ask player for name and create Player
    char * playerName = getPlayerName();
    
    Player * currentPlayer;  
    currentPlayer = createPlayer(20, 1, 1, 0, playerName);

    // TESTING
    printf("Player's name is %s\n", currentPlayer->name);
    printf("Player's HP is %d\n", currentPlayer->hp);
    printf("Player's attack is %d\n", currentPlayer->att);
    printf("Player's defense is %d\n", currentPlayer->def);
    printf("Player's agility is %d\n", currentPlayer->agl);
    printInventory(currentPlayer->inventory);

    // Start story
    startStory();
}