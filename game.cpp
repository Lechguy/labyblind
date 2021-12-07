#include "game.h"
#include "path.h"
#include "color.h"
#include <cmath>
#include <map>
#include <cstdlib>

Game::Game() :
_moveInPxPerSecond    (250.f),
_cinematicActive      (false),
_lose                 (false),
_lvlComplete          (false),
_win                  (false),
_loseTimerStarted     (false),
_menuTimeOut          (false),
_menuTimerStarted     (false),
_oneSec               (false),
_twoSec               (false),
_threeSec             (false),
_lvlIndex             (0),
_window               (nullptr),
_event                (nullptr),
_loseClock            (nullptr),
_menuClock            (nullptr),
_background           (nullptr),
_character            (nullptr),
_light                (nullptr),
_one                  (nullptr),
_two                  (nullptr),
_three                (nullptr),
_direction            (Dev::Game::Utils::Direction::NONE),
_soundLaunched        (false),
_t                    (0.f),
_howToPlayActive      (false),
_menuTime             (0.f)
{
    /* '-----' Framwork objects '-----' */
    _window        = new sf::RenderWindow(sf::VideoMode(1000,1000), "LabyBlind !", sf::Style::None);
    _window->setFramerateLimit(60);
    _event         = new sf::Event;
    _sound         = new sf::Sound;
    _soundBuffer.loadFromFile(Path::Sounds + "countDown.wav");
    _sound->setBuffer(_soundBuffer);
    _gameTimer     = new sf::Clock;

    /* '-----' Statements '-----' */
    initializeMenus();

    /* '-----' Widgets relative to level '-----' */
    initializeLevel();
}

Game::~Game()
{
    delete _window;
    delete _event;
    delete _sound;
    delete _gameTimer;
    delete _loseClock;
    delete _menuClock;
    delete _background;
    delete _character;
    delete _light;
    delete _one;
    delete _two;
    delete _three;
    for (Dev::Game::Elements::Boost * i : _boosts)
    {
        delete i;
    }
    _boosts.clear();
    delete _htpMenuStaticStatement;
    for (Dev::Game::Statements::BounceStatement * i : _htpMenuBounceStatements)
    {
        delete i;
    }
    _htpMenuBounceStatements.clear();
    delete _htpMenu;
    delete _loseMenuStaticStatement;
    for (Dev::Game::Statements::BounceStatement * i : _loseMenuBounceStatements)
    {
        delete i;
    }
    _loseMenuBounceStatements.clear();
    delete _loseMenu;
    delete _lvlCompleteMenuStaticStatement;
    for (Dev::Game::Statements::BounceStatement * i : _lvlCompleteMenuBounceStatements)
    {
        delete i;
    }
    _lvlCompleteMenuBounceStatements.clear();
    delete _lvlCompleteMenu;
    delete _startMenuStaticStatement;
    for (Dev::Game::Statements::BounceStatement * i : _startMenuBounceStatements)
    {
        delete i;
    }
    _startMenuBounceStatements.clear();
    delete _startMenu;
    delete _winMenuStaticStatement;
    for (Dev::Game::Statements::BounceStatement * i : _winMenuBounceStatements)
    {
        delete i;
    }
    _winMenuBounceStatements.clear();
    delete _winMenu;
}

sf::RenderWindow*
Game::getWindow() const
{
    return _window;
}

