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
#include "LocalizationManager.h"

using namespace PlayerCc;
class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
        LocalizationManager* _localization;
        
        int _realX;
        int _realY;
        
        double _dX;
	double _dY;
	double _dYaw;
        
        void UpdateLocalization();
	double SetPosition(double dX, double dY, double dYaw, bool setOdemetry);
	void SetOdemetry(double dX, double dY, double dYaw);
        
public:
	Robot(char* ip, int port, LocalizationManager* localization);
        void ReadAndUpdateLocalization();
        void SetOdometryByPixelCoord(double dX, double dY, double dYaw, double resolution, double mapWidth, double mapHeight);
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
            //return _pp->GetYaw();
            //printf("robot Yaw: %f\n", _dYaw);
            return _dYaw;
        }
        
        double GetX() {
            //return _pp->GetXPos();
            //printf("robot X: %f\n", _dX);
            return _dX;
        }
        
        double GetY() {
            //return _pp->GetYPos();
            //printf("robot Y: %f\n", _dY);
            return _dY;
        }
        
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
