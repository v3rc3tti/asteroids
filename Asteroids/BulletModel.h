#pragma once

#include "Model.h"

class BulletModel: public Model
{
public:
	static const ModelType type = ModelType::BULLET;

	BulletModel(float x, float y, float dx, float dy);
};

