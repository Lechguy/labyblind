#include "dev_game_statements.h"
#include "dev_math.h"
#include <cmath>
#include <iostream>

#define FRICTION_THRESHOLD 0.2f

namespace Dev {
namespace Game {
namespace Statements {

Statement::Statement(std::string const & labelString,
                     std::string const & fontFileName,
                     unsigned int        characterSize)
{
    _label.setString(labelString);
    _font.loadFromFile(fontFileName);
    _label.setCharacterSize(characterSize);
    _label.setFont(_font);
}

sf::Text const & 
Statement::getLabel() const
{
    return _label;
}

Dev::Game::Statements::MenuStatement
Statement::getMenuStatementFromLabel() const
{
    if (static_cast<std::string>(_label.getString()) == "try again")
    {
        return Dev::Game::Statements::MenuStatement::TRYAGAIN;
    }
    else if (static_cast<std::string>(_label.getString()) == "quit")
    {
        return Dev::Game::Statements::MenuStatement::QUIT;
    }
    else if (static_cast<std::string>(_label.getString()) == "next level")
    {
        return Dev::Game::Statements::MenuStatement::NEXTLEVEL;
    }
    else if (static_cast<std::string>(_label.getString()) == "start")
    {
        return Dev::Game::Statements::MenuStatement::START;
    }
    else if (static_cast<std::string>(_label.getString()) == "how to play?")
    {
        return Dev::Game::Statements::MenuStatement::HOWTOPLAY;
    }
    else if (static_cast<std::string>(_label.getString()) == "main menu")
    {
        return Dev::Game::Statements::MenuStatement::MAINMENU;
    }
    else
    {
        return Dev::Game::Statements::MenuStatement::NONE;
    }
}


/* '---------------------------------------------------------------------' */


StaticStatement::StaticStatement(std::string const & labelString,
                                 std::string const & fontFileName,
                                 unsigned int        characterSize,
                                 sf::Color   const & color) :
Statement(labelString, fontFileName, characterSize)
{
    _label.setPosition(500.f - _label.getGlobalBounds().width/2,
                       500.f - _label.getGlobalBounds().height);
    _label.setFillColor(color);
}


/* '---------------------------------------------------------------------' */


DynamicStatement::DynamicStatement(std::string const & labelString,
                                   std::string const & fontFileName) :
Statement(labelString, fontFileName)
{
    _clock = new sf::Clock;
}

DynamicStatement::~DynamicStatement()
{
    delete _clock;
}

void
DynamicStatement::restartClock()
{
    _clock->restart();
}


/* '---------------------------------------------------------------------' */


SpawnStatement::SpawnStatement(std::string const & labelString,
                               std::string const & fontFileName) :
DynamicStatement(labelString, fontFileName),
_launched(false)
{
    _label.setFillColor(sf::Color(255.f, 255.f, 255.f, 64.f));
}

void
SpawnStatement::updateLabelShape()
{
    if (!_launched)
    {
        _clock->restart();
        _launched = true;
    }
    float const t = _clock->getElapsedTime().asSeconds();

    unsigned int const size = std::round(1500 * (1 - t));
    _label.setCharacterSize(size);
    _label.setPosition(500.f - _label.getGlobalBounds().width/2,
                       500.f - _label.getGlobalBounds().height);
}


/* '---------------------------------------------------------------------' */


BounceStatement::BounceStatement(std::string const & labelString,
                                 std::string const & fontFileName,
                                 int posY) :
DynamicStatement(labelString, fontFileName),
_posY(posY),
_amplitude(50.f),
_period(1.f),
_friction(1.f),
_timerStarted(false),
_size(Size::SMALL)
{}

void
BounceStatement::select()
{
    _label.setCharacterSize(80);
    _label.setFillColor(sf::Color(255.f, 255.f, 255.f, 255.f));
    _size = Size::BIG;
    updateLabelShape();
}

void
BounceStatement::updateLabelShape()
{
    if (!_timerStarted)
    {
        restartClock();
        _timerStarted = true;
    }
    float const tau = 2 * _period;
    float t   = _clock->getElapsedTime().asSeconds();
    _friction = std::exp(-t / tau);
    if (_friction < FRICTION_THRESHOLD)
    {
        restartClock();
        t = _clock->getElapsedTime().asSeconds();
        _friction = std::exp(-t / tau);
    }
    float const A = _amplitude * std::pow(_friction, 2);
    float const T = 2 * _period * _friction;
    float const posY_variable = -std::abs(A * std::sin(2 * 3.14f * (1/T) * t));
    float const posY_cte      = _posY - 500.f + _amplitude / 2 * 0.75f;
    _label.setPosition(500.f - _label.getGlobalBounds().width/2,
                       500.f - _label.getGlobalBounds().height + posY_cte + posY_variable);
}

void
BounceStatement::unselect()
{
    _label.setCharacterSize(60);
    _label.setFillColor(sf::Color(255.f, 255.f, 255.f, 128.f));
    _size = Size::SMALL;
    resetPosition();
}

void
BounceStatement::resetPosition()
{
    _label.setPosition(500.f - _label.getGlobalBounds().width/2,
                       500.f - _label.getGlobalBounds().height + _posY - 500.f);
}

Size
BounceStatement::getSize() const
{
    return _size;
}


/* '---------------------------------------------------------------------' */


Menu::Menu(Dev::Game::Statements::StaticStatement               const * staticStatement,
           std::vector<Dev::Game::Statements::BounceStatement*> const & bounceStatements) :
_staticStatement(staticStatement),
_bounceStatements(bounceStatements),
_currentSelectedStatementIndex(0)
{}

void
Menu::updateSelectedStatement()
{
    for (int i = 0; i < _bounceStatements.size(); ++i)
    {
        if (i == _currentSelectedStatementIndex)
        {
            _bounceStatements[i]->select();
        }
        else
        {
            _bounceStatements[i]->unselect();
        }
    }
}

Dev::Game::Statements::MenuStatement
Menu::getSelectedStatement() const
{
    return _bounceStatements[_currentSelectedStatementIndex]->getMenuStatementFromLabel();
}

void
Menu::upMove()
{
    if (_currentSelectedStatementIndex != std::max<int>(_currentSelectedStatementIndex - 1, 0))
    {
        --_currentSelectedStatementIndex;
        restartClock();
    }
}

void
Menu::downMove()
{
    if (_currentSelectedStatementIndex != std::min<int>(_currentSelectedStatementIndex + 1, _bounceStatements.size() - 1))
    {
        ++_currentSelectedStatementIndex;
        restartClock();
    }
}

void
Menu::restartClock()
{
    _bounceStatements[_currentSelectedStatementIndex]->restartClock();
}

Dev::Game::Statements::StaticStatement const * 
Menu::getStaticStatement() const
{
    return _staticStatement;
}

std::vector<Dev::Game::Statements::BounceStatement*> const & 
Menu::getBounceStatements() const
{
    return _bounceStatements;
}


/* '---------------------------------------------------------------------' */


} /*Statements*/
} /*Game*/
} /*Dev*/