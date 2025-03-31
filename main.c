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
    initializeRandom();

    // Ask player for name and create Player
    char * playerName = getPlayerName();
    
    Player * currentPlayer;  
    currentPlayer = createPlayer(20, 1, 1, 0, playerName);

    // TESTING Player initialization only:
    // printf("Player's name is %s\n", currentPlayer->name);
    // printf("Player's HP is %d\n", currentPlayer->hp);
    // printf("Player's attack is %d\n", currentPlayer->att);
    // printf("Player's defense is %d\n", currentPlayer->def);
    // printf("Player's agility is %d\n", currentPlayer->agl);
    displayInventory(currentPlayer->inventory);

    // Start story
    startStory(currentPlayer);

    // Create dungeon and load previous state if exists
    Dungeon *dungeon = NULL;
    FILE *f = fopen("dungeon.txt", "r");
    if (f) {
        fclose(f);
        dungeon = loadDungeon("dungeon.txt");
        printf("Loaded saved dungeon.\n");
    } else {
        dungeon = createDungeon();
        dungeon->player->visited = 1; // Mark starting room as visited
        printf("Created new dungeon.\n");
    }

    // Display the dungeon layout
    displayDungeon(dungeon);

    printf("Use N, S, E, W to move. Q to quit.\n");
    char command;
    while (1) {
        printf("Enter command: ");
        scanf(" %c", &command);
        if (command == 'Q') break;
        movePlayer(dungeon, command);
    }

    // Save and free dungeon
    saveDungeon(dungeon, "dungeon.txt");
    freeDungeon(dungeon);
    printf("Game over. Dungeon saved!\n");

    // TESTING 
    Scenario * currentScenario = pickScenario();
    triggerScenario(currentScenario, currentPlayer);
}