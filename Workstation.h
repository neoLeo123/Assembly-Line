// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Dec 2,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"
#include <deque>

namespace sdds {

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation:public Station {
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{ nullptr };
    public:

        Workstation(const std::string& src);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;

    };
}


#endif