/*
 * MapSearchNode.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: colman
 */

#include "MapSearchNode.h"
#include <math.h>

MapSearchNode::~MapSearchNode() {
}

float MapSearchNode::GoalDistanceEstimate(MapSearchNode &nodeGoal) {
    float deltaX = fabs((float)GetX() - (float)nodeGoal.GetY());
    float deltaY = fabs((float)GetX() - (float)nodeGoal.GetY());

    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

bool MapSearchNode::IsGoal(MapSearchNode &nodeGoal) {
    return (GetX() == nodeGoal.GetX() &&
            GetY() == nodeGoal.GetY());
}

bool MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode>* aStarSearch, MapSearchNode* parentNode) {
    int parentX = -1, parentY = -1;

    if (parentNode) {
            parentX = parentNode->GetX();
            parentY = parentNode->GetY();
    }

    // Top Cell
    AddSuccessor(GetX(), GetY() - 1, parentX, parentY, aStarSearch);

    // Bottom Cell
    AddSuccessor(GetX(), GetY() + 1, parentX, parentY, aStarSearch);

    // Left Cell
    //AddSuccessor(GetX() - 1, GetY(), parentX, parentY, aStarSearch);

    // Right Cell
    AddSuccessor(GetX() + 1, GetY(), parentX, parentY, aStarSearch);

    // Add 4 more directions if needed
    AddSuccessor(GetX() + 1, GetY() + 1, parentX, parentY, aStarSearch);
    AddSuccessor(GetX() - 1, GetY() - 1, parentX, parentY, aStarSearch);
    AddSuccessor(GetX() + 1, GetY() - 1, parentX, parentY, aStarSearch);
    AddSuccessor(GetX() - 1, GetY() + 1, parentX, parentY, aStarSearch);

    return true;
}

bool MapSearchNode::AddSuccessor(int currentX, int currentY, int parentX, int parentY, AStarSearch<MapSearchNode>* aStarSearch) {
    float weight = _map->GetCellWeight(currentX, currentY);

    // Add the cell as a successor (new node you can move to) if it's valid
    if (weight != -1 &&
            !(currentX == parentX &&
                currentY == parentY) && _map->IsPassable(weight)) {
        MapSearchNode newNode = MapSearchNode(currentX, currentY, _map);
        aStarSearch->AddSuccessor(newNode);
        return true;
    }

    return false;
}

float MapSearchNode::GetCost(MapSearchNode &successor) {
	return _map->GetCellWeight(successor.GetX(), successor.GetY());
}

bool MapSearchNode::IsSameState(MapSearchNode& searchNode) {
    // Same state in our world (grid) is simply when both nodes in the same position
    return (GetX() == searchNode.GetX() &&
            GetY() == searchNode.GetY());
}
