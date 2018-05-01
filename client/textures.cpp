
#include <sys/stat.h>
#include <sys/mman.h>
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
	};
}
