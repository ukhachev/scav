#ifndef SCAV_GAME_OBJECT_HPP_
#define SCAV_GAME_OBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class GameObject {
 private:
	int id;
 public:
 	GameObject(int _id);
 	virtual ~GameObject();
 	int get_id();
};

//Fix this: need rotation angle or transform draw - отрисовка
class DrawableObject: public GameObject {
 private:
 	sf::Vector2f pos;
 public:
 	const sf::Vector2f& get_pos() const;
    void set_pos(Vector2f new_pos);
 	virtual void draw(RenderWindow* draw);
    virtual ~DrawableObject();
};


class Player: public DrawableObject{
 private:
    float rotation;
    sf::Sprite* skin;
 public:
    Player(int _id);
    void set_player_sprite(Texture player_texture);
    void set_rotation(RenderWindow* window);
    float get_rotation();
    void draw(RenderWindow* window);
    ~Player();
};

class GameMap: public DrawableObject {
 private:
    sf::Sprite* map_sprite;
 public:
     GameMap(Texture map_texture);
     ~GameMap();

};


#endif
