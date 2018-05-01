#ifndef SCAV_MAP_CONSTRUCTOR_HPP_
#define SCAV_MAP_CONSTRUCTOR_HPP_

#include "textures.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <list>



/*class MapBlock {
private:
    Sprite* block;
public:
    MapBlock(Texture* texture, int x, int y);
    void draw(RenderWindow& window);
    ~MapBlock();
};*/


class MapConst {
 private:
    int m;
    int n;
    //std::list<MapBlock*> game_map;
    std::list<Sprite*> game_map;
 public:
     MapConst(int w, int h, Textures t_cont);
     void draw(sf::RenderWindow& window);
     ~MapConst();
};




#endif  // SCAV_MAP_CONSTRUCTOR_HPP_
