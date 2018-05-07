#ifndef SCAV_MENU_HPP_
#define SCAV_MENU_HPP_

#include "game_object.hpp"
#include <mutex>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <list>

class MenuElement {
	protected:
		int width;
		int height;
		int x;
		int y;
		RenderWindow* window;
	public:
		MenuElement(int w, int h, int dx, int dy, RenderWindow* wnd);
		int hover();
		int pressed();
		void setPos(int dx, int dy);
		virtual void draw()=0;
		virtual void hide()=0;
		virtual void redraw()=0;
		virtual void set_text(std::string str)=0;
		virtual std::string get_text()=0;
		virtual void set_color(int r, int g, int b)=0;
};

class Button: public MenuElement {
	private:
		sf::Text buttonText;
		sf::Font font;
		int fontSize;
	public:
		Button(int w, int h, int dx, int dy, std::string fontname, std::string text, int size, RenderWindow* wnd);
		void draw();
		void hide();
		int hover();
		int pressed();
		void redraw();
		void set_text(std::string str);
		std::string get_text();
		void set_color(int r, int g, int b);
};

class TextInput : public MenuElement {
	private:
		int bg;
		sf::Text text;
		std::string defaultValue;
		sf::Font font;
		int fontSize;
	public:
		TextInput(int w, int h, int dx, int dy, std::string fontname, std::string txt, int size, RenderWindow* wnd, int dbg);
		void draw();
		void redraw();
		void hide();
		int hover();
		int pressed();
		void set_text(std::string str);
		std::string get_text();
		void set_color(int r, int g, int b);
};

class Menu {
	private:
		std::list<MenuElement*> elements;
		std::string background;
		sf::Sprite bg;
		std::string font;
		RenderWindow* window;
		std::string name;
		std::string ip;
		int port;
		int visible;
	public:
		Menu(RenderWindow* wnd, std::string bckg, std::string f);
		void add_element(MenuElement* el);
		void remove_button();
		void draw();
		void redraw_elements();
		std::string get_input_value(std::list<MenuElement*>::iterator ptr);
		std::string get_name();
		std::string get_ip();
		int get_port();
		//void hide();

};



class Interface {
	private:
		int hp;
		int ammo;
		std::list<MenuElement*> elements;
		RenderWindow* window;
	public:
		Interface(RenderWindow* wnd);
		void add_element(MenuElement* el);
		void draw(float cx, float cy);
		void set_hp(int points);
		void set_ammo(int points);
		void dead_window();

};



/*
class Indicators : public MenuElement {
	private:
		int bg;
		sf::Text text;
		std::string defaultValue;
		sf::Font font;
		int fontSize;
	public:
		Indicators(int w, int h, int dx, int dy, std::string fontname, std::string txt, int size, RenderWindow* wnd, int dbg);
		void draw();
		void redraw();
		void hide();
		int hover();
		int pressed();
		void set_text(std::string str);
		std::string get_text();
};*/



#endif  // SCAV_MENU_HPP_
