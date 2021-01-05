#pragma once

#include "Model.h"

class ShipModel: public Model {
public:
	static const ModelType type = ModelType::SHIP;

	ShipModel(std::vector<Vec2>* mesh, float x = 0.f, float y = 0.f, float scale = 1.f, float dx = 0.f, float dy = 0.f);
	void update() override;
};