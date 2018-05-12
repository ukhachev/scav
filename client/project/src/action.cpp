#include "action.hpp"


Action* ActionConstructor::get_action(sf::Packet& packet, Textures* textures) {
	int act_id = 0;
	packet >> act_id;

	switch (act_id) {
		case 1: return new MoveAction(packet, textures);
	}

}

Action::Action(sf::Packet& packet, Textures* _textures): textures(_textures)  {
	packet >> obj_id;
}

Action::~Action() {

}

int Action::get_object_id() {
    return obj_id;
}

MoveAction::MoveAction(sf::Packet& packet, Textures* _textures): 
			Action(packet, _textures) {
    packet >> x >> y >> angle;
}

MoveAction::~MoveAction() {

}

void MoveAction::execute(GameField* field) {
    Player* obj = field->find_player(obj_id);
	if (obj != nullptr && obj != field->get_player()) {
		Vector2f pos(x, y);
		obj->set_pos(pos);
		obj->set_rotation(angle);
	}
}
