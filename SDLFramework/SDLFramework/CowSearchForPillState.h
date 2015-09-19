#pragma once
#include "State.h"
#include "Cow.h"
#include "Node.h"
#include <stack>
class CowSearchForPillState :
	public State<Cow>
{
private:
	int stepTimer;
	std::stack<Node*> shortestPath;
public:
	CowSearchForPillState();
	~CowSearchForPillState();
	void Enter(Cow* cow) override;
	void Execute(Cow* cow) override;
	void Exit(Cow* cow) override;
	std::string GetStateName() override { return "Search For Pill State"; }
	static CowSearchForPillState* Instance()
	{
		static CowSearchForPillState instance;
		return &instance;
	}
};

