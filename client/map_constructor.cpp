

#include "map_constructor.hpp"
#include <time.h>
#include <cstdlib>

using namespace std;



/*MapBlock::MapBlock(Texture* texture, int x, int y) {
    Sprite* block = new Sprite(*texture);
    block->setPosition(x * block->getTextureRect().width, y * block->getTextureRect().height);
}

void MapBlock::draw(RenderWindow& window) {
    window.draw(*block);
}

MapBlock::~MapBlock() {
    delete block;
}*/

MapConst::MapConst(int w, int h, Textures t_cont): n(w), m(h) {
    srand(time(NULL));
    int num;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //num = rand() % 2 + 1;
            Texture t;
            t.loadFromFile("grass2.png");
            //sf::Sprite* block = new sf::Sprite(*t_cont.get_texture(2));
            //block->setScale(0.75, 0.75);
            Sprite* block = new Sprite();
            block->setTexture(t);
            block->setPosition(i * block->getTextureRect().width, j * block->getTextureRect().height);
            /*MapBlock m_block(t_cont.get_texture(2), i, j);
            game_map.push_back(m_block);*/
            game_map.push_back(block);

        }
    }
}


void MapConst::draw(RenderWindow& window) {
    for (auto iter = game_map.begin(); iter != game_map.end(); iter++) {
        window.draw(**iter);
        //*iter->draw(window);
    }
}

MapConst::~MapConst() {
    for (auto iter = game_map.begin(); iter != game_map.end(); iter++) {
        delete *iter;
    }
}
