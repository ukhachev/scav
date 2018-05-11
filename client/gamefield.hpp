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
#include "menu.hpp"
#include "animation.hpp"
#include "cursor.hpp"
#include "inventor.hpp"
#include <map>
#include <list>
#include <ctime>
using namespace sf;

class GameField {
 private:

    b2World* world;
    Textures t_cont;
    MapConst g_map;
    Interface interface;
    Cursor g_curs;
    Inventor inv;
    bool start;

    Player* player;
    RenderWindow window;
    View g_cam;

    TempContainer tmp_a_cont;

    RectangleShape field_border;

    StaticObject* borders[4];
 	std::map<int, Player*> players;
 	std::map<int, PhysicsObject*> objects;
    bool was_shot;
 	std::list<DrawableBullet*> bullets;
 	std::mutex mtx;
    int last_shot;

    void draw_border(float x, float y);
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
    void delete_all();

    Inventor* get_inventor();
    int add_object(PhysicsObject* obj, int new_id);
    void set_start(bool _s);
    bool get_start();
    void delete_object(int id);
    PhysicsObject* get_object(int id);

 	int add_bullet(DrawableBullet* obj);
    void delete_bullet(DrawableBullet* b);
    void move_border(float secs);
    RenderWindow* get_window();
};

#endif  // SCAV_GAME_OBJECT_HPP_
