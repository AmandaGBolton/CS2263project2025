#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "inventory.h"
#include "player.h"

// No size to make it easier. Is a linked list that easily expands.

// create inventory node
Inventory * createInventoryNode(Item * item, Inventory * prev, Inventory * next) {
    Inventory *inventory = (Inventory *)malloc(sizeof(Inventory));
    if (!inventory) {
        printf("Memory allocation for inventory failed!\n");
        exit(1);
    }
    inventory->item = item;
    inventory->prev = prev;
    inventory->next = next;
    return inventory;
}

void freeInventory(Inventory *inventory) {
    // While items are in inventory free each item
    Inventory * temp = inventory;
    while (temp != NULL) {
        Inventory * next = temp->next;
        freeItem(temp->item);
        free(temp);
        temp = next;
    }
}
 
// initializes inventory, gold and potion are always first for fast searching
void starterInventory(Player *player) {
    Item * sword = generateItem("sword", 1);
    Item * armor = generateItem("armor", 1);
    Item * potion = generateItem("potion", 1);
    Item * gold = generateItem("gold", 5);
    Inventory * node1 = createInventoryNode(gold, NULL, NULL);
    Inventory * node2 = createInventoryNode(potion, node1, NULL);
    node1->next = node2;
    Inventory * node3 = createInventoryNode(armor, node2, NULL);
    node2->next = node3;
    Inventory * node4 = createInventoryNode(sword, node3, NULL);
    node3->next = node4;
    player->inventory = node1;
}

// Adds to the end of the inventory
void addToInventory(Inventory *inventory, Item *item) {

     if(strcmp(item->name,"gold") == 0 || strcmp(item->name, "coin purse") == 0 || strcmp(item->name, "healing potion") == 0 || strcmp(item->name, "potion belt") == 0) {
        Inventory * temp = inventory;
        while (temp != NULL) {
            if (strcmp(temp->item->name, item->name) == 0) {
                temp->item->mod += item->mod;
                printf("%d was added to %s\n", item->mod, temp->item->name);
                return;
            }
            temp = temp->next;
        }
    }

    // If it isn't gold or potions, add a new node
    Inventory * newNode = createInventoryNode(item, NULL, NULL);
    if (inventory == NULL) {
        inventory = newNode; // If the inventory is empty, set the new node as the head
    } else {
        Inventory *temp = inventory;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    
    printf("Added %s to inventory.\n", item->name);
}

// adds to inventory and prints item that was picked up
void pickUpItem(Player *player, Item * item) {
    if (player->inventory == NULL) {
        player->inventory = createInventoryNode(item, NULL, NULL);
    } else {
        addToInventory(player->inventory, item);
    }    
}

// remove item from inventory
void dropItem(Inventory *inventory, char *itemName, int num) {
    // When gold or potion, only subtract from total in item to a max low of 0
    if(strcmp(itemName,"gold") == 0 || strcmp(itemName, "coin purse") == 0 || strcmp(itemName, "healing potion") == 0 || strcmp(itemName, "potion belt") == 0) {
        Inventory * temp = inventory;
        while (temp != NULL) {
            if (strcmp(temp->item->name, itemName) == 0) {
                temp->item->mod -= num;
                if (temp->item->mod < 0) {
                    temp->item->mod = 0;
                }
                printf("%s now has %d remaining\n", temp->item->name, temp->item->mod);
                return;
            }
            temp = temp->next;
        }
    } else if (strcmp(itemName, "Magical Goblet (Quest Item)") == 0) {
        // Not allowed to remove this from inventory
        printf("You cannot remove this item from your inventory!\n");
        return;
    }

    // Any other items, remove from inventory
    Inventory * temp = inventory;
    while (temp != NULL) {
        if (strcmp(temp->item->name, itemName) == 0) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            freeItem(temp->item);
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

// function to display inventory printing its contents in order
void displayInventory(Inventory *inventory) {
    printf("Current Inventory: ");
    Inventory *temp = inventory;
    while (temp != NULL) {
        if (strcmp(temp->item->name, "gold") == 0) {
            printf("%d gold ", temp->item->mod);
        } else if (strcmp(temp->item->name, "coin purse") == 0) {
            printf("%d gold in your coin purse ", temp->item->mod);
        } else if (strcmp(temp->item->name, "healing potion") == 0) {
            printf("%d potions ", temp->item->mod);
        } else if (strcmp(temp->item->name, "potion belt") == 0) {
            printf("%d potions ", temp->item->mod);
        } else {
            printf("%s ", temp->item->name);
        }
        temp = temp->next; // Move to the next node
    }
    printf("\n");
}

int isInInventory(Inventory * list, Item * item) {
    Inventory * temp = list;
    while (temp != NULL) {
        if (strcmp(temp->item->name, item->name) == 0) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

Item * findItem(Inventory * inventory, char * itemName) {
    Inventory * temp = inventory;
    while (temp != NULL) {
        if (temp->item != NULL && strcmp(temp->item->name, itemName) == 0) {
            return temp->item;
        }
        temp = temp->next;
    }
    printf("Failed to find %s in inventory", itemName);
    return NULL;
}

int getCurrentGold(Player * player) {
    Item * gold = findItem(player->inventory, "coin purse");
    return gold->mod;
}

int getCurrentPotions(Player * player) {
    Item * potion = findItem(player->inventory, "potion belt");
    return potion->mod;
}