#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<sstream>
#include<cmath>
#include<fstream>

using namespace sf;
using namespace std;

//Player struct
struct Player {
    Texture PlayerTex;
    Sprite PlayerSprite;
    RectangleShape PlayerColl;
    Vector2f Velocity;
    int RightTexNumber = 0, IdleTexNumber = 0, TexDelay = 0, IdleDelay = 0, LeftTexNumber = 22;
    int scoreValue = 0, lives = 3, hitCounter = -1, deathDealy = 0, FinalScore = 0;
    bool start = false, Running = false, idle1 = false, txToggle = false, onTile = false;
    bool on_ground = true, hitRight = false, hitLeft = false, RunningSound = false;
} sonic;
//Boss
struct BossSt {
    Texture BossTx;
    Sprite BossSprite;
    RectangleShape HitBox;
    Vector2f Velocity;
    int hitCounter = 0, TexDelay = 0, TexNumber = 0, lives = 10;
    bool SceneStart = false, FightStart = false, MoveStart = false, MovingLeft = true, StartDelay = false;
};
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
    Sprite TileSprite2;
    RectangleShape TileColl2;
} tiles2[30];
//Coins
struct Coin {
    Sprite CoinSprite;
    int TexNumber = 0, TexDelay = 0;
} coins[400];

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
} enemies[20];

struct Enemies2 {
    Sprite EnemySprite;
    RectangleShape EnemyColl;
    int TexNumber = 0, TexDelay = 0, xStart = 0, xEnd = 0, DamageDelay = 0;
    bool MovingRight = true;
    bool Hit = false;
} enemies2[20];

struct Spikes {
    Texture SpikeTex;
    Sprite SpikeSprite;
    int TexNum = 0, TexDelay = 0;
}spikes[200];

struct Spikes2 {
    Texture SpikeTex2;
    Sprite SpikeSprite2;
}spikes2[100];

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
multimap <  int, string, greater<> > leaderBoard;

void saveLDToFile();
void clearLeaderBoard();
void pushScore(pair<int, string> score);
void loadLDFromFile();


