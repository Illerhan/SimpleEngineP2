#pragma once
#include <xstring>

#include "Actor.h"


class BallActor;

class CubeActor : public Actor
{
public:
	CubeActor();
	void setMesh(std::string meshName);
	void updateActor(float dt) override;
	class CubeMoveComponent* cubeMove;
	void hitBall(BallActor* ball);
	void hitPins(CubeActor* pins);
	void setArrow(Actor* arrow);
	void setMeshName(const char* meshNameP){meshName = meshNameP;}

private:
	float lifetimeSpan;
	bool gotHit;
	std::string meshName;

public:

};

