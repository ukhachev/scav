#ifndef SCAV_MAP_CONSTRUCTOR_HPP_
#define SCAV_MAP_CONSTRUCTOR_HPP_

#include "textures.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <list>
#include <map>
class MapConst {
 private:
    int m;
    int n;
    std::list<Sprite*> game_map;
    std::map<int, Sprite*> tiles;
 public:
     MapConst(int w, int h, Texture* m_texture);
     void draw(sf::RenderWindow& window, float px, float py);
     void add_tile(int id, float x, float y, int sx, int sy, Texture* txt);
     ~MapConst();
};




#endif  // SCAV_MAP_CONSTRUCTOR_HPP_
