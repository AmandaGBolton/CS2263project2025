#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inventory.h>
#include <item.h>

typedef struct {
    int hp;
    int att;
    int def;
    Inventory rewards[];
    char* name;
} Monster;

// Saving monsters should be tied to rooms

// Function to free a monster from memory
void freeMonster(Monster *monster) {
    // free(monster->rewards);
    free(monster);
}

// Function to create a Monster
Monster *createMonster(int hp, int att, int def, Inventory rewards[], char* name) {
    Monster *monster = (Monster *)malloc(sizeof(Monster));
    if (!monster) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    monster->hp = hp;
    monster->att = att;
    monster->def = def;
    monster->rewards = rewards;
    monster->name = name;
    return monster;
}

Monster *createSnake() {
    Item lowItem = getLowItem();
    Inventory rewards = [lowItem];
    snake = createMonster(4, 1, 1, rewards, "Angry Snake");
    return snake;
}

Monster *createSpider() {
    Item midItem = getMidItem();
    Inventory rewards = [midItem];
    spider = createMonster(6, 2, 1, rewards, "Giant Spider");
    return spider;
}

Monster *createTroll(){
    Item highItem = getHighItem();
    Inventory rewards = [highItem];
    troll = createMonster(7, 3, 2, rewards, "Smelly Troll");
    return troll;
}

Monster *createGnome() {
    Item lowItem = getLowItem();
    Inventory rewards = [lowItem];
    gnome = createMonster(5, 1, 1, rewards, "Evil Gnome");
    return gnome;
}

Monster *createGhost() {
    Item midItem = getMidItem();
    Inventory rewards = [midItem];
    ghost = createMonster(3, 1, 3, rewards, "Ethereal Ghost");
    return ghost;
}

Monster createArmor(){
    Item highItem = getHighItem();
    Inventory rewards = [highItem];
    armor = createMonster(3, 3, 3, rewards, "Possessed Armor");
    return armor;
}

Monster *createSkeleton() {
    Item lowItem = getLowItem();
    Inventory rewards = [lowItem];
    skel = createMonster(3, 2, 1, rewards, "Creaking Skeleton");
    return skel;
}

Monster *createMimic() {
    Item midItem = getMidItem();
    Inventory rewards = [midItem];
    mimic = createMonster(4, 2, 2, rewards, "Mimic Chest");
    return mimic;
}

Monster *createMist() {
    Item lowItem = getLowItem();
    Inventory rewards = [lowItem];
    mist = createMonster(2, 2, 2, rewards, "Black Mist");
    return mist;
}

Monster *createDog() {
    Item midItem = getMidItem();
    Inventory rewards = [midItem];
    dog = createMonster(5, 2, 2, rewards, "Demonic Dog");
    return dog;
}

