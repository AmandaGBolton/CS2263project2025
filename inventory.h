#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"

typedef struct Inventory {
    // This will need to be a linked list
    // So inventory is a series of nodes where each node is an Item
    // Using pointers to items instead of actual items to make it easier to add/remove items from memory
    struct Item * item;
    struct Inventory *next;
    struct Inventory *prev;
} Inventory;

// Method signatures here

#endif