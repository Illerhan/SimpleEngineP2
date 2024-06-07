#include "ActivableDoor.h"

#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"
#include "MeshComponent.h"

ActivableDoor::ActivableDoor()
{
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = &Assets::getMesh("Mesh_Cube");
    mc->setMesh(*mesh);
    box = new BoxComponent(this);
    box->setObjectBox(mesh->getBox());

    getGame().addDoor(this);
}
ActivableDoor::~ActivableDoor()
{
    getGame().removeDoor(this);
}

