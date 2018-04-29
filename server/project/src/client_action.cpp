#include <server.hpp>
#include <iostream>
//Base class
ClientAction::ClientAction(int _cl_id) : cl_id(_cl_id) {
}

ClientAction::~ClientAction() {
}

int ClientAction::get_client_id() {
	return cl_id;
}


//When new player joins

PlayerJoinedAction::PlayerJoinedAction(int _cl_id) : ClientAction(_cl_id) {
}

PlayerJoinedAction::~PlayerJoinedAction() {
}

int PlayerJoinedAction::get_id() {
	return 100;
}

void PlayerJoinedAction::execute(GameField& gf) {
	gf.add_player(cl_id);
	int id = gf.get_player(cl_id)->get_id();
	*(gf.get_state_packet()) << 100 << cl_id << cl_id;
}

//Moves player

MoveAction::MoveAction(int _cl_id, sf::Packet& packet) : ClientAction(_cl_id) {
	packet >> this->x >> this->y >> this->angle;
}

MoveAction::~MoveAction() {
}

int MoveAction::get_id() {
	return 1;
}

void MoveAction::execute(GameField& gf) {
	Player* player = gf.get_player(cl_id);
	//std::cout << id << std::endl;
	player->set_pos(x, y);
	*(gf.get_state_packet()) << 1 << id << x << y << angle;
}
