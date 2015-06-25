/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(int startX, int startY, int goalX, int goalY, Map* map) {
	_aStarAlgorithm = new AStarSearch<MapSearchNode>(MAX_NODES_COUNT);
	MapSearchNode startNode(startX, startY, map);
	MapSearchNode goalNode(goalX, goalY, map);
	_aStarAlgorithm->SetStartAndGoalStates(startNode, goalNode);
}

PathPlanner::~PathPlanner() {
	// TODO Auto-generated destructor stub
}

void PathPlanner::GetAStarNodes(vector<MapSearchNode*> &nodesFromStartToGoal)
{
	unsigned int searchState;

	do	{
			searchState = _aStarAlgorithm->SearchStep();
		} while (searchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

	// Get the actual path from start and goal nodes

	if (searchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
		int nodes = 1;
		MapSearchNode *node = _aStarAlgorithm->GetSolutionStart();
		nodesFromStartToGoal.push_back(node);

		for (;;) {
			node = _aStarAlgorithm->GetSolutionNext();

			if (!node) {
				break;
			}

			nodes++;
			nodesFromStartToGoal.push_back(node);
		}

		printf("Path made of %d nodes.\n", nodes);
	} else {
		printf("Search terminated after. Didn't find goal.\n");
	}
}



