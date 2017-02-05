#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

// rapidjson/example/simpledom/simpledom.cpp`
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "util/util.h"
#include "constants.h"
#include "gameError.h"

using namespace rapidjson;

struct PaddleControls {
	UCHAR up;
	UCHAR down;
	PaddleControls() {}
	PaddleControls(UCHAR up, UCHAR down) : up(up), down(down) {}
};

struct ControlsJson {
	PaddleControls p1;
	PaddleControls p2;

	ControlsJson() {}
	ControlsJson(
		PaddleControls p1, 
		PaddleControls p2
	) : 
		p1(p1), 
		p2(p2) {}
};

class DataManager {
private:
	ControlsJson controlsJson;

public:
	DataManager();
	~DataManager();

	// getters
	ControlsJson getControlsJson() { return controlsJson; };
	
	// setters
	void setControlsJson(ControlsJson cj) { controlsJson = cj; }

	Document readFile(const char* fileName);	// Takes in a pointer to a char array
	void initControlData(const char* fileName);
};

#endif
