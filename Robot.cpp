/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port, LocalizationManager* localization) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);
        _localization = localization;
	_pp->SetMotorEnable(true);
        
        //SetOdemetry(2.175, -2.875, ((20 * M_PI) / 180));
        //_pp->SetOdometry(2.175, -2.875, ((20 * M_PI) / 180));
        
        
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();
}
void Robot::ReadAndUpdateLocalization() {
	Read();
	UpdateLocalization();
}

double Robot::SetPosition(double dX, double dY, double dYaw, bool setOdemetry) {
    //printf("best particle (%f, %f, %f)\n", dX, dY, dYaw);
    _dX = dX;
    _dY = dY;
    _dYaw = dYaw;

    if (setOdemetry) {
            SetOdemetry(dX, dY, dYaw);
    }
}

void Robot::SetOdemetry(double dX, double dY, double dYaw) {
	_pp->SetOdometry(dX, dY, dYaw);
	while (((float)dX != (float)_pp->GetXPos()) || ((float)dY != (float)_pp->GetYPos()) || ((float)dYaw != (float)_pp->GetYaw())) {
//		printf("%lg, %lg, %lg ? %u - %u - %u || %lg, %lg\n", _pp->GetXPos(), _pp->GetYPos(), _pp->GetYaw(),
//				(dX != _pp->GetXPos()), (dY != _pp->GetYPos()), (dYaw != _pp->GetYaw()),
//				dX, _pp->GetXPos());
		_pc->Read();
		_pp->SetOdometry(dX, dY, dYaw);
	}
}

void Robot::SetOdometryByPixelCoord(double dX, double dY, double dYaw, double resolution, double mapWidth, double mapHeight) {		
	SetPosition(Convert::PixelToRobotX(dX, CM_TO_METERS(resolution), mapWidth),
                    Convert::PixelToRobotY(dY, CM_TO_METERS(resolution), mapHeight),
                    DTOR(dYaw), true);

	_localization->CreateParticle(_dX, _dY, _dYaw, 1);
}

void Robot::UpdateLocalization() {
	double deltaX = _pp->GetXPos() - _dX;
	double deltaY = _pp->GetYPos() - _dY;
	double deltaYaw = _pp->GetYaw() - _dYaw;
//	printf("%f, %f, %f\n", x, y, yaw);
//	printf("%f, %f, %f\n", deltaX, deltaY, deltaYaw);
	
	/*
	 * We update the localization manager by the delta position and chose the
	 * best particle to use as our real position
	 */
	_localization->Update(deltaX, deltaY, deltaYaw, _lp);
	Particle* particle = _localization->GetBestParticle();
	SetPosition(particle->GetX(), particle->GetY(), particle->GetYaw(), false);
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
