#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "item.h"
#include "monsters.h"

// Saving monsters should be tied to rooms

// Function to free a monster from memory
void freeMonster(Monster *monster) {
    // free(monster->rewards);
    free(monster->inventory);
    free(monster);
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
    Inventory ** inventory = (Inventory **)malloc(sizeof(Inventory));
    if (!inventory) {
        printf("Memory allocation failed!\n");
        free(monster);
        exit(1);
    }
    monster->inventory[0] = reward;
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

