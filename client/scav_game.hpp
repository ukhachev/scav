#ifndef SCAV_GAME_HPP_
#define SCAV_GAME_HPP_

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <map>
#include <string>


class Connector {
private:
	sf::TcpSocket socket;
	std::string ip;
	int port;
public:
	Connector(const std::string& address, int prt);
	~Connector();
	Action* get();
	void send(packet& packet);
};

class GameObject {
 private:
	int id;
 public:
 	GameObject(int _id);
 	virtual ~GameObject();
 	int get_id();
};

class Action {
 protected:
	int obj_id;
public:
	Action(int obj);
	virtual ~Action();
	virtual void execute(GameObject* obj, GameField* field);
};


class GameField {
 private:
 	std::map<int, DrawableObject*> map;
 public:
 	void render();
 	void add(DrawableObject* obj);
 	void execute(Action* act);
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

class DrawableObject {
 private:
 	sf::Vector2f pos;
 public:
 	const Vector2f& get_pos() const;
 	virtual void draw();
};

#endif
