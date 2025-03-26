#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"

typedef struct Inventory {
    struct Item **items;
} Inventory;

#endif