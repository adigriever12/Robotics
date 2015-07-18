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
        //printf("forward free: %u\n", _robot->isForwardFree());
        
        int mapwidth = ConfiguraionManager::MapWidth;
        int mapheight = ConfiguraionManager::MapHeight;
        double mapresolution = ConfiguraionManager::MapResolutionCM;
        int gridresolution = ConfiguraionManager::GridResolutionCM;
            
        int calcx = (((mapwidth * mapresolution) / 2) + (_robot->GetX() * 100)) / gridresolution;
        int _realX = ceil(calcx);
        int calcy = (((mapheight * mapresolution) / 2) - (_robot->GetY() * 100)) / gridresolution;
        int _realY = ceil(calcy) * (-1);

//        std::cout << "isAtWayPoint parameters: " << _realX << " " << _realY << std::endl << std::flush;
//        std::cout << "isAtWayPoint parameters: robot: " << _robot->GetX() << " " << _robot->GetY() << std::endl << std::flush;
//        std::cout << "right cost: " << abs(calc_right_cost()) << std::endl;
//        std::cout << "left cost: " << abs(calc_left_cost()) << std::endl << std::flush;
        //std::cout << "Is it a forward angle? " << ((abs(calc_right_cost()) < (M_PI / 12)) || abs(calc_left_cost()) < (M_PI / 12)) << std::endl;
        
        bool fIsForwardsAngle = ((abs(calc_right_cost()) < (M_PI / 12)) || abs(calc_left_cost()) < (M_PI / 12));
	bool fGoForward = (_robot->isForwardFree() && 
                (!isAtWaypoint(_realX, _realY)) && 
                fIsForwardsAngle);
        
        //std::cout << "Should I go forward? " << fGoForward << std::endl;
        
        return (fGoForward);
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

