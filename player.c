#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "item.h"
#include "inventory.h"

// Free?

// Function to free a player from memory (e.g., on death)
void freePlayer(Player *player) {
    // free(player->inventory);
    free(player);
}

// Function to create a Player
Player *createPlayer(int hp, int att, int def, int agl, int gold, char* name) {
    Player *player = (Player *)malloc(sizeof(Player));
    if (!player) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    player->hp = hp;
    player->att = att;
    player->def = def;
    player->agl = agl;
    player->gold = gold;
    player->name = name;
    equipStartingPlayer(player);
    return player;
}

// Add starting items. Armor, sword, 1 HP potion, 5 gold.
// Still need to figure out gold and inventory
// Also figure out inventory items in general so they have stats (type Item)
// Ideally import Item, make copy of desired item to add to player inventory
void *equipStartingPlayer(Player *player) {
    Item * sword = createSword();
    Item * armor = createArmor();
    Item * potion = createPotion();
    // Need to add these to player inventory in some way
    pickUpItem(player.inventory, sword);
    pickUpItem(player.inventory, armor);
    pickUpItem(player.inventory, potion);
    adjustStats(player);
}

// Heal for the given number of HP, checking against max HP
void heal(Player *player, int hpRegained){
    int currentHP = player.hp;
    currentHP += 5;
    //Check if over max and reduce if needed
    if (currentHP>20) {
        currentHP = 20;
    }
    player->hp = currentHP;
}

void isPlayerDead(Player *player, int damage){
    int currentHP = player.hp;
    currentHP -= damage;
    if (currentHP <= 0){
        printf("You have died!\n");
        freePlayer(&player);
    } else {
        player->hp = currentHP;
        printf("You were hit for %d damage.\n", damage);
    }
}

//This needs to look at current inventory and adjust stats
// Check for stat modifying items for ATT, DEF, and AGL
void adjustStats(Player *player) {
    // base values
    int att = 1;
    int def = 1;
    int agl = 0;
    
    // Exact same item does not stack, but different items can
    // ^ loop to create list of unique items in inventory that mod > 0
    
    // Only ONE sword and ONE armor allowed to count (highest)
    // ^ loop to get only highest mod value of sword / armor, remove others
    
    // With final list add mod to appropriate stats, ignore potions
    // ^If ATT, then =+ mod value on att, etc.

    // Set final values
    player->att = att;
    player->def = def;
    player->agl = agl;
}

int main() {

    // Ask player for name and check length
    char* playerName;
    printf("What is your name? (Max 20 characters) ");
    scanf(" %c", &playerName);
    if(playerName[0]=="\0") {
        playerName = "Bob";
        printf("No name? We'll call you Bob then.\n");
    } else if (strlen(playerName)>20) {
        printf("\nThat is too long! Please choose something shorter.");
        scanf(" %c", &playerName);
    }
    if (strlen(playerName)>20) {
        printf("\nThat is too long! We'll just call you Bob then.\n");
        playerName = "Bob";
    }
    printf("Welcome to the game %c!\n", playerName);
    
    struct Player currentPlayer;
    currentPlayer = createPlayer(20, 1, 1, 0, 5, playerName);
    
    return 0;
}

