#include "animation.hpp"
#include <iostream>



TempObject::TempObject(Texture* temp_texture, int _timer, float x, float y): timer(_timer) {
    temp_sprite = new Sprite(*temp_texture);
    temp_sprite->setPosition(x, y);
    temp_sprite->setOrigin(temp_sprite->getLocalBounds().width / 2, temp_sprite->getLocalBounds().height / 2);
   // temp_sprite->setScale(3, 3);
}

TempObject::TempObject(Sprite* new_sprite, int _timer): timer(_timer) {
    temp_sprite = new_sprite;
    //temp_sprite->setPosition(x, y);
    //temp_sprite->setOrigin(temp_sprite->getLocalBounds().width / 2, temp_sprite->getLocalBounds().height / 2);
    //temp_sprite->setScale(0.25, 0.25);
}

TempObject::TempObject() {}


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
    /*for (auto iter = tmp_list.begin(); iter != tmp_list.end(); iter++) {
        if((*iter)->get_timer() != 0) {
            (*iter)->draw(window);
        } else {
            tmp_list.erase(iter);
            delete *iter;
            iter--;
        }
    }*/
    auto iter = tmp_list.begin();
    while (iter != tmp_list.end()) {
        if((*iter)->get_timer() != 0) {
            (*iter)->draw(window);
            iter++;
        } else {
            delete *iter;
            iter = tmp_list.erase(iter);
        }
    }
}

TempContainer::~TempContainer() {
    for (auto iter = tmp_list.begin(); iter != tmp_list.end(); iter++) {
        tmp_list.erase(iter);
    }
}

AnimationObject::AnimationObject(Sprite* new_sprite, int _frames/*int _timer*/): TempObject(new_sprite, 20/*_timer*/) {
    frames = _frames;
    cur_frame = 0;
    temp_sprite->setTextureRect(IntRect(96 * cur_frame, 0, 96, 96));
    temp_sprite->setScale(16, 16);
    temp_sprite->setOrigin(temp_sprite->getLocalBounds().width / 2, temp_sprite->getLocalBounds().height / 2);
    //temp_sprite = new_sprite;
    //temp_sprite->setTextureRect(IntRect(96 * cur_frame, 0, 96, 96));
    //temp_sprite->setOrigin(temp_sprite->getLocalBounds().width / 2, temp_sprite->getLocalBounds().height / 2);
}

AnimationObject::AnimationObject(AnimationObject* a_obj) {
    frames = a_obj->frames;
    timer = a_obj->timer;
    temp_sprite = new Sprite;
    *temp_sprite = *(a_obj->temp_sprite);
}

void AnimationObject::set_position(Vector2f new_pos) {
    temp_sprite->setPosition(new_pos);
}

int AnimationObject::get_timer() {
    return timer;
}


void AnimationObject::draw(RenderWindow& window) {
    if ((timer % 4) == 0) {
        if (cur_frame < frames) {
            temp_sprite->setTextureRect(IntRect(96 * cur_frame, 0, 96, 96));
            cur_frame++;
        }
    }
    window.draw(*temp_sprite);
    timer--;
}

AnimationObject::~AnimationObject() {
    std::cout << "deleted" << std::endl;
    //delete temp_sprite;
}
