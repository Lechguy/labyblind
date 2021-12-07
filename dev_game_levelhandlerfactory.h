#ifndef __DEV_GAME_HANDLER_H__
#define __DEV_GAME_HANDLER_H__

#include <map>
#include <vector>
#include "dev_game_utils.h"

namespace Dev     {
namespace Game    {
namespace Handler {

class Levels
{
    public:
    Levels();
    Dev::Game::Utils::Level const & getLevel(int index);

    private:
    std::vector<Dev::Game::Utils::Level> _levels;
};

} /* Dev */
} /* Game */
} /* Handler */

#endif /* __DEV_GAME_HANDLER_H__ */