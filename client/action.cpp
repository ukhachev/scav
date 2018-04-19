#include "action.hpp"



Action::Action(int obj): obj_id(obj) {}
Action::~Action() {}

void Action::execute(GameObject* obj) {}


int Action::get_object_id() {
    return obj_id;
}



MoveAction::MoveAction(int _id, float x, float y): Action(_id), pos(Vector2f(x, y)) {}

void MoveAction::execute(DrawableObject* obj) {
    Vector2f prev_position = obj->get_pos();
    obj->set_pos(pos + prev_position);
}
