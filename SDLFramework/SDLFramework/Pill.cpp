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
	// If the rabbit or the cow is on the same spot as the pill,
	// respawn the pill somewhere else.
	if (Graph::cow->currentNode->id == currentNode->id || Graph::rabbit->currentNode->id == currentNode->id)
		SetCurrentNode(Graph::graphNodes.at(rand() % Graph::graphNodes.size()));
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