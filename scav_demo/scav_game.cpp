#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <map>

#include 'scav_game.hpp'

int GameObject::get_id() {
    return id;
}

void MoveAction::execute(GameObject* g) {
    g->move(dx, dy);
}



void GameField::render(RenderWindow *window) {
    for(auto iter = map.begine(); iter != map.end(); iter++) {
        iter->draw(window);
    }
}


void GameField::
