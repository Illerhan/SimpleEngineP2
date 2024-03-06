#include "CubeActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"

CubeActor::CubeActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Target").getBox());
	
}
