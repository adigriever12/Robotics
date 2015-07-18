#ifndef PARTICLE_H
#define	PARTICLE_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDL2Wrapper.h"
#include "Debug.h"
#include "ConfiguraionManager.h"
using namespace std;

#include "Map.h"
#include "Convert.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc; 
#define NORMAL_BREED 5 // particles child breed count for particles with normal belif
#define HIGH_BREED 20 // particles child breed count for particles with high belif
#define MAX_PARTICLES_COUNT 200 // max particles count
#define EXPANSION_RADIUS 0.3 // expansion radius for each child particle
#define YAW_RANGE 0.2 // yaw range for each child particle
#define LOW_BELIEF_MIN 0.2 // minimum for low belif particles
#define HIGH_BELIEF_MIN 0.7 // minimum for high belif particles
#define BELIEF_MAGIC_NUMBER 2 // belif magic number
#define PARTICLE_LIFES_NUM 5 // particles lifes before deleted from vector
#define EMERGENCY_EXPANSION_RADIUS EXPANSION_RADIUS * 2 // emergency expansion radius when no particles exists
#define EMERGENCY_YAW_RANGE YAW_RANGE * 2 // emergency yaw range when no particles exists
#define PARTICLE_EMERGENCY_BREED MAX_PARTICLES_COUNT - 2 // Particles emergency breed count when no particles exists

// Waypoint Manager
#define WAYPOINT_RADIUS 4
#define DEFAULT_WAYPOINT_RESOLUTION 6
#define DEFAULT_WAYPOINT_ACCURACY (0.1F)
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
	float ProbabilityByLaserScan(float X_delta, float Y_delta, float Yaw_delta, Map* map, SDL2Wrapper* sdl, LaserProxy* lp, bool shouldDraw);
	
public:
	Particle(float X_delta, float Y_delta, float Yaw_delta, float belief);
	virtual ~Particle();
        float GetX();
	float GetY();
	float GetYaw();
	float GetBelif();
	Particle* CreateChild();
	Particle* CreateChild(float expansion_radius, float yaw_range);
	void Update(float X_delta, float Y_delta, float Yaw_delta, Map* map,SDL2Wrapper* sdl, LaserProxy* lp);
	void DrawLaserScan(Map* map, SDL2Wrapper* sdl, LaserProxy* lp);
	void IncreaseAge();
	int Age();
	void DecreaseLife();
	bool IsDead();
	
private:

};

#endif	/* PARTICLE_H */