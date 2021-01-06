#include "AsterModel.h"

AsterModel::AsterModel(float x, float y, float scale, float dx, float dy)
	: Model(x, y, dx, dy)
{
    m_mesh = new std::vector<Vec2>();
    int sectors = 40;
    double sectorAngle = 2 * 3.1416 / sectors;
    double angle = 0.0;
    for (int i = 0; i < sectors; i++) {
        Vec2 p;
        float randDelta = .25f * rand() / (float)RAND_MAX;
        p.x = cosf(angle) * (1 + randDelta);
        p.y = sinf(angle) * (1 + randDelta);
        m_mesh->push_back(p);
        angle += sectorAngle;
    }

    m_scale = scale;
}

void AsterModel::update() {
	m_angle += 0.01f;
	Model::update();
}

ModelType AsterModel::getType() {
	return ModelType::ASTEROID;
}