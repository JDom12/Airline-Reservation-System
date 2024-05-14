//
//  ECAirlineSimulator.hpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//  Simulate airline activities: booking, flights, etc

#ifndef ECAirlineSimulator_h
#define ECAirlineSimulator_h

#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include "ECFlight.h"
#include "ECAirlineTicketing.h"

class ECAirlineOperation;
class ECAirlineTicketing;
class ECAirlineFinancial;
class ECFlightItinerary;


//****************************************************************************
// Airline simulator

class ECAirlineSimulator
{
public:
    ECAirlineSimulator()
        : pAirlineTicket(nullptr) {
    }

    ~ECAirlineSimulator() {
        delete pAirlineTicket;
    }
    
    // *****************************************************
    // Configuration
    
    // Adding airport with name and IATA code
    void AddAirport(const std::string &name, const std::string &code);
    
    // Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
    void SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist);
    
    // Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate );
    
    // Called to indicate no more flights to add
    void DoneFlightAdding(){};

    std::vector<std::string> GetAirportCodes();
    

    // *****************************************************
    // Flight search
    
    // Searcch for flights; return all flights in listItineraries that go from src to dest
    void SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries ) ;
    
    const std::vector<ECFlight>& GetFlightsFrom(const std::string &airport) const;

    void PreferLowPrice(){};
    void PreferShortTime(){};
    void PreferEarlyArrival(){};

    // Access airlines
    //ECAirlineFinancial *GetAirlineFin() { return pAirlineFin; }
    ECAirlineOperation *GetAirlineOp() { return pAirlineOp; }
    ECAirlineTicketing *GetAirlineTicketing() { return pAirlineTicket; }

    
private:
    // initialize
    void Init();
    
    // key data member
    ECAirlineOperation *pAirlineOp;
    ECAirlineFinancial *pAirlineFin;
    ECAirlineTicketing *pAirlineTicket;

    std::unordered_map<std::string, std::vector<ECFlight> > flights; 
};


#endif /* ECAirlineSimulator_h */
