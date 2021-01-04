#include <Windows.h>
#include "ShipModel.h"

extern bool g_keys[];

ShipModel::ShipModel(std::vector<Vec2>* mesh, float x, float y, float scale, float dx, float dy)
	:Model(mesh, x, y, scale, dx, dy) {
}

void ShipModel::update() {
    //rotation
    if (g_keys[VK_LEFT]) {
        setAngle(getAngle() - 0.05f);
    }
    else if (g_keys[VK_RIGHT]) {
        setAngle(getAngle() + 0.05f);
    }

    //thrust
    if (g_keys[VK_UP]) {
        float angle = getAngle();
        float dx = cosf(angle) * 0.005f;
        float dy = sinf(angle) * 0.005f;
        Vec2 speed = getSpeed();
        speed.x += dx;
        speed.y += dy;
        setSpeed(speed);
    }

    Model::update();
}