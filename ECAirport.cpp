//
//  ECAirport.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirport.h"
#include <map>
#include <string>
#include <utility>

void ECAirportInfo::CreateAirport(const std::string &name, const std::string &code){
    ECAirport airport(name,code);
    AirportDatabase[code] = airport;
}

ECAirport &ECAirportInfo::GetAirport(const std::string &code){
    auto airport = AirportDatabase.find(code);
    if(airport == AirportDatabase.end()){
        throw "code not found";
    }
    return airport->second;
}

void ECAirportInfo::SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, double dist){
    AirportDistances[ap1Code][ap2Code] = dist;
    AirportDistances[ap2Code][ap1Code] = dist;
}

double ECAirportInfo::GetDistance(const std::string &ap1Code, const std::string &ap2Code){
    auto OuterMap = AirportDistances.find(ap1Code);
    if(OuterMap != AirportDistances.end()){
        auto InnerMap = OuterMap->second.find(ap2Code);
        if(InnerMap != OuterMap->second.end()){
            return InnerMap->second;
        }
    }
    throw "airport distance not found";
}

ECAirportInfo* ECAirportInfo::infoptr = nullptr;

double ECAirportInfo::GetFlightTime(const std::string &ap1Code, const std::string &ap2Code){
    std::pair<std::string, std::string> airports1;
    airports1.first = ap1Code;
    airports1.second = ap2Code;

    auto time = FlightTime.find(airports1);

    if(time != FlightTime.end()){
        return time->second;
    }

    try{
        double distance = GetDistance(ap1Code, ap2Code);
        double flight = distance / 500;

        FlightTime[airports1] = flight;
        return flight;
    } catch(std::exception& e) {
        return -1;
    }

}

