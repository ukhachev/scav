#ifndef SCAV_GAME_OBJECT_HPP_
#define SCAV_GAME_OBJECT_HPP_
//проверить течь памяти
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Box2D/Box2D.h"
#include "physics_object.hpp"
#include "animation.hpp"

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
    virtual void set_pos(Vector2f new_pos);
 	  virtual void draw(RenderWindow &window);
    virtual void hit();
    virtual void get_delete_sprite(TempContainer& tmp_a_cont);
    virtual ~DrawableObject();
};


class Player: public DrawableObject, public KinematicObject {
 private:
    float player_rotation;
    Sprite* skin;
    Sprite* damage;
    Sprite* dead;
    int timer;
    int ammo;
    std::string nickname;
 public:
    Player(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
    void set_pos(Vector2f new_pos);

    int get_ammo();
    void set_ammo(int val);

    void set_player_sprite(Texture* player_texture);
    void set_damage_sprite(Texture* damage_texture);
    void set_dead_sprite(Texture* dead_texture);
    void get_delete_sprite(TempContainer& tmp_a_cont);

    //void set_position();
    void mouse_rotation(RenderWindow &window);
    void set_rotation(float new_rot);
    float get_rotation();
    void draw(RenderWindow &window);
    void hit();
    void set_nickname(const std::string& nickname);
    void interpolate(float x, float y);
    const std::string& get_nickname();
    //void get_damage(int dmg);

    ~Player();
};

class DrawableBullet: public DrawableObject, public Bullet {
 private:
    Sprite* bullet_sprite;
 public:
    DrawableBullet(b2World* _world, const b2Vec2& size,const b2Vec2& pos, const b2Vec2& speed, int _dmg);
    void draw(RenderWindow &window);
    void set_rotation(float new_rot);
    void set_sprite(Texture* texture);
    ~DrawableBullet();
};

class Wall: public DrawableObject, public StaticObject {
 private:
     Sprite* wall_sprite;
     Sprite* damage;
     int timer;
 public:
      Wall(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
      void set_pos(Vector2f new_pos);
      void set_sprite(Texture* player_texture);
      void set_damage_sprite(Texture* damage_texture);
      void draw(RenderWindow& window);
      void set_dead_sprite(Texture* dead_texture);
      //void get_delete_sprite(TempContainer tmp_a_cont);
      void hit();
      void set_rotation(float new_rot);
      ~Wall();
};

class AidKit : public DrawableObject, public Entity {
 private:
    Sprite* sprite;
    //Sprite* dead;
    AnimationObject* dead;
 public:
    AidKit(int _id);
    void set_pos(Vector2f new_pos);
    void set_sprite(Texture* texture);
    //void set_dead_sprite(Texture* texture);
    void set_dead_animation(AnimationObject* a_obj);
    void get_delete_sprite(TempContainer& tmp_a_cont);
    void draw(RenderWindow& window);
    void set_rotation(float new_rot);
    ~AidKit();
};

/*class Cursor: public DrawableObject {
 private:
     Sprite* cursor;
 public:
     Cursor();
     void set_pos();
};*/

// Сделать класс для временных объектов с таймером, который изменяется при вызове метода draw.

#endif
