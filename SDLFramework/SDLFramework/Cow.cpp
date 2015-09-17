#include "Cow.h"
#include "Graph.h"
#include "AStar.h"
#include <string>
#include <memory>
#include <assert.h>
#include "CowWanderingState.h"
using namespace std;

Cow::Cow(int id) : BaseGameEntity(id)
{
	mTexture = mApplication->LoadTexture("cow-1.png");
	mApplication->AddRenderable(this);
	mX = 100;
	mY = 100;

	// Add sample code here that is responsible for updating the cow
	// Set up the state machine
	stateMachine = new StateMachine<Cow>(this);

	stateMachine->SetCurrentState(CowWanderingState::Instance());
	//stateMachine->SetGlobalState()
}


void Cow::Update(float deltaTime)
{

	stateMachine->Update();
}


Cow::~Cow()
{
	delete stateMachine;
}


void Cow::setCurrentNode(Node* node)
{
	 currentNode = node; 
	 mX = node->GetBoundingBox().x;
	 mY = node->GetBoundingBox().y;
}

// Draw cow texture
void Cow::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY,100, 100);
}

//Handle all clicks
void Cow::OnClick(SDL_Event& event)
{
	// Handle clicks that are made within the range in which the cow is situated on
	if (event.motion.x >= static_cast<Sint32>(mX - 90) &&
		event.motion.x <= static_cast<Sint32>(mX + 90) &&
		event.motion.y >= static_cast<Sint32>(mY - 90) &&
		event.motion.y <= static_cast<Sint32>(mY + 90))
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			OnLeftClick(event);
		if (event.button.button == SDL_BUTTON_RIGHT)
			OnRightClick(event);
	}
}

// Execute code when rabbit has been left clicked upon
void Cow::OnLeftClick(SDL_Event &event)
{	
	shared_ptr<AStar> aStar = make_shared<AStar>();

	// Calculate the shortest path based on the current node of both the cow(start) and the rabbit(goal)
	auto shortestPath = aStar->GetShortestPath(currentNode, Graph::rabbit->getCurrentNode());

	while (!shortestPath.empty())
	{
		Node* step = shortestPath.top();		// Get the next node to go to.	
		this->setCurrentNode(step);					// Set the cow's node to the next node to go to
		shortestPath.pop();
	}

}

// Execute code when rabbit has been right clicked upon
void Cow::OnRightClick(SDL_Event &event)
{
	printf("Right-clicked on cow!\n");
}

void Cow::ChangeState(State<Cow>* newState)
{

	// to make sure both states are valid before attempting to
	// call their methods
	//assert(currentState && newState);

}