
//#include "view.hpp"
#include "gamefield.hpp"
#include "textures.hpp"
#include "map_constructor.hpp"
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
    Textures t_cont("textures.txt");
    Texture* t = t_cont.get_texture(2);
    //Sprite s(t_cont.get_texture(1));
    //Texture t;
    //t.loadFromFile("wall.png");
    Sprite s(*t);
    s.setScale(0.1, 0.1);

    //MapConst g_map(2, 2, t_cont);
    while (window.isOpen())
    {
        View view;
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
            view.setCenter(player->get_pos().x, player->get_pos().y);

        }
        world->Step(1/60.f, 8, 3);
        window.clear();
        window.setView(view);

        window.draw(s);

        for (auto iter = map.begin(); iter != map.end(); iter++) {
            iter->second->draw(window);
            //std::cout << iter->second->get_id() << std::endl;
        }
        //g_map.draw(window);
        window.display();
    }
    delete player;
}



int GameField::add(DrawableObject* obj, int new_id) {

    map.emplace(new_id, obj);

    return 0;
}

int GameField::add_wall(Wall* obj, int new_id) {

    map_wall.emplace(new_id, obj);

    return 0;
}

/*int GameField::add_bullet(Bullet* obj, int new_id) {

    map_bullets.emplace(new_id, obj);

    return 0;
}*/

void GameField::set_player(int player_id) {
    player = dynamic_cast<Player*>(find(player_id));
}

Player* GameField::get_player() {
    return player;
}
