#include "Pill.h"
#include "Graph.h"

Pill::Pill()
{
	mTexture = mApplication->LoadTexture("pill.png");

	// Put the pill at a random location
	SetCurrentNode(Graph::graphNodes.at(rand() % Graph::graphNodes.size()));
	mApplication->AddRenderable(this);
}



Pill::~Pill()
{
}

// Check for changes regarding the pill
void Pill::Update(float deltaTime)
{
}

// Draw the pill on screen
void Pill::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY, 100, 100);
};

// Put the pill at a new location
void Pill::SetCurrentNode(Node* newNode)
{
	currentNode = newNode;
	mX = currentNode->GetBoundingBox().x;
	mY = currentNode->GetBoundingBox().y;
}

// Respawn the pill somewhere else.
void Pill::PutOnRandomLocation()
{
	SetCurrentNode(Graph::graphNodes.at(rand() % Graph::graphNodes.size()));
}