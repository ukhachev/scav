
#include<sys/stat.h>
#include <sys/mman.h>
#include <sstream>
#include "textures.hpp"



using namespace sf;

Textures::Textures(const char* file_name) {
    FILE* fp = fopen(file_name, "r");
    struct stat st;
    stat(file_name, &st);
    char* f_pointer = reinterpret_cast<char*>(mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fileno(fp), 0));
    std::string f_string = f_pointer;
    std::istringstream f_stream(f_string);
    int id;
    std::string str;
    while(f_stream >> id >> str) {
        Texture texture;
        texture.loadFromFile(str);
        texture_container.emplace(id, texture);
    }
}


Texture Textures::get_texture(int _id) {
    auto iter = texture_container.find(_id);
    if (iter != texture_container.end()) {
        return iter->second;
    }
    //return nullptr;
}


Textures::~Textures() {

}
