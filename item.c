#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

// Saving player should record current stats (incld HP) and inventory

int getRandomNumber();

// Function to free a player from memory (e.g., on death)
void freeItem(Item *item) {
    free(item);
}

// Function to create an Item
Item *createItem(char * stat, int mod, char* name) {
    if (stat == "GOLD"){
        // Add it to current gold item, adding num/mod to current value
    }

    if (name == "potion belt"){
        // Add num/mod to current potions
    }

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

Item * generateItem(char itemType, int num){
    // Use switch to create appropriate item instead of all the separate methods below
    switch(itemType) {
        case 'p':
            return createPotion();
        case 'r':
            return createAgilityRing();
        case 'g':
            return createAgilityAmulet();
        case 't':
            return createStrengthAmulet();
        case 's':
            return createSword();
        case 'b':
            return createBronzeSword();
        case 'i':
            return createIronSword();
        case 'm':
            return createMythicSword();
        case 'A':
            return createArmor();
        case 'B':
            return createBronzeArmor();
        case 'I"':
            return createIronArmor();
        case 'M':
            return createMythicArmor();
        case 'c':
            return createCoinPurse(num);
        case 'P':
            return createPotionBelt(num);
        default:
            printf("Invalid item type.\n");
            return NULL;
    }
}

// These can be created as needed to make a new copy of the item
// Gold is not part of this. It is a variable with its own value.

// Create Potion
Item *createPotion() {
    Item * item = createItem('HP', 5, "healing potion");
    return item;
}

// Create Agility Ring
Item *createAgilityRing() {
    Item * item = createItem('AGL', 1, "agility ring");
    return item;
}

// Create Agility Amulet
Item *createAgilityAmulet() {
    Item * item = createItem('AGL', 2, "agility amulet");
    return item;
}

// Create Strength Amulet
Item *createStrengthAmulet() {
    Item * item = createItem('ATT', 2, "strength amulet");
    return item;
}

// Create starter Sword
Item *createSword() {
    Item * item = createItem('ATT', 1, "sword");
    return item;
}

// Create Bronze Sword
Item *createBronzeSword() {
    Item * item = createItem('ATT', 2, "bronze sword");
    return item;
}

// Create Iron Sword
Item *createIronSword() {
    Item * item = createItem('ATT', 3, "iron sword");
    return item;
}

// Create Mythic Sword
Item *createMythicSword() {
    Item * item = createItem('ATT', 4, "mythic sword");
    return item;
}

// Create starter Armor
Item *createArmor() {
    Item * item = createItem('DEF', 1, "armor");
    return item;
}

// Create Bronze Armor
Item *createBronzeArmor() {
    Item * item = createItem('DEF', 2, "bronze armor");
    return item;
}

// Create Iron Armor
Item *createIronArmor() {
    Item * item = createItem('DEF', 3, "iron armor");
    return item;
}

// Create Mythic Armor
Item *createMythicArmor() {
    Item * item = createItem('DEF', 4, "mythic armor");
    return item;
}

// Create gold, turn this into inventory gold
Item *createCoinPurse(int gold) {
    Item * item = createItem('GOLD', gold, "coin purse");
    return item;
}

// Create multiple potions, turn this into inventory potions
Item *createPotionBelt(int numPotions) {
    Item * item = createItem('HP', numPotions, "potion belt");
    return item;
}

Item * getLowItem(){
    Item * item;
    // Probability roll, need to test if this works
    int r = getRandomNumber();
    switch(r){
        case 0 ... 19:
            item = createPotion();
            break;
        case 20 ... 39:
            item = createAgilityRing();
            break;
        case 40 ... 59:
            item = createBronzeSword();
            break;
        case 60 ... 79:
            item = createBronzeArmor();
            break;
        default:
            item = createCoinPurse(5);
            break;
    }
    return item;
}

Item * getMidItem(){
    Item * item;
    int r = getRandomNumber();

    switch(r){
        case 0 ... 19:
            item = createPotionBelt(2);
            break;
        case 20 ... 39:
            item = createAgilityAmulet();
            break;
        case 40 ... 59:
            item = createIronSword();
            break;
        case 60 ... 79:
            item = createIronArmor();
            break;
        default:
            item = createCoinPurse(10);
            break;
    }
    return item;
}

Item * getHighItem(){
    Item * item;
    int r = getRandomNumber();

    switch (r) {
    case 0 ... 19:
        item = createPotionBelt(5);
        break;
    case 20 ... 39:
        item = createStrengthAmulet();
        break;
    case 40 ... 59:
        item = createMythicSword();
        break;
    case 60 ... 79:
        item = createMythicArmor();
        break;
    default:
        item = createCoinPurse(20);
        break;
    }
    return item;
}
