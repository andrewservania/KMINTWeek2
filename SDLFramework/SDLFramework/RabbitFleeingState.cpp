#include "RabbitFleeingState.h"
#include "Graph.h"
#include "RabbitWanderingState.h"
#include "Dashboard.h"
RabbitFleeingState::RabbitFleeingState()
{
	timer = 0;
	fled = false;
}

RabbitFleeingState::~RabbitFleeingState()
{

}

void RabbitFleeingState::Enter(Rabbit* rabbit)
{
	timer = 0;
	fled = false;
}

void RabbitFleeingState::Execute(Rabbit* rabbit)
{

	if (fled == false)
	{
		Node* newLocation = Graph::graphNodes.at(rand() % 8);					// Put the rabbit in a random location
		rabbit->setCurrentNode(newLocation);
		while (Graph::cow->getCurrentNode()->id == rabbit->getCurrentNode()->id) // if it's still on the same location as the cow. Choose a different location for the rabbit.
		{
			newLocation = Graph::graphNodes.at(rand() % 8);
			rabbit->setCurrentNode(newLocation);
		}
		fled = true;
	}
		
	if (timer == 100)
	{
		rabbit->GetFSM()->ChangeState(RabbitWanderingState::Instance());
		timer = 0;
	}
	timer++;
}

void RabbitFleeingState::Exit(Rabbit* rabbit)
{
	Dashboard::Instance()->ShortestPathLabel("");
}
