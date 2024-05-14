//
//  ECFlightItinerary.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlightItinerary.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

double ECFlightItinerary::GetFlightTime() const{
    double total = 0;
    for(const auto& x: itinerary){
        total += x.GetTime(x.GetSource(), x.GetDest());
    }
    return total;
}

double ECFlightItinerary::GetDepartTime() const {
    return itinerary[0].GetDepartureTime();
}

double ECFlightItinerary::GetArrivalTime() const{
    return itinerary[itinerary.size() - 1].GetArrivalTime();
}

double ECFlightItinerary::GetPrice()const {
    double total = 0;
    for(auto& x: itinerary){
        total += x.AirTimePrice();
    }
    return total;
}

void ECFlightItinerary::Dump(){
    std::cout << "FLIGHT:" << std::endl;
    for (const auto& flight : itinerary) {
        std::cout << "Flight from: " << flight.GetSource() 
                  << " to: " << flight.GetDest() << std::endl;
        std::cout << "Departure Time: " << flight.GetDepartureTime() 
                  << " hrs, Arrival Time: " << flight.GetArrivalTime() 
                  << " hrs" << std::endl;
        std::cout << "Time in the air: " << flight.GetTime(flight.GetSource(), flight.GetDest()) 
                  << " hrs" << std::endl;
    }
}

std::string ECFlightItinerary::GetDescription() const
{
    std::string output = "";
    for(const auto& flight: itinerary){
        output += "Flight from: " + flight.GetSource() + " to: " + flight.GetDest();
    }
    return output;
}






