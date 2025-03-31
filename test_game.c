#include <assert.h>
#include "dungeon.h"

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

    printf("All tests passed!\n");

    freeDungeon(dungeon);
    freeDungeon(loaded);
    return 0;
}