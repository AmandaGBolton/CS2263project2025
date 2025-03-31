#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dungeon.h"

#define WIDTH 5
#define HEIGHT 5

// Function to create a room
Room *createRoom(int x, int y) {
    Room *room = (Room *)malloc(sizeof(Room));
    if (!room) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    room->x = x;
    room->y = y;
    room->north = room->south = room->east = room->west = NULL;
    return room;
}

// Function to generate dungeon
Dungeon *createDungeon() {
    Dungeon *dungeon = (Dungeon *)malloc(sizeof(Dungeon));
    if (!dungeon) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    memset(dungeon->rooms, 0, sizeof(dungeon->rooms));
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            dungeon->rooms[y][x] = createRoom(x, y);
        }
    }
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Room *room = dungeon->rooms[y][x];
            if (y > 0) room->north = dungeon->rooms[y - 1][x];
            if (y < HEIGHT - 1) room->south = dungeon->rooms[y + 1][x];
            if (x > 0) room->west = dungeon->rooms[y][x - 1];
            if (x < WIDTH - 1) room->east = dungeon->rooms[y][x + 1];
        }
    }
    
    dungeon->player = dungeon->rooms[0][0];
    return dungeon;
}

// Function to move the player
void movePlayer(Dungeon *dungeon, char direction) {
    Room *current = dungeon->player;
    switch (direction) {
        case 'N': if (current->north) dungeon->player = current->north; break;
        case 'S': if (current->south) dungeon->player = current->south; break;
        case 'E': if (current->east) dungeon->player = current->east; break;
        case 'W': if (current->west) dungeon->player = current->west; break;
        default: printf("You've bumped into a wall! Ouch.\n"); return;
    }
    printf("Moved to room (%d, %d)\n", dungeon->player->x, dungeon->player->y);
}

// Function to save dungeon layout
void saveDungeon(Dungeon *dungeon, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing!\n");
        return;
    }
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fprintf(file, "%d %d\n", dungeon->rooms[y][x]->x, dungeon->rooms[y][x]->y);
        }
    }
    fclose(file);
}

// Function to free memory
void freeDungeon(Dungeon *dungeon) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            free(dungeon->rooms[y][x]);
        }
    }
    free(dungeon);
}

int main() {
    Dungeon *dungeon = createDungeon();
    char command;
    printf("Use N, S, E, W to move. Q to quit.\n");
    
    while (1) {
        printf("Enter command: ");
        scanf(" %c", &command);
        if (command == 'Q') break;
        movePlayer(dungeon, command);
    }
    
    saveDungeon(dungeon, "dungeon.txt");
    freeDungeon(dungeon);
    printf("Game over. Dungeon saved!\n");
    return 0;
}
