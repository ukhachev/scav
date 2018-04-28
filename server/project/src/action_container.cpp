#include "server.hpp"

ActionContainer::ActionContainer() {
}

ActionContainer::~ActionContainer() {
	ClientAction* act = pop();
	while (act != nullptr) {
		delete act;
		act = pop();
	}
}

ClientAction* ActionContainer::pop() {
	if (actions.size() == 0) {
		return nullptr;
	}
	ClientAction* res = actions.front();
	actions.pop();
	return res;
}

void ActionContainer::add_action(ClientAction* action) {
	actions.push(action);
}

SafeActionContainer::SafeActionContainer() {
	actions = new ActionContainer();
}

SafeActionContainer::~SafeActionContainer() {
	mtx.lock();
		delete actions;
	mtx.unlock();
}

ActionContainer* SafeActionContainer::get_actions() {

	ActionContainer* res = actions;

	mtx.lock();
		actions = new ActionContainer();
	mtx.unlock();

	return res;
}

void SafeActionContainer::add_action(ClientAction* action) {
	mtx.lock();
		actions->add_action(action);
	mtx.unlock();
}