
// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Nov 11,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Utilities.h"	
#include <algorithm>
using namespace std;
namespace sdds {

	char Utilities::m_delimiter = ' ';


	std::string trim(const std::string& str) {
		size_t first = str.find_first_not_of(" \t\n\r");
		size_t last = str.find_last_not_of(" \t\n\r");

		if (first == std::string::npos) {

			return "";
		}

		return str.substr(first, last - first + 1);
	}
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string extractedToken;
		size_t endPos = str.find(m_delimiter, next_pos);

		if (endPos != std::string::npos) {
			extractedToken = str.substr(next_pos, endPos - next_pos);
			next_pos = endPos + 1;
			more = true;
		}
		else {
			extractedToken = str.substr(next_pos);
			more = false;
		}

		extractedToken = trim(extractedToken);
		m_widthField = std::max(m_widthField, extractedToken.length());
		if (extractedToken.empty()) {
			more = false;
			throw "ERROR: Token is empty!";
		}

		return extractedToken;
	}




	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}