// function
void setTilePos(FloatingTiles& tile, int x, int y, int x1 = 0, int x2 = 0);
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
void enemy1_coordinate(int index, int X_pos, int Y_pos, int start, int end);
void enemy2_coordinate(int index, int X_pos, int Y_pos, int start, int end);
void draw_enemies();
void area2();
//Textures and Variables
int enemy_cnt = 0; bool enemy_check = false;
Texture CoinTex;
Texture RedCoinTx;
Texture SpikeTex;
Texture vertical_tile_R;
Texture vertical_tile_L;
Texture TilesTx;
Texture TileTx2;
Texture SpikeTex2;

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

    for (int i = 0; i < 10; i++)
    {
        LDNames[i].setFont(font);
        scores[i].setFont(font);

        LDNames[i].setFillColor(Color::White);
        scores[i].setFillColor(Color::White);
    }


    string Sscore;
    int Iscore;
    int i;

    /// Loading tex
    Texture loadingMenuTex;
    loadingMenuTex.loadFromFile("Assets/Textures/loading.png");
    Sprite loadingMenuSprite(loadingMenuTex);
    Menu.clear();
    Menu.draw(loadingMenuSprite);
    Menu.display();
    //Settings choice
    Texture correctTex;
    correctTex.loadFromFile("Assets/Textures/correct-logo.png");
    Sprite correctSprite[2];
    correctSprite[0].setTexture(correctTex);
    correctSprite[0].setPosition(620, 240);
    correctSprite[0].setScale(0.032, 0.032);
    correctSprite[1].setTexture(correctTex);
    bool correctIsVisible = false;

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
    leaderbackSprite.setScale(0.7, 0.7);
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
    bool CreditClosed = true;
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

        //LDName.setPosition(1000, 500);
        //marko2

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
                    cout << it->second << "\t" << it->first << endl;
                    // cout << leaderBoard.size()<<endl;
                     //cout << endl <<it->second << "\t" << it->first << endl;
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
        if (creditSprite.getPosition().x >= 0) CreditStopAnim = true;
        if (!CreditStopAnim && !CreditClosed) creditSprite.move(7, 0);
        if (creditSprite.getPosition().x <= -1200) CBackAnim = false;

        if (CBackAnim && CreditClosed) creditSprite.move(-7, 0);


        // setting animation 
        if (SettingsBackgroundSprite.getPosition().x >= 0)
        {
            SettingStopAnim = true;
            correctIsVisible = true;
        }
        else correctIsVisible = false;

        if (!SettingStopAnim && !SettingsClosed) SettingsBackgroundSprite.move(7, 0);

        if (SettingsBackgroundSprite.getPosition().x <= -1200) SBackAnim = false;

        if (SBackAnim && SettingsClosed) SettingsBackgroundSprite.move(-7, 0);
        //leaderboard animation
        if (leaderSprite.getPosition().x >= 0) LeaderStopAnim = true;
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
                for (i = 0; i < leaderBoard.size(); i++)
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
                if (leaderbackIsVisible){
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
            if (MusicOn && correctIsVisible) Menu.draw(correctSprite[0]);
        }
        Menu.display();
    }
    // rendering window
    if (start && !Exit) {
        srand(time(0));
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
        // map player
        Sprite Map;
        Map.setTexture(MapTx);
        Map.setScale(1, 1.013);
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
        LevelPassed.setPosition(14800, 0);
        LevelPassed.setScale(0, 0);

        bool paused = false;
        int pauseDelay = 0;

        //BackgroundShip
        Texture ShipTx;
        ShipTx.loadFromFile("Assets/Textures/Tyara.png");

        for (int i = 0; i < 3; i++) {
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

        //Sky Bullet
        Texture SkyBulletTx;
        SkyBulletTx.loadFromFile("Assets/Textures/SkyBullet.png");
        int BulletsSpawnDelay = 0, BulletDelay = 0, BulletsSpawned = 0;
        bool SpawnStart = false, BulletsPositioned = false;
        for (int i = 0; i < 5; i++) {
            skyBullets[i].SkyBulletsSprite.setTexture(SkyBulletTx);
            skyBullets[i].SkyBulletsSprite.setTextureRect(IntRect(skyBullets[i].TexNumber * 114, 0, 114, 227));
            skyBullets[i].SkyBulletsSprite.setScale(0.8, 0.8);
            skyBullets[i].SkyBulletsSprite.setPosition(-500, -500);
            skyBullets[i].BulletColl.setSize(Vector2f(24, 108.8));
            //24 108.8
        }

        coinPos();
        //// sonic player
           // sonic texture
        sonic.PlayerTex.loadFromFile("Assets/Textures/Sonic-Character.png");
        sonic.PlayerSprite.setTexture(sonic.PlayerTex);
        // sonic sprite
        sonic.PlayerSprite.setTextureRect(IntRect(sonic.IdleTexNumber * 59.1578, 0, 59.1578, 60));
        sonic.PlayerColl.setSize(Vector2f(55.f, 80.f));
        sonic.PlayerColl.setPosition(205, 300);
        //sonic.PlayerColl.setPosition(14500, 300);
        sonic.PlayerSprite.setPosition(200, 300);
        //sonic.PlayerSprite.setPosition(14500, 300);
        sonic.PlayerSprite.setScale(2.5, 2.5);
        sonic.lives = 3;
        sonic.scoreValue = 0; sonic.hitCounter = -1;
        sonic.hitRight = false; sonic.hitLeft = false;
        //

        ///Jumppad Setting Texture
        for (int i = 0; i < 30; i++) {
            jumppad[i].JumppadSprite.setTexture(JumppadTx);
            jumppad[i].JumppadSprite.setTextureRect(IntRect(jumppad[i].Texnumber * 80, 543, 80, 66));
        }
        //Jumppad Position
        Draw_jumppad();
        //

        ///Floating Tiles Setting Texture
        for (int i = 0; i < 30; i++) {
            tiles[i].TileSprite.setTexture(TilesTx);
            tiles[i].TileSprite.setScale(1.3, 1.3);
            tiles[i].TileColl.setSize(Vector2f(298.9f, 1.f));
            tiles[i].LowerTileColl.setSize(Vector2f(298.9f, 1.f));
        }
        draw_tiles();
        //
        // vertical Walls setting 

        // for left;
        for (int i = 0; i < 10; i++) {
            Vertical_tiles_left[i].Vertical_Tiles_sprite.setTexture(vertical_tile_L);
            Vertical_tiles_left[i].Vertical_Tiles_sprite.setTextureRect(IntRect(0, 0, 46, 253));
            Vertical_tiles_right[i].Vertical_Tiles_sprite.setTexture(vertical_tile_R);
            Vertical_tiles_right[i].Vertical_Tiles_sprite.setTextureRect(IntRect(0, 0, 46, 253));
            if (i % 2 != 0) {
                Vertical_tiles_left[i].tilecole.setSize(Vector2f(1.f, 298.9f));
                Vertical_tiles_right[i].tilecole.setSize(Vector2f(1.f, 298.9f));
            }
        }
        draw_vertical_tiles();


        ///Enemies Setting Texture
        for (int i = 0; i < 20; i++) {
            enemies[i].EnemySprite.setTexture(EnemyTx);
            enemies[i].EnemyColl.setSize(Vector2f(110.f, 50.f));
            enemies[i].EnemyColl.setScale(Vector2f(1, 1));
            enemies[i].EnemySprite.setTextureRect(IntRect(enemies[i].TexNumber * 54, 345, 54, 29.2));
            enemies[i].EnemySprite.setScale(2.5f, 2.5f);
        }
        for (int i = 0; i < 20; i++) {
            enemies2[i].EnemySprite.setTexture(EnemyTx2);
            enemies2[i].EnemyColl.setSize(Vector2f(100.f, 60.f));
            enemies2[i].EnemyColl.setScale(Vector2f(1, 1));
            enemies2[i].EnemySprite.setTextureRect(IntRect(enemies2[i].TexNumber * 47, 411, 47, 30));
            enemies2[i].EnemySprite.setScale(2.5f, 2.5f);
        }
        draw_enemies();
        //
        
        //Spikes system
        for (int i = 0; i < 200; i++) {
            spikes[i].SpikeSprite.setTexture(SpikeTex);
            spikes[i].SpikeSprite.setTextureRect(IntRect(0, 0, 142, 163));
            spikes[i].SpikeSprite.setScale(0.5f, 0.5f);
        }
        draw_spikes();

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
        // the music of playgound
        Music BackgroundMusic;
        BackgroundMusic.openFromFile("Assets/Sounds/05-Labyrinth-Zone.ogg");
        BackgroundMusic.setVolume(5);
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

        area2();

        /// ground rectangle shape
        RectangleShape ground(Vector2f(17000, 70)); ground.setScale(1, 1); ground.setPosition(0, 640);
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
            if (sonic.lives > 0 && !paused && Boss.lives > 0) {
                if (sonic.TexDelay <= 3) sonic.TexDelay++;
                if (sonic.IdleDelay <= 10) sonic.IdleDelay++;
                for (int i = 0; i < 400; i++) {
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
                for (int i = 0; i < 6; i++) {
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
                for (int i = 0; i < 200; i++) {
                    if (spikes[i].SpikeSprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                        sonic.lives--;
                        sonic.Velocity.y = 10;
                        SpikeDeathAudio.play();
                    }
                    else if (spikes[i].SpikeSprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0)) {
                        if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                        if (sonic.PlayerColl.getPosition().x >= spikes[i].SpikeSprite.getPosition().x) sonic.hitRight = true;
                        else sonic.hitLeft = true;
                        sonic.hitCounter = 50;
                        sonic.Velocity.y = 7;
                        sonic.PlayerSprite.move(0, -10);
                        SpikeDeathAudio.play();
                    }
                    if (i < 50) {
                        if (spikes2[i].SpikeSprite2.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                            if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > spikes2[i].SpikeSprite2.getPosition().x) sonic.hitRight = true;
                            else sonic.hitLeft = true;
                            sonic.hitCounter = 50;
                            sonic.Velocity.y = -7;
                            sonic.PlayerSprite.move(0, 10);
                            SpikeDeathAudio.play();
                        }
                    }
                }

                //Hit Counter
                if (sonic.hitCounter <= 50 && sonic.hitCounter > -1) {
                    sonic.hitCounter--;
                    sonic.PlayerSprite.setColor(Color(255, 0, 0, 220));
                }
                else if (sonic.hitCounter == -1) sonic.PlayerSprite.setColor(Color::White);

                //Idle Animation
                if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::Space)
                    && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Up)) {
                    sonic.Running = false;
                    sonic.txToggle = false;
                    sonic.RunningSound = false;
                    if (sonic.IdleDelay >= 10) {
                        sonic.IdleDelay = 0;
                        if (sonic.IdleTexNumber == 7) sonic.idle1 = true;
                        else if (sonic.IdleTexNumber == 0) sonic.idle1 = false;
                        if (sonic.idle1) sonic.IdleTexNumber--;
                        else sonic.IdleTexNumber++;
                        if (!sonic.Running) sonic.PlayerSprite.setTextureRect(IntRect(sonic.IdleTexNumber * 48.75, 0 * 60, 48.75, 51));
                    }
                }

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    std::cout << Mouse::getPosition(window).x << ' ' << Mouse::getPosition(window).y << '\n';
                }

                //Moving Right
                if (!Boss.SceneStart) {
                    if ((Boss.FightStart && sonic.PlayerSprite.getPosition().x < 15900) || !Boss.FightStart) {
                        if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) && !sonic.hitLeft && !sonic.hitRight) {
                            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                                // Running Sonic Right
                                sonic.PlayerSprite.move(12, 0);
                                if (!sonic.RunningSound) {
                                    RunningSound.play();
                                    sonic.RunningSound = true;
                                }
                                if (sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStart) {
                                    camera.move(12, 0);
                                    text.move(12, 0);
                                    lives.move(12, 0);
                                    SonicFace.move(12, 0);
                                    pauseMenu.move(12, 0);
                                }
                                if (sonic.TexDelay >= 3) {
                                    sonic.RightTexNumber++;
                                    sonic.TexDelay = 0;
                                    if (sonic.Running) if (sonic.RightTexNumber >= 22) sonic.RightTexNumber = 19;
                                    else sonic.RightTexNumber = (sonic.RightTexNumber % 12) + 12;
                                    if (sonic.RightTexNumber >= 17) sonic.Running = true;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.86, 1 * 60, 48.86, 51));
                                }
                            }
                            else {
                                // Walking Sonic Right
                                sonic.PlayerSprite.move(9, 0);
                                if (sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStart) {
                                    camera.move(9, 0);
                                    text.move(9, 0);
                                    lives.move(9, 0);
                                    SonicFace.move(9, 0);
                                    pauseMenu.move(9, 0);
                                }
                                if (sonic.TexDelay >= 3) {
                                    sonic.RightTexNumber++;
                                    sonic.TexDelay = 0;
                                    sonic.RightTexNumber %= 11;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 48.86, 1 * 60, 48.86, 51));
                                }
                            }
                        }
                    }

                    //Moving Left
                    if ((Boss.FightStart && sonic.PlayerSprite.getPosition().x >= 14800) || !Boss.FightStart) {
                        if ((Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Left)) && !sonic.hitLeft && !sonic.hitRight && sonic.PlayerSprite.getPosition().x > 0) {
                            if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                                // Running Sonic Left                
                                sonic.PlayerSprite.move(-12, 0);
                                if (!sonic.RunningSound) {
                                    RunningSound.play();
                                    sonic.RunningSound = true;
                                }
                                if (sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStart) {
                                    camera.move(-12, 0);
                                    text.move(-12, 0);
                                    lives.move(-12, 0);
                                    SonicFace.move(-12, 0);
                                    pauseMenu.move(-12, 0);
                                }
                                if (sonic.TexDelay >= 3) {
                                    sonic.LeftTexNumber--;
                                    sonic.TexDelay = 0;
                                    if (sonic.Running) if (sonic.LeftTexNumber <= 0) sonic.LeftTexNumber = 3;
                                    else if (sonic.LeftTexNumber <= 0) sonic.LeftTexNumber = 12;
                                    if (sonic.LeftTexNumber <= 6) sonic.Running = true;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.86, 3 * 60, 48.86, 51));
                                }
                            }
                            else {
                                // Moving Sonic Left
                                sonic.PlayerSprite.move(-9, 0);
                                if (sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStart) {
                                    camera.move(-9, 0);
                                    text.move(-9, 0);
                                    lives.move(-9, 0);
                                    SonicFace.move(-9, 0);
                                    pauseMenu.move(-9, 0);
                                }
                                if (sonic.TexDelay >= 3) {
                                    sonic.LeftTexNumber--;
                                    sonic.TexDelay = 0;
                                    if (sonic.txToggle) if (sonic.LeftTexNumber <= 12) sonic.LeftTexNumber = 22;
                                    else if (sonic.LeftTexNumber <= 12) sonic.LeftTexNumber = 22;
                                    if (sonic.LeftTexNumber <= 17) sonic.txToggle = true;
                                    sonic.PlayerSprite.setTextureRect(IntRect(sonic.LeftTexNumber * 48.86, 3 * 60, 48.86, 51));
                                }
                            }
                        }
                    }
                }

                //Hit Right and Left
                if (sonic.hitRight) {
                    if ((sonic.PlayerSprite.getPosition().x <= 15900 && Boss.FightStart) || !Boss.FightStart) sonic.PlayerSprite.move(5, 0);
                    if (sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStart) {
                        camera.move(5, 0);
                        text.move(5, 0);
                        lives.move(5, 0);
                        SonicFace.move(5, 0);
                        pauseMenu.move(5, 0);
                    }
                    if (sonic.on_ground || sonic.onTile) sonic.hitRight = false;
                }
                else if (sonic.hitLeft) {
                    if ((sonic.PlayerSprite.getPosition().x > 14800 && Boss.FightStart) || !Boss.FightStart) sonic.PlayerSprite.move(-5, 0);
                    if (sonic.PlayerSprite.getPosition().x >= 200 && !Boss.FightStart) {
                        camera.move(-5, 0);
                        text.move(-5, 0);
                        lives.move(-5, 0);
                        SonicFace.move(-5, 0);
                        pauseMenu.move(-5, 0);
                    }
                    if (sonic.on_ground || sonic.onTile) sonic.hitLeft = false;
                }

                //Enemy System
                for (int i = 0; i < 20; i++) {
                    if (enemies[i].TexDelay <= 8) enemies[i].TexDelay++;
                    if (enemies[i].MovingRight) {
                        enemies[i].EnemySprite.move(4, 0);
                        if (enemies[i].TexDelay >= 8) {
                            enemies[i].TexDelay = 0;
                            enemies[i].TexNumber++;
                            enemies[i].TexNumber %= 11;
                            enemies[i].EnemySprite.setTextureRect(IntRect(enemies[i].TexNumber * 58, 345, 58, 29.2));
                        }
                        if (enemies[i].EnemySprite.getPosition().x >= enemies[i].xEnd) enemies[i].MovingRight = false;
                    }
                    else {
                        enemies[i].EnemySprite.move(-4, 0);
                        if (enemies[i].TexDelay >= 8) {
                            enemies[i].TexDelay = 0;
                            enemies[i].TexNumber--;
                            if (enemies[i].TexNumber <= 0) enemies[i].TexNumber = 10;
                            enemies[i].EnemySprite.setTextureRect(IntRect(enemies[i].TexNumber * 58, 313, 58, 29.2));
                        }
                        if (enemies[i].EnemySprite.getPosition().x <= enemies[i].xStart) enemies[i].MovingRight = true;
                    }

                    if (enemies[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                        if (!enemies[i].Hit) enemies[i].Hit = true;
                        else {
                            enemies[i].EnemySprite.setScale(0, 0);
                            enemies[i].EnemyColl.setScale(0, 0);
                            sonic.scoreValue += 100;
                            EnemyScore.setCharacterSize(50);
                            EnemyScore.setPosition(enemies[i].EnemyColl.getPosition().x + 60, enemies[i].EnemyColl.getPosition().y + 60);
                            EnemyScoreCounter = 100;
                        }
                        sonic.Velocity.y = 10;
                        EnemyDamageSound.play();
                    }
                    else if (enemies[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0)) {
                        if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                        if (sonic.PlayerSprite.getPosition().x > enemies[i].EnemySprite.getPosition().x) sonic.hitRight = true;
                        else sonic.hitLeft = true;
                        sonic.hitCounter = 50;
                        sonic.Velocity.y = 8;
                        sonic.PlayerSprite.move(0, -10);
                        SpikeDeathAudio.play();
                    }
                    if (enemies[i].Hit && enemies[i].DamageDelay <= 30 && enemies[i].DamageDelay >= 0) {
                        enemies[i].DamageDelay++;
                        enemies[i].EnemySprite.setColor(Color(255, 0, 0, 200));
                    }
                    else if (enemies[i].Hit && enemies[i].DamageDelay >= 30) {
                        enemies[i].EnemySprite.setColor(Color::White);
                        enemies[i].DamageDelay = -1;
                    }
                    enemies[i].EnemyColl.setPosition(enemies[i].EnemySprite.getPosition().x + 15, enemies[i].EnemySprite.getPosition().y + 8);
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

                    if (enemies2[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && !sonic.on_ground && sonic.Velocity.y <= 0) {
                        if (!enemies2[i].Hit) enemies2[i].Hit = true;
                        else {
                            enemies2[i].EnemySprite.setScale(0, 0);
                            enemies2[i].EnemyColl.setScale(0, 0);
                            sonic.scoreValue += 100;
                            EnemyScore.setCharacterSize(50);
                            EnemyScore.setPosition(enemies2[i].EnemyColl.getPosition().x + 60, enemies2[i].EnemyColl.getPosition().y);
                            EnemyScoreCounter = 100;
                        }
                        sonic.Velocity.y = 10;
                        EnemyDamageSound.play();
                    }
                    else if ((enemies2[i].EnemyColl.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds()) && (sonic.on_ground || sonic.Velocity.y > 0))) {
                        if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                        if (sonic.PlayerSprite.getPosition().x > enemies2[i].EnemySprite.getPosition().x) sonic.hitRight = true;
                        else sonic.hitLeft = true;
                        sonic.hitCounter = 50;
                        sonic.Velocity.y = 8;
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
                    enemies2[i].EnemyColl.setPosition(enemies2[i].EnemySprite.getPosition().x + 10, enemies2[i].EnemySprite.getPosition().y + 8);
                }

                // Jumppad System
                for (int i = 0; i < 30; i++) {
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
                else {
                    bool found = false;
                    for (int i = 0; i < 30; i++) {
                        if (sonic.PlayerSprite.getGlobalBounds().intersects(tiles[i].TileColl.getGlobalBounds()) && sonic.Velocity.y <= 0 && sonic.PlayerSprite.getPosition().y + 100 < tiles[i].TileSprite.getPosition().y) {
                            found = true;
                            sonic.onTile = true;
                            sonic.Velocity.y = 0;
                        }
                        if (sonic.PlayerColl.getGlobalBounds().intersects(tiles[i].LowerTileColl.getGlobalBounds()) && !sonic.on_ground) sonic.Velocity.y = -2;
                    }
                    for (int i = 0; i < 10; i++)
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
                    if (!found) {
                        sonic.on_ground = false;
                        sonic.onTile = false;
                    }
                    if (!sonic.on_ground && !sonic.onTile) {
                        sonic.RightTexNumber++;
                        sonic.RightTexNumber %= 16;
                        sonic.PlayerSprite.setTextureRect(IntRect(sonic.RightTexNumber * 49, 2 * 60, 49, 48));
                        sonic.Velocity.y -= 0.3;
                    }
                    if (sonic.onTile) {
                        sonic.Velocity.y = 0;
                        if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
                            sonic.Velocity.y = 10;
                        }
                    }
                }

                for (int i = 0; i < 10; i++) {
                    if (Vertical_tiles_left[i].Vertical_Tiles_sprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                        if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                            sonic.PlayerSprite.move(-15, 0);
                            camera.move(-15, 0);
                            text.move(-15, 0);
                            lives.move(-15, 0);
                            SonicFace.move(-15, 0);
                            pauseMenu.move(-15, 0);
                        }
                        else {
                            sonic.PlayerSprite.move(-12, 0);
                            camera.move(-12, 0);
                            text.move(-12, 0);
                            lives.move(-12, 0);
                            SonicFace.move(-12, 0);
                            pauseMenu.move(-12, 0);
                        }
                    }
                    if (Vertical_tiles_right[i].Vertical_Tiles_sprite.getGlobalBounds().intersects(sonic.PlayerColl.getGlobalBounds())) {
                        if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                            sonic.PlayerSprite.move(15, 0);
                            camera.move(15, 0);
                            text.move(15, 0);
                            lives.move(15, 0);
                            SonicFace.move(15, 0);
                            pauseMenu.move(15, 0);
                        }
                        else {
                            sonic.PlayerSprite.move(12, 0);
                            camera.move(12, 0);
                            text.move(12, 0);
                            lives.move(12, 0);
                            SonicFace.move(12, 0);
                            pauseMenu.move(12, 0);
                        }
                    }
                }
                sonic.PlayerSprite.move(0, -sonic.Velocity.y);
                sonic.PlayerColl.setPosition(sonic.PlayerSprite.getPosition().x + 28, sonic.PlayerSprite.getPosition().y + 30);
                window.setView(camera);

                //Background Ship
                for (int i = 0; i < 3; i++) {
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
                        }
                        else {
                            if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                            if (sonic.PlayerSprite.getPosition().x > floatingShips[i].ShipSprite.getPosition().x) sonic.hitRight = true;
                            else sonic.hitLeft = true;
                            sonic.hitCounter = 50;
                            if (sonic.PlayerSprite.getPosition().y > floatingShips[i].ShipSprite.getPosition().y + 73.2)
                                sonic.Velocity.y = -4;
                            else
                                sonic.Velocity.y = 7;
                            SpikeDeathAudio.play();
                        }
                    }
                    //cout << floatingShips[i].ShipSprite.getPosition().x << ' ' << floatingShips[i].ShipSprite.getPosition().y << '\n';
                }

                if (sonic.lives <= 0) {
                    sonic.PlayerSprite.setTextureRect(IntRect(278, 240, 48.86, 51));
                    sonic.deathDealy = 10;
                    BackgroundMusic.stop();
                    GameoverAudio.play();
                }
                if (Boss.TexDelay <= 30 && (!Boss.MoveStart || Boss.StartDelay)) Boss.TexDelay++;
                if (sonic.PlayerSprite.getPosition().x >= 15000 && !Boss.FightStart) {
                    Boss.SceneStart = true;
                }
                if (Boss.SceneStart) {
                    if (Boss.TexDelay >= 10) {
                        Boss.TexNumber++;
                        Boss.TexDelay = 0;
                        Boss.BossSprite.setTextureRect(IntRect(Boss.TexNumber * 100, 800, 100, 64));
                    }
                    if (Boss.TexNumber == 5) {
                        Boss.FightStart = true;
                        Boss.SceneStart = false;
                        Boss.TexDelay = 0;
                        Boss.TexNumber = 0;
                    }
                }
                if (Boss.FightStart) {
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
                            for (int i = 0; i < 5; i++) {
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
                            cout << BulletsSpawned << '\n';
                        }
                    }
                    for (int i = 0; i < 5; i++) {
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
                            SpikeDeathAudio.play();
                        }
                    }
                    if (SpawnStart && !skyBullets[4].SkyBulletsSprite.getScale().x) {
                        SpawnStart = false;
                        BulletsPositioned = false;
                        BulletsSpawnDelay = 0;
                        BulletsSpawned = 0;
                    }
                }
                if (sonic.PlayerColl.getGlobalBounds().intersects(Boss.HitBox.getGlobalBounds())) {
                    if (sonic.Velocity.y >= 0) {
                        if (!sonic.hitLeft && !sonic.hitRight && sonic.hitCounter == -1) sonic.lives--;
                        if (sonic.PlayerSprite.getPosition().x > Boss.HitBox.getPosition().x + 49) sonic.hitRight = true;
                        else sonic.hitLeft = true;
                        sonic.hitCounter = 50;
                        sonic.Velocity.y = 8;
                        sonic.PlayerSprite.move(0, -10);
                        SpikeDeathAudio.play();
                    }
                    else if (sonic.Velocity.y < 0) {
                        if (Boss.hitCounter == -1) {
                            Boss.lives--;
                            Boss.hitCounter = 50;
                        }
                        sonic.Velocity.y = 10;
                        if (!Boss.MovingLeft) Boss.BossSprite.setTextureRect(IntRect(111, 875, 86, 60));
                        else Boss.BossSprite.setTextureRect(IntRect(107, 952, 86, 60));
                    }
                }
                if (Boss.hitCounter != -1) Boss.hitCounter--;
                Boss.HitBox.setPosition(Boss.BossSprite.getPosition().x + 25, Boss.BossSprite.getPosition().y + 38);
            }
            else if (paused) {
                pauseMenu.setScale(1.05, 1);
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    std::cout << Mouse::getPosition(window).x << ' ' << Mouse::getPosition(window).y << '\n';
                }
                if (Mouse::getPosition(window).x >= 440 && Mouse::getPosition(window).x <= 778 && Mouse::getPosition(window).y >= 344 && Mouse::getPosition(window).y <= 409) {
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        paused = false;
                    }
                }
                if (Mouse::getPosition(window).x >= 420 && Mouse::getPosition(window).x <= 865 && Mouse::getPosition(window).y >= 434 && Mouse::getPosition(window).y <= 480) {
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        window.close();
                        BackgroundMusic.stop();
                        main();
                    }
                }
            }


            //marko
            else if (Boss.lives <= 0) {
                LevelPassed.setScale(1, 1);
                if (Mouse::getPosition(window).x >= 300 && Mouse::getPosition(window).x <= 900 && Mouse::getPosition(window).y >= 632 && Mouse::getPosition(window).y <= 711) {
                    if (Mouse::isButtonPressed(Mouse::Left)) {

                        // saving score to leaderboard
                        pushScore(pair<int, string>(sonic.scoreValue, playerInput));
                        saveLDToFile();

                        window.close();
                        BackgroundMusic.stop();
                        main();
                    }
                }
                FinalScore.setFillColor(Color::Black);
                FinalScore.setPosition(15330, 300);
                FinalScore.setCharacterSize(60);
                if (sonic.FinalScore < sonic.scoreValue) {
                    sonic.FinalScore += 7;
                }
                if (sonic.FinalScore > sonic.scoreValue) sonic.FinalScore = sonic.scoreValue;
            }
            else {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    std::cout << Mouse::getPosition(window).x << ' ' << Mouse::getPosition(window).y << '\n';
                }
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
                                main();
                            }
                        }
                        if (sonic.FinalScore < sonic.scoreValue) sonic.FinalScore += 7;
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
            for (int i = 0; i < 3; i++) window.draw(floatingShips[i].ShipSprite);
            for (int i = 0; i < 9; i++) window.draw(tiles[i].TileSprite);
            for (int i = 0; i < 13; i++) window.draw(jumppad[i].JumppadSprite);
            for (int i = 0; i < 2; i++) window.draw(Red_coins[i].CoinSprite);
            for (int i = 0; i < 64; i++) window.draw(spikes[i].SpikeSprite);
            for (int i = 0; i < 6; i++) window.draw(tiles2[i].TileSprite2);
            for (int i = 0; i < 24; i++) window.draw(spikes2[i].SpikeSprite2);
            for (int i = 0; i < 320; i++) window.draw(coins[i].CoinSprite);
            for (int i = 0; i < 8; i++) {
                window.draw(Vertical_tiles_right[i].Vertical_Tiles_sprite);
                window.draw(Vertical_tiles_left[i].Vertical_Tiles_sprite);
            }
            for (int i = 0; i < 2; i++) window.draw(enemies[i].EnemySprite);
            for (int i = 0; i < 3; i++) window.draw(enemies2[i].EnemySprite);
            window.draw(Boss.BossSprite);
            //window.draw(Boss.HitBox);
            window.draw(sonic.PlayerSprite);
            for (int i = 0; i < 5; i++) window.draw(skyBullets[i].SkyBulletsSprite);
            window.draw(SonicFace);
            window.draw(text);
            window.draw(lives);
            window.draw(pauseMenu);
            window.draw(Gameover);
            window.draw(LevelPassed);
            window.draw(FinalScore);
            window.draw(EnemyScore);
            window.display();
        }
    }

    return 0;
}

