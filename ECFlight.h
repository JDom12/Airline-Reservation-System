//
//  ECFlight.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlight_h
#define ECFlight_h

#include <string>
#include <sstream>
#include <iomanip>
#include "ECAirport.h"


// ****************************************************************************
// Flight: service between two airports at a specific time;

class ECFlight 
{
public:
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn, double cost)
    : source(srcIn), dest(destIn), depart(tmDepartIn), MaxPass(maxPassengersIn), OperatingCost(cost)
    {
    }
    virtual ~ECFlight()
    {
    }
    
    // Get departure time
    double GetDepartureTime() const {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << depart;
        return std::stod(stream.str());
    }
    
    // Get arrival time
    double GetArrivalTime() const {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << (depart + static_cast<double>(GetTime(source, dest)));
        return std::stod(stream.str());
    }    
    // Set max passenger for this
    void SetMaxNumPassengers(int m) {MaxPass = m;}
    
    // Get src airport code
    std::string GetSource() const {return source;}
    
    // Get destination code
    std::string GetDest() const {return dest;}
    // more to add...    

    //return flight time
    double GetTime(const std::string &code1, const std::string &code2) const {
        ECAirportInfo* airportInfo = ECAirportInfo::Instance();
        return airportInfo->GetFlightTime(code1, code2);
    }

    double AirTimePrice()const{
        return GetTime(source, dest) * 120;
    }

private:
    // your code
    double OperatingCost;
    double depart;
    int MaxPass;
    std::string source;
    std::string dest;
};

#endif /* ECFlight_h */
