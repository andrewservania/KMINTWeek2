#include "CowWanderingState.h"
#include "Graph.h"


CowWanderingState::CowWanderingState()
{
	counter = 0;
}

// Do the necessary preparations to enter the Cow Wandering State
void CowWanderingState::Enter(Cow* cow)
{

}

// Execute the code correspesonding to the Cow Wandering state
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

// Do the necessary cleanups and close ups before leaving the Cow Wandering State
void CowWanderingState::Exit(Cow* cow)
{
}


CowWanderingState::~CowWanderingState()
{
}
