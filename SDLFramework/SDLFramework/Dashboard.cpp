#include "Dashboard.h"
#include "FWApplication.h"
#include "Graph.h"

std::string Dashboard::applicationInformation;
std::string Dashboard::shortestPathLabel;
std::string Dashboard::cowStateLabel;
std::string Dashboard::rabbitStateLabel;

Dashboard::Dashboard()
{
	ApplicationInformation("Andrew Servania - KMINT Week 2");
	ShortestPathLabel("");
	RabbitStateLabel("No state implemented yet");
}


Dashboard::~Dashboard()
{
}

void Dashboard::Update()
{
	FWApplication::GetInstance()->DrawText(applicationInformation, 150, 50);
	FWApplication::GetInstance()->DrawText(shortestPathLabel, 200, 500);
	CowStateLabel(Graph::cow->GetCurrentState());
	FWApplication::GetInstance()->DrawText(cowStateLabel, 150, 150);
	RabbitStateLabel(Graph::rabbit->GetCurrentState());
	FWApplication::GetInstance()->DrawText(rabbitStateLabel, 150, 200);
}