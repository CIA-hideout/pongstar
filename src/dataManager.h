#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

// rapidjson/example/simpledom/simpledom.cpp`
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

class DataManager {
private:

public:
	DataManager();
	~DataManager();

	void readFile(const char* fileName);	// Takes in a pointer to a char array
};

#endif
