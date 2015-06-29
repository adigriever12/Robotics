/*
 * PlnObstacleAvoid.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_
#include "Plan.h"
#include <vector>

#include "Forward.h"
#include "TurnLeft.h"
#include "../behaviors/TurnRight.h"

//#include "../behaviors/A.h"
//#include "../behaviors/B.h"
//#include "../behaviors/C.h"

class PlnObstacleAvoid: public Plan {
    vector<Behavior*> _behaviours;

public:
	PlnObstacleAvoid(Robot* robot);
	Behavior* getStartPoint(){return _start;}
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
