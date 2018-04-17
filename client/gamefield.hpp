#include <game_object.hpp>
#include <SFML/Network.hpp>
//map содержит id объектов и указатели на них
//добавление: id последнего + 1
//execute: act->execute(<полученный из мапы указатель по id в act->get_object_id()>)
class GameField {
 private:
 	std::map<int, DrawableObject*> map;
 public:
 	void render();
 	void add(DrawableObject* obj);
 	void execute(Action* act);
 	sf::Packet* get_action();
};

