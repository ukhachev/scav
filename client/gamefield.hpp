#ifndef SCAV_GAMEFIELD_HPP_
#define SCAV_GAMEFIELD_HPP_

#include "game_object.hpp"
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class GameField {
 private:
    Player* player;
    RenderWindow* window;
 	std::map<int, DrawableObject*> map;
 public:
    GameField();
    DrawableObject* find(int obj_id);
    void set_player(int player_id);
    bool get_action(sf::Packet& packet);
 	void render();
 	int add(DrawableObject* obj, int new_id);
 	//void execute(Action* act);
};

#endif  // SCAV_GAME_OBJECT_HPP_
