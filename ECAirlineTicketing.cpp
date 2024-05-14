//
//  ECAirlineTicketing.cpp
//  
//
//  Created by Yufeng Wu on 5/12/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineTicketing.h"
#include "ECFlightItinerary.h"
#include <string>
#include <queue>

using namespace std;

void ECAirlineTicketing::SearchForItinerary(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries)const {
    std::vector<ECFlight> currentPath;
    std::set<std::string> visited;
    DFS(src, dest, listItineraries, currentPath, visited);
}

void ECAirlineTicketing::DFS(const std::string &current, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries, std::vector<ECFlight> &path, std::set<std::string> &visited) const {
        if (visited.count(current)) return;  // prevent revisiting/cycles
        if (current == dest) {
            // Convert path to itinerary and add to list
            ECFlightItinerary itinerary;
            for (auto& flight : path) {
                itinerary.AddFlight(flight);
            }
            listItineraries.push_back(itinerary);
            return;
        }

        visited.insert(current);
        auto& flights = simulator.GetFlightsFrom(current);
        for (auto& flight : flights) {
            if (path.empty() || path.back().GetArrivalTime() <= flight.GetDepartureTime()) {
                path.push_back(flight);
                DFS(flight.GetDest(), dest, listItineraries, path, visited);
                path.pop_back();  
            }
        }
        visited.erase(current);  
    };

