/*
 * Map.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include <iostream>
#include <vector>
#include "lodepng.h"
#include "ConfiguraionManager.h"
#include <stdio.h>
#include <math.h>
    
struct Point
		{
			int x;
			int y;
		};
class Map {
	const int NUMBER_OF_CELLS = 4;
	const int BLACK_RGB = 0;
	const int GREY_RGB = 204;
	const int WHITE_RGB = 255;
	std::vector<unsigned char> _image;
	unsigned _height;
	unsigned _width;
	int** _grid;
	int _grid_height;
	int _grid_width;

	int robotSize = ConfiguraionManager::RobotSize;
	double MapResolutionCM = ConfiguraionManager::MapResolutionCM;
	int GridResolutionCM = ConfiguraionManager::GridResolutionCM;

public:
	int** GetGrid()
		{
			return _grid;
		}

        double GetPixelResolution() 
        {
            return MapResolutionCM;
        }
        
        int GetMapWidth()
        { 
            ConfiguraionManager::SetMapWidth(_width);
            return _width;
        }
        
        int GetMapHeight()
        { 
            ConfiguraionManager::SetMapHeight(_height);
            return _height;
        }
        
	Map(char* mapname);
	virtual ~Map();
	int getMatrixValue(int row, int col);
	void setMatrixColor(int row, int col);
	void blowMap();
	void turnToGrid();
	void distributeWeights();
	void setGridWeight(int row, int col);
	int PixleLocationToGrid(int pixle);
	float GetCellWeight(int row, int col);
	bool IsPassable(float weight);
};


#endif /* MAP_H_ */
