#include "physics_object.hpp"
#include <iostream>
PhysicsObject::PhysicsObject(b2World* _world) : 
					world(_world) {

}

PhysicsObject::~PhysicsObject() {
	this->body->GetWorld()->DestroyBody(body);
}

void PhysicsObject::set_pos(float px, float py) {
	body->SetTransform(b2Vec2(px /100.0f, py /100.0f), 0);
}

const b2Vec2 PhysicsObject::get_pos() const {
	b2Vec2 pos = body->GetWorldCenter();
	pos.x *= 100;
	pos.y *= 100;
	return pos;
}

int PhysicsObject::get_hp() {
	return hp;
}

void PhysicsObject::hit(int dmg) {
	hp -= dmg;
}

StaticObject::StaticObject(b2World* _world, const b2Vec2& size,const b2Vec2& pos) : PhysicsObject(_world) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x/100.0f, pos.y/100.0f);
	def.type = b2_staticBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x/100.0f, size.y/100.0f);

	b2FixtureDef fixture;
	fixture.density = 0;
	fixture.shape = &shape;

	body->CreateFixture(&fixture);
	body->SetUserData(this); 

}

StaticObject::~StaticObject() {
}

KinematicObject::KinematicObject(b2World* _world, const b2Vec2& size,const b2Vec2& pos): PhysicsObject(_world) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x/100.0f, pos.y/100.0f);
	def.type = b2_dynamicBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x/100.0f, size.y/100.0f);

	b2FixtureDef fixture;
	fixture.density = 1;
	fixture.friction = 0;
	fixture.shape = &shape;

	body->CreateFixture(&fixture);
	body->SetUserData(this); 

}

KinematicObject::~KinematicObject() {
	
}
void KinematicObject::set_speed(float sx, float sy) {
	body->SetLinearVelocity(b2Vec2(sx / 100.0f, sy / 100.0f));
}

const b2Vec2& KinematicObject::get_speed() const {
	return body->GetLinearVelocity();
}

Bullet::Bullet(b2World* _world, const b2Vec2& size,const b2Vec2& pos, const b2Vec2& speed, int _dmg): 
							PhysicsObject(_world), dmg(_dmg) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x/100.0f, pos.y/100.0f);
	def.type = b2_dynamicBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x /100.0f, size.y/100.0f);

	b2FixtureDef fixture;
	fixture.density = 1;
	fixture.friction = 0;
	fixture.shape = &shape;

	body->CreateFixture(&fixture);
	body->SetUserData(this); 

	body->SetBullet(true);
	b2Vec2 local_speed(speed.x / 100.0f, speed.y / 100.0f);
	body->SetLinearVelocity(local_speed);
}
void Bullet::set_speed(float sx, float sy) {
	body->SetLinearVelocity(b2Vec2(sx /100.0f, sy /100.0f));
}
const b2Vec2& Bullet::get_speed() const {

	return body->GetLinearVelocity();
}

Bullet::~Bullet() {

}

int Bullet::get_dmg() {
	return dmg;
}