void
Game::initializeMenus()
{
    _loseMenuStaticStatement = new Dev::Game::Statements::StaticStatement("game over",
                                                                          Path::Fonts + "aldoTheApache.ttf",
                                                                          170, Color::Slight::RED);
    _loseMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("try again",
                                                                                   Path::Fonts + "aldoTheApache.ttf",
                                                                                   700));
    _loseMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("quit",
                                                                                   Path::Fonts + "aldoTheApache.ttf",
                                                                                   800));
    _loseMenu = new Dev::Game::Statements::Menu(_loseMenuStaticStatement, _loseMenuBounceStatements);

    _lvlCompleteMenuStaticStatement = new Dev::Game::Statements::StaticStatement("level complete",
                                                                         Path::Fonts + "aldoTheApache.ttf",
                                                                         140, Color::Slight::GREEN);
    _lvlCompleteMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("next level",
                                                                                   Path::Fonts + "aldoTheApache.ttf",
                                                                                   700));
    _lvlCompleteMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("quit",
                                                                                   Path::Fonts + "aldoTheApache.ttf",
                                                                                   800));
    _lvlCompleteMenu = new Dev::Game::Statements::Menu(_lvlCompleteMenuStaticStatement, _lvlCompleteMenuBounceStatements);

    _startMenuStaticStatement = new Dev::Game::Statements::StaticStatement("labyblind",
                                                                           Path::Fonts + "aldoTheApache.ttf",
                                                                           170, Color::Slight::BLUE);
    _startMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("start",
                                                                                   Path::Fonts + "aldoTheApache.ttf",
                                                                                   650));
    _startMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("how to play?",
                                                                                   Path::Fonts + "aldoTheApache.ttf",
                                                                                   750));
    _startMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("quit",
                                                                                   Path::Fonts + "aldoTheApache.ttf",
                                                                                   850));
    _startMenu = new Dev::Game::Statements::Menu(_startMenuStaticStatement, _startMenuBounceStatements);

    _winMenuStaticStatement = new Dev::Game::Statements::StaticStatement("you win!",
                                                                           Path::Fonts + "aldoTheApache.ttf",
                                                                           200, Color::Slight::BLUE);
    _winMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("quit",
                                                                                  Path::Fonts + "aldoTheApache.ttf",
                                                                                  750));
    _winMenu = new Dev::Game::Statements::Menu(_winMenuStaticStatement, _winMenuBounceStatements);

    _htpMenuStaticStatement = nullptr;
    _htpMenuBounceStatements.push_back(new Dev::Game::Statements::BounceStatement("main menu",
                                                                                  Path::Fonts + "aldoTheApache.ttf",
                                                                                  500));
    _htpMenu = new Dev::Game::Statements::Menu(_htpMenuStaticStatement, _htpMenuBounceStatements);
}

void
Game::initializeLevel()
{
    _lose            = false;
    _lvlComplete     = false;
    _cinematicActive = (_lvlIndex == 0);

    /* '-----' Timers '-----' */
    delete _loseClock;
    _loseClock = new sf::Clock;
    _loseTimerStarted = false;

    delete _menuClock;
    _menuClock = new sf::Clock;
    _menuTimeOut      = false;
    _menuTimerStarted = false;

    /* '-----' Statements '----' */
    delete _one;
    _one      = new Dev::Game::Statements::SpawnStatement("1", Path::Fonts + "aldoTheApache.ttf");
    _oneSec   = false;
    delete _two;
    _two      = new Dev::Game::Statements::SpawnStatement("2", Path::Fonts + "aldoTheApache.ttf");
    _twoSec   = false;
    delete _three;
    _three    = new Dev::Game::Statements::SpawnStatement("3", Path::Fonts + "aldoTheApache.ttf");
    _threeSec = false;

    /* '-----' Sound '-----' */
    _soundLaunched = false;

    /* '-----' Elements '-----' */
    _direction = Dev::Game::Utils::Direction::NONE;
    if (_cinematicActive)
    {
        _moveInPxPerSecond = 450.f;
    }
    else
    {
        _moveInPxPerSecond = 250.f;
    }
    delete _background;
    _background = new Dev::Game::Elements::Background(_lvlHandler.getLevel(_lvlIndex).getNbPx           (),
                                                      _lvlHandler.getLevel(_lvlIndex).getBgFileName     (),
                                                      _lvlHandler.getLevel(_lvlIndex).getInitialPosition());
    delete _light;
    _light = new Dev::Game::Elements::Light(_lvlHandler.getLevel(_lvlIndex).getLightRadius    (),
                                            _lvlHandler.getLevel(_lvlIndex).getNbPx           (),
                                            _lvlHandler.getLevel(_lvlIndex).getInitialPosition());

    for (Dev::Game::Elements::Boost * i : _boosts)
    {
        delete i;
    }
    _boosts.clear();
    for (Dev::Game::Utils::BoostPosition const & i : _lvlHandler.getLevel(_lvlIndex).getBoostPositions())
    {
        _boosts.push_back(new Dev::Game::Elements::Boost(_lvlHandler.getLevel(_lvlIndex).getNbPx(),
                                                         _lvlHandler.getLevel(_lvlIndex).getInitialPosition(),
                                                         i.position,
                                                         i.speed));
    }

    delete _character;
    _character = new Dev::Game::Elements::Character(_lvlHandler.getLevel(_lvlIndex).getCharacterRadius(),
                                                    _lvlHandler.getLevel(_lvlIndex).getNbPx           (),
                                                    _lvlHandler.getLevel(_lvlIndex).getInitialPosition(),
                                                    _lvlHandler.getLevel(_lvlIndex).getFinalPosition  (),
                                                    _light,
                                                    _background,
                                                    _boosts);
}

