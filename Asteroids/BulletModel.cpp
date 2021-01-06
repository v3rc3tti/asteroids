#include "BulletModel.h"

BulletModel::BulletModel(float x, float y, float dx, float dy)
	:Model(x, y, dx, dy)
{}

ModelType BulletModel::getType() {
	return ModelType::BULLET;
}