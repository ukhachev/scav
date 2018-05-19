
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
        const sf::Vector2f& pos = (*iter)->getPosition();
        if (px + 1500 > pos.x && px - 1500 < pos.x && py + 800 > pos.y && py -750 < pos.y)
            window.draw(**iter);
    }
     for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        //const sf::Vector2f& pos = iter->second->getPosition();
        //if (px + 1500 > pos.x && px - 1500 < pos.x && py + 800 > pos.y && py -750 < pos.y)
            window.draw(*(iter->second));
    }
}

void MapConst::add_tile(int id, float x, float y, int sx, int sy, Texture* txt) {
    if (tiles.find(id) == tiles.end()) {
        txt->setRepeated(true);
        Sprite* tile = new Sprite();
        tile->setTexture(*txt);
        tile->setTextureRect({ 0, 0, sx, sy });
        tile->setPosition(x, y);
        tiles.emplace(id, tile);
    }

}

MapConst::~MapConst() {
    for (auto iter = game_map.begin(); iter != game_map.end(); iter++) {
        delete *iter;
    }
    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        delete iter->second;
    }
}
