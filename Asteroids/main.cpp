#include <Windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ToroidalWindow.h"
#include "ShipModel.h"
#include "Model.h"

ToroidalWindow* pWindow;
bool g_keys[256];

void procKeyMessage(MSG msg) {
    UINT uMsg = msg.message;
    WPARAM wParam = msg.wParam;

    if (uMsg == WM_KEYDOWN) {
        g_keys[wParam] = true;
    }
    else if (uMsg == WM_KEYUP) {
        g_keys[wParam] = false;
    }
}

bool procSysMsg() {
    MSG msg = { 0 };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            return false;
        } else if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP) {
            procKeyMessage(msg);
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return true;
}

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    srand(time(NULL));
    pWindow = new ToroidalWindow();
    pWindow->initialize(320, 200, 2, L"TestWindow");

    //generate asteroid mesh

    std::vector<Vec2> mesh;
    int sectors = 40;
    double sectorAngle = 2 * 3.1416 / sectors;
    double angle = 0.0;
    for (int i = 0; i < sectors; i++) {
        Vec2 p;
        float randDelta = .25f * rand() / (float)RAND_MAX;
        p.x = cosf(angle) * (1 + randDelta);
        p.y = sinf(angle) * (1 + randDelta);
        mesh.push_back(p);
        angle += sectorAngle;
    }

    //generate ship mesh
    std::vector<Vec2> shipMesh;
    shipMesh.push_back({ 1.f, 0.0f });
    shipMesh.push_back({ -0.5f, .5f });
    shipMesh.push_back({ -0.5f, -.5f });

    std::vector<Model*> models;

    //create models of asteroids

    models.push_back(new ShipModel(&shipMesh, 200.f, 150.f, 10.f));
    models.push_back(new Model(&mesh, 10.f, 10.f, 50.f, 0.2f, 0.2f));
    models.push_back(new Model(&mesh, 100.f, 49.f, 20.f, 0.2f));

    while (true) {
        if (!procSysMsg()) {
            break;
        }

        pWindow->clearColor(0, 0, 0);
        for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++) {
            (*it)->update();
            (*it)->draw(pWindow);
        }
        pWindow->redraw();
        Sleep(20);
    }
    pWindow->shutdown();
}