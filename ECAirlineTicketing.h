//
//  ECAirlineTicketing.h
//  
//
//  Created by Yufeng Wu on 5/12/23.
//

#ifndef ECAirlineTicketing_h
#define ECAirlineTicketing_h


// ****************************************************************************
// Airline ticketing: search for flights, issue tickets, etc
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include "ECAirlineSimulator.h"
#include "ECFlightItinerary.h"
#include "ECFlight.h"


class ECAirlineSimulator;

class ECAirlineTicketing {
public:
    // Initialize with a reference to the flights data from the simulator
    ECAirlineTicketing(const ECAirlineSimulator& simulator) : simulator(simulator) {}

    void SearchForItinerary(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const;

private:
    const ECAirlineSimulator& simulator;

    void DFS(const std::string &current, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries, std::vector<ECFlight> &path, std::set<std::string> &visited) const;
};

#endif /* ECAirlineTicketing_h */
