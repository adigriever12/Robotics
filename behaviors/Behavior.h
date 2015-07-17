/*
 * Behavior.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#include <vector>
#include "../Robot.h"
#include <math.h>

using namespace std;

class Behavior {
	vector<Behavior*> _behVect;
protected:
	Robot* _robot;
        int _NextPointX;
        int _NextPointY;
public:
	Behavior(Robot* robot);
	virtual ~Behavior();
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
        
        void setNextPoint(int x, int y) { _NextPointX = x; _NextPointY = y; }
        
        int getNextPointX() {
            return _NextPointX;
        }
        
        int getNextPointY() {
            return _NextPointY;
        } 
        
	void addBeh(Behavior* next)
	{
		_behVect.push_back(next);
	}
	Behavior* selectNext(int x, int y)
	{
            for (int i = 0; i < _behVect.size(); i++)
            {
                _behVect[i]->setNextPoint(x, y);
                
                if (_behVect[i]->startCond()) {
                    return _behVect[i];
                }
            }
	}
        
        void double_mod(double& val)
        {
            if (val < 0)
            {
                val += (2 * M_PI);
            }		
            else if (val >= (2 * M_PI))
            {		
                while (val > (2 * M_PI))
                {
                    val -= (2 * M_PI);
                }
            }
        }
        
        double calc_right_cost()
        {
            double current_angle = _robot->GetYaw();

            int calcx = (((550 * 2.5) / 2) + _robot->GetX() * 100) / 10;
            int curr_x = ceil(calcx);
            int calcy = (((380 * 2.5) / 2) - _robot->GetY() * 100) / 10;
            int curr_y = ceil(calcy) * (-1);
            int target_x = _NextPointX;
            int target_y = _NextPointY * (-1);

            
            double target_angle = atan2(target_y - curr_y, target_x - curr_x);
            
            if (current_angle < 0)
            {
                current_angle = ((2 * M_PI) + current_angle);
            }
            
            double m = -99;
            
            if (target_x != curr_x)
            {
                m = (target_y - curr_y) / (target_x - curr_x);
            }
            
         //   std::cout << "current angle: " << current_angle << std::endl << std::flush;
          //  std::cout << "target angel: " << target_angle << std::endl << std::flush;
            
           // printf("Going from (%u, %u) to (%u, %u) with grad %f\n",
            //        curr_x, curr_y * -1, target_x, target_y * -1, m);
            
            double right_cost = current_angle - target_angle;
          //  double full_right_cost = ((right_cost < 0) ? ((2 * M_PI) + right_cost) : right_cost);
            
            double_mod(right_cost);
            
            return (right_cost);
        }
        
        double calc_left_cost() 
        {
            double left_cost = (2 * M_PI) - calc_right_cost();
            //double full_left_cost = ((left_cost < 0) ? ((2 * M_PI) + left_cost) : left_cost);
            double_mod(left_cost);
            
            return (left_cost);
        }
        
        bool isAtWaypoint(int x, int y)
        {
            int calcx = (((550 * 2.5) / 2) + _robot->GetX() * 100) / 10;
            int curr_x = ceil(calcx);
            int calcy = (((380 * 2.5) / 2) - _robot->GetY() * 100) / 10;
            int curr_y = ceil(calcy);
            
            int dX = abs(_NextPointX - curr_x) * 10;
            int dY = abs((_NextPointY) - curr_y) * 10;

            printf("(%d, %d), (%d, %d) Distance to next WP <%u, %u>: %f\n",curr_x, curr_y, _NextPointX, _NextPointY, dX, dY, sqrt((dX * dX) + (dY * dY)));
            return (sqrt((dX * dX) + (dY * dY)) < 20);
        }
};

#endif /* BEHAVIOR_H_ */
