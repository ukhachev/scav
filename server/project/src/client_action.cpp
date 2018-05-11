#include <server.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
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
	*(gf.get_state_packet()) << 100 << cl_id;
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
	packet >> weapon >> start_point.x >> start_point.y >> angle; 
}

ShotAction::~ShotAction() {

}

void ShotAction::create_bullet(float angle, GameField& gf, int dmg) {
	b2World* world = gf.get_world();
	b2Vec2 speed(700 * cos(angle) , 700 * sin(angle));
	b2Vec2 delta_point(start_point.x + 40 * cos(angle), start_point.y + 40 * sin(angle));
	
	Bullet* bullet = new Bullet(cl_id, world, b2Vec2(4, 4), delta_point, speed, dmg);

	*(gf.get_state_packet()) << 14 << cl_id << delta_point.x << delta_point.y << angle;
	
	gf.add_bullet(bullet);

}

void ShotAction::execute(GameField& gf) {

	//srand(time(NULL));
	angle = (angle - 90) * (3.1415 / 180);
	int r = rand();
	switch (weapon) {
		case 103: {
			float da = (r % 20)/60.f - 1.f/12.f;
			create_bullet(angle + da, gf, 5);
			create_bullet(angle + (1.f /6.f) + da, gf, 5);
			create_bullet(angle -(1.f / 6.f) + da, gf, 5);
		}
		break;
		case 102: {
			float da = (r % 5)/60.f - 1.f/24.f;
			create_bullet(angle + da, gf, 5);
		}
		break;

		default: {
			float da = (r % 15)/60.f - 1.f/8.f;
			create_bullet(angle + da, gf, 10);
		}
	}
	
}

PlayerLeftAction::PlayerLeftAction(int _cl_id): ClientAction(_cl_id) {

}

PlayerLeftAction::~PlayerLeftAction() {

}

void PlayerLeftAction::execute(GameField& gf) {
	*(gf.get_state_packet()) << 102 << cl_id;
	gf.delete_player(cl_id);
}

SetNicknameAction::SetNicknameAction(int cl_id, sf::Packet& packet): ClientAction(cl_id) {
	packet >> nickname;
}

SetNicknameAction::~SetNicknameAction() {

}

void SetNicknameAction::execute(GameField& gf) {
	Player* p = gf.get_player(cl_id);
	if (p != nullptr) {
		p->set_nickname(nickname);
		*(gf.get_state_packet()) << 10 << cl_id << nickname;
	}
}