#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "encounter.h"

// Saving player should record current stats (incld HP) and inventory^

// Function to free a player from memory (e.g., on death)
void freeItem(Item *item) {
    free(item->name);
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
    item->name = strdup(name); 
    if (!item->name) {
        printf("Memory allocation for item name failed!\n");
        free(item); // Free the item structure to avoid memory leaks
        exit(1);
    }
    return item;
}

// Statement to create an item based on type and number, calls main item constructor
// Pass in the name of what you want and how many
// Method uses a helper to translate string into char used by switch
Item * generateItem(char * itemType, int num){
    char desiredItem = getItemType(itemType);
    Item * item;

    switch(desiredItem) {
        case 'p':
            item = createItem("HP", 1, "healing potion");
        case 'r':
            item = createItem("AGL", 1, "agility ring");
        case 'g':
            item = createItem("AGL", 2, "agility amulet");
        case 't':
            item = createItem("ATT", 2, "strength amulet");
        case 's':
            item = createItem("ATT", 1, "sword");
        case 'b':
            item = createItem("ATT", 2, "bronze sword");
        case 'i':
            item = createItem("ATT", 3, "iron sword");
        case 'm':
            item = createItem("ATT", 4, "mythic sword");
        case 'a':
            item = createItem("DEF", 1, "armor");
        case 'z':
            item = createItem("DEF", 2, "bronze armor");
        case 'n':
            item = createItem("DEF", 3, "iron armor");
        case 'y':
            item = createItem("DEF", 4, "mythic armor");
        case 'c':
            item = createItem("GOLD", num, "coin purse");
        case 'l':
            item = createItem("POTION", num, "potion belt");
        default:
            printf("Invalid item type.\n");
            free(item);
            return NULL;
    }
    return item;
}

char getItemType(char * itemName) {
     if(strcmp(itemName, "potion") == 0){
        return 'p';
    } else if(strcmp(itemName,"agility ring") == 0){
        return 'r';
    } else if(strcmp(itemName, "agility amulet") == 0) {
        return 'g';
    } else if(strcmp(itemName, "strength amulet") == 0) {
        return 't';
    } else if(strcmp(itemName, "sword") == 0) {
        return 's';
    } else if(strcmp(itemName, "bronze sword") == 0) {
        return 'b';
    } else if(strcmp(itemName, "iron sword") == 0) {
        return 'i';
    } else if(strcmp(itemName, "mythic sword") == 0) {
        return 'm';
    } else if(strcmp(itemName, "armor") == 0) {
        return 'a';
    } else if(strcmp(itemName, "bronze armor") == 0) {
        return 'z';
    } else if(strcmp(itemName, "iron armor") == 0) {
        return 'n';
    } else if(strcmp(itemName ,"mythic armor") == 0) {
        return 'y';
    } else if(strcmp(itemName, "coin purse") == 0) {
        return 'c';
    } else if(strcmp(itemName, "potion belt") == 0) {
        return 'l';
    } else {
        printf("Invalid item name.\n");
        return '\0';
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
