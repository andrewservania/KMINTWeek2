#include "CowSearchForPillState.h"
#include "AStar.h"
#include "Graph.h"
#include "CowChaseRabbitState.h"
#include <memory>

using namespace std;

CowSearchForPillState::CowSearchForPillState()
{
}


CowSearchForPillState::~CowSearchForPillState()
{
}

void CowSearchForPillState::Enter(Cow* cow)
{
	stepTimer = 0;
	shared_ptr<AStar> astar = make_shared<AStar>();

	shortestPath = astar->GetShortestPath(cow->getCurrentNode(), Graph::pill->GetCurrentNode());

}

void CowSearchForPillState::Execute(Cow* cow)
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
			cow->GetFSM()->ChangeState(CowChaseRabbitState::Instance());
		}
	}

	stepTimer++;
}

void CowSearchForPillState::Exit(Cow* cow)
{
}