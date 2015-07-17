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
        double cost = calc_left_cost();
	printf("left is free: %u left cost: %f\n", _robot->isLeftFree(), cost);
        return ((_robot->isLeftFree()) && (abs(cost) < M_PI) && (abs(cost) > (M_PI / 48)));
    }
    
    bool stopCond()
    {
	return !startCond();
    }

    void action()
    {
	_robot->setSpeed(0.0, 0.2);
    }
    
    virtual ~TurnLeft();
};

#endif	/* TURNLEFT_H */

