
#ifndef CONVERT_H
#define	CONVERT_H

#define CM_TO_METERS(cm) cm / 100

class Convert {
public:
	
	static float PixelToRobotX(float Xdelta, float resolution, float mapWidth) {
		float halfSize = mapWidth / 2;
		
		if (Xdelta > halfSize)
                {
                    Xdelta -= halfSize;
                }
		else 
                {
                    Xdelta = halfSize - Xdelta;
                    Xdelta *= -1;			
		}
		
		return Xdelta * resolution;
	}
	
	static float PixelToRobotY(float Ydelta, float resolution, float mapHeight) {
		float halfSize = mapHeight / 2;
		
		if (Ydelta > halfSize) 
                {
                    Ydelta -= halfSize;
                    Ydelta *= -1;
		} 
                else 
                {
                    Ydelta = halfSize - Ydelta;
		}
		
		return Ydelta * resolution;
	}
	
	static float RobotToPixelX(float Xdelta, float resolution, float mapWidth) {
		double halfSize = (mapWidth / 2) * resolution;
		
		if (Xdelta > 0)
                {
                    Xdelta += halfSize;
                }
		else 
                {
                    Xdelta *= -1;
                    Xdelta = halfSize - Xdelta;
		}
		
		return Xdelta / resolution;
	}
	
	static float RobotToPixelY(float Ydelta, float resolution, float mapHeight) {
		float halfSize = (mapHeight / 2) * resolution;
		
		if (Ydelta < 0) 
                {
                    Ydelta *= -1;
                    Ydelta += halfSize;
		} 
                else 
                {
                    Ydelta = halfSize - Ydelta;
		}
		
		return Ydelta / resolution;
	}
};

#endif	/* CONVERT_H */