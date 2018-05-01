#ifndef SCAV_ACTION_HPP_
#define SCAV_ACTION_HPP_
#include <SFML/Network.hpp>
#include "gamefield.hpp"
#include "textures.hpp"
/*class Action {
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
*/
class ActionConstructor {
 public:
	static void execute_action(GameField* field, sf::Packet& packet, Textures* textures);
};

#endif
