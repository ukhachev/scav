#include "action.hpp"
#include "game_object.hpp"

#include <SFML/Network.hpp>
#include <iostream>
#include <math.h>
#include <mutex>
void ActionConstructor::execute_action(GameField* field, sf::Packet& packet, Textures* textures) {
	static int cl_id = 0;
	int id = 0;
	int obj_id = 0;
	packet >> id;
	packet >> obj_id;
	std::mutex& mtx = field->get_mutex();
	if (id == 100) {
		std::cout << obj_id << std::endl;
	}
	mtx.lock();
	switch (id) {
		case 1: {
			float x = 0;
			float y = 0;
			float angle = 0;

			packet >> x >> y >> angle;
			Player* obj = field->find_player(obj_id);
			if (obj != nullptr)
			if (obj != field->get_player()) {
				Vector2f pos(x, y);
                obj->set_pos(pos);
				obj->set_rotation(angle);
			}
			break;
		}
		case 14: {
			float x = 0;
			float y = 0;
			float angle = 0;
			packet >> x >> y >> angle;
			b2World* world = field->get_physics_world();
			b2Vec2 start_point(x, y);
			b2Vec2 speed(700.0f * cos(angle) , 700.0f * sin(angle));
			
			DrawableBullet* b = new DrawableBullet(world, b2Vec2(4, 4), start_point, speed, 10);
			
			b->set_sprite(textures->get_texture(5));

			field->add_bullet(b);

			break;
		}
		case 100: {
			//int _cl_id = 0;
			//packet >> _cl_id;
			Player* p = new Player(obj_id, field->get_physics_world(), b2Vec2(20, 20), b2Vec2(0, 0));

			p->set_player_sprite(textures->get_texture(1));
			field->add_player(p, obj_id);

			if (obj_id == cl_id) {
				field->set_player(obj_id);
			}
			break;
		}
		case 101: {
			cl_id = obj_id;
		}
	}
	mtx.unlock();
}
