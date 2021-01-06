#include <Windows.h>
#include "ShipModel.h"
#include "BulletModel.h"

extern bool g_keys[];
extern std::vector<Model*> NextFrameModels;

ShipModel::ShipModel(std::vector<Vec2>* mesh, float x, float y, float scale, float dx, float dy)
	:Model(mesh, x, y, scale, dx, dy) {
}

void ShipModel::update() {
    //rotation
    if (g_keys[VK_LEFT]) {
        setAngle(getAngle() - 0.1f);
    }
    else if (g_keys[VK_RIGHT]) {
        setAngle(getAngle() + 0.1f);
    }

    //thrust
    if (g_keys[VK_UP]) {
        float angle = getAngle();
        float dx = cosf(angle) * 0.05f;
        float dy = sinf(angle) * 0.05f;
        Vec2 speed = getSpeed();
        speed.x += dx;
        speed.y += dy;
        setSpeed(speed);
    }

    static bool wasSpaceDown = true;
    if (g_keys[VK_SPACE] && wasSpaceDown) {
        wasSpaceDown = false;
        float bulletDx = cosf(getAngle()) * 5.f;
        float bulletDy = sinf(getAngle()) * 5.f;
        NextFrameModels.push_back(new BulletModel(m_x, m_y, bulletDx, bulletDy));
    }
    else if (!g_keys[VK_SPACE]) {
        wasSpaceDown = true;
    }

    Model::update();
}

ModelType ShipModel::getType() {
    return ModelType::SHIP;
}