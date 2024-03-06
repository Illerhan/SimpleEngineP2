#pragma once
#include "Actor.h"
#include "CubeActor.h"

class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void hitTarget(CubeActor* target);


private:
	//class AudioComponent* audio;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
};

