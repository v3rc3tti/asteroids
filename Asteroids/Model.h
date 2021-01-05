#pragma once

#include <cstdint>
#include <vector>
#include <cstdlib>
#include "Vec2.h"
#include "PixelWindow.h"

enum class ModelType {
	ASTEROID = 1,
	SHIP,
	BULLET,
};

class Model {
public:
	Model(float x = 0.f, float y = 0.f, float dx = 0.f, float dy = 0.f);
	Model(std::vector<Vec2>* mesh, float x = 0.f, float y = 0.f, float scale = 1.f, float dx = 0.f, float dy = 0.f);
	Vec2 getPos();
	void setPos(Vec2 p);
	Vec2 getSpeed();
	void setSpeed(Vec2 s);
	float getAngle();
	void setAngle(float angle);
	float getScale();
	virtual void update();
	virtual void draw(PixelWindow* pWindow);

protected:

	float m_x;
	float m_y;
	float m_dx;
	float m_dy;
	float m_angle;
	float m_scale;
	std::vector<Vec2> *m_mesh;

	void scale(std::vector<Vec2>& v, float scale);
	void rotate(std::vector<Vec2>& v, float angle);
	void translate(std::vector<Vec2>& v, int x, int y);
};