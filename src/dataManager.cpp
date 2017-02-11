#include "dataManager.h"

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

Value DataManager::convertHsmToVal(HighScoreMap hsm, Document::AllocatorType& a) {
	Value scoreArr(kArrayType);

	for (auto &x : hsm) {
		Value scoreObj(kObjectType), name;

		char buffer[30];
		int len = sprintf(buffer, "%s", x.second.c_str() ); // dynamically created string.
		name.SetString(buffer, len, a);
		memset(buffer, 0, sizeof(buffer));

		scoreObj.AddMember("name", name, a);
		scoreObj.AddMember("score", x.first, a);
		
		scoreArr.PushBack(scoreObj, a);
	}

	return scoreArr;
}

void DataManager::saveHighScore() {
	Document d;
	d.SetObject();
	Document::AllocatorType& a = d.GetAllocator();

	d.AddMember("classic", convertHsmToVal(highScoreJson.classic, a), a);
	d.AddMember("timeAttack", convertHsmToVal(highScoreJson.timeAttack, a), a);

	// Stringify the DOM
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	d.Accept(writer);

	// Write to file 
	std::ofstream ofs(dataManagerNS::HIGH_SCORES_JSON, std::ofstream::out);
	ofs << buffer.GetString();
	ofs.close();
}

PaddleControls DataManager::parseControlVal(Value val) {
	UCHAR upChar, downChar;
	std::string upStr = toUpperCase(val["up"].GetString());
	std::string downStr = toUpperCase(val["down"].GetString());

	// casting and de-referencing only gives the first letter
	// string needs to be converted to CHAR* then to UCHAR
	upChar = isSpecialKey(upStr) == 0 ? (UCHAR)*strToCharArr(upStr) : isSpecialKey(upStr);
	downChar = isSpecialKey(downStr) == 0 ? (UCHAR)*strToCharArr(downStr) : isSpecialKey(downStr);

	return PaddleControls(upChar, downChar);
}

HighScoreMap DataManager::parseHighScoreVal(const Value& val) {
	HighScoreMap hsm;

	for (Value::ConstValueIterator itr = val.Begin(); itr != val.End(); ++itr) {
		hsm.insert(HighScorePair(
			itr->GetObjectA()["score"].GetInt(),
			itr->GetObjectA()["name"].GetString()
			));	
	}
	
	return hsm;
}

void DataManager::initControlData() {
	Document document = readFile(dataManagerNS::CONTROLS_JSON);

	std::string aiStr = toUpperCase(document["triggerAI"].GetString());
	UCHAR triggerAIKey = isSpecialKey(aiStr) == 0 ? (UCHAR)*strToCharArr(aiStr) : isSpecialKey(aiStr);
	
	ControlsJson cj = ControlsJson(
		parseControlVal(document["p1"].GetObjectA()),
		parseControlVal(document["p2"].GetObjectA()),
		triggerAIKey
		);

	controlsJson = cj;
}

void DataManager::initHighScoreData() {
	Document document = readFile(dataManagerNS::HIGH_SCORES_JSON);
	const Value& classicVal = document["classic"].GetArray();
	const Value& timeAtkVal = document["timeAttack"].GetArray();
	
	HighScoreJson hsj;
	hsj.classic = parseHighScoreVal(classicVal);
	hsj.timeAttack = parseHighScoreVal(timeAtkVal);

	highScoreJson = hsj;
}
