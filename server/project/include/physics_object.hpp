#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "Box2D/Box2D.h"

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
	b2Body* body;
	b2World* world;

 public:
 	PhysicsObject(int _id, b2World* _world);
 	virtual ~PhysicsObject();
 	virtual const b2Vec2& get_pos() const;
 	virtual void set_pos(float px, float py);
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


/*class Bullet: public KinematicObject {

};*/

#endif