void setTilePos(FloatingTiles& tile, int x, int y, int x2, int y2) {
    tile.TileSprite.setPosition(x, y);
    tile.TileColl.setPosition(x + 15, y);
    tile.LowerTileColl.setPosition(x + 15, y + 48);
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
        coins[i].CoinSprite.setScale(1, 1);
    }
}
void Moving_in_X_Y(int First_index, int Last_index, int X_position, int Y_Position, int X_increament, int Y_increament) {
    for (int i = First_index; i < Last_index; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition((X_position + ((i - First_index) * X_increament)), (Y_Position - ((i - First_index) * Y_increament)));
        coins[i].CoinSprite.setScale(1, 1);
    }
}
void Moving_in_Y_Axis(int First_index, int Last_index, int X_position, int Y_Position, int increase = 45) {
    for (int i = First_index; i < Last_index; i++) {
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
    for (int i = First_index; i < Last_index; i++) {
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
    for (int i = 38; i < 39; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1465, 375);
        coins[i].CoinSprite.setScale(1, 1);
    }
    for (int i = 39; i < 41; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1370 + ((i - 38) * 35), 510 - ((i - 37) * 35));
        coins[i].CoinSprite.setScale(1, 1);
    }
    for (int i = 42; i < 45; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1520 + ((i - 41) * 35), 335 + ((i - 41) * 35));
        coins[i].CoinSprite.setScale(1, 1);
    }
    for (int i = 47; i < 50; i++) {
        coins[i].CoinSprite.setTexture(CoinTex);
        coins[i].CoinSprite.setTextureRect(IntRect(0, 460, 40, 39));
        coins[i].CoinSprite.setPosition(1400 + ((i - 47) * 35), 540 + ((i - 47) * 25));
        coins[i].CoinSprite.setScale(1, 1);
    }
    for (int i = 51; i < 54; i++) {
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
    singleRedCoinPs(0, 1980, 350);
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
}

