#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;

/// plyer struct

struct Player {
    Texture PlayerTex;
    Sprite PlayerSprite;
    Vector2f Velocity;
    int sonic_adminator = 0, Idle_adminator = 0, delay = 0, idle_delay = 0, left_adminator = 22;
    bool on_ground = true;
    bool start = false;
    bool Running = false;
    bool idle1 = false;
    bool txToggle = false;
} sonic;

struct Jumppad{
    Texture JumppadTX;
    Sprite JumppadSprite;
    int Texnumber = 6, TexCnt = 0, delay = 0;
    bool TexLeft = false, jumped = false;
} jumppad[5];

// main function

int main()
{
    // rendering window
    RenderWindow window(VideoMode(1200, 760), "Sonic!");
    window.setFramerateLimit(60);

    /// map
       // map texture
    Texture MapTx;
    MapTx.loadFromFile("Assets/Textures/Map.png");
    // map player
    Sprite Map;
    Map.setTexture(MapTx);
    //

   //// sonic player
       // sonic texture
    sonic.PlayerTex.loadFromFile("Assets/Textures/Sonic-Character.png");
    sonic.PlayerSprite.setTexture(sonic.PlayerTex);
    // sonic sprite
    sonic.PlayerSprite.setTextureRect(IntRect(sonic.Idle_adminator * 59.1578, 0 * 60, 59.1578, 60));
    sonic.PlayerSprite.setPosition(200, 330);
    sonic.PlayerSprite.setScale(2.5, 2.5);
    //

    for (int i = 0; i < 5; i++) {
        jumppad[i].JumppadTX.loadFromFile("Assets/Textures/Some Sprites.png");
        jumppad[i].JumppadSprite.setTexture(jumppad[i].JumppadTX);
        jumppad[i].JumppadSprite.setTextureRect(IntRect(jumppad[i].Texnumber * 80, 543, 80, 66));

    }
   

    jumppad[0].JumppadSprite.setPosition(400, 600);

    /// ground rectangle shape
    RectangleShape ground(Vector2f(17000, 70)); ground.setScale(1, 1); ground.setPosition(0, 660);
    //

    // view camera
    View camera(FloatRect(0, 0, 1200, 760));
    window.setView(camera);
    //

    /// game loop

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        /// UPDATE

        //Sonic movement

        if (sonic.delay <= 3) sonic.delay++;
        if (sonic.idle_delay <= 10) sonic.idle_delay++;

        if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S)) {
            sonic.Running = false;
            sonic.txToggle = false;
            if (sonic.idle_delay >= 10) {
                sonic.idle_delay = 0;
                if (sonic.Idle_adminator == 7) sonic.idle1 = true;
                else if (sonic.Idle_adminator == 0) sonic.idle1 = false;
                if (sonic.idle1) sonic.Idle_adminator--;
                else sonic.Idle_adminator++;
                if (!sonic.Running) sonic.PlayerSprite.setTextureRect(IntRect(sonic.Idle_adminator * 48.75, 0 * 60, 48.75, 51));
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            std::cout << Mouse::getPosition().x << ' ' << Mouse::getPosition().y << '\n';
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                sonic.PlayerSprite.move(15, 0);
                camera.move(15, 0);
                if (sonic.delay >= 3) {
                    sonic.sonic_adminator++;
                    sonic.delay = 0;
                    if (sonic.Running) if (sonic.sonic_adminator >= 22) sonic.sonic_adminator = 19;
                    else sonic.sonic_adminator = (sonic.sonic_adminator % 12) + 12;
                    if (sonic.sonic_adminator >= 17) sonic.Running = true;
                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 48.86, 1 * 60, 48.86, 51));
                }
            }
            else {
                sonic.PlayerSprite.move(12, 0);
                camera.move(12, 0);
                if (sonic.delay >= 3) {
                    sonic.sonic_adminator++;
                    sonic.delay = 0;
                    if (sonic.txToggle) sonic.sonic_adminator = (sonic.sonic_adminator % 5) + 5;
                    else sonic.sonic_adminator %= 11;
                    if (sonic.sonic_adminator == 6) sonic.txToggle = true;
                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 48.86, 1 * 60, 48.86, 51));
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::A) ) {
            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                sonic.PlayerSprite.move(-15, 0);
                camera.move(-15, 0);
                if (sonic.delay >= 3) {
                    sonic.left_adminator--;
                    sonic.delay = 0;
                    if (sonic.Running) if (sonic.left_adminator <= 0) sonic.left_adminator = 3;
                    else if (sonic.left_adminator <= 0) sonic.left_adminator = 12;
                    if (sonic.left_adminator <= 6) sonic.Running = true;
                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.left_adminator * 48.86, 3 * 60, 48.86, 51));
                }
            }
            else {
                sonic.PlayerSprite.move(-12, 0);
                camera.move(-12, 0);
                if (sonic.delay >= 3) {
                    sonic.left_adminator--;
                    sonic.delay = 0;
                    if (sonic.txToggle) if (sonic.left_adminator <= 13) sonic.left_adminator = 17;
                    else if (sonic.left_adminator <= 13) sonic.left_adminator = 22;
                    if (sonic.left_adminator <= 17) sonic.txToggle = true;
                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.left_adminator * 48.86, 3 * 60, 48.86, 51));
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            if(jumppad[i].delay <= 2) jumppad[i].delay++;
            if (sonic.PlayerSprite.getGlobalBounds().intersects(jumppad[i].JumppadSprite.getGlobalBounds()) && !sonic.on_ground) {
                sonic.Velocity.y = 15;
                jumppad[i].jumped = true;
            }
            if (jumppad[i].jumped) {
                if (jumppad[i].delay >= 2) {
                    jumppad[i].delay = 0;
                    if (jumppad[i].TexLeft) jumppad[i].Texnumber++;
                    else jumppad[i].Texnumber--;
                    if (jumppad[i].Texnumber >= 6) jumppad[i].jumped = false;
                    else if (jumppad[i].Texnumber <= 0) jumppad[i].TexLeft = true;
                    jumppad[i].JumppadSprite.setTextureRect(IntRect(jumppad[i].Texnumber * 80, 543, 80, 66));
                }
            }
            else {
                jumppad[i].JumppadSprite.setTextureRect(IntRect(6 * 80, 543, 80, 66));
                jumppad[i].Texnumber = 6;
                jumppad[i].TexLeft = false;
            }
        }


        


        if (sonic.PlayerSprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            sonic.on_ground = true;
            sonic.Velocity.y = 0;
            if (Keyboard::isKeyPressed(Keyboard::Key::Space)) sonic.Velocity.y = 10;
        }
        else {
            sonic.on_ground = false;
            sonic.sonic_adminator++;
            sonic.sonic_adminator %= 16;
            sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 49, 2 * 60, 49, 46));
            sonic.Velocity.y -= 0.3;
        }
        sonic.PlayerSprite.move(0, -sonic.Velocity.y);
        window.setView(camera);


        // clear
        window.clear();

        //draw
        window.draw(Map);
        window.draw(jumppad[0].JumppadSprite);
        window.draw(sonic.PlayerSprite);
        window.display();
    }


    return 0;
}