void
Game::update()
{
    /* '-----' Events '-----' */
    while (_window->pollEvent(*_event))
    {
        if (_event->type == sf::Event::Closed)
        {
            _window->close();
        }
        else if (sf::Event::KeyPressed && !_lose && !_lvlComplete && !_cinematicActive && !_win && !_howToPlayActive)
        {
            updateWhenKeyPressed();
        }
        else if (sf::Event::KeyPressed && _menuTimeOut && (_menuClock->getElapsedTime().asMilliseconds()) - _menuTime > 200.f)
        {
            updateMenuSelectedStatement();
            _menuTime = _menuClock->getElapsedTime().asMilliseconds();
        }
    }

    /* '-----' Game handler '-----' */
    if (_lose || _lvlComplete || _cinematicActive || _win || _howToPlayActive)
    {
        if (!_menuTimerStarted)
        {
            activateNightMode();
            _menuClock->restart();
            _menuTimerStarted = true;
        }
        checkMenuTimer();
        if (_menuTimeOut)
        {
            updateMenu();
        }
        if (_cinematicActive || _howToPlayActive)
        {
            updateCharacterMove();
        }
    }
    else
    {
        checkLoseTimer();
        updateCountDown();
        updateCharacterMove();
        if (_character->getFoundStatus())
        {
            updateSpeedIfBoost();
        }
    }
}

void
Game::updateMenu()
{
    if (_win)
    {
        _winMenu->updateSelectedStatement();
    }
    if (_lose)
    {
        _loseMenu->updateSelectedStatement();
    }
    else if (_lvlComplete)
    {
        _lvlCompleteMenu->updateSelectedStatement();
    }
    else if (_cinematicActive)
    {
        _startMenu->updateSelectedStatement();
    }
    else if (_howToPlayActive)
    {
        _htpMenu->updateSelectedStatement();
    }
}

void
Game::checkLoseTimer()
{
    if (_character->getFoundStatus() && !_loseTimerStarted)
    {
        _loseClock->restart();
        _loseTimerStarted = true;
    }
    if (_loseTimerStarted)
    {
        _lvlComplete = _character->getWinStatus();
        _win = _lvlComplete && _lvlIndex == 6;
        _lose = _loseClock->getElapsedTime().asSeconds() >
                _lvlHandler.getLevel(_lvlIndex).getTimeToReturn() && !_lvlComplete;

        /* '-----' Countdown '-----' */
        _oneSec   = _loseClock->getElapsedTime().asSeconds() >
                    _lvlHandler.getLevel(_lvlIndex).getTimeToReturn() - 1.f && !_lose && !_lvlComplete;
        _twoSec   = _loseClock->getElapsedTime().asSeconds() >
                    _lvlHandler.getLevel(_lvlIndex).getTimeToReturn() - 2.f && !_lose && !_lvlComplete;
        _threeSec = _loseClock->getElapsedTime().asSeconds() >
                    _lvlHandler.getLevel(_lvlIndex).getTimeToReturn() - 3.f && !_lose && !_lvlComplete;
    }
}

void
Game::updateCountDown()
{
    if (_oneSec)
    {
        _one->updateLabelShape();
    }
    else if (_twoSec)
    {
        _two->updateLabelShape();
    }
    else if (_threeSec)
    {
        _three->updateLabelShape();
        if (!_soundLaunched)
        {
            _sound->play();
            _soundLaunched = true;
        }
    }
    else
    {
        _sound->stop();
    }
}

