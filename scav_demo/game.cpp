#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include <vector>


using namespace sf;
int main()
{

    RenderWindow window(sf::VideoMode(640, 480), "project");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(0);





    class Bullet {
    public:
        Bullet(float radius = 5.f)
            : currVelicity(0.f, 0.f), maxSpeed(25.f) {
                //this->shape.setRadius(radius);
                //this->shape.setFillColor(Color::Red);
            };
        Sprite shape;
        Vector2f currVelicity;
        float maxSpeed;
    };

    Texture cursor_texture;
    cursor_texture.loadFromFile("Cursor.png");
    Sprite cursor(cursor_texture);
    cursor.setScale(0.05, 0.05);
    cursor.setOrigin(cursor.getLocalBounds().width / 2, cursor.getLocalBounds().height / 2);


    Texture bullet_texture;
    bullet_texture.loadFromFile("Bullet.png");
    Sprite bullet_sprite(bullet_texture);
    bullet_sprite.setScale(5, 5);

    Image heroimage;
    heroimage.loadFromFile("map.png");

    Texture herotexture;
    herotexture.loadFromImage(heroimage);

    Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setPosition(0, 0);


    Texture texture;
    texture.loadFromFile("Solder clone.png");

    Vector2f size(25.f, 25.f);
    //CircleShape player(25.f);
    Sprite player(texture);
    //player.setTexture(&herotexture)
    player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
    player.setScale(0.05, 0.05);


    View camera;

    //BUllet
    Bullet b1;
    std::vector<Bullet> bullets;

    //Vectors
    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;

    float timer = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

        //Update
        playerCenter = Vector2f(player.getPosition().x, player.getPosition().y);
        mousePosWindow = Vector2f(Mouse::getPosition(window));
        aimDir = mousePosWindow - playerCenter;
        aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
        float rotation = (atan2(aimDir.y, aimDir.x)) * 180 / 3.14159265 + 90;
        player.setRotation(rotation);

        //Player
        if(Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-10.f, 0.f);
        }
        if(Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(10.f, 0.f);
        }
        if(Keyboard::isKeyPressed(Keyboard::W)) {
            player.move(0.f, -10.f);
        }
        if(Keyboard::isKeyPressed(Keyboard::S)) {
            player.move(0.f, 10.f);
        }

        Clock clock;
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        std::cout << time << std::endl;

        timer += time;

        //Shooting
        if (Mouse::isButtonPressed(Mouse::Left)) {
            b1.shape.setPosition(playerCenter);
            b1.shape.setTexture(bullet_texture);
            b1.shape.setScale(0.05, 0.05);
            b1.shape.setOrigin(b1.shape.getLocalBounds().width / 2, b1.shape.getLocalBounds().height / 2);
            b1.shape.setRotation(player.getRotation());

            b1.currVelicity = aimDirNorm * b1.maxSpeed;

            bullets.push_back(Bullet(b1));
        }
        for (size_t i = 0; i < bullets.size(); i++) {

            bullets[i].shape.move(bullets[i].currVelicity);

            if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
            || bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y) {
                bullets.erase(bullets.begin() + i);
            }
        }

        cursor.setPosition(mousePosWindow);

        camera.setCenter(playerCenter);




        //Draw
		window.clear();
        window.draw(herosprite);
		window.draw(player);
        window.draw(cursor);
        //window.setView(camera);

        for (size_t i = 0; i < bullets.size(); i++) {
            window.draw(bullets[i].shape);
        }
        window.draw(b1.shape);

		window.display();
	}

	return 0;
}
