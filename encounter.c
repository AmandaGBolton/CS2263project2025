#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "encounter.h"
#include "scenario.h"

// Create an NPC encounter 

Encounter * createEncounter(char* prompt, Inventory * shop, char * thanksMsg){
    Encounter * encounter = (Encounter *)malloc(sizeof(Encounter));
    if (!encounter) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    encounter->prompt = strdup(prompt);
    if (!encounter->prompt) {
        printf("Memory allocation for prompt failed!\n");
        free(encounter);
        exit(1);
    }
        encounter->thanksMsg = strdup(thanksMsg);
    if (!encounter->thanksMsg) {
        printf("Memory allocation for thankMsg failed!\n");
        free(encounter->prompt);
        free(encounter);
        exit(1);
    }
    encounter->inventory = shop;
    return encounter;    
}

void freeEncounter(Encounter * encounter){
    free(encounter->prompt);
    free(encounter->thanksMsg);
    free(encounter);
}

void describeShop(Inventory * inventory){
    Inventory * current = inventory;
    printf("Welcome to the shop! Here is what we have for sale:\n");
    while (current != NULL){
        printf("Item: %s\n", current->item->name);
        current = current->next;
    }
}

void purchaseDialog(Player *player, Inventory *shop) {
    char input;
    char name[50];

    while (shop != NULL) {
        printf("Would you like to buy anything? Each item costs 5 gold. You currently have %d gold. Y or N: ", getCurrentGold(player));
        scanf(" %c", &input);

        // Clear the input buffer to discard extra characters
        while (getchar() != '\n');

        if (input == 'Y' || input == 'y') {
            while (1) {
                // Prompt for the item name
                printf("\nWhat would you like to purchase? Type its name exactly (or type 'exit' to cancel): ");
                scanf(" %[^\n]", name);

                // Check if the user wants to exit
                if (strcmp(name, "exit") == 0) {
                    printf("\nOkay, thank you for stopping by!\n");
                    return;
                }

                // Attempt to purchase the item
                purchaseItem(player, shop, name);

                // Break out of the inner loop to re-prompt for Y/N
                break;
            }
        } else if (input == 'N' || input == 'n') {
            printf("\nOkay, thank you for stopping by!\n");
            return;
        } else {
            printf("I didn't understand that. Please enter Yes (Y) or No (N).\n");
        }
    }
}

// Checks for sufficient gold, does inventory management
void purchaseItem(Player *player, Inventory *shop, char *itemName) {
    // Get the item from the inventory
    Inventory *current = shop;
    Inventory *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->item->name, itemName) == 0) {
            break;
        }
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Item %s not found in shop inventory.\n", itemName);
        return;
    }

    // Check if player has enough gold
    int currentGold = getCurrentGold(player);
    if (currentGold < 5) {
        printf("You do not have enough gold to purchase %s.\n", itemName);
        return;
    }

    // Deduct gold from the player's inventory
    dropItem(player->inventory, "coin purse", 5);

    // Create a copy of the item and add it to the player's inventory
    Item *itemCopy = createItem(current->item->stat, current->item->mod, current->item->name);
    pickUpItem(player, itemCopy);

    // Remove the item from the shop inventory
    if (prev == NULL) {
        shop = current->next;
    } else {
        prev->next = current->next;
    }
 
    free(current->item); // Free the original item in the shop
    free(current);       // Free the shop inventory node

    printf("You purchased %s.\n", itemName);
}

Encounter * createQuestEncounter(){
    Item * questItem = createItem("QUEST", 1, "Magical Goblet (Quest Item)");
    Inventory * questInventory = createInventoryNode(questItem, NULL, NULL);
    return createEncounter("You have found it! The magical goblet sits on a shelf. You go and pick it up.\n", questInventory, "The goblet feels warm in your hands. You hear a roar behind you. Time to esacpe!\n");
}

Encounter * createExitEncounter() {
    return createEncounter("You have found the exit. You can return to the village! Would you like to leave?\n", NULL, "Thank you for playing!\n");
}

Encounter * createDwarfNPC() {
    //Lost dwarf. Sells +2 sword or +2 armour for 5gold each
    Item * sword = generateItem("bronze sword", 1);
    Item * armor = generateItem("bronze armor", 1);
    Inventory * dwarfInventory = createInventoryNode(sword, NULL, NULL);
    addToInventory(dwarfInventory, armor);
    return createEncounter("You have found a lost dwarf. He offers you a +2 sword or +2 armor for 5 gold each.\n", dwarfInventory, "The dwarf nods and grunts his thanks.\n");
}

Encounter * createGoodsMerchant() {
    // Goods merchant. Sells HP potions (5 gold each) and agility amulet +1 (5 gold) 
    Item * potion = generateItem("potion belt", 5);
    Item * amulet = generateItem("strength amulet", 1);
    Inventory * goodsInventory = createInventoryNode(potion, NULL, NULL);
    addToInventory(goodsInventory, amulet);
    return createEncounter("You have found a goods merchant. He offers you potions for 5 gold each and a strength amulet for 5 gold.\n", goodsInventory, "Thank you for your business!\n");
}

Encounter * createCrazyMan() {
    // Crazy old man. Random gibberish but warns of certain strong monsters. Armor and Trolls. But they also give better loot.
    return createEncounter("You encounter an old man. He's talking to himself. Over and over, he says 'Trolls! No! Armor! Hide!'\n", NULL, "As you leave, he mutters 'but they have the good stuff if you beat them...'\n");
}

Encounter * createWitch() {
    // Witch. Give her any gold, gives you +1 ring of agility. 
    Item * ring = generateItem("agility ring", 1);
    Inventory * witchInventory = createInventoryNode(ring, NULL, NULL);
    return createEncounter("You have found a witch. She offers you a +1 ring of agility for 5 gold.\n", witchInventory, "She grins widely and wiggles her fingers at you.\n");
}

// Need to make them still, will be similar to traps and monsters. Each is a person who offers something (or nothing)
Encounter * pickRandomEncounter() {
    int r = getRandomNumber();
    if (r < 33){
        return createDwarfNPC();
    } else if (r < 50){
        return createCrazyMan();
    } else if (r < 70){
        return createWitch();
    } else {
        return createGoodsMerchant();
    }
}