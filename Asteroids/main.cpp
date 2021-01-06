#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "ToroidalWindow.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    srand(time(NULL));
    ToroidalWindow* pWindow = new ToroidalWindow();
    pWindow->initialize(320, 200, 2, L"TestWindow");

    Game* game = new Game(pWindow);
    game->start();

    delete game;
    pWindow->shutdown();
}