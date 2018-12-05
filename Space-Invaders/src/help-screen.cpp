#include "help-screen.h"

namespace game {
	namespace helpspace {

		button back;

		void backToMenu() {
			menuspace::initMenu();
			currentstate = menustate;
		}

		void initHelp() {
			back.position.x = GetScreenWidth() / 2.0f - 110.0f;
			back.position.y = GetScreenHeight() / 2.0f + 210.0f;
			back.size.x = 220.0f;
			back.size.y = 60.0f;
		}

		void updateHelp() {
			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };
			
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (back.position.x <= mousePosition.x && mousePosition.x <= back.position.x + back.size.x) {
					if (back.position.y <= mousePosition.y && mousePosition.y <= back.position.y + back.size.y) {
						backToMenu();
					}
				}
			}
		}

		void drawHelp() {
			DrawRectangle(back.position.x, back.position.y, back.size.x, back.size.y, WHITE);
			DrawText("BACK", back.position.x + 32, back.position.y + 10, 45, BLACK);
		}
	}
}