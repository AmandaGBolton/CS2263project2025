#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "item.h"
#include "inventory.h"

// Free?

// Function to free a player from memory (e.g., on death)
void freePlayer(Player *player) {
    // Need to free inventory in whatever way is appropriate^
    freeInventory(player->inventory);
    free(player->name);
    free(player);
}

// Function to create a Player
Player *createPlayer(int hp, int att, int def, int agl, char* name) {
    Player *player = (Player *)malloc(sizeof(Player));
    if (!player) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

     player->name = malloc(strlen(name) + 1); 
    if (!player->name) {
        printf("Memory allocation for player name failed!\n");
        free(player); // Free the player structure to avoid memory leaks
        exit(1);
    }
    strcpy(player->name, name);

    player->hp = hp;
    player->att = att;
    player->def = def;
    player->agl = agl;

    equipStartingPlayer(player);
    return player;
}

char * getPlayerName() {
    char name[21];
    printf("*********** TREASURE QUEST ***********\n");
    printf("What is your name? (Max 20 characters) ");
    scanf(" %s", name);
    while (name[0] == '\0' || strlen(name) > 20) {
        printf("\nThat isn't right. Please enter a valid name. ");
        scanf(" %s", name);
    }    
    char * playerName = malloc(strlen(name)+1);
    if(playerName == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(playerName, name);

    printf("\nWelcome to the game %s!\n", playerName);
    return playerName;
}

// Add starting items. Armor, sword, 1 HP potion, 5 gold.
// Still need to figure out gold and inventory
// Also figure out inventory items in general so they have stats (type Item)
// Ideally import Item, make copy of desired item to add to player inventory
void equipStartingPlayer(Player *player) {
    starterInventory(player);
    adjustStats(player);
}

// Heal for the given number of HP, checking against max HP
void healPlayer(Player *player, int hpRegained){
    int currentHP = player->hp;
    currentHP += 5;
    //Check if over max and reduce if needed
    if (currentHP>20) {
        currentHP = 20;
    }
    player->hp = currentHP;
}

void isPlayerDead(Player *player, int damage){
    int currentHP = player->hp;
    currentHP -= damage;
    if (currentHP <= 0){
        printf("You have died!\n");
        freePlayer(player);
        // Free dungeon^
    } else {
        player->hp = currentHP;
        printf("You were hit for %d damage. You have %d HP left.\n", damage, currentHP);
    }
}

//This needs to look at current inventory and adjust stats
// Check for stat modifying items for ATT, DEF, and AGL
void adjustStats(Player *player) {
    // base values for sword/armor
    int att = 0;
    int def = 0;
    int agl = 0;
    // For all other objects
    int objAtt = 0;
    int objDef = 0;

    Inventory * tempList = NULL;
    
    // Loop should add only one sword and one armor to att and def, whatever is highest value
    // Any other ATT and DEF that are not sword or armor can be added to att and def but only unique names
    // All unique AGL items can be added to agl
    Inventory * temp = player->inventory;
    while (temp != NULL) {
        if (strcmp(temp->item->stat, "ATT") == 0) {
            // Check if substring contains "sword"
            if (strstr(temp->item->name, "sword") != NULL) {
                if (temp->item->mod > att) {
                    att = temp->item->mod;
                }
            } else {
                // Check if item is not already in list
                int present = isInInventory(tempList, temp->item);
                if (present != 0) {
                    // Add item to list
                    addToInventory(tempList, temp->item);
                    objAtt += temp->item->mod;
                }
            }
        } else if (strcmp(temp->item->stat, "DEF") == 0) {
            // Check if substring contains "armor"
            if (strstr(temp->item->name, "armor") != NULL) {
                if (temp->item->mod > def) {
                    def = temp->item->mod;
                }
            }
            else {
                // Check if item is not already in list
                int present = isInInventory(tempList, temp->item);
                if (present != 0) {
                    // Add item to list
                    addToInventory(tempList, temp->item);
                    objDef += temp->item->mod;
                }
            }
        } else if (strcmp(temp->item->stat, "AGL") == 0) {
                int present = isInInventory(tempList, temp->item);
                if (present != 0) {
                // Add item to list
                addToInventory(tempList, temp->item);
                agl += temp->item->mod;
            }                
        }
 
        temp = temp->next;
    }  

    player->att = 1 + att + objAtt;
    player->def = 1 + def + objDef;
    player->agl = agl;
    printf("Your current stats > HP: %d, ATT: +%d, DEF: +%d, AGL: +%d, Gold: %d, Potions: %d\n", player->hp, player->att, player->def, player->agl, getCurrentGold(player), getCurrentPotions(player));
    free(tempList);
    free(temp);
}

// int main() {

//     // Ask player for name and check length
//     char* playerName;
//     printf("What is your name? (Max 20 characters) ");
//     scanf(" %c", &playerName);
//     if(playerName[0]=="\0") {
//         playerName = "Bob";
//         printf("No name? We'll call you Bob then.\n");
//     } else if (strlen(playerName)>20) {
//         printf("\nThat is too long! Please choose something shorter.");
//         scanf(" %c", &playerName);
//     }
//     if (strlen(playerName)>20) {
//         printf("\nThat is too long! We'll just call you Bob then.\n");
//         playerName = "Bob";
//     }
//     printf("Welcome to the game %c!\n", playerName);
    
//     struct Player * currentPlayer;
//     currentPlayer = createPlayer(20, 1, 1, 0, playerName);
    
//     return 0;
// }

