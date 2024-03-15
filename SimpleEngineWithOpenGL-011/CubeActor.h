#pragma once
#include <xstring>

#include "Actor.h"


class BallActor;

class CubeActor : public Actor
{
public:
	CubeActor();
	CubeActor(std::string spriteNameP);
	void updateActor(float dt) override;
	class CubeMoveComponent* cubeMove;
	void hitBall(BallActor* ball);
	void hitPins(CubeActor* pins);
	void setArrow(Actor* arrow);
	void setSpriteName(const char* spriteNameP){spriteName = spriteNameP;}

private:
	float lifetimeSpan;
	bool gotHit;
	std::string spriteName;

public:

};

