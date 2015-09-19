#pragma once
#include "State.h"
#include "Cow.h"
#include <stack>
#include "Node.h"

class CowChaseRabbitState :
	public State<Cow>
{
private:
	int stepTimer;
	std::stack<Node*> shortestPath;
public:
	CowChaseRabbitState();
	~CowChaseRabbitState();

	void Enter(Cow* cow) override;
	void Execute(Cow* cow) override;
	void Exit(Cow* cow) override;
	std::string GetStateName() override { return "Cow Chase Rabbit State"; }
	static CowChaseRabbitState* Instance()
	{
		static CowChaseRabbitState instance;
		return &instance;
	}

};

