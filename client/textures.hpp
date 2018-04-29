#ifndef SCAV_TEXTURES_HPP_
#define SCAV_TEXTURES_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>

using namespace sf;

class Textures {
 private:
    std::map<int, Texture> texture_container;
 public:
     Textures(const char* file_name);
     Texture get_texture(int _id);
     ~Textures();
};


#endif  // SCAV_TEXTURES_HPP_
