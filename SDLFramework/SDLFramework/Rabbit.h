#pragma once
#include "IGameObject.h"
#include "Node.h"
#include "StateMachine.h"

class Rabbit :
	public IGameObject
{
public:
	Node* currentNode;
	StateMachine<Rabbit>* stateMachine;

	Rabbit();
	~Rabbit();
	virtual void Update(float deltaTime) override;
	virtual void Draw()override;
	void OnLeftClick();
	void OnRightClick();
	void setCurrentNode(Node* node);
	Node* getCurrentNode() { return currentNode; }
	std::string GetCurrentState() { return stateMachine->CurrentState()->GetStateName(); }
};

