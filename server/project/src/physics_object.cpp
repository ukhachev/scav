#include "physics_object.hpp"
#include <iostream>
PhysicsObject::PhysicsObject(int _id, b2World* _world) : 
					GameObject(_id), world(_world) {

}

PhysicsObject::~PhysicsObject() {
	body->SetActive(false);
	this->body->GetWorld()->DestroyBody(body);
	std::cout << "delete" << std::endl;

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

StaticObject::StaticObject(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos) : PhysicsObject(_id, _world) {
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
	//body->SetActive(false);
	//this->body->GetWorld()->DestroyBody(body);
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
	//this->body->GetWorld()->DestroyBody(body);
}

void KinematicObject::set_speed(float sx, float sy) {
	body->SetLinearVelocity(b2Vec2(sx /100.f, sy /100.f));
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
	//body->SetActive(false);
	//this->body->GetWorld()->DestroyBody(body);
}

int Bullet::get_dmg() {
	return dmg;
}