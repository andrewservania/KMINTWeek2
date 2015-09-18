#include "CowWanderingState.h"
#include "Graph.h"


CowWanderingState::CowWanderingState()
{
	counter = 0;
}


void CowWanderingState::Enter(Cow* cow)
{

}

void CowWanderingState::Execute(Cow* cow)
{
	if (counter == 50)
	{
		counter = 0;

		// Cow will go to a neighboring node from the current node in which it is standing
		int amountOfneighbors = cow->getCurrentNode()->GetEdges().size();
		Node* nodeToWanderTo = cow->getCurrentNode()->GetEdges().at(rand() % amountOfneighbors)->child;
		cow->setCurrentNode(nodeToWanderTo);
	}
	counter++;
}

void CowWanderingState::Exit(Cow* cow)
{
}



CowWanderingState::~CowWanderingState()
{
}
