#include "gamefield.hpp"
#include "menu.hpp"
#include <iostream>
#include <SFML/Audio.hpp>

MenuElement::MenuElement(int w, int h, int dx, int dy, RenderWindow* wnd) {
    width=w;
    height=h;
    x=dx;
    y=dy;
    window=wnd;
}

int MenuElement::hover() {
    if (IntRect(x, y, width, height).contains(Mouse::getPosition(*window))) {
        return 1;
    }
    return 0;
}

int MenuElement::pressed() {
    if(Mouse::isButtonPressed(Mouse::Left) && hover()) {
        return 1;
    }
    return 0;
}

void MenuElement::setPos(int dx, int dy) {
    x=dx;
    y=dy;
    redraw();
}


Button::Button(int w, int h, int dx, int dy, std::string fontname, std::string text, int size, RenderWindow* wnd):MenuElement(w,h,dx,dy,wnd) {
    font.loadFromFile(fontname);
    buttonText=Text(text, font, size);
    buttonText.setColor(Color::White);
    buttonText.setStyle(sf::Text::Bold);
}

int Button::hover() {
    if(MenuElement::hover()) {
        return 1;
    }
    return 0;
}

int Button::pressed() {
    if(MenuElement::pressed()) {
        return 1;
    }
    return 0;
}

void Button::draw() {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color(128,128,128));
    window->draw(rectangle);
    buttonText.setColor(sf::Color::White);
    buttonText.setPosition(x+10, y);
    window->draw(buttonText);
}

void Button::redraw() {
    buttonText.setPosition(x,y);
}


void Button::hide() {
    buttonText.setString("");
}
void Button::set_text(std::string str) {
    buttonText.setString(str);
}

std::string Button::get_text() {
    return buttonText.getString();
}

void Button::set_color(int r, int g, int b) {
    buttonText.setColor(sf::Color(r,g,b));
}

TextInput::TextInput(int w, int h, int dx, int dy, std::string fontname, std::string txt, int size, RenderWindow* wnd, int dbg):MenuElement(w,h,dx,dy,wnd) {
    font.loadFromFile(fontname);
    text=Text(txt, font, size);
    text.setColor(Color(57,57,57));
    text.setStyle(sf::Text::Regular);
    bg=dbg;
}

void TextInput::draw() {
    if(bg) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition(x, y);
        text.setColor(Color(179,179,179));
        rectangle.setFillColor(sf::Color(60,60,60));
        window->draw(rectangle);
    }
    text.setPosition(x+5, y+2);
    window->draw(text);
}

void TextInput::redraw() {
    text.setPosition(x,y);
}


void TextInput::hide() {
    text.setString("");
}

int TextInput::hover() {
    if(MenuElement::hover()) {
        return 1;
    }
    return 0;
}

int TextInput::pressed() {
    if(MenuElement::pressed()) {
        return 1;
    }
    return 0;
}

void TextInput::set_text(std::string str) {
    text.setString(str);
}

std::string TextInput::get_text() {
    return text.getString();
}

void TextInput::set_color(int r, int g, int b) {
    text.setColor(sf::Color(r,g,b));
}


Menu::Menu(RenderWindow* wnd, std::string bckg, std::string f) {
    window=wnd;
    background=bckg;
    font=f;
    visible=0;
    add_element(new TextInput(200,30,180,10, font, "Name:", 25, window,0));
    add_element(new TextInput(200,30,255,10, font, "Your nickname", 20, window,1));
    add_element(new TextInput(200,30,180,50, font, "IP:", 25, window,0));
    add_element(new TextInput(200,30,255,50, font, "ip address", 20, window,1));
    add_element(new TextInput(200,30,180,90, font, "Port:", 25, window,0));
    add_element(new TextInput(200,30,255,90, font, "port number", 20, window,1));
    add_element(new Button(100,30,270,140, font, "ENTER", 25, window));
    
}

void Menu::add_element(MenuElement* el) {
    elements.push_back(el);
}

