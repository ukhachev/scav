#ifndef SCAV_SERVER_GAME_OBJECT_HPP_
#define SCAV_SERVER_GAME_OBJECT_HPP_

#include "Box2D/Box2D.h"
#include <SFML/System.hpp>
#include "physics_object.hpp"

class Player : public StaticObject {
 public:
 	Player(int _id, b2World* _world, const b2Vec2& size,const b2Vec2& pos);
 	~Player();
};

#endif