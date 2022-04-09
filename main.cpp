#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;
using std::cout;

//Player struct
struct Player {
    Texture PlayerTex;
    Sprite PlayerSprite;
    RectangleShape PlayerColl;
    Vector2f Velocity;
    int sonic_adminator = 0, Idle_adminator = 0, delay = 0, idle_delay = 0, left_adminator = 22;
    int scoreValue = 0, lives = 3, hitCounter = 0;
    bool start = false, Running = false, idle1 = false, txToggle = false, onTile = false;
    bool on_ground = true, hitRight = false, hitLeft = false, RunningSound = false;
} sonic;
//Jumpad struct
struct Jumppad {
    Sprite JumppadSprite;
    int Texnumber = 6, TexCnt = 0, delay = 0;
    bool TexLeft = false, jumped = false;
} jumppad[5];
//Tiles
struct FloatingTiles {
    Sprite TileSprite;
    RectangleShape TileColl;
} tiles[30];
//Coins
struct Coin {
    Sprite CoinSprite;
    int TexNumber = 0, TexDelay = 0;
} coins[100];

struct Red_Coin {
    Sprite CoinSprite;
    int TexNumber = 0, TexDelay = 0;
} Red_coins[100];

struct Enemies {
    Sprite EnenmySprite;
    int TexNumber = 0, TexDelay = 0, xStart, xEnd, DamageDelay = 0;
    bool MovingRight = true;
    bool Hit = false;
} enemies[10];

struct Enemies2 {
    Sprite EnemySprite;
    int TexNumber = 0, TexDelay = 0, xStart, xEnd, DamageDelay = 0;
    bool MovingRight = true;
    bool Hit = false;
} enemies2[10];

struct Spikes {
    Texture SpikeTex;
    Sprite SpikeSprite;
    int TexNum = 0, TexDelay = 0;
}spikes[100];

// function
void setTilePos(FloatingTiles& tile, int x, int y);
void PosRowCoins(int First_index, int Last_index, int X_position, int Y_Position);
void SingleCoinPos(int, int, int);
void Moving_in_Y_Axis(int, int, int, int, int);
void Moving_in_X_Axis(int, int, int, int);
void singleRedCoinPs(int, int, int);
void coinPos();
void PosRowSpikes(int First_index, int Last_index, int X_position, int Y_Position);
// main function

Texture CoinTex;
Texture RedCoinTx;
Texture SpikeTex;

