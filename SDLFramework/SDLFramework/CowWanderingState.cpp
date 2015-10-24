#include "CowWanderingState.h"
#include "Graph.h"
#include "CowSearchForPillState.h"
#include "Dashboard.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowWanderingState::CowWanderingState()
{
	counter = 0;
	boredom = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Do the necessary preparations to enter the Cow Wandering State.
/// 			set the cow's boredom level to 0. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowWanderingState::Enter(Cow* cow)
{
	boredom = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Execute the code correspesonding to the Cow Wandering state. 
/// 			Cow just wanders around by hoping onto neighboring nodes.
/// 			Every step (node visited) the cow takes, its boredom level will go up by 1.
/// 			When the cow's boredom level has reached 10, it will go in a SearchForPill state.
/// 			</summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowWanderingState::Execute(Cow* cow)
{
	if (counter == 100){
		counter = 0;

		// Cow will go to a neighboring node from the current node in which it is standing
		int amountOfneighbors = cow->getCurrentNode()->GetEdges().size();
		Node* nodeToWanderTo = cow->getCurrentNode()->GetEdges().at(rand() % amountOfneighbors)->child;
		cow->setCurrentNode(nodeToWanderTo);
		boredom++;
		Dashboard::Instance()->CowBoredomLevel(boredom);
	}
	counter++;

	if (boredom == 10){
		cow->GetFSM()->ChangeState(CowSearchForPillState::Instance());
		
		Dashboard::Instance()->CowBoredomLevel(boredom);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Do the necessary cleanups and close ups before leaving the Cow Wandering State.
/// </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowWanderingState::Exit(Cow* cow)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowWanderingState::~CowWanderingState()
{
}
