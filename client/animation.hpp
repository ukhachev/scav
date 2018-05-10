#ifndef SCAV_ANIMATION_HPP_
#define SCAV_ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <list>

using namespace sf;

class TempObject {
protected:
    Sprite* temp_sprite;
    int timer;
public:
    TempObject(Texture* tenp_texture, int _timer, float x, float y);
    TempObject(Sprite* new_sprite, int _timer);
    TempObject();
    virtual int get_timer();
    virtual void draw(RenderWindow& window);
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

class AnimationObject: public TempObject {
 private:
     int frames;
     int cur_frame;
 public:
     AnimationObject(Sprite* new_sprite, int _frames /*int _timer*/);
     AnimationObject(AnimationObject* a_obj);
     int get_timer();
     void set_position(Vector2f new_pos);
     void draw(RenderWindow& window);
     ~AnimationObject();
};


#endif   // SCAV_ANIMATION_HPP_
