#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

// Saving player should record current stats (incld HP) and inventory^

int getRandomNumber();

// Function to free a player from memory (e.g., on death)
void freeItem(Item *item) {
    free(item);
}

// Function to create an Item
// GOLD and POTTIONS are stackable, so in Inventory need to stack them
Item * createItem(char * stat, int mod, char* name) {
    Item *item = (Item *)malloc(sizeof(Item));
    if (!item) {
        printf("Memory allocation for item creation failed!\n");
        exit(1);
    }
    item->stat = stat;
    item->mod = mod;
    item->name = name;
    return item;
}

// Statement to create an item based on type and number, calls main item constructor
// Pass in the name of what you want and how many
// Method uses a helper to translate string into char used by switch
Item * generateItem(char * itemType, int num){
    char desiredItem = getItemType(itemType);

    switch(desiredItem) {
        case 'p':
            Item * item = createItem('HP', 1, "healing potion");
            return item;
        case 'r':
            Item * item = createItem('AGL', 1, "agility ring");
            return item;
        case 'g':
            Item * item = createItem('AGL', 2, "agility amulet");
            return item;
        case 't':
            Item * item = createItem('ATT', 2, "strength amulet");
            return item;
        case 's':
            Item * item = createItem('ATT', 1, "sword");
            return item;
        case 'b':
            Item * item = createItem('ATT', 2, "bronze sword");
            return item;
        case 'i':
            Item * item = createItem('ATT', 3, "iron sword");
            return item;
        case 'm':
            Item * item = createItem('ATT', 4, "mythic sword");
            return item;
        case 'A':
            Item * item = createItem('DEF', 1, "armor");
            return item;
        case 'B':
            Item * item = createItem('DEF', 2, "bronze armor");
            return item;
        case 'I"':
            Item * item = createItem('DEF', 3, "iron armor");
            return item;
        case 'M':
            Item * item = createItem('DEF', 4, "mythic armor");
            return item;
        case 'c':
            Item * item = createItem('GOLD', num, "coin purse");
            return item;
        case 'P':
            Item * item = createItem('POTION', num, "potion belt");
            return item;
        default:
            printf("Invalid item type.\n");
            return NULL;
    }
}

char desiredItem(char * itemName) {
     if(itemName == "potion") {
        return 'p';
    } else if(itemName == "agility ring") {
        return 'r';
    } else if(itemName == "agility amulet") {
        return 'g';
    } else if(itemName == "strength amulet") {
        return 't';
    } else if(itemName == "sword") {
        return 's';
    } else if(itemName == "bronze sword") {
        return 'b';
    } else if(itemName == "iron sword") {
        return 'i';
    } else if(itemName == "mythic sword") {
        return 'm';
    } else if(itemName == "armor") {
        return 'A';
    } else if(itemName == "bronze armor") {
        return 'B';
    } else if(itemName == "iron armor") {
        return 'I';
    } else if(itemName == "mythic armor") {
        return 'M';
    } else if(itemName == "coin purse") {
        return 'c';
    } else if(itemName == "potion belt") {
        return 'P';
    } else {
        printf("Invalid item name.\n");
        return NULL;
    }
}
     
// These can be created as needed to make a new copy of the item
// Gold generated using the coin purse.

Item * getLowItem(){
    Item * item;
    // Probability roll, need to test if this works
    int r = getRandomNumber();
    switch(r){
        case 0 ... 19:
            item = generateItem("potion", 1);
            break;
        case 20 ... 39:
            item = generateItem("agility ring", 1);
            break;
        case 40 ... 59:
            item = generateItem("sword", 1);
            break;
        case 60 ... 79:
            item = generateItem("bronze armor", 1);
            break;
        default:
            item = generateItem("coin purse", 10);
            break;
    }
    return item;
}

Item * getMidItem(){
    Item * item;
    int r = getRandomNumber();

    switch(r){
        case 0 ... 19:
            item = generateItem("potion belt", 2);
            break;
        case 20 ... 39:
            item = generateItem("agility amulet", 1);
            break;
        case 40 ... 59:
            item = generateItem("iron sword", 1);
            break;
        case 60 ... 79:
            item = generateItem("iron armor", 1);
            break;
        default:
            item = generateItem("coin purse", 15);
            break;
    }
    return item;
}

Item * getHighItem(){
    Item * item;
    int r = getRandomNumber();

    switch (r) {
    case 0 ... 19:
        item = generateItem("potin belt", 5);
        break;
    case 20 ... 39:
        item = generateItem("strength amulet", 1);
        break;
    case 40 ... 59:
        item = generateItem("mythic sword", 1);
        break;
    case 60 ... 79:
        item = generateItem("mythic armor", 1);
        break;
    default:
        item = generateItem("coin purse", 20);
        break;
    }
    return item;
}
