#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"
#include "player.h"

typedef struct Inventory {
    // This will need to be a linked list
    // So inventory is a series of nodes where each node is an Item
    // Using pointers to items instead of actual items to make it easier to add/remove items from memory
    struct Item * item;
    struct Inventory *next;
    struct Inventory *prev;
} Inventory;

// Method signatures here
Inventory * createInventoryNode(Item * item, Inventory * prev, Inventory * next);
void freeInventory(Inventory *inventory);
void starterInventory(Player *player);
void addToInventory(Inventory *inventory, Item *item);
void pickUpItem(Player *player, Item *item);
void dropItem(Inventory *inventory, char *itemName, int num);
Item * findItem(Inventory *inventory, char *itemName);
void printInventory(Inventory *inventory);
int isInInventory(Inventory * list, Item * item);
#endif