#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "encounter.h"

// Create an NPC encounter 

Encounter * createEncounter(char* prompt, Inventory * shop, char * thanksMsg){
    Encounter * encounter = (Encounter *)malloc(sizeof(Encounter));
    if (!encounter) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    encounter->prompt = prompt;
    encounter->thanksMsg = thanksMsg;
    encounter->inventory = shop;
    return encounter;    
}

void freeEncounter(Encounter * encounter){
    free(encounter);
}

// Need to make them still, will be similar to traps and monsters. Each is a person who offers something (or nothing)
Encounter * pickRandomEncounter() {
    int r = getRandomNumber();
    if (r < 33){
        return createEncounter("You have encountered a shopkeeper. Would you like to buy something?", createInventoryNode(generateItem("potion", 1), NULL, NULL), "Thank you for stopping by!");
    } else if (r < 66){
        return createEncounter("You have encountered a shopkeeper. Would you like to buy something?", createInventoryNode(generateItem("potion", 1), NULL, NULL), "Thank you for stopping by!");
    } else {
        return createEncounter("You have encountered a shopkeeper. Would you like to buy something?", createInventoryNode(generateItem("potion", 1), NULL, NULL), "Thank you for stopping by!");
    }
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
    char name[20];
    scanf(" %c", &input);
    if (input == "Y"){
        // purchase item
        printf("\nWhat would you like to purchase? Type its name exactly. ");
        scanf(" %s", &name);
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
        pickUpItem(player->inventory, current->item);
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
}

Encounter * createQuestEncounter(){
    Item * questItem = createItem("QUEST", 1, "Magical Goblet (Quest Item)");
    Inventory * questInventory = createInventoryNode(questItem, NULL, NULL);
    return createEncounter("You have found it! The magical goblet sits on a shelf. You go and pick it up.", questInventory, "The goblet feels warm in your hands. You hear a roar behind you. Time to esacpe!");
}