#ifndef LOCALIZATIONMANAGER_H
#define	LOCALIZATIONMANAGER_H

#include <vector>
using namespace std;

#include "typedefs.h"
#include "Particle.h"
#include "Map.h"
#include "Convert.h"
#include "Debug.h"

class LocalizationManager {
	Map* _map;
	vector<Particle*> _particles;
	SDL2Wrapper* _sdl;
        
	float _X_delta;
	float _Y_delta;
	float _Yaw_delta;
	
        // Transfer childs vector to the main particles vector as new future parents
	void ChildsToParticles(vector<Particle*> childs);
        
	// Fill in the childs vector with new childs from the parent particle
	void BreedParticle(Particle* particle, int dwChildCount, vector<Particle*>& childs);
	void BreedParticle(Particle* particle, int dwChildCount, float dExpansionRadius, float dYawRange, vector<Particle*>& childs);
	
	
public:
           // Create new particle and breed him with max childs count
	bool CreateParticle(float X_delta, float Y_delta, float Yaw_delta, float Belief);
	bool CreateParticle(float X_delta, float Y_delta, float Yaw_delta, float Belief, float Expansion_Radius, float Yaw_Range, int childsCount);

	LocalizationManager(Map* map, SDL2Wrapper* sdl);
	virtual ~LocalizationManager();
	
	// Update all particles with new position and breed or kill if necessary
	void Update(float deltaX, float deltaY, float deltaYaw, LaserProxy* lp);
	
	// Get the best particle that represent the actual robot position
	Particle* BestParticle();
	
	private:

};

#endif	/* LOCALIZATIONMANAGER_H */