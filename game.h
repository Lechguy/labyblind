#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "dev_game_cinematic.h"
#include "dev_game_utils.h"
#include "dev_game_elements.h"
#include "dev_game_statements.h"
#include "dev_game_levelhandlerfactory.h"

class Game
{
    public:
    Game();
    ~Game();

    void update();
    void render();

    sf::RenderWindow* getWindow() const;

    private:
    void restartGame();
    void checkLoseTimer();
    void updateCountDown();
    void checkMenuTimer();
    void updateWhenKeyPressed();
    void updateCharacterMove();
        void moveShapesToTheRight();
        void moveShapesToTheLeft();
        void moveShapesUp();
        void moveShapesDown();
    void updateMenu();
    void updateMenuSelectedStatement();
    void updateSpeedIfBoost();
    void activateNightMode();

    /* '-----' Cinematic '-----' */
    Dev::Game::Cinematic _cinematic;
    bool _cinematicActive;

    /* '-----' SFML objects '-----' */
    sf::RenderWindow* _window;
    sf::Event       * _event;
    sf::Sound       * _sound;
    sf::SoundBuffer   _soundBuffer;
    bool              _soundLaunched;

    /* '-----' How to play '-----' */
    Dev::Game::Elements::HowToPlay _howToPlay;
    bool _howToPlayActive;

    /* '-----' Elements '-----' */
    Dev::Game::Elements::Background* _background;
    Dev::Game::Elements::Character * _character;
    Dev::Game::Elements::Light     * _light;
    
    /* '-----' Menus '-----' */
    void initializeMenus();
    Dev::Game::Statements::Menu*                         _htpMenu;
    Dev::Game::Statements::StaticStatement*              _htpMenuStaticStatement;
    std::vector<Dev::Game::Statements::BounceStatement*> _htpMenuBounceStatements;
    Dev::Game::Statements::Menu*                         _startMenu;
    Dev::Game::Statements::StaticStatement*              _startMenuStaticStatement;
    std::vector<Dev::Game::Statements::BounceStatement*> _startMenuBounceStatements;
    Dev::Game::Statements::Menu*                         _loseMenu;
    Dev::Game::Statements::StaticStatement*              _loseMenuStaticStatement;
    std::vector<Dev::Game::Statements::BounceStatement*> _loseMenuBounceStatements;
    Dev::Game::Statements::Menu*                         _lvlCompleteMenu;
    Dev::Game::Statements::StaticStatement*              _lvlCompleteMenuStaticStatement;
    std::vector<Dev::Game::Statements::BounceStatement*> _lvlCompleteMenuBounceStatements;
    Dev::Game::Statements::Menu*                         _winMenu;
    Dev::Game::Statements::StaticStatement*              _winMenuStaticStatement;
    std::vector<Dev::Game::Statements::BounceStatement*> _winMenuBounceStatements;

    /* '-----' Statements '----' */
    Dev::Game::Statements::SpawnStatement* _one;
    Dev::Game::Statements::SpawnStatement* _two;
    Dev::Game::Statements::SpawnStatement* _three;

    /* '-----' Game handling '-----' */
    void initializeLevel();
    Dev::Game::Handler::Levels _lvlHandler;
    int                        _lvlIndex;

    /* '-----' Game status '-----' */
    bool _lose;
    bool _win;
    bool _lvlComplete;

    /* '-----' Timer '-----' */
    sf::Clock * _gameTimer;
    float       _t;
    sf::Clock * _loseClock;
    bool        _loseTimerStarted;
    sf::Clock * _menuClock;
    bool        _menuTimeOut;
    bool        _menuTimerStarted;
    float       _menuTime;
    bool        _oneSec;
    bool        _twoSec;
    bool        _threeSec;

    /* '-----' Dynamic '-----' */
    float                       _moveInPxPerSecond;
    Dev::Game::Utils::Direction _direction;

    /* '-----' Boost '-----' */
    std::vector<Dev::Game::Elements::Boost *> _boosts;
};

#endif /*__GAME_H__*/