
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include "textures.hpp"



using namespace sf;

Textures::Textures(const char* file_name) {
	std::ifstream f_stream(file_name);
    int id;
    std::string str;
    while(f_stream >> id >> str) {
        Texture* texture  = new Texture();
        texture->loadFromFile(str);
        texture_container.emplace(id, texture);
    }
    f_stream.close();
}


Texture* Textures::get_texture(int _id) {
    auto iter = texture_container.find(_id);
    if (iter != texture_container.end()) {
        return iter->second;
    }
    return nullptr;
}


Textures::~Textures() {
	for (auto i = texture_container.begin(); i != texture_container.end(); ++i) {
		delete i->second;
	}
};


Animations::Animations(const char* file_name) {
    std::ifstream f_stream(file_name);
    int id;
    std::string str;
    int frames;
    while(f_stream >> id >> str >> frames) {
        //Texture texture;
        Texture* texture  = new Texture();
        texture->loadFromFile(str);
        //texture.loadFromFile(str);

        Sprite* anim_sprite = new Sprite(*texture);

        //anim_sprite->setOrigin()
        AnimationObject* a_obj = new AnimationObject(anim_sprite, frames);
        animation_container.emplace(id, a_obj);
    }
    f_stream.close();
}


AnimationObject* Animations::get_animation(int _id) {
    auto iter = animation_container.find(_id);
    if (iter != animation_container.end()) {
        return iter->second;
    }
    return nullptr;
}

Animations::~Animations() {
	for (auto i = animation_container.begin(); i != animation_container.end(); ++i) {
		delete i->second;
	}
};
