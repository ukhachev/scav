#include <Box2D/Box2D.h>

class GameObject {
 protected:
 	int id;
 public:
 	GameObject(int _id);
 	void delete_event(sf::packet& packet);
}

class PhysicsObject {
 protected:
 	Body box;
 public:
 	Body& get_body();
 	void set_speed(float s_val)
}