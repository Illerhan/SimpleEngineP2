#include "ShootButton.h"

#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"
#include "MeshComponent.h"

ShootButton::ShootButton(ActivableDoor* Adoor) : door()
{
    setRotation(Quaternion(Vector3::unitZ, Maths::pi));
    MeshComponent* mc = new MeshComponent(this);
    mc->setMesh(Assets::getMesh("Mesh_Target"));
    // Add collision box
    BoxComponent* bc = new BoxComponent(this);
    bc->setObjectBox(Assets::getMesh("Mesh_Target").getBox());
    getGame().addButton(this);
    door = Adoor;
}

ShootButton::~ShootButton()
{
    getGame().removeButton(this);
}

