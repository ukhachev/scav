
//#include "view.hpp"
#include "gamefield.hpp"
#include "textures.hpp"
#include "map_constructor.hpp"
#include "camera.hpp"
#include <iostream>


GameField::GameField(): world(new b2World(b2Vec2(0, 0))) {
    player = nullptr;
    window.create(sf::VideoMode(640, 480), "project");
    window.setFramerateLimit(60);
    //window.setMouseCursorVisible(0);
}
b2World* GameField::get_physics_world() {
    return world;
}

Player* GameField::find_player(int obj_id) {

    auto iter = players.find(obj_id);
    if (iter != players.end()) {
        return iter->second;
    }

    return nullptr;

}


bool GameField::get_action(sf::Packet& packet) {

    if (player != nullptr) {
        packet << 1 << player->get_pos().x <<player->get_pos().y << player->get_rotation();
        return true;
    }
    mtx.unlock();
    return false;
}

void GameField::shoot(float x, float y) {
    b2Vec2 point(x, y);
    b2Vec2 aim_dir = point - player->get_pos();
}

void GameField::render() {
    Textures t_cont("textures.txt");
    Texture* t = t_cont.get_texture(4);
    //Sprite s(t_cont.get_texture(1));
    //Texture t;
    //t.loadFromFile("wall.png");
    //Sprite s(*t);
    //s.setScale(0.5, 0.5);
    MapConst g_map(20, 20, t_cont);
    //MapConst g_map(2, 2, t_cont);
    //View view; ---
    Camera g_cam;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        if (player != nullptr) {
            b2Vec2 speed(0, 0);

	        if(Keyboard::isKeyPressed(Keyboard::A)) {
	            speed += b2Vec2(-100.f, 0.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::D)) {
	            speed += b2Vec2(100.f, 0.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::W)) {
	            speed += b2Vec2(0.f, -100.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::S)) {
	            speed += b2Vec2(0.f, 100.f);
	        }
	        player->set_speed(speed.x, speed.y);

            //player->set_position();

            player->mouse_rotation(window);
            std::cout << "player" <<std::endl;
            g_cam.set_center(player);

        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            shoot(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
        }



        world->Step(1/60.f, 8, 3);
        window.clear();
        g_cam.draw(window);
        g_map.draw(window);
;

        for (auto iter = players.begin(); iter != players.end(); iter++) {
            iter->second->draw(window);
            //std::cout << iter->second->get_id() << std::endl;
        }
        for (auto iter = walls.begin(); iter != walls.end(); iter++) {
            iter->second->draw(window);
        }
        //g_map.draw(window);
        window.display();
    }
    delete player;
}



int GameField::add_player(Player* obj, int new_id) {

    players.emplace(new_id, obj);
    return 0;
}

int GameField::add_wall(Wall* obj, int new_id) {

    walls.emplace(new_id, obj);
    return 0;
}

/*int GameField::add_bullet(Bullet* obj, int new_id) {

    map_bullets.emplace(new_id, obj);

    return 0;
}*/

void GameField::set_player(int player_id) {
    player = find_player(player_id);
}

Player* GameField::get_player() {
    return player;
}
