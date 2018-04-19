#ifndef SCAV_ACTION_HPP_
#define SCAV_ACTION_HPP_

#include "game_object.hpp"
//#include "gamefield.hp.h
#include<SFML/Network.hpp>

class Action {
 protected:
	int obj_id;
public:
	Action(int obj);
	int get_object_id();
	virtual ~Action();
	virtual void execute(GameObject* obj/*, GameField& field*/);
};



class MoveAction: public Action {
protected:
	sf::Vector2f pos;
public:
	MoveAction(int id, float _x, float _y);
	void execute(DrawableObject* obj/*, GameField& field*/);
    //~MoveAction();
};

/*class ActionConstructor {
 private:
	static int cl_id;
 public:
	static void execute_action(GameField& field, sf::Packet& packet);
};*/



#endif
