#ifndef SCAV_TEXTURES_HPP_
#define SCAV_TEXTURES_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include "animation.hpp"

using namespace sf;

class Textures {
 private:
    std::map<int, Texture*> texture_container;
 public:
     Textures(const char* file_name);
     Texture* get_texture(int _id);
     ~Textures();
};

class Animations {
 private:
     std::map<int, AnimationObject*> animation_container;
 public:
     Animations(const char* file_name);
     AnimationObject* get_animation(int _id);
     ~Animations();
};


#endif  // SCAV_TEXTURES_HPP_
