#include "ElevatorDoor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"
#include "MoveComponent.h"

ElevatorDoor::ElevatorDoor()
{
    moveC = new MoveComponent(this);
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = &Assets::getMesh("Mesh_Door");
    mc->setMesh(*mesh);
    box = new BoxComponent(this);
    box->setObjectBox(mesh->getBox());
    moveC->setForwardSpeed(0.f);
}
ElevatorDoor::~ElevatorDoor()
{
}
