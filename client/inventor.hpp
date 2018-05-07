#ifndef SCAV_INVENTOR_HPP_
#define SCAV_INVENTOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <list>

class Weapon {
	private:
		int ammo;
		int maxAmmo;
		Texture txt;
		int speed;
		int damage;
		Sprite pic;
		int id;
	public:
		Weapon(int max, int s, int d, std::string filename, int did);
		void set_ammo(int a);
		int get_ammo();
		int get_speed();
		Sprite* getSprite();
		~Weapon();
};

class Inventor {
		int current;
	public:
		Weapon* inv[5]={NULL,NULL,NULL,NULL,NULL};
		RenderWindow* window;
		Inventor(RenderWindow* wnd);
		void draw(float cx, float cy);
		Weapon* get_current();
		void check_key();
		void set_current(int id);
		void put(Weapon* weapon);
		void remove(int id);
};

#endif  // SCAV_INVENTOR_HPP_