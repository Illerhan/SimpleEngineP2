#pragma once
#include "Actor.h"
class OrbitActor :
    public Actor
{
public:
    OrbitActor();
    void actorInput(const InputState& inputState) override;
    void setVisible(bool isVisible);

private:
    class OrbitCameraComponent* cameraComponent;
    class MeshComponent* meshComponent;
};

