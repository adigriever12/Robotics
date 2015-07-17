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

//PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) {
//	//Creating Behaviors
////	_beh[0] = new A(robot);
////	_beh[1] = new B(robot);
////	_beh[2] = new C(robot);
//
//	//Connecting Behaviors
//	_beh[0]->addBeh(_beh[1]);
//	_beh[0]->addBeh(_beh[2]);
//	_beh[1]->addBeh(_beh[2]);
//	_beh[2]->addBeh(_beh[0]);
//	_start = _beh[0];
//}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	for(int i=0 ; i < _behaviours.size() ; i++) {	
            delete _behaviours[i];
        }
}
