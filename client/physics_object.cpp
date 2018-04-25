#include "physics_object.hpp"

PhysicsObject::PhysicsObject(b2World* _world) : world(_world) {

}

PhysicsObject::~PhysicsObject() {
	this->body->GetWorld()->DestroyBody(body);
}

void PhysicsObject::set_pos(float px, float py) {
	body->SetTransform(b2Vec2(px, py), 0);
}

const b2Vec2& PhysicsObject::get_pos() const {
	return body->GetLocalCenter();
}

StaticObject::StaticObject(b2World* _world, const b2Vec2& size,const b2Vec2& pos) : PhysicsObject(_world) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x, pos.y);
	def.type = b2_staticBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x, size.y);

	b2FixtureDef fixture;
	fixture.density = 0;
	fixture.shape = &shape;

	body->CreateFixture(&fixture); 

}

StaticObject::~StaticObject() {
	this->body->GetWorld()->DestroyBody(body);
}

KinematicObject::KinematicObject(b2World* _world, const b2Vec2& size,const b2Vec2& pos): PhysicsObject(_world) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x, pos.y);
	def.type = b2_staticBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x, size.y);

	b2FixtureDef fixture;
	fixture.density = 1;
	fixture.friction = 0;
	fixture.shape = &shape;

	body->CreateFixture(&fixture); 

}

KinematicObject::~KinematicObject() {
	this->body->GetWorld()->DestroyBody(body);
}

void KinematicObject::set_speed(float sx, float sy) {
	body->SetLinearVelocity(b2Vec2(sx, sy));
}

const b2Vec2& KinematicObject::get_speed() const {
	return body->GetLinearVelocity();
}
