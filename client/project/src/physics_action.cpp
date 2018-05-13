#include "physics_action.hpp"

PhysicsAction::PhysicsAction() {
}

PhysicsAction::~PhysicsAction() {
}

HitPhysicsAction::HitPhysicsAction(DrawableBullet* b, PhysicsObject* o) : bullet(b), object(o) {

}

HitPhysicsAction::~HitPhysicsAction() {

}

void HitPhysicsAction::execute(GameField& field) {
	
	int hp = object->get_hp();
	field.delete_bullet(bullet);
	DrawableObject* d_obj = dynamic_cast<DrawableObject*>(object);
	if (d_obj) {
		d_obj->hit();
	}
}
