#ifndef SCAV_ANIMATION_HPP_
#define SCAV_ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <list>

using namespace sf;

class TempObject {
private:
    Sprite* temp_sprite;
    int timer;
public:
    TempObject(Texture* tenp_texture, int _timer, float x, float y);
    TempObject(Sprite* new_sprite, int _timer);
    int get_timer();
    void draw(RenderWindow& window);
    ~TempObject();
};

class TempContainer {
 private:
     std::list<TempObject*> tmp_list;
 public:
     TempContainer();
     void add(TempObject* tmp_obj);
     void draw(RenderWindow& window);
     ~TempContainer();
};


#endif   // SCAV_ANIMATION_HPP_
