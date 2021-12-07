#include "dev_game_elements.h"
#include "dev_math.h"
#include "path.h"
#include <cmath>
#include <iostream>

namespace Dev {
namespace Game {
namespace Elements {

/* '---------------------------------------------------------------------' */

IElement::IElement()
{}


IElementStatic::IElementStatic()
{}

/* '---------------------------------------------------------------------' */

Background::Background(int nbPx,
                       std::string const & bgFileName,
                       Dev::Game::Utils::Coordinates const & initialPositionInCell) :
_bgFileName(bgFileName),
_minPos(-(nbPx - 1000)),
_maxPos(0.f)
{
    initTextures();
    initSprites();

    /* '-----' Position '-----' */
    float const initPosX = -100 * (initialPositionInCell.x - (5.f + 0.5f));
    float const initPosY = -100 * (initialPositionInCell.y - (5.f + 0.5f));
    _spriteBckgnd.setPosition(Dev::Math::BoundFloatValue(initPosX, _minPos, _maxPos),
                              Dev::Math::BoundFloatValue(initPosY, _minPos, _maxPos));
}

void
Background::initTextures()
{
    _textureBckgnd.loadFromFile(_bgFileName);
    _textureBckgnd.setSmooth(true);
}

void
Background::initSprites()
{
    _spriteBckgnd.setTexture(_textureBckgnd);
}

void
Background::activateNightMode()
{
    _spriteBckgnd.setColor(sf::Color(_spriteBckgnd.getColor().r,
                                     _spriteBckgnd.getColor().g,
                                     _spriteBckgnd.getColor().b, 50));
}

void
Background::moveRight(float moveInPx)
{
    _spriteBckgnd.move(-moveInPx, 0.f);
}

void
Background::moveLeft(float moveInPx)
{
    _spriteBckgnd.move(moveInPx, 0.f);
}

void
Background::moveUp(float moveInPx)
{
    _spriteBckgnd.move(0.f, moveInPx);
}

void
Background::moveDown(float moveInPx)
{
    _spriteBckgnd.move(0.f, -moveInPx);
}

bool
Background::isRightMovePossible(float moveInPx) const
{
    return _spriteBckgnd.getPosition().x - moveInPx > _minPos;
}

bool
Background::isLeftMovePossible(float moveInPx) const
{
    return _spriteBckgnd.getPosition().x + moveInPx < _maxPos;
}

bool
Background::isUpMovePossible(float moveInPx) const
{
    return _spriteBckgnd.getPosition().y + moveInPx < _maxPos;
}

bool
Background::isDownMovePossible(float moveInPx) const
{
    return _spriteBckgnd.getPosition().y - moveInPx > _minPos;
}

sf::Sprite const &
Background::getBackground() const
{
    return _spriteBckgnd;
}


/* '---------------------------------------------------------------------' */


Boost::Boost(int nbPx,
             Dev::Game::Utils::Coordinates const & initPos,
             Dev::Game::Utils::Coordinates const & initBoostPos,
             float initSpeed)
{
    initTextures();
    initSprites();

    float const minPos = -(nbPx - 1000);
    float const maxPos = 0.f;

    float const initPosX = -100 * (initPos.x - (5.f + 0.5f));
    float const initPosY = -100 * (initPos.y - (5.f + 0.5f));

    _spriteBoost.setPosition(Dev::Math::BoundFloatValue(initPosX, minPos, maxPos) + 100 * (initBoostPos.x - 1),
                             Dev::Math::BoundFloatValue(initPosY, minPos, maxPos) + 100 * (initBoostPos.y - 1));

    _spriteBoost.setColor(sf::Color(255.f, (1 - initSpeed/3000.f) * 255.f, 0.f));
}

void
Boost::initTextures()
{
    _textureBoost.loadFromFile(Path::Pictures::Boost + "boost.png");
    _textureBoost.setSmooth(true);
}

void
Boost::initSprites()
{
    _spriteBoost.setTexture(_textureBoost);
}

void
Boost::activateNightMode()
{
    _spriteBoost.setColor(sf::Color(_spriteBoost.getColor().r,
                                    _spriteBoost.getColor().g,
                                    _spriteBoost.getColor().b, 50));
}

void
Boost::moveRight(float moveInPx)
{
    _spriteBoost.move(-moveInPx, 0.f);
}

void
Boost::moveLeft(float moveInPx)
{
    _spriteBoost.move(moveInPx, 0.f);
}

void
Boost::moveUp(float moveInPx)
{
    _spriteBoost.move(0.f, moveInPx);
}

void
Boost::moveDown(float moveInPx)
{
    _spriteBoost.move(0.f, -moveInPx);
}

sf::Sprite const &
Boost::getBoost() const
{
    return _spriteBoost;
}


/* '---------------------------------------------------------------------' */


IElementDynamic::IElementDynamic()
{}

IElementDynamic::IElementDynamic(int radius, int nbPx, Dev::Game::Utils::Coordinates const & initialPositionInCell) :
_radius(radius)
{
    _initialPositionInPx.x = 100 * (initialPositionInCell.x - 0.5f);
    _initialPositionInPx.y = 100 * (initialPositionInCell.y - 0.5f);

    float const minPos = -(nbPx - 1000);
    float const maxPos = 0.f;
    float const initPosX = -100 * (initialPositionInCell.x - (5.f + 0.5f));
    float const initPosY = -100 * (initialPositionInCell.y - (5.f + 0.5f));
    _initialPositionInPxInWindow.x = _initialPositionInPx.x + Dev::Math::BoundFloatValue(initPosX, minPos, maxPos);
    _initialPositionInPxInWindow.y = _initialPositionInPx.y + Dev::Math::BoundFloatValue(initPosY, minPos, maxPos);
}

/* '---------------------------------------------------------------------' */

Light::Light()
{}

Light::Light(int radius, int nbPx, Dev::Game::Utils::Coordinates const & initialPositionInCell) :
IElementDynamic(radius, nbPx, initialPositionInCell)
{
    initTextures();
    initShapes();
}

void
Light::initTextures()
{
    _textureVisibleArea.loadFromFile(Path::Pictures::Elements + "light.png");
    _textureVisibleArea.setSmooth(true);
}

void
Light::initShapes()
{
    _symbBlindArea.setRadius(_radius);
    _symbBlindArea.setFillColor(sf::Color::Transparent);
    _symbBlindArea.setOutlineColor(sf::Color(0.f, 0.f, 0.f, 255.f));
    _symbBlindArea.setOutlineThickness(2000.f);
    _symbBlindArea.setPosition(_initialPositionInPxInWindow.x, _initialPositionInPxInWindow.y);
    _symbBlindArea.move(-_radius, -_radius);

    _symbVisibleArea.setRadius(_radius);
    _symbVisibleArea.setTexture(&_textureVisibleArea);
    _symbVisibleArea.setPosition(_initialPositionInPxInWindow.x, _initialPositionInPxInWindow.y);
    _symbVisibleArea.move(-_radius, -_radius);
}

void
Light::moveRight(float moveInPx)
{
    _symbBlindArea.move(moveInPx, 0.f);
    _symbVisibleArea.move(moveInPx, 0.f);
}

void
Light::moveLeft(float moveInPx)
{
    _symbBlindArea.move(-moveInPx, 0.f);
    _symbVisibleArea.move(-moveInPx, 0.f);
}

void
Light::moveUp(float moveInPx)
{
    _symbBlindArea.move(0.f, -moveInPx);
    _symbVisibleArea.move(0.f, -moveInPx);
}

void
Light::moveDown(float moveInPx)
{
    _symbBlindArea.move(0.f, moveInPx);
    _symbVisibleArea.move(0.f, moveInPx);
}

void
Light::activateNightMode()
{}

sf::CircleShape const &
Light::getBlindArea() const
{
    return _symbBlindArea;
}

sf::CircleShape const &
Light::getVisibleArea() const
{
    return _symbVisibleArea;
}

/* '---------------------------------------------------------------------' */

Character::Character()
{}

Character::Character(int radius, int nbPx,
                     Dev::Game::Utils::Coordinates            const & initialPositionInCell,
                     Dev::Game::Utils::Coordinates            const & finalPositionInCell,
                     Dev::Game::Elements::Light                     * light,
                     Dev::Game::Elements::Background                * background,
                     std::vector<Dev::Game::Elements::Boost*> const & boosts) :
IElementDynamic(radius, nbPx, initialPositionInCell),
_nbPx(nbPx),
_light(light),
_boosts(boosts),
_background(background),
_found(false),
_win(false),
_nightMode(false)
{
    _finalPositionInPx.x = 100 * (finalPositionInCell.x - 0.5f);
    _finalPositionInPx.y = 100 * (finalPositionInCell.y - 0.5f);

    initTextures();
    initShapes();
    updateColor();
}

void
Character::initTextures()
{
    _textureBubble.loadFromFile(Path::Pictures::Elements + "bubble.png");
    _textureBubble.setSmooth(true);
    _textureShadow.loadFromFile(Path::Pictures::Elements + "shadow.png");
    _textureShadow.setSmooth(true);
}

void
Character::initShapes()
{
    _symbBubble.setRadius(_radius);
    _symbBubble.setTexture(&_textureBubble);
    _symbBubble.setPosition(_initialPositionInPxInWindow.x, _initialPositionInPxInWindow.y);
    _symbBubble.move(-_radius, -_radius);

    _symbShadow.setRadius(2 * _radius);
    _symbShadow.setTexture(&_textureShadow);
    _symbShadow.setPosition(_initialPositionInPxInWindow.x, _initialPositionInPxInWindow.y);
    _symbShadow.move(-2 * _radius, -2 * _radius);
}

bool
Character::checkObstacleRight(Dev::Game::Utils::Obstacle const & obstacle, float moveInPx)
{
    float const xRightAfterMove   = _symbBubble.getPosition().x - _background->getBackground().getPosition().x
                                    + 2*_symbBubble.getRadius() + moveInPx;
    bool  const isInObstacleXAxis = xRightAfterMove > obstacle.getPosX() &&
                                    xRightAfterMove < obstacle.getPosX() + obstacle.getSizeX();

    bool const isInObstacleYAxis = _symbBubble.getPosition().y - _background->getBackground().getPosition().y
                                   + 2*_symbBubble.getRadius() > obstacle.getPosY() &&
                                   _symbBubble.getPosition().y - _background->getBackground().getPosition().y
                                   < obstacle.getPosY() + obstacle.getSizeY();

    return isInObstacleXAxis && isInObstacleYAxis;
}

bool
Character::checkObstacleLeft(Dev::Game::Utils::Obstacle const & obstacle, float moveInPx)
{
    float const xLeftAfterMove    = _symbBubble.getPosition().x - _background->getBackground().getPosition().x
                                    - moveInPx;
    bool  const isInObstacleXAxis = xLeftAfterMove > obstacle.getPosX() && 
                                    xLeftAfterMove < obstacle.getPosX() + obstacle.getSizeX();

    bool const isInObstacleYAxis = _symbBubble.getPosition().y - _background->getBackground().getPosition().y
                                   + 2*_symbBubble.getRadius() > obstacle.getPosY() &&
                                   _symbBubble.getPosition().y - _background->getBackground().getPosition().y
                                   < obstacle.getPosY() + obstacle.getSizeY();

    return isInObstacleXAxis && isInObstacleYAxis;
}

bool
Character::checkObstacleUp(Dev::Game::Utils::Obstacle const & obstacle, float moveInPx)
{
    float const yUpAfterMove      = _symbBubble.getPosition().y - _background->getBackground().getPosition().y
                                    - moveInPx;
    bool  const isInObstacleYAxis = yUpAfterMove > obstacle.getPosY() && 
                                    yUpAfterMove < obstacle.getPosY() + obstacle.getSizeY();

    bool const isInObstacleXAxis = _symbBubble.getPosition().x - _background->getBackground().getPosition().x
                                   + 2*_symbBubble.getRadius() > obstacle.getPosX() &&
                                   _symbBubble.getPosition().x - _background->getBackground().getPosition().x
                                   < obstacle.getPosX() + obstacle.getSizeX();

    return isInObstacleXAxis && isInObstacleYAxis;
}

bool
Character::checkObstacleDown(Dev::Game::Utils::Obstacle const & obstacle, float moveInPx)
{
    float const yDownAfterMove    = _symbBubble.getPosition().y - _background->getBackground().getPosition().y
                                    + 2*_symbBubble.getRadius() + moveInPx;
    bool  const isInObstacleYAxis = yDownAfterMove > obstacle.getPosY() && 
                                    yDownAfterMove < obstacle.getPosY() + obstacle.getSizeY();

    bool const isInObstacleXAxis = _symbBubble.getPosition().x - _background->getBackground().getPosition().x
                                   + 2*_symbBubble.getRadius() > obstacle.getPosX() &&
                                   _symbBubble.getPosition().x - _background->getBackground().getPosition().x
                                   < obstacle.getPosX() + obstacle.getSizeX();

    return isInObstacleXAxis && isInObstacleYAxis;
}

float
Character::computeRightMoveInPx(Dev::Game::Utils::Obstacle const & obstacle)
{
    return obstacle.getPosX() - 2 * _symbBubble.getRadius()
           - (_symbBubble.getPosition().x - _background->getBackground().getPosition().x);
}

float
Character::computeLeftMoveInPx(Dev::Game::Utils::Obstacle const & obstacle)
{
    return -(obstacle.getPosX() + obstacle.getSizeX()
             - (_symbBubble.getPosition().x - _background->getBackground().getPosition().x));
}

float
Character::computeUpMoveInPx(Dev::Game::Utils::Obstacle const & obstacle)
{
    return -(obstacle.getPosY() + obstacle.getSizeY()
             - (_symbBubble.getPosition().y - _background->getBackground().getPosition().y));
}

float
Character::computeDownMoveInPx(Dev::Game::Utils::Obstacle const & obstacle)
{
    return obstacle.getPosY() - 2 * _symbBubble.getRadius()
           - (_symbBubble.getPosition().y - _background->getBackground().getPosition().y);
}

void
Character::moveRight(float moveInPx)
{
    if (_symbBubble.getPosition().x + 2 * _radius + moveInPx > 800.f && _background->isRightMovePossible(moveInPx))
    {
        _background->moveRight(moveInPx);
        for (Dev::Game::Elements::Boost * i : _boosts)
        {
            i->moveRight(moveInPx);
        }
    }
    else
    {
        _symbBubble.move(moveInPx, 0.f);
        _symbShadow.move(moveInPx, 0.f);
        _light->moveRight(moveInPx);        
    }

    if (!_found)
    {
        checkIfFound();
        updateColor();
    }
    else
    {
        checkIfWin();
    }
}

void
Character::moveLeft(float moveInPx)
{
    if (_symbBubble.getPosition().x - moveInPx < 200.f && _background->isLeftMovePossible(moveInPx))
    {
        _background->moveLeft(moveInPx);
        for (Dev::Game::Elements::Boost * i : _boosts)
        {
            i->moveLeft(moveInPx);
        }
    }
    else
    {
        _symbBubble.move(-moveInPx, 0.f);
        _symbShadow.move(-moveInPx, 0.f);
        _light->moveLeft(moveInPx);        
    }
 
    if (!_found)
    {
        checkIfFound();
        updateColor();
    }
    else
    {
        checkIfWin();
    }
}

void
Character::moveUp(float moveInPx)
{
    if (_symbBubble.getPosition().y - moveInPx < 200.f && _background->isUpMovePossible(moveInPx))
    {
        _background->moveUp(moveInPx);
        for (Dev::Game::Elements::Boost * i : _boosts)
        {
            i->moveUp(moveInPx);
        }
    }
    else
    {
        _symbBubble.move(0.f, -moveInPx);
        _symbShadow.move(0.f, -moveInPx);
        _light->moveUp(moveInPx);    
    }

    if (!_found)
    {
        checkIfFound();
        updateColor();
    }
    else
    {
        checkIfWin();
    }
}

void
Character::moveDown(float moveInPx)
{
    if (_symbBubble.getPosition().y + 2 * _radius + moveInPx > 800.f && _background->isDownMovePossible(moveInPx))
    {
        _background->moveDown(moveInPx);
        for (Dev::Game::Elements::Boost * i : _boosts)
        {
            i->moveDown(moveInPx);
        }
    }
    else
    {
        _symbBubble.move(0.f, moveInPx);
        _symbShadow.move(0.f, moveInPx);
        _light->moveDown(moveInPx);    
    }

    if (!_found)
    {
        checkIfFound();
        updateColor();
    }
    else
    {
        checkIfWin();
    }
}

void
Character::activateNightMode()
{
    _nightMode = true;
    updateColor();
}

bool
Character::checkIfInCell(Dev::Game::Utils::Coordinates const & cell)
{
    return _symbBubble.getPosition().x - _background->getBackground().getPosition().x               >= cell.x - 50 &&
           _symbBubble.getPosition().x - _background->getBackground().getPosition().x + 2 * _radius <= cell.x + 50 &&
           _symbBubble.getPosition().y - _background->getBackground().getPosition().y               >= cell.y - 50 &&
           _symbBubble.getPosition().y - _background->getBackground().getPosition().y + 2 * _radius <= cell.y + 50;
}

void
Character::checkIfFound()
{
    _found = checkIfInCell(_finalPositionInPx);
}

void
Character::checkIfWin()
{
    _win = checkIfInCell(_initialPositionInPx);
}

bool
Character::getFoundStatus() const
{
    return _found;
}

bool
Character::getWinStatus() const
{
    return _win;
}

void
Character::updateColor()
{
    float gain = 1.f;
    if (_nightMode)
    {
        gain = 0.2f;
    }
    if (_found)
    {
        _symbBubble.setFillColor(sf::Color(0.f * gain, 255.f * gain, 0.f * gain, 255.f));
    }
    else
    {
        float const yMaxDistFromEnd = std::max<float>(_finalPositionInPx.y, _nbPx - _finalPositionInPx.y);
        float const xMaxDistFromEnd = std::max<float>(_finalPositionInPx.x, _nbPx - _finalPositionInPx.x);
        float const maxDistFromEnd  = std::sqrt(std::pow(xMaxDistFromEnd, 2) + std::pow(yMaxDistFromEnd, 2));

        float const xCurrentDistFromEnd = std::abs(_finalPositionInPx.x
                                                   - (_symbBubble.getPosition().x
                                                      - _background->getBackground().getPosition().x));
        float const yCurrentDistFromEnd = std::abs(_finalPositionInPx.y
                                                   - (_symbBubble.getPosition().y
                                                      - _background->getBackground().getPosition().y));
        float const currentDistFromEnd  = std::sqrt(std::pow(xCurrentDistFromEnd, 2) + std::pow(yCurrentDistFromEnd, 2));

        float const greenColor = currentDistFromEnd / maxDistFromEnd * 255.f;
        _symbBubble.setFillColor(sf::Color(255.f * gain, greenColor * gain, 0.f * gain, 255.f));        
    }
}

Dev::Game::Utils::Direction
Character::computeNeededVerticalAssist(Dev::Game::Utils::Obstacle const & obstacle)
{
    Dev::Game::Utils::Direction assistDirection = Dev::Game::Utils::Direction::NONE;

    if (_symbBubble.getPosition().y + 2 * _radius - _background->getBackground().getPosition().y > obstacle.getPosY() + obstacle.getSizeY())
    {
        assistDirection = Dev::Game::Utils::Direction::DOWN;
    }
    else if (_symbBubble.getPosition().y - _background->getBackground().getPosition().y < obstacle.getPosY())
    {
        assistDirection = Dev::Game::Utils::Direction::UP;
    }

    return assistDirection;
}

Dev::Game::Utils::Direction
Character::computeNeededLateralAssist(Dev::Game::Utils::Obstacle const & obstacle)
{
    Dev::Game::Utils::Direction assistDirection = Dev::Game::Utils::Direction::NONE;

    if (_symbBubble.getPosition().x + 2 * _radius - _background->getBackground().getPosition().x > obstacle.getPosX() + obstacle.getSizeX())
    {
        assistDirection = Dev::Game::Utils::Direction::RIGHT;
    }
    else if (_symbBubble.getPosition().x - _background->getBackground().getPosition().x < obstacle.getPosX())
    {
        assistDirection = Dev::Game::Utils::Direction::LEFT;
    }

    return assistDirection;
}

sf::CircleShape const &
Character::getBubble() const
{
    return _symbBubble;
}

sf::CircleShape const & 
Character::getShadow() const
{
    return _symbShadow;
}

/* '---------------------------------------------------------------------' */

HowToPlay::HowToPlay()
{
    initTextures();
    initSprites();
}

void
HowToPlay::activateNightMode()
{}

sf::Sprite const &
HowToPlay::getPicture() const
{
    return _htpSprite;
}

void
HowToPlay::initTextures()
{
    _htpTexture.loadFromFile(Path::Pictures::HowToPlay + "howtoplay.jpg");
}

void
HowToPlay::initSprites()
{
    _htpSprite.setTexture(_htpTexture);
}

/* '---------------------------------------------------------------------' */

} /*Elements*/
} /*Game*/
} /*Dev*/