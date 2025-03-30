#ifndef DUNGEON_H
#define DUNGEON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "inventory.h"
#include "scenario.h"

#define WIDTH 5
#define HEIGHT 5

typedef struct Room {
    int x, y;
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
void movePlayer(Dungeon *dungeon, char direction);

// Function to save dungeon layout
void saveDungeon(Dungeon *dungeon, const char *filename);

// Function to free memory
void freeDungeon(Dungeon *dungeon);

#endif