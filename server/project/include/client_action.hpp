ActionContainer::~ActionContainer() {
	for (auto i = actions.begin(); i != actions.end(); ++i) {
		delete i->second;
	}
}

int ActionContainer::get_hash(int x, int y) {
	return (y - 1) * (y - 2) / 2 + x;
}