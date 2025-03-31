#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "scenario.h"

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
    
    item->stat = malloc(strlen(stat) + 1); // +1 for null terminator
    if (!item->stat) {
        printf("Memory allocation for item stat failed!\n");
        free(item); // Free the item structure to avoid memory leaks
        exit(1);
    }
    strcpy(item->stat, stat);
    
    item->name = malloc(strlen(name) + 1); // +1 for null terminator
    if (!item->name) {
        printf("Memory allocation for item name failed!\n");
        free(item->stat); // Free the stat string
        free(item);       // Free the item structure
        exit(1);
    }
    strcpy(item->name, name);

    item->mod = mod;
    return item;
}

// Statement to create an item based on type and number, calls main item constructor
// Pass in the name of what you want and how many
// Method uses a helper to translate string into char used by switch
Item * generateItem(char * itemType, int num){
    char desiredItem = getItemType(itemType);
    Item * item = NULL;

    switch(desiredItem) {
        case 'p':
            item = createItem("POTION", num, "potion belt");
            break;
        case 'r':
            item = createItem("AGL", 1, "agility ring");
            break;
        case 'g':
            item = createItem("AGL", 2, "agility amulet");
            break;
        case 't':
            item = createItem("ATT", 2, "strength amulet");
            break;
        case 's':
            item = createItem("ATT", 1, "sword");
            break;
        case 'b':
            item = createItem("ATT", 2, "bronze sword");
            break;
        case 'i':
            item = createItem("ATT", 3, "iron sword");
            break;
        case 'm':
            item = createItem("ATT", 4, "mythic sword");
            break;
        case 'a':
            item = createItem("DEF", 1, "armor");
            break;
        case 'z':
            item = createItem("DEF", 2, "bronze armor");
            break;
        case 'n':
            item = createItem("DEF", 3, "iron armor");
            break;
        case 'y':
            item = createItem("DEF", 4, "mythic armor");
            break;
        case 'c':
            item = createItem("GOLD", num, "coin purse");
            break;
        default:
            printf("Invalid item type.\n");
            free(item);
            return NULL;
    }
    return item;
}

char getItemType(char * itemName) {
     if (strcmp(itemName, "potion") == 0 || 
    strcmp(itemName, "healing potion") == 0 || 
    strcmp(itemName, "potion belt") == 0) {
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
    } else if(strcmp(itemName, "gold") == 0) {
        return 'c';
    } else {
        printf("Invalid item name %s.\n", itemName);
        return '\0';
    }
}
     
// These can be created as needed to make a new copy of the item
// Gold generated using the coin purse.

Item * getLowItem(){
    Item * item;
    // Probability roll, need to test if this works
    int r = getRandomNumber();
    if (r >= 0 && r <= 19) {
        item = generateItem("potion belt", 1);
    } else if (r >= 20 && r <= 39) {
        item = generateItem("agility ring", 1);
    } else if (r >= 40 && r <= 59) {
        item = generateItem("sword", 1);
    } else if (r >= 60 && r <= 79) {
        item = generateItem("bronze armor", 1);
    } else {
        item = generateItem("coin purse", 10);
    }
    return item;
}

Item * getMidItem(){
    Item * item;
    int r = getRandomNumber();

    if (r >= 0 && r <= 19) {
        item = generateItem("potion belt", 2);
    } else if (r >= 20 && r <= 39) {
        item = generateItem("agility amulet", 1);
    } else if (r >= 40 && r <= 59) {
        item = generateItem("iron sword", 1);
    } else if (r >= 60 && r <= 79) {
        item = generateItem("iron armor", 1);
    } else {
        item = generateItem("coin purse", 15);
    }
    return item;
}

Item * getHighItem(){
    Item * item;
    int r = getRandomNumber();

   if (r >= 0 && r <= 19) {
        item = generateItem("potion belt", 5);
    } else if (r >= 20 && r <= 39) {
        item = generateItem("strength amulet", 1);
    } else if (r >= 40 && r <= 59) {
        item = generateItem("mythic sword", 1);
    } else if (r >= 60 && r <= 79) {
        item = generateItem("mythic armor", 1);
    } else {
        item = generateItem("coin purse", 20);
    }
    return item;
}
