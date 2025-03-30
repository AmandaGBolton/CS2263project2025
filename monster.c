#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "item.h"
#include "monster.h"
#include "player.h"

// Saving monsters should be tied to rooms

// Function to free a monster from memory
void freeMonster(Monster *monster) {
    // free(monster->rewards);
    free(monster->inventory);
    free(monster);
}

Monster * pickRandomMonster(){
    int r = getRandomNumber();
    if (r < 10){
        return createSnake();
    } else if (r < 20){
        return createSpider();
    } else if (r < 30){
        return createTroll();
    } else if (r < 40){
        return createGnome();
    } else if (r < 50){
        return createGhost();
    } else if (r < 60){
        return createArmor();
    } else if (r < 70){
        return createSkeleton();
    } else if (r < 80){
        return createMimic();
    } else if (r < 90){
        return createMist();
    } else {
        return createDog();
    }
}

// Function to create a Monster, assumes only one item in inventory
Monster *createMonster(int hp, int att, int def, Item * reward, char* name) {
    Monster *monster = (Monster *)malloc(sizeof(Monster));
    if (!monster) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    monster->hp = hp;
    monster->att = att;
    monster->def = def;
    Inventory * inventory = createInventoryNode(reward, NULL, NULL);
    if (!inventory) {
        printf("Memory allocation failed!\n");
        free(monster);
        exit(1);
    }
    monster->inventory = inventory;
    monster->name = name;
    return monster;
}

Monster * generateMonster(char monsterType){
    // Use switch to create appropriate monster instead of all the separate methods below
    switch(monsterType) {
        case 's':
            return createSnake();
        case 'p':
            return createSpider();
        case 't':
            return createTroll();
        case 'g':
            return createGnome();
        case 'h':
            return createGhost();
        case 'a':
            return createArmor();
        case 'k':
            return createSkeleton();
        case 'm':
            return createMimic();
        case 'y':
            return createMist();
        case 'd':
            return createDog();
        default:
            printf("Invalid monster type.\n");
            return NULL;
    }
}

Monster *createSnake() {
    Item * item = getLowItem();
    Monster * snake = createMonster(4, 1, 1, item, "Angry Snake");
    return snake;
}

Monster *createSpider() {
    Item * midItem = getMidItem();
    Monster * spider = createMonster(6, 2, 1, midItem, "Giant Spider");
    return spider;
}

Monster *createTroll(){
    Item * highItem = getHighItem();
    Monster * troll = createMonster(7, 3, 2, highItem, "Smelly Troll");
    return troll;
}

Monster *createGnome() {
    Item * lowItem = getLowItem();
    Monster * gnome = createMonster(5, 1, 1, lowItem, "Evil Gnome");
    return gnome;
}

Monster *createGhost() {
    Item * midItem = getMidItem();
    Monster * ghost = createMonster(3, 1, 3, midItem, "Ethereal Ghost");
    return ghost;
}

Monster * createArmor(){
    Item * highItem = getHighItem();
    Monster * armor = createMonster(3, 3, 3, highItem, "Possessed Armor");
    return armor;
}

Monster *createSkeleton() {
    Item * lowItem = getLowItem();
    Monster * skel = createMonster(3, 2, 1, lowItem, "Creaking Skeleton");
    return skel;
}

Monster *createMimic() {
    Item * midItem = getMidItem();
    Monster * mimic = createMonster(4, 2, 2, midItem, "Mimic Chest");
    return mimic;
}

Monster *createMist() {
    Item * lowItem = getLowItem();
    Monster * mist = createMonster(2, 2, 2, lowItem, "Black Mist");
    return mist;
}

Monster *createDog() {
    Item * midItem = getMidItem();
    Monster * dog = createMonster(5, 2, 2, midItem, "Demonic Dog");
    return dog;
}

void fightOrFlight(Monster * monster, Player * player) {
    // Player prompt with monster description
    printf("There is a monster in the room!\n");
    printf("It is a %s. What will you do? Fight (F) or run (R)?\n", monster->name);
    char choice[1];
    scanf("%c", choice);
    if(choice=='R') {
        // Do navigation options^
    } else if (choice=='F') {
        fightMonster(player, monster);
    } else {
        printf("Invalid choice. Please enter F or R.\n");
        fightOrFlight(monster, player);
    }
}

// Fight method
void fightMonster(Player * player, Monster * monster) {
    // Roll to attack monster
    int playerRoll = rollDice(20);
    int playerAtt = player->att;
    int playerFinal = playerRoll + playerAtt;
    int monsterDef = monster->def + 10;
    if (playerFinal > monsterDef) {
        int damagerRoll = rollDice(4);
        int damage = player->att + damagerRoll - monster->def;
        if (damage < 0) {
            damage = 0;
        }
        printf("You hit the monster for %d damage!\n", damage);
        monster->hp -= damage;
        if (monster->hp <= 0) {
            printf("You have defeated the monster!\n");
            // Add monster reward to player inventory
            pickUpItem(player->inventory, monster->inventory->item);
            // Adjust player stats
            adjustStats(player);
        } else {
            printf("The monster has %d health left.\n", monster->hp);
            printf("The monster attacks you!\n");
            // Monster attacks player
            int damage = monster->att - player->def;
            if (damage < 0) {
                damage = 0;
            }
            isPlayerDead(player, damage);
            fightOrFlight(monster, player);
        }
    } else {
        printf("You missed the monster!\n");
        printf("The monster attacks you!\n");
        // Monster attacks player
        int damage = monster->att - player->def;
        if (damage < 0) {
            damage = 0;
        }
        isPlayerDead(player, damage);
        fightOrFlight(monster, player);
    }   
}