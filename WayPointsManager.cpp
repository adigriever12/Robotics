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

bool WayPointsManager::IsClose(int y, int x, int y1, int x1) {
    //return ((x1 - 1 == x) || (x1 == x) || (y1 - 1 == y) || (y1 == y)
    //        || (x1 + 1 == x) || (y1 + 1 == y));
    int dX = abs(x - x1);
    int dY = abs(y - y1);
            
    return (sqrt((dX * dX) + (dY * dY)) < 3);
}

void WayPointsManager::deleteFromVec(vector<MapSearchNode*> &filtered_nodes,vector<MapSearchNode*> &new_nodes, int n)
{
    for (int i = 0; i < filtered_nodes.size(); i ++)
    {
        if (i != n)
        {
            new_nodes.push_back(filtered_nodes[i]);
        }
    }
}

//void WayPointsManager::NewNodes(vector<MapSearchNode*> &filtered_nodes) 
//{
//    vector<MapSearchNode*> new_nodes;
//    bool find;
//    for (int i = 0; i < filtered_nodes.size(); i++) 
//    {
//        if (!IsClose(filtered_nodes[i]->GetY(), filtered_nodes[i]->GetX(),
//                     filtered_nodes[i - 1]->GetY(), filtered_nodes[i - 1]->GetX()))
//        {
//            find = true;
//            MapSearchNode* node = new MapSearchNode(filtered_nodes[i - 1]->GetX(),filtered_nodes[i - 1]->GetY(), _map);
//            new_nodes.push_back(node);
////            vector<MapSearchNode*> new_nodes;
////            deleteFromVec(filtered_nodes, new_nodes, i);
////            filtered_nodes = new_nodes;
//        }
//        else if (!find)
//        {
//            MapSearchNode* node = new MapSearchNode(filtered_nodes[i]->GetX(),filtered_nodes[i]->GetY(), _map);
//            new_nodes.push_back(node);
////            vector<MapSearchNode*> new_nodes;
////            deleteFromVec(filtered_nodes, new_nodes, i - 1);
////            filtered_nodes = new_nodes;
//        }
//    }
//    
//    filtered_nodes = new_nodes;
//
//}

void WayPointsManager::NewNodes(vector<MapSearchNode*> &filtered_nodes) 
{
    vector<MapSearchNode*> new_nodes;
    
    new_nodes.push_back(filtered_nodes[0]);
    
    for (int i = 1; i < filtered_nodes.size() - 1; i++) 
    {
        int j = i;
        
        while ((j < filtered_nodes.size() - 1) &&
                (IsClose(filtered_nodes[j + 1]->GetY(), filtered_nodes[j + 1]->GetX(),
                       filtered_nodes[j]->GetY(), filtered_nodes[j]->GetX())))
        {
            j++;
        }
        
        new_nodes.push_back(filtered_nodes[i]);
        i = j;
    }
    
    new_nodes.push_back(filtered_nodes[filtered_nodes.size() - 1]);
    
    filtered_nodes = new_nodes;

}

void WayPointsManager::GetWayPointNodes(vector<MapSearchNode*> &filtered_nodes) {
    
    MapSearchNode* node = new MapSearchNode(_nodes[0]->GetY(), _nodes[0]->GetX(), _map);
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
            MapSearchNode* node = new MapSearchNode(_nodes[i + 1]->GetY(),_nodes[i + 1]->GetX(), _map);
            filtered_nodes.push_back(node);
        }
        
        
    }
    
    // add last node
    MapSearchNode* node1 = new MapSearchNode(_nodes[_nodes.size() - 1]->GetY(), _nodes[_nodes.size() - 1]->GetX(),_map);
    filtered_nodes.push_back(node1);
}
