#include "dataManager.h"

DataManager::DataManager() {}

DataManager::~DataManager() {}

Document DataManager::readFile(const char* fileName) {
	
	Document document;
	std::string jsonString,line;
	std::ifstream file(fileName, std::ifstream::binary);

	if (file.is_open()) {
		while (getline(file, line)) {
			jsonString.append(line + "\n");
		}
		file.close();
	}
	else {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in opening " + std::string(fileName)));
	}

	// Check for invalid json
	if (document.Parse(jsonString.c_str()).HasParseError()) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in parsing " + std::string(fileName)));
	}

	return document;
}

char* strToCharArr(std::string str) {
	char *temp = new char[str.length() + 1];

	std::strcpy(temp, str.c_str());
	return temp;
}

UCHAR isSpecialKey(std::string target) {
	std::string strArr[] = { "UP", "DOWN", "LEFT", "RIGHT" };
	std::map<std::string, UCHAR> strUcharMap;	// a map of special keys to UCHAR
	
	strUcharMap["UP"] = UP_KEY;
	strUcharMap["DOWN"] = DOWN_KEY;
	strUcharMap["LEFT"] = LEFT_KEY;
	strUcharMap["RIGHT"] = RIGHT_KEY;
	
	for (int i = 0; i < sizeof(strArr); i++) {
		if (target.compare(strArr[i]))
			return strUcharMap[target];
	}

	return 0;
}

PaddleControls getPaddleControls(Value val) {
	UCHAR upChar, downChar;
	std::string upStr = toUpperCase(val["up"].GetString());
	std::string downStr = toUpperCase(val["down"].GetString());

	// casting and de-referencing only gives the first letter
	// string needs to be converted to CHAR* then to UCHAR
	upChar = isSpecialKey(upStr) == 0 ? (UCHAR)*strToCharArr(upStr) : isSpecialKey(upStr);
	downChar = isSpecialKey(downStr) == 0 ? (UCHAR)*strToCharArr(downStr) : isSpecialKey(downStr);

	return PaddleControls(upChar, downChar);
}

void DataManager::initControlData(const char* fileName) {
	Document document = readFile(fileName);
	
	ControlsJson cj = ControlsJson(
		getPaddleControls(document["p1"].GetObjectA()), 
		getPaddleControls(document["p2"].GetObjectA())
		);

	controlsJson = cj;
}
