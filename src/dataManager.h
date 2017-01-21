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

struct PickupJson {
	std::vector<PickupData*> pickupDataVec;

	PickupJson() {}
	PickupJson(std::vector<PickupData*> p) : pickupDataVec(p) {}
};

class DataManager {
private:
	ControlsJson controlsJson;
	PickupJson pickupJson;

public:
	DataManager();
	~DataManager();

	// getters
	ControlsJson getControlsJson() { return controlsJson; };
	PickupJson	getPickupJson() { return pickupJson; }
	
	// setters
	void setControlsJson(ControlsJson cj) { controlsJson = cj; }
	void setPickupJson(PickupJson pj) { pickupJson = pj; }

	Document readFile(const char* fileName);	// Takes in a pointer to a char array
	void initControlData(const char* fileName);
	void initPickupsData(const char* fileName);

	// Logging
	void logPickupsJson();
};

#endif
