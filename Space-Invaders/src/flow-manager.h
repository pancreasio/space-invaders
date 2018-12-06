#ifndef FLOW_MANAGER_H
#define FLOW_MANAGER_H

#include <iostream>

#include "raylib.h"

#include "menu-screen.h"
#include "help-screen.h"
#include "game-screen.h"
#include "credit-screen.h"
#include "gameover-screen.h"

namespace game {
	enum gamestate {
		menustate, gameplaystate, gameoverstate, creditsstate, helpstate,
	};
	struct button {
		Vector2 position;
		Vector2 size;
		std::string text;
	};
	extern bool gameSwitch, mute;
	extern gamestate currentstate;
	extern const unsigned int version, subVersion;
	extern Vector2 mousePosition;
	void initGame();
	void exitGame();
}
#endif
