#include <stdio.h>
#include <string.h>

#define INVENTORY_SIZE 20

// struct for inventory
typedef struct Inventory {
    char *items[INVENTORY_SIZE];  // array of items
    int size;  // number of items in inventory
} Inventory;

// initializes inventory
void initializeInventory(Inventory *inventory) {
    inventory->size = 0;
}

// adds to inventory with checks for size, prints item that was picked up
void pickUpItem(Inventory *inventory, const char *itemName) {
    if (inventory->size < INVENTORY_SIZE) {
        inventory->items[inventory->size] = (char *)itemName;
        inventory->size++;
        printf("Picked up: %s\n", itemName);
    }
}

// remove item from inventory
void dropItem(Inventory *inventory, const char *itemName) {
    int foundIndex = -1;
    for (int i = 0; i < inventory->size; i++) {
        if (strcmp(inventory->items[i], itemName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // fixes array moving stuff to the left one and corrects size variable
        for (int i = foundIndex; i < inventory->size - 1; i++) {
            inventory->items[i] = inventory->items[i + 1];
        }
        inventory->size--;
        printf("Dropped: %s\n", itemName);
    }
}

// function to display inventory
void displayInventory(Inventory *inventory) {
    if (inventory->size == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("Inventory contents:\n");
    for (int i = 0; i < inventory->size; i++) {
        printf("- %s\n", inventory->items[i]);
    }
}
