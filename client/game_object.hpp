#ifndef SCAV_GAME_OBJECT_HPP_
#define SCAV_GAME_OBJECT_HPP_
//проверить течь памяти
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Box2D/Box2D.h"
#include "physics_object.hpp"

using namespace sf;


class GameObject {
 private:
	int id;
 public:
 	GameObject(int _id);
 	//virtual ~GameObject();
 	int get_id();
};

class DrawableObject: public GameObject {
 protected:
    int id;
 	sf::Vector2f pos;
 public:
    virtual void set_rotation(float new_rot) = 0;
    DrawableObject(int _id);
 	//const sf::Vector2f& get_pos() const;
    virtual void set_pos(Vector2f new_pos);// сделать виртуальным
 	virtual void draw(RenderWindow &window);
    virtual ~DrawableObject();
};


class Player: public DrawableObject, public KinematicObject {
 private:
    float player_rotation;
    sf::Sprite* skin;
    int hp;
 public:
    Player(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
    void set_pos(Vector2f new_pos);
    void set_player_sprite(Texture* player_texture);
    //void set_position();
    void mouse_rotation(RenderWindow &window);
    void set_rotation(float new_rot);
    float get_rotation();
    void draw(RenderWindow &window);
    //void get_damage(int dmg);

    ~Player();
};

/*class Bullet: public DrawableObject {
 private:
    Vector2f velicity;
    Sprite* bullet_sprite;
    float maxSpeed;
 public:
    Bullet();

};*/

class Wall: public DrawableObject, public StaticObject {
 private:
     Sprite* wall_sprite;
 public:
      Wall(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
      void set_pos(Vector2f new_pos);
      void set_sprite(Texture* player_texture);
      void draw(RenderWindow& window);
      void set_rotation(float new_rot);
     // float get_rotation();
      ~Wall();
};


class Cursor: public DrawableObject {
 private:
     Sprite* cursor;
 public:
     Cursor();
     void set_pos();
};

// Сделать класс для временных объектов с таймером, который изменяется при вызове метода draw.

#endif
