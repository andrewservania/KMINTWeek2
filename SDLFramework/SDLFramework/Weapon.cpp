#include "Weapon.h"
#include "Graph.h"

Weapon::Weapon()
{
	mTexture = mApplication->LoadTexture("gun-metal.png");
	// Put the weapon at a random location
	SetCurrentNode(Graph::graphNodes.at(rand() % Graph::graphNodes.size()));
	mApplication->AddRenderable(this);
	mApplication->AddRenderable(this);
}


Weapon::~Weapon()
{
}

void Weapon::Update(float deltaTime)
{
	// If the rabbit or the cow is on the same spot as the weapon,
	// respawn the weapon somewhere else.
	//if (Graph::cow->currentNode->id == currentNode->id || Graph::rabbit->currentNode->id == currentNode->id)
	//	SetCurrentNode(Graph::graphNodes.at(rand() % Graph::graphNodes.size()));
}

void Weapon::Draw()
{
	mApplication->DrawTexture(mTexture, mX,mY, 100, 100);
};

// Put the weapon at a new location
void Weapon::SetCurrentNode(Node* newNode)
{
	currentNode = newNode;
	mX = currentNode->GetBoundingBox().x;
	mY = currentNode->GetBoundingBox().y;
}

void Weapon::PutOnRandomLocation()
{
	SetCurrentNode(Graph::graphNodes.at(rand() % Graph::graphNodes.size()));
}