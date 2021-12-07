#ifndef __DEV_GAMES_ELEMENTS_H__
#define __DEV_GAMES_ELEMENTS_H__

#include <SFML/Graphics.hpp>
#include "dev_game_utils.h"

namespace Dev {
namespace Game {
namespace Elements {

class IElement {
    public:
    IElement();
    virtual void initTextures() = 0;
    virtual void activateNightMode() = 0;
};

class IElementStatic : public IElement {
    public:
    IElementStatic();
    virtual void initSprites() = 0;
};

class Background : public IElementStatic {
    public:
    Background(int nbPx,
               std::string const & bgFileName,
               Dev::Game::Utils::Coordinates const & initialPosition);
    virtual void activateNightMode() final;
    void moveRight(float moveInPx);
    void moveLeft (float moveInPx);
    void moveUp   (float moveInPx);
    void moveDown (float moveInPx);

    bool isRightMovePossible(float moveInPx) const;
    bool isLeftMovePossible (float moveInPx) const;
    bool isUpMovePossible   (float moveInPx) const;
    bool isDownMovePossible (float moveInPx) const;

    sf::Sprite const & getBackground() const;

    private:
    virtual void initTextures() final;
    virtual void initSprites () final;
    sf::Sprite  _spriteBckgnd;
    sf::Texture _textureBckgnd;
    std::string _bgFileName;
    float       _minPos;
    float       _maxPos;
};

class Boost : public IElementStatic {
    public:
    Boost(int nbPx,
          Dev::Game::Utils::Coordinates const & initPos,
          Dev::Game::Utils::Coordinates const & initBoostPos,
          float initSpeed);

    virtual void activateNightMode() final;
    void moveRight(float moveInPx);
    void moveLeft (float moveInPx);
    void moveUp   (float moveInPx);
    void moveDown (float moveInPx);

    sf::Sprite const & getBoost() const;

    private:
    virtual void initTextures() final;
    virtual void initSprites () final;

    sf::Sprite  _spriteBoost;
    sf::Texture _textureBoost;
};

class IElementDynamic : public IElement {
    public:
    IElementDynamic();
    IElementDynamic(int radius, int nbPx,
                    Dev::Game::Utils::Coordinates const & initialPositionInCell);
    virtual void initShapes() = 0;
    virtual void moveRight (float moveInPx) = 0;
    virtual void moveLeft  (float moveInPx) = 0;
    virtual void moveUp    (float moveInPx) = 0;
    virtual void moveDown  (float moveInPx) = 0;

    protected:
    int _radius;
    Dev::Game::Utils::Coordinates _initialPositionInPx;
    Dev::Game::Utils::Coordinates _initialPositionInPxInWindow;
};

class Light : public IElementDynamic {
    public:
    Light();
    Light(int radius, int nbPx,
          Dev::Game::Utils::Coordinates const & initialPositionInCell);
    virtual void initTextures() final;
    virtual void initShapes  () final;
    virtual void moveRight   (float moveInPx) final;
    virtual void moveLeft    (float moveInPx) final;
    virtual void moveUp      (float moveInPx) final;
    virtual void moveDown    (float moveInPx) final;
    virtual void activateNightMode() final;

    sf::CircleShape const & getBlindArea() const;
    sf::CircleShape const & getVisibleArea() const;

    private:
    sf::CircleShape _symbBlindArea;

    sf::CircleShape _symbVisibleArea;
    sf::Texture     _textureVisibleArea;
};

class Character : public IElementDynamic {
    public:
    Character();
    Character(int radius, int nbPx,
              Dev::Game::Utils::Coordinates            const & initialPositionInCell,
              Dev::Game::Utils::Coordinates            const & finalPositionInCell,
              Dev::Game::Elements::Light                     * light,
              Dev::Game::Elements::Background                * background,
              std::vector<Dev::Game::Elements::Boost*> const & boosts);
    virtual void initTextures() final;
    virtual void initShapes  () final;
    bool  checkObstacleRight  (Dev::Game::Utils::Obstacle    const & obstacle, float moveInPx);
    bool  checkObstacleLeft   (Dev::Game::Utils::Obstacle    const & obstacle, float moveInPx);
    bool  checkObstacleUp     (Dev::Game::Utils::Obstacle    const & obstacle, float moveInPx);
    bool  checkObstacleDown   (Dev::Game::Utils::Obstacle    const & obstacle, float moveInPx);
    float computeRightMoveInPx(Dev::Game::Utils::Obstacle    const & obstacle);
    float computeLeftMoveInPx (Dev::Game::Utils::Obstacle    const & obstacle);
    float computeUpMoveInPx   (Dev::Game::Utils::Obstacle    const & obstacle);
    float computeDownMoveInPx (Dev::Game::Utils::Obstacle    const & obstacle);
    bool  checkIfInCell       (Dev::Game::Utils::Coordinates const & cell);
    virtual void moveRight(float moveInPx) final;
    virtual void moveLeft (float moveInPx) final;
    virtual void moveUp   (float moveInPx) final;
    virtual void moveDown (float moveInPx) final;
    virtual void activateNightMode() final;
    void checkIfFound  ();
    void checkIfWin    ();
    bool getFoundStatus() const;
    bool getWinStatus  () const;
    void updateColor   ();
    Dev::Game::Utils::Direction computeNeededVerticalAssist(Dev::Game::Utils::Obstacle const & obstacle);
    Dev::Game::Utils::Direction computeNeededLateralAssist (Dev::Game::Utils::Obstacle const & obstacle);

    sf::CircleShape const & getBubble() const;
    sf::CircleShape const & getShadow() const;

    void setCinematicMode();

    private:
    sf::CircleShape _symbBubble;
    sf::Texture     _textureBubble;

    sf::CircleShape _symbShadow;
    sf::Texture     _textureShadow;

    Dev::Game::Elements::Light              * _light;
    Dev::Game::Elements::Background         * _background;
    std::vector<Dev::Game::Elements::Boost*>  _boosts;
    Dev::Game::Utils::Coordinates             _finalPositionInPx;
    
    bool _found;
    bool _win;
    int  _nbPx;
    bool _nightMode;
};

class HowToPlay : public IElementStatic {
    public:
    HowToPlay();

    virtual void activateNightMode() final;

    sf::Sprite const & getPicture() const;

    private:
    virtual void initTextures() final;
    virtual void initSprites() final;
    sf::Texture _htpTexture;
    sf::Sprite  _htpSprite;
};

} /*Elements*/
} /*Game*/
} /*Dev*/

#endif /*__DEV_GAMES_ELEMENTS_H__*/