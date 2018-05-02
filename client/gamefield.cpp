
//#include "view.hpp"
#include "gamefield.hpp"
#include <iostream>


GameField::GameField(): world(new b2World(b2Vec2(0, 0))), t_cont("textures.txt"), g_map(5, 5, t_cont.get_texture(4)) {
    player = nullptr;
    window.create(sf::VideoMode(640, 480), "project");
    window.setFramerateLimit(60);
    StaticObject* left = new StaticObject(world, b2Vec2(10, 1000), b2Vec2(-500, 0));
    StaticObject* right = new StaticObject(world, b2Vec2(10, 1000), b2Vec2(500, 0));
    StaticObject* top = new StaticObject(world, b2Vec2(1000, 10), b2Vec2(0, 500));
    StaticObject* bot = new StaticObject(world, b2Vec2(1000, 10), b2Vec2(0, -500));
    (void)left;
    (void)top;
    (void)bot;
    (void)right;
    //window.setMouseCursorVisible(0);
}
b2World* GameField::get_physics_world() {
    return world;
}

Player* GameField::find_player(int obj_id) {

    auto iter = players.find(obj_id);
    if (iter != players.end()) {
        return iter->second;
    }

    return nullptr;

}


bool GameField::get_action(sf::Packet& packet) {

    if (player != nullptr) {
        packet << 1 << player->get_pos().x <<player->get_pos().y << player->get_rotation();
        if (was_shot) {
            packet << 14 << player->get_pos().x <<player->get_pos().y << player->get_rotation();
            was_shot = false;
        }
        return true;
    }
    return false;
}

void GameField::shoot() {
	if (last_shot > 5) {
	    was_shot = true;
	    last_shot = 0;
	}
}

bool GameField::render() {
    //Textures t_cont("textures.txt");
    //Texture* t = t_cont.get_texture(4);
   // MapConst g_map(20, 20, t_cont);
    if (window.isOpen())
    {
    	if (last_shot < 100000) {
    		last_shot++;
    	}
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }
     window.clear();
        if (player != nullptr) {
            b2Vec2 speed(0, 0);

	        if(Keyboard::isKeyPressed(Keyboard::A)) {
	            speed += b2Vec2(-200.f, 0.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::D)) {
	            speed += b2Vec2(200.f, 0.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::W)) {
	            speed += b2Vec2(0.f, -200.f);
	        }
	        if(Keyboard::isKeyPressed(Keyboard::S)) {
	            speed += b2Vec2(0.f, 200.f);
	        }
	        player->set_speed(speed.x, speed.y);

            player->mouse_rotation(window);
            g_cam.set_center(player);
            if (Mouse::isButtonPressed(Mouse::Left)) {
            	shoot();
        	}
            g_map.draw(window, player->get_pos().x, player->get_pos().y);

        }

       
        g_cam.draw(window);
        

        for (auto iter = players.begin(); iter != players.end(); iter++) {
            iter->second->draw(window);
            //std::cout << iter->second->get_id() << std::endl;
        }
        for (auto iter = walls.begin(); iter != walls.end(); iter++) {
            iter->second->draw(window);
        }
        for (auto iter = bullets.begin(); iter != bullets.end(); iter++) {
            (*iter)->draw(window);
        }
        //g_map.draw(window);
        window.display();
    }
    else {
    	return false;
    }
    return true;
    //delete player;
}


std::mutex& GameField::get_mutex() {
	return mtx;
}
int GameField::add_player(Player* obj, int new_id) {

    players.emplace(new_id, obj);
    return 0;
}

int GameField::add_wall(Wall* obj, int new_id) {

    walls.emplace(new_id, obj);
    return 0;
}

int GameField::add_bullet(DrawableBullet* obj) {

    bullets.push_front(obj);

    return 0;
}

void GameField::set_player(int player_id) {
    player = find_player(player_id);
}

Player* GameField::get_player() {
    return player;
}

void GameField::delete_bullet(DrawableBullet* b) {
	for (auto i = bullets.begin(); i != bullets.end(); ++i) {
		if (*i == b) {
			bullets.erase(i);
			delete b;
			return;
		}
	}
}

void GameField::delete_player(int cl_id) {
    auto p = players.find(cl_id);
    delete p->second;
    players.erase(p);
}

void GameField::delete_wall(int id) {
    auto w = walls.find(id);
    if (w == walls.end()) {
        return;
    }
    delete w->second;
    walls.erase(w);
}

Wall* GameField::get_wall(int id) {
    auto iter = walls.find(id);
    if (iter != walls.end()) {
        return iter->second;
    }

    return nullptr;
}