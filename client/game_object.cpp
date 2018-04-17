#include 'game_object.hpp'


GameObject::GameObject(int _id): id(_id);

int GameObject::get_id() {
    return id;
}



const Vector2f& DrawableObject::get_pos() const {
    return pos;
}

void Player::set_rotation(DrawableObject* cursor, GameField* window) {
    playerCenter = Vector2f(player->skin.getPosition().x, player->skin.getPosition().y);
    Vector2f prevPosition = Vector2f(Mouse::getPosition(*window));
    aimDir = mousePosWindow - playerCenter;//privet
    aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
    float rotation = (atan2(aimDir.y, aimDir.x)) * 180 / 3.14159265 + 90;
}

Player::Player() {
    rotation = 0;
    pos = 0;
    id = 1;
    Texture playertexture.loadFromFile("Solder clone.png");
    skin.setTexture(playertexture);
}

void draw(RenderWindow* draw) {
    skin
    window.draw(skin)
}
