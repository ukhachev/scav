#include <Box2D/Box2D.h>
#include <SFML/Network.hpp>

//Временно
struct Position {
	int x;
	int y;
	float angle;
};

class GameObject {
 protected:
	int id;
 public:
	GameObject(int _id);
};

class PhysicsObject {
 protected:
	b2Body body;

 public:
	b2Body& get_body();
	virtual void set_speed(float s_val);
};


class Player : PhysicsObject {
	Position pos;
 public:
	void set_rotation(float angle);
	void set_position(const Position& _pos);
	Position& get_position();
};

class ClientAction {
 protected:
	Player* player;
 public:
	int get_id();
	virtual void execute() = 0;
	Player* get_player();
};

class MoveAction : ClientAction {
 private:
	int direction;
 public:
	void execute();
};

class Network {
 private:
	sf::TcpListener listener;
	std::list<sf::TcpSocket*> clients;
 public:
	Network(int port);
	~Network();
	void send_packet(sf::packet& packet);
	get_actions();
};

class GameController {
 private:
	b2AABB world;
	std::map<int, PhysicsObject*> objects;
	std::map<int, Player*> players;
 public:
	GameController(sf::Vector2f world_size);
};