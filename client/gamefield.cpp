
#include "view.hpp"
#include "gamefield.hpp"
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

DrawableObject* GameField::find(int obj_id) {

    auto iter = map.find(obj_id);
    if (iter != map.end()) {
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


void GameField::render() {
    Texture *map_text = new Texture();
    map_text->loadFromFile("game_map.png");
    //Camera player_cam;
    GameMap g_map = new GameMap(map_text);
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
            //std::cout << player->get_rotation() << std::endl;
            std::cout << "player" <<std::endl;

        }
        world->Step(1/60.f, 8, 3);
        window.clear();


        //player_cam.set_center(player->get_pos());
        g_map.draw(window);
        for (auto iter = map.begin(); iter != map.end(); iter++) {
            iter->second->draw(window);
            //std::cout << iter->second->get_id() << std::endl;
        }


        //player_cam.draw(window);
        window.display();
    }
    delete map_text;
    delete player;
    //delete map;
}



int GameField::add(DrawableObject* obj, int new_id) {

    map.emplace(new_id, obj);

    return 0;
}


void GameField::set_player(int player_id) {
    player = dynamic_cast<Player*>(find(player_id));
}

Player* GameField::get_player() {
    return player;
}
