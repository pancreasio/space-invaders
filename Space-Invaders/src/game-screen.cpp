#include "game-screen.h"

namespace game {
	namespace gameplayspace {

		const unsigned int maxFriendlyShots = 3;
		const unsigned int maxSnipers = 6;
		const unsigned int maxSwarmPerRow = 5;
		const unsigned int maxSwarmRows = 3;
		const unsigned int maxEnemyShots = 6;
		const unsigned int maxFortresses = 4;

		button exitButton;
		Player player1;
		Shot player1ShotArray[maxFriendlyShots], auxBullet;
		Sniper sniperArray[maxSnipers];
		Swarm swarmRow0Array[maxSwarmPerRow];
		Swarm swarmRow1Array[maxSwarmPerRow];
		Swarm swarmRow2Array[maxSwarmPerRow];
		EnemyShot sniperArrayShots[maxEnemyShots];
		Fortress fortressArray[maxFortresses];
		Texture playerTexture, swarmTexture, bomberTexture, fortressTexture, shotTexture, explosionTexture, background, sniperTexture, enemyShotTexture;
		Rectangle bulletAABB, sniperBulletAABB, fortressAABB, swarmAABB;
		unsigned int frameSpeed, currentFrame, frameCounter, bulletCounter;
		unsigned const int leftLimit = 30, rightLimit = 1224, timeToKill = 1;
		int snipers, swarmIn0, swarmIn1, swarmIn2, enemies;
		float bulletSpeed, sniperSpeed, sniperAcceleration, enemyShotSpeed, swarmSpeed, swarmAcceleration;
		const float characterScale = 1.4f, bulletScale = 2.0f;
		bool fireSwitch, sniperFireSwitch[maxSnipers], sniperDirection, row0Direction, row1Direction, row2Direction, won, isPaused;
		double sniperShotCooldown = 3.0;

		void returnToMenu() {
			UnloadTexture(playerTexture);
			UnloadTexture(swarmTexture);
			UnloadTexture(sniperTexture);
			UnloadTexture(bomberTexture);
			UnloadTexture(fortressTexture);
			UnloadTexture(shotTexture);
			UnloadTexture(enemyShotTexture);
			UnloadTexture(explosionTexture);
			UnloadTexture(background);
			menuspace::initMenu();
			currentstate = menustate;
		}

