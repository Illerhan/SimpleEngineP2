#include "HUDHitPoint.h"
#include "FPSActor.h"
#include "Assets.h"
#include "Game.h"

HUDHitPoint::~HUDHitPoint()
{
}

HUDHitPoint::HUDHitPoint()
{
    hitPoint = &Assets::getTexture("HitPoint");
    hitPoint2 = &Assets::getTexture("HitPoint");
    hitPoint3 = &Assets::getTexture("HitPoint");
    hitPoint4 = &Assets::getTexture("HitPoint");
}

void HUD::draw(Shader& shader)
{
    switch (Game::instance().getPlayer()->getHP()) {  }
    const Vector2 hitPointPosition {-475.f,-350.f};
    drawTexture(shader, radarArrow, hitPointPosition);
	
	
}