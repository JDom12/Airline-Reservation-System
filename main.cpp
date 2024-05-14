#include "ECTextViewImp.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUITextField.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUIButton.h"
#include "ECAirport.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h"
#include "ECAirlineSimulator.h"
#include "ECObserver.h"
#include "ECAirlineFinancial.h"
#include "ECAirlineOperation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Function to load data from a file into the simulator
void loadFromFile(const std::string &filename, ECAirlineSimulator &simulator) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        int type;
        iss >> type;
        switch (type) {
            case 1: {  // Airport info
                std::string code, name;
                iss >> code >> std::ws;  // Consume whitespace
                std::getline(iss, name);
                simulator.AddAirport(name, code);
                break;
            }
            case 2: {  // Distance info
                std::string src, dest;
                int distance;
                iss >> src >> dest >> distance;
                simulator.SetDistBtwAirports(src, dest, distance);
                break;
            }
            case 3: {  // Flight info
                std::string src, dest;
                double time, cost;
                int length;
                iss >> src >> dest >> time >> length >> cost;
                simulator.AddFlight(src, dest, time, length, cost);
                break;
            }
        }
    }
}

class FlightSimulatorUI {
    ECTextViewImp textViewImp;
    ECConsoleUIView* uiView;
    ECConsoleUIListBox* sourceBox;
    ECConsoleUIListBox* destinationBox;
    ECConsoleUIListBox* itinerariesBox;
    ECAirlineSimulator simulator;

public:
    FlightSimulatorUI() : textViewImp(), uiView(new ECConsoleUIView(&textViewImp)),
                          sourceBox(nullptr), destinationBox(nullptr), itinerariesBox(nullptr), simulator() {
        loadFromFile("data.txt", simulator);
        buildUI();
    }

    ~FlightSimulatorUI() {
        delete uiView; 
        delete sourceBox;
        delete destinationBox;
        delete itinerariesBox;
    }

    void buildUI() {
        sourceBox = new ECConsoleUIListBox(20, 6, 60, 16);
        destinationBox = new ECConsoleUIListBox(67, 6, 108, 16);
        itinerariesBox = new ECConsoleUIListBox(20, 30, 115, 50);  

        ECConsoleUITextLabel* appTitle = new ECConsoleUITextLabel(40, 1, "Flight Simulator App");
        uiView->AddUIItem(appTitle);

        ECConsoleUITextLabel* sourceLabel = new ECConsoleUITextLabel(20, 4, "Source Airport");
        uiView->AddUIItem(sourceLabel);

        ECConsoleUITextLabel* destinationLabel = new ECConsoleUITextLabel(67, 4, "Destination Airport");
        uiView->AddUIItem(destinationLabel);

        for (const auto& code : simulator.GetAirportCodes()) {
            sourceBox->AddChoice(code);
            destinationBox->AddChoice(code);
        }
        

        ECConsoleUIButton* searchButton = new ECConsoleUIButton(35, 20, 52, 20, "Search Flights");
        searchButton->SetAction([&]() {
            std::string src = sourceBox->GetChoice();
            std::string dest = destinationBox->GetChoice();
            std::vector<ECFlightItinerary> results;
            simulator.SearchForFlights(src, dest, results);
            updateItinerariesList(itinerariesBox, results);
            uiView->Refresh();
        });

        uiView->AddUIItem(sourceBox);
        uiView->AddUIItem(destinationBox);
        uiView->AddUIItem(searchButton);
        uiView->AddUIItem(itinerariesBox);
    }

    void updateItinerariesList(ECConsoleUIListBox* itinerariesBox, const std::vector<ECFlightItinerary>& itineraries) {
        itinerariesBox->ClearChoices();
        std::ostringstream stream;

        for (const auto& itinerary : itineraries) {
            stream.str("");  // Clear the stream
            stream.clear();  // Clear any error flags
            stream << std::fixed << std::setprecision(2);

            // Concatenate all flights in the itinerary into one string
            bool first = true;
            for (const auto& flight : itinerary.GetFlights()) {
                if (!first) {
                    stream << " | ";  
                }
                stream << "Flight from: " << flight.GetSource() << " to: " << flight.GetDest()
                    << " at: "<< flight.GetDepartureTime();
                first = false;
            }

            itinerariesBox->AddChoice(stream.str());
        }
    }


    void run() {
        uiView->Refresh();
        textViewImp.Show();
    }
};


// Main function: Set up the text view, UI view, load data, and display the UI
int main() {
    try {
        FlightSimulatorUI app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
