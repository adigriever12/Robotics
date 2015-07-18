/* 
 * File:   ConfiguraionManager.cpp
 * Author: colman
 * 
 * Created on July 18, 2015, 4:49 AM
 */

#include "ConfiguraionManager.h"
string ConfiguraionManager::MapFileName;
int ConfiguraionManager::StartLocationX;
int ConfiguraionManager::StartLocationY;
int ConfiguraionManager::StartLocationYAW;
int ConfiguraionManager::GoalLocationX;
int ConfiguraionManager::GoalLocationY;
int ConfiguraionManager::RobotSize;
double ConfiguraionManager::MapResolutionCM;
double ConfiguraionManager::GridResolutionCM;
int ConfiguraionManager::MapWidth;
int ConfiguraionManager::MapHeight;

ConfiguraionManager::ConfiguraionManager(char* filename) {
    _filename = filename;
}

void ConfiguraionManager::ReadParameters()
{
    string line;
    ifstream infile;
    infile.open (_filename);
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,line); // Saves the line in STRING.
        if (line != "")
        {
            vector<string> tokens;
            split_string(line, &tokens);

            string mapper = tokens[0];
            if (mapper == "map:") {
                MapFileName = (tokens[1]);
            }
            else if (mapper == "startLocation:") {
                StartLocationY = atoi((tokens[1]).c_str());
                StartLocationX = atoi((tokens[2]).c_str());
                StartLocationYAW = atoi((tokens[3]).c_str());
            }
            else if (mapper == "goal:") {
                GoalLocationY = atoi((tokens[1]).c_str());
                GoalLocationX = atoi((tokens[2]).c_str());
            }
            else if (mapper == "robotSize:") {
                RobotSize = atoi((tokens[1]).c_str());
            }
            else if (mapper == "MapResolutionCM:") {
                MapResolutionCM = atof((tokens[1]).c_str());
            }
            else if (mapper == "GridResolutionCM:") {
                GridResolutionCM = atof((tokens[1]).c_str());
            }
        }
                        
    }
    infile.close();
}

ConfiguraionManager::~ConfiguraionManager() {
}

