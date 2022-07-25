#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cmath>
#include <fstream>
#define fa(i, a, n) for(int (i) = (a); (i) < (n); (i)++)
#define fb(i, n, a) for(int (i) = (n); (i) >= (a); (i)--)
using namespace sf;
using namespace std;

//Player struct
struct Player {
    Texture PlayerTex;
    Sprite PlayerSprite;
    RectangleShape PlayerColl, LeftColl, RightColl;
    Vector2f Velocity;
    int RightTexNumber = 0, IdleTexNumber = 0, TexDelay = 0, IdleDelay = 0, HitTxDelay = 0, LeftTexNumber = 22, HitCounter2 = 5;
    int scoreValue = 0, lives = 5, hitCounter = -1, deathDealy = 0, FinalScore = 0;
    bool start = false, Running = false, IdleDirectionL = false, txToggle = false, onTile = false, OnVTile = false;
    bool on_ground = true, hitRight = false, hitLeft = false, RunningSound = false, HitAbove = false;
};
//Boss
struct BossSt {
    Texture BossTx;
    Sprite BossSprite;
    RectangleShape HitBox, HealthBarBG, HealthBarRect;
    CircleShape HitBoxLvl2;
    Vector2f Velocity;
    Texture BossFaceTx;
    Sprite BossFaceSprite;
    int hitCounter = 0, TexDelay = 0, TexNumber = 0, lives = 10, BarCounter = 0;
    double HealthBar = 10;
    bool SceneStart = false, FightStartLevel1 = false, FightStartLevel2 = false, MoveStart = false, MovingLeft = true, StartDelay = false;
    bool Level1FightEnd = false;
};

struct WreckingBall {
    Texture WreckingChainTx;
    Sprite WreckingChainSprite;
    Texture WreckingBallTx;
    Sprite WreckingBallSprite;
    CircleShape HitBox;
    double Velocity = 1;
    bool MovingLeft = true;
};

struct Explosions {
    Sprite ExplosionSprite;
    int rowTxNum = 0, colomnTxNum = 0, TxDelay = 0;
    bool Spawned = false;
} Explosion[40];

//Jumpad start
struct Jumppad {
    Sprite JumppadSprite;
    int Texnumber = 6, TexCnt = 0, delay = 0;
    bool TexLeft = false, jumped = false;
} jumppad[30];
//Tiles
struct FloatingTiles {
    Sprite TileSprite;
    RectangleShape TileColl;
    RectangleShape LowerTileColl;
} tiles[200];

struct FloatingTiles2 {
    Texture TileTx2;
    Sprite TileSprite;
    RectangleShape TileColl;
} tiles2[6];

struct AnimatedTiles {
    Sprite TileSprite;
    RectangleShape TileColl;
    int xStart = 0, xEnd = 0, yStart = 0, yEnd = 0, counter = 0, dCounter = 0, AnimCounter = 0;
    bool Direction = true, FullDisappeared = false, Disappeared = true;
} HAnimTiles[2], VAnimTiles[23], DisappearingTiles[11];
//Coins
struct Coin {
    Sprite CoinSprite;
    int TexNumber = 0, TexDelay = 0;
} coins[425];

struct Red_Coin {
    Sprite CoinSprite;
    int TexNumber = 0, TexDelay = 0;
} Red_coins[6];

struct Enemies {
    Sprite EnemySprite;
    RectangleShape EnemyColl;
    int TexNumber = 0, TexDelay = 0, xStart = 0, xEnd = 0, DamageDelay = 0;
    bool MovingRight = true;
    bool Hit = false;
} Worms[20], Crabs[20], Enemy3[20];

struct Spikes {
    Sprite SpikeSprite;
}spikes[300];

struct Spikes2 {
    Sprite SpikeSprite;
}spikes2[76];

struct animatedSpikes2 {
    Texture SpikeTex2;
    Sprite SpikeSprite2;
    int xStart = 0, xEnd = 0, yStart = 0, yEnd = 0, counter = 0;
    bool Direction = true;
}animespikes2[100];

struct Vertical_Tiles {
    Sprite Vertical_Tiles_sprite;
    RectangleShape tilecole;
    RectangleShape upper_tilecole;
}Vertical_tiles_right[10], Vertical_tiles_left[10];

struct SkyBullets {
    Sprite SkyBulletsSprite;
    RectangleShape BulletColl;
    int TexNumber = 0, TexDelay = 0;
    bool spawned = false;
} skyBullets[10];

struct FloatingShip {
    Sprite ShipSprite;
    int shipTexDelay = 0, ShipTexNumber = 0;
    bool ShipMovingLeft = true;
} floatingShips[3];

//leaderboaerd functions

//leaderboard map
multimap <int, string, greater<>> leaderBoard;

void saveLDToFile();
void clearLeaderBoard();
void pushScore(pair<int, string> score);
void loadLDFromFile();


// function
void setTilePos(FloatingTiles& tile, int x, int y);
void PosRowCoins(int First_index, int Last_index, int X_position, int Y_Position);
void SingleCoinPos(int, int, int);
void Moving_in_Y_Axis(int, int, int, int, int);
void Moving_in_X_Axis(int, int, int, int);
void singleRedCoinPs(int, int, int);
void coinPos();
void PosRowSpikes(int First_index, int Last_index, int X_position, int Y_Position);
void Moving_in_X_Y(int First_index, int Last_index, int X_position, int Y_Position, int X_increament = 45, int Y_increament = 45);
void Draw_jumppad();
void draw_tiles();
void draw_spikes();
void draw_vertical_tiles();
void WormsPos(int index, int X_pos, int Y_pos, int start, int end);
void CrabsPos(int index, int X_pos, int Y_pos, int start, int end);
void DisappearingTilesd(int index, int X_position, int Y_position, int delay);
void draw_enemies();
void area2();
void area3();
void DrawAnimTiles();
void DrawDisappearingTiles();

//Textures and Variables
Texture CoinTex;
Texture RedCoinTx;
Texture SpikeTex;
Texture vertical_tile_R;
Texture vertical_tile_L;
Texture TilesTx;
Texture TileTx2;
Texture SpikeTex2;
Texture ExplosionTx;
bool CreditClosed = true;

