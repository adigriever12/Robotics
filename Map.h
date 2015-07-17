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



	// TODO:: change later for parameters file
	int robotSize = 30;
	double MapResolutionCM = 2.5;
	int GridResolutionCM = 10;

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
            //return _grid_width;   
            return 550;
        }
        
        int GetMapHeight()
        {
            //return _grid_height;   
            return 380;
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
