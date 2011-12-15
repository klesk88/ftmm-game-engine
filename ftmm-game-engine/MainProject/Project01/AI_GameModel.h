#ifndef AI_GameModel_H
#define AI_GameModel_H

#pragma once

using namespace::std;

class AI_GameModel
{
private:

	static AI_GameModel * p_instance;

	int player_x;
	int player_y;
	int player_velocity;
	int npc01_x;
	int npc01_y;
	int npc01_velocity;
	int npc02_x;
	int npc02_y;
	int npc02_velocity;
	int npc03_x;
	int npc03_y;
	int npc03_velocity;

	int carMeshWidth;

protected:

	AI_GameModel();

public:

	static AI_GameModel * getInstance();
	~AI_GameModel();
	
	void set_carMeshWidth(int w);
	void set_playerInfo(int x, int y, int velo);
	void set_npcInfo(int x, int y, int velo, int id);	
	bool get_playerOnSameLane(int id);

};

#endif