// main function
int main()
{
    leaderBoard.clear();
    RenderWindow Menu(VideoMode(1200, 760), "Sonic", Style::None);
    /// leaderboard

    Font font;
    font.loadFromFile("Assets/EvilEmpire-4BBVK.ttf");

    Text LDNames[10];
    Text scores[10];

    fa(i, 0, 10)
    {
        LDNames[i].setFont(font);
        scores[i].setFont(font);

        LDNames[i].setFillColor(Color::White);
        scores[i].setFillColor(Color::White);
    }


    string Sscore;
    int Iscore;
    int i;

    // the music of playgound
    Music BackgroundMusic;
    BackgroundMusic.openFromFile("Assets/Sounds/05-Labyrinth-Zone.ogg");
    BackgroundMusic.setVolume(50);
    BackgroundMusic.setLoop(true);

    /// Loading tex
    Texture loadingMenuTex;
    loadingMenuTex.loadFromFile("Assets/Textures/loading.png");
    Sprite loadingMenuSprite(loadingMenuTex);
    Menu.clear();
    Menu.draw(loadingMenuSprite);
    Menu.display();
    //Settings choice

    //Leaderboard
    Texture LeaderBackgroundTex;
    LeaderBackgroundTex.loadFromFile("Assets/Textures/leaderboard.png");
    Sprite leaderSprite;
    leaderSprite.setTexture(LeaderBackgroundTex);
    leaderSprite.setOrigin(0, 0);
    leaderSprite.setPosition(-1200, 0);
    bool LeaderClosed = true;
    //Credits
    Texture CreditBackgroundTex;
    CreditBackgroundTex.loadFromFile("Assets/Textures/credits.png");
    Sprite creditSprite;
    creditSprite.setTexture(CreditBackgroundTex);
    creditSprite.setOrigin(0, 0);
    creditSprite.setPosition(-1200, 0);

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
    SettingsBackgroundSprite.setOrigin(0, 0);
    SettingsBackgroundSprite.setPosition(Vector2f(-1200, 0));
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
    bool SBackAnim = true;

    // music slider components
    CircleShape slider(30);
    slider.setFillColor(Color::Blue);
    slider.setOrigin(30, 30);
    slider.setPosition(563, 250);
    slider.setOutlineThickness(10);
    slider.setOutlineColor(Color::Black);
    BackgroundMusic.setVolume(0);

    double vloumePercentage;
    bool selected = false;


    //Settings Music button
    CircleShape MusicCircle;
    MusicCircle.setFillColor(Color::White);
    MusicCircle.setRadius(29.f);
    MusicCircle.setPosition(620, 240);
    bool MusicOn = true;
    int ButtonDelay = 0;
    bool SettingStopAnim = false;

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
    leaderbackSprite.setScale(0.7f, 0.7f);
    leaderbackSprite.setTexture(backButtonTex);
    RectangleShape leaderbackButton;
    leaderbackButton.setSize(Vector2f(150, 50));
    leaderbackButton.setPosition(50, 700);
    bool leaderbackIsVisible = false;
    bool LeaderStopAnim = false;
    bool LBackAnim = true;
    //Credit button
    Sprite creditBarSprite;
    creditBarSprite.setTexture(BarTex);
    creditBarSprite.setScale(0.12f, 0.12f);
    creditBarSprite.setPosition(160, 500);
    bool creditIsPlayed = false;
    Text CreditText;
    CreditText.setFont(EvilEmpire);
    CreditText.setString("Credits");
    CreditText.setFillColor(Color(14, 24, 95));
    CreditText.setCharacterSize(50);
    CreditText.setPosition(210, 593);
    //Credit back button
    Sprite creditbackSprite;
    creditbackSprite.setPosition(43, 716);
    creditbackSprite.setScale(0.7, 0.7);
    creditbackSprite.setTexture(backButtonTex);
    RectangleShape creditbackButton;
    creditbackButton.setSize(Vector2f(150, 50));
    creditbackButton.setPosition(50, 700);
    bool creditbackIsVisible = false;
    bool CreditStopAnim = false;
    bool CBackAnim = true;
    //Exit button
    Sprite ExitBarSprite;
    ExitBarSprite.setTexture(BarTex);
    ExitBarSprite.setScale(0.12f, 0.12f);
    ExitBarSprite.setPosition(160, 500);
    bool exitIsPlayed = false;
    bool Exit = false;
    int ExitDelay = 300;
    bool pressable = false;
    Text ExitText;
    ExitText.setFont(EvilEmpire);
    ExitText.setString("Exit");
    ExitText.setFillColor(Color(14, 24, 95));
    ExitText.setCharacterSize(50);
    ExitText.setPosition(240, 693);

    Text LDName;
    LDName.setFont(font);
    LDName.setFillColor(Color::Yellow);
    LDName.setCharacterSize(50);
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
    MenuMusic.setVolume(0);
    MenuMusic.setLoop(true);
    MenuMusic.play();

    //Keyboard Selection
    int selection = 0;
    bool keyHold = false;

    bool start = false;

    //Taking player name
    string playerInput;
    Text playerText;
    playerText.setPosition(320, 350);
    playerText.setCharacterSize(80);
    playerText.setFont(EvilEmpire);
    playerText.setFillColor(sf::Color::White);
    bool canWrite = false;

    Texture PlayerNameTx;
    PlayerNameTx.loadFromFile("Assets/Textures/PlayerName.png");
    Sprite PlayerName;
    PlayerName.setTexture(PlayerNameTx);
    BackgroundMusic.play();

    loadLDFromFile();
    while (Menu.isOpen())
    {
        Event menuEvent;
        while (Menu.pollEvent(menuEvent))
        {
            if (canWrite) {
                if (menuEvent.type == Event::TextEntered) {
                    if (Keyboard::isKeyPressed(Keyboard::Backspace) && !playerInput.empty())
                    {
                        playerInput.pop_back();
                        playerText.setString(playerInput);
                    }
                    else if (menuEvent.text.unicode >= 65 && menuEvent.text.unicode < 128)
                    {
                        playerInput += menuEvent.text.unicode;
                        playerText.setString(playerInput);
                    }

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter) && playerInput.size() > 1)
                {
                    Menu.close();
                    start = true;
                    MenuMusic.stop();
                }
            }

            if (menuEvent.type == Event::Closed)
            {
                Menu.close();
                MenuMusic.stop();
            }
        }
        //Keyboard controller

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if (!keyHold)
            {
                selection++;
            }
            selection %= 6;
            keyHold = true;
        }
        else if (menuEvent.type == Event::KeyReleased)
        {
            keyHold = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if (!keyHold)
            {
                selection--;
            }
            if (selection <= 0)
                selection = 5;
            keyHold = true;
        }
        else if (menuEvent.type == Event::KeyReleased)
        {
            keyHold = false;
        }

        multimap<int, string>::iterator it;

        //Press on leaderboard
        if (Sensor.getGlobalBounds().intersects(leaderBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed && CreditClosed && LeaderClosed && !canWrite
            || selection == 3 && Keyboard::isKeyPressed(Keyboard::Enter) && SettingsClosed && CreditClosed && LeaderClosed && !canWrite) {
            LeaderClosed = false;
            LeaderStopAnim = false;
            leaderSprite.setPosition(-1200, 0);


            if (!leaderBoard.empty()) {
                for (i = 0, it = leaderBoard.begin(); it != leaderBoard.end() && (i < leaderBoard.size()); it++, i++)
                {
                    if (i >= 10)
                        break;
                    LDNames[i].setString(it->second);
                    Iscore = (it->first);
                    Sscore = to_string(Iscore);
                    scores[i].setString(Sscore);
                }
                cout << "Done!" << endl;
            }
            else
                cout << "leaderBoard is empty" << endl;
        }

        //Starting game
        if (Sensor.getGlobalBounds().intersects(startBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed && LeaderClosed && CreditClosed && !canWrite
            || selection == 1 && Keyboard::isKeyPressed(Keyboard::Enter) && SettingsClosed && CreditClosed && LeaderClosed && !canWrite) {
            canWrite = true;
        }
        //Press on settings

        if (Sensor.getGlobalBounds().intersects(settingsBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed && LeaderClosed && CreditClosed && !canWrite
            || selection == 2 && Keyboard::isKeyPressed(Keyboard::Enter) && SettingsClosed && CreditClosed && LeaderClosed && !canWrite) {
            SettingsClosed = false;
            SettingStopAnim = false;
            SettingsBackgroundSprite.setPosition(-1200, 0);
        }

        // slider functionality
        if (!SettingsClosed) {
            if (Sensor.getGlobalBounds().intersects(slider.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
                selected = true;
            if (!(Mouse::isButtonPressed(Mouse::Left)))
                selected = false;

            if (selected)
            {
                if (!(Sensor.getPosition().x <= 563 || Sensor.getPosition().x >= 863))
                {
                    slider.setPosition(Sensor.getPosition().x, slider.getPosition().y);
                    vloumePercentage = (slider.getPosition().x - 563) / (863 - 563) * 100;
                    if (vloumePercentage <= 5)
                        vloumePercentage = 0;
                    BackgroundMusic.setVolume(vloumePercentage);
                }
            }
        }

        //Press on credits
        if (Sensor.getGlobalBounds().intersects(creditBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed && LeaderClosed && CreditClosed && !canWrite
            || selection == 4 && Keyboard::isKeyPressed(Keyboard::Enter) && SettingsClosed && CreditClosed && LeaderClosed && !canWrite)
        {
            CreditClosed = false;
            CreditStopAnim = false;
            creditSprite.setPosition(-1200, 0);
        }
        //Press on Exit
        if ((Sensor.getGlobalBounds().intersects(ExitBarSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && SettingsClosed && LeaderClosed && CreditClosed) && pressable && !canWrite
            || selection == 5 && Keyboard::isKeyPressed(Keyboard::Enter) && SettingsClosed && CreditClosed && LeaderClosed && pressable && !canWrite) {
            MenuMusic.stop();
            Menu.close();
            Exit = true;
        }
        if (!pressable) {
            if (ExitDelay <= 0) pressable = true;
            else ExitDelay--;
        }

        //credit animation
        if (creditSprite.getPosition().x >= -4) {
            CreditStopAnim = true;
            if (creditSprite.getPosition().x == -3) creditSprite.move(3, 0);
        }
        if (!CreditStopAnim && !CreditClosed) creditSprite.move(7, 0);
        if (creditSprite.getPosition().x <= -1200) CBackAnim = false;

        if (CBackAnim && CreditClosed) creditSprite.move(-7, 0);


        // setting animation 
        if (SettingsBackgroundSprite.getPosition().x >= -4) {
            SettingStopAnim = true;
            if (SettingsBackgroundSprite.getPosition().x == -3) SettingsBackgroundSprite.move(3, 0);
        }

        if (!SettingStopAnim && !SettingsClosed) SettingsBackgroundSprite.move(7, 0);

        if (SettingsBackgroundSprite.getPosition().x <= -1200) SBackAnim = false;

        if (SBackAnim && SettingsClosed) SettingsBackgroundSprite.move(-7, 0);
        //leaderboard animation
        if (leaderSprite.getPosition().x >= -4) {
            LeaderStopAnim = true;
            if (leaderSprite.getPosition().x == -3) leaderSprite.move(3, 0);
        }
        if (!LeaderStopAnim && !LeaderClosed) leaderSprite.move(7, 0);
        if (leaderSprite.getPosition().x <= -1200) LBackAnim = false;
        if (LBackAnim && LeaderClosed) leaderSprite.move(-7, 0);

        //Settings Back button
        if (Sensor.getGlobalBounds().intersects(backButton.getGlobalBounds()) && !SettingsClosed || Keyboard::isKeyPressed(Keyboard::Escape) && !SettingsClosed) {
            backIsVisible = true;
            if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Escape)) {
                SettingsClosed = true;
                pressable = false;
                ExitDelay = 300;
                SBackAnim = true;

            }
        }
        else backIsVisible = false;
        //Leader back button
        if (Sensor.getGlobalBounds().intersects(leaderbackButton.getGlobalBounds()) && !LeaderClosed || Keyboard::isKeyPressed(Keyboard::Escape) && !LeaderClosed) {
            leaderbackIsVisible = true;
            if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Escape)) {
                LeaderClosed = true;
                pressable = false;
                ExitDelay = 300;
                LBackAnim = true;
            }
        }
        else leaderbackIsVisible = false;
        //Credit back button

        if (Sensor.getGlobalBounds().intersects(creditbackButton.getGlobalBounds()) && !CreditClosed || Keyboard::isKeyPressed(Keyboard::Escape) && !CreditClosed) {
            creditbackIsVisible = true;
            if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Escape)) {
                CreditClosed = true;
                pressable = false;
                ExitDelay = 300;
                CBackAnim = true;

            }
        }
        else creditbackIsVisible = false;
        //touch music circle
        if (Sensor.getGlobalBounds().intersects(MusicCircle.getGlobalBounds()) && !SettingsClosed && Mouse::isButtonPressed(Mouse::Left) && ButtonDelay >= 60) {
            if (MusicOn) {
                MusicOn = false;
                MenuMusic.stop();
            }
            else {
                MusicOn = true;
                MenuMusic.play();
            }
            ButtonDelay = 0;
        }
        if (ButtonDelay <= 60) ButtonDelay++;

        // Slider music controller
        if (Sensor.getGlobalBounds().intersects(MusicCircle.getGlobalBounds()) && !SettingsClosed && Mouse::isButtonPressed(Mouse::Left) && ButtonDelay >= 60) {
            if (MusicOn) {
                MusicOn = false;
                MenuMusic.stop();
            }
            else {
                MusicOn = true;
                MenuMusic.play();
            }
            ButtonDelay = 0;
        }
        //Sensor pos
        Sensor.setPosition(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y);
        //Start
        if (Sensor.getGlobalBounds().intersects(startBarSprite.getGlobalBounds()) || selection == 1) {
            startBarSprite.setColor(Color(45, 49, 250));
            StartText.setFillColor(Color(255, 255, 255));
            startBarSprite.setScale(0.19f, 0.155f);
            startBarSprite.setPosition(145, 295);
            if (!startIsPlayed && SettingsClosed && LeaderClosed && CreditClosed && !canWrite) {
                ButtonClickSound.play();
                startIsPlayed = true;
            }
        }
        else {
            StartText.setFillColor(Color(14, 24, 95));
            startBarSprite.setColor(Color(255, 255, 255));
            startBarSprite.setScale(0.16f, 0.12f);
            startBarSprite.setPosition(160, 300);
            startIsPlayed = false;
        }
        //Settings
        if (Sensor.getGlobalBounds().intersects(settingsBarSprite.getGlobalBounds()) || selection == 2) {
            SettingsText.setFillColor(Color::White);
            settingsBarSprite.setScale(0.19f, 0.155f);
            settingsBarSprite.setColor(Color(45, 49, 250));
            settingsBarSprite.setPosition(145, 395);
            if (!settingsIsPlayed && SettingsClosed && LeaderClosed && CreditClosed && !canWrite) {
                ButtonClickSound.play();
                settingsIsPlayed = true;
            }

        }
        else {
            SettingsText.setFillColor(Color(14, 24, 95));
            settingsBarSprite.setScale(0.16f, 0.12f);
            settingsBarSprite.setColor(Color(255, 255, 255));
            settingsBarSprite.setPosition(160, 400);
            settingsIsPlayed = false;
        }
        //Leaderboard
        if (Sensor.getGlobalBounds().intersects(leaderBarSprite.getGlobalBounds()) || selection == 3) {
            LeaderText.setFillColor(Color::White);
            leaderBarSprite.setScale(0.27f, 0.145f);
            leaderBarSprite.setColor(Color(45, 49, 250));
            leaderBarSprite.setPosition(120, 495);
            if (!leaderIsPlayed && SettingsClosed && LeaderClosed && CreditClosed && !canWrite) {
                ButtonClickSound.play();
                leaderIsPlayed = true;
            }

        }
        else {
            LeaderText.setFillColor(Color(14, 24, 95));
            leaderBarSprite.setScale(0.22f, 0.12f);
            leaderBarSprite.setColor(Color(255, 255, 255));
            leaderBarSprite.setPosition(125, 500);
            leaderIsPlayed = false;
        }
        //Credits

        if (Sensor.getGlobalBounds().intersects(creditBarSprite.getGlobalBounds()) || selection == 4) {
            CreditText.setFillColor(Color::White);
            creditBarSprite.setScale(0.19f, 0.155f);
            creditBarSprite.setColor(Color(45, 49, 250));
            creditBarSprite.setPosition(145, 595);
            if (!creditIsPlayed && SettingsClosed && LeaderClosed && CreditClosed && !canWrite) {
                ButtonClickSound.play();
                creditIsPlayed = true;
            }

        }
        else {
            CreditText.setFillColor(Color(14, 24, 95));
            creditBarSprite.setScale(0.16f, 0.12f);
            creditBarSprite.setColor(Color(255, 255, 255));
            creditBarSprite.setPosition(160, 600);
            creditIsPlayed = false;
        }
        //Exit
        if (Sensor.getGlobalBounds().intersects(ExitBarSprite.getGlobalBounds()) || selection == 5) {
            ExitText.setFillColor(Color::White);
            ExitBarSprite.setScale(0.17f, 0.135f);
            ExitBarSprite.setColor(Color(45, 49, 250));
            ExitBarSprite.setPosition(145, 695);
            if (!exitIsPlayed && SettingsClosed && LeaderClosed && CreditClosed && !canWrite) {
                ButtonClickSound.play();
                exitIsPlayed = true;
            }

        }
        else {
            ExitText.setFillColor(Color(14, 24, 95));
            ExitBarSprite.setScale(0.16f, 0.12f);
            ExitBarSprite.setColor(Color(255, 255, 255));
            ExitBarSprite.setPosition(160, 700);
            exitIsPlayed = false;
        }


        Menu.clear();

        Menu.draw(MenuBackgroundSprite);
        Menu.draw(startBarSprite);
        Menu.draw(settingsBarSprite);
        Menu.draw(StartText);
        Menu.draw(SettingsText);
        Menu.draw(leaderBarSprite);
        Menu.draw(LeaderText);
        Menu.draw(creditBarSprite);
        Menu.draw(CreditText);
        Menu.draw(ExitBarSprite);
        Menu.draw(ExitText);

        if (canWrite)
        {
            Menu.draw(PlayerName);
        }
        Menu.draw(playerText);
        if (!LeaderClosed) {
            Menu.draw(leaderSprite);
            if (LeaderStopAnim)
            {
                fa(i, 0, leaderBoard.size())
                {
                    if (i >= 10)
                        break;
                    LDNames[i].setPosition(295, 172 + i * 52);
                    LDNames[i].setCharacterSize(22);

                    scores[i].setPosition(734, 172 + i * 52);
                    scores[i].setCharacterSize(22);

                    Menu.draw(LDNames[i]);
                    Menu.draw(scores[i]);
                }
                if (leaderbackIsVisible) {
                    Menu.draw(leaderbackSprite);
                }
            }
        }
        if (!CreditClosed) {
            Menu.draw(creditSprite);
            if (creditbackIsVisible) Menu.draw(creditbackSprite);
        }
        if (SBackAnim) Menu.draw(SettingsBackgroundSprite);
        if (LBackAnim) Menu.draw(leaderSprite);
        if (CBackAnim)Menu.draw(creditSprite);

        if (!SettingsClosed) {
            Menu.draw(SettingsBackgroundSprite);
            if (backIsVisible) Menu.draw(backSprite);
            if (SettingStopAnim) Menu.draw(slider);
        }
        Menu.display();
    }
    // rendering window
    if (start && !Exit) {
        srand(time(0));
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        // rendering window
        RenderWindow window(VideoMode(1200, 760), "Sonic!");
        window.setFramerateLimit(60);
        //Loading Screen
        Texture loadingTex;
        loadingTex.loadFromFile("Assets/Textures/loading.png");
        Sprite loadingSprite(loadingTex);
        window.clear();
        window.draw(loadingSprite);
        window.display();
        /// map
           // map texture
        Texture MapTx;
        MapTx.loadFromFile("Assets/Textures/Map.png");
        Texture MapTx2;
        MapTx2.loadFromFile("Assets/Textures/Map2.png");
        // map player
        Sprite Map;
        Map.setTexture(MapTx);
        Map.setScale(1, 1.013);
        Sprite Map2;
        Map2.setTexture(MapTx2);
        Map2.setScale(1, 1.013);
        Map2.setPosition(17000, 0);
        //
        bool Fade2Start = false, Level2AnimStart = false, Fade1End = false, Level2Start = false;
        int fadeOp = 0;
        Texture FadeTx;
        FadeTx.loadFromFile("Assets/Textures/Fade.png");
        Sprite FadeRect;
        FadeRect.setTexture(FadeTx);
        FadeRect.setPosition(14800, 0);
        FadeRect.setColor(Color(0, 0, 0, fadeOp));

        //Coin texture
        CoinTex.loadFromFile("Assets/Textures/Some Sprites.png");
        //Redcoin Texture
        RedCoinTx.loadFromFile("Assets/Textures/Some-Sprites-red-coin.png");
        //Jumppad Texture
        Texture JumppadTx;
        JumppadTx.loadFromFile("Assets/Textures/Some Sprites2.png");
        //Enemy texture
        Texture Enemies;
        Enemies.loadFromFile("Assets/Textures/Enemies.png");
        //Spike texture
        SpikeTex.loadFromFile("Assets/Textures/Spike.png");
        //Tiles texture
        TilesTx.loadFromFile("Assets/Textures/Wall2.png");
        TileTx2.loadFromFile("Assets/Textures/UpsideDownWall.png");
        SpikeTex2.loadFromFile("Assets/Textures/UpsidedownSpike.png");
        vertical_tile_R.loadFromFile("Assets/Textures/Vertical_tile_R.png");
        vertical_tile_L.loadFromFile("Assets/Textures/Vertical_tile_L.png");
        //Pause Menu
        Texture PauseMenuTx;
        PauseMenuTx.loadFromFile("Assets/Textures/Pause_Menu.png");
        Sprite pauseMenu;
        pauseMenu.setTexture(PauseMenuTx);
        pauseMenu.setScale(0, 0);
        //
        //Gameover
        Texture GameoverTx;
        GameoverTx.loadFromFile("Assets/Textures/game-over.png");
        Sprite Gameover;
        Gameover.setTexture(GameoverTx);
        Gameover.setScale(0, 0);
        View GameoverCamera(FloatRect(0, 0, 1200, 720));
        //
        //Level Passed
        Texture LevelPassedTx;
        LevelPassedTx.loadFromFile("Assets/Textures/Lvl1Passed.png");
        Sprite LevelPassed;
        LevelPassed.setTexture(LevelPassedTx);
        LevelPassed.setPosition(14808, 0);
        LevelPassed.setScale(0, 0);
        Texture Level2PassedTx;
        Level2PassedTx.loadFromFile("Assets/Textures/Lvl2Passed.png");
        Sprite Level2Passed;
        Level2Passed.setTexture(Level2PassedTx);
        Level2Passed.setPosition(35510, 0);
        Level2Passed.setScale(0, 0);

        bool paused = false;
        int pauseDelay = 0;
        int Level = 1;

        //BackgroundShip
        Texture ShipTx;
        ShipTx.loadFromFile("Assets/Textures/Tyara.png");

        fa(i, 0, 3) {
            floatingShips[i].ShipSprite.setTexture(ShipTx);
            floatingShips[i].ShipSprite.setPosition(5000 * i, 100 + (i * 50));
            floatingShips[i].ShipSprite.setScale(0.4, 0.4);
        }

        //Boss
        BossSt Boss;
        Boss.BossTx.loadFromFile("Assets/Textures/Boss.png");
        Boss.BossSprite.setTexture(Boss.BossTx);
        Boss.BossSprite.setTextureRect(IntRect(Boss.TexNumber * 100, 800, 100, 64));
        Boss.BossSprite.setPosition(15800, 470);
        Boss.HitBox.setPosition(15525, 508);
        Boss.HitBox.setSize(Vector2f(58 * 2.8, 29 * 2.8));
        Boss.BossSprite.setScale(2.8, 2.8);
        Boss.HealthBarBG.setSize(Vector2f(610.f, 30.f));
        Boss.HealthBarBG.setFillColor(Color::Black);
        Boss.HealthBarRect.setSize(Vector2f(60.f, 20.f));
        Boss.HealthBarRect.setScale(0, 0);
        Boss.HealthBarBG.setScale(0, 0);
        Boss.HealthBarRect.setFillColor(Color::Red);
        Boss.BossFaceTx.loadFromFile("Assets/Textures/BossFace.png");
        Boss.BossFaceSprite.setTexture(Boss.BossFaceTx);
        Boss.BossFaceSprite.setScale(0, 0);
        Boss.HealthBarBG.setPosition(15195, 30);
        Boss.HealthBarRect.setPosition(15200, 35);
        Boss.BossFaceSprite.setPosition(15090.92, 24);

        ExplosionTx.loadFromFile("Assets/Textures/Explosion.png");
        int ExplosionsSpawned = 0, SpawnCounter = 0;
        fa(i, 0, 40) {
            Explosion[i].ExplosionSprite.setTexture(ExplosionTx);
            Explosion[i].ExplosionSprite.setTextureRect(IntRect(Explosion[i].colomnTxNum * 130, Explosion[i].rowTxNum * 114, 130, 114));
            Explosion[i].ExplosionSprite.setScale(0, 0);
        }

        WreckingBall wreckingBall;
        wreckingBall.WreckingChainTx.loadFromFile("Assets/Textures/BossWreckingBall.png");
        wreckingBall.WreckingChainSprite.setTexture(wreckingBall.WreckingChainTx);
        wreckingBall.WreckingChainSprite.setTextureRect(IntRect(38, 30, 32, 128));
        wreckingBall.WreckingChainSprite.setScale(1.5, 1.5);
        wreckingBall.WreckingChainSprite.setOrigin(16, 0);
        wreckingBall.WreckingChainSprite.setPosition(0, -800);
        wreckingBall.WreckingChainSprite.rotate(290);

        wreckingBall.WreckingBallTx.loadFromFile("Assets/Textures/BossWreckingBall.png");
        wreckingBall.WreckingBallSprite.setTexture(wreckingBall.WreckingBallTx);
        wreckingBall.WreckingBallSprite.setTextureRect(IntRect(6, 165, 96, 96));
        wreckingBall.WreckingBallSprite.setScale(1.5, 1.5);
        wreckingBall.WreckingBallSprite.setOrigin(48, -128);
        wreckingBall.WreckingBallSprite.setPosition(0, -800);
        wreckingBall.WreckingBallSprite.rotate(290);
        wreckingBall.HitBox.setRadius(57);
        wreckingBall.HitBox.setOrigin(57, -203);
        wreckingBall.HitBox.setPosition(0, -800);
        wreckingBall.HitBox.rotate(290);

        //Sky Bullet
        Texture SkyBulletTx;
        SkyBulletTx.loadFromFile("Assets/Textures/SkyBullet.png");
        int BulletsSpawnDelay = 0, BulletDelay = 0, BulletsSpawned = 0;
        bool SpawnStart = false, BulletsPositioned = false;
        fa(i, 0, 5) {
            skyBullets[i].SkyBulletsSprite.setTexture(SkyBulletTx);
            skyBullets[i].SkyBulletsSprite.setTextureRect(IntRect(skyBullets[i].TexNumber * 114, 0, 114, 227));
            skyBullets[i].SkyBulletsSprite.setScale(0.8, 0.8);
            skyBullets[i].SkyBulletsSprite.setPosition(-500, -500);
            skyBullets[i].BulletColl.setSize(Vector2f(24, 108.8));
        }

        //// sonic player
        Player sonic;
        // sonic texture
        sonic.PlayerTex.loadFromFile("Assets/Textures/Sonic-Character.png");
        sonic.PlayerSprite.setTexture(sonic.PlayerTex);
        // sonic sprite
        sonic.PlayerSprite.setTextureRect(IntRect(sonic.IdleTexNumber * 59.1578, 0, 59.1578, 60));
        sonic.PlayerColl.setSize(Vector2f(55.f, 80.f));
        sonic.RightColl.setSize(Vector2f(27.f, 80.f));
        sonic.LeftColl.setSize(Vector2f(28.f, 80.f));
        sonic.PlayerSprite.setPosition(200, 300);
        //sonic.PlayerSprite.setPosition(14500, 300);
        sonic.PlayerColl.setPosition(0, -12000);
        sonic.PlayerSprite.setScale(2.5, 2.5);
        //

        ///Jumppad Setting Texture
        fa(i, 0, 30) {
            jumppad[i].JumppadSprite.setTexture(JumppadTx);
            jumppad[i].JumppadSprite.setTextureRect(IntRect(jumppad[i].Texnumber * 80, 543, 80, 66));
        }

        ///Floating Tiles Setting Texture
        fa(i, 0, 60) {
            tiles[i].TileSprite.setTexture(TilesTx);
            tiles[i].TileSprite.setScale(1.3, 1.3);
            tiles[i].TileColl.setSize(Vector2f(298.9f, 1.f));
            tiles[i].LowerTileColl.setSize(Vector2f(298.9f, 1.f));
            //329  60
        }

        //
        // vertical Walls setting 

        // for left;
        fa(i, 0, 10) {
            Vertical_tiles_left[i].Vertical_Tiles_sprite.setTexture(vertical_tile_L);
            Vertical_tiles_left[i].Vertical_Tiles_sprite.setTextureRect(IntRect(0, 0, 46, 253));
            Vertical_tiles_right[i].Vertical_Tiles_sprite.setTexture(vertical_tile_R);
            Vertical_tiles_right[i].Vertical_Tiles_sprite.setTextureRect(IntRect(0, 0, 46, 253));
            if (i % 2 != 0) {
                Vertical_tiles_left[i].tilecole.setSize(Vector2f(1.f, 298.9f));
                Vertical_tiles_right[i].tilecole.setSize(Vector2f(1.f, 298.9f));
            }
        }

        ///Enemies Setting Texture
        fa(i, 0, 20) {
            Worms[i].EnemySprite.setTexture(Enemies);
            Worms[i].EnemyColl.setSize(Vector2f(110.f, 50.f));
            Worms[i].EnemyColl.setScale(Vector2f(1, 1));
            Worms[i].EnemySprite.setTextureRect(IntRect(Worms[i].TexNumber * 54, 345, 54, 29.2));
            Worms[i].EnemySprite.setScale(2.5f, 2.5f);

            Crabs[i].EnemySprite.setTexture(Enemies);
            Crabs[i].EnemyColl.setSize(Vector2f(100.f, 60.f));
            Crabs[i].EnemyColl.setScale(Vector2f(1, 1));
            Crabs[i].EnemySprite.setTextureRect(IntRect(Crabs[i].TexNumber * 47, 411, 47, 30));
            Crabs[i].EnemySprite.setScale(2.5f, 2.5f);

            Enemy3[i].EnemySprite.setTexture(Enemies);
            Enemy3[i].EnemyColl.setSize(Vector2f(90.f, 60.f));
            Enemy3[i].EnemyColl.setScale(Vector2f(1, 1));
            Enemy3[i].EnemySprite.setTextureRect(IntRect(Enemy3[i].TexNumber * 42.75, 268, 42.75, 30));
            Enemy3[i].EnemySprite.setScale(2.5f, 2.5f);
        }
        //

        //Spikes system
        fa(i, 0, 200) {
            spikes[i].SpikeSprite.setTexture(SpikeTex);
            spikes[i].SpikeSprite.setTextureRect(IntRect(0, 0, 142, 163));
            spikes[i].SpikeSprite.setScale(0.5f, 0.5f);
        }

        //score
        Font font;
        font.loadFromFile("Assets/EvilEmpire-4BBVK.ttf");
        Text FinalScore;
        FinalScore.setFont(font);
        FinalScore.setFillColor(Color::Yellow);
        FinalScore.setCharacterSize(0);
        FinalScore.setPosition(737, 195);
        Text text;
        text.setFont(font);
        text.setString("Score: " + std::to_string(sonic.scoreValue));
        text.setFillColor(Color::Yellow);
        text.setPosition(10, 10);
        text.setCharacterSize(35);

        Text EnemyScore;
        EnemyScore.setFont(font);
        EnemyScore.setString("+100");
        EnemyScore.setFillColor(Color::Yellow);
        EnemyScore.setCharacterSize(100);
        EnemyScore.setPosition(400, 400);
        int EnemyScoreCounter = 0;

        //health_bar
        Texture SonicFaceTx;
        SonicFaceTx.loadFromFile("Assets/Textures/sonic-blue-logo.png");
        Sprite SonicFace;
        SonicFace.setTexture(SonicFaceTx);
        SonicFace.setScale(0.12, 0.12);
        SonicFace.setPosition(-9, 680);
        Text lives;
        lives.setFont(font);
        lives.setString("x" + std::to_string(sonic.lives));
        lives.setFillColor(Color::Yellow);
        lives.setPosition(90, 700);
        lives.setCharacterSize(35);

        // the music of main menu
        Music MainMenuMusic;
        MainMenuMusic.openFromFile("Assets/Sounds/mainmenu.wav");
        //Boss Fight
        Music BossFightMusic;
        BossFightMusic.openFromFile("Assets/Sounds/Sonic-3-Final-Boss-_Big-Arms_-Remix-_Kamex__1.ogg");
        BossFightMusic.setVolume(50);
        BossFightMusic.setLoop(true);
        bool BossMusicStarted = false;
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
        //Boss damage sound
        SoundBuffer BossDamageBuffer[3];
        BossDamageBuffer[0].loadFromFile("Assets/Sounds/EggmanHit.ogg");
        BossDamageBuffer[1].loadFromFile("Assets/Sounds/EggmanHit2.ogg");
        BossDamageBuffer[2].loadFromFile("Assets/Sounds/EggmanHit3.ogg");
        Sound BossDamageSound[3];
        BossDamageSound[0].setBuffer(BossDamageBuffer[0]);
        BossDamageSound[1].setBuffer(BossDamageBuffer[1]);
        BossDamageSound[2].setBuffer(BossDamageBuffer[2]);
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
        //deathspike sound
        SoundBuffer SonicHitBuffer;
        SonicHitBuffer.loadFromFile("Assets/Sounds/Ouch.ogg");
        Sound SonicHitAudio;
        SonicHitAudio.setBuffer(SonicHitBuffer);
        //speedchute sound
        SoundBuffer RunningBuffer;
        RunningBuffer.loadFromFile("Assets/Sounds/speedchute.wav");
        Sound RunningSound;
        RunningSound.setBuffer(RunningBuffer);
        RunningSound.setVolume(30);
        // sound gameover
        SoundBuffer GameoverBuffer;
        GameoverBuffer.loadFromFile("Assets/Sounds/gameover.wav");
        Sound GameoverAudio;
        GameoverAudio.setBuffer(GameoverBuffer);

        draw_vertical_tiles();
        draw_enemies();
        draw_spikes();
        Draw_jumppad();
        draw_tiles();
        coinPos();
        area2();


        tiles[10].TileSprite.setScale(0.7, 1);
        tiles[10].TileColl.setSize(Vector2f(137.1f, 1.f));
        tiles[10].LowerTileColl.setScale(0, 0);
        tiles[10].TileColl.setPosition(tiles[10].TileSprite.getPosition().x + 25, tiles[10].TileSprite.getPosition().y - 15);
        tiles[11].TileSprite.setScale(0.7, 1);
        tiles[11].TileColl.setSize(Vector2f(137.1f, 1.f));
        tiles[11].LowerTileColl.setScale(0, 0);
        tiles[11].TileColl.setPosition(tiles[11].TileSprite.getPosition().x + 25, tiles[11].TileSprite.getPosition().y - 15);

        //level 2
        fa(i, 0, 2) {
            HAnimTiles[i].TileSprite.setTexture(TilesTx);
            HAnimTiles[i].TileSprite.setScale(1.3, 1.3);
            HAnimTiles[i].TileColl.setSize(Vector2f(298.9f, 1.f));

        }
        fa(i, 0, 23)
        {
            VAnimTiles[i].TileSprite.setTexture(TilesTx);
            VAnimTiles[i].TileSprite.setScale(1.3, 1.3);
            VAnimTiles[i].TileColl.setSize(Vector2f(298.9f, 1.f));
        }

        fa(i, 0, 10) {
            DisappearingTiles[i].TileSprite.setTexture(TilesTx);
            DisappearingTiles[i].TileSprite.setScale(1.3, 1.3);
            DisappearingTiles[i].TileColl.setSize(Vector2f(298.9f, 1.f));
        }
        DrawDisappearingTiles();

        fa(i, 0, 100) {
            animespikes2[i].SpikeSprite2.setTexture(SpikeTex2);
            animespikes2[i].SpikeSprite2.setTextureRect(IntRect(0, 0, 142, 163));
            animespikes2[i].SpikeSprite2.setScale(0.5f, 0.5f);
        }
        DrawAnimTiles();
        area3();

        /// ground rectangle shape
        RectangleShape ground(Vector2f(50000, 70)); ground.setScale(1, 1); ground.setPosition(0, 640);
        //

        // view camera
        //View camera(FloatRect(14300, 0, 1200, 760));
        View camera(FloatRect(0, 0, 1200, 760));
        window.setView(camera);
        //

        /// game loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                if (pauseDelay == 0) {
                    if (!paused) paused = true;
                    else paused = false;
                    pauseDelay = 50;
                }
            }

            /// UPDATE
            if (pauseDelay > 0) pauseDelay--;
            if (!paused) pauseMenu.setScale(0, 0);


            //Delays and coins
            if (sonic.lives > 0 && !paused) {
                if (sonic.TexDelay <= 3) sonic.TexDelay++;
                if (sonic.IdleDelay <= 10) sonic.IdleDelay++;
                fa(i, 0, 420) {
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
                //Red Coins
                fa(i, 0, 6) {
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

                //Spikes System
                fa(i, 0, 180) {
                    if (sonic.hitCounter == -1) {
                        if (spikes[i].SpikeSprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                            sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > spikes[i].SpikeSprite.getPosition().x) {
                                sonic.hitRight = true;
                                sonic.RightTexNumber = 4;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                            }
                            else {
                                sonic.hitLeft = true;
                                sonic.LeftTexNumber = 0;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                            }
                            sonic.hitCounter = 300;
                            sonic.Velocity.y = 5;
                            sonic.HitTxDelay = 0;
                            sonic.PlayerSprite.move(0, -10);
                            sonic.HitCounter2 = 0;
                            SpikeDeathAudio.play();
                        }
                    }
                    if (i < 76) {
                        if (sonic.hitCounter == -1) {
                            if (spikes2[i].SpikeSprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                                sonic.HitAbove = true;
                                sonic.lives--;
                                if (!sonic.OnVTile) {
                                    if (sonic.PlayerSprite.getPosition().x > spikes2[i].SpikeSprite.getPosition().x) {
                                        sonic.hitRight = true;
                                        sonic.RightTexNumber = 4;
                                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                                    }
                                    else {
                                        sonic.hitLeft = true;
                                        sonic.LeftTexNumber = 0;
                                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                                    }
                                    sonic.Velocity.y = -7;
                                }
                                sonic.Velocity.y = -7;
                                sonic.PlayerSprite.move(0, 10);
                                sonic.hitCounter = 300;
                                sonic.HitTxDelay = 0;
                                sonic.HitCounter2 = 0;
                                SpikeDeathAudio.play();
                            }
                        }
                    }
                }

                fa(i, 0, 100) {
                    if (sonic.hitCounter == -1) {
                        if (animespikes2[i].SpikeSprite2.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                            sonic.HitAbove = true;
                            sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > animespikes2[i].SpikeSprite2.getPosition().x) sonic.hitRight = true;
                            else sonic.hitLeft = true;
                            sonic.hitCounter = 300;
                            sonic.HitCounter2 = 0;
                            sonic.Velocity.y = -7;
                            SpikeDeathAudio.play();
                        }
                    }
                    if (animespikes2[i].Direction) animespikes2[i].SpikeSprite2.move(0, 5);
                    else animespikes2[i].SpikeSprite2.move(0, -5);
                    if (animespikes2[i].SpikeSprite2.getPosition().y >= animespikes2[i].yEnd && animespikes2[i].Direction) {
                        animespikes2[i].Direction = false;
                    }
                    else if (animespikes2[i].SpikeSprite2.getPosition().y <= animespikes2[i].yStart && !animespikes2[i].Direction) {
                        animespikes2[i].Direction = true;
                    }
                }

                //Hit Counter
                if (sonic.hitCounter > -1) {
                    sonic.hitCounter--;
                    sonic.PlayerSprite.setColor(Color(255, 0, 0, 220));
                }
                else if (sonic.hitCounter == -1) sonic.PlayerSprite.setColor(Color::White);

                //Idle Animation
                if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::Space)
                    && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up) && !sonic.hitLeft && !sonic.hitRight) {
                    sonic.txToggle = false;
                    sonic.RunningSound = false;
                    sonic.Velocity.x = 0;
                    if (sonic.IdleDelay >= 10) {
                        sonic.IdleDelay = 0;
                        if (sonic.IdleTexNumber == 7) sonic.IdleDirectionL = true;
                        else if (sonic.IdleTexNumber == 0) sonic.IdleDirectionL = false;
                        if (sonic.IdleDirectionL) sonic.IdleTexNumber--;
                        else sonic.IdleTexNumber++;
                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.IdleTexNumber * 48.75, 0 * 60, 48.75, 51));
                    }
                }


                //Moving Right
                if (!Boss.SceneStart) {
                    if ((Boss.FightStartLevel1 && sonic.PlayerSprite.getPosition().x < 15900 && !Boss.Level1FightEnd) || (Boss.FightStartLevel2 && sonic.PlayerSprite.getPosition().x < 36600) || (!Boss.FightStartLevel1 && Level == 1) || (Level == 2 && !Boss.FightStartLevel2 && Boss.Level1FightEnd)) {
                        if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && !sonic.hitLeft && !sonic.hitRight) {
                            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                                // Running Sonic Right
                                sonic.Velocity.x = 15;
                                if (!sonic.RunningSound) {
                                    RunningSound.play();
                                    sonic.RunningSound = true;
                                }
                                if (sonic.TexDelay >= 3) {
                                    sonic.RightTexNumber++;
                                    sonic.TexDelay = 0;
                                    if (sonic.RightTexNumber >= 22) sonic.RightTexNumber = 19;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.86, 1 * 60, 48.86, 51));
                                }
                            }
                            else {
                                // Walking Sonic Right
                                sonic.Velocity.x = 12;
                                if (sonic.TexDelay >= 3) {
                                    sonic.RightTexNumber++;
                                    sonic.TexDelay = 0;
                                    sonic.RightTexNumber %= 11;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.86, 1 * 60, 48.86, 51));
                                }
                            }
                        }
                    } else
                        sonic.Velocity.x = 0;
                    //Moving Left
                    if ((Boss.FightStartLevel1 && sonic.PlayerSprite.getPosition().x >= 14790 && !Level2Start) || (Boss.FightStartLevel2 && sonic.PlayerSprite.getPosition().x >= 35500) || (!Boss.FightStartLevel1 && Level == 1) || (Level == 2 && !Boss.FightStartLevel2 && Level2Start)) {
                        if ((Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Left)) && !sonic.hitLeft && !sonic.hitRight && ((sonic.PlayerSprite.getPosition().x > 20 && !Level2Start) || (Level2Start && sonic.PlayerSprite.getPosition().x > 17000))) {
                            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                                // Running Sonic Left
                                sonic.Velocity.x = -15;
                                if (!sonic.RunningSound) {
                                    RunningSound.play();
                                    sonic.RunningSound = true;
                                }
                                if (sonic.TexDelay >= 3) {
                                    sonic.LeftTexNumber--;
                                    sonic.TexDelay = 0;
                                    if (sonic.LeftTexNumber <= 0) sonic.LeftTexNumber = 3;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.86, 3 * 60, 48.86, 51));
                                }
                            }
                            else {
                                // Moving Sonic Left
                                sonic.Velocity.x = -12;
                                if (sonic.TexDelay >= 3) {
                                    sonic.LeftTexNumber--;
                                    sonic.TexDelay = 0;
                                    if (sonic.LeftTexNumber <= 12) sonic.LeftTexNumber = 22;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.86, 3 * 60, 48.86, 51));
                                }
                            }
                        }
                    }
                    else {
                        if (!Keyboard::isKeyPressed(Keyboard::D)) sonic.Velocity.x = 0;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::A) && ((sonic.PlayerSprite.getPosition().x <= 0 && !Level2Start) || (Level2Start && sonic.PlayerSprite.getPosition().x <= 17000))) sonic.Velocity.x = 0;
                }
                if (sonic.HitTxDelay <= 5) sonic.HitTxDelay++;
                //Hit Right and Left
                if ((sonic.hitLeft || sonic.hitRight || sonic.HitAbove) && sonic.HitCounter2 != 5 ) {
                    sonic.HitCounter2++;
                    sonic.hitCounter = 125;
                    if (!sonic.HitAbove)
                        sonic.Velocity.y = 5;
                    else
                        sonic.Velocity.y = -5;
                    sonic.HitTxDelay = 0;
                    sonic.PlayerSprite.move(0, -10);
                }
                else if (sonic.hitRight) {
                    if ((sonic.PlayerSprite.getPosition().x <= 15900 && Boss.FightStartLevel1 && !Boss.Level1FightEnd) || (sonic.PlayerSprite.getPosition().x <= 36600 && Boss.FightStartLevel2) || !Boss.FightStartLevel1 || (Boss.Level1FightEnd && !Boss.FightStartLevel2))
                        sonic.Velocity.x = 5;
                    if (sonic.on_ground || sonic.onTile) sonic.hitRight = false, sonic.HitAbove = false;
                    //290
                    if (sonic.HitTxDelay >= 5 && sonic.RightTexNumber > 0) {
                        sonic.RightTexNumber--;
                        sonic.HitTxDelay = 0;
                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                    }
                }
                else if (sonic.hitLeft) {
                    if ((sonic.PlayerSprite.getPosition().x > 14800 && Boss.FightStartLevel1 && !Boss.Level1FightEnd) || (sonic.PlayerSprite.getPosition().x > 35500 && Boss.FightStartLevel2) || !Boss.FightStartLevel1 || (Boss.Level1FightEnd && !Boss.FightStartLevel2))
                        sonic.Velocity.x = -5;
                    if (sonic.on_ground || sonic.onTile)  sonic.hitLeft = false, sonic.HitAbove = false;
                    //246
                    if (sonic.HitTxDelay >= 5 && sonic.LeftTexNumber < 4) {
                        sonic.LeftTexNumber++;
                        sonic.HitTxDelay = 0;
                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                    }
                }
               
                //Enemy System
                fa(i, 0, 20) {
                    if (Worms[i].TexDelay <= 8) Worms[i].TexDelay++;
                    if (Worms[i].MovingRight) {
                        Worms[i].EnemySprite.move(4, 0);
                        if (Worms[i].TexDelay >= 8) {
                            Worms[i].TexDelay = 0;
                            Worms[i].TexNumber++;
                            Worms[i].TexNumber %= 11;
                            Worms[i].EnemySprite.setTextureRect(IntRect(Worms[i].TexNumber * 58, 345, 58, 29.2));
                        }
                        if (Worms[i].EnemySprite.getPosition().x >= Worms[i].xEnd) Worms[i].MovingRight = false;
                    }
                    else {
                        Worms[i].EnemySprite.move(-4, 0);
                        if (Worms[i].TexDelay >= 8) {
                            Worms[i].TexDelay = 0;
                            Worms[i].TexNumber--;
                            if (Worms[i].TexNumber <= 0) Worms[i].TexNumber = 10;
                            Worms[i].EnemySprite.setTextureRect(IntRect(Worms[i].TexNumber * 58, 313, 58, 29.2));
                        }
                        if (Worms[i].EnemySprite.getPosition().x <= Worms[i].xStart) Worms[i].MovingRight = true;
                    }

                    if (sonic.hitCounter == -1) {
                        if (Worms[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                            if (!Worms[i].Hit) Worms[i].Hit = true;
                            else {
                                Worms[i].EnemySprite.setScale(0, 0);
                                Worms[i].EnemyColl.setScale(0, 0);
                                sonic.scoreValue += 100;
                                EnemyScore.setString("+100");
                                EnemyScore.setCharacterSize(50);
                                EnemyScore.setPosition(Worms[i].EnemyColl.getPosition().x + 60, Worms[i].EnemyColl.getPosition().y + 60);
                                EnemyScoreCounter = 100;
                            }
                            sonic.Velocity.y = 10;
                            EnemyDamageSound.play();
                        }
                        else if (Worms[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0)) {
                            if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > Worms[i].EnemySprite.getPosition().x) {
                                sonic.hitRight = true;
                                sonic.RightTexNumber = 4;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                            }
                            else {
                                sonic.hitLeft = true;
                                sonic.LeftTexNumber = 0;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                            }
                            sonic.hitCounter = 50;
                            sonic.Velocity.y = 5;
                            sonic.HitTxDelay = 0;
                            sonic.PlayerSprite.move(0, -10);
                            sonic.HitCounter2 = 0;
                            SonicHitAudio.play();
                        }
                    }
                    if (Worms[i].Hit && Worms[i].DamageDelay <= 30 && Worms[i].DamageDelay >= 0) {
                        Worms[i].DamageDelay++;
                        Worms[i].EnemySprite.setColor(Color(255, 0, 0, 200));
                    }
                    else if (Worms[i].Hit && Worms[i].DamageDelay >= 30) {
                        Worms[i].EnemySprite.setColor(Color::White);
                        Worms[i].DamageDelay = -1;
                    }
                    Worms[i].EnemyColl.setPosition(Worms[i].EnemySprite.getPosition().x + 15, Worms[i].EnemySprite.getPosition().y + 8);

                    //Crabs
                    if (Crabs[i].TexDelay <= 8) Crabs[i].TexDelay++;
                    if (Crabs[i].MovingRight) {
                        Crabs[i].EnemySprite.move(4, 0);
                        if (Crabs[i].TexDelay >= 8) {
                            Crabs[i].TexDelay = 0;
                            Crabs[i].TexNumber++;
                            Crabs[i].TexNumber %= 4;
                            Crabs[i].EnemySprite.setTextureRect(IntRect(Crabs[i].TexNumber * 47, 411, 48, 30));
                        }
                        if (Crabs[i].EnemySprite.getPosition().x >= Crabs[i].xEnd) {
                            Crabs[i].MovingRight = false;
                        }
                    }
                    else {
                        Crabs[i].EnemySprite.move(-4, 0);
                        if (Crabs[i].TexDelay >= 8) {
                            Crabs[i].TexDelay = 0;
                            Crabs[i].TexNumber--;
                            if (Crabs[i].TexNumber <= 0) Crabs[i].TexNumber = 3;
                            Crabs[i].EnemySprite.setTextureRect(IntRect(Crabs[i].TexNumber * 47, 411, 48, 30));
                        }
                        if (Crabs[i].EnemySprite.getPosition().x <= Crabs[i].xStart) Crabs[i].MovingRight = true;
                    }
                    if (sonic.hitCounter == -1) {
                        if (Crabs[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                            if (!Crabs[i].Hit) Crabs[i].Hit = true;
                            else {
                                Crabs[i].EnemySprite.setScale(0, 0);
                                Crabs[i].EnemyColl.setScale(0, 0);
                                sonic.scoreValue += 100;
                                EnemyScore.setString("+100");
                                EnemyScore.setCharacterSize(50);
                                EnemyScore.setPosition(Crabs[i].EnemyColl.getPosition().x + 60, Crabs[i].EnemyColl.getPosition().y);
                                EnemyScoreCounter = 100;
                            }
                            sonic.Velocity.y = 10;
                            EnemyDamageSound.play();
                        }
                        else if ((Crabs[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0))) {
                            if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > Crabs[i].EnemySprite.getPosition().x) {
                                sonic.hitRight = true;
                                sonic.RightTexNumber = 4;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                            }
                            else {
                                sonic.hitLeft = true;
                                sonic.LeftTexNumber = 0;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                            }
                            sonic.hitCounter = 50;
                            sonic.Velocity.y = 5;
                            sonic.HitTxDelay = 0;
                            sonic.PlayerSprite.move(0, -10);
                            sonic.HitCounter2 = 0;
                            SonicHitAudio.play();
                        }
                    }
                    if (Crabs[i].Hit && Crabs[i].DamageDelay <= 30 && Crabs[i].DamageDelay >= 0) {
                        Crabs[i].DamageDelay++;
                        Crabs[i].EnemySprite.setColor(Color(255, 0, 0, 200));
                    }
                    else if (Crabs[i].Hit && Crabs[i].DamageDelay >= 30) {
                        Crabs[i].EnemySprite.setColor(Color::White);
                        Crabs[i].DamageDelay = -1;
                    }
                    Crabs[i].EnemyColl.setPosition(Crabs[i].EnemySprite.getPosition().x + 10, Crabs[i].EnemySprite.getPosition().y + 8);

                    //Flying Enemy
                    if (Enemy3[i].TexDelay <= 8) Enemy3[i].TexDelay++;
                    if (Enemy3[i].MovingRight) {
                        Enemy3[i].EnemySprite.move(4, 0);
                        if (Enemy3[i].TexDelay >= 8) {
                            Enemy3[i].TexDelay = 0;
                            Enemy3[i].TexNumber++;
                            Enemy3[i].TexNumber %= 4;
                            Enemy3[i].EnemySprite.setTextureRect(IntRect(Enemy3[i].TexNumber * 42.75, 268, 42.75, 30));
                        }
                        if (Enemy3[i].EnemySprite.getPosition().x >= Enemy3[i].xEnd) {
                            Enemy3[i].MovingRight = false;
                        }
                    }
                    else {
                        Enemy3[i].EnemySprite.move(-4, 0);
                        if (Enemy3[i].TexDelay >= 8) {
                            Enemy3[i].TexDelay = 0;
                            Enemy3[i].TexNumber--;
                            if (Enemy3[i].TexNumber <= 0) Enemy3[i].TexNumber = 3;
                            Enemy3[i].EnemySprite.setTextureRect(IntRect(Enemy3[i].TexNumber * 42.75, 232, 42.75, 30));
                        }
                        if (Enemy3[i].EnemySprite.getPosition().x <= Enemy3[i].xStart) Enemy3[i].MovingRight = true;
                    }
                    if (sonic.hitCounter == -1) {
                        if (Enemy3[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && !sonic.onTile && sonic.Velocity.y < 0) {
                            if (!Enemy3[i].Hit) Enemy3[i].Hit = true;
                            else {
                                Enemy3[i].EnemySprite.setScale(0, 0);
                                Enemy3[i].EnemyColl.setScale(0, 0);
                                sonic.scoreValue += 100;
                                EnemyScore.setString("+100");
                                EnemyScore.setCharacterSize(50);
                                EnemyScore.setPosition(Enemy3[i].EnemyColl.getPosition().x + 60, Enemy3[i].EnemyColl.getPosition().y);
                                EnemyScoreCounter = 100;
                            }
                            sonic.Velocity.y = 10;
                            EnemyDamageSound.play();
                        }
                        else if ((Enemy3[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && ((sonic.on_ground || sonic.onTile) || sonic.Velocity.y > 0))) {
                            if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > Enemy3[i].EnemySprite.getPosition().x) {
                                sonic.hitRight = true;
                                sonic.RightTexNumber = 4;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                            }
                            else {
                                sonic.hitLeft = true;
                                sonic.LeftTexNumber = 0;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                            }
                            sonic.hitCounter = 50;
                            sonic.Velocity.y = 5;
                            sonic.HitTxDelay = 0;
                            sonic.PlayerSprite.move(0, -10);
                            sonic.HitCounter2 = 0;
                            SonicHitAudio.play();
                        }
                    }
                    if (Enemy3[i].Hit && Enemy3[i].DamageDelay <= 30 && Enemy3[i].DamageDelay >= 0) {
                        Enemy3[i].DamageDelay++;
                        Enemy3[i].EnemySprite.setColor(Color(255, 0, 0, 200));
                    }
                    else if (Enemy3[i].Hit && Enemy3[i].DamageDelay >= 30) {
                        Enemy3[i].EnemySprite.setColor(Color::White);
                        Enemy3[i].DamageDelay = -1;
                    }
                    Enemy3[i].EnemyColl.setPosition(Enemy3[i].EnemySprite.getPosition().x + 7, Enemy3[i].EnemySprite.getPosition().y + 8);

                }

                // Jumppad System
                fa(i, 0, 30) {
                    if (jumppad[i].delay <= 2) jumppad[i].delay++;
                    if (sonic.PlayerColl.getGlobalBounds().intersects(jumppad[i].JumppadSprite.getGlobalBounds())) {
                        sonic.Velocity.y = 15;
                        sonic.PlayerSprite.move(0, -5);
                        jumppad[i].jumped = true;
                        sonic.hitRight = false;
                        sonic.hitLeft = false;
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
                    if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
                        sonic.Velocity.y = 10;
                        JumpSound.play();
                    }
                }
                else if (sonic.HitCounter2 == 5) {
                    bool found = false;
                    fa(i, 0, 60) {
                        if (sonic.PlayerColl.getGlobalBounds().intersects(tiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < tiles[i].TileSprite.getPosition().y) {
                            found = true;
                            sonic.onTile = true;
                            sonic.Velocity.y = 0;
                        }
                        if (sonic.PlayerColl.getGlobalBounds().intersects(tiles[i].LowerTileColl.getGlobalBounds()) && !sonic.on_ground) sonic.Velocity.y = -2;
                    }
                    fa(i, 0, 10)
                    {
                        if (sonic.PlayerColl.getGlobalBounds().intersects(Vertical_tiles_left[i].tilecole.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < Vertical_tiles_left[i].tilecole.getPosition().y) {
                            found = true;
                            sonic.onTile = true;
                            sonic.Velocity.y = 0;
                        }
                        if (sonic.PlayerColl.getGlobalBounds().intersects(Vertical_tiles_right[i].tilecole.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < Vertical_tiles_right[i].tilecole.getPosition().y) {
                            found = true;
                            sonic.onTile = true;
                            sonic.Velocity.y = 0;
                        }
                    }
                    fa(i, 0, 2) {
                        if (sonic.PlayerColl.getGlobalBounds().intersects(HAnimTiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < HAnimTiles[i].TileSprite.getPosition().y) {
                            found = true;
                            sonic.onTile = true;
                            sonic.Velocity.y = 0;
                        }
                    }
                    fa(i, 0, 23) {
                        if (sonic.PlayerColl.getGlobalBounds().intersects(VAnimTiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < VAnimTiles[i].TileSprite.getPosition().y) {
                            found = true;
                            sonic.onTile = true;
                            sonic.OnVTile = true;
                            sonic.Velocity.y = 0;
                        }
                    }
                    fa(i, 0, 10) {
                        if (sonic.PlayerColl.getGlobalBounds().intersects(DisappearingTiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < DisappearingTiles[i].TileSprite.getPosition().y) {
                            found = true;
                            sonic.onTile = true;
                            sonic.Velocity.y = 0;
                        }
                    }
                    if (!found) {
                        sonic.on_ground = false;
                        sonic.onTile = false;
                        sonic.OnVTile = false;
                    }
                    if (!sonic.on_ground && !sonic.onTile && !sonic.OnVTile) {
                        if (!sonic.hitLeft && !sonic.hitRight) {
                            sonic.RightTexNumber++;
                            sonic.RightTexNumber %= 16;
                            sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 49, 2 * 60, 49, 48));
                        }
                        sonic.Velocity.y -= 0.3;
                    }
                    if (sonic.onTile || sonic.OnVTile) {
                        sonic.Velocity.y = 0;
                        if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
                            sonic.Velocity.y = 10;
                            JumpSound.play();
                        }
                    }
                }
                fa(i, 0, 10) {
                    if (Vertical_tiles_left[i].Vertical_Tiles_sprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                        if (Keyboard::isKeyPressed(Keyboard::Key::LShift))
                            sonic.Velocity.x = -15;
                        else
                            sonic.Velocity.x = -12;
                    }
                    if (Vertical_tiles_right[i].Vertical_Tiles_sprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                        if (Keyboard::isKeyPressed(Keyboard::Key::LShift))
                            sonic.Velocity.x = 15;
                        else
                            sonic.Velocity.x = 12;
                    }
                }
                sonic.PlayerSprite.move(sonic.Velocity.x, -sonic.Velocity.y);
                if ((sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStartLevel1) || (Level == 2 && sonic.PlayerSprite.getPosition().x >= 17200 && !Boss.FightStartLevel2)) {
                    camera.move(sonic.Velocity.x, 0);
                    text.move(sonic.Velocity.x, 0);
                    lives.move(sonic.Velocity.x, 0);
                    SonicFace.move(sonic.Velocity.x, 0);
                    pauseMenu.move(sonic.Velocity.x, 0);
                }
                sonic.PlayerColl.setPosition(sonic.PlayerSprite.getPosition().x + 28, sonic.PlayerSprite.getPosition().y + 30);
                sonic.RightColl.setPosition(sonic.PlayerSprite.getPosition().x + 55, sonic.PlayerSprite.getPosition().y + 30);
                sonic.LeftColl.setPosition(sonic.PlayerSprite.getPosition().x + 28, sonic.PlayerSprite.getPosition().y + 30);

                window.setView(camera);

                //Background Ship
                fa(i, 0, 3) {
                    if (floatingShips[i].shipTexDelay <= 10) floatingShips[i].shipTexDelay++;
                    if (floatingShips[i].ShipMovingLeft) {
                        if (floatingShips[i].ShipSprite.getPosition().x < -200) {
                            floatingShips[i].ShipMovingLeft = false;
                            floatingShips[i].ShipTexNumber = 4;
                            floatingShips[i].shipTexDelay = 0;
                        }
                        else {
                            floatingShips[i].ShipSprite.move(-10, 0);
                        }
                    }
                    else {
                        if (floatingShips[i].ShipSprite.getPosition().x > 16500) {
                            floatingShips[i].ShipMovingLeft = true;
                            floatingShips[i].shipTexDelay = 0;
                        }
                        else {
                            floatingShips[i].ShipSprite.move(10, 0);
                        }
                    }
                    if (floatingShips[i].ShipSprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                        if (!sonic.on_ground && sonic.Velocity.y < 0 && sonic.hitCounter == -1) {
                            sonic.scoreValue += 300;
                            sonic.Velocity.y = 7;
                            floatingShips[i].ShipSprite.setScale(0, 0);
                            EnemyScore.setString("+300");
                            EnemyScore.setCharacterSize(50);
                            EnemyScore.setPosition(floatingShips[i].ShipSprite.getPosition().x + 60, floatingShips[i].ShipSprite.getPosition().y);
                            EnemyScoreCounter = 100;
                        }
                        else {
                            if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > floatingShips[i].ShipSprite.getPosition().x) {
                                sonic.hitRight = true;
                                sonic.RightTexNumber = 4;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                            }
                            else {
                                sonic.hitLeft = true;
                                sonic.LeftTexNumber = 0;
                                sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                            }
                            sonic.hitCounter = 50;
                            if (sonic.PlayerSprite.getPosition().y > floatingShips[i].ShipSprite.getPosition().y + 73.2)
                                sonic.Velocity.y = -4;
                            else
                                sonic.Velocity.y = 7;
                            SonicHitAudio.play();
                        }
                    }
                }

                //
                if (Boss.TexDelay <= 30 && (!Boss.MoveStart || Boss.StartDelay)) Boss.TexDelay++;
                if (sonic.PlayerSprite.getPosition().x >= 15000 && !Boss.FightStartLevel1) Boss.SceneStart = true;
                if (Boss.SceneStart && Level == 1) {
                    if (!BossMusicStarted) {
                        BackgroundMusic.stop();
                        BossFightMusic.play();
                        BossMusicStarted = true;
                    }
                    sonic.Velocity.x = 0;
                    if (Boss.TexDelay >= 10) {
                        Boss.TexNumber++;
                        Boss.TexDelay = 0;
                        Boss.BossSprite.setTextureRect(IntRect(Boss.TexNumber * 100, 800, 100, 64));
                    }
                    if (Boss.TexNumber == 5) {
                        Boss.FightStartLevel1 = true;
                        Boss.SceneStart = false;
                        Boss.TexDelay = 0;
                        Boss.TexNumber = 0;
                    }
                }
                if (Boss.FightStartLevel1 && Level == 1 && Boss.lives > 0) {
                    Boss.HealthBarRect.setScale(Boss.HealthBar, 1);
                    Boss.HealthBarBG.setScale(1, 1);
                    Boss.BossFaceSprite.setScale(0.16, 0.16);
                    if (!Boss.MoveStart) {
                        if (Boss.MovingLeft) {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(707, 800, 100, 64));
                            if (!Boss.StartDelay) {
                                if (Boss.TexDelay >= 10) {
                                    Boss.MoveStart = true;
                                    Boss.TexDelay = 0;
                                    Boss.Velocity.x = -15;
                                }
                                else Boss.BossSprite.move(-1, 0);
                            }
                            else {
                                if (Boss.TexDelay >= 30) {
                                    Boss.StartDelay = false;
                                    Boss.TexDelay = 0;
                                }
                            }
                        }
                        else {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(700, 725, 100, 64));
                            if (!Boss.StartDelay) {
                                if (Boss.TexDelay >= 10) {
                                    Boss.MoveStart = true;
                                    Boss.TexDelay = 0;
                                    Boss.Velocity.x = 15;
                                }
                                else Boss.BossSprite.move(1, 0);
                            }
                            else {
                                if (Boss.TexDelay >= 30) {
                                    Boss.StartDelay = false;
                                    Boss.TexDelay = 0;
                                }
                            }
                        }
                    }
                    else {
                        if (Boss.MovingLeft) {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(607, 800, 98, 64));
                            if (Boss.Velocity.x < 0) {
                                Boss.Velocity.x += 0.116;
                                Boss.BossSprite.move(Boss.Velocity.x, 0);
                            }

                        }
                        else {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(810, 725, 98, 64));
                            if (Boss.Velocity.x > 0) {
                                Boss.Velocity.x -= 0.116;
                                Boss.BossSprite.move(Boss.Velocity.x, 0);
                            }
                        }
                        if (Boss.MovingLeft) {
                            if (Boss.Velocity.x >= 0) {
                                Boss.MovingLeft = false;
                                Boss.MoveStart = false;
                                Boss.StartDelay = true;
                            }
                        }
                        else {
                            if (Boss.Velocity.x <= 0) {
                                Boss.MovingLeft = true;
                                Boss.MoveStart = false;
                                Boss.StartDelay = true;
                            }
                        }
                    }
                    if (BulletsSpawnDelay <= 300 && !SpawnStart) BulletsSpawnDelay++;
                    if (BulletDelay <= 30 && SpawnStart) BulletDelay++;
                    if (BulletsSpawnDelay >= 300) {
                        SpawnStart = true;
                        if (!BulletsPositioned) {
                            fa(i, 0, 5) {
                                skyBullets[i].SkyBulletsSprite.setPosition(rand() % 1109 + 14800, -300);
                                skyBullets[i].spawned = false;
                                skyBullets[i].SkyBulletsSprite.setScale(0.8, 0.8);
                                skyBullets[i].BulletColl.setScale(1, 1);
                                skyBullets[i].TexNumber = 0;
                            }
                            BulletsPositioned = true;
                        }
                        if (BulletDelay >= 30 && BulletsSpawned < 5) {
                            BulletDelay = 0;
                            skyBullets[BulletsSpawned].spawned = true;
                            BulletsSpawned++;
                        }
                    }
                    fa(i, 0, 5) {
                        if (skyBullets[i].spawned) {
                            if (skyBullets[i].SkyBulletsSprite.getPosition().y <= 485) {
                                skyBullets[i].SkyBulletsSprite.move(0, 12);
                                skyBullets[i].SkyBulletsSprite.setTextureRect(IntRect(114, 0, 114, 227));
                            }
                            else if (skyBullets[i].SkyBulletsSprite.getPosition().y > 485) {
                                skyBullets[i].SkyBulletsSprite.setScale(0, 0);
                                skyBullets[i].BulletColl.setScale(0, 0);
                            }
                        }
                        skyBullets[i].BulletColl.setPosition(skyBullets[i].SkyBulletsSprite.getPosition().x + 34.4, skyBullets[i].SkyBulletsSprite.getPosition().y + 56.8);
                        if (skyBullets[i].BulletColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                            skyBullets[i].SkyBulletsSprite.setScale(0, 0);
                            skyBullets[i].BulletColl.setScale(0, 0);
                            if (sonic.hitCounter == -1) sonic.lives--;
                            sonic.hitCounter = 50;
                            SonicHitAudio.play();
                        }
                    }
                    if (SpawnStart && !skyBullets[4].SkyBulletsSprite.getScale().x) {
                        SpawnStart = false;
                        BulletsPositioned = false;
                        BulletsSpawnDelay = 0;
                        BulletsSpawned = 0;
                    }
                }
                else {
                    fa(i, 0, 5) {
                        if (skyBullets[i].spawned) {
                            if (skyBullets[i].SkyBulletsSprite.getPosition().y <= 485) {
                                skyBullets[i].SkyBulletsSprite.move(0, 12);
                                skyBullets[i].SkyBulletsSprite.setTextureRect(IntRect(114, 0, 114, 227));
                            }
                            else if (skyBullets[i].SkyBulletsSprite.getPosition().y > 485) {
                                skyBullets[i].SkyBulletsSprite.setScale(0, 0);
                                skyBullets[i].BulletColl.setScale(0, 0);
                            }
                        }
                    }
                }
                if (sonic.PlayerColl.getGlobalBounds().intersects(Boss.HitBox.getGlobalBounds()) && Boss.lives > 0 && Level == 1 && sonic.hitCounter == -1) {
                    if (sonic.Velocity.y >= 0) {
                        if (!sonic.hitLeft && !sonic.hitRight) sonic.lives--;
                        if (sonic.PlayerSprite.getPosition().x > Boss.BossSprite.getPosition().x) {
                            sonic.hitRight = true;
                            sonic.RightTexNumber = 4;
                            sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                        }
                        else {
                            sonic.hitLeft = true;
                            sonic.LeftTexNumber = 0;
                            sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                        }
                        sonic.hitCounter = 300;
                        sonic.Velocity.y = 8;
                        sonic.PlayerSprite.move(0, -10);
                        sonic.HitCounter2 = 0;
                        SonicHitAudio.play();
                    }
                    else if (sonic.Velocity.y < 0) {
                        if (Boss.hitCounter == -1) {
                            Boss.lives--;
                            Boss.hitCounter = 50;
                            Boss.BarCounter += 50;
                            BossDamageSound[rand() % 3].play();
                        }
                        if (Boss.lives == 0) sonic.scoreValue += 1000;
                        sonic.Velocity.y = 10;
                        if (!Boss.MovingLeft) Boss.BossSprite.setTextureRect(IntRect(111, 875, 86, 60));
                        else Boss.BossSprite.setTextureRect(IntRect(107, 952, 86, 60));
                    }
                }
                if (Boss.hitCounter != -1) Boss.hitCounter--;
                if (Boss.lives <= 0 && Level < 2) {
                    Boss.HealthBarRect.setScale(0, 0);
                    Boss.HealthBarBG.setScale(0, 0);
                    Boss.BossFaceSprite.setScale(0, 0);
                    Boss.Level1FightEnd = true;
                    if (Boss.BossSprite.getPosition().y >= 150) {
                        Boss.BossSprite.setTextureRect(IntRect(500, 725, 100, 64));
                        Boss.BossSprite.move(0, -6);
                    }
                    else if (Boss.BossSprite.getPosition().x <= 16100) {
                        Boss.BossSprite.setTextureRect(IntRect(800, 725, 100, 64));
                        Boss.BossSprite.move(10, 0);
                    }
                    else if (Level != 2) Level = 2;
                    if (BossMusicStarted) {
                        BossFightMusic.stop();
                        BackgroundMusic.play();
                    }
                }
                if (!Fade1End && sonic.PlayerSprite.getPosition().x >= 16020) {
                    if (Level == 2 && !Level2AnimStart) {
                        LevelPassed.setScale(1, 1);
                        FinalScore.setFillColor(Color::Black);
                        FinalScore.setPosition(15330, 300);
                        FinalScore.setCharacterSize(60);
                        if (Mouse::getPosition(window).x >= 300 && Mouse::getPosition(window).x <= 900 && Mouse::getPosition(window).y >= 632 && Mouse::getPosition(window).y <= 711) {
                            if (Mouse::isButtonPressed(Mouse::Left)) {
                                LevelPassed.setScale(0, 0);
                                Level2AnimStart = true;
                                FinalScore.setCharacterSize(0);
                            }
                        }
                        if (sonic.FinalScore < sonic.scoreValue) sonic.FinalScore += 7;
                        if (sonic.FinalScore > sonic.scoreValue) sonic.FinalScore = sonic.scoreValue;
                    }
                    else {
                        if (fadeOp < 255) {
                            fadeOp += 5;
                            FadeRect.setColor(Color(0, 0, 0, fadeOp));
                        }
                        else Fade1End = true;
                    }
                }
                else if (Fade1End && Level2AnimStart && !Level2Start) {
                    if (!Fade2Start) {
                        sonic.PlayerSprite.setPosition(17200, 400);
                        //sonic.PlayerSprite.setPosition(35000, 400);
                        //camera.move(20000, 0);
                        camera.move(2200, 0);
                        text.move(2200, 0);
                        lives.move(2200, 0);
                        SonicFace.move(2200, 0);
                        pauseMenu.move(2200, 0);
                        FadeRect.move(2200, 0);
                        Fade2Start = true;
                        Boss.lives = 10;
                        //36100 --> 35960
                        Boss.BossSprite.setPosition(35960, -500);
                        Boss.HealthBarBG.setPosition(35846, 30);
                        Boss.HealthBarRect.setPosition(35851, 35);
                        Boss.BossFaceSprite.setPosition(35744, 24);
                        Boss.HealthBar = 10;
                        //102.08 + 610 = 712.08
                        Boss.MovingLeft = false;
                        Boss.Velocity.x = 11;
                        BossMusicStarted = false;
                        wreckingBall.WreckingChainSprite.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 - 18, 192.2);
                        wreckingBall.WreckingBallSprite.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 - 18, 192.2);
                        wreckingBall.HitBox.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 - 18, 192.2);
                        //15400
                    }
                    else {
                        if (fadeOp > 0) {
                            fadeOp -= 5;
                            FadeRect.setColor(Color(0, 0, 0, fadeOp));
                        }
                        else Level2Start = true;
                    }
                }
                //Boss Level 2
                if (Level == 2 && Level2Start) {
                    if (Boss.MovingLeft) {
                        wreckingBall.WreckingChainSprite.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 - 18, Boss.HitBox.getPosition().y + 95);
                        wreckingBall.WreckingBallSprite.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 - 18, Boss.HitBox.getPosition().y + 95);
                        wreckingBall.HitBox.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 - 18, Boss.HitBox.getPosition().y + 95);
                    }
                    else {
                        wreckingBall.WreckingChainSprite.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 + 4, Boss.HitBox.getPosition().y + 95);
                        wreckingBall.WreckingBallSprite.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 + 4, Boss.HitBox.getPosition().y + 95);
                        wreckingBall.HitBox.setPosition(Boss.HitBox.getPosition().x + Boss.HitBox.getSize().x / 2 + 4, Boss.HitBox.getPosition().y + 95);
                    }
                }
                if (Boss.TexDelay <= 30 && (!Boss.MoveStart || Boss.StartDelay)) Boss.TexDelay++;
                if (sonic.PlayerSprite.getPosition().x >= 35700 && !Boss.FightStartLevel2) Boss.SceneStart = true;
                if (Boss.SceneStart && Level == 2) {
                    if (!BossMusicStarted) {
                        BackgroundMusic.stop();
                        BossFightMusic.play();
                        BossMusicStarted = true;
                    }
                    sonic.Velocity.x = 0;
                    if (Boss.BossSprite.getPosition().y <= 100) Boss.BossSprite.move(0, 3);
                    else {
                        Boss.SceneStart = false;
                        Boss.FightStartLevel2 = true;
                        Boss.TexDelay = 0;
                        Boss.TexNumber = 0;
                    }
                }
                if (Boss.FightStartLevel2 && Boss.lives > 0) {
                    Boss.HealthBarRect.setScale(Boss.HealthBar, 1);
                    Boss.HealthBarBG.setScale(1, 1);
                    Boss.BossFaceSprite.setScale(0.16, 0.16);
                    if (!Boss.MoveStart) {
                        if (Boss.MovingLeft) {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(707, 800, 100, 64));
                            if (!Boss.StartDelay) {
                                if (Boss.TexDelay >= 10) {
                                    Boss.MoveStart = true;
                                    Boss.TexDelay = 0;
                                    Boss.Velocity.x = -15;
                                }
                                else Boss.BossSprite.move(-1, 0);
                            }
                            else {
                                if (Boss.TexDelay >= 30) {
                                    Boss.StartDelay = false;
                                    Boss.TexDelay = 0;
                                }
                            }
                        }
                        else {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(707, 725, 100, 64));
                            if (!Boss.StartDelay) {
                                if (Boss.TexDelay >= 10) {
                                    Boss.MoveStart = true;
                                    Boss.TexDelay = 0;
                                    Boss.Velocity.x = 15;
                                }
                                else Boss.BossSprite.move(1, 0);
                            }
                            else {
                                if (Boss.TexDelay >= 30) {
                                    Boss.StartDelay = false;
                                    Boss.TexDelay = 0;
                                }
                            }
                        }
                    }
                    else {
                        if (Boss.MovingLeft) {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(607, 800, 98, 64));
                            if (Boss.Velocity.x < 0) {
                                Boss.Velocity.x += 0.116;
                                Boss.BossSprite.move(Boss.Velocity.x, 0);
                            }
                        }
                        else {
                            if (Boss.hitCounter == -1) Boss.BossSprite.setTextureRect(IntRect(810, 725, 98, 64));
                            if (Boss.Velocity.x > 0) {
                                Boss.Velocity.x -= 0.116;
                                Boss.BossSprite.move(Boss.Velocity.x, 0);
                            }
                        }
                        if (Boss.MovingLeft) {
                            if (Boss.Velocity.x >= 0) {
                                Boss.MovingLeft = false;
                                Boss.MoveStart = false;
                                Boss.StartDelay = true;
                            }
                        }
                        else {
                            if (Boss.Velocity.x <= 0) {
                                Boss.MovingLeft = true;
                                Boss.MoveStart = false;
                                Boss.StartDelay = true;
                            }
                        }
                    }
                }
                if (sonic.PlayerColl.getGlobalBounds().intersects(wreckingBall.HitBox.getGlobalBounds()) && Boss.lives > 0 && Level == 2 && sonic.hitCounter == -1) {
                    if (!sonic.hitLeft && !sonic.hitRight) sonic.lives--;
                    if (sonic.RightColl.getGlobalBounds().intersects(wreckingBall.HitBox.getGlobalBounds())) {
                        sonic.hitLeft = true;
                        sonic.RightTexNumber = 4;
                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.2, 290, 48.2, 34));
                    }
                    else {
                        sonic.hitRight = true;
                        sonic.LeftTexNumber = 0;
                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.2, 246, 48.2, 34));
                    }
                    sonic.hitCounter = 300;
                    SonicHitAudio.play();
                    sonic.Velocity.y = 2;
                    sonic.PlayerSprite.move(0, -20);
                    sonic.LeftTexNumber = 0;
                    sonic.RightTexNumber = 4;
                    sonic.HitCounter2 = 0;
                }
                if (sonic.PlayerColl.getGlobalBounds().intersects(Boss.HitBox.getGlobalBounds()) && Boss.lives > 0 && Level == 2 && sonic.hitCounter == -1) {
                    if (Boss.hitCounter == -1) {
                        Boss.lives--;
                        Boss.hitCounter = 50;
                        Boss.BarCounter += 50;
                        BossDamageSound[rand() % 3].play();
                    }
                    if (Boss.lives == 0) sonic.scoreValue += 1000;
                    if (!Boss.MovingLeft) Boss.BossSprite.setTextureRect(IntRect(111, 875, 86, 60));
                    else Boss.BossSprite.setTextureRect(IntRect(107, 952, 86, 60));
                }
                if (Boss.hitCounter != -1) Boss.hitCounter--;
                if (Boss.lives <= 0 && Level == 2 && Boss.FightStartLevel2) {
                    Boss.HealthBarRect.setScale(0, 0);
                    Boss.HealthBarBG.setScale(0, 0);
                    Boss.BossFaceSprite.setScale(0, 0);
                    if (SpawnCounter <= 6) SpawnCounter++;
                    if (Explosion[19].rowTxNum != 6 && Explosion[19].colomnTxNum <= 6) {
                        fa(i, 0, 20) {
                            if (!Explosion[i].Spawned) {
                                if (SpawnCounter > 6) {
                                    ExplosionsSpawned++;
                                    SpawnCounter = 0;
                                    Explosion[i].Spawned = true;
                                    Explosion[i].ExplosionSprite.setPosition(Boss.BossSprite.getPosition().x - 40 + (rand() % 160), Boss.BossSprite.getPosition().y - 30 + (rand() % 90));
                                    Explosion[i].ExplosionSprite.setScale(1, 1);
                                }
                            }
                            else {
                                if (Explosion[i].rowTxNum < 5 && Explosion[i].colomnTxNum > 5) {
                                    Explosion[i].rowTxNum++;
                                    Explosion[i].colomnTxNum = 0;
                                }
                                else if (Explosion[i].rowTxNum == 5 && Explosion[i].colomnTxNum > 2) {
                                    Explosion[i].ExplosionSprite.setScale(0, 0);
                                }
                                Explosion[i].colomnTxNum++;
                                Explosion[i].ExplosionSprite.setTextureRect(IntRect(Explosion[i].colomnTxNum * 130, Explosion[i].rowTxNum * 114, 130, 114));
                            }
                        }
                    }
                    else if (Level != 3) {
                        Level = 3;
                        sonic.scoreValue += (sonic.lives * 100);
                        sonic.FinalScore = 0;
                    }
                    if (BossMusicStarted) {
                        BossFightMusic.stop();
                        BackgroundMusic.play();
                    }
                }
                if (Boss.MovingLeft)
                    Boss.HitBox.setPosition(Boss.BossSprite.getPosition().x + 10, Boss.BossSprite.getPosition().y + 48);
                else
                    Boss.HitBox.setPosition(Boss.BossSprite.getPosition().x + 78, Boss.BossSprite.getPosition().y + 48);

                if (Level == 2 && Level2Start && Boss.lives > 0) {
                    if (wreckingBall.WreckingBallSprite.getRotation() == 70 && wreckingBall.MovingLeft) {
                        wreckingBall.MovingLeft = false;
                        wreckingBall.Velocity = -1;
                    }
                    else if (wreckingBall.WreckingBallSprite.getRotation() == 290 && !wreckingBall.MovingLeft) {
                        wreckingBall.MovingLeft = true;
                        wreckingBall.Velocity = 1;
                    }
                    wreckingBall.WreckingBallSprite.rotate(wreckingBall.Velocity);
                    wreckingBall.WreckingChainSprite.rotate(wreckingBall.Velocity);
                    wreckingBall.HitBox.rotate(wreckingBall.Velocity);
                }

                if (Boss.BarCounter > 0) {
                    Boss.BarCounter--;
                    Boss.HealthBar -= 0.02;
                }
                if (Level == 3) {
                    Level2Passed.setScale(1, 1);
                    FinalScore.setPosition(36030, 270);
                    FinalScore.setCharacterSize(60);
                    if (Mouse::getPosition(window).x >= 300 && Mouse::getPosition(window).x <= 900 && Mouse::getPosition(window).y >= 632 && Mouse::getPosition(window).y <= 711) {
                        if (Mouse::isButtonPressed(Mouse::Left)) {
                            pushScore(make_pair(sonic.scoreValue, playerInput));
                            saveLDToFile();
                            window.close();
                            BackgroundMusic.stop();
                            BossFightMusic.stop();
                            CreditClosed = false;
                            main();
                        }
                    }
                    //Test
                    if (sonic.FinalScore < sonic.scoreValue) sonic.FinalScore += 100;
                    if (sonic.FinalScore > sonic.scoreValue) sonic.FinalScore = sonic.scoreValue;
                }
                //level 2
                fa(i, 0, 2) {
                    if (HAnimTiles[i].Direction) {
                        HAnimTiles[i].TileSprite.move(5, 0);
                        HAnimTiles[i].TileColl.move(5, 0);
                        if (sonic.PlayerSprite.getGlobalBounds().intersects(HAnimTiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < HAnimTiles[i].TileSprite.getPosition().y) {
                            sonic.PlayerSprite.move(5, 0);
                            if ((sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStartLevel1) || (Level == 2 && sonic.PlayerSprite.getPosition().x >= 17200)) {
                                camera.move(5, 0);
                                text.move(5, 0);
                                lives.move(5, 0);
                                SonicFace.move(5, 0);
                                pauseMenu.move(5, 0);
                            }
                        }
                    }
                    else {
                        HAnimTiles[i].TileSprite.move(-5, 0);
                        HAnimTiles[i].TileColl.move(-5, 0);
                        if (sonic.PlayerSprite.getGlobalBounds().intersects(HAnimTiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < HAnimTiles[i].TileSprite.getPosition().y) {
                            sonic.PlayerSprite.move(-5, 0);
                            if ((sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStartLevel1) || (Level == 2 && sonic.PlayerSprite.getPosition().x >= 17200)) {
                                camera.move(-5, 0);
                                text.move(-5, 0);
                                lives.move(-5, 0);
                                SonicFace.move(-5, 0);
                                pauseMenu.move(-5, 0);
                            }
                        }
                    }
                    if (HAnimTiles[i].TileSprite.getPosition().x >= HAnimTiles[i].xEnd && HAnimTiles[i].Direction) {
                        HAnimTiles[i].Direction = false;
                    }
                    else if (HAnimTiles[i].TileColl.getPosition().x <= HAnimTiles[i].xStart && !HAnimTiles[i].Direction) {
                        HAnimTiles[i].Direction = true;
                    }
                }
                fa(i, 0, 23) {
                    if (VAnimTiles[i].Direction) {
                        VAnimTiles[i].TileSprite.move(0, 5);
                        VAnimTiles[i].TileColl.move(0, 5);
                        if (sonic.PlayerSprite.getGlobalBounds().intersects(VAnimTiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < VAnimTiles[i].TileSprite.getPosition().y) {
                            sonic.PlayerSprite.move(0, 5);
                        }
                    }
                    else {
                        VAnimTiles[i].TileSprite.move(0, -5);
                        VAnimTiles[i].TileColl.move(0, -5);
                        if (sonic.PlayerSprite.getGlobalBounds().intersects(VAnimTiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < VAnimTiles[i].TileSprite.getPosition().y) {
                            sonic.PlayerSprite.move(0, -5);
                        }
                    }
                    if (VAnimTiles[i].TileSprite.getPosition().y >= VAnimTiles[i].yEnd && VAnimTiles[i].Direction) {
                        VAnimTiles[i].Direction = false;
                    }
                    else if (VAnimTiles[i].TileColl.getPosition().y <= VAnimTiles[i].yStart && !VAnimTiles[i].Direction) {
                        VAnimTiles[i].Direction = true;
                    }
                }
                fa(i, 0, 10) {
                    if (!DisappearingTiles[i].FullDisappeared) {
                        if (DisappearingTiles[i].dCounter <= 160) DisappearingTiles[i].dCounter++;
                        else {
                            DisappearingTiles[i].TileSprite.setScale(0, 0);
                            DisappearingTiles[i].TileColl.setScale(0, 0);
                            DisappearingTiles[i].FullDisappeared = true;
                            DisappearingTiles[i].dCounter = 0;
                        }
                        if (DisappearingTiles[i].dCounter >= 100) {
                            if (DisappearingTiles[i].AnimCounter <= 5) DisappearingTiles[i].AnimCounter++;
                            else {
                                DisappearingTiles[i].AnimCounter = 0;
                                if (!DisappearingTiles[i].Disappeared) {
                                    DisappearingTiles[i].TileSprite.setColor(Color(255, 255, 255, 0));
                                    DisappearingTiles[i].Disappeared = true;
                                }
                                else {
                                    DisappearingTiles[i].TileSprite.setColor(Color(255, 255, 255, 255));
                                    DisappearingTiles[i].Disappeared = false;
                                }
                            }
                        }
                        else {
                            DisappearingTiles[i].TileSprite.setColor(Color(255, 255, 255, 255));
                        }
                    }
                    else {
                        DisappearingTiles[i].AnimCounter = 0;
                        if (DisappearingTiles[i].dCounter <= 80) DisappearingTiles[i].dCounter++;
                        else {
                            DisappearingTiles[i].TileSprite.setScale(1.3, 1.3);
                            DisappearingTiles[i].TileColl.setScale(1.3, 1.3);
                            DisappearingTiles[i].FullDisappeared = false;
                            DisappearingTiles[i].dCounter = 0;
                        }
                    }
                }

                if (sonic.lives <= 0) {
                    sonic.PlayerSprite.setTextureRect(IntRect(278, 240, 48.86, 51));
                    sonic.deathDealy = 10;
                    BackgroundMusic.stop();
                    BossFightMusic.stop();
                    GameoverAudio.play();
                }
            }
            else if (paused) {
                pauseMenu.setScale(1.05, 1);
                if (Mouse::getPosition(window).x >= 440 && Mouse::getPosition(window).x <= 778 && Mouse::getPosition(window).y >= 344 && Mouse::getPosition(window).y <= 409) {
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        paused = false;
                    }
                }
                if (Mouse::getPosition(window).x >= 420 && Mouse::getPosition(window).x <= 865 && Mouse::getPosition(window).y >= 434 && Mouse::getPosition(window).y <= 480) {
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        window.close();
                        BackgroundMusic.stop();
                        BossFightMusic.stop();
                        main();
                    }
                }
            }
            else {
                sonic.deathDealy--;
                if (sonic.deathDealy >= 0) {
                    sonic.PlayerSprite.move(0, -1);
                }
                else {
                    sonic.PlayerSprite.setTextureRect(IntRect(333, 240, 48.86, 51));
                    sonic.PlayerSprite.move(0, 7);
                    if (sonic.PlayerSprite.getPosition().y > 800) {
                        window.setView(GameoverCamera);
                        FinalScore.setCharacterSize(70);
                        Gameover.setScale(1, 0.94);
                        if (Mouse::getPosition(window).x >= 407 && Mouse::getPosition(window).x <= 833 && Mouse::getPosition(window).y >= 662 && Mouse::getPosition(window).y <= 737) {
                            if (Mouse::isButtonPressed(Mouse::Left)) {
                                window.close();
                                BackgroundMusic.stop();
                                GameoverAudio.stop();
                                BossFightMusic.stop();
                                main();
                            }
                        }
                        if (sonic.FinalScore < sonic.scoreValue) sonic.FinalScore += 100;
                        else if (sonic.FinalScore > sonic.scoreValue) sonic.FinalScore = sonic.scoreValue;
                    }
                }
            }
            if (EnemyScoreCounter > 0) {
                EnemyScoreCounter--;
                EnemyScore.move(0, -0.5);
            }
            else EnemyScore.setCharacterSize(0);

            // clear
            window.clear();
            lives.setString("x" + std::to_string(sonic.lives));
            text.setString("Score: " + std::to_string(sonic.scoreValue));
            FinalScore.setString(std::to_string(sonic.FinalScore));
            //draw
            window.draw(Map);
            window.draw(Map2);
            fa(i, 0, 3)window.draw(floatingShips[i].ShipSprite);
            fa(i, 0, 12)window.draw(tiles[i].TileSprite);
            fa(i, 0, 15) window.draw(jumppad[i].JumppadSprite);
            fa(i, 0, 5) window.draw(Red_coins[i].CoinSprite);
            fa(i, 0, 171) window.draw(spikes[i].SpikeSprite);
            fa(i, 0, 6) window.draw(tiles2[i].TileSprite);
            fa(i, 0, 68) window.draw(spikes2[i].SpikeSprite);
            fa(i, 0, 82) window.draw(animespikes2[i].SpikeSprite2);
            fa(i, 0, 420) window.draw(coins[i].CoinSprite);
            fa(i, 0, 6) window.draw(DisappearingTiles[i].TileSprite);
            fa(i, 0, 8) window.draw(Vertical_tiles_right[i].Vertical_Tiles_sprite);
            fa(i, 0, 8) window.draw(Vertical_tiles_left[i].Vertical_Tiles_sprite);
            fa(i, 0, 2) window.draw(HAnimTiles[i].TileSprite);
            fa(i, 0, 23) window.draw(VAnimTiles[i].TileSprite);
            fa(i, 0, 2) window.draw(Worms[i].EnemySprite);
            fa(i, 0, 3) window.draw(Crabs[i].EnemySprite);
            fa(i, 0, 3) window.draw(Enemy3[i].EnemySprite);
            window.draw(Boss.BossSprite);
            window.draw(wreckingBall.WreckingBallSprite);
            window.draw(wreckingBall.WreckingChainSprite);
            fa(i, 0, 40) window.draw(Explosion[i].ExplosionSprite);
            window.draw(sonic.PlayerSprite);
            fa(i, 0, 5) window.draw(skyBullets[i].SkyBulletsSprite);
            window.draw(SonicFace);
            window.draw(text);
            window.draw(lives);
            window.draw(pauseMenu);
            window.draw(Gameover);
            window.draw(LevelPassed);
            window.draw(Level2Passed);
            window.draw(FinalScore);
            window.draw(EnemyScore);
            window.draw(Boss.HealthBarBG);
            window.draw(Boss.HealthBarRect);
            window.draw(Boss.BossFaceSprite);
            window.draw(FadeRect);
            window.display();
        }
    }

    return 0;
}

