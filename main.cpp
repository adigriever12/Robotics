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
#include "WayPointsManager.h"
#include "Robot.h"
#include "Manager.h"
#include "Plans/PlnObstacleAvoid.h"
#include "ConfiguraionManager.h"

using namespace PlayerCc;
using namespace std;

int main() {
    
    
        ConfiguraionManager cnf("/home/colman/Desktop/parameters.txt");
        cnf.ReadParameters();
        
        srand (time(NULL));
	Map m("/home/colman/Desktop/roboticLabMap.png");
	m.blowMap();

	m.turnToGrid();
        
	int startX = m.PixleLocationToGrid(ConfiguraionManager::StartLocationX);
	int startY = m.PixleLocationToGrid(ConfiguraionManager::StartLocationY);
	int goalX = m.PixleLocationToGrid(ConfiguraionManager::GoalLocationX);
	int goalY = m.PixleLocationToGrid(ConfiguraionManager::GoalLocationY);

	int** grid = m.GetGrid();

	PathPlanner pathplanner(startX, startY, goalX, goalY, &m);

	vector<MapSearchNode*> nodes;
	pathplanner.GetAStarNodes(nodes);
        
        WayPointsManager waypointsmanager(nodes, &m);
        
        vector<MapSearchNode*> filtered_nodes;
        waypointsmanager.GetWayPointNodes(filtered_nodes);
        
        for (int blat = 0; blat < filtered_nodes.size(); blat++)
            printf("Waypoints %u: (%u, %u)\n", blat, filtered_nodes[blat]->GetX(), filtered_nodes[blat]->GetY());
        
        waypointsmanager.NewNodes(filtered_nodes);
        
        //for (int blat = 0; blat < filtered_nodes.size(); blat++)
          //  printf("Waypoints %u: (%u, %u)\n", blat, filtered_nodes[blat]->GetX(), filtered_nodes[blat]->GetY());
        
//        for (int i = 0; i < filtered_nodes.size() - 1; i++) {
//            if (filtered_nodes[i]->)
//        }

        LocalizationManager localization(&m);
        
        Robot robot("10.10.245.65",6665, &localization);
	PlnObstacleAvoid plnOA(&robot);
        
        robot.SetOdometryByPixelCoord(ConfiguraionManager::StartLocationY,
                ConfiguraionManager::StartLocationX, ConfiguraionManager::StartLocationYAW,
				m.GetPixelResolution(), m.GetMapWidth(), m.GetMapHeight());
        
        
        printf("%f, %f, %f\n", robot.GetX(), robot.GetY(), robot.GetYaw());

        Manager manager(&robot, &plnOA);
	manager.run(filtered_nodes);
        
        for(int i = 0; i < nodes.size(); i++)
	{
		int x = nodes[i]->GetX();
		int y = nodes[i]->GetY();
		grid[x][y] = 7;
	}
        
        for(int i = 0; i < filtered_nodes.size(); i++)
	{
		int x = filtered_nodes[i]->GetX();
		int y = filtered_nodes[i]->GetY();
		grid[y][x] = 5;
	}

//	for(int i = 0; i < 95; i++)
//        {
//            for(int j = 0; j < 138; j++)
//            {
//		std::cout << grid[i][j] << std::flush;
//            }
//            std::cout << "\n" << std::flush;
//	}
}
