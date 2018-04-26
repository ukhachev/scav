#ifndef SCAV_GAMEFIELD_HPP_
#define SCAV_GAMEFIELD_HPP_

#include "game_object.hpp"
#include <mutex>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "physics_object.hpp"

using namespace sf;

class GameField {
 private:
    Player* player;
    RenderWindow window;
 	std::map<int, DrawableObject*> map;
 	std::mutex mtx;
 	b2World* world;
 public:
    GameField();
    DrawableObject* find(int obj_id);
    b2World* get_physics_world();
    void set_player(int player_id);
    bool get_action(sf::Packet& packet);
    void render();
    Player* get_player();
 	int add(DrawableObject* obj, int new_id);
};

#endif  // SCAV_GAME_OBJECT_HPP_