void
Game::checkMenuTimer()
{
    _menuTimeOut = _menuTimerStarted && _menuClock->getElapsedTime().asSeconds() > 1.5f;
}

void
Game::activateNightMode()
{
    _background->activateNightMode();
    _character->activateNightMode();
    for (Dev::Game::Elements::Boost * i : _boosts)
    {
        i->activateNightMode();
    }
}

void
Game::updateWhenKeyPressed()
{
    switch (_event->key.code)
    {
        case sf::Keyboard::LControl :
            _moveInPxPerSecond += 50;
            break;
        case sf::Keyboard::LAlt :
            _moveInPxPerSecond -= 50;
            break;
        case sf::Keyboard::Right :
            _gameTimer->restart();
            _t = 0.f;
            _direction = Dev::Game::Utils::Direction::RIGHT;
            break;
        case sf::Keyboard::Left :
            _gameTimer->restart();
            _t = 0.f;
            _direction = Dev::Game::Utils::Direction::LEFT;
            break;
        case sf::Keyboard::Up :
            _gameTimer->restart();
            _t = 0.f;
            _direction = Dev::Game::Utils::Direction::UP;
            break;
        case sf::Keyboard::Down :
            _gameTimer->restart();
            _t = 0.f;
            _direction = Dev::Game::Utils::Direction::DOWN;
            break;
        case sf::Keyboard::Space :
            _gameTimer->restart();
            _t = 0.f;
            _direction = Dev::Game::Utils::Direction::NONE;
            break;
        default:
            break;
    }
}

void
Game::updateCharacterMove()
{
    Dev::Game::Utils::Direction currentDirection = _direction;
    if (_cinematicActive || _howToPlayActive)
    {
        currentDirection = _cinematic.getCurrentDirection();
    }
    switch (currentDirection)
    {
    case Dev::Game::Utils::Direction::RIGHT:
        moveShapesToTheRight();
        break;

    case Dev::Game::Utils::Direction::LEFT:
        moveShapesToTheLeft();
        break;

    case Dev::Game::Utils::Direction::UP:
        moveShapesUp();
        break;

    case Dev::Game::Utils::Direction::DOWN:
        moveShapesDown();
        break;
    
    default:
        break;
    }
}

