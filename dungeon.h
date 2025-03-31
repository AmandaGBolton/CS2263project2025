#ifndef DUNGEON_H
#define DUNGEON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "inventory.h"
#include "scenario.h"

#define WIDTH 10
#define HEIGHT 10

typedef struct Room {
    int x, y;
    int visited;
    struct Room *north, *south, *east, *west;
} Room;

typedef struct {
    Room *rooms[HEIGHT][WIDTH];
    Room *player;
} Dungeon;

// Function to create a room
Room *createRoom(int x, int y);

// Function to generate dungeon
Dungeon *createDungeon();

// Function to move the player
void movePlayer(Dungeon *dungeon, char direction); // Updated to void

// Function to save dungeon layout
void saveDungeon(Dungeon *dungeon, const char *filename); // No change

//function to free memory
void freeDungeon(Dungeon *dungeon);

// Function to load dungeon layout
Dungeon *loadDungeon(const char *filename);

// Function to display the dungeon layout
void displayDungeon(Dungeon *dungeon);
// Recursive function to explore the dungeon
void exploreDungeon(Room *room);

#endif