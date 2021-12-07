#include "dev_game_utils.h"

namespace Dev {
namespace Game {
namespace Utils {

Coordinates::Coordinates()
{}

Coordinates::Coordinates(int initPosX, int initPosY) :
x(initPosX),
y(initPosY)
{}

BoostPosition::BoostPosition()
{}

BoostPosition::BoostPosition(Dev::Game::Utils::Coordinates const & initPosition, float initSpeed) :
position(initPosition),
speed(initSpeed)
{}


Obstacle::Obstacle()
{}

Obstacle::Obstacle(int posX, int posY, int sizeX, int sizeY, int rotationAngle, int nbPx) :
_posX         (posX),
_posY         (posY),
_sizeX        (sizeX),
_sizeY        (sizeY),
_rotationAngle(rotationAngle),
_nbPx(nbPx)
{
    adaptAttributesToRotationAngle();
}

void
Obstacle::adaptAttributesToRotationAngle()
{
    switch (_rotationAngle)
    {
    case 90:
    case -90:
        computeAttributesWithPerpandicularRotation();
        break;

    case 180:
    case -180:
        computeAttributesWithParallelRotation();
        break;
    
    default:
        break;
    }
}

void
Obstacle::computeAttributesWithPerpandicularRotation()
{
    int const posX  = _nbPx - (_posY + _sizeY);
    int const posY  = _posX;
    int const sizeX = _sizeY;
    int const sizeY = _sizeX;

    _posX  = posX;
    _posY  = posY;
    _sizeX = sizeX;
    _sizeY = sizeY;
}

void
Obstacle::computeAttributesWithParallelRotation()
{
    int const posX  = _nbPx - (_sizeX + _posX);
    int const posY  = _nbPx - (_sizeY + _posY);
    int const sizeX = _sizeX;
    int const sizeY = _sizeY;

    _posX  = posX;
    _posY  = posY;
    _sizeX = sizeX;
    _sizeY = sizeY;
}

int
Obstacle::getPosX() const
{
    return _posX;
}

int
Obstacle::getPosY() const
{
    return _posY;
}

int
Obstacle::getSizeX() const
{
    return _sizeX;
}

int
Obstacle::getSizeY() const
{
    return _sizeY;
}

void
Obstacle::setPosX(int posX)
{
    _posX = posX;
}

void
Obstacle::setPosY(int posY)
{
    _posY = posY;
}

void
Obstacle::setSizeX(int sizeX)
{
    _sizeX = sizeX;
}

void
Obstacle::setSizeY(int sizeY)
{
    _sizeY = sizeY;
}

Level::Level(std::vector<Dev::Game::Utils::Obstacle>      const & obstacles,
             Dev::Game::Utils::Coordinates                const & initialPosition,
             Dev::Game::Utils::Coordinates                const & finalPosition,
             std::string                                  const & bgFileName,
             int                                                  nbPx,
             int                                                  lightRadius,
             int                                                  characterRadius,
             float                                                timeToReturn,
             std::vector<Dev::Game::Utils::BoostPosition> const & boostPositions) :
_obstacles      (obstacles),
_initialPosition(initialPosition),
_finalPosition  (finalPosition),
_bgFileName     (bgFileName),
_lightRadius    (lightRadius),
_characterRadius(characterRadius),
_timeToReturn   (timeToReturn),
_nbPx           (nbPx),
_boostPositions (boostPositions)
{
    /* '-----' Limits '-----' */
    _obstacles.push_back(Dev::Game::Utils::Obstacle(_nbPx,     0,   100, _nbPx));
    _obstacles.push_back(Dev::Game::Utils::Obstacle( -100,     0,   100, _nbPx));
    _obstacles.push_back(Dev::Game::Utils::Obstacle(    0,  -100, _nbPx,   100));
    _obstacles.push_back(Dev::Game::Utils::Obstacle(    0, _nbPx, _nbPx,   100));
}

std::vector<Dev::Game::Utils::Obstacle> const & 
Level::getObstacles() const
{
    return _obstacles;
}

Dev::Game::Utils::Coordinates const & 
Level::getInitialPosition() const
{
    return _initialPosition;
}

Dev::Game::Utils::Coordinates const & 
Level::getFinalPosition() const
{
    return _finalPosition;
}

std::string const &
Level::getBgFileName() const
{
    return _bgFileName;
}

int
Level::getNbPx() const
{
    return _nbPx;
}

int
Level::getLightRadius() const
{
    return _lightRadius;
}

int
Level::getCharacterRadius() const
{
    return _characterRadius;
}

float
Level::getTimeToReturn() const
{
    return _timeToReturn;
}

std::vector<Dev::Game::Utils::BoostPosition> const &
Level::getBoostPositions() const
{
    return _boostPositions;
}


} /*Utils*/
} /*Game*/
} /*Dev*/