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

	if (object->get_hp() > 0) {
		//Нанесение урона
		*(field.get_state_packet()) << 5 << id << hp;
	}
	else {
		//Объект уничтожен
		*(field.get_state_packet()) << 6 << id;
	}
	field.delete_bullet(bullet);
	//Реализовать удаление пули и смерть игрока
}
