#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dungeon.h"

// Function to create a room
Room *createRoom(int x, int y) {
    Room *room = (Room *)malloc(sizeof(Room));
    if (!room) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    room->x = x;
    room->y = y;
    room->visited = 0;
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

    // Assign the quest treasure room and exit coordinates at creation
    int randomX = rollDice(WIDTH) -1;
    int randomY = rollDice(HEIGHT) -1;
    int randomX2 = rollDice(WIDTH) -1;
    int randomY2 = rollDice(HEIGHT) -1;
    while(randomX == randomX2 && randomY == randomY2){
        randomX2 = rollDice(WIDTH) -1;
        randomY2 = rollDice(HEIGHT) -1;
    }
    dungeon->questX = randomX;
    dungeon->questY = randomY;
    dungeon->exitX = randomX2;
    dungeon->exitY = randomY2;
    
    dungeon->player = dungeon->rooms[0][0];
    dungeon->player->visited = 1;
    return dungeon;
}

// Function to move the player
void movePlayer(Dungeon *dungeon, char direction) {
    Room *current = dungeon->player;
    Room *next = NULL;

    switch (direction) {
        case 'N': next = current->north; break;
        case 'S': next = current->south; break;
        case 'E': next = current->east; break;
        case 'W': next = current->west; break;
        case 'n': next = current->north; break;
        case 's': next = current->south;break;
        case 'e': next = current->east;break;
        case 'w': next = current->west;break;
        default:
            printf("Invalid direction! Use N, S, E, or W.\n");
            return;
    }

    if (next) {
        dungeon->player = next;
        next->visited = 1;
        printf("Moved to room (%d, %d)\n", next->x, next->y);
        displayDungeon(dungeon);
    } else {
        printf("You hit a wall. You can't go that way. Ouch!\n");
    }
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
            Room *room = dungeon->rooms[y][x];
            int north = room->north ? 1 : 0;
            int south = room->south ? 1 : 0;
            int east  = room->east  ? 1 : 0;
            int west  = room->west  ? 1 : 0;

            fprintf(file, "%d %d %d %d %d %d %d\n", 
                room->x, room->y, north, south, east, west, room->visited);
        }
    }

    // Save player position
    fprintf(file, "PLAYER %d %d\n", dungeon->player->x, dungeon->player->y);

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

Dungeon *loadDungeon(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file for reading!\n");
        return NULL;
    }

    Dungeon *dungeon = (Dungeon *)malloc(sizeof(Dungeon));
    if (!dungeon) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Initialize rooms array
    memset(dungeon->rooms, 0, sizeof(dungeon->rooms));

    int x, y, n, s, e, w, v;

    // First pass: create all rooms and store connection info
    while (fscanf(file, "%d %d %d %d %d %d %d", &x, &y, &n, &s, &e, &w, &v) == 7) {
        Room *room = createRoom(x, y);  // Uses your existing function
        dungeon->rooms[y][x] = room;

        // Temporarily store the connection data in the room's x/y (optional)
        room->north = (Room *)(long)n;
        room->south = (Room *)(long)s;
        room->east  = (Room *)(long)e;
        room->west  = (Room *)(long)w;
        room->visited = v;
    }

    // Rewind to find player line
    rewind(file);
    char buffer[64];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "PLAYER", 6) == 0) {
            sscanf(buffer, "PLAYER %d %d", &x, &y);
            if (!dungeon->rooms[y][x]) {
                printf("Warning: loaded player position (%d, %d) is invalid. Defaulting to (0, 0)\n", x, y);
                dungeon->player = dungeon->rooms[0][0];
            } else {
                dungeon->player = dungeon->rooms[y][x];
            }
            dungeon->player->visited = 1;
            break;
        }
    }

    // Second pass: link rooms based on stored flags
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Room *room = dungeon->rooms[y][x];
            if (!room) continue;

            if ((long)room->north == 1 && y > 0)
                room->north = dungeon->rooms[y - 1][x];
            else
                room->north = NULL;

            if ((long)room->south == 1 && y < HEIGHT - 1)
                room->south = dungeon->rooms[y + 1][x];
            else
                room->south = NULL;

            if ((long)room->east == 1 && x < WIDTH - 1)
                room->east = dungeon->rooms[y][x + 1];
            else
                room->east = NULL;

            if ((long)room->west == 1 && x > 0)
                room->west = dungeon->rooms[y][x - 1];
            else
                room->west = NULL;
        }
    }

    fclose(file);
    return dungeon;
}

// Function to display the dungeon layout
void displayDungeon(Dungeon *dungeon) {
    printf("\nDungeon Map:\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (dungeon->player == dungeon->rooms[y][x]) {
                printf("[P] ");
            } else if (dungeon->rooms[y][x]->visited) {
                printf("[x] ");
            } else {
                printf("[ ] ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Recursive function to explore the dungeon
void exploreDungeon(Room *room) {
    if (!room || room->visited) return;

    room->visited = 1;
    printf("Visited room (%d, %d)\n", room->x, room->y);

    exploreDungeon(room->north);
    exploreDungeon(room->south);
    exploreDungeon(room->east);
    exploreDungeon(room->west);
}