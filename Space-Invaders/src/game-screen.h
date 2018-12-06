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

		

		struct Fortress {
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
			Texture texture;
		};

		struct Player {
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
			Texture texture;
			bool charged;
			bool chargeCount;
			double startCharge;
			double chargeTimeLimit;
		};

		struct Enemy {
			bool active;
			enum type{
				swarm, bomber,
			};
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
			Texture texture;
		};

		struct Shot {
			bool active;
			bool friendly;
			Rectangle sourceRec;
			Rectangle destRec;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
			Texture texture;
		};
	}
}
#endif
