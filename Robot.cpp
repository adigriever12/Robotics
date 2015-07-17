/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
        
        _pp->SetOdometry(2.175, -2.875, ((20 * M_PI) / 180));
        
        
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
