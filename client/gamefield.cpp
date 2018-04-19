

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
    return iter->second;
}


/*bool GameField::get_action(sf::Packet& packet) {
if (player == nullptr) {
return false;
&
packet << 1 << player->get_pos().x <<player->get_pos().y << player->get_rotation();
}
}*/


void GameField::render(Player* player) {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::A)) {
            MoveAction move(1, -10.f, 0.f);
            move.execute(player);
        }
        if(Keyboard::isKeyPressed(Keyboard::D)) {
            MoveAction move(1, 10.f, 0.f);
            move.execute(player);
        }
        if(Keyboard::isKeyPressed(Keyboard::W)) {
            MoveAction move(1, 0.f, -10.f);
            move.execute(player);
        }
        if(Keyboard::isKeyPressed(Keyboard::S)) {
            MoveAction move(1, 0.f, 10.f);
            move.execute(player);
        }
        player->set_position();
        player->set_rotation(window);
        std::cout << player->get_rotation() << std::endl;

        window.clear();

        for (auto iter = map.begin(); iter != map.end(); iter++) {
            iter->second->draw(window);
            //std::cout << iter->second->get_id() << std::endl;

        }
        window.display();
    }
}



int GameField::add(DrawableObject* obj, int new_id) {
    auto iter = map.end();
    map.emplace(new_id, obj);
    return 0;
}


void GameField::set_player(int player_id) {
    player = new Player(player_id);
    add(player, player_id);
}

Player* GameField::get_player() {
    return player;
}
