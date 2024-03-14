#pragma once
#include "Actor.h"


class BallActor;

class CubeActor : public Actor
{
public:
	CubeActor();
	void updateActor(float dt) override;
	class CubeMoveComponent* cubeMove;
	void hitBall(BallActor* ball);
	void hitPins(CubeActor* pins);
	void setArrow(Actor* arrow);

private:
	float lifetimeSpan;
	bool gotHit;
};

