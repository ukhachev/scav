#include "physics_object.hpp"
#include <iostream>
PhysicsObject::PhysicsObject(int _id, b2World* _world) : 
					GameObject(_id), world(_world), hp(100) {

}

PhysicsObject::~PhysicsObject() {
	body->SetActive(false);
	this->body->GetWorld()->DestroyBody(body);

}

void PhysicsObject::set_pos(float px, float py) {

	body->SetTransform(b2Vec2(px /100.f, py / 100.f), 0);
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

void PhysicsObject::set_hp(int val) {
	hp = val;
}


StaticObject::StaticObject(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos, int t) 
			: PhysicsObject(_id, _world), texture_id(t) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x /100.f, pos.y / 100.f);
	def.type = b2_staticBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x /100.f, size.y /100.f);

	b2FixtureDef fixture;
	fixture.density = 0;
	fixture.shape = &shape;

	body->CreateFixture(&fixture);
	body->SetUserData(this); 

}

StaticObject::~StaticObject() {

}

int StaticObject::object_type() {
	return 2;
}

int StaticObject::texture() {
	return texture_id;
}

KinematicObject::KinematicObject(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos): PhysicsObject(_id, _world) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x /100.f, pos.y /100.f);
	def.type = b2_dynamicBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x /100.f, size.y /100.f);

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
	body->SetLinearVelocity(b2Vec2(sx /100.f, sy /100.f));
}

int KinematicObject::object_type() {
	return 1;
}

const b2Vec2& KinematicObject::get_speed() const {
	return body->GetLinearVelocity();
}

Bullet::Bullet(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos, const b2Vec2& speed, int _dmg): 
							KinematicObject(_id, _world, size, pos), dmg(_dmg) {
	body->SetBullet(true);
	set_speed(speed.x, speed.y);
}

Bullet::~Bullet() {
}

int Bullet::object_type() {
	return 0;
}

int Bullet::get_dmg() {
	return dmg;
}

Entity::Entity(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos) : PhysicsObject(_id, _world) {
	b2BodyDef def;
	def.position = b2Vec2(pos.x /100.f, pos.y /100.f);
	def.type = b2_dynamicBody;
	body = world->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x /100.f, size.y /100.f);

	b2FixtureDef fixture;
	fixture.density = 1;
	fixture.friction = 0;
	fixture.shape = &shape;
	fixture.isSensor = true;
	body->CreateFixture(&fixture);
	body->SetUserData(this);
	body->SetSleepingAllowed(false);
}

Entity::~Entity() {

}


