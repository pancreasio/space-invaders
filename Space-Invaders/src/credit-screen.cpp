#include "credit-screen.h"

namespace game {
	namespace creditsspace {
		button back;
		const unsigned int auxAllignment0 = 300, auxAllignment1 = 200, titleFontSize = 50, creditFontSize = 45, versionFontSize = 20;
		void goToMenu() {
			menuspace::initMenu();
			currentstate = menustate;
		}
		void initCredits() {
			back.position.x = GetScreenWidth() / 2.0f - 110.0f;
			back.position.y = GetScreenHeight() / 2.0f + 100.0f;
			back.size.x = 220.0f;
			back.size.y = 60.0;
		}
		void updateCredits() {

			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (back.position.x <= mousePosition.x && mousePosition.x <= back.position.x + back.size.x) {
					if (back.position.y <= mousePosition.y && mousePosition.y <= back.position.y + back.size.y) {
						goToMenu();
					}
				}
			}

		}
		void drawCredits() {
			DrawText("Game by Julian Serulnikov", GetScreenWidth() / 2 - auxAllignment0, GetScreenHeight() / 2 - auxAllignment1, 50, WHITE);
			DrawText("Made with Raylib", GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 130, 50, WHITE);
			DrawRectangle(static_cast<int>(back.position.x), static_cast<int>(back.position.y), static_cast<int>(back.size.x), static_cast<int>(back.size.y), WHITE);
			DrawText("BACK", static_cast<int>(back.position.x) + 32, static_cast<int>(back.position.y) + 10, 45, BLACK);
			DrawText(FormatText("v%0i.%1i",version, subVersion), GetScreenWidth() - 150, GetScreenHeight() - 20, 20, GRAY);
		}		
	}
}