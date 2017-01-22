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

struct PickupData {
	std::string name;
	int frame;
	float duration;

	PickupData() {}
	PickupData(std::string n, int f, float d) : name(n), frame(f), duration(d) {}
};

class DataManager {
private:
	ControlsJson controlsJson;
	std::vector<PickupData*> pickupVec;

public:
	DataManager();
	~DataManager();

	// getters
	ControlsJson getControlsJson() { return controlsJson; };
	std::vector<PickupData*> getPickupVec() { return pickupVec; }
	
	// setters
	void setControlsJson(ControlsJson cj) { controlsJson = cj; }
	void setPickupVec(std::vector<PickupData*> pv) { pickupVec = pv; }

	Document readFile(const char* fileName);	// Takes in a pointer to a char array
	void initControlData(const char* fileName);
	void initPickupsData(const char* fileName);

	// Logging
	void logPickupsJson();
};

#endif
