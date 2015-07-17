/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* pln, SDL2Wrapper* sdl) {
	_robot = robot;
	_curr = pln->getStartPoint();
        _sdl = sdl;
}
void Manager::run(vector<MapSearchNode*> waypoints)
{
	_robot->ReadAndUpdateLocalization();
	if(!(_curr->startCond()))
        {
            _curr = _curr->selectNext(waypoints[1]->GetX(), waypoints[1]->GetY());
            
            if (_curr->stopCond())
                return;
        }
	//	return;
        int i = 1;
        
	//_curr->action();
	while(_curr !=NULL)
	{
        
//            for (int i = 1; i < waypoints.size() - 1; i++)
            {
                int x = waypoints[i]->GetX();
                int y = waypoints[i]->GetY();
                _curr->setNextPoint(x, y);
                
                //while (!_robot->isAtWayPoint(x, y))
                //{
                while(_curr->stopCond() == false)
                {
                    _curr->action();
                    _robot->ReadAndUpdateLocalization();
                    _sdl->FlushChanges();
                }

                if (_curr->isAtWaypoint(x, y))
                {
                    std::cout << "We have reached (" << x << ", " << y << "), moving to next WP!" << std::endl;
                    i++;
                    
                    _curr->setNextPoint(waypoints[i]->GetX(), waypoints[i]->GetY());
                }

                if (!_curr->startCond())
                {
                    _curr = _curr->selectNext(waypoints[i]->GetX(), 
                                              waypoints[i]->GetY());
                }       
                
                _robot->ReadAndUpdateLocalization();
                //}
            }
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
