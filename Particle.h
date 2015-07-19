#ifndef PARTICLE_H
#define	PARTICLE_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ConfiguraionManager.h"
using namespace std;

#include "Map.h"
#include "Convert.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc; 
#define NORMAL_BREED 5
#define HIGH_BREED 20
#define MAX_PARTICLES_COUNT 200
#define EXPANSION_RADIUS 0.3
#define YAW_RANGE 0.2
#define LOW_BELIEF_MIN 0.2
#define HIGH_BELIEF_MIN 0.7
#define BELIEF_MAGIC_NUMBER 2
#define PARTICLE_LIFES_NUM 5
#define EMERGENCY_EXPANSION_RADIUS EXPANSION_RADIUS * 2
#define EMERGENCY_YAW_RANGE YAW_RANGE * 2
#define PARTICLE_EMERGENCY_BREED MAX_PARTICLES_COUNT - 2
#define DEFAULT_WAYPOINT_RESOLUTION 6
#define DEFAULT_WAYPOINT_ACCURACY (0.1F)
#define WAYPOINT_RADIUS 4
#define DETECT_EVASION_RADIUS 0.6

class Particle {
	float _X_delta;
	float _Y_delta;
	float _Yaw_delta;
	float _belief;
	
	int _lifes;
	int _age;
	
	float Random(float min, float max);
	float ProbabilityByMovement(float X_delta, float Y_delta, float Yaw_delta);
	float ProbabilityByLaserScan(float X_delta, float Y_delta, float Yaw_delta, Map* map, LaserProxy* lp);
	
public:
	Particle(float X_delta, float Y_delta, float Yaw_delta, float belief);
	virtual ~Particle();
        float GetX();
	float GetY();
	float GetYaw();
	float GetBelif();
	Particle* CreateChild();
	Particle* CreateChild(float expansion_radius, float yaw_range);
	void Update(float X_delta, float Y_delta, float Yaw_delta, Map* map, LaserProxy* lp);
	void IncreaseAge();
	int Age();
	void DecreaseLife();
	bool IsDead();
	
private:

};

#endif	/* PARTICLE_H */