void Menu::redraw_elements() {
    window->draw(bg);
    for(std::list<MenuElement*>::iterator ptr = elements.begin(); ptr != elements.end(); ptr++) {
            (*ptr)->draw();
        }
}
std::string Menu::get_input_value(std::list<MenuElement*>::iterator ptr) {
                        int isInput=1;
                        std::string s;
                        while(isInput) {
                            window->clear();
                            sf::Event event;
                            while (window->pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    window->close();
                            }
                            if(s.size() == 0) {
                                (*ptr)->set_text("");
                            }
                            if(event.type==sf::Event::TextEntered) {
                                if(Keyboard::isKeyPressed(Keyboard::BackSpace) && s.size() != 0) {
                                    s.pop_back();
                                    (*ptr)->set_text(s);
                                }
                                else if(Keyboard::isKeyPressed(Keyboard::Return) && s.size() != 0) {
                                    std::string ip_addr=(*ptr)->get_text();
                                    //std::cout<<"returned ip: "<<ip_addr<<std::endl;
                                    return s;
                                    isInput=0;
                                }
                                else if (event.text.unicode <128) {
                                    s.push_back((char)event.text.unicode);
                                    (*ptr)->set_text(s);

                                }
                            }
                            redraw_elements();
                            window->display();
                        }
}
void Menu::draw() {
    window->clear();
    sf::Texture bgtxt;
    bgtxt.loadFromFile(background);
    bg=Sprite(bgtxt);
    bg.setPosition(1,1);
    int isMenu = 1;
    sf::Event event;
    while(isMenu && window->isOpen()) {
        int menuAction=0;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window->close();
        }
        window->draw(bg);
        for(std::list<MenuElement*>::iterator ptr = elements.begin(); ptr != elements.end(); ptr++) {
            menuAction++;
            (*ptr)->draw();
            if((*ptr)->pressed()) {
                switch(menuAction) {
                    case 2 : {
                        std::string sname=get_input_value(ptr);
                        name=sname;
                        break;
                    }
                    case 4 : {
                        std::string sip=get_input_value(ptr);
                        ip=sip;
                        break;
                    }
                    case 6 : {
                        std::string sport=get_input_value(ptr);
                        port=std::stoi(sport);;
                        break;
                    }
                    case 7: {
                        isMenu=0;
                        //sound.stop();
                        break;
                    }
                    default : 
                        break;
                }            
            }

        }
        window->display();
        if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                printf("close menu\n");
                isMenu=0;
                window->clear();
        }
    }
}

std::string Menu::get_name() {
    return name;
}

std::string Menu::get_ip() {
    return ip;
}

int Menu::get_port() {
    return port;
}


Interface::Interface(RenderWindow* wnd) {
    window=wnd;
    hp=100;
    ammo=100;
    add_element(new TextInput(200,30,1,1, "minecraft.otf",std::string("HP:") +std::to_string(hp), 50, window,0));
    elements.front()->set_color(51,255,0);
    add_element(new TextInput(200,30,1,100, "minecraft.otf",std::string("AM:") +std::to_string(ammo), 50, window,0));
    elements.back()->set_color(255,255,255);

}

void Interface::add_element(MenuElement* el) {
    elements.push_back(el);
}

void Interface::draw(float cx, float cy) {
    int i = 0;
    for(std::list<MenuElement*>::iterator ptr = elements.begin(); ptr != elements.end(); ptr++) {
            ++i;
            (*ptr)->setPos(cx - 450, cy + i*75 - 450);
            (*ptr)->draw();
        }
}

void Interface::set_hp(int points) {
    hp=points;
    elements.front()->set_text(std::string("HP:")+std::to_string(hp));
    if(hp<80 && hp>40) {
        elements.front()->set_color(255,222,0);
    }
    else if(hp<40 && hp>0) {
        elements.front()->set_color(255,0,0);
    }
    /*else if(hp<1) {
        dead_window();
    }*/
    else {
        elements.front()->set_color(51,255,0);
    }
}

void Interface::set_ammo(int points) {
    ammo=points;
    elements.back()->set_text(std::string("AM:")+std::to_string(ammo));
    //sf::SoundBuffer buffer;
    //buffer.loadFromFile("gun.wav");
    //sf::Sound sound;
    //sound.setBuffer(buffer);
   // sound.setVolume(80);
    //sound.play();
}


void Interface::dead_window()  { //Не нужно пока
    Texture backtxt;
    backtxt.loadFromFile("dead_back.jpg");
    Sprite back(backtxt);
    int stillDead=1;
    while (window->isOpen() && stillDead)
    {
        window->clear();
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window->close();
        }    
        back.setPosition(2,2);
        window->draw(back);
        if(Keyboard::isKeyPressed(Keyboard::Return)) {
            stillDead=0;
            hp=100;
            ammo=100;
        }
        window->display();

    }
}


void Interface::drawLine(RenderWindow* window,std::string str, float x, float y) {
    sf::Font font;
    font.loadFromFile("minecraft.otf");
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(38);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(x,y);
    window->draw(text);
}