		void gameOver() {
			UnloadTexture(playerTexture);
			UnloadTexture(swarmTexture);
			UnloadTexture(sniperTexture);
			UnloadTexture(bomberTexture);
			UnloadTexture(fortressTexture);
			UnloadTexture(shotTexture);
			UnloadTexture(enemyShotTexture);
			UnloadTexture(explosionTexture);
			UnloadTexture(background);
			menuspace::initMenu();
			gameoverspace::initGameOver();
			currentstate = gameoverstate;
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

			exitButton.position.x = static_cast<float>(GetScreenWidth()) / 2.0f - 120.0f;
			exitButton.position.y = static_cast<float>(GetScreenHeight()) / 2.0f + 60.0f;
			exitButton.size.x = 240;
			exitButton.size.y = 60.0;

			//player settings
			player1.position = { static_cast<float>(GetScreenWidth()) / 2.0f,static_cast<float>(GetScreenHeight()) / 2.0f + 260.0f };
			player1.speed = 400.0f;
			player1.AABB = { 0.0f,0.0f,25.0f,64.0f };
			won = false;
			isPaused = false;

			//player animation settings
			player1.scale = characterScale;
			player1.sourceRec = { 0.0f, 0.0f, static_cast<float>(playerTexture.width) / 2.0f ,static_cast<float>(playerTexture.height) };
			player1.destRec = { player1.position.x,player1.position.y, static_cast<float>(playerTexture.width) * player1.scale, static_cast<float>(playerTexture.height) * 2.0f * player1.scale };
			frameSpeed = 1;
			frameCounter = 0;
			currentFrame = 0;

			//bullet settings
			bulletAABB = { 0.0f,0.0f,15.0f,32.0f };
			fireSwitch = false;
			bulletCounter = 0;
			bulletSpeed = 700.0f;

			//fortress settings
			fortressAABB = { 0.0f,0.0f,92.0f,40.0f };

			//enemy settings
			enemies = 0;
			//snipers
			sniperSpeed = 80.0f;
			sniperAcceleration = 0.013f;
			sniperDirection = true;
			snipers = 0;
			enemyShotSpeed = 400.0f;
			sniperBulletAABB = { 0.0f,0.0f,10.0f,32.0f };
			//swarm
			swarmSpeed = 50.0f;
			swarmAcceleration = 0.02f;
			swarmIn0 = 0;
			swarmIn1 = 0;
			swarmIn2 = 0;
			swarmAABB = { 0.0f,0.0f,45.0f,45.0f };
			row0Direction = true;
			row1Direction = false;
			row2Direction = true;

			//bullet initialization
			for (int i = 0; i < maxFriendlyShots; i++) {
				player1ShotArray[i].active = 0;
			}

			//fortress initialization
			for (int i = 0; i < maxFortresses; i++) {
				fortressArray[i].active = true;
				fortressArray[i].position = { 105.0f + static_cast<float>(i) * static_cast<float>(GetScreenWidth()) / static_cast<float>(maxFortresses), static_cast<float>(GetScreenHeight()) - 228.0f };
				fortressArray[i].HP = 4;
				fortressArray[i].AABB = fortressAABB;
				fortressArray[i].AABB.x = fortressArray[i].position.x + 5.0f;
				fortressArray[i].AABB.y = fortressArray[i].position.y + 40.0f;
			}

			//enemy initialization
			//snipers
			for (int i = 0; i < maxSnipers; i++) {
				sniperArray[i].active = true;
				sniperArray[i].position.y = 30.0f;
				sniperArray[i].position.x = 50.0f + static_cast<float>(i)* static_cast<float>(GetScreenWidth()) / static_cast<float>(maxSnipers);
				sniperArray[i].AABB = { sniperArray[i].position.x ,sniperArray[i].position.y, 58.0f,63.0f };
				sniperArray[i].timeShot = GetTime() + 1.0f * static_cast<float>(i);
				snipers++;
				enemies++;
			}
			//sniper bullets
			for (int i = 0; i < maxEnemyShots; i++) {
				sniperArrayShots[i].active = 0;
			}


			//swarm
			for (int i = 0; i < maxSwarmPerRow; i++) {
				//row 0
				swarmRow0Array[i].active = true;
				swarmRow0Array[i].position.y = 110.0f;
				swarmRow0Array[i].position.x = 100.0f + static_cast<float>(i)* static_cast<float>(GetScreenWidth()) / static_cast<float>(maxSwarmPerRow);
				swarmRow0Array[i].AABB = swarmAABB;
				swarmRow0Array[i].AABB.x = swarmRow0Array[i].position.x;
				swarmRow0Array[i].AABB.y = swarmRow0Array[i].position.y;
				swarmIn0++;
				enemies++;
				//row 1
				swarmRow1Array[i].active = true;
				swarmRow1Array[i].position.y = 170.0f;
				swarmRow1Array[i].position.x = 100.0f + static_cast<float>(i)* static_cast<float>(GetScreenWidth()) / static_cast<float>(maxSwarmPerRow);
				swarmRow1Array[i].AABB = swarmAABB;
				swarmRow1Array[i].AABB.x = swarmRow1Array[i].position.x;
				swarmRow1Array[i].AABB.y = swarmRow1Array[i].position.y;
				swarmIn1++;
				enemies++;
				//row 2
				swarmRow2Array[i].active = true;
				swarmRow2Array[i].position.y = 230.0f;
				swarmRow2Array[i].position.x = 100.0f + static_cast<float>(i)* static_cast<float>(GetScreenWidth()) / static_cast<float>(maxSwarmPerRow);
				swarmRow2Array[i].AABB = swarmAABB;
				swarmRow2Array[i].AABB.x = swarmRow2Array[i].position.x;
				swarmRow2Array[i].AABB.y = swarmRow2Array[i].position.y;
				swarmIn2++;
				enemies++;
			}
		}

		void updateGameplay() {
			mousePosition = GetMousePosition();
			if (IsKeyPressed(KEY_ENTER)) {
				isPaused = !isPaused;
			}
			if (!isPaused) {
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
							player1ShotArray[bulletCounter].position.x = player1.position.x + static_cast<float>(playerTexture.width) / 2.0f - 27.0f;
							player1ShotArray[bulletCounter].position.y = player1.position.y + 8.0f;
							player1ShotArray[bulletCounter].active = true;
							player1ShotArray[bulletCounter].hitFortress = false;
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
								player1ShotArray[0].hitFortress = false;
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
							player1ShotArray[i].hitFortress = false;
						}
					}
				}

