/*
 * Map.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map(char* mapname) {
	unsigned error = lodepng::decode(_image, _width, _height, mapname);
}

Map::~Map() {
}

int Map::getMatrixValue(int row, int col)
{
	if (row >= 0 && col >= 0 && row < _height && col < _width)
	{
		int place = NUMBER_OF_CELLS * _width * row + col * NUMBER_OF_CELLS;

		return _image[place];
	}

}

// in case cell is white, turning it to grey
void Map::setMatrixColor(int row, int col)
{
	if (row >= 0 && col >= 0 && row < _height && col < _width)
	{
		int place = NUMBER_OF_CELLS * _width * row + col * NUMBER_OF_CELLS;

		if (_image[place] == WHITE_RGB)
		{
			_image[place]     = GREY_RGB;
			_image[place + 1] = GREY_RGB;
			_image[place + 2] = GREY_RGB;
		}
	}
}

void Map::blowMap()
{
	// dividing by half the robot size
	double numOfCells = robotSize / 2 / MapResolutionCM;

	for(int i = 0; i < _height; i++)
	{
		for(int j = 0; j < _width; j++)
		{
			// in case cell is black
			if (getMatrixValue(i, j) == BLACK_RGB)
			{
				for(int k = 0; k < numOfCells; k++)
				{
					for (int l = 0; l < numOfCells; l++)
					{
						setMatrixColor(i + k, j + l);
						setMatrixColor(i - k, j - l);
						setMatrixColor(i - k, j + l);
						setMatrixColor(i + k, j - l);
					}
				}
			}
		}
	}

	unsigned error = lodepng::encode("/home/colman/Desktop/roboticLabMap2.png", _image, _width, _height);

}

void Map::turnToGrid()
{
	_grid_height = ceil(_height * MapResolutionCM / GridResolutionCM );
	_grid_width = ceil(_width * MapResolutionCM / GridResolutionCM);

	double numOfCells = floor(GridResolutionCM / MapResolutionCM);

	_grid = new int*[_grid_height];

	for(int i = 0; i < _grid_height; ++i)
	{
		_grid[i] = new int[_grid_width];
	}

	for(int i = 0; i < _grid_height; i++)
	{
		for(int j = 0; j < _grid_width; j++)
		{
			bool is_taken = false;

			for(int k = 0; k < numOfCells && !is_taken; k++)
			{
				for (int l = 0; l < numOfCells && !is_taken; l++)
				{
					// in case the cell is black or grey.
					if (getMatrixValue(i * numOfCells + k, j * numOfCells + l) != WHITE_RGB ||
						getMatrixValue(i * numOfCells - k, j * numOfCells - l) != WHITE_RGB ||
						getMatrixValue(i * numOfCells - k, j * numOfCells + l) != WHITE_RGB ||
						getMatrixValue(i * numOfCells + k, j * numOfCells - l) != WHITE_RGB)
					{
						is_taken = true;
					}
				}
			}

			// if the cell is either black or grey
			if (is_taken)
			{
				_grid[i][j] = 1;
			}
			else
			{
				_grid[i][j] = 0; // in case the cell is white
			}
		}
	}

	distributeWeights();
}

void Map::setGridWeight(int row, int col)
{
	if (row >= 0 && col >= 0 && row < _grid_height && col < _grid_width && _grid[row][col] == 0)
	{
		_grid[row][col] = 2;
	}
}

void Map::distributeWeights()
{
	for(int i = 0; i < _grid_height; i++)
	{
		for(int j = 0; j < _grid_width; j++)
		{
			if (_grid[i][j] == 1)
			{
				setGridWeight(i, j + 1);
				setGridWeight(i, j - 1);
				setGridWeight(i + 1, j);
				setGridWeight(i - 1, j);
				setGridWeight(i + 1, j + 1);
				setGridWeight(i + 1, j - 1);
				setGridWeight(i - 1, j + 1);
				setGridWeight(i - 1, j - 1);
			}
		}
	}

//	for(int i = 0; i < _grid_height; i++)
//	{
//		for(int j = 0; j < _grid_width; j++)
//		{
//			std::cout << _grid[i][j] << std::flush;
//		}
//		std::cout << "\n" << std::flush;
//	}
}

int Map::PixleLocationToGrid(int pixle)
{
	if (pixle == 0)
	{
		return 0;
	}
	else
	{
		return (ceil(pixle/(floor(GridResolutionCM / MapResolutionCM))) - 1);
	}
}

float Map::GetCellWeight(int row, int col)
{
	if (row >= 0 && col >= 0 && row < _grid_height && col < _grid_width)
	{
		return _grid[row][col];
	}
	else
	{
		return -1;
	}
}

bool Map::IsPassable(float weight)
{
	return (weight == 0 || weight == 2);
}
