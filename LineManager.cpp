// Name:Leo Ru
// Seneca Student ID: 144337227
// Seneca email: lru1@myseneca.ca
// Date of completion:Dec 2,2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace sdds {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream inputfile(file);
        if (!inputfile.is_open()) {
            throw "Failed to open file";
        }
        Utilities utils;
        std::string line;
        bool more = true;
        size_t nextpos = 0;
        size_t nextcopy = nextpos;
        std::vector<std::string> lStations;
        std::vector<std::string> rStations;

        while (std::getline(inputfile, line)) {
            nextpos = nextcopy;

            std::string cStation, tStation{};
            cStation = utils.extractToken(line, nextpos, more);

            if (!(nextpos == nextcopy)) {
                tStation = utils.extractToken(line, nextpos, more);

                lStations.push_back(cStation);
                rStations.push_back(tStation);
            }
            auto currStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return station->getItemName() == cStation;
                });

            m_activeLine.push_back(*currStation);


            if (!tStation.empty()) {
                auto nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == tStation;
                    });
                (*currStation)->setNextStation(*nextStation);
            }
        }

       
        std::string firstS{};
        auto it = std::find_if(lStations.begin(), lStations.end(), [&](const auto& leftStation) {
            return std::none_of(rStations.begin(), rStations.end(), [&](const auto& rightStation) {
                return leftStation == rightStation;
                });
            });

        if (it != lStations.end()) {
            firstS = *it;
        }

        auto firstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
            return station->getItemName() == firstS;
            });
        m_firstStation = *firstStation;

        m_cntCustomer = g_pending.size();
    }

  void LineManager::reorderStations() {
    std::vector<Workstation*> reorderedStations;
    
    for (Workstation* currentStation = m_firstStation; currentStation != nullptr; currentStation = currentStation->getNextStation()) {
        reorderedStations.push_back(currentStation);
    }
    
    m_activeLine = reorderedStations;
}

    bool LineManager::run(std::ostream& os) {
    static size_t iterationCount = 1;
    os << "Line Manager Iteration: " << iterationCount << std::endl;
    ++iterationCount;

    if (!g_pending.empty()) {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }

    for (auto& station : m_activeLine) {
        station->fill(os);
        
    }
    for (auto& station : m_activeLine) {
        station->attemptToMoveOrder();

    }
   
    return (g_completed.size() + g_incomplete.size()) == m_cntCustomer;
}

    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
            station->display(os);
            });
    }
}