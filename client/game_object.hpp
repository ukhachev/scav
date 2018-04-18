#ifndef SCAV_GAME_OBJECT_HPP_
#define SCAV_GAME_OBJECT_HPP_

#include <SFML/System.hpp>

class GameObject {
 private:
	int id;
 public:
 	GameObject(int _id);
 	virtual ~GameObject();
 	int get_id();
};

//Fix this: need rotation angle or transform draw - отрисовка
class DrawableObject {
 private:
 	sf::Vector2f pos;
 public:
 	const sf::Vector2f& get_pos() const;
 	virtual void draw();
};


class Player: public DrawableObject, public GameObject {
 private:
    float rotation;
    sf::Sprite* skin;
 public:
    Player();
    void set_palyer_sprite(Texture& player_texture);
    void set_rotation(DrawableObject* cursor, GameField* window);
    float get_rotation();
    void draw(RenderWindow* window);
}

class GameMap: public DrawableObject {
 private:
    sf::Sprite* map_sprite;
 public:
     GameMap(Texture map_texture);

}


#endif
