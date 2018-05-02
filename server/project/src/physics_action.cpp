#include "physics_action.hpp"
#include <iostream>
PhysicsAction::PhysicsAction() {
}

PhysicsAction::~PhysicsAction() {
}

HitPhysicsAction::HitPhysicsAction(Bullet* b, PhysicsObject* o) : bullet(b), object(o) {

}

HitPhysicsAction::~HitPhysicsAction() {

}

void HitPhysicsAction::execute(GameField& field) {
	object->hit(bullet->get_dmg());
	
	int hp = object->get_hp();
	int id = object->get_id();
	std::cout << id << std::endl;

	if (id > 0) {
		*(field.get_state_packet()) << 5 << id << hp;

		if (object->get_hp() < 0) {
			field.delete_object(id);
		
		}
	}
	field.delete_bullet(bullet);
}
