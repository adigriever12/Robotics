/*
 * PathPlanner.h
 *
 *  Created on: Jun 24, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_
#include "MapSearchNode.h"
#include "Map.h"

#define MAX_NODES_COUNT 32767

class PathPlanner {
	AStarSearch<MapSearchNode>* _aStarAlgorithm;

public:
	PathPlanner(int startX, int startY, int goalX, int goalY, Map* map);
	virtual ~PathPlanner();
	void GetAStarNodes(vector<MapSearchNode*> &nodesFromStartToGoal);
};

#endif /* PATHPLANNER_H_ */
