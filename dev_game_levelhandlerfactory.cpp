#include "dev_game_levelhandlerfactory.h"
#include "path.h"

namespace Dev     {
namespace Game    {
namespace Handler {

Levels::Levels()
{
    /* '----------------------------' Level 0 '----------------------------' */

    std::vector<Dev::Game::Utils::Obstacle> cinematicObstacles;
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(   0, 1600,  600,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 100, 1800,  800,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1000, 1800,  200,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1300, 1800,  200,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1600, 1800,  300,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 700, 1400,  300,  300, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 100, 1300,  500,  200, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1300, 1100,  300,  500, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1100, 1100,  100,  500, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1200, 1300,  100,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 100,  100,  100,  300, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 200,  300,  100,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1400, 1600,  100,  200, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1700,  800,  100, 1000, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1100,  600,  700,  200, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 700,  900,  500,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 700, 1000,  100,  300, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 800, 1200,  300,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(   0, 1000,  300,  200, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 400,  900,  200,  300, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(   0,  500,  500,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 600,  500,  300,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 300,  400,  100,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 700,  400,  100,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1400,  900,  100,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1800, 1000,  100,  500, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1900,  600,  100,  200, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 100,  700,  200,  200, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 600,  700,  100,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1400,  100,  300,  400, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1100,  300,  200,  300, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 900,  500,  100,  400, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 900,    0,  100,  400, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1000,  300,  100,  100, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle( 300,  200,  500,  200, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1900,    0,  100,  500, 180, 2000));
    cinematicObstacles.push_back(Dev::Game::Utils::Obstacle(1100,    0,  100,  200, 180, 2000));

    Dev::Game::Utils::Coordinates cinematicInitialPosition(16, 12);
    Dev::Game::Utils::Coordinates cinematicFinalPosition  (18, 15);
    std::string cinematicBgFileName = Path::Pictures::Maps + "lvl0.jpg";
    int cinematicNbPx = 2000;
    int cinematicLightRadius = 400;
    int cinematicCharacterRadius = 25;
    float cinematicTimeToReturn = 50 * 100 / 250 + 1.5f;

    std::vector<Dev::Game::Utils::BoostPosition> cinematicBoostPositions;

    _levels.push_back(Dev::Game::Utils::Level(cinematicObstacles,
                                              cinematicInitialPosition,
                                              cinematicFinalPosition,
                                              cinematicBgFileName,
                                              cinematicNbPx,
                                              cinematicLightRadius,
                                              cinematicCharacterRadius,
                                              cinematicTimeToReturn,
                                              cinematicBoostPositions));

    
    /* '----------------------------' Level 1 '----------------------------' */

    std::vector<Dev::Game::Utils::Obstacle> lvl1Obstacles;
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(  0, 200, 500, 300));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(100, 900, 900, 100));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(100, 600, 100, 300));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 700, 700, 100));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 600, 400, 100));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(500, 200, 200, 100));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(600, 300, 100, 200));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(800, 200, 100, 400));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(900, 200, 100, 100));
    lvl1Obstacles.push_back(Dev::Game::Utils::Obstacle(100,   0, 900, 100));

    Dev::Game::Utils::Coordinates lvl1InitialPosition( 1, 10);
    Dev::Game::Utils::Coordinates lvl1FinalPosition  ( 1,  1);
    std::string lvl1BgFileName = Path::Pictures::Maps + "lvl1.jpg";
    int lvl1NbPx = 1000;
    int lvl1LightRadius = 400;
    int lvl1CharacterRadius = 25;
    float lvl1TimeToReturn = 23 * 100 / 250 + 1.5f;
    std::vector<Dev::Game::Utils::BoostPosition> lvl1BoostPositions;

    _levels.push_back(Dev::Game::Utils::Level(lvl1Obstacles,
                                              lvl1InitialPosition,
                                              lvl1FinalPosition,
                                              lvl1BgFileName,
                                              lvl1NbPx,
                                              lvl1LightRadius,
                                              lvl1CharacterRadius,
                                              lvl1TimeToReturn,
                                              lvl1BoostPositions));

    /* '----------------------------' Level 2 '----------------------------' */

    std::vector<Dev::Game::Utils::Obstacle> lvl2Obstacles;
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(  0, 200, 500, 300, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(100, 900, 900, 100, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(100, 600, 100, 300, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 700, 700, 100, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 600, 400, 100, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(500, 200, 200, 100, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(600, 300, 100, 200, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(800, 200, 100, 400, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(900, 200, 100, 100, -90));
    lvl2Obstacles.push_back(Dev::Game::Utils::Obstacle(100,   0, 900, 100, -90));

    Dev::Game::Utils::Coordinates lvl2InitialPosition( 9, 10);
    Dev::Game::Utils::Coordinates lvl2FinalPosition  ( 2, 10);
    std::string lvl2BgFileName = Path::Pictures::Maps + "lvl2.jpg";
    int lvl2NbPx = 1000;
    int lvl2LightRadius = 200;
    int lvl2CharacterRadius = 25;
    float lvl2TimeToReturn = 21 * 100 / 250 + 1.5f;
    std::vector<Dev::Game::Utils::BoostPosition> lvl2BoostPositions;

    _levels.push_back(Dev::Game::Utils::Level(lvl2Obstacles,
                                              lvl2InitialPosition,
                                              lvl2FinalPosition,
                                              lvl2BgFileName,
                                              lvl2NbPx,
                                              lvl2LightRadius,
                                              lvl2CharacterRadius,
                                              lvl2TimeToReturn,
                                              lvl2BoostPositions));


    /* '----------------------------' Level 3 '----------------------------' */

    std::vector<Dev::Game::Utils::Obstacle> lvl3Obstacles;
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(100, 100, 100, 800));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 800, 100, 200));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 500, 100, 200));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 100, 100, 200));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(200, 100, 100, 100));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(300, 400, 500, 100));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(500, 600, 100, 300));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(700, 900, 100, 100));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(600, 700, 300, 100));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(500, 100, 300, 100));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(800, 100, 100, 600));
    lvl3Obstacles.push_back(Dev::Game::Utils::Obstacle(500,   0, 100, 100));

    Dev::Game::Utils::Coordinates lvl3InitialPosition( 1, 10);
    Dev::Game::Utils::Coordinates lvl3FinalPosition  ( 7,  1);
    std::string lvl3BgFileName = Path::Pictures::Maps + "lvl3.jpg";
    int lvl3NbPx = 1000;
    int lvl3LightRadius = 300;
    int lvl3CharacterRadius = 25;
    float lvl3TimeToReturn = 25 * 100 / 250 + 1.5f;
    std::vector<Dev::Game::Utils::BoostPosition> lvl3BoostPositions;

    _levels.push_back(Dev::Game::Utils::Level(lvl3Obstacles,
                                              lvl3InitialPosition,
                                              lvl3FinalPosition,
                                              lvl3BgFileName,
                                              lvl3NbPx,
                                              lvl3LightRadius,
                                              lvl3CharacterRadius,
                                              lvl3TimeToReturn,
                                              lvl3BoostPositions));

    /* '----------------------------' Level 4 '----------------------------' */

    std::vector<Dev::Game::Utils::Obstacle> lvl4Obstacles;
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(   0, 1600,  600,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 100, 1800,  800,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1000, 1800,  200,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1300, 1800,  200,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1600, 1800,  300,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 700, 1400,  300,  300));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 100, 1300,  500,  200));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1300, 1100,  300,  500));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1100, 1100,  100,  500));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1200, 1300,  100,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 100,  100,  100,  300));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 200,  300,  100,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1400, 1600,  100,  200));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1700,  800,  100, 1000));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,  600,  700,  200));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 700,  900,  500,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 700, 1000,  100,  300));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 800, 1200,  300,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(   0, 1000,  300,  200));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 400,  900,  200,  300));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(   0,  500,  500,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 600,  500,  300,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 300,  400,  100,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 700,  400,  100,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1400,  900,  100,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1800, 1000,  100,  500));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1900,  600,  100,  200));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 100,  700,  200,  200));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 600,  700,  100,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1400,  100,  300,  400));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,  300,  200,  300));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 900,  500,  100,  400));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 900,    0,  100,  400));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1000,  300,  100,  100));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle( 300,  200,  500,  200));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1900,    0,  100,  500));
    lvl4Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,    0,  100,  200));

    Dev::Game::Utils::Coordinates lvl4InitialPosition(13, 15);
    Dev::Game::Utils::Coordinates lvl4FinalPosition  ( 3,  5);
    std::string lvl4BgFileName = Path::Pictures::Maps + "lvl4.jpg";
    int lvl4NbPx = 2000;
    int lvl4LightRadius = 400;
    int lvl4CharacterRadius = 25;
    float lvl4TimeToReturn = 50 * 100 / 250 + 1.5f;

    std::vector<Dev::Game::Utils::BoostPosition> lvl4BoostPositions;

    _levels.push_back(Dev::Game::Utils::Level(lvl4Obstacles,
                                              lvl4InitialPosition,
                                              lvl4FinalPosition,
                                              lvl4BgFileName,
                                              lvl4NbPx,
                                              lvl4LightRadius,
                                              lvl4CharacterRadius,
                                              lvl4TimeToReturn,
                                              lvl4BoostPositions));


    /* '----------------------------' Level 5 '----------------------------' */

    std::vector<Dev::Game::Utils::Obstacle> lvl5Obstacles;
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,  100, 300,  100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,  700, 100,  700));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle(1000,  800, 100,  100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle(1300,  300, 100,  600));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle(1400, 1000, 100,  200));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle(1200, 1300, 300,  100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle(1200, 1000, 100,  100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 900,  100, 100, 1100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 700,  100, 100, 1100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 300,  100, 100, 1100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 500,  200, 100,  300));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 600,  300, 100,  100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 500,  900, 100,  500));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 500,  600, 100,  200));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 100,  800, 100,  600));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 200, 1300, 200,  100));
    lvl5Obstacles.push_back(Dev::Game::Utils::Obstacle( 100,    0, 100,  700));

    Dev::Game::Utils::Coordinates lvl5InitialPosition(15,  1);
    Dev::Game::Utils::Coordinates lvl5FinalPosition  ( 9, 15);
    std::string lvl5BgFileName = Path::Pictures::Maps + "lvl5.jpg";
    int lvl5NbPx = 1500;
    int lvl5LightRadius = 300;
    int lvl5CharacterRadius = 25;
    float lvl5TimeToReturn = 17 * 100 / 250 + 1.5f;

    std::vector<Dev::Game::Utils::BoostPosition> lvl5BoostPositions;
    lvl5BoostPositions.push_back(Dev::Game::Utils::BoostPosition(Dev::Game::Utils::Coordinates(5, 14), 3000.f));
    lvl5BoostPositions.push_back(Dev::Game::Utils::BoostPosition(Dev::Game::Utils::Coordinates(5,  3),  250.f));

    _levels.push_back(Dev::Game::Utils::Level(lvl5Obstacles,
                                              lvl5InitialPosition,
                                              lvl5FinalPosition,
                                              lvl5BgFileName,
                                              lvl5NbPx,
                                              lvl5LightRadius,
                                              lvl5CharacterRadius,
                                              lvl5TimeToReturn,
                                              lvl5BoostPositions));



    /* '----------------------------' Level 6 '----------------------------' */

    std::vector<Dev::Game::Utils::Obstacle> lvl6Obstacles;
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(   0, 1600,  600,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 100, 1800,  800,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1000, 1800,  200,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1300, 1800,  200,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1600, 1800,  300,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 700, 1400,  300,  300, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 100, 1300,  500,  200, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1300, 1100,  300,  500, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1100, 1100,  100,  500, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1200, 1300,  100,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 100,  100,  100,  300, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 200,  300,  100,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1400, 1600,  100,  200, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1700,  800,  100, 1000, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,  600,  700,  200, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 700,  900,  500,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 700, 1000,  100,  300, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 800, 1200,  300,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(   0, 1000,  300,  200, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 400,  900,  200,  300, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(   0,  500,  500,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 600,  500,  300,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 300,  400,  100,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 700,  400,  100,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1400,  900,  100,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1800, 1000,  100,  500, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1900,  600,  100,  200, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 100,  700,  200,  200, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 600,  700,  100,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1400,  100,  300,  400, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,  300,  200,  300, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 900,  500,  100,  400, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 900,    0,  100,  400, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1000,  300,  100,  100, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle( 300,  200,  500,  200, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1900,    0,  100,  500, -90, 2000));
    lvl6Obstacles.push_back(Dev::Game::Utils::Obstacle(1100,    0,  100,  200, -90, 2000));

    Dev::Game::Utils::Coordinates lvl6InitialPosition(12,  9);
    Dev::Game::Utils::Coordinates lvl6FinalPosition  (20, 13);
    std::string lvl6BgFileName = Path::Pictures::Maps + "lvl6.jpg";
    int lvl6NbPx = 2000;
    int lvl6LightRadius = 400;
    int lvl6CharacterRadius = 25;
    float lvl6TimeToReturn = 52 * 100 / 250 + 1.5f;

    std::vector<Dev::Game::Utils::BoostPosition> lvl6BoostPositions;

    _levels.push_back(Dev::Game::Utils::Level(lvl6Obstacles,
                                              lvl6InitialPosition,
                                              lvl6FinalPosition,
                                              lvl6BgFileName,
                                              lvl6NbPx,
                                              lvl6LightRadius,
                                              lvl6CharacterRadius,
                                              lvl6TimeToReturn,
                                              lvl6BoostPositions));
}

Dev::Game::Utils::Level const & 
Levels::getLevel(int index)
{
    return _levels[index];
}


} /* Dev */
} /* Game */
} /* Handler */