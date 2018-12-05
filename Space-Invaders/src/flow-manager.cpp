#include "flow-manager.h"
namespace game {
	gamestate currentstate;
	bool gameSwitch;
	const unsigned int screenheight = 600;
	const unsigned int screenwidth = 800;
	const float version = 0.0f;
	Vector2 mousePosition;
	void initGame() {
		gameSwitch = true;
		InitWindow(screenwidth, screenheight, "Invaders from Space");
		menuspace::initMenu();
		SetExitKey(0);
		InitAudioDevice();
		currentstate = menustate;
		gameLoop();
	}
	void gameLoop() {
		while (gameSwitch && !WindowShouldClose()) {
			switch (currentstate) {
			case menustate:
				menuspace::updateMenu();
				generalDraw();
				break;
			case gameplaystate:
				gameplayspace::updateGameplay();
				generalDraw();
				break;
			case creditsstate:
				creditsspace::updateCredits();
				generalDraw();
				break;
			case gameoverstate:
				gameoverspace::updateGameOver();
				generalDraw();
				break;
			case helpstate:
				helpspace::updateHelp();
				generalDraw();
				break;
			}
		}
	}
	void generalDraw() {
		BeginDrawing();
		ClearBackground(BLACK);
		switch (currentstate)
		{
		case menustate:
			menuspace::drawMenu();
			break;
		case gameplaystate:
			gameplayspace::drawGameplay();
			break;
		case creditsstate:
			creditsspace::drawCredits();
			break;
		case gameoverstate:
			gameoverspace::drawGameOver();
			break;
		}

		EndDrawing();
	}
	void exitGame() {
		gameSwitch = !gameSwitch;
	}
}