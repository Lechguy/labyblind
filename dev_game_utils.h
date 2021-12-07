#ifndef __DEV_GAMES_UTILS_H__
#define __DEV_GAMES_UTILS_H__

#include <map>
#include <vector>
#include <string>

namespace Dev {
namespace Game {
namespace Utils {

enum class Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NONE
};


class Coordinates
{
    public:
    Coordinates();
    Coordinates(int initPosX, int initPosY);
    int x;
    int y;
};


class BoostPosition
{
    public:
    BoostPosition();
    BoostPosition(Dev::Game::Utils::Coordinates const & initPos, float initSpeed);
    Dev::Game::Utils::Coordinates position;
    float speed;
};


class Obstacle
{
    public:
    Obstacle();
    Obstacle(int posX, int posY, int sizeX, int sizeY, int rotationAngle = 0, int _nbPx = 1000);

    int  getPosX () const;
    int  getPosY () const;
    int  getSizeX() const;
    int  getSizeY() const;

    void setPosX (int posX );
    void setPosY (int posY );
    void setSizeX(int sizeX);
    void setSizeY(int sizeY);

    private:
    void adaptAttributesToRotationAngle();
        void computeAttributesWithPerpandicularRotation();
        void computeAttributesWithParallelRotation();

    int _posX;
    int _posY;
    int _sizeX;
    int _sizeY;
    int _rotationAngle;
    int _nbPx;
};


class Level
{
    public:
    Level(std::vector<Dev::Game::Utils::Obstacle>      const & obstacles,
          Dev::Game::Utils::Coordinates                const & initialPosition,
          Dev::Game::Utils::Coordinates                const & finalPosition,
          std::string                                  const & bgFileName,
          int                                                  nbPx,
          int                                                  lightRadius,
          int                                                  characterRadius,
          float                                                timeToReturn,
          std::vector<Dev::Game::Utils::BoostPosition> const & boostPositions);

    std::vector<Dev::Game::Utils::Obstacle>      const & getObstacles      () const;
    Dev::Game::Utils::Coordinates                const & getInitialPosition() const;
    Dev::Game::Utils::Coordinates                const & getFinalPosition  () const;
    std::string                                  const & getBgFileName     () const;
    int                                                  getNbPx           () const;
    int                                                  getLightRadius    () const;
    int                                                  getCharacterRadius() const;
    float                                                getTimeToReturn   () const;
    std::vector<Dev::Game::Utils::BoostPosition> const & getBoostPositions () const;

    private:
    std::vector<Dev::Game::Utils::Obstacle>      _obstacles;
    Dev::Game::Utils::Coordinates                _initialPosition;
    Dev::Game::Utils::Coordinates                _finalPosition;
    std::string                                  _bgFileName;
    int                                          _nbPx;
    int                                          _lightRadius;
    int                                          _characterRadius;
    float                                        _timeToReturn;
    std::vector<Dev::Game::Utils::BoostPosition> _boostPositions;
};


} /*Utils*/
} /*Game*/
} /*Dev*/

#endif /*__DEV_GAMES_UTILS_H__*/