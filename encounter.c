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

void purchaseDialog(Player * player, Inventory * shop){
    printf("What would you like to buy anything? Each item costs 5 gold. Y or N: ");
    // get input
    char input;
    char name[50];
    scanf(" %c", &input);
    if (input == 'Y' || input == 'y'){
        // purchase item
        printf("\nWhat would you like to purchase? Type its name exactly. ");
        scanf(" %49s", name);
        purchaseItem(player, shop, name);
    } else {
        printf("\nOkay, thank you for stopping by!\n");
    }
}

// Checks for sufficient gold, does inventory management
void purchaseItem(Player * player, Inventory * shop, char * itemName){
    // Get the item from the inventory
    Inventory * current = shop;
    while (current != NULL){
        if (strcmp(current->item->name, itemName) == 0){
            break;
        }
        current = current->next;
    }
    if (current == NULL){
        printf("Item not found in shop inventory.\n");
        return;
    }
    // Check if player has enough gold
    Item * goldItem = findItem(player->inventory, "gold");

    if (goldItem->mod < 5){
        printf("You do not have enough gold to purchase this item.\n");
        return;
    } else {
        dropItem(player->inventory, "gold", 5);
        // Add item to player inventory
        pickUpItem(player, current->item);
        // Remove item from shop inventory
        if (current->prev != NULL){
            current->prev->next = current->next;
        } else {
            shop = current->next;
        }
        if (current->next != NULL){
            current->next->prev = current->prev;
        }
        free(current);
    }
    purchaseDialog(player, shop);
    if(shop->item == NULL){
        // If shop has no items left, free the inventory
        freeInventory(shop);
    }
}

Encounter * createQuestEncounter(){
    Item * questItem = createItem("QUEST", 1, "Magical Goblet (Quest Item)");
    Inventory * questInventory = createInventoryNode(questItem, NULL, NULL);
    return createEncounter("You have found it! The magical goblet sits on a shelf. You go and pick it up.", questInventory, "The goblet feels warm in your hands. You hear a roar behind you. Time to esacpe!");
}

Encounter * createExitEncounter() {
    return createEncounter("You have found the exit. You can return to the village! Would you like to leave?", NULL, "Thank you for playing!");
}

Encounter * createDwarfNPC() {
    //Lost dwarf. Sells +2 sword or +2 armour for 5gold each
    Item * sword = generateItem("bronze sword", 1);
    Item * armor = generateItem("bronze armor", 1);
    Inventory * dwarfInventory = createInventoryNode(sword, NULL, NULL);
    addToInventory(dwarfInventory, armor);
    return createEncounter("You have found a lost dwarf. He offers you a +2 sword or +2 armor for 5 gold each.", dwarfInventory, "The dwarf nods and grunts his thanks.");
}

Encounter * createGoodsMerchant() {
    // Goods merchant. Sells HP potions (5 gold each) and agility amulet +1 (5 gold) 
    Item * potion = generateItem("potion belt", 5);
    Item * amulet = generateItem("strength amulet", 1);
    Inventory * goodsInventory = createInventoryNode(potion, NULL, NULL);
    addToInventory(goodsInventory, amulet);
    return createEncounter("You have found a goods merchant. He offers you potions for 5 gold each and a strength amulet for 5 gold.", goodsInventory, "Thank you for your business!");
}

Encounter * createCrazyMan() {
    // Crazy old man. Random gibberish but warns of certain strong monsters. Armor and Trolls. But they also give better loot.
    return createEncounter("You encounter an old man. He's talking to himself. Over and over, he says 'Trolls! No! Armor! Hide!'", NULL, "As you leave, he mutters 'but they have the good stuff if you beat them...'");
}

Encounter * createWitch() {
    // Witch. Give her any gold, gives you +1 ring of agility. 
    Item * ring = generateItem("agility ring", 1);
    Inventory * witchInventory = createInventoryNode(ring, NULL, NULL);
    return createEncounter("You have found a witch. She offers you a +1 ring of agility for 5 gold.", witchInventory, "She grins widely and wiggles her fingers at you.");
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