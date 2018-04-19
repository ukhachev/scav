#ifndef SCAV_SERVER_GAME_OBJECT_HPP_
#define SCAV_SERVER_GAME_OBJECT_HPP_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>

struct Position {
	float x;
	float y;
	float angle;
};

class GameObject {
 protected:
	int id;
 public:
	GameObject();
	virtual ~GameObject();
	void set_id(int _id);
	int get_id();
};

class PhysicsObject: public GameObject {
 protected:
	//b2Body body;
	Position pos;

 public:
 	PhysicsObject();
 	virtual ~PhysicsObject();
 	void set_position(float _x, float _y, float _angle);
 	const Position& get_pos();
	//b2Body& get_body();
};

class Player : public PhysicsObject {
	int cl_id;
 public:
 	Player(int _cl_id);
 	~Player();
 	int get_client();
};

#endif