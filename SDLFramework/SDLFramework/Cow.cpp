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

	//TODO: Add pill and weapon on the screen
	//TODO: 1) Create new kind of counter to trigger a SearchForWeaponState. This has to be triggered in the WanderingState
	//TODO: 2) Arm the rabbit class with the BaseGameEntity class
	//TODO: 3) Make sure the rabbit can also change from state (For example a fleeing state) You'll have to delay the screen in terms of refresh rate in order to show it
	//TODO: 4) Make sure you put state labels for the cow and rabbit and make sure to update them accordingly!
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
