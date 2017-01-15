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
		printf("Unable to open file\n");
	}

	if (document.Parse(jsonString.c_str()).HasParseError()) {
		printf("Error in json");
	}

	return document;
}

pControls getPlayerControls(Value val) {
	return pControls((unsigned char)val["up"].GetString(), (unsigned char)val["down"].GetString());
}

controlsJson DataManager::initControlData(const char* fileName) {
	Document document = readFile(fileName);
	
	controlsJson cj = controlsJson();
	cj.p1Control = getPlayerControls(document["p1"].GetObjectA());
	cj.p2Control = getPlayerControls(document["p2"].GetObjectA());

	return cj;
}

/*char b = 'B';
UCHAR unsignedB = (unsigned char)b;

printf("%u", A_KEY);
printf("%u", unsignedB);*/