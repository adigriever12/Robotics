#ifndef LOCALIZATIONMANAGER_H
#define	LOCALIZATIONMANAGER_H

#include <vector>
using namespace std;

#include "typedefs.h"
#include "Particle.h"
#include "Map.h"
#include "Convert.h"

class LocalizationManager {
	Map* _map;
	vector<Particle*> _particles;
        
	float _X_delta;
	float _Y_delta;
	float _Yaw_delta;

	void ChildsToParticles(vector<Particle*> childs);
	void BreedParticle(Particle* particle, int dwChildCount, vector<Particle*>& childs);
	void BreedParticle(Particle* particle, int dwChildCount, float dExpansionRadius, float dYawRange, vector<Particle*>& childs);
	
public:        
	bool CreateParticle(float X_delta, float Y_delta, float Yaw_delta, float Belief);
	bool CreateParticle(float X_delta, float Y_delta, float Yaw_delta, float Belief, float Expansion_Radius, float Yaw_Range, int childsCount);

	LocalizationManager(Map* map);
	virtual ~LocalizationManager();
	void Update(float deltaX, float deltaY, float deltaYaw, LaserProxy* lp);
	Particle* BestParticle();
	
	private:

};

#endif	/* LOCALIZATIONMANAGER_H */