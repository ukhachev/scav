#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "Box2D/Box2D.h"
#include <SFML/Network.hpp>

class GameObject {
 protected:
	int id;
 public:
	GameObject(int _id);
	void set_id(int _id);
	virtual ~GameObject();
	virtual int object_type() = 0; //1 игрок, 2 статика, 3 аптечка, 4 тайл
	virtual int texture();
	int get_id();
};

class PhysicsObject: public GameObject {
protected:
	b2Body* body;
	b2World* world;
	int hp;
 public:
 	PhysicsObject(int _id, b2World* _world);
 	virtual ~PhysicsObject();
 	virtual const b2Vec2 get_pos() const;
 	virtual void set_pos(float px, float py);

 	int get_hp();
 	void hit(int dmg);
 	void set_hp(int val);
};

class StaticObject: public PhysicsObject {
	int texture_id;
 public:
	StaticObject(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos, int t);
	~StaticObject();
	int object_type();
	virtual int texture();
};

class KinematicObject: public PhysicsObject {
 public:
 	KinematicObject(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
 	~KinematicObject();
 	void set_speed(float sx, float sy);
 	const b2Vec2& get_speed() const;
 	int object_type();
};


class Bullet: public KinematicObject {
 private:
 	int dmg;
 public:
	Bullet(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos, const b2Vec2& speed, int _dmg);
	~Bullet();
	int get_dmg();
	int object_type();
};

class Entity: public PhysicsObject {
 public:
	Entity(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
	virtual ~Entity();
	virtual void interact(PhysicsObject* object, sf::Packet* packet) = 0;
};
#endif