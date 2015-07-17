/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/PlnObstacleAvoid.h"
#include "Robot.h"
#include "MapSearchNode.h"
#include "SDL2Wrapper.h"

class Manager {
	Behavior* _curr;
	Robot* _robot;
        SDL2Wrapper* _sdl;
        
public:
	Manager(Robot* robot, Plan* pln, SDL2Wrapper* sdl);
	void run(vector<MapSearchNode*> waypoints);
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
