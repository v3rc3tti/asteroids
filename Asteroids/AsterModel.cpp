#include "AsterModel.h"

AsterModel::AsterModel(std::vector<Vec2>* mesh, float x, float y, float scale, float dx, float dy)
	: Model(mesh, x, y, scale, dx, dy)
{}

void AsterModel::update() {
	m_angle += 0.01f;
	Model::update();
}