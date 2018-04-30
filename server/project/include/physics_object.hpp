#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "Box2D/Box2D.h"

class GameObject {
 protected:
	int id;
 public:
	GameObject(int _id);
	void set_id(int _id);
	virtual ~GameObject();
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
 	virtual const b2Vec2& get_pos() const;
 	virtual void set_pos(float px, float py);
 	int get_hp();
 	void hit(int dmg);
};

class StaticObject: public PhysicsObject {
 public:
	StaticObject(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
	~StaticObject();
};

class KinematicObject: public PhysicsObject {
 public:
 	KinematicObject(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
 	~KinematicObject();
 	void set_speed(float sx, float sy);
 	const b2Vec2& get_speed() const;
};


class Bullet: public KinematicObject {
 private:
 	int dmg;
 public:
	Bullet(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos, const b2Vec2& speed, int _dmg);
	~Bullet();
	int get_dmg();
};

#endif