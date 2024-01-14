// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Nov 11,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <string>
namespace sdds {

	class Utilities {
		size_t m_widthField{ 1u };
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		
		static char getDelimiter();
	};
	std::string trim(const std::string& str);


}




#endif // !SDDS_UTILITIES_H
