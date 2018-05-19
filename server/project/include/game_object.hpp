#ifndef SCAV_SERVER_GAME_OBJECT_HPP_
#define SCAV_SERVER_GAME_OBJECT_HPP_

#include "Box2D/Box2D.h"
#include <SFML/System.hpp>
#include "physics_object.hpp"

class Player : public KinematicObject {
	std::string nickname;
 public:
 	Player(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos,const std::string& nick);
 	void set_nickname(const std::string& nick);
 	const std::string& get_nickname();
 	~Player();
};

class AidKit : public Entity {
 public:
	AidKit(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
	~AidKit();
	int texture();
	void interact(PhysicsObject* object, sf::Packet* packet);
	int object_type();
};


class LandingMine: public Entity {
 public:
	LandingMine(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
	~LandingMine();
	int texture();
	void interact(PhysicsObject* object, sf::Packet* packet);
	int object_type();
};

class BulletContainer: public Entity {
 public:
	BulletContainer(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
	~BulletContainer();
	int texture();
	void interact(PhysicsObject* object, sf::Packet* packet);
	int object_type();
};

class Weapon: public Entity {
 private: 
 	int type;
 public:
	Weapon(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos, int t);
	~Weapon();
	int texture();
	void interact(PhysicsObject* object, sf::Packet* packet);
	int object_type();
};

class Tile: public GameObject {
 private:
 	b2Vec2 pos;
	b2Vec2 size;
 	int texture_id;

 public:
 	Tile(float x, float y, float sx, float sy, int t);
	const b2Vec2& get_size();
	const b2Vec2& get_pos();
	int object_type();
	int texture();
};

#endif