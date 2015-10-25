#include "RabbitFleeingState.h"
#include "Graph.h"
#include "RabbitWanderingState.h"
#include "Dashboard.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor.
/// 			Set the timer to 0 and the 'fled' flag to false. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

RabbitFleeingState::RabbitFleeingState()
{
	timer = 0;
	fled = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

RabbitFleeingState::~RabbitFleeingState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Take action right after entering the state.
/// 			Set timer to 0.
/// 			Set 'fled' flag to false. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="rabbit">	[in,out] If non-null, the rabbit. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RabbitFleeingState::Enter(Rabbit* rabbit)
{
	timer = 0;
	fled = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Flee the rabbit to a random node, as long as its not the same node
/// 			as the cow (ofcourse), the pill or the weapon.
/// 			When the rabbit has reaches a safe node, it goes back into a Wandering state.
/// 			</summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="rabbit">	[in,out] If non-null, the rabbit. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RabbitFleeingState::Execute(Rabbit* rabbit)
{
	if (timer == 80)
	{
		if (fled == false)
		{
			Node* newLocation = Graph::graphNodes.at(rand() % 8);					// Put the rabbit in a random location
			rabbit->setCurrentNode(newLocation);
			while (rabbit->getCurrentNode()->id == Graph::cow->getCurrentNode()->id ||
				rabbit->getCurrentNode()->id == Graph::pill->GetCurrentNode()->id ||
				rabbit->getCurrentNode()->id == Graph::weapon->GetCurrentNode()->id) // if it's still on the same location as the cow. Choose a different location for the rabbit.
			{
				newLocation = Graph::graphNodes.at(rand() % 8);
				rabbit->setCurrentNode(newLocation);
			}
			fled = true;
		}

		rabbit->GetFSM()->ChangeState(RabbitWanderingState::Instance());
		timer = 0;
	}
	timer++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Take action right before exiting the state.
/// 			Clear the label showing the shortest path </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="rabbit">	[in,out] If non-null, the rabbit. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void RabbitFleeingState::Exit(Rabbit* rabbit)
{
	Dashboard::Instance()->ShortestPathLabel("");
}