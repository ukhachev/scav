

#include "gamefield.hpp"
#include <iostream>


GameField::GameField() {
    player = nullptr;
    window.create(sf::VideoMode(640, 480), "project");
    window.setFramerateLimit(60);
    //window.setMouseCursorVisible(0);
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
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        if (player != nullptr) {

	        Vector2f prev_position = player->get_pos();
            Vector2f pos;

	        if(Keyboard::isKeyPressed(Keyboard::A)) {
	            pos = Vector2f(-10.f, 0.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::D)) {
	            pos = Vector2f(10.f, 0.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::W)) {
	            pos = Vector2f(0.f, -10.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::S)) {
	            pos = Vector2f(0.f, 10.f);
	        }
	        player->set_pos(pos + prev_position);

            player->set_position();

            player->mouse_rotation(window);
            std::cout << player->get_rotation() << std::endl;
            std::cout << "player" <<std::endl;

        }

        window.clear();

        for (auto iter = map.begin(); iter != map.end(); iter++) {
            iter->second->draw(window);
            //std::cout << iter->second->get_id() << std::endl;
        }
        window.display();
    }
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
