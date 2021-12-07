#ifndef __DEV_GAMES_STATEMENTS_H__
#define __DEV_GAMES_STATEMENTS_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Dev {
namespace Game {
namespace Statements {

enum class MenuStatement {
    TRYAGAIN,
    QUIT,
    NEXTLEVEL,
    START,
    HOWTOPLAY,
    MAINMENU,
    NONE
};

enum class Size {
    BIG,
    SMALL
};
    
class Statement
{
    public:
    Statement(std::string const & labelString,
              std::string const & fontFileName,
              unsigned int        characterSize = 30);
    sf::Text const & getLabel() const;
    Dev::Game::Statements::MenuStatement getMenuStatementFromLabel() const;

    protected:
    sf::Text _label;
    sf::Font _font;
};

class StaticStatement : public Statement
{
    public:
    StaticStatement(std::string const & labelString,
                    std::string const & fontFileName,
                    unsigned int        characterSize,
                    sf::Color   const & color);
};

class DynamicStatement : public Statement
{
    public:
    DynamicStatement(std::string const & labelString,
                     std::string const & fontFileName);
    ~DynamicStatement();
    virtual void updateLabelShape() = 0;
    void restartClock();
    float getElapsedTimeInMilliseconds();

    protected:
    sf::Clock* _clock;

    private:

};

class SpawnStatement : public DynamicStatement
{
    public:
    SpawnStatement(std::string const & labelString,
                   std::string const & fontFileName);

    virtual void updateLabelShape() final;

    private:
    bool _launched;
};

class BounceStatement : public DynamicStatement
{
    public:
    BounceStatement(std::string const & labelString,
                    std::string const & fontFileName,
                    int posY);
    void select();
        virtual void updateLabelShape() final;
    void unselect();
        void resetPosition();

    Size getSize() const;

    private:
    int   _amplitude;
    float _period;
    int   _posY;
    float _friction;
    bool  _timerStarted;
    Size  _size;
};


class Menu
{
    public:
    Menu(Dev::Game::Statements::StaticStatement               const * staticStatement,
         std::vector<Dev::Game::Statements::BounceStatement*> const & bounceStatements);

    void updateSelectedStatement();
    Dev::Game::Statements::MenuStatement getSelectedStatement() const;
    void upMove  ();
    void downMove();
    void restartClock();

    Dev::Game::Statements::StaticStatement               const * getStaticStatement () const; 
    std::vector<Dev::Game::Statements::BounceStatement*> const & getBounceStatements() const;

    private:
    Dev::Game::Statements::StaticStatement const *       _staticStatement;
    std::vector<Dev::Game::Statements::BounceStatement*> _bounceStatements;
    int _currentSelectedStatementIndex;
};


} /*Statements*/
} /*Game*/
} /*Dev*/

#endif /*__DEV_GAMES_STATEMENTS_H__*/