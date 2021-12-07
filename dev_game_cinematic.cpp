#include "dev_game_cinematic.h"
#include "stdlib.h"
#include <iostream>

namespace Dev {
namespace Game {

Cinematic::Cinematic() :
_currentDirection(Dev::Game::Utils::Direction::DOWN)
{}

void
Cinematic::computeAnotherDirection()
{
    int const randomNumber = rand() % 2;
    switch (randomNumber)
    {
    /* '-----' Clockwise '-----' */
    case 0:
        switch (_currentDirection)
        {
        case Dev::Game::Utils::Direction::RIGHT:
            _currentDirection = Dev::Game::Utils::Direction::DOWN;
            break;

        case Dev::Game::Utils::Direction::DOWN:
            _currentDirection = Dev::Game::Utils::Direction::LEFT;
            break;

        case Dev::Game::Utils::Direction::LEFT:
            _currentDirection = Dev::Game::Utils::Direction::UP;
            break;

        case Dev::Game::Utils::Direction::UP:
            _currentDirection = Dev::Game::Utils::Direction::RIGHT;
            break;
        
        default:
            _currentDirection = Dev::Game::Utils::Direction::NONE;
            break;
        }
        break;

    /* '-----' Counter-clockwise '-----' */
    case 1:
        switch (_currentDirection)
        {
            case Dev::Game::Utils::Direction::RIGHT:
                _currentDirection = Dev::Game::Utils::Direction::UP;
                break;

            case Dev::Game::Utils::Direction::UP:
                _currentDirection = Dev::Game::Utils::Direction::LEFT;
                break;

            case Dev::Game::Utils::Direction::LEFT:
                _currentDirection = Dev::Game::Utils::Direction::DOWN;
                break;

            case Dev::Game::Utils::Direction::DOWN:
                _currentDirection = Dev::Game::Utils::Direction::RIGHT;
                break;
            
            default:
                _currentDirection = Dev::Game::Utils::Direction::NONE;
                break;
        }
        break;
    }
}

Dev::Game::Utils::Direction
Cinematic::getCurrentDirection() const
{
    return _currentDirection;
}

} /* Game */
} /* Dev */