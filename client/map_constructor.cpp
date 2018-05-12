
#include "map_constructor.hpp"
#include <time.h>
#include <cstdlib>

using namespace std;

MapConst::MapConst(int w, int h, Texture* m_texture): n(w), m(h) {
    srand(time(NULL));
    int num;
    for (int i = -n; i < n; i++) {
        for (int j = -m; j < m; j++) {
            Sprite* block = new Sprite(*m_texture);
            block->setPosition(i * block->getTextureRect().width, j * block->getTextureRect().height);
            game_map.push_back(block);

        }
    }
}


void MapConst::draw(RenderWindow& window, float px, float py) {
    for (auto iter = game_map.begin(); iter != game_map.end(); iter++) {
        sf::Vector2f pos = (*iter)->getPosition();
        if (px + 1500 > pos.x && px - 1500 < pos.x && py + 800 > pos.y && py -750 < pos.y)
            window.draw(**iter);
        //*iter->draw(window);
    }
}

MapConst::~MapConst() {
    for (auto iter = game_map.begin(); iter != game_map.end(); iter++) {
        delete *iter;
    }
}
