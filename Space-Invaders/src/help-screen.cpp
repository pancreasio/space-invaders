#include "help-screen.h"

namespace game {
	namespace helpspace {

		button back;
		Texture playerTexture, swarmTexture, sniperTexture, fortressTexture, bomberTexture;

		void backToMenu() {
			UnloadTexture(playerTexture);
			UnloadTexture(swarmTexture);
			UnloadTexture(sniperTexture);
			UnloadTexture(bomberTexture);
			UnloadTexture(fortressTexture);
			menuspace::initMenu();
			currentstate = menustate;
		}

		void initHelp() {
			playerTexture = LoadTexture("res/assets/shipsheet.png");
			swarmTexture = LoadTexture("res/assets/swarm.png");
			bomberTexture = LoadTexture("res/assets/bomber.png");
			sniperTexture = LoadTexture("res/assets/sniper.png");
			fortressTexture = LoadTexture("res/assets/fortress.png");
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
			DrawTexturePro(playerTexture, { 0.0f, 0.0f, static_cast<float>(playerTexture.width) / 2.0f, static_cast<float>(playerTexture.height) }, { 40.0f,90.0f ,150.0f,150.0f }, { 0.0f,0.0f }, 0.0f, WHITE);
			DrawTextureEx(fortressTexture, {40.0f, 330.0f}, 0.0f, 4.0f, WHITE);
			DrawTextureEx(swarmTexture, {600.0f,90.0f}, 0.0f, 4.0f, WHITE);
			DrawTextureEx(sniperTexture, {600.0f, 330.0f}, 0.0f, 4.0f, WHITE);
			DrawText("dodge everything!", 190, 80, 25, WHITE);
			DrawText("one hit means death", 190, 110, 25, WHITE);
			DrawText("move with the arrow keys, fire with spacebar",70,258,25, WHITE);
			DrawText("get behind the armored turrets!", 70, 460, 25, WHITE);
			DrawText("be careful, they take damage", 70, 495, 25, WHITE);
			DrawText("destroy all the enemies!", 820, 50, 25, WHITE);
			DrawText("the swarm moves quickly and deals", 800, 120, 25, WHITE);
			DrawText("massive damage to turrets", 800, 170, 25, WHITE);
			DrawText("snipers harass you from afar", 800, 400, 25, WHITE);
			DrawText("destroy them or handle the pressure", 800, 430, 25, WHITE);
			DrawRectangle(static_cast<int>(back.position.x), static_cast<int>(back.position.y), static_cast<int>(back.size.x), static_cast<int>(back.size.y), WHITE);
			DrawText("BACK", static_cast<int>(back.position.x) + 32, static_cast<int>(back.position.y) + 10, 45, BLACK);
		}
	}
}