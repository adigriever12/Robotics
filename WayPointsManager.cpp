/* 
 * File:   WayPointsManager.cpp
 * Author: colman
 * 
 * Created on June 27, 2015, 10:24 PM
 */

#include "WayPointsManager.h"

WayPointsManager::WayPointsManager(vector<MapSearchNode*> nodes, Map* map) {
    _nodes = nodes;
    _map = map;
}

WayPointsManager::WayPointsManager(const WayPointsManager& orig) {
}

WayPointsManager::~WayPointsManager() {
}

void WayPointsManager::GetWayPointNodes(vector<MapSearchNode*> &filtered_nodes) {
    
    MapSearchNode* node = new MapSearchNode(_nodes[0]->GetX(), _nodes[0]->GetY(), _map);
    filtered_nodes.push_back(node);
    
    for (int i = 0; i < _nodes.size() - 2; i++)
    {   
        double incline_calc1 = -99;
        double incline_calc2 = -99;
        
        if (_nodes[i + 1]->GetX() != _nodes[i]->GetX())
        {
            incline_calc1 = (_nodes[i + 1]->GetY() - _nodes[i]->GetY()) / (_nodes[i + 1]->GetX() - _nodes[i]->GetX());
        }
        
        if (_nodes[i + 2]->GetX() != _nodes[i + 1]->GetX())
        {
            incline_calc2 = (_nodes[i + 2]->GetY() - _nodes[i + 1]->GetY()) / (_nodes[i + 2]->GetX() - _nodes[i + 1]->GetX());
        }
        
        double result1 = atan(incline_calc1);
        double result2 = atan (incline_calc2);
        
        if (result1 != result2)
        {
            MapSearchNode* node = new MapSearchNode(_nodes[i + 1]->GetX(), _nodes[i + 1]->GetY(), _map);
            filtered_nodes.push_back(node);
        }
        
        // add last node
        MapSearchNode* node = new MapSearchNode(_nodes[_nodes.size() - 1]->GetX(), _nodes[_nodes.size() - 1]->GetY(), _map);
        filtered_nodes.push_back(node);
    }
}
