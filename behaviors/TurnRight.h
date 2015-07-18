/*
 * TurnRight.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef TURNRIGHT_H_
#define TURNRIGHT_H_

#include "Behavior.h"

class TurnRight: public Behavior {
public:
    TurnRight(Robot* robot);
        
    bool startCond()
    {
        //printf("right is free: %u right cost: %f\n", _robot->isRightFree(), calc_right_cost());
        double cost = calc_right_cost();
        return ((_robot->isRightFree()) && (abs(cost) < M_PI) && (abs(cost) > (M_PI / 48)));
    }

    bool stopCond()
    {
        return !startCond();
    }

    void action()
    {
        _robot->setSpeed(0.0, -0.2);
    }

    virtual ~TurnRight();
};

#endif /* TURNRIGHT_H_ */
