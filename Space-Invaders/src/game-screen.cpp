#include "game-screen.h"

namespace game {
	namespace gameplayspace {

		Player player1;
		Shot player1ShotArray[maxFriendlyShots], enemyArrayShotArray[maxEnemyShots];
		Enemy enemyArray[maxEnemies];
		Fortress fortressArray[maxFortresses];
		Texture playerTexture, swarmTexture, bomberTexture, fortressTexture, shotTexture, explosionTexture;
		unsigned int frameSpeed, currentFrame, frameCounter;
		bool aux = false;

		void returnToMenu() {
			menuspace::initMenu();
			currentstate = menustate;
		}

		void initGameplay() {
			playerTexture = LoadTexture("res/assets/shipsheet.png");
			swarmTexture = LoadTexture("res/assets/swarm.png");
			bomberTexture = LoadTexture("res/assets/bomber.png");
			fortressTexture = LoadTexture("res/assets/fortress.png");
			shotTexture = LoadTexture("res/assets/shot.png");
			explosionTexture = LoadTexture("res/assets/explosionsheet.png");
			for (int i = 0; i < maxEnemies; i++) {
				enemyArray[i].type = swarm;
				enemyArray[i].active = true;
			}
			//player settings
			player1.position = {static_cast<float>(GetScreenWidth()),static_cast<float>(GetScreenHeight())};
			player1.speed = 400.0f;

			//player animation settings
			player1.scale = 1.4;
			player1.sourceRec = {0.0f, 0.0f, static_cast<float>(playerTexture.width) / 2.0f ,static_cast<float>(playerTexture.height)};
			player1.destRec = {player1.position.x,player1.position.y, static_cast<float>(playerTexture.width) * player1.scale, static_cast<float>(playerTexture.height) * 2.0f * player1.scale};
			frameSpeed = 1.0f;
			frameCounter = 0;
			currentFrame = 0;

		}

		void updateGameplay() {

			//ship movement (and emergency exit button)
			if (IsKeyDown(KEY_LEFT)) {
				player1.position.x -= player1.speed * GetFrameTime();
			}
			if (IsKeyDown(KEY_RIGHT)) {
				player1.position.x += player1.speed * GetFrameTime();
			}
			if (IsKeyPressed(KEY_Q)) {
				returnToMenu();
			}

			//ship animation 
			frameCounter++;

			if (frameCounter >= (2.0 / frameSpeed))
			{
				frameCounter = 0;
				currentFrame++;

				if (currentFrame > 1) currentFrame = 0;

				player1.sourceRec.x = static_cast<float>(currentFrame)*static_cast<float>(playerTexture.width) / 2.0;
			}
			player1.destRec = { player1.position.x,player1.position.y,static_cast<float>(playerTexture.width) * player1.scale,static_cast<float>(playerTexture.height) * 2 * player1.scale };
		}

		void drawGameplay() {
			//DrawTexture(playerTexture,GetScreenWidth() /2, GetScreenHeight() /2, WHITE);

			if(!aux) DrawTexturePro(playerTexture, player1.sourceRec, player1.destRec, {static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f}, 0.0f, WHITE);
		}
	}
}