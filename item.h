#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
    char* stat;
    int mod;
    char name[21];
} Item;

void freeItem(Item *item);
Item *createItem(char * stat, int mod, char* name);

Item * generateItem(char * itemType);

Item getLowItem();
Item getMidItem();
Item getHighItem();
#endif