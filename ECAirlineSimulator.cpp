//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"

#include <iostream>
using namespace std;

void ECAirlineSimulator::AddAirport(const std::string &name, const std::string &code){
    ECAirportInfo *airportInfo = ECAirportInfo::Instance();
    airportInfo->CreateAirport(name,code);
}

void ECAirlineSimulator::SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist){
    ECAirportInfo *airportInfo = ECAirportInfo::Instance();
    airportInfo->SetDistanceBtw(srcAirport,destAirport,dist);
}

// Add flight to flights dictionary using source airport as key
void ECAirlineSimulator::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate ){
    flights[srcAirport].emplace_back(srcAirport, destAirport, tmDepart, maxPassengers, costOperate);
}

const std::vector<ECFlight>& ECAirlineSimulator::GetFlightsFrom(const std::string &airport) const {
    static const std::vector<ECFlight> none; 
    auto it = flights.find(airport);
    if (it != flights.end()) {
        return it->second;
    }
    return none;
}

vector<std::string> ECAirlineSimulator::GetAirportCodes(){
    ECAirportInfo *airportInfo = ECAirportInfo::Instance();
    return airportInfo->getCodes();
}

void ECAirlineSimulator::SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries ) {
    if (!pAirlineTicket) {  // Check if it's already initialized
        pAirlineTicket = new ECAirlineTicketing(*this);  // Initialize it
    }
    pAirlineTicket->SearchForItinerary(src, dest, listItineraries);
}



