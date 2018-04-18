#include "server.hpp"

int ActionContainer::get_hash(int x, int y) {
	return y * 1000 + x;
}
ActionContainer::ActionContainer() {
}

ActionContainer::~ActionContainer() {
	for (auto i = begin(); i != end(); ++i) {
		delete i->second;
	}
}

std::map<int, ClientAction*>::iterator ActionContainer::begin() {
	return actions.begin();
}

std::map<int, ClientAction*>::iterator ActionContainer::end() {
	return actions.end();
}

void ActionContainer::add_action(int cl_id, ClientAction* action) {
	int id = get_hash(action->get_id(), cl_id);
	auto i = actions.find(id);

	if (i == actions.end()) {
		actions.emplace(id, action);
	} else {
		delete i->second;
		i->second = action;
	}
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

void SafeActionContainer::add_action(int cl_id, ClientAction* action) {
	mtx.lock();
		actions->add_action(cl_id, action);
	mtx.unlock();
}