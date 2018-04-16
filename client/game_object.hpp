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

#endif