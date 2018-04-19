#include "action.hpp"
#include "game_object.hpp"
#include <SFML/Network.hpp>
#include <iostream>

void ActionConstructor::execute_action(GameField* field, sf::Packet& packet) {
	static int cl_id = 0;
	int id = 0;
	int obj_id = 0;

	packet >> id;
	packet >> obj_id;

	switch (id) {
		case 1: {
			float x = 0;
			float y = 0;
			float angle = 0;

			packet >> x >> y >> angle;
			DrawableObject* obj = field->find(obj_id);
			if (obj!=nullptr)
			if (obj != field->get_player()) {
				Vector2f pos(x, y);
				obj->set_pos(pos);
				Player *p = dynamic_cast<Player*>(obj);
				if (p) {
					p->set_position();
				}
				obj->set_rotation(angle);
			}
			return;
		}
		case 100: {
			int _cl_id = 0;
			packet >> _cl_id;
			Player* p = new Player(obj_id);
			Texture* playertexture = new Texture();
			playertexture->loadFromFile("Solder clone.png");
			p->set_player_sprite(playertexture);
			field->add(p, obj_id);

			if (_cl_id == cl_id) {
				field->set_player(obj_id);
			}
			return;
		}
		case 101: {
			cl_id = obj_id;
			std::cout << obj_id << std::endl;
		}
	}
}