int main()
{
    RenderWindow Menu(VideoMode(1200, 760), "Sonic");
    

    //Settings choice
    Texture correctTex;
    correctTex.loadFromFile("Assets/Textures/correct-logo.png");
    Sprite correctSprite[2];
    correctSprite[0].setTexture(correctTex);
    correctSprite[0].setPosition(620, 240);
    correctSprite[0].setScale(0.032, 0.032);
    correctSprite[1].setTexture(correctTex);

    //Leaderboard
    Texture LeaderBackgroundTex;
    LeaderBackgroundTex.loadFromFile("Assets/Textures/leaderboard.png");
    Sprite leaderSprite;
    leaderSprite.setTexture(LeaderBackgroundTex);
    bool LeaderClosed = true;
    //Font
    Font EvilEmpire;
    EvilEmpire.loadFromFile("Assets/EvilEmpire-4BBVK.ttf");
    
    //Menu Background
    Texture MenuBackgroundTex;
    MenuBackgroundTex.loadFromFile("Assets/Textures/MenuBackground.png");
    Sprite MenuBackgroundSprite;
    MenuBackgroundSprite.setTexture(MenuBackgroundTex);
    //Settings Background
    Texture SettingsBackgroundTex;
    SettingsBackgroundTex.loadFromFile("Assets/Textures/setting-menu.png");
    Sprite SettingsBackgroundSprite;
    SettingsBackgroundSprite.setTexture(SettingsBackgroundTex);
    //Mouse
    RectangleShape Sensor;
    Sensor.setSize(Vector2f(1, 1));
    //Start Button
    Texture BarTex;
    Sprite startBarSprite;
    BarTex.loadFromFile("Assets/Textures/Bar.png");
    startBarSprite.setTexture(BarTex);
    startBarSprite.setScale(0.12f, 0.12f);
    startBarSprite.setPosition(160, 300);
    bool startIsPlayed = false;
    Text StartText;
    StartText.setFont(EvilEmpire);
    StartText.setString("Start");
    StartText.setFillColor(Color(14, 24, 95));
    StartText.setCharacterSize(50);
    StartText.setPosition(230, 292);
    
    //Settings Button
    bool SettingsClosed = true;
    Sprite settingsBarSprite;
    settingsBarSprite.setTexture(BarTex);
    settingsBarSprite.setScale(0.12f, 0.12f);
    settingsBarSprite.setPosition(160, 400);
    bool settingsIsPlayed = false;
    Text SettingsText;
    SettingsText.setFont(EvilEmpire);
    SettingsText.setString("Settings");
    SettingsText.setFillColor(Color(14, 24, 95));
    SettingsText.setCharacterSize(50);
    SettingsText.setPosition(200, 393);

    //Settings back button
    Texture backButtonTex;
    backButtonTex.loadFromFile("Assets/Textures/back-setting-menu.png");
    Sprite backSprite;
    backSprite.setPosition(43, 716);
    backSprite.setScale(0.7, 0.7);
    backSprite.setTexture(backButtonTex);
    RectangleShape backButton;
    backButton.setSize(Vector2f(150, 50));
    backButton.setPosition(50, 700);
    bool backIsVisible = false;

    //Settings Music button
    CircleShape MusicCircle;
    MusicCircle.setFillColor(Color::White);
    MusicCircle.setRadius(29.f);
    MusicCircle.setPosition(620, 240);
    bool MusicOn = true;
    int ButtonDelay = 0;
    
    //Leaderboard Button
    Sprite leaderBarSprite;
    leaderBarSprite.setTexture(BarTex);
    leaderBarSprite.setScale(0.12f, 0.12f);
    leaderBarSprite.setPosition(160, 500);
    bool leaderIsPlayed = false;
    Text LeaderText;
    LeaderText.setFont(EvilEmpire);
    LeaderText.setString("Leaderboard");
    LeaderText.setFillColor(Color(14, 24, 95));
    LeaderText.setCharacterSize(50);
    LeaderText.setPosition(172, 493);
    //Leader back button
    Sprite leaderbackSprite;
    leaderbackSprite.setPosition(43, 716);
    leaderbackSprite.setScale(0.7, 0.7);
    leaderbackSprite.setTexture(backButtonTex);
    RectangleShape leaderbackButton;
    leaderbackButton.setSize(Vector2f(150, 50));
    leaderbackButton.setPosition(50, 700);
    bool leaderbackIsVisible = false;

    
    BarTex.setSmooth(true);
    //Button selection sound
    SoundBuffer ButtonClickBuffer;
    ButtonClickBuffer.loadFromFile("Assets/Sounds/Picksound.ogg");
    Sound ButtonClickSound;
    ButtonClickSound.setBuffer(ButtonClickBuffer);
    ButtonClickSound.setVolume(30);
    
    //Menu music
    Music MenuMusic;
    MenuMusic.openFromFile("Assets/Sounds/awesomeness.ogg");
    MenuMusic.setVolume(50);
    MenuMusic.setLoop(true);
    MenuMusic.play();

    
        bool start = false;
        while (Menu.isOpen())
        {
            Event menuEvent;
            while (Menu.pollEvent(menuEvent))
            {
                if (menuEvent.type == Event::Closed)
                { 
                    Menu.close();
                    MenuMusic.stop();
                }
            }
            //Press on leaderboard
            if (Sensor.getGlobalBounds().intersects(leaderBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed)
            {
                LeaderClosed = false;
            }

            //Starting game
            if (Sensor.getGlobalBounds().intersects(startBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed && LeaderClosed )
            {
                Menu.close();
                start = true;
                MenuMusic.stop();
            }
            //Press on settings
            if (Sensor.getGlobalBounds().intersects(settingsBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed && LeaderClosed)
            {
                SettingsClosed = false;
            }
            //Settings Back button
            if (Sensor.getGlobalBounds().intersects(backButton.getGlobalBounds()) && !SettingsClosed)
            {
                backIsVisible = true;
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    SettingsClosed = true;
                }
            }
            else
            {
                backIsVisible = false;
            }
            //Leader back button
            if (Sensor.getGlobalBounds().intersects(leaderbackButton.getGlobalBounds()) && !LeaderClosed)
            {
                leaderbackIsVisible = true;
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    LeaderClosed = true;
                }
            }
            else
            {
                leaderbackIsVisible = false;
            }

            //touch music circle
            if (Sensor.getGlobalBounds().intersects(MusicCircle.getGlobalBounds()) && !SettingsClosed && Mouse::isButtonPressed(Mouse::Left) && ButtonDelay >= 60)
            {

                if (MusicOn)
                { 
                    MusicOn = false;
                    MenuMusic.stop();
                }
                else
                {
                    MusicOn = true;
                    MenuMusic.play();
                }
                ButtonDelay = 0;
            }
            if (ButtonDelay <= 60)
                ButtonDelay++;
            
            //Sensor pos
            Sensor.setPosition(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y);
            //Start
            if (Sensor.getGlobalBounds().intersects(startBarSprite.getGlobalBounds()))
            {
                startBarSprite.setColor(Color(45, 49, 250));
                StartText.setFillColor(Color(255,255,255));
                startBarSprite.setScale(0.17f, 0.135f);
                startBarSprite.setPosition(145, 295);
                if(!startIsPlayed && SettingsClosed && LeaderClosed)
                { 
                ButtonClickSound.play();
                startIsPlayed = true;
                }
            }
            else
            {
                StartText.setFillColor(Color(14, 24, 95));
                startBarSprite.setColor(Color(255, 255, 255));
                startBarSprite.setScale(0.16f, 0.12f);
                startBarSprite.setPosition(160, 300);
                startIsPlayed = false;
            }
            //Settings
            if (Sensor.getGlobalBounds().intersects(settingsBarSprite.getGlobalBounds()))
            {
                SettingsText.setFillColor(Color::White);
                settingsBarSprite.setScale(0.17f, 0.135f);
                settingsBarSprite.setColor(Color(45, 49, 250));
                settingsBarSprite.setPosition(145, 395);
                if (!settingsIsPlayed && SettingsClosed && LeaderClosed)
                {
                    ButtonClickSound.play();
                    settingsIsPlayed = true;
                }

            }
            else
            {
                SettingsText.setFillColor(Color(14, 24, 95));
                settingsBarSprite.setScale(0.16f, 0.12f);
                settingsBarSprite.setColor(Color(255, 255, 255));
                settingsBarSprite.setPosition(160, 400);
                settingsIsPlayed = false;
            }
            //Leaderboard
            if (Sensor.getGlobalBounds().intersects(leaderBarSprite.getGlobalBounds()))
            {
                LeaderText.setFillColor(Color::White);
                leaderBarSprite.setScale(0.25f, 0.135f);
                leaderBarSprite.setColor(Color(45, 49, 250));
                leaderBarSprite.setPosition(120, 495);
                if (!leaderIsPlayed && SettingsClosed && LeaderClosed)
                {
                    ButtonClickSound.play();
                    leaderIsPlayed = true;
                }

            }
            else
            {
                LeaderText.setFillColor(Color(14, 24, 95));
                leaderBarSprite.setScale(0.22f, 0.12f);
                leaderBarSprite.setColor(Color(255, 255, 255));
                leaderBarSprite.setPosition(125, 500);
                leaderIsPlayed = false;
            }

           

            Menu.clear();
           
            Menu.draw(MenuBackgroundSprite);
            Menu.draw(startBarSprite);
            Menu.draw(settingsBarSprite);
            Menu.draw(StartText);
            Menu.draw(SettingsText);
            Menu.draw(leaderBarSprite);
            Menu.draw(LeaderText);
            if (!LeaderClosed)
            {
                Menu.draw(leaderSprite);

                if (leaderbackIsVisible)
                    Menu.draw(leaderbackSprite);

            }


            if (!SettingsClosed)
            { 
                
                Menu.draw(SettingsBackgroundSprite);
               
                if (backIsVisible)
                    Menu.draw(backSprite);
                if (MusicOn)
                    Menu.draw(correctSprite[0]);
            }
            Menu.display();
        }

    // rendering window
    if(start){
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

    //Coin texture
    CoinTex.loadFromFile("Assets/Textures/Some Sprites.png");
    //Redcoin Texture
    RedCoinTx.loadFromFile("Assets/Textures/Some-Sprites-red-coin.png");
    //Jumppad Texture
    Texture JumppadTx;
    JumppadTx.loadFromFile("Assets/Textures/Some Sprites.png");
    //Enemy texture
    Texture EnemyTx;
    EnemyTx.loadFromFile("Assets/Textures/Enemies.png");
    Texture EnemyTx2;
    EnemyTx2.loadFromFile("Assets/Textures/Enemies.png");
    //Spike texture
    SpikeTex.loadFromFile("Assets/Textures/Spike.png");
    //Tiles texture
    Texture TilesTx;
    TilesTx.loadFromFile("Assets/Textures/Wall2.png");



    coinPos();
    //// sonic player
       // sonic texture
    sonic.PlayerTex.loadFromFile("Assets/Textures/Sonic-Character.png");
    sonic.PlayerSprite.setTexture(sonic.PlayerTex);
    // sonic sprite
    sonic.PlayerSprite.setTextureRect(IntRect(sonic.Idle_adminator * 59.1578, 0, 59.1578, 60));
    sonic.PlayerColl.setSize(Vector2f(55.f, 80.f));
    sonic.PlayerColl.setPosition(205, 300);
    sonic.PlayerSprite.setPosition(200, 300);
    sonic.PlayerSprite.setScale(2.5, 2.5);
    //

    ///Jumppad Setting Texture
    for (int i = 0; i < 5; i++) {
        jumppad[i].JumppadSprite.setTexture(JumppadTx);
        jumppad[i].JumppadSprite.setTextureRect(IntRect(jumppad[i].Texnumber * 80, 543, 80, 66));
    }
    //Jumppad Position
    jumppad[0].JumppadSprite.setPosition(3000, 590);
    //

    ///Floating Tiles Setting Texture
    for (int i = 0; i < 30; i++) {
        tiles[i].TileSprite.setTexture(TilesTx);
        tiles[i].TileSprite.setScale(1.3, 1.3);
        tiles[i].TileColl.setSize(Vector2f(298.9f, 1.f));
    }
    setTilePos(tiles[0], 3400, 300);
    setTilePos(tiles[1], 4200, 200);
    setTilePos(tiles[2], 5000, 250);
    //


    ///Enemies Setting Texture
    for (int i = 0; i < 10; i++) {
        enemies[i].EnenmySprite.setTexture(EnemyTx);
        enemies[i].EnenmySprite.setTextureRect(IntRect(enemies[i].TexNumber * 54, 345, 54, 29.2));
        enemies[i].EnenmySprite.setScale(2.5f, 2.5f);
    }
    enemies[0].EnenmySprite.setPosition(1500, 580);
    enemies[0].xStart = 500;
    enemies[0].xEnd = 1100;

    for (int i = 0; i < 10; i++) {
        enemies2[i].EnemySprite.setTexture(EnemyTx2);
        enemies2[i].EnemySprite.setTextureRect(IntRect(enemies2[i].TexNumber * 47, 411, 47, 30));
        enemies2[i].EnemySprite.setScale(2.5f, 2.5f);
    }
    enemies2[0].EnemySprite.setPosition(1500, 585);
    enemies2[0].xStart = 1500;
    enemies2[0].xEnd = 2500;
    //
    //Spikes system
    for (int i = 0; i < 10; i++) {
        spikes[i].SpikeSprite.setTexture(SpikeTex);
        spikes[i].SpikeSprite.setTextureRect(IntRect(0, 0, 142, 163));
        spikes[i].SpikeSprite.setScale(0.5f, 0.5f);
    }
    //Spikes
    PosRowSpikes(0, 30, 3400, 580);

    //score
    Font font;
    font.loadFromFile("Assets/EvilEmpire-4BBVK.ttf");
    Text text;
    text.setFont(font);
    text.setString("Score: " + std::to_string(sonic.scoreValue));
    text.setFillColor(Color::Yellow);
    text.setPosition(10, 10);
    text.setCharacterSize(35);

    //health_bar
    Texture SonicFaceTx;
    SonicFaceTx.loadFromFile("Assets/Textures/chances.png");
    Sprite SonicFace;
    SonicFace.setTexture(SonicFaceTx);
    SonicFace.setScale(0.1, 0.1);
    SonicFace.setPosition(10, 700);
    Text lives;
    lives.setFont(font);
    lives.setString("x" + std::to_string(sonic.lives));
    lives.setFillColor(Color::Yellow);
    lives.setPosition(90, 700);
    lives.setCharacterSize(35);

    // the music of main menu
    Music MainMenuMusic;
    MainMenuMusic.openFromFile("Assets/Sounds/mainmenu.wav");
    // the music of playgound
    Music BackgroundMusic;
    BackgroundMusic.openFromFile("Assets/Sounds/05-Labyrinth-Zone.ogg");
    BackgroundMusic.setVolume(50);
    BackgroundMusic.setLoop(true);
    BackgroundMusic.play();
    //coin sound
    SoundBuffer CoinBuffer;
    CoinBuffer.loadFromFile("Assets/Sounds/coin.WAV");
    Sound CoinAudio;
    CoinAudio.setBuffer(CoinBuffer);
    //jump sound
    SoundBuffer JumpBuffer;
    JumpBuffer.loadFromFile("Assets/Sounds/jump.WAV");
    Sound JumpSound;
    JumpSound.setBuffer(JumpBuffer);
    //death sound
    SoundBuffer DeathBuffer;
    DeathBuffer.loadFromFile("Assets/Sounds/death.WAV");
    Sound DeathAudio;
    DeathAudio.setBuffer(DeathBuffer);
    //open sound
    SoundBuffer IntroBuffer;
    IntroBuffer.loadFromFile("Assets/Sounds/open.WAV");
    Sound IntroAudio;
    IntroAudio.setBuffer(IntroBuffer);
    //enemy damage sound
    SoundBuffer EnemyDamageBuffer;
    EnemyDamageBuffer.loadFromFile("Assets/Sounds/enemy damage.WAV");
    Sound EnemyDamageSound;
    EnemyDamageSound.setBuffer(EnemyDamageBuffer);
    //spring sound
    SoundBuffer JumppadBuffer;
    JumppadBuffer.loadFromFile("Assets/Sounds/spring.WAV");
    Sound JumppadAudio;
    JumppadAudio.setBuffer(JumppadBuffer);
    //deathspike sound
    SoundBuffer SpikeDeathBuffer;
    SpikeDeathBuffer.loadFromFile("Assets/Sounds/death-spike.wav");
    Sound SpikeDeathAudio;
    SpikeDeathAudio.setBuffer(SpikeDeathBuffer);
    //speedchute sound
    SoundBuffer RunningBuffer;
    RunningBuffer.loadFromFile("Assets/Sounds/speedchute.wav");
    Sound RunningSound;
    RunningSound.setBuffer(RunningBuffer);
    // sound gameover
    SoundBuffer GameoverBuffer;
    GameoverBuffer.loadFromFile("Assets/Sounds/gameover.wav");
    Sound GameoverAudio;
    GameoverAudio.setBuffer(GameoverBuffer);


    /// ground rectangle shape
    RectangleShape ground(Vector2f(17000, 70)); ground.setScale(1, 1); ground.setPosition(0, 640);
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
        if (sonic.hitCounter > 0) sonic.hitCounter--;
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
            if (sonic.PlayerColl.getGlobalBounds().intersects(coins[i].CoinSprite.getGlobalBounds())) {
                coins[i].CoinSprite.setScale(0, 0);
                sonic.scoreValue += 10;
                CoinAudio.play();
            }
        }
        for (int i = 0; i < 100; i++) {
            if (Red_coins[i].TexDelay <= 3)Red_coins[i].TexDelay++;
            if (Red_coins[i].TexDelay >= 3) {
                Red_coins[i].TexDelay = 0;
                Red_coins[i].TexNumber++;
                Red_coins[i].TexNumber %= 14;
                Red_coins[i].CoinSprite.setTextureRect(IntRect(Red_coins[i].TexNumber * 113.0, 0, 113.0, 112));
            }
            if (sonic.PlayerColl.getGlobalBounds().intersects(Red_coins[i].CoinSprite.getGlobalBounds())) {
                Red_coins[i].CoinSprite.setScale(0, 0);
                sonic.scoreValue += 20;
                sonic.lives++;
                CoinAudio.play();
            }
        }

        for (int i = 0; i < 50; i++) {
            if (spikes[i].SpikeSprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                sonic.lives--;
                sonic.Velocity.y = 10;
                SpikeDeathAudio.play();
            }
            else if (spikes[i].SpikeSprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0)) {
                if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == 0) sonic.lives--;
                if (sonic.PlayerColl.getPosition().x > spikes[i].SpikeSprite.getPosition().x) sonic.hitRight = true;
                else sonic.hitLeft = true;
                sonic.hitCounter = 50;
                sonic.Velocity.y = 7;
                sonic.PlayerSprite.move(0, -10);
                SpikeDeathAudio.play();
            }
        }

        //Idle Animation
        if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S)) {
            sonic.Running = false;
            sonic.txToggle = false;
            sonic.RunningSound = false;
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
        if (Keyboard::isKeyPressed(Keyboard::Key::D) && !sonic.hitLeft && !sonic.hitRight) {
            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                // Running Sonic Left
                sonic.PlayerSprite.move(15, 0);
                if (!sonic.RunningSound) {
                    RunningSound.play();
                    sonic.RunningSound = true;
                }
                if (sonic.PlayerSprite.getPosition().x >= 200) {
                    camera.move(15, 0);
                    text.move(15, 0);
                    lives.move(15, 0);
                    SonicFace.move(15, 0);
                }
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
                if (sonic.PlayerSprite.getPosition().x >= 200) {
                    camera.move(12, 0);
                    text.move(12, 0);
                    lives.move(12, 0);
                    SonicFace.move(12, 0);
                }
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
        if (Keyboard::isKeyPressed(Keyboard::Key::A) && !sonic.hitLeft && !sonic.hitRight && sonic.PlayerSprite.getPosition().x > 0) {
            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                // Running Sonic Right                
                sonic.PlayerSprite.move(-15, 0);
                if (!sonic.RunningSound) {
                    RunningSound.play();
                    sonic.RunningSound = true;
                }
                if (sonic.PlayerSprite.getPosition().x >= 200) {
                    camera.move(-15, 0);
                    text.move(-15, 0);
                    lives.move(-15, 0);
                    SonicFace.move(-15, 0);
                }
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
                if (sonic.PlayerSprite.getPosition().x >= 200) {
                    camera.move(-12, 0);
                    text.move(-12, 0);
                    lives.move(-12, 0);
                    SonicFace.move(-12, 0);
                }
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

        if (sonic.hitRight) {
            sonic.PlayerSprite.move(5, 0);
            if (sonic.PlayerSprite.getPosition().x >= 200) {
                camera.move(5, 0);
                text.move(5, 0);
                lives.move(5, 0);
                SonicFace.move(5, 0);
            }
            if (sonic.on_ground) sonic.hitRight = false;
        }
        else if (sonic.hitLeft) {
            sonic.PlayerSprite.move(-5, 0);
            if (sonic.PlayerSprite.getPosition().x >= 200) {
                camera.move(-5, 0);
                text.move(-5, 0);
                lives.move(-5, 0);
                SonicFace.move(-5, 0);
            }
            if (sonic.on_ground) sonic.hitLeft = false;
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

            if (enemies[i].EnenmySprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                if (!enemies[i].Hit) enemies[i].Hit = true;
                else enemies[i].EnenmySprite.setScale(0, 0);
                sonic.Velocity.y = 10;
                EnemyDamageSound.play();
            }
            else if (enemies[i].EnenmySprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0)) {
                if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == 0) sonic.lives--;
                if (sonic.PlayerSprite.getPosition().x > enemies[i].EnenmySprite.getPosition().x) sonic.hitRight = true;
                else sonic.hitLeft = true;
                sonic.hitCounter = 50;
                sonic.Velocity.y = 10;
                sonic.PlayerSprite.move(0, -10);
                SpikeDeathAudio.play();
            }
            if (enemies[i].Hit && enemies[i].DamageDelay <= 30 && enemies[i].DamageDelay >= 0) {
                enemies[i].DamageDelay++;
                enemies[i].EnenmySprite.setColor(Color(255, 0, 0, 200));
            }
            else if (enemies[i].Hit && enemies[i].DamageDelay >= 30) {
                enemies[i].EnenmySprite.setColor(Color::White);
                enemies[i].DamageDelay = -1;
            }
            if (enemies2[i].TexDelay <= 8) enemies2[i].TexDelay++;
            if (enemies2[i].MovingRight) {
                enemies2[i].EnemySprite.move(4, 0);
                if (enemies2[i].TexDelay >= 8) {
                    enemies2[i].TexDelay = 0;
                    enemies2[i].TexNumber++;
                    enemies2[i].TexNumber %= 4;
                    enemies2[i].EnemySprite.setTextureRect(IntRect(enemies2[i].TexNumber * 47, 411, 48, 30));
                }
                if (enemies2[i].EnemySprite.getPosition().x >= enemies2[i].xEnd) {
                    enemies2[i].MovingRight = false;
                }
            }
            else {
                enemies2[i].EnemySprite.move(-4, 0);
                if (enemies2[i].TexDelay >= 8) {
                    enemies2[i].TexDelay = 0;
                    enemies2[i].TexNumber--;
                    if (enemies2[i].TexNumber <= 0) enemies2[i].TexNumber = 3;
                    enemies2[i].EnemySprite.setTextureRect(IntRect(enemies2[i].TexNumber * 47, 411, 48, 30));
                }
                if (enemies2[i].EnemySprite.getPosition().x <= enemies2[i].xStart) enemies2[i].MovingRight = true;
            }

            if (enemies2[i].EnemySprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                if (!enemies2[i].Hit) enemies2[i].Hit = true;
                else enemies2[i].EnemySprite.setScale(0, 0);
                sonic.Velocity.y = 10;
                EnemyDamageSound.play();
            }
            else if ((enemies2[i].EnemySprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0))) {
                if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == 0) sonic.lives--;
                if (sonic.PlayerSprite.getPosition().x > enemies2[i].EnemySprite.getPosition().x) sonic.hitRight = true;
                else sonic.hitLeft = true;
                sonic.hitCounter = 50;
                sonic.Velocity.y = 10;
                sonic.PlayerSprite.move(0, -10);
                SpikeDeathAudio.play();
            }
            if (enemies2[i].Hit && enemies2[i].DamageDelay <= 30 && enemies2[i].DamageDelay >= 0) {
                enemies2[i].DamageDelay++;
                enemies2[i].EnemySprite.setColor(Color(255, 0, 0, 200));
            }
            else if (enemies2[i].Hit && enemies2[i].DamageDelay >= 30) {
                enemies2[i].EnemySprite.setColor(Color::White);
                enemies2[i].DamageDelay = -1;
            }
        }


        // Jumpingpad System
        for (int i = 0; i < 5; i++) {
            if (jumppad[i].delay <= 2) jumppad[i].delay++;
            if (sonic.PlayerColl.getGlobalBounds().intersects(jumppad[i].JumppadSprite.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                sonic.Velocity.y = 15;
                jumppad[i].jumped = true;
                JumppadAudio.play();
            }
            // Jumppad Animation
            if (jumppad[i].jumped) {
                if (jumppad[i].delay >= 2) {
                    jumppad[i].delay = 0;
                    if (jumppad[i].TexLeft) jumppad[i].Texnumber++;
                    else jumppad[i].Texnumber--;
                    if (jumppad[i].Texnumber >= 6) jumppad[i].jumped = false;
                    else if (jumppad[i].Texnumber <= 0) jumppad[i].TexLeft = true;
                    jumppad[i].JumppadSprite.setTextureRect(IntRect(jumppad[i].Texnumber * 80, 543, 79.7, 66));
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
        if (sonic.PlayerColl.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            sonic.on_ground = true;
            sonic.Velocity.y = 0;
            if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
                sonic.Velocity.y = 10;
                JumpSound.play();
            }
        }
        else {
            bool found = false;
            for (int i = 0; i < 30; i++) {
                if (sonic.PlayerSprite.getGlobalBounds().intersects(tiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < tiles[i].TileSprite.getPosition().y) {
                    found = true;
                    sonic.onTile = true;
                    sonic.Velocity.y = 0;
                }
            }
            if (!found) {
                sonic.on_ground = false;
                sonic.onTile = false;
            }

            if (!sonic.on_ground && !sonic.onTile) {
                sonic.sonic_adminator++;
                sonic.sonic_adminator %= 16;
                sonic.PlayerSprite.setTextureRect(IntRect(sonic.sonic_adminator * 49, 2 * 60, 49, 48));
                sonic.Velocity.y -= 0.3;
            }
            if (sonic.onTile) {
                sonic.Velocity.y = 0;
                if (Keyboard::isKeyPressed(Keyboard::Key::Space)) sonic.Velocity.y = 10;
            }
        }

        sonic.PlayerSprite.move(0, -sonic.Velocity.y);
        sonic.PlayerColl.setPosition(sonic.PlayerSprite.getPosition().x + 28, sonic.PlayerSprite.getPosition().y + 30);
        window.setView(camera);


        // clear
        window.clear();
        lives.setString("x" + std::to_string(sonic.lives));
        text.setString("Score: " + std::to_string(sonic.scoreValue));

        //draw
        window.draw(Map);
        window.draw(jumppad[0].JumppadSprite);
        for (int i = 0; i < 3; i++) {
            window.draw(tiles[i].TileSprite);
        }
        for (int i = 0; i < 100; i++) {
            window.draw(Red_coins[i].CoinSprite);
            window.draw(coins[i].CoinSprite);
            window.draw(spikes[i].SpikeSprite);
        }
        window.draw(enemies[0].EnenmySprite);
        window.draw(enemies2[0].EnemySprite);
        window.draw(sonic.PlayerSprite);
        window.draw(SonicFace);
        window.draw(text);
        window.draw(lives);
        window.display();
    }

    }
    return 0;
}

void setTilePos(FloatingTiles& tile, int x, int y) {
    tile.TileSprite.setPosition(x, y);
    tile.TileColl.setPosition(x + 15, y);
}

void singleRedCoinPs(int index, int X_position, int Y_Position) {
    Red_coins[index].CoinSprite.setTexture(RedCoinTx);
    Red_coins[index].CoinSprite.setTextureRect(IntRect(0, 0, 1588, 112));
    Red_coins[index].CoinSprite.setScale(0.7, 0.7);
    Red_coins[index].CoinSprite.setPosition(X_position, Y_Position);
}
void Moving_in_X_Axis(int First_index, int Last_index, int X_position, int Y_Position) {
    for (int i = First_index; i < Last_index; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(X_position + ((i - First_index) * 45), Y_Position);
    }
}
void Moving_in_Y_Axis(int First_index, int Last_index, int X_position, int Y_Position, int increase = 45) {
    for (int i = First_index; i < Last_index; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(X_position, Y_Position - ((i - First_index) * 45));
    }
}
void SingleCoinPos(int num, int X_Position, int Y_position) {
    coins[num].CoinSprite.setTexture(CoinTex);
    coins[num].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
    coins[num].CoinSprite.setPosition(X_Position, Y_position);
}
void PosRowCoins(int First_index, int Last_index, int X_position, int Y_Position) {
    for (int i = First_index; i < Last_index; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(X_position + (i * 40), Y_Position);
    }
}

void coinPos() {
    // coins positioning ........................................................................................
    // Walll..............
    PosRowCoins(0, 8, 3400, 265);
    PosRowCoins(8, 16, 3889, 170);
    PosRowCoins(16, 24, 4356, 220);
    //letter S .................................
    Moving_in_X_Axis(24, 27, 1160, 350);
    Moving_in_X_Axis(34, 37, 1160, 580);
    Moving_in_X_Axis(29, 32, 1160, 470);
    Moving_in_Y_Axis(27, 29, 1120, 430, 50);
    Moving_in_Y_Axis(32, 34, 1280, 540, 50);
    // letter "o"

    SingleCoinPos(45, 1385, 490);
    SingleCoinPos(46, 1630, 490);
    SingleCoinPos(41, 1510, 360);
    SingleCoinPos(50, 1505, 600);
    for (int i = 38; i < 39; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1465, 375);
    }
    for (int i = 39; i < 41; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1370 + ((i - 38) * 35), 510 - ((i - 37) * 35));
    }
    for (int i = 42; i < 45; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1520 + ((i - 41) * 35), 335 + ((i - 41) * 35));
    }
    for (int i = 47; i < 50; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1400 + ((i - 47) * 35), 540 + ((i - 47) * 25));
    }
    for (int i = 51; i < 54; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1410 + ((i - 47) * 35), 680 - ((i - 47) * 25));
    }
    // letter n...........
    Moving_in_Y_Axis(54, 59, 1720, 605);
    Moving_in_Y_Axis(62, 67, 1880, 605);
    Moving_in_X_Axis(59, 62, 1760, 400);
    // letter i 
    Moving_in_Y_Axis(67, 72, 1980, 600);
    Moving_in_Y_Axis(72, 77, 2020, 600);
    // letter c.................................................
    SingleCoinPos(77, 2100, 515);
    SingleCoinPos(78, 2120, 470);
    SingleCoinPos(79, 2120, 560);
    SingleCoinPos(80, 2145, 440);
    SingleCoinPos(81, 2145, 590);
    Moving_in_X_Axis(82, 84, 2190, 600);
    Moving_in_X_Axis(84, 86, 2190, 420);
    //Red coins................................
    singleRedCoinPs(1, 1980, 350);
    Red_coins[2].CoinSprite.setTexture(RedCoinTx);
    Red_coins[2].CoinSprite.setTextureRect(IntRect(0, 0, 1588, 112));
    Red_coins[2].CoinSprite.setScale(1.5, 1.5);
    Red_coins[2].CoinSprite.setPosition(1440, 430);
}

void PosRowSpikes(int First_index, int Last_index, int X_position, int Y_Position) {
    for (int i = First_index; i < Last_index; i++) {
        spikes[i].SpikeSprite.setTexture(SpikeTex);
        spikes[i].SpikeSprite.setTextureRect(IntRect(0, 0, 142, 163));
        spikes[i].SpikeSprite.setScale(0.5f, 0.5f);
        spikes[i].SpikeSprite.setPosition(X_position + (i * 71), Y_Position);
    }
}
