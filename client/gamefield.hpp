#include <game_object.hpp>
#include<iostream>
//map содержит id объектов и указатели на них
//добавление: id последнего + 1
//execute: act->execute(<полученный из мапы указатель по id в act->get_object_id()>)
class GameField {
 private:
    Player* player;
    RenderWindow* window;
 	std::map<int, DrawableObject*> map;
 public:
    GameField();
    void set_player(int player_id);
    bool get_action(sf::Packet& packet);
 	void render();
 	void add(DrawableObject* obj);
 	void execute(Action* act);
};
