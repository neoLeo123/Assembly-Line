// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Dec 2,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"
#include <iostream>

namespace sdds {

    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string& str) : Station(str) {}


    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty())
            m_orders.front().fillItem(*this, os);

    }

    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0) {
                if (m_pNextStation)
                    *m_pNextStation += std::move(m_orders.front());
                else
                    (m_orders.front().isOrderFilled() ? g_completed : g_incomplete).push_back(std::move(m_orders.front()));

                m_orders.pop_front();
                return true;
            }
        }

        return false;
    }


    void Workstation::setNextStation(Workstation* station) { 
        m_pNextStation = station; 
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation; 
    }

    void Workstation::display(std::ostream& os) const {
        os << (this)->getItemName() << " --> ";
        (m_pNextStation) ?
            (os << m_pNextStation->getItemName()) :
            (os << "End of Line");
        os << "\n";
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}