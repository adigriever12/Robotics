/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include "pngUtil.h"
#include "pngUtil.h"
#include "lodepng.h"
#include <iostream>
#include <fstream>
#include "Map.h"
#include "PathPlanner.h"

using namespace PlayerCc;
using namespace std;

int main() {

	//Map m("/home/colman/Desktop/hospital_section.png");

	Map m("/home/colman/Desktop/roboticLabMap.png");
	m.blowMap();

	m.turnToGrid();

	// TODO:: Read from parameters file later
	int startX = m.PixleLocationToGrid(305);
	int startY = m.PixleLocationToGrid(362);
	int goalX = m.PixleLocationToGrid(138);
	int goalY = m.PixleLocationToGrid(169);

	int** grid = m.GetGrid();


	PathPlanner pathplanner(startX, startY, goalX, goalY, &m);

	vector<MapSearchNode*> nodes;
	pathplanner.GetAStarNodes(nodes);

	for(int i = 0; i < nodes.size(); i++)
	{
		int x = nodes[i]->GetX();
		int y = nodes[i]->GetY();
		grid[x][y] = 7;
	}

	for(int i = 0; i < 95; i++)
		{
			for(int j = 0; j < 138; j++)
			{
				std::cout << grid[i][j] << std::flush;
			}
			std::cout << "\n" << std::flush;
		}
}
