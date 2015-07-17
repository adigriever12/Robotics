/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include <math.h>
#include <stdio.h>

using namespace PlayerCc;
class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
        int _realX;
        int _realY;
public:
	Robot(char* ip, int port);
        
//        bool isAtWayPoint(int x, int y) {
//            int calcx = (700 + _pp->GetXPos() * 100) / 2.5 / 10;
//            int _realX = ceil(calcx);
//            int calcy = (700 + _pp->GetYPos() * 100) / 2.5 / 10;
//            int _realY = ceil(calcy);
//            
//            return (x == _realX && y == _realY);
//        }
        
	void Read() {
		_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		_pp->SetSpeed(xSpeed, angularSpeed);
	}
	bool isRightFree() {
		if ((*_lp)[50] > 0.35 && (*_lp)[75] > 0.35 && (*_lp)[100] > 0.35)
			return true;
		else
			return false;
	}
        bool isLeftFree() {
		if ((*_lp)[615] > 0.35 && (*_lp)[590] > 0.35 && (*_lp)[565] > 0.35)
			return true;
		else
			return false;
	}
	bool isForwardFree() {
		if ((*_lp)[282] > 0.4 && (*_lp)[332] > 0.4 && (*_lp)[382] > 0.4)
			return true;
		else
			return false;
	}
        
        double GetYaw() {
            return _pp->GetYaw();
        }
        
        double GetX() {
            return _pp->GetXPos();
        }
        
        double GetY() {
            return _pp->GetYPos();
        }
        
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
