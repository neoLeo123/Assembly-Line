// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Nov 11,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
using namespace std;
namespace sdds {

	class Station {
		int id{0};
		string itemName{""};
		string desc{""};
		unsigned serialNum{0u};
		unsigned NuminStock{0u};

		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const string& src);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};
}




#endif // !SDDS_STATION_H