void PosRowSpikes(int First_index, int Last_index, int X_position, int Y_Position) {
    for (int i = First_index; i < Last_index; i++) {
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
}

void draw_tiles() {
    setTilePos(tiles[0], 3400, 300, -46, -46);
    setTilePos(tiles[1], 4200, 200, -46, -46);
    setTilePos(tiles[2], 5000, 250, -46, -46);
    setTilePos(tiles[3], 6050, 240, 6050, 240);
    setTilePos(tiles[4], 6375, 240, 6375, 240);
    setTilePos(tiles[5], 6700, 240, 6700, 240);
    setTilePos(tiles[6], 7025, 240, 7025, 240);
    setTilePos(tiles[7], 7350, 240, 7350, 240);
    setTilePos(tiles[8], 7675, 240, 7675, 240);

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
    for (int i = 0; i < 30; i++) spikes2[i].SpikeSprite2.setPosition(10000 + (i * 50), 113);
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

void enemy1_coordinate(int index, int X_pos, int Y_pos, int start, int end) {
    enemies[index].EnemySprite.setPosition(X_pos, Y_pos);
    enemies[index].xStart = start;
    enemies[index].xEnd = end;
    enemies[index].Hit = false;
    enemies[index].DamageDelay = 0;
}
void enemy2_coordinate(int index, int X_pos, int Y_pos, int start, int end) {
    enemies2[index].EnemySprite.setPosition(X_pos, Y_pos);
    enemies2[index].xStart = start;
    enemies2[index].xEnd = end;
    enemies2[index].Hit = false;
    enemies2[index].DamageDelay = 0;
}
void draw_enemies() {
    enemy1_coordinate(0, 1500, 580, 500, 1100);
    enemy2_coordinate(0, 1500, 585, 1500, 2500);
    enemy1_coordinate(1, 8300, 585, 8100, 8500);
    enemy2_coordinate(1, 10000, 585, 10000, 10500);
    enemy2_coordinate(2, 10550, 585, 10550, 11000);
}

void area2() {
    for (int i = 0; i < 30; i++) {
        tiles2[i].TileSprite2.setTexture(TileTx2);
        tiles2[i].TileSprite2.setScale(1.3, 1.3);
        tiles2[i].TileColl2.setSize(Vector2f(298.9f, 1.f));
    }
    for (int i = 0; i < 30; i++) tiles2[i].TileSprite2.setPosition(10000 + (i * 180), 60);

    for (int i = 0; i < 24; i++) {
        spikes2[i].SpikeSprite2.setTexture(SpikeTex2);
        spikes2[i].SpikeSprite2.setTextureRect(IntRect(0, 0, 142, 163));
        spikes2[i].SpikeSprite2.setScale(0.5f, 0.5f);
    }
}
//leaderboard finctions defenitions



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

void loadLDFromFile(){
    bool Empty = false;
    string score, name;
    int intSCore;
    fstream LDFile; //creating file stream
    LDFile.open("leaderBoard.txt", ios::in);

    if (LDFile.is_open()) {
        //loading data from the file
        while (!Empty) {
            LDFile >> score;
            if (score == "#") {
                Empty = true;
            } else {
                LDFile >> name;
                //converting the score  to int
                stringstream convert;
                convert << score;
                convert >> intSCore;

                //pushing score into the leader board map
                pushScore(pair<int, string>(intSCore, name));
            }
        }
        LDFile.close();
    }
    else cout << "Cannot Open This File";
}
