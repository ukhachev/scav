#include "gamefield.hpp"
#include "game_object.hpp"
#include "action.hpp"


int main() {

    GameField* game = new GameField();

    Texture map_texture;
    map_texture.loadFromFile("map.png");


    Texture player_texture;
    player_texture.loadFromFile("Solder clone.png");

    GameMap map(12, map_texture);

    game->add(&map, map.get_id());


    game->set_player(666);

    Player *player = game->get_player();
    player->set_player_sprite(player_texture);

    game->render(player);
}
