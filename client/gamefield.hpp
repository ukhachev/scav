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

#include "textures.hpp"
#include "map_constructor.hpp"
#include "camera.hpp"

#include <map>
#include <list>
using namespace sf;

class GameField {
 private:
    Player* player;
    RenderWindow window;
    Textures t_cont;
    Camera g_cam;
    MapConst g_map;

 	std::map<int, Player*> players;
 	std::map<int, Wall*> walls;
    bool was_shot = false;
 	std::list<DrawableBullet*> bullets;
 	std::mutex mtx;
 	b2World* world;
    int last_shot = 0;
 public:
    GameField();
    b2World* get_physics_world();
    void set_player(int player_id);
    bool get_action(sf::Packet& packet);
    void shoot();
    bool render();

    std::mutex& get_mutex();
    Player* get_player();
    Player* find_player(int obj_id);

 	int add_player(Player* obj, int new_id);
    void delete_player(int cl_id);

    int add_wall(Wall* obj, int new_id);
    void delete_wall(int id);
    Wall* get_wall(int id);
 	int add_bullet(DrawableBullet* obj);
    void delete_bullet(DrawableBullet* b);
};

#endif  // SCAV_GAME_OBJECT_HPP_
