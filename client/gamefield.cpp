

#include "gamefield.hpp"


GameField::GameField() {
    player = nullptr;
    window = new RenderWindow(sf::VideoMode(640, 480), "project");
    window->setFramerateLimit(60);
    //window.setMouseCursorVisible(0);
}

DrawableObject* GameField::find(int obj_id) {
    auto iter = map.find(obj_id);
    return iter->second;
}

bool GameField::get_action(sf::Packet& packet) {
    if (player == nullptr) {
        return false;
    }
    packet << 1 << player->get_pos().x <<player->get_pos().y << player->get_rotation();
}


void GameField::render() {
    if(Keyboard::isKeyPressed(Keyboard::A)) {
    //MoveAction move()
    }
    if(Keyboard::isKeyPressed(Keyboard::D)) {

    }
    if(Keyboard::isKeyPressed(Keyboard::W)) {

    }
    if(Keyboard::isKeyPressed(Keyboard::S)) {

    }

    for (auto iter = map.begin(); iter != map.end(); iter++) {
        window->clear();
        iter->second->draw(*window);
        window->display();
    }
}

int GameField::add(DrawableObject *obj, int new_id) {
    auto iter = map.end();
    map.emplace(new_id, obj);
    return 0;
}

//Передача координат id = 1
/*void GameField::execute(Action *act) {
    int obj_id = act->get_object_id();
    auto iter = map.found(obj_id);
    act->execute(iter, this);
}*/



void GameField::set_player(int player_id) {
    Player* player = new Player(player_id);


}
