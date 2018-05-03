#include "animation.hpp"
#include <iostream>



TempObject::TempObject(Texture* temp_texture, int _timer, float x, float y): timer(_timer) {
    temp_sprite = new Sprite(*temp_texture);
    temp_sprite->setPosition(x, y);
    temp_sprite->setOrigin(temp_sprite->getLocalBounds().width / 2, temp_sprite->getLocalBounds().height / 2);
    temp_sprite->setScale(0.25, 0.25);
}


int TempObject::get_timer() {
    return timer;
}

void TempObject::draw(RenderWindow& window) {
    window.draw(*temp_sprite);
    timer--;
}

TempObject::~TempObject() {
    delete temp_sprite;
}


TempContainer::TempContainer() {}


void TempContainer::add(TempObject* tmp_obj) {
    tmp_list.push_back(tmp_obj);
}

void TempContainer::draw(RenderWindow& window) {
    for (auto iter = tmp_list.begin(); iter != tmp_list.end(); iter++) {
        if((*iter)->get_timer() != 0) {
            (*iter)->draw(window);
        } else {
            tmp_list.erase(iter);
            iter--;
        }
    }
}

TempContainer::~TempContainer() {
    for (auto iter = tmp_list.begin(); iter != tmp_list.end(); iter++) {
        tmp_list.erase(iter);
    }
}
