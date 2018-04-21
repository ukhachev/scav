#ifndef SCAV_SERVER_ACTION_CONTAINER_HPP_
#define SCAV_SERVER_ACTION_CONTAINER_HPP_

#include "client_action.hpp"
#include <mutex>
#include <stack>

class ActionContainer {
 private:
 	std::stack<ClientAction*> actions;
 public:
	ActionContainer();
	~ActionContainer();
	ClientAction* pop();
	void add_action(ClientAction* action);
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
 	void add_action(ClientAction* action);
};

#endif