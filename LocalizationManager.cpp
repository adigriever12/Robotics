#include "LocalizationManager.h"
#include <ctime>

LocalizationManager::LocalizationManager(Map* map) {
	_map = map;
        
	_X_delta = _Y_delta = _Yaw_delta = 0;
}

LocalizationManager::~LocalizationManager() {
	if (_particles.size() > 0) 
        {
		for (int i=0; i < _particles.size(); i++) 
                {
			delete _particles[i];
		}
		
		_particles.clear();
	}
}
bool LocalizationManager::CreateParticle(float X_delta, float Y_delta, float Yaw_delta, float Belief) 
{
	CreateParticle(X_delta, Y_delta, Yaw_delta, Belief, EXPANSION_RADIUS, YAW_RANGE, HIGH_BREED);
}
bool LocalizationManager::CreateParticle(float X_delta, float Y_delta, float Yaw_delta, float Belief, float Expansion_Radius, float Yaw_Range, int childsCount) 
{
	if (_particles.size() + childsCount < MAX_PARTICLES_COUNT) 
        {
            Particle* particle = new Particle(X_delta, Y_delta, Yaw_delta, Belief);
            _particles.push_back(particle);
            vector<Particle*> childs;
            BreedParticle(particle, childsCount, Expansion_Radius, Yaw_Range, childs);
            ChildsToParticles(childs);
            return true;
	}
	
	return false;
}

void LocalizationManager::Update(float deltaX, float deltaY, float deltaYaw, LaserProxy* lp) {		
	vector<Particle*> childsToAdd;
	vector<int> childsToRemove;
	int particles_size = _particles.size();
	
	for (int i = 0; i < particles_size; i++) 
        {
            Particle* particle = _particles[i];
            particle->Update(deltaX, deltaY, deltaYaw, _map, lp);

            float belif = particle->GetBelif();

            if (belif <= LOW_BELIEF_MIN) 
            {
                particle->DecreaseLife();
                //printf("Particle <%f, %f, %f> belief %f\n", particle->GetX(), particle->GetY(), particle->GetYaw(), particle->GetBelif());
                if (particle->IsDead() || belif <= 0) 
                {
                    //printf("So much death\n");
                    //PlayerClient* pc = new PlayerClient("localhost",6665);
                    //Position2dProxy* pp = new Position2dProxy(pc);
                    //pp->SetSpeed(0, 0);
                    childsToRemove.push_back(i);				
                }
            } 
            else if (belif >= HIGH_BELIEF_MIN &&
                     ((particles_size + HIGH_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT)) 
            {
                    particle->IncreaseAge();
                    BreedParticle(particle, HIGH_BREED, childsToAdd);
            } 
            else if ((particles_size + NORMAL_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT) 
            {
                    particle->IncreaseAge();
                    BreedParticle(particle, NORMAL_BREED, childsToAdd);
            }
	}
	
	if (childsToRemove.size() > 0) 
        {
		for(int i = childsToRemove.size() - 1; i >=0 ; i--) 
                {
			int indexToRemove = childsToRemove[i];
			_particles.erase(_particles.begin() + indexToRemove);
		}
	}
	
	if (childsToAdd.size() > 0) 
        {
		ChildsToParticles(childsToAdd);
	}
}

void LocalizationManager::BreedParticle(Particle* particle, int child_count, vector<Particle*>& childs) 
{
	if (_particles.size() + child_count < MAX_PARTICLES_COUNT) 
        {
            for (int i = 0; i < child_count; i++) 
            {
                    Particle* child = particle->CreateChild();
                    childs.push_back(child);
            }
	}
}

void LocalizationManager::BreedParticle(Particle* particle, int child_count, float expansion_radius, float yaw_range, vector<Particle*>& childs) 
{
	if (_particles.size() + child_count < MAX_PARTICLES_COUNT) 
        {
            for (int i = 0; i < child_count; i++) 
            {
                    Particle* child = particle->CreateChild(expansion_radius, yaw_range);
                    childs.push_back(child);
            }
	}
}

Particle* LocalizationManager::BestParticle() 
{
	if (_particles.empty()) 
        {
            //printf("Out of particles! Making new ones!\n");
            CreateParticle(_X_delta, _Y_delta, _Yaw_delta, 1, EMERGENCY_EXPANSION_RADIUS, EMERGENCY_YAW_RANGE,  PARTICLE_EMERGENCY_BREED);
            
            Particle* random_particle = _particles[rand() % _particles.size()];
            
            _X_delta = random_particle->GetX();
            _Y_delta = random_particle->GetY();
            _Yaw_delta = random_particle->GetYaw();
            
            return random_particle;
	}
	
	Particle* best_particle = _particles[0];
        
	for (int i = 1; i < _particles.size(); i++) 
        {
            if (_particles[i]->GetBelif() > best_particle->GetBelif() &&
                _particles[i]->Age() < best_particle->Age()) 
            {
                    best_particle = _particles[i];
            }
	}
	
	_X_delta = best_particle->GetX();
	_Y_delta = best_particle->GetY();
	_Yaw_delta = best_particle->GetYaw();
	
	return best_particle;
}

void LocalizationManager::ChildsToParticles(vector<Particle*> childs) 
{
	for (int i = 0; i < childs.size(); i++) 
        {
		_particles.push_back(childs[i]);
	}
}

