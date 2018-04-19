#ifndef SCAV_SERVER_CLIENT_ACTION_HPP_
#define SCAV_SERVER_CLIENT_ACTION_HPP_

#include "game_object.hpp"
#include "game_field.hpp"
#include <SFML/Network.hpp>
#include <list>

class ClientAction {
 protected:
 	int cl_id;
 public:
 	ClientAction(int _cl_id);
 	virtual ~ClientAction();
 	int get_client_id();
	virtual int get_id() = 0;
	virtual void execute(GameField& gf) = 0;
};

class PlayerJoinedAction: public ClientAction {
 public:
 	PlayerJoinedAction(int _cl_id);
 	~PlayerJoinedAction();
 	int get_id();
 	void execute(GameField& gf);
};

class MoveAction : public ClientAction {
 private:
	float x;
	float y;
	float angle;
 public:
 	MoveAction(int _cl_id, sf::Packet& packet);
 	~MoveAction();
 	int get_id();
	void execute(GameField& gf);
};

#endif
