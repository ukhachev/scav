#include "action.hpp"
#include "game_object.hpp"
#include "inventor.hpp"
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

	mtx.lock();
	switch (id) {
		case 1: { //Движение
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
		case 2: { //Создание объекта
			float x =0;
			float y = 0;
			int obj_type = 0;
			int texture_id = 0;

			packet >> obj_type >> x >> y >> texture_id;

			switch (obj_type) {
				case 2: {
					Wall* w = new Wall(obj_id, field->get_physics_world(), b2Vec2(20, 20), b2Vec2(x, y));
					w->set_sprite(textures->get_texture(2));
					w->set_damage_sprite(textures->get_texture(7));
					field->add_object(w, obj_id);
					std::cout << "wall " << obj_id << std::endl;
					break;
				}
				case 3: {
					AidKit* a = new AidKit(obj_id);
					a->set_sprite(textures->get_texture(texture_id));
					//Криво
					if (texture_id == 10)
                    	a->set_dead_sprite(textures->get_texture(12));
                    if (texture_id == 9) {
                    	a->set_dead_sprite(textures->get_texture(15));
                    }
                    //------
					a->set_pos(Vector2f(x, y));
					field->add_object(a, obj_id);
					std::cout << "entity " << obj_id << std::endl;
					break;
				}
			}
			break;
		}
		case 3: {  //Боезапас
			int ammo = 0;
			packet >> ammo;
			Player* p = field->find_player(obj_id);
			if (p!= nullptr) {
				p->set_ammo(ammo);
			}
			break;
		}
		case 5: { //Хп
			PhysicsObject* obj = nullptr;
			int hp = 0;
			packet >> hp;
			if (obj_id >= 200) {
				obj = field->get_object(obj_id);
			}
			else {
				obj = field->find_player(obj_id);
			}
			if (obj != nullptr) {
				obj->set_hp(hp);

			}
			break;
		}  
		case 6: { //Подбор оружия
			int wtype = 0;
			Inventor* inv = field->get_inventor();
			
			packet >> wtype;
			if (obj_id == cl_id) {
				Weapon* w = inv->find(wtype);
				if (w==nullptr) {
					w = WeaponCreator::create(wtype, textures);
					inv->put(w);
				} else {
					w->set_ammo(150);
				}
			}
			break;
		}

		case 14: {//Пули
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
		case 100: { //Создать игрока
			std::cout << "player "<<obj_id << std::endl;

			Player* p = new Player(obj_id, field->get_physics_world(), b2Vec2(20, 20), b2Vec2(0, 0));

			p->set_player_sprite(textures->get_texture(1));
			p->set_damage_sprite(textures->get_texture(6));
			p->set_dead_sprite(textures->get_texture(8));
			field->add_player(p, obj_id);

			if (obj_id == cl_id) {
				field->set_player(obj_id);
			}
			break;
		}
		case 101: { //Привязать игрока
			cl_id = obj_id;
			break;
		}
		case 102: { //Удалить игрока
			field->delete_player(obj_id);
			break;
		}
		case 103: { //Удалить объект
			field->delete_object(obj_id);
			break;
		}
		case 104: {
			std::cout << "reset game" << std::endl;
			field->delete_all();
		}

	}
	mtx.unlock();
}
