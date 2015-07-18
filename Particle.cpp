#include "Particle.h"

Particle::Particle(float X_delta, float Y_delta, float Yaw_delta, float belief) 
{
    _X_delta = X_delta;
    _Y_delta = Y_delta;
    _Yaw_delta = Yaw_delta;
    _belief = belief;

    _lifes = PARTICLE_LIFES_NUM;
    _age = 1;
}

Particle::~Particle() 
{
}
float Particle::GetBelif() 
{
    return _belief;
}

float Particle::GetX() 
{
    return _X_delta;
}

float Particle::GetY() 
{
    return _Y_delta;
}

float Particle::GetYaw() 
{
    return _Yaw_delta;
}

Particle* Particle::CreateChild() 
{
    return CreateChild(EXPANSION_RADIUS, YAW_RANGE);
}

Particle* Particle::CreateChild(float expansion_radius, float yaw_range) 
{
    float newX = _X_delta + Random(-expansion_radius, expansion_radius);
    float newY = _Y_delta + Random(-expansion_radius, expansion_radius);
    float newYaw = _Yaw_delta + Random(-yaw_range, yaw_range);
    return new Particle(newX, newY, newYaw, 1);
}

void Particle::Update(float X_delta, float Y_delta, float Yaw_delta, Map* map,SDL2Wrapper* sdl, LaserProxy* lp) 
{
    _X_delta += X_delta;
    _Y_delta += Y_delta;
    _Yaw_delta += Yaw_delta;

    // Calculate new belief value from prediction belif, laser scan and the belif magic number
    float predictionBelif = ProbabilityByMovement(X_delta, Y_delta, Yaw_delta) * _belief;
    float probabilityByScan = ProbabilityByLaserScan(_X_delta, _Y_delta, _Yaw_delta, map, sdl, lp, false);
    _belief = probabilityByScan * predictionBelif * BELIEF_MAGIC_NUMBER;
    //_dBel = predictionBelif * BELIF_MAGIC_NUMBER;

    if (_belief > 1)
        _belief = 1;
}

float Particle::Random(float min, float max) 
{
    float num = (float)rand() / RAND_MAX;
    return min + num * (max - min);
}

float Particle::ProbabilityByMovement(float X_delta, float Y_delta, float Yaw_delta) 
{
	
	float distance = sqrt(pow(X_delta,2) + pow(Y_delta,2));
	
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

float Particle::ProbabilityByLaserScan(float X_delta, float Y_delta, float Yaw_delta, Map* map, SDL2Wrapper* sdl, LaserProxy* lp, bool should_draw)
{
	// Convert relative obstacle position to our valid map position
	float resolution = (map->GetPixelResolution()) / 100;
	float map_width = map->GetMapWidth();
	float map_height = map->GetMapHeight();
        
	float x = Convert::RobotToPixelX(X_delta, resolution, map_width);
	float y = Convert::RobotToPixelY(Y_delta, resolution, map_height);
        
        int x_coord = floor(x / (ConfiguraionManager::GetCMInCell()));
        int y_coord = floor(y / (ConfiguraionManager::GetCMInCell()));
        
	// Check if current position is a valid position before continue
	if (x < 0 || (x) >= map->GetMapWidth() ||
	    y < 0 || (y) >= map->GetMapHeight()) 
        {
            //printf("Oops! out of bound! (%f, %f)\n", x, y);
            return 0;
	}
        
	int** grid = map->GetGrid();
	
        if (grid[y_coord][x_coord] == 1)
        {
            //printf("obstacle ahead! at (%u, %u) with value:%u\n", yCoord, xCoord, grid[yCoord][xCoord]);
            return 0;
        }
        
	int scans = lp->GetCount();
	float max_range = lp->GetMaxRange();
			
	float total_hits = 0;
	float correct_hits = 0;
	int boundary_misses = 0;
        
	for(int i=0; i<scans; i++) 
        {
            float range = lp->GetRange(i);
		
            if (range < max_range) 
            {
                total_hits++;
			
                // Calculate obstacle position
                float bearing = lp->GetBearing(i);
                float obstacle_X = X_delta + range * cos(Yaw_delta + bearing);
                float obstacle_Y = Y_delta + range * sin(Yaw_delta + bearing);

                obstacle_X = Convert::RobotToPixelX(obstacle_X, resolution, map_width);
                obstacle_Y = Convert::RobotToPixelY(obstacle_Y, resolution, map_height);

                // Check bounds before actually trying to get cell
                if ((obstacle_X) < 0 || (obstacle_X) >= map->GetMapWidth() ||
                     obstacle_Y < 0 || (obstacle_Y) >= map->GetMapHeight()) 
                {
                    boundary_misses++;	
                    continue;
                }

                x_coord = floor(obstacle_X / (ConfiguraionManager::GetCMInCell()));
                y_coord = floor(obstacle_Y / (ConfiguraionManager::GetCMInCell()));

                if (grid[y_coord][x_coord] != 0)
                {
                    if (should_draw) 
                    {
                        sdl->DrawPoint(obstacle_X, obstacle_Y, GREEN_RGB_FORMAT, 255);
                    }
//                            printf("Correct hits incremented %f ->", correctHits);
                    correct_hits++;
//                            printf("%f\n", correctHits);
                }
                else
                {
                    if (should_draw) 
                    {
                        sdl->DrawPoint(obstacle_X, obstacle_Y, RED_RGB_FORMAT, 255);
                    }
//                            printf("Oh noes, no hit at (%u, %u)\n", xCoord, yCoord);
                }
            }
	}
	
	float accuracy = correct_hits / total_hits;
//	printf("Particle accuracy: %f\n", accuracy);
	return accuracy;
}

void Particle::DrawLaserScan(Map* map, SDL2Wrapper* sdl, LaserProxy* lp) 
{
    ProbabilityByLaserScan(GetX(), GetY(), GetYaw(), map, sdl, lp, true);
}

void Particle::IncreaseAge() 
{
    _age++;
}

int Particle::Age() 
{
    return _age;
}


void Particle::DecreaseLife() 
{
	_lifes--;
}

bool Particle::IsDead() 
{
    return _lifes <= 0;
}