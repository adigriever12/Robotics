/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlnObstacleAvoid.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) : Plan(robot)
{
    Forward* forward = new Forward(robot);
    TurnLeft* left = new TurnLeft(robot);
    TurnRight* right = new TurnRight(robot);
    
    forward->addBeh(right);
    forward->addBeh(left);
    left->addBeh(forward);
    left->addBeh(right);
    right->addBeh(forward);
    right->addBeh(left);
    
    _behaviours.push_back(forward);
    _behaviours.push_back(left);
    _behaviours.push_back(right);
    _start = forward;
}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	for(int i=0 ; i < _behaviours.size() ; i++) {	
            delete _behaviours[i];
        }
}
