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
		int speed;
		int damage;
		Sprite pic;
		int id;
	public:
		Weapon(int max, int s, int d, Texture* txt, int did);
		void set_ammo(int a);
		int get_ammo();
		int get_speed();
		int get_id();
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
		Weapon* find(int id);
		void check_key();
		void set_current(int id);
		void put(Weapon* weapon);
		void remove(int id);
};

class WeaponCreator
{
public:
	static Weapon* create(int id, Textures* t_cont);	
};
#endif  // SCAV_INVENTOR_HPP_