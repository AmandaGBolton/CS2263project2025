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
    printf("COORDS TO CHEAT ARE %d, %d & %d, %d\n", dungeon->questX, dungeon->questY, dungeon->exitX, dungeon->exitY);

    printf("Use N, S, E, W to move. H to heal. I to show current inventory. Q to quit.\n");
    char command;
    while (1) {
        printf("Enter command: ");
        scanf(" %c", &command);
        if (command == 'Q' || command == 'q') break;
        if (command == 'H' || command == 'h') {
            healPlayer(currentPlayer, 1);
            continue;
        }
        if (command == 'i' || command == 'I') {
            displayInventory(currentPlayer->inventory);
            continue;
        }
        movePlayer(dungeon, command);

        // Get the player's current position
        int currentX = dungeon->player->x;
        int currentY = dungeon->player->y;

        // Access the current room
        Room *currentRoom = dungeon->rooms[currentY][currentX];

        // Assign a scenario if the room's scenario is NULL
        if (currentRoom->scenario == NULL) {
            if (currentX == dungeon->questX && currentY == dungeon->questY) {
                // Assign the quest scenario
                currentRoom->scenario = createQuestRoom();
            } else if (currentX == dungeon->exitX && currentY == dungeon->exitY) {
                // Assign the exit scenario
                currentRoom->scenario = createExitRoom();
            } else {
                // Assign a random scenario
                currentRoom->scenario = pickScenario();
            }
        } else {
            if(currentX == dungeon->exitX && currentY == dungeon->exitY) {
                    if(hasGoblet(currentPlayer) == 1) {
                    printf("You have found the exit with the goblet and have won the game!\n");
                    break;
                    }
            }
        }

        triggerScenario(dungeon->rooms[currentY][currentX]->scenario, currentPlayer);
    }

    // Save and free dungeon
    saveDungeon(dungeon, "dungeon.txt");
    freeDungeon(dungeon);
    printf("Game over. Dungeon saved!\n");

    // TESTING 
    // Scenario * currentScenario = pickScenario();
}