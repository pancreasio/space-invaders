#include "game-screen.h"

namespace game {
	namespace gameplayspace {

		Player p1;
		Shot p1s[maxFriendlyShots], eas[maxEnemyShots];
		Enemy ea[maxEnemies];


		void returnToMenu() {
			menuspace::initMenu();
			currentstate = menustate;		
		}

		void initGameplay() {
			//p1.texture = LoadTexture("res/shipsheet.png");
		}

		void updateGameplay() {
		
		}

		void drawGameplay() {
		
		}
	}
}