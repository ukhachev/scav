#ifndef SCAV_ACTION_HPP_
#define SCAV_ACTION_HPP_

#include <game_field.hpp>

class Action {
 protected:
	int obj_id;
public:
	Action(int obj);
	int get_object_id();
	virtual ~Action();
	virtual void execute(GameObject* obj, GameField* field);
};



class MoveAction: public Action {
protected:
	sf::Vector2f pos;
public:
	MoveAction(int id, float _x, float _y);
	void execute(GameObject* obj, GameField* field);
};

class ActionConstructor {
	static Action* get_action(sf::packet& packet);
};

class RotateAction : public Action {
 protected:
 	float angle;
 public:
 	RotateAction(int id, float _angle);
	void execute(GameObject* obj, GameField* field);
};

#endif