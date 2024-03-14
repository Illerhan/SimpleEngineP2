#pragma once
#include "Actor.h"
#include "SoundEvent.h"
#include "Vector3.h"

class FPSActor : public Actor
{
public:
	FPSActor();
	
	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;
	void shoot();

	void setFootstepSurface(float value);
	void setVisible(bool isVisible);
	void fixCollisions();
	void resetGame();

	bool getDirSelected(){ return dirSelected;}
	bool getPowerSelected(){ return powerSelected;}
	bool getHasShoot(){ return hasShoot;}

private:
	class MoveComponent* moveComponent;
	//class AudioComponent* audioComponent;
	class MeshComponent* meshComponent;
	class FPSCameraComponent* cameraComponent;
	class Actor* FPSModel;
	//SoundEvent footstep;
	float lastFootstep;
	class BoxComponent* boxComponent;
	bool dirSelected = false;
	bool powerSelected = false;
	bool hasShoot = false;
	float delay = 0;
	bool canShoot = true;
	int shootCount = 0;

};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);
