#pragma once
#include "State.h"
#include "Cow.h"
#include <stack>
#include "Node.h"

class CowSearchForWeaponState :
	public State<Cow>
{
private:
	std::stack<Node*> shortestPath;
	int stepTimer;
public:
	
	CowSearchForWeaponState();
	~CowSearchForWeaponState();
	
	void Enter(Cow* cow) override;
	void Execute(Cow* cow) override;
	void Exit(Cow* cow) override;
	std::string GetStateName() override { return "Search For Weapon State"; }
	static CowSearchForWeaponState* Instance()
	{
		static CowSearchForWeaponState instance;
		return &instance;
	}
};

