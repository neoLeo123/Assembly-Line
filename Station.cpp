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
#include "Station.h"	
#include "Utilities.h"
#include <algorithm>
#include <iomanip>
namespace sdds {
	size_t Station::m_widthField = 0u;
	size_t Station::id_generator = 0u;

	Station::Station(const string& src) {
		Utilities util;
		id = ++Station::id_generator;
		bool more = true;
		size_t pos = 0u;

		itemName = util.extractToken(src, pos, more);
		serialNum = stoi(util.extractToken(src, pos, more));
		NuminStock = stoi(util.extractToken(src, pos, more));
		m_widthField = max(util.getFieldWidth(), m_widthField);
		desc = util.extractToken(src, pos, more);
	}
	const std::string& Station::getItemName() const {
		return itemName;
	}

	size_t Station::getNextSerialNumber() {
		size_t current = serialNum;
		++serialNum;
		return current;
	}

	size_t Station::getQuantity() const {
		return NuminStock;
	}

	void Station::updateQuantity() {
		if (NuminStock == 0)
		{
			NuminStock = 0;
		}
		else
		{
			NuminStock--;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << right << setw(3) << setfill('0') << id << " | "
			<< left << setw(Station::m_widthField+1) << setfill(' ') << itemName << "| "
			<< right << setw(6) << setfill('0') << serialNum << " | ";

		if (full) {
			os << left << setw(Station::m_widthField) << setfill(' ') << setw(4) << right << NuminStock << " | "
				<< desc << endl;
		}
		else {
			os << endl;
		}
	}

}
