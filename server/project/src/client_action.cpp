#include <server.hpp>
#include <iostream>
#include <math.h>
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

void PlayerJoinedAction::execute(GameField& gf) {
	gf.add_player(cl_id);
	*(gf.get_state_packet()) << 100 << cl_id << cl_id;
}

//Moves player

MoveAction::MoveAction(int _cl_id, sf::Packet& packet) : ClientAction(_cl_id) {
	packet >> this->x >> this->y >> this->angle;
}

MoveAction::~MoveAction() {
}

void MoveAction::execute(GameField& gf) {
	Player* player = gf.get_player(cl_id);
	player->set_pos(x, y);
	*(gf.get_state_packet()) << 1 << cl_id << x << y << angle;
}

ShotAction::ShotAction(int _cl_id, sf::Packet& packet): ClientAction(_cl_id) {
	packet >> start_point.x >> start_point.y >> angle; 
}

ShotAction::~ShotAction() {

}

void ShotAction::execute(GameField& gf) {
	b2World* world = gf.get_world();
	Bullet* bullet = new Bullet(cl_id, world, b2Vec2(4, 4), start_point, b2Vec2(100 * cos(angle) , 100 * sin(angle)), 10);
	gf.add_bullet(bullet);
}