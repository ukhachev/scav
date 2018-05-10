#include "gamefield.hpp"
#include "menu.hpp"
#include "inventor.hpp"
#include <iostream>

Weapon::Weapon(int max, int s, int d, Texture* txt, int did) {
	maxAmmo = max;
	ammo = max;
	speed = s;
	damage=d;
	pic = Sprite(*txt);
    pic.setScale(0.80,0.80);
    id = did;
}
int Weapon::get_id() {
	return id;
}

void Weapon::set_ammo(int a) {
	ammo = a;
}

Sprite* Weapon::getSprite() {
	return &pic;
}

Weapon::~Weapon() {

}


Inventor::Inventor(RenderWindow* wnd) {
	window=wnd;
	current=0;
}

void Inventor::draw(float cx, float cy) {
	for(int i=0; i<5; ++i) {
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(100, 100));
			if(i==current){
                rectangle.setOutlineColor(sf::Color(0,51,255));
            }
            else {
                rectangle.setOutlineColor(sf::Color::Black);
            }
			rectangle.setOutlineThickness(4);
			rectangle.setPosition(cx-260+120*i, cy+370);
			rectangle.setFillColor(sf::Color(60,60,60));
			window->draw(rectangle);
			if(inv[i] != NULL) {
                inv[i]->getSprite()->setPosition(cx-258+115*i, cy+360);
                window->draw(*(inv[i]->getSprite()));
            }
	}
}

Weapon* Inventor::get_current() {
	return inv[current];
}

void Inventor::set_current(int id) {
	current=id;
}

void Inventor::put(Weapon* weapon) {
	for(int i=0; i<5; ++i) {
		if(inv[i]==NULL) {
			inv[i]=weapon;
			break;
		}
	}
}

void Inventor::remove(int id) {
	for(int i = 0; i < 5; ++i) {
		if(inv[i]->get_id() == id) {
			delete inv[i];
			inv[i] = NULL;
			break;
		}
	}
}

void Inventor::check_key() {
    if(Keyboard::isKeyPressed(Keyboard::Num1)) {
                    set_current(0);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num2)) {
                    set_current(1);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num3)) {
                    set_current(2);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num4)) {
                    set_current(3);
    }
    if(Keyboard::isKeyPressed(Keyboard::Num5)) {
                    set_current(4);
    }

}

Weapon* Inventor::find(int id) {
	for(int i = 0; i < 5; ++i) {
		if (inv[i]) {
			if(inv[i]->get_id() == id) {
				return inv[i];
			}
		}
	}
	return nullptr;
}
int Weapon::get_ammo() {
    return ammo;
}

int Weapon::get_speed() {
    return speed;
}

void Inventor::clear() {
	for(int i = 0; i < 5; ++i) {
		if (inv[i]) {
			delete inv[i];
			inv[i] = NULL;
		}
	}
}
Weapon* WeaponCreator::create(int id, Textures* t_cont) {
	switch(id) {
		case 101: return new Weapon(150, 5, 15, t_cont->get_texture(101), 101);
		case 102: return new Weapon(150, 10, 15, t_cont->get_texture(102), 102);
		case 103: return new Weapon(150, 15, 15, t_cont->get_texture(103), 103);
		case 104: return new Weapon(150, 30, 15, t_cont->get_texture(104), 104);
		case 105: return new Weapon(150, 1000000, 15, t_cont->get_texture(105), 105);
	}
}
