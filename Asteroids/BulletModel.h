#pragma once

#include "Model.h"

class BulletModel: public Model
{
public:
	BulletModel(float x, float y, float dx, float dy);
	ModelType getType() override;
};

