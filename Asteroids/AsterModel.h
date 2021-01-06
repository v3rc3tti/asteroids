#pragma once

#include "Model.h"

class AsterModel : public Model {
public:
	static const ModelType type = ModelType::ASTEROID;

	AsterModel(float x = 0.f, float y = 0.f, float scale = 1.f, float dx = 0.f, float dy = 0.f);
	void update() override;
	ModelType getType() override;
};