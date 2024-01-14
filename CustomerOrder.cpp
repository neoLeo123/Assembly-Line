// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Nov 18,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CustomerOrder.h"	
#include <iomanip>
#include <algorithm>
#include "Utilities.h"
using namespace std;
namespace sdds {
	size_t CustomerOrder::m_widthField = 0u;

	CustomerOrder::CustomerOrder(const std::string& src) {
		Utilities util;
		bool more = true;
		size_t pos = 0u;
		size_t idx = 0u;

		
			m_name = util.extractToken(src, pos, more);
			m_product = util.extractToken(src, pos, more);
			m_cntItem = std::count(src.begin(), src.end(), util.getDelimiter()) - 1;

			if (m_cntItem)
				m_lstItem = new Item * [m_cntItem];

			while (more && m_cntItem) {
				m_lstItem[idx] = new Item(util.extractToken(src, pos, more));
				++idx;
			}

			CustomerOrder::m_widthField = max(util.getFieldWidth(), CustomerOrder::m_widthField);
		
		
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "Copy not allowed.";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			
			for (size_t i = 0u; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			
			delete[] m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;

			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0u;
			src.m_lstItem = nullptr;
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder(){

		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];

			
		}
		delete[] m_lstItem;

	}

	bool CustomerOrder::isOrderFilled() const {
		
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;  
			}
		}
		return true;
		
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					return false;
				}
			}
		}
		return true;
		
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool filled{ false };
		for (size_t i = 0; i < m_cntItem && !filled; i++) {
			if ((m_lstItem[i]->m_itemName == station.getItemName()) && !m_lstItem[i]->m_isFilled && (station.getQuantity() > 0)) {

				station.updateQuantity();
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				filled = true;
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
			else if ((m_lstItem[i]->m_itemName == station.getItemName()) && (station.getQuantity() == 0)) {
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;

		for (auto i = 0u; i < m_cntItem; i++) {
			os << "[" << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << left << setw((CustomerOrder::m_widthField)+1) << setfill(' ') << m_lstItem[i]->m_itemName;
			os << "- " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
		
	}
}