void DisappearingTilesd(int index, int X_position, int Y_position, int delay) {
    DisappearingTiles[index].TileSprite.setPosition(X_position, Y_position);
    DisappearingTiles[index].TileColl.setPosition(X_position, Y_position - 10);
    DisappearingTiles[index].dCounter = delay;
}

void HAnimTiles_pos(int index, int X_pos, int Y_pos, int start, int end) {
    HAnimTiles[index].TileSprite.setPosition(X_pos, Y_pos);
    HAnimTiles[index].TileColl.setPosition(X_pos, Y_pos - 9);
    HAnimTiles[index].xStart = start;
    HAnimTiles[index].xEnd = end;
}

void VAnimTiles_pos(int index, int X_pos, int Y_pos, int start, int end) {
    VAnimTiles[index].TileSprite.setPosition(X_pos, Y_pos);
    VAnimTiles[index].TileColl.setPosition(X_pos, Y_pos - 9);
    VAnimTiles[index].yStart = start;
    VAnimTiles[index].yEnd = end;
}
void animatedspikes_pos(int index, int X_pos, int Y_pos, int start, int end) {
    animespikes2[index].SpikeSprite2.setPosition(X_pos, Y_pos);
    animespikes2[index].yStart = start;
    animespikes2[index].yEnd = end;
}

