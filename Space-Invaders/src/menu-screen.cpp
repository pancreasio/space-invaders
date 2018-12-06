#include "menu-screen.h"

namespace game {
	namespace menuspace {
		button start;
		button help;
		button quit;
		button credits;

		void startGame() {
			gameplayspace::initGameplay();
			currentstate = gameplaystate;
		}

		void goToHelp() {
			helpspace::initHelp();
			currentstate = helpstate;
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
			help.position.x = GetScreenWidth() / 2.0f - 110.0f;
			help.position.y = GetScreenHeight() / 2.0f + 70.0f;
			help.size.x = 220.0f;
			help.size.y = 60.0f;
			credits.position.x = GetScreenWidth() / 2.0f - 110.0f;
			credits.position.y = GetScreenHeight() / 2.0f + 140.0f;
			credits.size.x = 220.0f;
			credits.size.y = 60.0f;
			quit.position.x = GetScreenWidth() / 2.0f - 110.0f;
			quit.position.y = GetScreenHeight() / 2.0f + 210.0f;
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
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (help.position.x <= mousePosition.x && mousePosition.x <= help.position.x + help.size.x) {
					if (help.position.y <= mousePosition.y && mousePosition.y <= help.position.y + help.size.y) {
						goToHelp();
					}
				}
			}
		}
		void drawMenu() {
			DrawText("Invaders from Space", GetScreenWidth() / 2 - 320, GetScreenHeight() / 2 - 90, 60, WHITE);
			DrawRectangle(static_cast<int>(start.position.x), static_cast<int>(start.position.y), static_cast<int>(start.size.x), static_cast<int>(start.size.y), WHITE);
			DrawText("START", static_cast<int>(start.position.x) + 32, static_cast<int>(start.position.y) + 10, 45, BLACK);
			DrawRectangle(static_cast<int>(help.position.x), static_cast<int>(help.position.y), static_cast<int>(help.size.x), static_cast<int>(help.size.y), WHITE);
			DrawText("HELP", static_cast<int>(help.position.x) + 49, static_cast<int>(help.position.y) + 10, 45, BLACK);
			DrawRectangle(static_cast<int>(credits.position.x), static_cast<int>(credits.position.y), static_cast<int>(credits.size.x), static_cast<int>(credits.size.y), WHITE);
			DrawText("CREDITS", static_cast<int>(credits.position.x) + 10, static_cast<int>(credits.position.y) + 10, 45, BLACK);
			DrawRectangle(static_cast<int>(quit.position.x), static_cast<int>(quit.position.y), static_cast<int>(quit.size.x), static_cast<int>(quit.size.y), WHITE);
			DrawText("QUIT", static_cast<int>(quit.position.x) + 55, static_cast<int>(quit.position.y) + 10, 45, BLACK);
			DrawText(FormatText("v%0i.%1i", version, subVersion), GetScreenWidth() - 150, GetScreenHeight() - 20, 20, GRAY);
		}
	
		
		void exitGame() {
			gameSwitch = false;
		}
	}
}