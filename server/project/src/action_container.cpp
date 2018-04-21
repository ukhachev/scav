#include "server.hpp"

ActionContainer::ActionContainer() {
}

ActionContainer::~ActionContainer() {
	for (auto i = begin(); i != end(); ++i) {
		delete *i;
	}
}

std::list<ClientAction*>::iterator ActionContainer::begin() {
	return actions.begin();
}

std::list<ClientAction*>::iterator ActionContainer::end() {
	return actions.end();
}

void ActionContainer::add_action(ClientAction* action) {
	actions.push_back(action);
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