void DrawAnimTiles() {
    HAnimTiles_pos(0, 21720, 240, 21720, 22545);
    HAnimTiles_pos(1, 23700, 240, 22874, 23700);
    VAnimTiles_pos(0, 24500, 700, 100, 530);
    VAnimTiles_pos(1, 25200, 0, 100, 530);
    VAnimTiles_pos(2, 25900, 700, 100, 530);
    VAnimTiles_pos(3, 26600, 0, 100, 530);
    VAnimTiles_pos(4, 28000, 0, 0, 480);
    VAnimTiles_pos(5, 28300, 0, 0, 480);
    VAnimTiles_pos(6, 28600, 0, 0, 480);
    VAnimTiles_pos(7, 28900, 0, 0, 480);
    VAnimTiles_pos(8, 29200, 0, 0, 480);
    VAnimTiles_pos(9, 29500, 0, 0, 480);
    VAnimTiles_pos(10, 29800, 0, 0, 480);
    VAnimTiles_pos(11, 30100, 0, 0, 480);
    VAnimTiles_pos(12, 30400, 0, 0, 480);
    VAnimTiles_pos(13, 30700, 0, 0, 480);
    VAnimTiles_pos(14, 30900, 0, 0, 480);
    VAnimTiles_pos(15, 31200, 0, 0, 480);
    VAnimTiles_pos(16, 31500, 0, 0, 480);
    VAnimTiles_pos(17, 31800, 0, 0, 480);
    VAnimTiles_pos(18, 32100, 0, 0, 480);
    VAnimTiles_pos(19, 32400, 0, 0, 480);
    VAnimTiles_pos(20, 32700, 0, 0, 480);
    VAnimTiles_pos(21, 33000, 0, 0, 480);
    VAnimTiles_pos(22, 33300, 0, 0, 480);
}

