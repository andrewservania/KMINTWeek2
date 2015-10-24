#include "CowSearchForWeaponState.h"
#include "AStar.h"
#include "Graph.h"
#include "CowWanderingState.h"
#include <memory>
#include "Dashboard.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowSearchForWeaponState::CowSearchForWeaponState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CowSearchForWeaponState::~CowSearchForWeaponState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Take action right after entering the state.
/// 			Calculate the shortest path between the cow and the weapon.
/// 			 </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowSearchForWeaponState::Enter(Cow* cow)
{
	stepTimer = 0;
	shared_ptr<AStar> astar = make_shared<AStar>();

	shortestPath = astar->GetShortestPath(cow->getCurrentNode(), Graph::weapon->GetCurrentNode());
	UpdateShortestPathLabel(cow, Graph::weapon);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Walk towards the weapon using the shortest path.
/// 			When the cow has reached the weapon, the goes back into a Wandering state. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">	[in,out] If non-null, the cow. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowSearchForWeaponState::Execute(Cow* cow)
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
			Graph::weapon->PutOnRandomLocation();

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

void CowSearchForWeaponState::Exit(Cow* cow)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the label showing the shortest path. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="cow">   	[in,out] If non-null, the cow. </param>
/// <param name="weapon">	[in,out] If non-null, the weapon. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CowSearchForWeaponState::UpdateShortestPathLabel(Cow* cow, Weapon* weapon)
{
	shared_ptr<AStar> aStar = make_shared<AStar>();
	auto shortPath = aStar->GetShortestPath(cow->getCurrentNode(), weapon->GetCurrentNode());
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