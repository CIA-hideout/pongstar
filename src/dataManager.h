#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

// rapidjson/example/simpledom/simpledom.cpp`
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "constants.h"

using namespace rapidjson;

struct pControls {
	UCHAR up;
	UCHAR down;
	pControls() {}
	pControls(UCHAR up, UCHAR down) : up(up), down(down) {}
};

struct controlsJson {
	pControls p1Control;
	pControls p2Control;

	controlsJson() {}
	controlsJson(
		pControls p1C, 
		pControls p2C
	) : 
		p1Control(p1C), 
		p2Control(p2C) {}
};

class DataManager {
private:

public:
	DataManager();
	~DataManager();

	Document readFile(const char* fileName);	// Takes in a pointer to a char array

	controlsJson initControlData(const char* fileName);
};

#endif
