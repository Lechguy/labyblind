#include "dev_game_utils.h"

namespace Dev {
namespace Game {

class Cinematic
{
    public:
    Cinematic();
    void computeAnotherDirection();
    Dev::Game::Utils::Direction getCurrentDirection() const;

    private:
    Dev::Game::Utils::Direction _currentDirection;
};

} /* Game */
} /* Dev */