#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include "Box2D/Box2D.h"
#include "gamefield.hpp"
#include "physics_action.hpp"
#include <list>

class ContactListener: public b2ContactListener {
    std::list<PhysicsAction*> actions;
  	void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
 public:
    void execute_actions(GameField& field);
};



#endif