				//swarm movement logic
				for (int i = 0; i < maxSwarmPerRow; i++)
				{
					//row 0
					if (swarmRow0Array[i].active) {
						if (row0Direction) {
							swarmRow0Array[i].position.x += swarmSpeed * GetFrameTime() + swarmAcceleration * (static_cast<float>(maxSwarmPerRow) - static_cast<float>(swarmIn0));
						}
						else {
							swarmRow0Array[i].position.x -= swarmSpeed * GetFrameTime() + swarmAcceleration * (static_cast<float>(maxSwarmPerRow) - static_cast<float>(swarmIn0));
						}
						if (swarmRow0Array[i].position.x < leftLimit) {
							row0Direction = true;
							for (int i = 0; i < maxSwarmPerRow; i++) {
								if (swarmRow0Array[i].active) {
									swarmRow0Array[i].position.y += 40.0f;
								}
							}
						}
						if (swarmRow0Array[i].position.x > rightLimit) {
							row0Direction = false;
							for (int i = 0; i < maxSwarmPerRow; i++) {
								if (swarmRow0Array[i].active) {
									swarmRow0Array[i].position.y += 40.0f;
								}
							}
						}
						swarmRow0Array[i].AABB.x = swarmRow0Array[i].position.x;
						swarmRow0Array[i].AABB.y = swarmRow0Array[i].position.y;
					}

					//row 1
					if (swarmRow1Array[i].active) {
						if (row1Direction) {
							swarmRow1Array[i].position.x += swarmSpeed * GetFrameTime() + swarmAcceleration * (static_cast<float>(maxSwarmPerRow) - static_cast<float>(swarmIn1));
						}
						else {
							swarmRow1Array[i].position.x -= swarmSpeed * GetFrameTime() + swarmAcceleration * (static_cast<float>(maxSwarmPerRow) - static_cast<float>(swarmIn1));
						}
						if (swarmRow1Array[i].position.x < leftLimit) {
							row1Direction = true;
							for (int i = 0; i < maxSwarmPerRow; i++) {
								if (swarmRow1Array[i].active) {
									swarmRow1Array[i].position.y += 40.0f;
								}
							}
						}
						if (swarmRow1Array[i].position.x > rightLimit) {
							row1Direction = false;
							for (int i = 0; i < maxSwarmPerRow; i++) {
								if (swarmRow1Array[i].active) {
									swarmRow1Array[i].position.y += 40.0f;
								}
							}
						}
						swarmRow1Array[i].AABB.x = swarmRow1Array[i].position.x;
						swarmRow1Array[i].AABB.y = swarmRow1Array[i].position.y;
					}

					//row 2
					if (swarmRow2Array[i].active) {
						if (row2Direction) {
							swarmRow2Array[i].position.x += swarmSpeed * GetFrameTime() + swarmAcceleration * (static_cast<float>(maxSwarmPerRow) - static_cast<float>(swarmIn2));
						}
						else {
							swarmRow2Array[i].position.x -= swarmSpeed * GetFrameTime() + swarmAcceleration * (static_cast<float>(maxSwarmPerRow) - static_cast<float>(swarmIn2));
						}
						if (swarmRow2Array[i].position.x < leftLimit) {
							row2Direction = true;
							for (int i = 0; i < maxSwarmPerRow; i++) {
								if (swarmRow2Array[i].active) {
									swarmRow2Array[i].position.y += 40.0f;
								}
							}
						}
						if (swarmRow2Array[i].position.x > rightLimit) {
							row2Direction = false;
							for (int i = 0; i < maxSwarmPerRow; i++) {
								if (swarmRow2Array[i].active) {
									swarmRow2Array[i].position.y += 40.0f;
								}
							}
						}
						swarmRow2Array[i].AABB.x = swarmRow2Array[i].position.x;
						swarmRow2Array[i].AABB.y = swarmRow2Array[i].position.y;
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
						if (sniperArray[i].position.x < leftLimit) {
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
				for (int i = 0; i < maxSnipers; i++) {
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

				for (int i = 0; i < maxEnemyShots; i++) {
					if (sniperArrayShots[i].active) {
						sniperArrayShots[i].position.y += enemyShotSpeed * GetFrameTime();
						sniperArrayShots[i].AABB.x = sniperArrayShots[i].position.x + 4.0f;
						sniperArrayShots[i].AABB.y = sniperArrayShots[i].position.y;
						if (sniperArrayShots[i].position.y > static_cast<float>(GetScreenHeight())) {
							sniperArrayShots[i].active = false;
						}
					}
				}

				//collisions
				//friendly bullets->swarm
				for (int i = 0; i < maxFriendlyShots; i++) {
					if (player1ShotArray[i].active) {
						for (int i2 = 0; i2 < maxSwarmPerRow; i2++) {
							//row 0
							if (swarmRow0Array[i2].active) {
								if (CheckCollisionRecs(player1ShotArray[i].AABB, swarmRow0Array[i2].AABB)) {
									swarmRow0Array[i2].active = false;
									player1ShotArray[i].active = false;
									swarmIn0--;
									enemies--;
								}
							}
							//row 1
							if (swarmRow1Array[i2].active) {
								if (CheckCollisionRecs(player1ShotArray[i].AABB, swarmRow1Array[i2].AABB)) {
									swarmRow1Array[i2].active = false;
									player1ShotArray[i].active = false;
									swarmIn1--;
									enemies--;
								}
							}
							//row 2
							if (swarmRow2Array[i2].active) {
								if (CheckCollisionRecs(player1ShotArray[i].AABB, swarmRow2Array[i2].AABB)) {
									swarmRow2Array[i2].active = false;
									player1ShotArray[i].active = false;
									swarmIn2--;
									enemies--;
								}
							}
						}
					}
				}

				//friendly bullet->snipers
				for (int i = 0; i < maxFriendlyShots; i++) {
					if (player1ShotArray[i].active) {
						for (int i2 = 0; i2 < maxSnipers; i2++) {
							if (sniperArray[i2].active) {
								if (CheckCollisionRecs(player1ShotArray[i].AABB, sniperArray[i2].AABB)) {
									sniperArray[i2].active = false;
									player1ShotArray[i].active = false;
									snipers--;
									enemies--;
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
				for (int i = 0; i < maxEnemyShots; i++) {
					if (sniperArrayShots[i].active) {
						if (CheckCollisionRecs(sniperArrayShots[i].AABB, player1.AABB)) {
							gameOver();
						}
					}
				}

				//swarm->fortresses
				for (int i = 0; i < maxFortresses; i++) {
					if (fortressArray[i].active) {
						for (int i2 = 0; i2 < maxSwarmPerRow; i2++) {
							//row 0
							if (swarmRow0Array[i2].active) {
								if (CheckCollisionRecs(fortressArray[i].AABB, swarmRow0Array[i2].AABB)) {
									swarmRow0Array[i2].active = false;
									fortressArray[i].HP -= 2;
									swarmIn0--;
									enemies--;
								}
							}
							//row 1
							if (swarmRow1Array[i2].active) {
								if (CheckCollisionRecs(fortressArray[i].AABB, swarmRow1Array[i2].AABB)) {
									swarmRow1Array[i2].active = false;
									fortressArray[i].HP -= 2;
									swarmIn1--;
									enemies--;
								}
							}
							//row 2
							if (swarmRow2Array[i2].active) {
								if (CheckCollisionRecs(fortressArray[i].AABB, swarmRow2Array[i2].AABB)) {
									swarmRow2Array[i2].active = false;
									fortressArray[i].HP -= 2;
									swarmIn2--;
									enemies--;
								}
							}
						}
					}
				}

				//swarm->player
				for (int i = 0; i < maxSwarmPerRow; i++) {
					//row 0
					if (swarmRow0Array[i].active) {
						if (CheckCollisionRecs(player1.AABB, swarmRow0Array[i].AABB)) {
							gameOver();
						}
					}
					//row 1
					if (swarmRow1Array[i].active) {
						if (CheckCollisionRecs(player1.AABB, swarmRow1Array[i].AABB)) {
							gameOver();
						}
					}
					//row 2
					if (swarmRow2Array[i].active) {
						if (CheckCollisionRecs(player1.AABB, swarmRow2Array[i].AABB)) {
							gameOver();
						}
					}
				}

				//friendly bullets->fortresses
				for (int i = 0; i < maxFriendlyShots; i++) {
					if (player1ShotArray[i].active) {
						for (int i2 = 0; i2 < maxFortresses; i2++) {
							if (fortressArray[i2].active && !player1ShotArray[i].hitFortress) {
								if (CheckCollisionRecs(player1ShotArray[i].AABB, fortressArray[i2].AABB)) {
									player1ShotArray[i].position.x = fortressArray[i2].position.x + 43.0f;
									player1ShotArray[i].position.y = fortressArray[i2].position.y + 60.0f;
									player1ShotArray[i].hitFortress = true;
								}
							}
						}
					}
				}

				//sniper bullets->fortresses
				for (int i = 0; i < maxEnemyShots; i++) {
					if (sniperArrayShots[i].active) {
						for (int i2 = 0; i2 < maxFortresses; i2++) {
							if (fortressArray[i2].active) {
								if (CheckCollisionRecs(sniperArrayShots[i].AABB, fortressArray[i2].AABB)) {
									sniperArrayShots[i].active = false;
									fortressArray[i2].HP--;
								}
							}
						}
					}
				}


				//fortress health logic
				for (int i = 0; i < maxFortresses; i++) {
					if (fortressArray[i].active) {
						if (fortressArray[i].HP <= 0) {
							fortressArray[i].active = false;
						}
					}
				}

				//win logic
				if (enemies <= 0) {
					won = true;
					gameOver();
				}

				//ship animation 
				frameCounter++;

				if (frameCounter >= (2.0 / frameSpeed)) {
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
			else {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (exitButton.position.x <= mousePosition.x && mousePosition.x <= exitButton.position.x + exitButton.size.x) {
					if (exitButton.position.y <= mousePosition.y && mousePosition.y <= exitButton.position.y + exitButton.size.y) {
						returnToMenu();
					}
				}
			}
			}

		}

		void drawGameplay() {
			//background
			DrawTextureEx(background, { 0.0f,0.0f }, 0.0f, 8.0f, WHITE);

			//player 
			DrawTexturePro(playerTexture, player1.sourceRec, player1.destRec, { static_cast<float>(playerTexture.width) / 2.0f, static_cast<float>(playerTexture.height) / 2.0f }, 0.0f, WHITE);

			//bullets
			for (int i = 0; i < maxFriendlyShots; i++) {
				if (player1ShotArray[i].active) {
					DrawTextureEx(shotTexture, player1ShotArray[i].position, 0.0f, bulletScale, WHITE);
				}
			}

			//fortresses
			for (int i = 0; i < maxFortresses; i++) {
				if (fortressArray[i].active) {
					DrawTextureEx(fortressTexture, fortressArray[i].position, 0.0f, characterScale * 2.3f, WHITE);
				}
			}

			//snipers
			for (int i = 0; i < maxSnipers; i++) {
				if (sniperArray[i].active) {
					DrawTextureEx(sniperTexture, sniperArray[i].position, 0.0f, characterScale*1.3f, WHITE);
				}
			}

			//sniper bullets
			for (int i = 0; i < maxEnemyShots; i++) {
				if (sniperArrayShots[i].active) {
					DrawTextureEx(enemyShotTexture, sniperArrayShots[i].position, 0.0f, bulletScale, WHITE);
				}
			}

			//swarm
			for (int i = 0; i < maxSwarmPerRow; i++) {
				//row 0
				if (swarmRow0Array[i].active) {
					DrawTextureEx(swarmTexture, swarmRow0Array[i].position, 0.0f, characterScale, WHITE);
				}
				//row 1
				if (swarmRow1Array[i].active) {
					DrawTextureEx(swarmTexture, swarmRow1Array[i].position, 0.0f, characterScale, WHITE);
				}
				//row 2
				if (swarmRow2Array[i].active) {
					DrawTextureEx(swarmTexture, swarmRow2Array[i].position, 0.0f, characterScale, WHITE);
				}
			}

			//pause
			if (isPaused) {
				DrawText("PAUSED", GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 30, 60, WHITE);
				DrawRectangle(static_cast<int>(exitButton.position.x), static_cast<int>(exitButton.position.y), static_cast<int>(exitButton.size.x), static_cast<int>(exitButton.size.y), WHITE);
				DrawText("EXIT", exitButton.position.x + 70, exitButton.position.y + 10, 45, BLACK);
			}
		}
	}
}