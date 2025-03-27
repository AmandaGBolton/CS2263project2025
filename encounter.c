#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "encounter.h"

// Create an NPC encounter 

Encounter * createEncounter(char* prompt, char * thanksMsg){
    Encounter * encounter = (Encounter *)malloc(sizeof(Encounter));
    if (!encounter) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    encounter->prompt = prompt;
    encounter->thanksMsg = thanksMsg;
    return encounter;    
}

void freeEncounter(Encounter * encounter){
    free(encounter->prompt);
    free(encounter->thanksMsg);
    free(encounter);
}

void describeShop(Inventory ** inventory){
    Inventory * current = *inventory;
    printf("Welcome to the shop! Here is what we have for sale:\n");
    while (current != NULL){
        printf("Item: %s\n", current->item->name);
        current = current->next;
    }
}

void purchaseDialog(){
    printf("What would you like to buy anything? Each item costs 5 gold. Y or N: ");
    // get input
    char input;
    scanf(" %c", &input);
    if (input == "Y"){
        // purchase item
    } else {
        printf("Okay, thank you for stopping by!\n");
    }
}

// Checks for sufficient gold, does inventory management
void purchaseItem(Player * player, Inventory ** inventory, char * itemName){
    // Get the item from the inventory
    Inventory * current = *inventory;
    while (current != NULL){
        if (strcmp(current->item->name, itemName) == 0){
            break;
        }
        current = current->next;
    }
    if (current == NULL){
        printf("Item not found in inventory.\n");
        return;
    }
    // Check if player has enough gold
    if (player->gold < 5){
        printf("You do not have enough gold to purchase this item.\n");
        return;
    } else {
        player->gold -= 5;
        // Add item to player inventory
        pickUpItem(player->inventory, current->item);
        // Remove item from shop inventory
        if (current->prev != NULL){
            current->prev->next = current->next;
        } else {
            *inventory = current->next;
        }
        if (current->next != NULL){
            current->next->prev = current->prev;
        }
        free(current);
    }
    purchaseDialog();
}

// Needs to be fixed to work with inventory
// Probably also has a method somewhere else
// But this is needed to run to add items to NPC's inventory "shops"
void addItemToInventory(Item * item, Inventory ** inventory){
  
    // inventory->item = item;
    // inventory->next = NULL;
    // inventory->prev = NULL;
    // if (*inventory == NULL){
    //     *inventory = inventory;
    // } else {
    //     Inventory * current = *inventory;
    //     while (current->next != NULL){
    //         current = current->next;
    //     }
    //     current->next = inventory;
    //     inventory->prev = current;
    // }

}
