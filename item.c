#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inventory.h>

typedef struct {
    char* stat;
    int mod;
    char name[21];
} Item;

// Saving player should record current stats (incld HP) and inventory


// Function to free a player from memory (e.g., on death)
void freeItem(Item *item) {
    free(item);
}

// Function to create an Item
Player *createItem(char * stat, int mod, char* name) {
    Item *item = (Item *)malloc(sizeof(Item));
    if (!item) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    item->stat = stat;
    item->mod = mod;
    item->name = name;
    return item;
}

// These can be created as needed to make a new copy of the item
// Gold is not part of this. It is a variable with its own value.

// Create Potion
Item *createPotion() {
    Item potion = createItem('HP', 5, "healing potion");
    return potion;
}

// Create Agility Ring
Item *createAgilityRing() {
    Item item = createItem('AGL', 1, "agility ring");
    return item;
}

// Create Agility Amulet
Item *createAgilityAmulet() {
    Item item = createItem('AGL', 2, "agility amulet");
    return item;
}

// Create Strength Amulet
Item *createStrengthAmulet() {
    Item item = createItem('ATT', 2, "strength amulet");
    return item;
}

// Create starter Sword
Item *createSword() {
    Item item = createItem('ATT', 1, "sword");
    return item;
}

// Create Bronze Sword
Item *createBronzeSword() {
    Item item = createItem('ATT', 2, "bronze sword");
    return item;
}

// Create Iron Sword
Item *createIronSword() {
    Item item = createItem('ATT', 3, "iron sword");
    return item;
}

// Create Mythic Sword
Item *createMythicSword() {
    Item item = createItem('ATT', 4, "mythic sword");
    return item;
}

// Create starter Armor
Item *createArmor() {
    Item item = createItem('DEF', 1, "armor");
    return item;
}

// Create Bronze Armor
Item *createBronzeArmor() {
    Item item = createItem('DEF', 2, "bronze armor");
    return item;
}

// Create Iron Armor
Item *createIronArmor() {
    Item item = createItem('DEF', 3, "iron armor");
    return item;
}

// Create Mythic Armor
Item *createMythicArmor() {
    Item item = createItem('DEF', 4, "mythic armor");
    return item;
}

// Create gold, turn this into inventory gold
Item *createCoinPurse(int gold) {
    Item item = createItem('GOLD', gold, "coin purse");
    return item;
}

// Create multiple potions, turn this into inventory potions
Item *createPotionBelt(int numPotions) {
    Item item = createItem('POTIONS', numPotions, "potion belt");
    return item;
}

Item getLowItem(){
    Item item;
    // Probability roll, need to test if this works
    int r = rand() % 100;

    // IF 0-19, createPotion();
    // IF 20-39, createAgilityRing();
    // IF 40-59, createBronzeSword();
    // IF 60-79, createBronzeArmor();
    // IF 80+, createCoinPurse(5);

    return item;
}

Item getMidItem(){
    Item item;
    // Probability roll
    // IF 0-19, createPotionBelt(2);
    // IF 20-39, createAgilityAmulet();
    // IF 40-59, createIronSword();
    // IF 60-79, createIronArmor();
    // IF 80+, createCoinPurse(10);

    return item;
}

Item getHighItem(){
    Item item;
    // Probability roll
    // IF 0-19, createPotionBelt(5);
    // IF 20-39, createStrengthAmulet();
    // IF 40-59, createMythicSword();
    // IF 60-79, createMythicArmor();
    // IF 80+, createCoinPurse(20);

    return item;
}
