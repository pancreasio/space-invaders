#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "raylib.h"

#include "flow-manager.h"

namespace game {
	namespace gameplayspace {
		void initGameplay();
		void updateGameplay();
		void drawGameplay();

		enum enemyType {
			swarm, bomber, sniper,
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

		struct Swarm {
			bool active;
			enemyType type;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
		};

		struct Bomber {
			bool active;
			enemyType type;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
		};

		struct Sniper {
			bool active;
			double timeShot;
			enemyType type;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
		};

		struct Shot {
			bool active;
			double birthDate;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
		};

		struct EnemyShot {
			bool active;
			double birthDate;
			Rectangle AABB;
			Vector2 position;
			Vector2 speed;
		};
	}
}
#endif
