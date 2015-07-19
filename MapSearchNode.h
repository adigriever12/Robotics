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

    float GoalDistanceEstimate(MapSearchNode &nodeGoal);
    
    bool IsGoal(MapSearchNode &nodeGoal);
	
    bool GetSuccessors(AStarSearch<MapSearchNode>* aStarSearch, MapSearchNode* parentNode);
	
    bool AddSuccessor(int currentX, int currentY, int parentX, int parentY, AStarSearch<MapSearchNode>* aStarSearch);
	
    float GetCost(MapSearchNode &successor);

    bool IsSameState(MapSearchNode &node);
};

#endif /* MAPSEARCHNODE_H_ */
