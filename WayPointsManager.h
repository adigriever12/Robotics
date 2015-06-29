/* 
 * File:   WayPointsManager.h
 * Author: colman
 *
 * Created on June 27, 2015, 10:24 PM
 */

#ifndef WAYPOINTSMANAGER_H
#define	WAYPOINTSMANAGER_H
#define PI 3.14159265
#include "MapSearchNode.h"
#include "Map.h"
#include <math.h>

class WayPointsManager {
public:
    WayPointsManager(vector<MapSearchNode*> nodes, Map* map);
    WayPointsManager(const WayPointsManager& orig);
    virtual ~WayPointsManager();
    void GetWayPointNodes(vector<MapSearchNode*> &filtered_nodes);
private:
    vector<MapSearchNode*> _nodes;
    Map* _map;
};

#endif	/* WAYPOINTSMANAGER_H */

