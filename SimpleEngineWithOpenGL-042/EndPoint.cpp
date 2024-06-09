#include "EndPoint.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"

EndPoint::EndPoint()
{
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = &Assets::getMesh("Mesh_Key");
    mc->setMesh(*mesh);
    box = new BoxComponent(this);
    box->setObjectBox(mesh->getBox());
}  
EndPoint::~EndPoint()
{
}
