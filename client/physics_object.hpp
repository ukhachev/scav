#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include <Box2D/Box2D.h>

class PhysicsObject {
protected:
	b2Body* body;
	b2World* world;

 public:
 	PhysicsObject(b2World* _world);
 	virtual ~PhysicsObject();
 	virtual const b2Vec2& get_pos() const;
 	virtual void set_pos(float px, float py);
};

class StaticObject: public PhysicsObject {
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


/*class Bullet: public KinematicObject {

};*/

#endif