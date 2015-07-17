/* 
 * File:   Particle.cpp
 * Author: colman
 * 
 * Created on June 12, 2015, 12:43 PM
 */

#include "Particle.h"

Particle::Particle(float dX, float dY, float dYaw, float dBel) {
	_dX = dX;
	_dY = dY;
	_dYaw = dYaw;
	_dBel = dBel;
	
	_lifes = PARTICLE_LIFES;
	_age = 1;
}

Particle::~Particle() {
}

Particle* Particle::CreateChild() {
	return CreateChild(EXPANSION_RADIUS, YAW_RANGE);
}

Particle* Particle::CreateChild(float dExpansionRadius, float dYawRange) {
	float newX = _dX + Randomize(-dExpansionRadius, dExpansionRadius);
	float newY = _dY + Randomize(-dExpansionRadius, dExpansionRadius);
	float newYaw = _dYaw + Randomize(-dYawRange, dYawRange);
	return new Particle(newX, newY, newYaw, 1);
}

void Particle::Update(float deltaX, float deltaY, float deltaYaw, Map* map, LaserProxy* lp) {
	_dX += deltaX;
	_dY += deltaY;
	_dYaw += deltaYaw;
	
	// Calculate new belif value from prediction belif, laser scan and the belif magic number
	float predictionBelif = ProbabilityByMovement(deltaX, deltaY, deltaYaw) * _dBel;
	float probabilityByScan = ProbabilityByLaserScan(_dX, _dY, _dYaw, map, lp);
	_dBel = probabilityByScan * predictionBelif * BELIF_MAGIC_NUMBER;
	
	if (_dBel > 1)
		_dBel = 1;
}

float Particle::GetBelif() {
	return _dBel;
}

float Particle::GetX() {
	return _dX;
}

float Particle::GetY() {
	return _dY;
}

float Particle::GetYaw() {
	return _dYaw;
}

float Particle::Randomize(float dMin, float dMax) {
	float num = (float)rand() / RAND_MAX;
	return dMin + num * (dMax - dMin);
}

float Particle::ProbabilityByMovement(float deltaX, float deltaY, float deltaYaw) {
	
	float distance = sqrt(pow(deltaX,2) + pow(deltaY,2));
	
	/*
	 * Welcome to magic numbers section - this one need a refactoring
	 * Any good ideas how to make it better?
	 */
	
//	if (deltaYaw > 0.5)
//		return 0;
//	
//	if (deltaYaw > 0.3)
//		return 0.1;
//	
//	if (deltaYaw > 0.2)
//		return 0.2;
	
	if (distance < 0.1)
		return 1;
	
	if (distance < 0.2)
		return 0.9;
	
	if (distance < 0.4)
		return 0.7;
	
	if (distance < 0.5)
		return 0.5;
	
	if (distance < 0.7)
		return 0.3;
	
	return 0.1;
}

float Particle::ProbabilityByLaserScan(float dX, float dY, float dYaw, Map* map, LaserProxy* lp) {
	// Convert relative obstacle position to our valid map position
	float resolution = (map->GetPixelResolution()) / 100;
	float mapWidth = map->GetMapWidth();
	float mapHeight = map->GetMapHeight();
        
	float x = Convert::RobotRelativeXPosToPixelXCoord(dX, resolution, mapWidth);
	float y = Convert::RobotRelativeYPosToPixelYCoord(dY, resolution, mapHeight);
        
        int xCoord = floor(x / 4);
        int yCoord = floor(y / 4);
        
	// Check if current position is a valid position before continue
	if (x < 0 || (x) >= map->GetMapWidth() ||
			y < 0 || (y) >= map->GetMapHeight()) {
		return 0;
	}
        
	int** grid = map->GetGrid();
	
        if (grid[yCoord][xCoord] != 0)
        {
            return 0;
        }
        
	int scans = lp->GetCount();
	float maxRange = lp->GetMaxRange();
			
	float totalHits = 0;
	float correctHits = 0;
	int boundary_misses = 0;
        
	for(int i=0; i<scans; i++) {
		float range = lp->GetRange(i);
		
		if (range < maxRange) {
			totalHits++;
			
			// Calculate obstacle position
			float bearing = lp->GetBearing(i);
			float dObstacleX = dX + range * cos(dYaw + bearing);
			float dObstacleY = dY + range * sin(dYaw + bearing);
			
			dObstacleX = Convert::RobotRelativeXPosToPixelXCoord(dObstacleX, resolution, mapWidth);
			dObstacleY = Convert::RobotRelativeYPosToPixelYCoord(dObstacleY, resolution, mapHeight);
			
			// Check bounds before actually trying to get cell
			if ((dObstacleX) < 0 || (dObstacleX) >= map->GetMapWidth() ||
					dObstacleY < 0 || (dObstacleY) >= map->GetMapHeight()) {
			boundary_misses++;	
                            continue;
			}
                        
                        xCoord = floor(dObstacleX / 4);
                        yCoord = floor(dObstacleY / 4);
                        
                        if (grid[yCoord][xCoord] != 0)
                        {
//                            printf("Correct hits incremented %f ->", correctHits);
                            correctHits++;
//                            printf("%f\n", correctHits);
                        }
                        else
                        {
//                            printf("Oh noes, no hit at (%u, %u)\n", xCoord, yCoord);
                        }
		}
	}
	
	float accuracy = correctHits / totalHits;
//	printf("Particle accuracy: %f\n", accuracy);
	return accuracy;
}

void Particle::IncreaseAge() {
	_age++;
}

int Particle::Age() {
	return _age;
}


void Particle::DecreaseLife() {
	_lifes--;
}

bool Particle::IsDead() {
	return _lifes <= 0;
}