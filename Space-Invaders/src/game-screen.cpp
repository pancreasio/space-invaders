#include "game-screen.h"

namespace game {
	namespace gameplayspace {

		const unsigned int maxFriendlyShots = 3;
		const unsigned int maxSnipers= 6;
		const unsigned int maxEnemyShots = 6;
		const unsigned int maxFortresses = 4;

		Player player1;
		Shot player1ShotArray[maxFriendlyShots],auxBullet;
		Sniper sniperArray[maxSnipers];
		EnemyShot sniperArrayShots[maxEnemyShots];
		Fortress fortressArray[maxFortresses];
		Texture playerTexture, swarmTexture, bomberTexture, fortressTexture, shotTexture, explosionTexture, background, sniperTexture, enemyShotTexture;
		Rectangle bulletAABB, sniperBulletAABB;
		unsigned int frameSpeed, currentFrame, frameCounter, bulletCounter;
		unsigned const int leftLimit = 30, rightLimit = 1224, timeToKill =1;
		int snipers;
		float bulletSpeed, sniperSpeed, sniperAcceleration, enemyShotSpeed;
		const float characterScale = 1.4f, bulletScale = 2.0f;
		bool fireSwitch, sniperFireSwitch[maxSnipers], sniperDirection;
		double sniperShotCooldown = 3.0;

		void returnToMenu() {
			menuspace::initMenu();
			currentstate = menustate;
		}

		void initGameplay() {
			playerTexture = LoadTexture("res/assets/shipsheet.png");
			swarmTexture = LoadTexture("res/assets/swarm.png");
			bomberTexture = LoadTexture("res/assets/bomber.png");
			sniperTexture = LoadTexture("res/assets/sniper.png");
			fortressTexture = LoadTexture("res/assets/fortress.png");
			shotTexture = LoadTexture("res/assets/shot.png");
			enemyShotTexture = LoadTexture("res/assets/enemyshot.png");
			explosionTexture = LoadTexture("res/assets/explosionsheet.png");
			background = LoadTexture("res/assets/background.png");
			
			//player settings
			player1.position = { static_cast<float>(GetScreenWidth()) / 2.0f,static_cast<float>(GetScreenHeight()) / 2.0f +260.0f };
			player1.speed = 400.0f;
			player1.AABB = {0.0f,0.0f,25.0f,64.0f};

			//player animation settings
			player1.scale = characterScale;
			player1.sourceRec = { 0.0f, 0.0f, static_cast<float>(playerTexture.width) / 2.0f ,static_cast<float>(playerTexture.height) };
			player1.destRec = { player1.position.x,player1.position.y, static_cast<float>(playerTexture.width) * player1.scale, static_cast<float>(playerTexture.height) * 2.0f * player1.scale };
			frameSpeed = 1;
			frameCounter = 0;
			currentFrame = 0;

			//bullet settings
			bulletAABB = {0.0f,0.0f,15.0f,32.0f};
			fireSwitch = false;
			bulletCounter = 0;
			bulletSpeed = 700.0f;

			//enemy settings
			sniperSpeed = 80.0f;
			sniperAcceleration = 0.013f;
			sniperDirection = true;
			snipers = 0;
			enemyShotSpeed = 400.0f;
			sniperBulletAABB = {0.0f,0.0f,10.0f,32.0f};


			//enemy initialization
			//snipers
			for (int i = 0; i < maxSnipers; i++) {
				sniperArray[i].active = true;
				sniperArray[i].position.y = 30.0f;
				sniperArray[i].position.x = 50.0f + static_cast<float>(i)* static_cast<float>(GetScreenWidth()) / static_cast<float>(maxSnipers);
				sniperArray[i].AABB = {sniperArray[i].position.x ,sniperArray[i].position.y, 58.0f,63.0f};
				sniperArray[i].timeShot = GetTime() + 1.0f * static_cast<float>(i);
				snipers++;
			}

		}

