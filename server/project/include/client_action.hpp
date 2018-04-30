#ifndef SCAV_SERVER_CLIENT_ACTION_HPP_
#define SCAV_SERVER_CLIENT_ACTION_HPP_

#include "game_object.hpp"
#include "game_field.hpp"
#include <SFML/Network.hpp>
#include <list>
#include "Box2D/Box2D.h"

class ClientAction {
 protected:
 	int cl_id;
 public:
 	ClientAction(int _cl_id);
 	virtual ~ClientAction();
 	int get_client_id();
	virtual void execute(GameField& gf) = 0;
};

//100 action
class PlayerJoinedAction: public ClientAction {
 public:
 	PlayerJoinedAction(int _cl_id);
 	~PlayerJoinedAction();
 	void execute(GameField& gf);
};

//1 action
class MoveAction : public ClientAction {
 private:
	float x;
	float y;
	float angle;
 public:
 	MoveAction(int _cl_id, sf::Packet& packet);
 	~MoveAction();
	void execute(GameField& gf);
};

//14 action
class ShotAction : public ClientAction {
 private:
 	b2Vec2 start_point;
 	float angle;
 public:
 	ShotAction(int _cl_id, sf::Packet& packet);
 	~ShotAction();
 	void execute(GameField& gf);
};
#endif
