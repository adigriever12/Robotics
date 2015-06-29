/* 
 * File:   Forward.h
 * Author: colman
 *
 * Created on June 29, 2015, 6:05 AM
 */

#ifndef FORWARD_H
#define	FORWARD_H

#include "../behaviors/Behavior.h"

class Forward: public Behavior {
public:
    Forward(Robot* robot);
    
    bool startCond()
    {
        printf("forward: %u\n", _robot->isForwardFree());
	return _robot->isForwardFree();
    }
    
    bool stopCond()
    {
	return !startCond();
    }

    void action()
    {
        _robot->setSpeed(0.2, 0);
    }
    
    virtual ~Forward();
};

#endif	/* FORWARD_H */

