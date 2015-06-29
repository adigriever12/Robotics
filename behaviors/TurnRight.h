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
        printf("right: %u\n", _robot->isRightFree());
        return _robot->isRightFree();
    }

    bool stopCond()
    {
        return _robot->isForwardFree();
    }

    void action()
    {
        _robot->setSpeed(0.0, -0.2);
    }

    virtual ~TurnRight();
};

#endif /* TURNRIGHT_H_ */
