#ifndef CREDIT_SCREEN_H
#define CREDIT_SCREEN_H

#include "raylib.h"

#include "flow-manager.h"

namespace game {
	namespace creditsspace {
		void initCredits();
		void updateCredits();
		void drawCredits();
	}
}
#endif