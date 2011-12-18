#include "AI_Manager.h"

#define NULL 0

AI_Manager * AI_Manager::p_instance = NULL;

AI_Manager::AI_Manager(){}

AI_Manager * getInstance();
	
AI_Manager * AI_Manager::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new AI_Manager();
	}
	return p_instance;
}

AI_Agent* AI_Manager::get_AIAgent(int id)
{
	AI_Agent * agent = new AI_Agent();
	ai_agents[id] = agent;
	return agent;
}