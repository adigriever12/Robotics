/* 
 * File:   ConfiguraionManager.h
 * Author: colman
 *
 * Created on July 18, 2015, 4:49 AM
 */

#ifndef CONFIGURAIONMANAGER_H
#define	CONFIGURAIONMANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h> 
#define MAP "map:"

using namespace std;

class ConfiguraionManager {
public:
    ConfiguraionManager(char* filename);
    void ReadParameters();
    
    virtual ~ConfiguraionManager();
    
    static string MapFileName;
    static int MapWidth;
    static int MapHeight;
    static int StartLocationX;
    static int StartLocationY;
    static int StartLocationYAW;
    static int GoalLocationX;
    static int GoalLocationY;
    static int RobotSize;
    static double MapResolutionCM;
    static double GridResolutionCM;
    
    static void SetMapWidth(int width)
    {
        MapWidth = width;
    }
    
    static void SetMapHeight(int height)
    {
        MapHeight = height;
    }
    
    static double GetCMInCell() {
        return (GridResolutionCM / MapResolutionCM);
    }

private:
    char* _filename;
    
    void split_string(string str, std::vector<string>* tokens) {
        string buf; // Have a buffer string
        stringstream ss(str); // Insert the string into a stream
        while (ss >> buf) {
            tokens->push_back(buf);
        }
    }
};

#endif	/* CONFIGURAIONMANAGER_H */

