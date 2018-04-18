

#include 'gamefield.hpp'


GameField::GameField() {
    player = nullptr;
    window = new RenderWindow(sf::VideoMode(640, 480), "project");
    window.setFramerateLimit(60);
    //window.setMouseCursorVisible(0);
}

bool GameField::get_action(sf::Pocket& packet) {
    if (player == nullptr) {
        return false;
    }
    packet << 1 << player->get_pos().x <<player->get_pos().y << player->get_rotation();
}


int GameField::render() {
    if(mp.begin() == NULL) {
        std::cout << "Map is empty." << std::endl;
        return 1;
    }
    for (auto iter = map.begin(); iter !=map.end(); iter++) {
        window.clear();
        iter->second->draw(window);
        window.display();
    }
}

void GameField::add(DrawableObject *obj) {
    auto iter = map.end();
    auto new_id = iter->first + 1;
    map.insert(new_id, obj);
}

//Передача координат id = 1
void GameField::execute(Action *act) {
    auto obj_id = act->get_object_id();
    auto iter = map.found(obj_id);
    act->execute(iter, this);
}



void GameField::set_player(int player_id) {
    Player* player = new Player();


}