void setTilePos(FloatingTiles& tile, int x, int y) {
    tile.TileSprite.setPosition(x, y);
    tile.TileColl.setPosition(x + 15, y - 15);
    tile.LowerTileColl.setPosition(x + 15, y + 48);
}
void singleRedCoinPs(int index, int X_position, int Y_Position, int scale = 0.7) {
    Red_coins[index].CoinSprite.setTexture(RedCoinTx);
    Red_coins[index].CoinSprite.setTextureRect(IntRect(0, 0, 1588, 112));
    Red_coins[index].CoinSprite.setScale(scale, scale);
    Red_coins[index].CoinSprite.setPosition(X_position, Y_Position);
}
void Moving_in_X_Axis(int First_index, int Last_index, int X_position, int Y_Position) {
    fa(i, First_index, Last_index) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(X_position + ((i - First_index) * 45), Y_Position);
        coins[i].CoinSprite.setScale(1, 1);
    }
}
void Moving_in_X_Y(int First_index, int Last_index, int X_position, int Y_Position, int X_increament, int Y_increament) {
    fa(i, First_index, Last_index) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition((X_position + ((i - First_index) * X_increament)), (Y_Position - ((i - First_index) * Y_increament)));
        coins[i].CoinSprite.setScale(1, 1);
    }
}
void Moving_in_Y_Axis(int First_index, int Last_index, int X_position, int Y_Position, int increase = 45) {
    fa(i, First_index, Last_index) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(X_position, Y_Position - ((i - First_index) * increase));
        coins[i].CoinSprite.setScale(1, 1);
    }
}
void SingleCoinPos(int num, int X_Position, int Y_position) {
    coins[num].CoinSprite.setTexture(CoinTex);
    coins[num].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
    coins[num].CoinSprite.setPosition(X_Position, Y_position);
    coins[num].CoinSprite.setScale(1, 1);
}
void PosRowCoins(int First_index, int Last_index, int X_position, int Y_Position) {
    fa(i, First_index, Last_index) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(X_position + (i * 40), Y_Position);
        coins[i].CoinSprite.setScale(1, 1);
    }
}
void coinPos() {
    // coins positioning ........................................................................................
    // Walll..............
    PosRowCoins(0, 8, 3400, 260);
    PosRowCoins(8, 16, 3889, 160);
    PosRowCoins(16, 24, 4356, 210);
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
    SingleCoinPos(38, 1465, 375);

    fa(i, 39, 41) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1370 + ((i - 38) * 35), 510 - ((i - 37) * 35));
        coins[i].CoinSprite.setScale(1, 1);
    }
    fa(i, 42, 45) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1520 + ((i - 41) * 35), 335 + ((i - 41) * 35));
        coins[i].CoinSprite.setScale(1, 1);
    }
    fa(i, 47, 50) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1400 + ((i - 47) * 35), 540 + ((i - 47) * 25));
        coins[i].CoinSprite.setScale(1, 1);
    }
    fa(i, 51, 54) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1410 + ((i - 47) * 35), 680 - ((i - 47) * 25));
        coins[i].CoinSprite.setScale(1, 1);
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
    singleRedCoinPs(0, 1980, 350, 0.7);
    Red_coins[1].CoinSprite.setTexture(RedCoinTx);
    Red_coins[1].CoinSprite.setTextureRect(IntRect(0, 0, 1588, 112));
    Red_coins[1].CoinSprite.setScale(1.5, 1.5);
    Red_coins[1].CoinSprite.setPosition(1440, 430);
    //final final
    Moving_in_X_Y(86, 92, 6070, 550, 30);
    Moving_in_X_Axis(92, 95, 6280, 315);
    Moving_in_X_Axis(141, 145, 6250, 370);
    Moving_in_X_Axis(145, 150, 6220, 420);
    Moving_in_X_Axis(150, 157, 6180, 470);
    Moving_in_X_Y(95, 101, 6420, 330, 30, -45);
    //
    Moving_in_X_Y(101, 107, 6630, 550, 30);
    Moving_in_X_Axis(107, 112, 6840, 315);
    Moving_in_X_Axis(165, 171, 6810, 370);
    Moving_in_X_Axis(173, 180, 6780, 420);
    Moving_in_X_Axis(183, 192, 6740, 470);
    Moving_in_X_Y(115, 121, 7070, 330, 30, -45);
    //
    Moving_in_X_Y(121, 127, 7250, 555, 30);
    Moving_in_X_Axis(127, 132, 7440, 315);
    Moving_in_X_Axis(208, 214, 7420, 370);
    Moving_in_X_Axis(214, 221, 7395, 420);
    Moving_in_X_Axis(221, 230, 7360, 470);
    Moving_in_X_Y(134, 140, 7670, 330, 30, -45);
    //
    Moving_in_X_Axis(248, 291, 6080, 200);
    //
    Moving_in_X_Y(291, 296, 12220, 20, 30, -45);
    Moving_in_X_Y(296, 301, 12030, 220, 30, 45);
    //
    Moving_in_X_Y(301, 306, 12505, 40, 30, -45);
    Moving_in_X_Y(306, 311, 12355, 220, 30, 45);
    //

    Moving_in_X_Axis(312, 329, 17350, 585);
    Moving_in_X_Axis(329, 372, 18550, 200);
    Moving_in_X_Axis(372, 379, 21410, 200);
    Moving_in_X_Axis(379, 391, 23450, 200);
    singleRedCoinPs(2, 29290, 570, 1);
    singleRedCoinPs(3, 30690, 570, 1);
    singleRedCoinPs(4, 32090, 570, 1);
    Moving_in_X_Axis(391, 420, 34000, 580);
}

