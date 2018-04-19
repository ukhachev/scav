#ifndef SCAV_SERVER_ACTION_CONTAINER_HPP_
#define SCAV_SERVER_ACTION_CONTAINER_HPP_

#include "client_action.hpp"
#include <mutex>
#include <map>

class ActionContainer {
 private:
 	std::map<int, ClientAction*> actions;
 	int get_hash(int x, int y);
 public:
	ActionContainer();
	~ActionContainer();

	std::map<int, ClientAction*>::iterator begin();
	std::map<int, ClientAction*>::iterator end();

	void add_action(int cl_id, ClientAction* action);
};

class SafeActionContainer {
 private:
 	ActionContainer* actions;
 	std::mutex mtx;

 public:
 	SafeActionContainer(const SafeActionContainer&);
 	SafeActionContainer();
 	~SafeActionContainer();
 	ActionContainer* get_actions();
 	void add_action(int cl_id, ClientAction* action);
};

#endif