		void updateGameplay() {

			//ship movement (and emergency exit button)
			if (IsKeyDown(KEY_LEFT)) {
				if (player1.position.x > leftLimit) {
					player1.position.x -= player1.speed * GetFrameTime();
				}
			}
			if (IsKeyDown(KEY_RIGHT)) {
				if (player1.position.x < rightLimit) {
					player1.position.x += player1.speed * GetFrameTime();
				}
			}
			if (IsKeyPressed(KEY_Q)) {
				returnToMenu();
			}

			//firing logic
			if (IsKeyPressed(KEY_SPACE)) {
				fireSwitch = false;
				for (bulletCounter = 0; bulletCounter < maxFriendlyShots; bulletCounter++) {
					if (!player1ShotArray[bulletCounter].active) {
						player1ShotArray[bulletCounter].position.x = player1.position.x + static_cast<float>(playerTexture.width) /2.0f - 27.0f;
						player1ShotArray[bulletCounter].position.y = player1.position.y +8.0f;
						player1ShotArray[bulletCounter].active = true;
						player1ShotArray[bulletCounter].birthDate = GetTime();
						player1ShotArray[bulletCounter].AABB = bulletAABB;
						player1ShotArray[bulletCounter].AABB.x = player1ShotArray[bulletCounter].position.x;
						player1ShotArray[bulletCounter].AABB.y = player1ShotArray[bulletCounter].position.y;
						bulletCounter = maxFriendlyShots;
						fireSwitch = true;
					}

					if (!fireSwitch) {
						if (bulletCounter == maxFriendlyShots) {
							for (int i = 0; i < maxFriendlyShots - 1; i++)
							{
								auxBullet = player1ShotArray[i + 1];
								player1ShotArray[i + 1] = player1ShotArray[i];
							}
							player1ShotArray[0].position = player1.position;
							player1ShotArray[0].active = true;
							player1ShotArray[0].birthDate = GetTime();
							player1ShotArray[0].AABB = bulletAABB;
							fireSwitch = true;
						}
					}
				}
			}

			for (int i = 0; i < maxFriendlyShots; i++) {
				if (player1ShotArray[i].active) {
					player1ShotArray[i].position.y -= bulletSpeed * GetFrameTime();
					player1ShotArray[i].AABB.y = player1ShotArray[i].position.y;
					if (GetTime() - player1ShotArray[i].birthDate > timeToKill) {
						player1ShotArray[i].active = false;
					}
				}
			}

			//sniper movement logic

			for (int i = 0; i < maxSnipers; i++)
			{
				if (sniperArray[i].active) {
					if (sniperDirection) {
						sniperArray[i].position.x += sniperSpeed * GetFrameTime() + sniperAcceleration * (static_cast<float>(maxSnipers) - static_cast<float>(snipers));
					}
					else {
						sniperArray[i].position.x -= sniperSpeed * GetFrameTime() + sniperAcceleration * (static_cast<float>(maxSnipers) - static_cast<float>(snipers));
					}
					if (sniperArray[i].position.x <leftLimit) {
						sniperDirection = true;
					}
					if (sniperArray[i].position.x > rightLimit) {
						sniperDirection = false;
					}
					sniperArray[i].AABB.x = sniperArray[i].position.x;
					sniperArray[i].AABB.y = sniperArray[i].position.y;
				}
				
			}

			//sniper firing logic
			for (int i = 0; i < maxSnipers; i++){
				if (sniperArray[i].active) {
					if (GetTime() - sniperArray[i].timeShot > sniperShotCooldown) {
						sniperArrayShots[i].active = true;
						sniperArrayShots[i].position.x = sniperArray[i].position.x + 30.0f;
						sniperArrayShots[i].position.y = sniperArray[i].position.y + 30.0f;
						sniperArrayShots[i].AABB = sniperBulletAABB;
						sniperArrayShots[i].AABB.x = sniperArrayShots[i].position.x;
						sniperArrayShots[i].AABB.y = sniperArrayShots[i].position.y;
						sniperArray[i].timeShot = GetTime();
					}
				}
			}
			
			for (int i = 0; i < maxEnemyShots; i++){
				if (sniperArrayShots[i].active) {
					sniperArrayShots[i].position.y += enemyShotSpeed * GetFrameTime();
					sniperArrayShots[i].AABB.x = sniperArrayShots[i].position.x +4.0f;
					sniperArrayShots[i].AABB.y = sniperArrayShots[i].position.y;
					if (sniperArrayShots[i].position.y > static_cast<float>(GetScreenHeight())) {
						sniperArrayShots[i].active = false;
					}
				}
			}

			//collisions
			//friendly bullet->snipers
			for (int i = 0; i < maxFriendlyShots; i++){
				if (player1ShotArray[i].active) {
					for (int i2 = 0; i2 < maxSnipers; i2++){
						if (sniperArray[i2].active) {
							if (CheckCollisionRecs(player1ShotArray[i].AABB, sniperArray[i2].AABB)) {
								sniperArray[i2].active = false;
								player1ShotArray[i].active = false;
								snipers--;
							}
						}
					}
				}
			}

			//friendly bullets->sniper bullets
			for (int i = 0; i < maxFriendlyShots; i++) {
				if (player1ShotArray[i].active) {
					for (int i2 = 0; i2 < maxEnemyShots; i2++) {
						if (sniperArrayShots[i2].active) {
							if (CheckCollisionRecs(player1ShotArray[i].AABB, sniperArrayShots[i2].AABB)) {
								sniperArrayShots[i2].active = false;
								player1ShotArray[i].active = false;
							}
						}
					}
				}
			}

			//sniper bullets->player
			for (int i = 0; i < maxEnemyShots; i++){
				if (sniperArrayShots[i].active) {
					if (CheckCollisionRecs(sniperArrayShots[i].AABB, player1.AABB)) {
						returnToMenu();
					}
				}
			}

			//win logic
			if (snipers <= 0) {
				returnToMenu();
			}
			//lose logic

			//ship animation 
			frameCounter++;

			if (frameCounter >= (2.0 / frameSpeed)){ 
				frameCounter = 0;
				currentFrame++;

				if (currentFrame > 1) {
					currentFrame = 0;
				}
				player1.sourceRec.x = static_cast<float>(currentFrame)*static_cast<float>(playerTexture.width) / 2.0f;
			}
			player1.destRec = { player1.position.x,player1.position.y,static_cast<float>(playerTexture.width) * player1.scale,static_cast<float>(playerTexture.height) * 2 * player1.scale };
			player1.AABB.x = player1.position.x;
			player1.AABB.y = player1.position.y;
		}

		void drawGameplay() {
			//background
			DrawTextureEx(background, { 0.0f,0.0f }, 0.0f, 8.0f, WHITE);

			//player 
			DrawTexturePro(playerTexture, player1.sourceRec, player1.destRec, {static_cast<float>(playerTexture.width) / 2.0f, static_cast<float>(playerTexture.height) / 2.0f }, 0.0f, WHITE);

			//bullets
			for (int i = 0; i < maxFriendlyShots; i++) {
				if (player1ShotArray[i].active) {
					DrawTextureEx(shotTexture, player1ShotArray[i].position, 0.0f, bulletScale, WHITE);					
				}
			}

			//snipers
			for (int i = 0; i < maxSnipers; i++){
				if (sniperArray[i].active) {
					DrawTextureEx(sniperTexture, sniperArray[i].position, 0.0f,characterScale*1.3f, WHITE);
				}
			}
			for (int i = 0; i < maxSnipers; i++) {
				if (sniperArrayShots[i].active) {
					DrawTextureEx(enemyShotTexture, sniperArrayShots[i].position, 0.0f, bulletScale, WHITE);
				}
			}

			//sniper bullets

			//swarm

			//bombers
		}
	}
}