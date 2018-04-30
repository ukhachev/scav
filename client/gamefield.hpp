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
#include <map>

using namespace sf;

class GameField {
 private:
    Player* player;
    RenderWindow window;
 	std::map<int, Player*> players; //я забыл, для чего именно нам это нужно, только для игроков, или для чего-то еще
 	std::map<int, Wall*> walls;

 	//std::map<int, Bullet*> map_bullets; Пока класса для пуль нет, но пусть будет здесь, пригодится
 	std::mutex mtx;
 	b2World* world;
 public:
    GameField();
    b2World* get_physics_world();
    void set_player(int player_id);
    bool get_action(sf::Packet& packet);
    void shoot();
    void render();

    Player* get_player();
    Player* find_player(int obj_id);

 	int add_player(Player* obj, int new_id);
 	int add_wall(Wall* obj, int new_id);

 	//int add_bullet(Bullet* obj, int new_id);  Пригодится
};

#endif  // SCAV_GAME_OBJECT_HPP_
