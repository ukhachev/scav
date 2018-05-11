#ifndef SCAV_ACTION_HPP_
#define SCAV_ACTION_HPP_
#include <SFML/Network.hpp>
#include "gamefield.hpp"
#include "textures.hpp"
class Action {
 protected:
	int obj_id;
	Textures* textures;
public:
	Action(sf::Packet& packet, Textures* _textures);
	int get_object_id();
	virtual ~Action();
	virtual void execute(GameField* field) = 0;
};



class MoveAction: public Action {
protected:
	float x;
	float y;
	float angle;

public:
	MoveAction(sf::Packet& packet, Textures* _textures);
	~MoveAction();
	void execute(GameField* field);
};

class ActionConstructor {
 public:
	static void execute_action(GameField* field, sf::Packet& packet, Textures* textures, Animations* animations);
	static Action* get_action(sf::Packet& packet, Textures* textures);
};

#endif
