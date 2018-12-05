#ifndef FLOW_MANAGER_H
#define FLOW_MANAGER_H

#include "raylib.h"

#include "menu-screen.h"
#include "help-screen.h"
#include "game-screen.h"
#include "credit-screen.h"
#include "gameover-screen.h"

namespace game {
	enum gamestate {
		menustate, gameplaystate, gameoverstate, creditsstate,helpstate,
	};
	extern bool gameSwitch;
	extern gamestate currentstate;
	extern const float version;
	void initGame();
	void generalDraw();
	void gameLoop();
	void exitGame();
}
#endif
