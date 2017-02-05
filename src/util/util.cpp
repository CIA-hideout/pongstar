#include "util.h"

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