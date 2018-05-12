#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "Box2D/Box2D.h"


class PhysicsObject {
protected:
	b2Body* body;
	b2World* world;
	int hp;
 public:
 	PhysicsObject(b2World* _world);
 	virtual ~PhysicsObject();
 	virtual const b2Vec2 get_pos() const;
 	virtual void set_pos(float px, float py);
 	int get_hp();
 	void set_hp(int _hp);
};

class StaticObject: public PhysicsObject {
 public:
	StaticObject(b2World* _world, const b2Vec2& size,const b2Vec2& pos);
	~StaticObject();
};

class KinematicObject: public PhysicsObject {
 public:
 	KinematicObject(b2World* _world, const b2Vec2& size,const b2Vec2& pos);
 	~KinematicObject();
 	void set_speed(float sx, float sy);
 	const b2Vec2& get_speed() const;
};


class Bullet: public PhysicsObject {
 private:
 	int dmg;
 public:
	Bullet(b2World* _world, const b2Vec2& size,const b2Vec2& pos, const b2Vec2& speed, int _dmg);
	~Bullet();
	void set_speed(float sx, float sy);
 	const b2Vec2& get_speed() const;
 	
	int get_dmg();
};

class Entity : public PhysicsObject {
 public:
 	Entity();
 	virtual ~Entity();
};

#endif