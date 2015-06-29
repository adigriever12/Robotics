/* 
 * File:   TurnLeft.h
 * Author: colman
 *
 * Created on June 29, 2015, 6:01 AM
 */

#ifndef TURNLEFT_H
#define	TURNLEFT_H

#include "../behaviors/Behavior.h"

class TurnLeft: public Behavior {
public:
    
    TurnLeft(Robot* robot);
    
    bool startCond()
    {
        printf("left: %u\n", _robot->isLeftFree());
	return _robot->isLeftFree();
    }
    
    bool stopCond()
    {
	return _robot->isForwardFree();
    }

    void action()
    {
	_robot->setSpeed(0.0, 0.2);
    }
    
    virtual ~TurnLeft();
};

#endif	/* TURNLEFT_H */