void
Game::moveShapesToTheRight()
{
    Dev::Game::Utils::Direction assistDirection = Dev::Game::Utils::Direction::NONE;

    float normalMove = _moveInPxPerSecond * (_gameTimer->getElapsedTime().asSeconds() - _t);
    float computedMove = normalMove;
    _t = _gameTimer->getElapsedTime().asSeconds();

    for (Dev::Game::Utils::Obstacle const & i : _lvlHandler.getLevel(_lvlIndex).getObstacles())
    {
        float moveToCheck = normalMove;
        if (_cinematicActive)
        {
            moveToCheck += 25.f;
        }
        if (_character->checkObstacleRight(i, moveToCheck))
        {
            if (_cinematicActive)
            {
                _cinematic.computeAnotherDirection();
                computedMove = 0.f;
            }
            else
            {
                computedMove = _character->computeRightMoveInPx(i);
                assistDirection = _character->computeNeededVerticalAssist(i);
            }
            break;
        }
    }
    if (assistDirection == Dev::Game::Utils::Direction::UP)
    {
        _character->moveUp(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::DOWN)
    {
        _character->moveDown(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::NONE)
    {
        _character->moveRight(computedMove);
    }
}

void
Game::moveShapesToTheLeft()
{
    Dev::Game::Utils::Direction assistDirection = Dev::Game::Utils::Direction::NONE;

    float normalMove = _moveInPxPerSecond * (_gameTimer->getElapsedTime().asSeconds() - _t);
    float computedMove = normalMove;
    _t = _gameTimer->getElapsedTime().asSeconds();

    for (Dev::Game::Utils::Obstacle const & i : _lvlHandler.getLevel(_lvlIndex).getObstacles())
    {
        float moveToCheck = normalMove;
        if (_cinematicActive)
        {
            moveToCheck += 25.f;
        }
        if (_character->checkObstacleLeft(i, moveToCheck))
        {
            if (_cinematicActive)
            {
                _cinematic.computeAnotherDirection();
                computedMove = 0.f;
            }
            else
            {
                computedMove = _character->computeLeftMoveInPx(i);
                assistDirection = _character->computeNeededVerticalAssist(i);
            }

            break;
        }
    }
    if (assistDirection == Dev::Game::Utils::Direction::UP)
    {
        _character->moveUp(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::DOWN)
    {
        _character->moveDown(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::NONE)
    {
        _character->moveLeft(computedMove);
    }
}

void
Game::moveShapesUp()
{
    Dev::Game::Utils::Direction assistDirection = Dev::Game::Utils::Direction::NONE;

    float normalMove = _moveInPxPerSecond * (_gameTimer->getElapsedTime().asSeconds() - _t);
    float computedMove = normalMove;
    _t = _gameTimer->getElapsedTime().asSeconds();

    for (Dev::Game::Utils::Obstacle const & i : _lvlHandler.getLevel(_lvlIndex).getObstacles())
    {
        float moveToCheck = normalMove;
        if (_cinematicActive)
        {
            moveToCheck += 25.f;
        }
        if (_character->checkObstacleUp(i, moveToCheck))
        {
            if (_cinematicActive)
            {
                _cinematic.computeAnotherDirection();
                computedMove = 0.f;
            }
            else
            {
                computedMove = _character->computeUpMoveInPx(i);
                assistDirection = _character->computeNeededLateralAssist(i);
            }

            break;
        }
    }
    if (assistDirection == Dev::Game::Utils::Direction::RIGHT)
    {
        _character->moveRight(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::LEFT)
    {
        _character->moveLeft(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::NONE)
    {
        _character->moveUp(computedMove);
    }
}

void
Game::moveShapesDown()
{
    Dev::Game::Utils::Direction assistDirection = Dev::Game::Utils::Direction::NONE;

    float normalMove = _moveInPxPerSecond * (_gameTimer->getElapsedTime().asSeconds() - _t);
    float computedMove = normalMove;
    _t = _gameTimer->getElapsedTime().asSeconds();

    for (Dev::Game::Utils::Obstacle const & i : _lvlHandler.getLevel(_lvlIndex).getObstacles())
    {
        float moveToCheck = normalMove;
        if (_cinematicActive)
        {
            moveToCheck += 25.f;
        }
        if (_character->checkObstacleDown(i, moveToCheck))
        {
            if (_cinematicActive)
            {
                _cinematic.computeAnotherDirection();
                computedMove = 0.f;
            }
            else
            {
                computedMove = _character->computeDownMoveInPx(i);
                assistDirection = _character->computeNeededLateralAssist(i);
            }
            break;
        }
    }
    if (assistDirection == Dev::Game::Utils::Direction::RIGHT)
    {
        _character->moveRight(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::LEFT)
    {
        _character->moveLeft(normalMove);
    }
    else if (assistDirection == Dev::Game::Utils::Direction::NONE)
    {
        _character->moveDown(computedMove);
    }
}

void
Game::updateMenuSelectedStatement()
{
    if (_win)
    {
        if (_event->key.code == sf::Keyboard::Up)
        {
            _winMenu->upMove();
        }
        else if (_event->key.code == sf::Keyboard::Down)
        {
            _winMenu->downMove();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _winMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::QUIT)
        {
            _window->close();
        }
    }
    else if (_lose)
    {
        if (_event->key.code == sf::Keyboard::Up)
        {
            _loseMenu->upMove();
        }
        else if (_event->key.code == sf::Keyboard::Down)
        {
            _loseMenu->downMove();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _loseMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::TRYAGAIN)
        {
            initializeLevel();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _loseMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::QUIT)
        {
            _window->close();
        }
    }
    else if (_lvlComplete)
    {
        if (_event->key.code == sf::Keyboard::Up)
        {
            _lvlCompleteMenu->upMove();
        }
        else if (_event->key.code == sf::Keyboard::Down)
        {
            _lvlCompleteMenu->downMove();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _lvlCompleteMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::NEXTLEVEL)
        {
            ++_lvlIndex;
            initializeLevel();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _lvlCompleteMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::QUIT)
        {
            _window->close();
        }
    }
    else if (_cinematicActive)
    {
        if (_event->key.code == sf::Keyboard::Up)
        {
            _startMenu->upMove();
        }
        else if (_event->key.code == sf::Keyboard::Down)
        {
            _startMenu->downMove();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _startMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::START)
        {
            ++_lvlIndex;
            initializeLevel();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _startMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::HOWTOPLAY)
        {
            _howToPlayActive = true;
            _cinematicActive = false;
            _htpMenu->restartClock();
        }
        else if (_event->key.code == sf::Keyboard::Enter &&
                 _startMenu->getSelectedStatement() == Dev::Game::Statements::MenuStatement::QUIT)
        {
            _window->close();
        }
    }
    else if (_howToPlayActive)
    {
        if (_event->key.code == sf::Keyboard::Up)
        {
            _htpMenu->upMove();
        }
        else if (_event->key.code == sf::Keyboard::Down)
        {
            _htpMenu->downMove();
        }
        else if (_event->key.code == sf::Keyboard::Enter)
        {
            _howToPlayActive = false;
            _cinematicActive = true;
            _startMenu->restartClock();
        }
    }
}

void
Game::updateSpeedIfBoost()
{
    for (auto const & i : _lvlHandler.getLevel(_lvlIndex).getBoostPositions())
    {
        Dev::Game::Utils::Coordinates iSpeedCell;
        iSpeedCell.x = 100 * (i.position.x - 0.5f);
        iSpeedCell.y = 100 * (i.position.y - 0.5f);
        if (_character->checkIfInCell(iSpeedCell) && _moveInPxPerSecond != i.speed)
        {
            _moveInPxPerSecond = i.speed;
        }
    }
}

void
Game::render()
{
    _window->clear();
    if (_howToPlayActive)
    {
        _window->draw(_howToPlay.getPicture());
        if (_menuTimeOut)
        {
            for (Dev::Game::Statements::BounceStatement * i : _htpMenu->getBounceStatements())
            {
                _window->draw(i->getLabel());
            }
        } 
    }
    else
    {
        _window->draw(_background->getBackground());
        if (_character->getFoundStatus())
        {
            for (Dev::Game::Elements::Boost * i : _boosts)
            {
                _window->draw(i->getBoost());
            }
        }
        _window->draw(_light->getBlindArea());
        _window->draw(_light->getVisibleArea());
        _window->draw(_character->getShadow());
        _window->draw(_character->getBubble());
        if (_oneSec)
        {
            _window->draw(_one->getLabel());
        }
        else if (_twoSec)
        {
            _window->draw(_two->getLabel());
        }
        else if (_threeSec)
        {
            _window->draw(_three->getLabel());
        }
        if (_win)
        {
            _window->draw(_winMenu->getStaticStatement()->getLabel());
            if (_menuTimeOut)
            {
                for (Dev::Game::Statements::BounceStatement * i : _winMenu->getBounceStatements())
                {
                    _window->draw(i->getLabel());
                }
            }
        }
        else if (_lose)
        {
            _window->draw(_loseMenu->getStaticStatement()->getLabel());
            if (_menuTimeOut)
            {
                for (Dev::Game::Statements::BounceStatement * i : _loseMenu->getBounceStatements())
                {
                    _window->draw(i->getLabel());
                }
            }
        }
        else if (_lvlComplete)
        {
            _window->draw(_lvlCompleteMenu->getStaticStatement()->getLabel());
            if (_menuTimeOut)
            {
                for (Dev::Game::Statements::BounceStatement * i : _lvlCompleteMenu->getBounceStatements())
                {
                    _window->draw(i->getLabel());
                }
            }
        }
        else if (_cinematicActive)
        {
            _window->draw(_startMenu->getStaticStatement()->getLabel());
            if (_menuTimeOut)
            {
                for (Dev::Game::Statements::BounceStatement * i : _startMenu->getBounceStatements())
                {
                    _window->draw(i->getLabel());
                }
            }
        }
    }
    _window->display();
}