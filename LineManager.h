// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Dec 2,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include "Workstation.h"
#include <iostream>
#include <vector>

namespace sdds {
    class LineManager {
    private:
        std::vector<Workstation*> m_activeLine{};
        size_t m_cntCustomer{ 0 };
        Workstation* m_firstStation{ nullptr };
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os = std::cout);
        void display(std::ostream& os = std::cout) const;
    };
}

#endif // SDDS_LINEMANAGER_H