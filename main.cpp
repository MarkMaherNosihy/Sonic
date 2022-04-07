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
    int sonic_adminator = 0, Idle_adminator = 0, delay = 0, idle_delay = 0, left_adminator = 22, lives = 3;
    bool on_ground = true;
    bool start = false;
    bool Running = false;
    bool idle1 = false;
    bool txToggle = false;
    bool onWall = false;
} sonic;

struct Jumppad{
    Texture JumppadTX;
    Sprite JumppadSprite;
    int Texnumber = 6, TexCnt = 0, delay = 0;
    bool TexLeft = false, jumped = false;
} jumppad[5];

struct FloatingTiles {
    Texture TileTx;
    Sprite TileSprite;
    RectangleShape TileColl;
} tiles[30];

struct Coin {
    Texture CoinTx;
    Sprite CoinSprite;
    int TexNumber = 0, TexDelay = 0;
} coins[100];

struct Enemies {
    Texture EnemyTx;
    Sprite EnenmySprite;
    int TexNumber = 0, TexDelay = 0, xStart, xEnd, DamageDelay = 0;
    bool MovingRight = true;
    bool Hit = false;
} enemies[10];

// main function

void setTilePos(FloatingTiles& tile, int x, int y) {
    tile.TileSprite.setPosition(x, y);
    tile.TileColl.setPosition(x + 15, y);
}

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
    sonic.PlayerSprite.setPosition(200, 300);
    sonic.PlayerSprite.setScale(2.5, 2.5);
    //

    ///Jumppad Setting Texture
    for (int i = 0; i < 5; i++) {
        jumppad[i].JumppadTX.loadFromFile("Assets/Textures/Some Sprites.png");
        jumppad[i].JumppadSprite.setTexture(jumppad[i].JumppadTX);
        jumppad[i].JumppadSprite.setTextureRect(IntRect(jumppad[i].Texnumber * 80, 543, 80, 66));
    }
    //Jumppad Position
    jumppad[0].JumppadSprite.setPosition(3000, 590);
    //

    ///Floating Tiles Setting Texture
    for (int i = 0; i < 30; i++) {
        tiles[i].TileTx.loadFromFile("Assets/Textures/Wall2.png");
        tiles[i].TileSprite.setTexture(tiles[i].TileTx);
        tiles[i].TileSprite.setScale(1.3, 1.3);
        tiles[i].TileColl.setSize(Vector2f(298.9f, 1.f));
    }
    setTilePos(tiles[0], 3400, 300);
    setTilePos(tiles[1], 4200, 200);
    setTilePos(tiles[2], 5000, 250);
    //

    /// Coins Setting Texture
    for (int i = 0; i < 100; i++) {
        coins[i].CoinTx.loadFromFile("Assets/Textures/Some Sprites.png");
        coins[i].CoinSprite.setTexture(coins[i].CoinTx);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 463, 40, 39));
    }
    //Coins Position
    coins[0].CoinSprite.setPosition(200, 200);
    //

    ///Enemies Setting Texture
    for (int i = 0; i < 10; i++) {
        enemies[i].EnemyTx.loadFromFile("Assets/Textures/Enemies.png");
        enemies[i].EnenmySprite.setTexture(enemies[i].EnemyTx);
        enemies[i].EnenmySprite.setTextureRect(IntRect(enemies[i].TexNumber * 54, 345, 54, 29.2));
        enemies[i].EnenmySprite.setScale(2.5f, 2.5f);
    }
    enemies[0].EnenmySprite.setPosition(500, 580);
    enemies[0].xStart = 500;
    enemies[0].xEnd = 1100;


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

        //Delays and coins
        if (sonic.delay <= 3) sonic.delay++;
        if (sonic.idle_delay <= 10) sonic.idle_delay++;
        for (int i = 0; i < 100; i++) {
            if (coins[i].TexDelay <= 3) coins[i].TexDelay++;
            if (coins[i].TexDelay >= 3) {
                coins[i].TexDelay = 0;
                coins[i].TexNumber++;
                coins[i].TexNumber %= 17;
                coins[i].CoinSprite.setTextureRect(IntRect(coins[i].TexNumber * 41.11, 461, 41.11, 41));
            }
        }

        //Idle Animation
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

        //Moving Right
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                // Running Sonic Left
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
                // Walking Sonic Left
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

        //Moving Left
        if (Keyboard::isKeyPressed(Keyboard::Key::A) ) {
            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                // Running Sonic Right
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
                // Moving Sonic Right
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

        //Enemy System
        for (int i = 0; i < 10; i++) {
            if (enemies[i].TexDelay <= 8) enemies[i].TexDelay++;
            if (enemies[i].MovingRight) {
                enemies[i].EnenmySprite.move(4, 0);
                if (enemies[i].TexDelay >= 8) {
                    enemies[i].TexDelay = 0;
                    enemies[i].TexNumber++;
                    enemies[i].TexNumber %= 11;
                    enemies[i].EnenmySprite.setTextureRect(IntRect(enemies[i].TexNumber * 58, 345, 58, 29.2));
                }
                if (enemies[i].EnenmySprite.getPosition().x >= enemies[i].xEnd) enemies[i].MovingRight = false;
            }
            else {
                enemies[i].EnenmySprite.move(-4, 0);
                if (enemies[i].TexDelay >= 8) {
                    enemies[i].TexDelay = 0;
                    enemies[i].TexNumber--;
                    if (enemies[i].TexNumber <= 0) enemies[i].TexNumber = 10;
                    enemies[i].EnenmySprite.setTextureRect(IntRect(enemies[i].TexNumber * 58, 313, 58, 29.2));
                }
                if (enemies[i].EnenmySprite.getPosition().x <= enemies[i].xStart) enemies[i].MovingRight = true;
            }

            if (enemies[i].EnenmySprite.getGlobalBounds().intersects(sonic.PlayerSprite.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                if (!enemies[i].Hit) enemies[i].Hit = true;
                else enemies[i].EnenmySprite.setScale(0, 0);
                sonic.Velocity.y = 10;
            }
            else if ((enemies[i].EnenmySprite.getGlobalBounds().intersects(sonic.PlayerSprite.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0))) sonic.lives--;
            if (enemies[i].Hit && enemies[i].DamageDelay <= 30 && enemies[i].DamageDelay >= 0) {
                enemies[i].DamageDelay++;
                enemies[i].EnenmySprite.setColor(Color(255, 0, 0, 120));
            }
            else if (enemies[i].Hit && enemies[i].DamageDelay >= 30) {
                enemies[i].EnenmySprite.setColor(Color::White);
                enemies[i].DamageDelay = -1;
            }
        }


        // Jumpingpad System
        for (int i = 0; i < 5; i++) {
            if(jumppad[i].delay <= 2) jumppad[i].delay++;
            if (sonic.PlayerSprite.getGlobalBounds().intersects(jumppad[i].JumppadSprite.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                sonic.Velocity.y = 15;
                jumppad[i].jumped = true;
            }
            // Jumppad Animation
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
            //
        }


        ///Jumping Stystem
        if (sonic.PlayerSprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            sonic.on_ground = true;
            sonic.Velocity.y = 0;
            if (Keyboard::isKeyPressed(Keyboard::Key::Space)) sonic.Velocity.y = 10;
        }
        else {
            bool found = false;
            for (int i = 0; i < 30; i++) {
                if (sonic.PlayerSprite.getGlobalBounds().intersects(tiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < tiles[i].TileSprite.getPosition().y) {
                    found = true;
                    sonic.onWall = true;
                    sonic.Velocity.y = 0;
                }
            }
            if (!found) {
                sonic.on_ground = false;
                sonic.onWall = false;
            }
            
            if (!sonic.on_ground && !sonic.onWall) {
                sonic.sonic_adminator++;
                sonic.sonic_adminator %= 16;
                sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 49, 2 * 60, 49, 48));
                sonic.Velocity.y -= 0.3;
            }
            if (sonic.onWall) {
                sonic.Velocity.y = 0;
                if (Keyboard::isKeyPressed(Keyboard::Key::Space)) sonic.Velocity.y = 10;
            }
        }

        sonic.PlayerSprite.move(0, -sonic.Velocity.y);
        window.setView(camera);


        // clear
        window.clear();

        //draw
        window.draw(Map);
        window.draw(jumppad[0].JumppadSprite);
        for (int i = 0; i < 3; i++) {
            window.draw(tiles[i].TileSprite);
        }
        window.draw(coins[0].CoinSprite);
        window.draw(enemies[0].EnenmySprite);
        window.draw(sonic.PlayerSprite);
        window.display();
    }


    return 0;
}
