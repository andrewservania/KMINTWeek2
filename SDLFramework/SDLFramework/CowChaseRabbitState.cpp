#include "CowChaseRabbitState.h"
#include "Graph.h"
#include "CowWanderingState.h"
#include "AStar.h"
#include "Graph.h"
#include "CowWanderingState.h"
#include "RabbitFleeingState.h"
#include <memory>
#include "Dashboard.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. 
/// 			Set pathIsCalculated flag to false
/// 			Set counter to zero.
/// 			</summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowChaseRabbitState::CowChaseRabbitState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowChaseRabbitState::~CowChaseRabbitState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Take action right after entering the state,
/// 			Calculate the shortest path between the rabbit and the cow and show it on screen.
/// 			 </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowChaseRabbitState::Enter(Cow* cow)
{
	stepTimer = 0;
	shared_ptr<AStar> astar = make_shared<AStar>();
	shortestPath = astar->GetShortestPath(cow->getCurrentNode(), Graph::rabbit->getCurrentNode());

	UpdateShortestPathLabel(cow, Graph::rabbit);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Calculate the shortest path between the rabbit and the cow as the rabbit moves around.
/// </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowChaseRabbitState::Execute(Cow* cow)
{
	if (stepTimer == 50)
	{
		if (!shortestPath.empty())					// If shortest path is empty, then go to the goal node step by step
		{
			cow->setCurrentNode(shortestPath.top()); // Cow will walk to the top next node
			shortestPath.pop();						 // Now remove the top next node
			stepTimer = 0;
		}
		else{
			cow->GetFSM()->ChangeState(CowWanderingState::Instance());
		}
	}

	stepTimer++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Take action just before exiting the state </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowChaseRabbitState::Exit(Cow* cow)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the shortest path label described by _shortestPath. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="_shortestPath">	[in,out] If non-null, full pathname of the shortest file. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowChaseRabbitState::UpdateShortestPathLabel(Cow* cow, Rabbit* rabbit)
{
	shared_ptr<AStar> aStar = make_shared<AStar>();
	auto shortPath = aStar->GetShortestPath(cow->getCurrentNode(), rabbit->getCurrentNode());
	string shortestPathLabel = "Shortest path from cow to rabbit: ";
	while (!shortPath.empty())
	{
		Node* step = shortPath.top();

		shortestPathLabel += to_string(step->id).c_str();

		shortPath.pop();
		if (!shortPath.empty())
			shortestPathLabel += " -> ";
	}
	Dashboard::Instance()->ShortestPathLabel(shortestPathLabel);
}