#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "raylib.h"

#include "flow-manager.h"

namespace game {
	namespace gameplayspace {
		void initGameplay();
		void updateGameplay();
		void drawGameplay();

		const unsigned int maxFriendlyShots = 5;
		const unsigned int maxEnemies = 55;
		const unsigned int maxEnemyShots = 10;
		const unsigned int maxFortresses = 5;

		enum enemyType {
			swarm, bomber,
		};

		struct Fortress {
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
		};

		struct Player {
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
			float speed;
			float scale;
			bool charged;
			bool chargeCount;
			double startCharge;
			double chargeTimeLimit;
		};

		struct Enemy {
			bool active;
			enemyType type;
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
		};

		struct Shot {
			bool active;
			bool friendly;
			double birthDate;
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
		};
	}
}
#endif
