#pragma once

#include "GameWindow.h"

class Game {
public:
	Game(GameWindow& wnd);
	void Go();
private:
	void UpdateModel();
	void ComposeFrame();
//	HRESULT CreateCube();
	/********************************/
	/*  User Functions              */
	/********************************/

private:
	GameWindow& wnd;
	Renderer renderer;
	/********************************/
	/*  User Variables              */
	/********************************/
};