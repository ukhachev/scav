#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

class PhysicsObject {
 public:
 	PhysicsObject(b2World* _world);
 	virtual sf::Vector2f get_pos();
 	void set_pos(const sf::Vector2f& _pos);
}

class StaticObject: public PhysicsObject {

}

class KinematicObject: public PhysicsObject {
 public:
 	void set_speed(const sf::Vector2f& _speed);
 	sf::Vector2f get_speed();
}

/*class Bullet: public KinematicObject {

}
*/
#endif