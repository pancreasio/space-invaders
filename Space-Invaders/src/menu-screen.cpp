#include "menu-screen.h"

namespace game {
	namespace menuspace {
		button start;
		button quit;
		button credits;

		void startGame() {
			gameplayspace::initGameplay();
			currentstate = gameplaystate;
		}

		void viewCredits() {
			creditsspace::initCredits();
			currentstate = creditsstate;
		}

		void initMenu() {
			start.position.x = GetScreenWidth() / 2.0f - 110.0f;
			start.position.y = GetScreenHeight() / 2.0f;
			start.size.x = 220.0f;
			start.size.y = 60.0f;
			credits.position.x = GetScreenWidth() / 2.0f - 110.0f;
			credits.position.y = GetScreenHeight() / 2.0f + 70.0f;
			credits.size.x = 220.0f;
			credits.size.y = 60.0f;
			quit.position.x = GetScreenWidth() / 2.0f - 110.0f;
			quit.position.y = GetScreenHeight() / 2.0f + 140.0f;
			quit.size.x = 220.0f;
			quit.size.y = 60.0f;
		}

		void updateMenu() {

			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };


			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (start.position.x <= mousePosition.x && mousePosition.x <= start.position.x + start.size.x) {
					if (start.position.y <= mousePosition.y && mousePosition.y <= start.position.y + start.size.y) {
						startGame();
					}
				}
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (credits.position.x <= mousePosition.x && mousePosition.x <= credits.position.x + credits.size.x) {
					if (credits.position.y <= mousePosition.y && mousePosition.y <= credits.position.y + credits.size.y) {
						viewCredits();
					}
				}
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (quit.position.x <= mousePosition.x && mousePosition.x <= quit.position.x + quit.size.x) {
					if (quit.position.y <= mousePosition.y && mousePosition.y <= quit.position.y + quit.size.y) {
						exitGame();
					}
				}
			}
		}
		void drawMenu() {
			DrawText("ASTEROIDS", GetScreenWidth() / 2 - 180, GetScreenHeight() / 2 - 90, 60, WHITE);
			DrawRectangle(start.position.x, start.position.y, start.size.x, start.size.y, WHITE);
			DrawText("START", start.position.x + 32, start.position.y + 10, 45, BLACK);
			DrawRectangle(credits.position.x, credits.position.y, credits.size.x, credits.size.y, WHITE);
			DrawText("CREDITS", credits.position.x + 10, credits.position.y + 10, 45, BLACK);
			DrawRectangle(quit.position.x, quit.position.y, quit.size.x, quit.size.y, WHITE);
			DrawText("QUIT", quit.position.x + 55, quit.position.y + 10, 45, BLACK);
			DrawText(FormatText("v%0i.%1i", version, subVersion), GetScreenWidth() - 150, GetScreenHeight() - 20, 20, GRAY);
		}
	
		
		void exitGame() {
			gameSwitch = false;
		}
	}
}