void PosRowSpikes(int First_index, int Last_index, int X_position, int Y_Position) {
    fa(i, First_index, Last_index) {
        spikes[i].SpikeSprite.setTexture(SpikeTex);
        spikes[i].SpikeSprite.setTextureRect(IntRect(0, 0, 142, 163));
        spikes[i].SpikeSprite.setScale(0.5f, 0.5f);
        spikes[i].SpikeSprite.setPosition(X_position + ((i - First_index) * 71), Y_Position);
    }
}

void Draw_jumppad() {
    jumppad[0].JumppadSprite.setPosition(2750, 590);
    jumppad[1].JumppadSprite.setPosition(5720, 590);
    jumppad[2].JumppadSprite.setPosition(6050, 590);
    jumppad[3].JumppadSprite.setPosition(6590, 590);
    jumppad[4].JumppadSprite.setPosition(7220, 590);
    jumppad[5].JumppadSprite.setPosition(8600, 590);
    jumppad[6].JumppadSprite.setPosition(7800, 590);
    jumppad[7].JumppadSprite.setPosition(11700, 590);
    jumppad[8].JumppadSprite.setPosition(10000, 590);
    jumppad[9].JumppadSprite.setPosition(10250, 590);
    jumppad[10].JumppadSprite.setPosition(10500, 590);
    jumppad[11].JumppadSprite.setPosition(10750, 590);
    jumppad[12].JumppadSprite.setPosition(11000, 590);
    jumppad[13].JumppadSprite.setPosition(18200, 590);
    jumppad[14].JumppadSprite.setPosition(21000, 590);
}

