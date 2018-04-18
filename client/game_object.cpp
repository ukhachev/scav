#include 'game_object.hpp'


GameObject::GameObject(int _id): id(_id);

int GameObject::get_id() {
    return id;
}



const Vector2f& DrawableObject::get_pos() const {
    return pos;
}

void Player::set_rotation(/*DrawableObject* cursor,*/ GameField* window) {
    Vector2f playerCenter = skin->get_pos();
    Vector2f prevPosition = Vector2f(Mouse::getPosition(*window));
    Vector2f aimDir = mousePosWindow - playerCenter;//privet
    Vector2f aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
    float rotation = (atan2(aimDir.y, aimDir.x)) * 180 / 3.14159265 + 90;
}

Player::Player() {
    pos = 0;
    id = 1;
}

void Player::set_player_sprite(Texture player_texture) {
    skin = new Sprite(player_texture);
    skin->setOrigin(skin->getLocalBounds().width / 2, skin->getLocalBounds().height / 2);
    skin->setScale(0.05, 0.05);
}

void Player::draw(RenderWindow* draw) {
    window.draw(skin);
}

GameMap::GameMap(Texture map_texture) {
    map_sprite = new Sprite(map_texture);

}
