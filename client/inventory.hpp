#ifndef SCAV_INVENTORY_HPP_
#define SCAV_INVENTORY_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Inventory {
 private:
     Sprite* weapon1;
     Sprite* weapon2;
 public:
     Inventory(Textures t_cont);
     Sprite* get_active_weapon(int num);
     ~Inventory();


}