void draw_tiles() {
    setTilePos(tiles[0], 3400, 300);
    setTilePos(tiles[1], 4200, 200);
    setTilePos(tiles[2], 5000, 250);
    setTilePos(tiles[3], 6050, 240);
    setTilePos(tiles[4], 6375, 240);
    setTilePos(tiles[5], 6700, 240);
    setTilePos(tiles[6], 7025, 240);
    setTilePos(tiles[7], 7350, 240);
    setTilePos(tiles[8], 7675, 240);
    setTilePos(tiles[9], 21400, 240);
    setTilePos(tiles[10], 35700, 480);
    setTilePos(tiles[11], 36323, 480);
}
void draw_spikes() {
    PosRowSpikes(0, 28, 3400, 575);
    PosRowSpikes(28, 34, 6145, 575);
    PosRowSpikes(34, 41, 6695, 575);
    PosRowSpikes(41, 47, 7335, 575);
    PosRowSpikes(47, 55, 8825, 580);
    PosRowSpikes(55, 58, 12100, 575);
    PosRowSpikes(58, 61, 12400, 575);
    PosRowSpikes(61, 64, 12700, 575);
    PosRowSpikes(64, 94, 18500, 575);
    PosRowSpikes(94, 100, 21400, 575);
    PosRowSpikes(100, 131, 21800, 575);
    PosRowSpikes(131, 171, 24500, 575);
    fa(i, 0, 24) spikes2[i].SpikeSprite.setPosition(10005 + (i * 50), 113);
    fa(i, 0, 44) spikes2[i + 24].SpikeSprite.setPosition(24500 + (i * 65), 0);
}

