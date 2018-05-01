#ifndef PHYSICS_ACTION_HPP
#define PHYSICS_ACTION_HPP

#include "Box2D/Box2D.h"
#include "physics_object.hpp"
#include "gamefield.hpp"

class PhysicsAction {
 public:
    PhysicsAction();
    virtual ~PhysicsAction();
    virtual void execute(GameField& field) = 0;
};

class HitPhysicsAction : public PhysicsAction {
 private:
    DrawableBullet* bullet;
    PhysicsObject* object;
 public:
    HitPhysicsAction(DrawableBullet* b, PhysicsObject* o);
    ~HitPhysicsAction();
    void execute(GameField& field);
};

#endif