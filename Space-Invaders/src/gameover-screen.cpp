#include "gameover-screen.h"

namespace game {
	namespace gameoverspace {

		button retry;
		button menu;

		void retryGame() {
			gameplayspace::initGameplay();
			currentstate = gameplaystate;
		}

		void goToMenu() {
			menuspace::initMenu();
			currentstate = menustate;
		}

		void initGameOver() {
			retry.position.x = GetScreenWidth() / 2.0f - 110.0f;
			retry.position.y = GetScreenHeight() / 2.0f;
			retry.size.x = 220.0f;
			retry.size.y = 60.0f;
			menu.position.x = GetScreenWidth() / 2.0f - 110.0f;
			menu.position.y = GetScreenHeight() / 2.0f + 70.0f;
			menu.size.x = 220.0f;
			menu.size.y = 60.0f;
		}

		void updateGameOver() {
			if (gameplayspace::won) {
				DrawText("You Won!", GetScreenWidth() / 2 - 110, GetScreenHeight() / 2 -100 , 50, WHITE);
			}
			else {
				DrawText("You Lost!", GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 -100, 50, WHITE);
			}
			mousePosition = GetMousePosition();
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (retry.position.x <= mousePosition.x && mousePosition.x <= retry.position.x + retry.size.x) {
					if (retry.position.y <= mousePosition.y && mousePosition.y <= retry.position.y + retry.size.y) {
						retryGame();
					}
				}
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (menu.position.x <= mousePosition.x && mousePosition.x <= menu.position.x + menu.size.x) {
					if (menu.position.y <= mousePosition.y && mousePosition.y <= menu.position.y + menu.size.y) {
						goToMenu();
					}
				}
			}
		}

		void drawGameOver() {
			DrawRectangle(static_cast<int>(retry.position.x), static_cast<int>(retry.position.y), static_cast<int>(retry.size.x), static_cast<int>(retry.size.y), WHITE);
			DrawText("RETRY", static_cast<int>(retry.position.x) + 32, static_cast<int>(retry.position.y) + 10, 45, BLACK);
			DrawRectangle(static_cast<int>(menu.position.x), static_cast<int>(menu.position.y), static_cast<int>(menu.size.x), static_cast<int>(menu.size.y), WHITE);
			DrawText("MENU", static_cast<int>(menu.position.x) + 49, static_cast<int>(menu.position.y) + 10, 45, BLACK);
		}
	}
}