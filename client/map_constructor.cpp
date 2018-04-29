

#include "map_constructor.hpp"
#include <time.h>
#include <cstdlib>

using namespace std;

MapConst::MapConst(int w, int h, Textures t_cont): n(w), m(h) {
    srand(time(NULL));
    int num;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //num = rand() % 2 + 1;
            Texture t;
            t.loadFromFile("grass2.png");
            sf::Sprite* block = new sf::Sprite(t/*t_cont.get_texture(4)*/);
            block->setScale(0.5, 0.5);
            block->setPosition(i, j);
            game_map.push_back(block);
        }
    }
}


void MapConst::draw(RenderWindow& window) {
    for (auto iter = game_map.begin(); iter != game_map.end(); iter++) {
        window.draw(**iter);
    }
}

MapConst::~MapConst() {

}
