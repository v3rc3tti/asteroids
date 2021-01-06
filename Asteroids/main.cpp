#include <Windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "ToroidalWindow.h"
#include "ShipModel.h"
#include "AsterModel.h"
#include "Model.h"

ToroidalWindow* pWindow;
std::vector<Model*> NextFrameModels;
bool g_keys[256];

bool isDead(Model* model) {
    return (model->isDead);
}

void AsterMetBullet(Model *aster, Model *bullet) {
    aster->isDead = true;
    bullet->isDead = true;
    Vec2 pos = aster->getPos();
    float randx = 2.f * rand() / RAND_MAX - 1.f;
    float randy = 2.f * rand() / RAND_MAX - 1.f;
    float scale = aster->getScale();
    if (scale >= 10.f) {
        NextFrameModels.push_back(new AsterModel(pos.x, pos.y, aster->getScale() / 2.f, randx, randy));
    }
}

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

bool isPointInside(Vec2 p1, float r, Vec2 p2) {
    float dist2 = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    if (dist2 <= r * r) {
        return true;
    }
    return false;
}

void ResolveCollisions(std::vector<Model*>& models) {
    typedef std::vector<Model*>::iterator Models;
    for (Models it = models.begin(); it != models.end(); it++) {
        for (Models sit = it+1; sit != models.end(); sit++) {
            
            Model* one = *it;
            Model* two = *sit;
            ModelType oneT = one->getType();
            ModelType twoT = two->getType();

            if (oneT == ModelType::SHIP && twoT == ModelType::ASTEROID
                || oneT == ModelType::ASTEROID && twoT == ModelType::SHIP) {
                //resolve ship-aster
                //start new game
                //NextFrameModels.clear();
            }
            else if (oneT == ModelType::BULLET && twoT == ModelType::ASTEROID) {
                //resolve bullet-aster
                if (isPointInside(two->getPos(), two->getScale(), one->getPos())) {
                    AsterMetBullet(two, one);
                }
            }
            else if (oneT == ModelType::ASTEROID && twoT == ModelType::BULLET) {
                //resolve bullet-aster
                if (isPointInside(one->getPos(), one->getScale(), two->getPos())) {
                    AsterMetBullet(one, two);
                }
            }
        }
    }
}

void StartGame(std::vector<Model*> &models) {
    //generate ship mesh
    std::vector<Vec2>* shipMesh = new std::vector<Vec2>();
    shipMesh->push_back({ 1.f, 0.0f });
    shipMesh->push_back({ -0.5f, .5f });
    shipMesh->push_back({ -0.5f, -.5f });

    //create models of asteroids
    models.push_back(new ShipModel(shipMesh, 200.f, 150.f, 10.f));
    models.push_back(new AsterModel(10.f, 10.f, 50.f, 0.2f, 0.2f));
    models.push_back(new AsterModel(100.f, 49.f, 20.f, 0.2f));
}

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    srand(time(NULL));
    pWindow = new ToroidalWindow();
    pWindow->initialize(320, 200, 2, L"TestWindow");

    std::vector<Model*> models;

    StartGame(models);

    while (true) {
        if (!procSysMsg()) {
            break;
        }

        pWindow->clearColor(0, 0, 0);

        for (std::vector<Model*>::iterator it = NextFrameModels.begin(); it != NextFrameModels.end(); it++) {
            models.push_back(*it);
        }
        NextFrameModels.clear();

        for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++) {
            (*it)->update();
            if ((*it)->getType() == ModelType::BULLET) {
                Vec2 pos = (*it)->getPos();
                if (pos.x >= pWindow->getWidth() || pos.x < 0.f || pos.y >= pWindow->getHeight()
                    || pos.y < 0) {
                    (*it)->isDead = true;
                }
            }
        }

        ResolveCollisions(models);

        std::vector<Model*>::iterator it = models.begin();
        while (it != models.end()) {
            std::vector<Model*>::iterator next = it;
            next++;
            if ((*it)->isDead) {
                delete (*it);
                next = models.erase(it);
            }
            it = next;
        }

        for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++) {
            (*it)->draw(pWindow);
        }
        pWindow->redraw();
        Sleep(20);
    }
    pWindow->shutdown();
}