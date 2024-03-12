#include "player.h"

void playerMove(Player *player, char dir) {
    switch (dir) {
    case 'w':
        player->coords.y -= player->speed;
        break;

    case 's':
        player->coords.y += player->speed;
        break;

    case 'a':
        player->coords.x -= player->speed;
        break;

    case 'd':
        player->coords.x += player->speed;
        break;

    default:
        break;
    }
}