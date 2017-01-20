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

std::string toUpperCase(std::string str) {
	const char* charArr = str.c_str();

	for (size_t i = 0; i < strlen(charArr); i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 'a' + 'A';
		}
	}

	return std::string(charArr);
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

void DataManager::initPickupsData(const char* fileName) {
	Document document = readFile(fileName);
	Value val;
	PickupData* pickupData;
	std::vector<PickupData*> pickups;
	
	std::string name;
	int frame;
	float duration;
	
	for (auto& v : document.GetArray()) {
		val = v.GetObjectA();

		name = val["name"].GetString();
		frame = val["frame"].GetInt();
		duration = val["duration"].GetFloat();

		pickupData = new PickupData(name, frame, duration);
		pickups.push_back(pickupData);
	}

	pickupsJson = PickupsJson(pickups);
}

void DataManager::logPickupsJson() {
	std::vector<PickupData*> pickups = pickupsJson.pickups;
	PickupData* tempPtr = NULL;

	for (size_t i = 0; i < pickups.size(); i++) {
		tempPtr = pickups[i];
		
		// c_str() is needed or else printf() will find the first sizeof(char*) bytes of the str, 
		// which leads to an access violation because those bytes aren't really a pointer.
		printf("name: %s frame: %d duration: %f \n", tempPtr->name.c_str(), tempPtr->frame, tempPtr->duration);
	}
}