//
//  ECAirport.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECAirport_h
#define ECAirport_h

#include <string>
#include <set>
#include <map>
#include <vector>



// ****************************************************************************
// Airport: start/end point of a flight

class ECAirport 
{
public:
    // by default, airport is operating (except in default constructor)
    ECAirport(): name(""), code(""), operating(false) {}; 
    ECAirport(const std::string &nameAP, const std::string &codeIATA): name(nameAP), code(codeIATA), operating(true) {};
    ECAirport(const ECAirport &rhs): name(rhs.name), code(rhs.code), operating(rhs.operating) {};
    
    // Get the name of the airport
    std::string GetName() const{return name;}
    
    // Get IATA code
    std::string GetCode() const{return code;}
    
    // Operating status: is it operating normally?
    bool IsOperating() const {return operating;}
    
    // Set operating status
    void SetOperating(bool f) {operating = f;}

private:
    // your code
    std::string name;
    std::string code;
    bool operating;
};

// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

class ECAirportInfo
{
public:
    
    // Create a new airport in the system
    void CreateAirport(const std::string &name, const std::string &code);
    
    // Get airport by code
    // Throw exception (std::string) if there is no airport with the code
    ECAirport &GetAirport(const std::string &code);
    
    // Set distance (in miles) between airports
    void SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, double dist);

    double GetDistance(const std::string &ap1Code, const std::string &ap2Code);

    std::vector<std::string> getCodes(){
        std::vector<std::string> code;
        for(auto& codes: AirportDatabase){
            code.push_back(codes.first);
        }
        return code;
    }
    
    // more to add...
    static ECAirportInfo* Instance(){
        if(infoptr == NULL){
            infoptr = new ECAirportInfo;
        }
        return infoptr;
    }

    double GetFlightTime(const std::string &ap1Code, const std::string &ap2Code);
    
private:
   // your code 
   static ECAirportInfo* infoptr;
   ECAirportInfo(){};
   std::map<std::string, ECAirport> AirportDatabase;
   std::map<std::string, std::map<std::string, double> > AirportDistances;
   std::map<std::pair<std::string, std::string>, double> FlightTime;
};


#endif /* ECAirport_h */
