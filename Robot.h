/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;
class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Robot(char* ip, int port);
	void Read() {
		_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		_pp->SetSpeed(xSpeed, angularSpeed);
	}
	bool isRightFree() {
		if ((*_lp)[50] > 0.7 && (*_lp)[75] > 0.7 && (*_lp)[100] > 0.7)
			return true;
		else
			return false;
	}
        bool isLeftFree() {
		if ((*_lp)[615] > 0.7 && (*_lp)[590] > 0.7 && (*_lp)[565] > 0.7)
			return true;
		else
			return false;
	}
	bool isForwardFree() {
		if ((*_lp)[282] > 0.7 && (*_lp)[332] > 0.7 && (*_lp)[382] > 0.7)
			return true;
		else
			return false;
	}
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
