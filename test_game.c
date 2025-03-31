#include <assert.h>
#include "dungeon.h"
#include "player.h"
#include "item.h"
#include "monster.h"
#include "encounter.h"
#include "inventory.h"

int main() {
    Dungeon *dungeon = createDungeon();
    assert(dungeon != NULL);
    assert(dungeon->rooms[0][0]->visited == 1);

    movePlayer(dungeon, 'E');
    assert(dungeon->player->x == 1);

    saveDungeon(dungeon, "test_save.txt");
    Dungeon *loaded = loadDungeon("test_save.txt");
    assert(loaded != NULL);
    assert(loaded->rooms[0][0]->visited == 1);

    // Test player initialization & Inventory & damage
    Player * player = createPlayer(20, 1, 1, 0, "test");
    assert(player != NULL);
    assert(strcmp(player->name, "test") == 0);
    assert(player->hp == 20);
    assert(player->att == 2);
    assert(player->def == 2);
    assert(player->agl == 0);
    assert(getCurrentGold(player) == 5);
    isPlayerDead(player, 1);
    assert(player->hp == 19);
    
    // Test item generation
    Item * item = generateItem("sword", 1);
    assert(item != NULL);
    assert(strcmp(item->name, "sword") == 0);
    assert(item->mod == 1);
    assert(strcmp(item->stat, "ATT") == 0);

    // Test monster generation
    Monster * monster = generateMonster('s');
    assert(monster != NULL);
    assert(strcmp(monster->name, "Angry Snake") == 0);
    assert(monster->hp == 4);
    assert(monster->att == 1);
    assert(monster->def == 1);
    assert(monster->inventory != NULL);
    
    // Test encounter creation
    Encounter * encounter = createEncounter("test", NULL, "thanks");
    assert(encounter != NULL);
    assert(strcmp(encounter->prompt, "test") == 0);
    assert(strcmp(encounter->thanksMsg, "thanks") == 0);

    // Test purchase item
    Inventory * shop = createInventoryNode(item, NULL, NULL);
    purchaseItem(player, shop, "sword");
    assert(player->inventory != NULL);
    assert(getCurrentGold(player) == 0);

    printf("All tests passed!\n");

    // Free remaining memory
    freeMonster(monster);
    freePlayer(player);
    // freeItem(item); // already free
    // freeInventory(shop); // already free
    freeEncounter(encounter);
    freeDungeon(dungeon);
    freeDungeon(loaded);
    return 0;
}