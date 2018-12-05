#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "raylib.h"

#include "flow-manager.h"

namespace game {
	namespace gameplayspace {
		void initGameplay();
		void updateGameplay();
		void drawGameplay();
	}
}
#endif
