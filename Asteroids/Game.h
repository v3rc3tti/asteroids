#pragma once

#include "Model.h"

class Game
{
public:
	bool g_keys[256];
	std::vector<Model*> NextFrameModels;

	Game(PixelWindow *window);
	void start();
private:
	std::vector<Model*> models;
	PixelWindow* pWindow;

	void ResetGame();
	static bool isDead(Model* model);
	void ResolveCollisions(std::vector<Model*>& models);
	bool isPointInside(Vec2 p1, float r, Vec2 p2);
	bool procSysMsg();
	void AsterMetBullet(Model* aster, Model* bullet);
	void procKeyMessage(MSG msg);
};

extern Game* g_pGame;