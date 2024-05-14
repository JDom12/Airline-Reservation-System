# Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = 

SOURCES = main.cpp ECTextViewImp.cpp ECConsoleUIListBox.cpp ECConsoleUITextLabel.cpp \
          ECConsoleUITextField.cpp ECConsoleUIView.cpp ECConsoleUIButton.cpp \
          ECAirport.cpp ECFlight.cpp ECFlightItinerary.cpp ECAirlineSimulator.cpp \
          ECAirlineTicketing.cpp ECAirlineFinancial.cpp ECAirlineOperation.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = FlightSimulatorApp

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
