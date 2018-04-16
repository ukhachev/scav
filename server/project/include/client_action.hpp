#ifndef SCAV_SERVER_CLIENT_ACTION_HPP_
#define SCAV_SERVER_CLIENT_ACTION_HPP_

#include <game_object.hpp>

class ClientAction {
 protected:
	Player* player;
 public:
	int get_id();
	virtual void execute() = 0;
	Player* get_player();
};

class MoveAction : ClientAction {
 private:
	int direction;
 public:
	void execute();
};

#endif
