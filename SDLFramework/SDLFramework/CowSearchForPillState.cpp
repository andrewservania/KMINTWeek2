#include "CowSearchForPillState.h"
#include "AStar.h"
#include "Graph.h"
#include "CowChaseRabbitState.h"
#include <memory>
#include "Dashboard.h"
#include "Node.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowSearchForPillState::CowSearchForPillState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowSearchForPillState::~CowSearchForPillState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Take action right after entering the state.
/// 			Calculate the shortest path between the cow and the pill.
/// 			  </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowSearchForPillState::Enter(Cow* cow)
{
	
	stepTimer = 0;
	shared_ptr<AStar> astar = make_shared<AStar>();
	shortestPath = astar->GetShortestPath(cow->getCurrentNode(), Graph::pill->GetCurrentNode());

	UpdateShortestPathLabel(cow, Graph::pill);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Slowly walk towards the pill using the shortest path. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowSearchForPillState::Execute(Cow* cow)
{
	if (stepTimer == 50)
	{
		if (!shortestPath.empty())					 // If shortest path is empty, then go to the goal node step by step
		{
			cow->setCurrentNode(shortestPath.top()); // Cow will walk to the top next node
			shortestPath.pop();						 // Now remove the top next node
			stepTimer = 0;
		}
	}

	stepTimer++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Take action right before exiting the state. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowSearchForPillState::Exit(Cow* cow)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the label showing the shortest path. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow"> 	[in,out] If non-null, the cow. </param>
/// <param name="pill">	[in,out] If non-null, the pill. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowSearchForPillState::UpdateShortestPathLabel(Cow* cow, Pill* pill)
{
	shared_ptr<AStar> aStar = make_shared<AStar>();
	auto shortPath = aStar->GetShortestPath(cow->getCurrentNode(), pill->GetCurrentNode());
	string shortestPathLabel = "Shortest path from cow to pill: ";
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