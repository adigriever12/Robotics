#include "LocalizationManager.h"
#include <ctime>

LocalizationManager::LocalizationManager(Map* map,  SDL2Wrapper* sdl) {
	_map = map;
	_sdl = sdl;
        
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
	CreateParticle(X_delta, Y_delta, Yaw_delta, Belief, EXPANSION_RADIUS, YAW_RANGE, PARTICLE_HIGH_BREED);
}
bool LocalizationManager::CreateParticle(float X_delta, float Y_delta, float Yaw_delta, float Belief, float Expansion_Radius, float Yaw_Range, int childsCount) 
{
	// Create new particle only if not exceeded the max particles allowed
	if (_particles.size() + childsCount < MAX_PARTICLES_COUNT) 
        {
            /*
             * This particle is a special one because we create him without parent
             * so basically he is the first one and from him we need to breed few
             * more just to start the natural breeding process.
             */
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
            // Get each particle and update position
            Particle* particle = _particles[i];
            particle->Update(deltaX, deltaY, deltaYaw, _map,_sdl, lp);

            float belif = particle->GetBelif();

            // Depending on the belif value kill or breed the given particle
            if (belif <= LOW_BELIF_THRESHOLD) 
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
            else if (belif >= HIGH_BELIF_THRESHOLD &&
                     ((particles_size + PARTICLE_HIGH_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT)) 
            {
                    particle->IncreaseAge();
                    BreedParticle(particle, PARTICLE_HIGH_BREED, childsToAdd);
            } 
            else if ((particles_size + PARTICLE_NORMAL_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT) 
            {
                    particle->IncreaseAge();
                    BreedParticle(particle, PARTICLE_NORMAL_BREED, childsToAdd);
            }
	}
	
	// Remove the dead particles from the main particles vector
	if (childsToRemove.size() > 0) 
        {
		for(int i = childsToRemove.size() - 1; i >=0 ; i--) 
                {
			int indexToRemove = childsToRemove[i];
			_particles.erase(_particles.begin() + indexToRemove);
		}
	}
	
	// Add new particles to the main particles vector
	if (childsToAdd.size() > 0) 
        {
		ChildsToParticles(childsToAdd);
	}
        
        Particle* bestParticle;
#ifdef DRAW_PARTICLES
	bestParticle = BestParticle();
	for (int i=0; i<_particles.size(); i++) {
		Particle* particle = _particles[i];
		float dX = Convert::RobotToPixelX(particle->GetX(), CM_TO_METERS(_map->GetPixelResolution()), _map->GetMapWidth());
		float dY = Convert::RobotToPixelY(particle->GetY(), CM_TO_METERS(_map->GetPixelResolution()), _map->GetMapHeight());
		if (particle->GetX() == bestParticle->GetX() &&
				particle->GetY() == bestParticle->GetY() &&
				particle->GetYaw() == bestParticle->GetYaw() &&
				particle->GetBelif() == bestParticle->GetBelif()) {
			continue;
		}
		
//		_sdl->FillRectangle(dX, dY, (double)(_map->GetGridResolution() / _map->GetPixelResolution()), PURPLE_RGB_FORMAT, 255, false);
		_sdl->DrawPoint(dX, dY, PURPLE_RGB_FORMAT, 255);
	}
	
	float dX = Convert::RobotToPixelX(bestParticle->GetX(), CM_TO_METERS(_map->GetPixelResolution()), _map->GetMapWidth());
	float dY = Convert::RobotToPixelY(bestParticle->GetY(), CM_TO_METERS(_map->GetPixelResolution()), _map->GetMapHeight());
	_sdl->FillRectangle(dX, dY, (double)(4), RED_RGB_FORMAT, 255, false);
#endif
	
#ifdef DRAW_BEST_LASER_SCAN
	bestParticle = BestParticle();
	bestParticle->DrawLaserScan(_map, _sdl, lp);
#endif
}

void LocalizationManager::BreedParticle(Particle* particle, int child_count, vector<Particle*>& childs) 
{
	/*
	 * We don't want to breed only half a family so we won't breed any child
	 * if their is no more room in our particles vector
	 */
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
	
	// Incase no particles found we create new one from last known position
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
	
	// Save last known position for the best particle
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

