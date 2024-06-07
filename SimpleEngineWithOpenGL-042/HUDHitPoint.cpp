#include "HUDHitPoint.h"

#include "HUD.h"
#include "Assets.h"
#include "Game.h"
#include "TargetComponent.h"
#include "FPSActor.h"

HUDHitPoint::HUDHitPoint():
	UIScreen()
{
	hitPoint = &Assets::getTexture("HitPoint");
	hitPoint2 = &Assets::getTexture("HitPoint2");
	hitPoint3 = &Assets::getTexture("HitPoint3");
	hitPoint4 = &Assets::getTexture("HitPoint4");
}

HUDHitPoint::~HUDHitPoint()
{
}

void HUDHitPoint::update(float dt)
{
	UIScreen::update(dt);
	updateHP(dt);

}

void HUDHitPoint::draw(Shader& shader)
{
	const Vector2 hitPointPosition {-475.f,-350.f};
	drawTexture(shader, hitPoint, hitPointPosition,0.05f);
}

void HUDHitPoint::updateHP(float dt)
{
	switch (Game::instance().getPlayer()->getHP())
	{
	case 4:
		hitPoint = &Assets::getTexture("HitPoint");
		break;
	case 3:
		hitPoint = &Assets::getTexture("HitPoint2");
		break;
	case 2 :
		hitPoint = &Assets::getTexture("HitPoint3");
		break;
	case 1:
		hitPoint = &Assets::getTexture("HitPoint4");
		break;
	default:
		hitPoint = &Assets::getTexture("HitPoint");
		break;
	}
}

