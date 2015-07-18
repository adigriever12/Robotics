/* 
 * File:   Particle.h
 * Author: colman
 *
 * Created on June 12, 2015, 12:43 PM
 */

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
#define LOW_BELIF_THRESHOLD 0.2 // minimum for low belif particles
#define HIGH_BELIF_THRESHOLD 0.7 // minimum for high belif particles
#define PARTICLE_NORMAL_BREED 5 // particles child breed count for particles with normal belif
#define PARTICLE_HIGH_BREED 20 // particles child breed count for particles with high belif
#define MAX_PARTICLES_COUNT 200 // max particles count
#define EXPANSION_RADIUS 0.3 // expansion radius for each child particle
#define YAW_RANGE 0.2 // yaw range for each child particle
#define BELIF_MAGIC_NUMBER 2 // belif magic number
#define PARTICLE_LIFES 5 // particles lifes before deleted from vector
#define EMERGENCY_EXPANSION_RADIUS EXPANSION_RADIUS * 2 // emergency expansion radius when no particles exists
#define EMERGENCY_YAW_RANGE YAW_RANGE * 2 // emergency yaw range when no particles exists
#define PARTICLE_EMERGENCY_BREED MAX_PARTICLES_COUNT - 2 // Particles emergency breed count when no particles exists

// Waypoint Manager
#define WAYPOINT_RADIUS 4
#define DEFAULT_WAYPOINT_RESOLUTION 6
#define DEFAULT_WAYPOINT_ACCURACY (0.1F)
#define DETECT_EVASION_RADIUS 0.6

class Particle {
	float _dX;
	float _dY;
	float _dYaw;
	float _dBel;
	
	int _lifes;
	int _age;
	
	float Randomize(float dMin, float dMax);
	float ProbabilityByMovement(float deltaX, float deltaY, float deltaYaw);
	float ProbabilityByLaserScan(float dX, float dY, float dYaw, Map* map, SDL2Wrapper* sdl, LaserProxy* lp, bool shouldDraw);
	
public:
	Particle(float dX, float dY, float dYaw, float dBel);
	virtual ~Particle();
	
	Particle* CreateChild();
	Particle* CreateChild(float dExpansionRadius, float dYawRange);
	void Update(float dX, float dY, float dYaw, Map* map, SDL2Wrapper* sdl, LaserProxy* lp);
	void DrawLaserScan(Map* map, SDL2Wrapper* sdl, LaserProxy* lp);
        
	float GetX();
	float GetY();
	float GetYaw();
	float GetBelif();
	
	void IncreaseAge();
	int Age();
	void DecreaseLife();
	bool IsDead();
	
private:

};

#endif	/* PARTICLE_H */