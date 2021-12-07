#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "game.h"

int main()
{
    Game labyblind;
    while (labyblind.getWindow()->isOpen())
    {
        labyblind.update();
        labyblind.render();
    }
    return 0;
}