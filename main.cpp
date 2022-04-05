#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;
struct Player {
    Texture PlayerTex;
    Sprite PlayerSprite;
    Vector2f Velocity;
    int sonic_adminator = 0, Idle_adminator = 0, delay = 0, idle_delay = 0;
    float velocity_jump = 0;
    bool on_ground = true;
    bool start = false;
    bool Running = false;
    bool idle1 = false;
};
int main()
{
    RenderWindow window(VideoMode(1600, 900), "Sonic");
    window.setFramerateLimit(60);
    Player sonic;
    sonic.PlayerTex.loadFromFile("Sonic-Character.png");
    sonic.PlayerSprite.setTexture(sonic.PlayerTex);
    sonic.PlayerSprite.setTextureRect(IntRect(sonic.Idle_adminator * 59.1578, 0 * 60, 59.1578, 60));
    sonic.PlayerSprite.setPosition(200, 700);
    sonic.PlayerSprite.setScale(2, 2);
    RectangleShape ground(Vector2f(5000, 70)); ground.setScale(1, 1); ground.setPosition(0, 800);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (sonic.delay <= 3) sonic.delay++; //Sonic movement 
        if (sonic.idle_delay <= 10) sonic.idle_delay++;

        if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S)) {
            if (sonic.idle_delay >= 10) {
                sonic.idle_delay = 0;
                if (sonic.Idle_adminator == 7) sonic.idle1 = true;
                else if(sonic.Idle_adminator == 0) sonic.idle1 = false;
                if (sonic.idle1) sonic.Idle_adminator--;
                else sonic.Idle_adminator++;
                sonic.PlayerSprite.setTextureRect(IntRect(sonic.Idle_adminator * 48.75, 0 * 60, 48.75, 51));
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            sonic.PlayerSprite.move(-7, 0);
            if (sonic.delay >= 3) {
                sonic.sonic_adminator++;
                sonic.delay = 0;
                sonic.sonic_adminator = sonic.sonic_adminator % 11;
                sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 48.86, 3 * 60, 48.86, 51));
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            sonic.PlayerSprite.move(7, 0);
            if (sonic.delay >= 3) {
                sonic.sonic_adminator++;
                sonic.delay = 0;
                sonic.sonic_adminator = sonic.sonic_adminator % 11;
                sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 48.86, 1 * 60, 48.86, 51));
            }
        }
        if (sonic.PlayerSprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            sonic.on_ground = true;
            sonic.velocity_jump = 0;
            if (Keyboard::isKeyPressed(Keyboard::Key::Space)) sonic.velocity_jump = 10;
        }
        else {
            sonic.on_ground = false;
            sonic.velocity_jump -= 0.3;
        }
        if (!sonic.on_ground){
            sonic.sonic_adminator++;
            sonic.sonic_adminator = sonic.sonic_adminator % 16;
            sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 49, 2 * 60, 49, 51));
        }
        sonic.PlayerSprite.move(0, -sonic.velocity_jump);


        
        window.clear();
        window.draw(sonic.PlayerSprite);
        window.draw(ground);
        window.display();
    }

    return 0;
}