void drawVerticalTile(int i, int x, int y) {
    Vertical_tiles_left[i].Vertical_Tiles_sprite.setPosition(x, y);
    Vertical_tiles_right[i].Vertical_Tiles_sprite.setPosition(x + 30, y);
    Vertical_tiles_left[i].tilecole.setPosition(x + 2, y - 10);
    Vertical_tiles_left[i].tilecole.setSize(Vector2f(70.f, 20.f));
}

void draw_vertical_tiles() {
    drawVerticalTile(0, 8750, 400);
    drawVerticalTile(1, 8750, 280);
    drawVerticalTile(2, 12030, 280);
    drawVerticalTile(3, 12030, 400);
    drawVerticalTile(4, 12325, 400);
    drawVerticalTile(5, 12325, 280);
    drawVerticalTile(6, 12625, 400);
    drawVerticalTile(7, 12625, 280);
}

void WormsPos(int index, int X_pos, int Y_pos, int start, int end) {
    Worms[index].EnemySprite.setPosition(X_pos, Y_pos);
    Worms[index].xStart = start;
    Worms[index].xEnd = end;
    Worms[index].Hit = false;
    Worms[index].DamageDelay = 0;
}
void CrabsPos(int index, int X_pos, int Y_pos, int start, int end) {
    Crabs[index].EnemySprite.setPosition(X_pos, Y_pos);
    Crabs[index].xStart = start;
    Crabs[index].xEnd = end;
    Crabs[index].Hit = false;
    Crabs[index].DamageDelay = 0;
}
void Enemy3Pos(int index, int X_pos, int Y_pos, int start, int end) {
    Enemy3[index].EnemySprite.setPosition(X_pos, Y_pos);
    Enemy3[index].xStart = start;
    Enemy3[index].xEnd = end;
    Enemy3[index].Hit = false;
    Enemy3[index].DamageDelay = 0;
}
void draw_enemies() {
    WormsPos(0, 1500, 580, 500, 1100);
    WormsPos(1, 8300, 585, 8100, 8500);
    CrabsPos(0, 1500, 585, 1500, 2500);
    CrabsPos(1, 10000, 585, 10000, 10500);
    CrabsPos(2, 10550, 585, 10550, 11000);
    Enemy3Pos(0, 6020, 166, 6020, 6887.5);
    Enemy3Pos(1, 7500, 166, 7000, 7967);
    Enemy3Pos(2, 21500, 166, 21410, 21580);
}

void DrawDisappearingTiles() {
    DisappearingTilesd(0, 18500, 250, 20);
    DisappearingTilesd(1, 18828, 250, 80);
    DisappearingTilesd(2, 19157, 250, 110);
    DisappearingTilesd(3, 19485, 250, 40);
    DisappearingTilesd(4, 19814, 250, 160);
    DisappearingTilesd(5, 20143, 250, 0);
}

void area2() {
    fa(i, 0, 6) {
        tiles2[i].TileSprite.setTexture(TileTx2);
        tiles2[i].TileSprite.setScale(1.3, 1.3);
        tiles2[i].TileColl.setSize(Vector2f(298.9f, 1.f));
    }
    fa(i, 0, 6) tiles2[i].TileSprite.setPosition(10000 + (i * 180), 60);

    fa(i, 0, 76) {
        spikes2[i].SpikeSprite.setTexture(SpikeTex2);
        spikes2[i].SpikeSprite.setTextureRect(IntRect(0, 0, 142, 163));
        spikes2[i].SpikeSprite.setScale(0.5f, 0.5f);
    }
}
void area3() {
    fa(i, 0, 20) animatedspikes_pos(i, 28000 + (i * 65), 50, 50, 521);
    fa(i, 0, 20) animatedspikes_pos(i + 20, 29400 + (i * 65), 50, 50, 521);
    fa(i, 0, 20) animatedspikes_pos(i + 40, 30800 + (i * 65), 50, 50, 521);
    fa(i, 0, 22) animatedspikes_pos(i + 60, 32200 + (i * 65), 50, 50, 521);
}
//leaderboard fUnctions defenitions

// push the into the leader board map from the code after the game play
void pushScore(pair<int, string> score) {
    leaderBoard.insert(score);
}

//clear leader board (file&map)

void clearLeaderBoard()
{
    leaderBoard.clear();
    //clearing the leader board file
    fstream LDFile;
    LDFile.open("leaderBoard.txt", ios::app);
    if (LDFile.is_open()) {
        LDFile << "#";
        //closing file stream
        LDFile.close();
    }
    else cout << "Failed to Open THis file";
}


// push the into the leader board file

void saveLDToFile() {
    fstream LDFile; //creating file stream
    LDFile.open("leaderBoard.txt", ios::out);

    if (LDFile.is_open()) {
        //saving the leaderboard elements
        multimap <  int, string > ::iterator itr;

        for (itr = (leaderBoard.begin()); itr != leaderBoard.end(); ++itr) {
            LDFile << itr->first << " " << itr->second << endl;

        }
        LDFile << "#";
        //closing file stream
        LDFile.close();
    }

    else cout << "Failed to Open THis file";
}

// loading scores from file

void loadLDFromFile() {
    bool Empty = false;
    string score, name;
    int intScore;
    fstream LDFile; //creating file stream
    LDFile.open("leaderBoard.txt", ios::in);

    if (LDFile.is_open()) {
        //loading data from the file
        while (!Empty) {
            LDFile >> score;
            if (score == "#") {
                Empty = true;
            }
            else {
                LDFile >> name;
                //converting the score  to int
                stringstream convert;
                convert << score;
                convert >> intScore;

                //pushing score into the leader board map
                pushScore(pair<int, string>(intScore, name));
            }
        }
        LDFile.close();
    }
    else cout << "Cannot Open This File";
}
