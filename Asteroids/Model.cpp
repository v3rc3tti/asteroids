#include <vector>
#include "Model.h"

Model::Model(std::vector<Vec2>* mesh, float x, float y, float scale, float dx, float dy) {
	m_x = x;
	m_y = y;
	m_dx = dx;
	m_dy = dy;
	m_angle = 0.f;
	m_scale = scale;
	m_mesh = mesh;
}

Vec2 Model::getPos() {
	Vec2 p = { m_x, m_y };
	return p;
}

void Model::setPos(Vec2 p) {
	m_x = p.x;
	m_y = p.y;
}

float Model::getAngle() {
	return m_angle;
}

void Model::setAngle(float angle) {
	m_angle = angle;
}

Vec2 Model::getSpeed() {
	Vec2 sp = { m_dx, m_dy };
	return sp;
}

void Model::setSpeed(Vec2 s) {
	m_dx = s.x;
	m_dy = s.y;
}

void Model::update() {
	m_x += m_dx;
	m_y += m_dy;
}

void Model::draw(PixelWindow* pWindow) {

	if (m_x < 0) {
		m_x += pWindow->getWidth();
	}
	else if (m_x >= pWindow->getWidth()) {
		m_x -= pWindow->getWidth();
	}

	if (m_y < 0) {
		m_y += pWindow->getHeight();
	}
	else if (m_y >= pWindow->getHeight()) {
		m_y -= pWindow->getHeight();
	}

	std::vector<Vec2>* points = new std::vector<Vec2>(*m_mesh);
	rotate(*points, m_angle);
	scale(*points, m_scale);
	translate(*points, m_x, m_y);

	for (int i = 0; i < points->size(); i++) {
		Vec2 p1 = (*points)[i];
		Vec2 p2 = (*points)[(i + 1) % points->size()];
		pWindow->drawLine(p1.x, p1.y, p2.x, p2.y, 255, 255, 255);
	}
	delete points;
}

void Model::scale(std::vector<Vec2>& v, float scale) {
	for (int i = 0; i < v.size(); i++) {
		v[i].x *= scale;
		v[i].y *= scale;
	}
}

void Model::rotate(std::vector<Vec2>& v, float angle) {
	for (int i = 0; i < v.size(); i++) {
		Vec2 old = v[i];
		v[i].x = old.x * cos(angle) - old.y * sin(angle);
		v[i].y = old.x * sin(angle) + old.y * cos(angle);
	}
}

void Model::translate(std::vector<Vec2>& v, int x, int y) {
	for (int i = 0; i < v.size(); i++) {
		v[i].x += x;
		v[i].y += y;
	}
}
