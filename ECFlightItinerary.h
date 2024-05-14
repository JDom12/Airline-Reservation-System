//
//  ECFlightItinerary.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlightItinerary_h
#define ECFlightItinerary_h

#include <vector>
#include <string>
#include "ECFlight.h"

class ECAirlineFinancial;

// ****************************************************************************
// Flight itineary: consisting segments of flights so to go from one airport to another airport

class ECFlightItinerary
{
public:
    ECFlightItinerary() = default;
    
    // access/edit segments
    // Return the number of segments of the itineary
    int GetNumSegments() const{return itinerary.size();};
    
    // Return a segment
    ECFlight *GetSegment(int segIndex) const {return const_cast<ECFlight*>(&itinerary[segIndex]);};
    
    // Get flight time: from departure to arrival
    double GetFlightTime() const;
    
    // Get segment time: add the time of all segments
    double GetTimeAllSegments() const;
    
    // Get departure time
    double GetDepartTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Price 
    double GetPrice() const;

    void AddFlight(ECFlight &flight) {itinerary.push_back(flight);}

    const std::vector<ECFlight>& GetFlights() const{return itinerary;};


    void Dump();

    std::string GetDescription() const;
    
    
private:
    // your code
    std::vector<ECFlight> itinerary;
};

#endif /* ECFlightItinerary_h */
