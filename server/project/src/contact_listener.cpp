#include "contact_listener.hpp"
#include "physics_object.hpp"
#include <iostream>
void ContactListener::BeginContact(b2Contact* contact) {
    //check if fixture A was a ball
    PhysicsObject* bodyUserData = static_cast<PhysicsObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Bullet* bullet = NULL;
    PhysicsObject* obj = NULL;
    std::cout << "contact" << std::endl;
    if (dynamic_cast<Bullet*>(bodyUserData)) {
        bullet = dynamic_cast<Bullet*>(bodyUserData);
    }
    else {
      obj = dynamic_cast<PhysicsObject*>(bodyUserData);
    }

    bodyUserData = static_cast<PhysicsObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (dynamic_cast<Bullet*>(bodyUserData)) {
        bullet = dynamic_cast<Bullet*>(bodyUserData);
    }
    else {
      obj = dynamic_cast<PhysicsObject*>(bodyUserData);
    }
    if (obj && bullet) {
        actions.push_front(new HitPhysicsAction(bullet, obj));
    }
  
}

void ContactListener::EndContact(b2Contact* contact) {
    (void) contact;
}
void ContactListener::execute_actions(GameField& field) {
    for (auto i = actions.begin(); i != actions.end(); ) {
        (*i)->execute(field);
        delete *i;
        i = actions.erase(i);
    }
}

