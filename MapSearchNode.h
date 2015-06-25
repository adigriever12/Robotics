/*
 * MapSearchNode.h
 *
 *  Created on: Jun 5, 2015
 *      Author: colman
 */

#ifndef MAPSEARCHNODE_H_
#define MAPSEARCHNODE_H_

#include "stlastar.h"
#include "Map.h"

class MapSearchNode {
	Map* _map;
	int _x;
	int _y;
public:
    MapSearchNode() {
        _map = NULL;
        _x = _y = 0;
    };

    MapSearchNode(int x, int y, Map* map) {
        _map = map;
		SetPosition(x, y);
    }

    virtual ~MapSearchNode();

    int GetX() { return _x; }
    int GetY() { return _y; }

    void SetPosition(int x, int y) {
        _x = x;
        _y = y;
    }

	// Distance between current node (this.) and the last node (goal)
    float GoalDistanceEstimate(MapSearchNode &nodeGoal);
    
	// Check if current node (this) is the goal node
	bool IsGoal(MapSearchNode &nodeGoal);
	
	// Create and add all possible nodes you can move to from current node
    bool GetSuccessors(AStarSearch<MapSearchNode>* aStarSearch, MapSearchNode* parentNode);
	
	// Add new successor (node) - helper method to GetSuccessors
    bool AddSuccessor(int currentX, int currentY, int parentX, int parentY, AStarSearch<MapSearchNode>* aStarSearch);
	
	// Get cost to move from current node to the successor (node)
    float GetCost(MapSearchNode &successor);
	
	// Same state in our world (grid) is simply when both nodes in the same position
    bool IsSameState(MapSearchNode &node);
};

#endif /* MAPSEARCHNODE_H_ */
