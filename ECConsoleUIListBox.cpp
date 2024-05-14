//
//  ECConsoleUIListBox.cpp
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#include "ECConsoleUIListBox.h"

void ECConsoleUIListBox::AddChoice(const std::string &text) {
    choices.push_back(text);
}

// choose item by index
void ECConsoleUIListBox::Choose(int rIndex) {
    if (rIndex >= 0 && rIndex < choices.size()) {
        indexChoice = rIndex;

        // Ensure the chosen item is within the visible region
        int visibleHeight = GetHeight();  // Get visible height
        if (rIndex < topVisibleRow) {
            topVisibleRow = rIndex;
        } else if (rIndex >= topVisibleRow + visibleHeight) {
            topVisibleRow = rIndex - visibleHeight + 1;
        }
    }
}

// ECConsoleUIListBox
void ECConsoleUIListBox::HdlKeyUp() {
    if (indexChoice > 0) {
        indexChoice--;
        if (indexChoice < topVisibleRow) {
            topVisibleRow = indexChoice;
        }
    }
    isOptionSelected = true; // Set the flag to indicate that an option is selected
    indexChoice = indexChoice;
}

void ECConsoleUIListBox::HdlKeyDown() {
    if (indexChoice < choices.size() - 1) {
        indexChoice++;
        if (indexChoice >= topVisibleRow + GetHeight()) {
            topVisibleRow = indexChoice - GetHeight() + 1;
        }
    }
    isOptionSelected = true; // Set the flag to indicate that an option is selected
    indexChoice = indexChoice;
}

void ECConsoleUIListBox::HdlKeyEnter() {
    // Update the indexChoice variable based on the current selection
    selectedChoiceIndex = indexChoice;
    isOptionSelected = true;
    selectedOptionRow = GetYUL() + indexChoice - topVisibleRow;
    selectedOptionXLeft = GetXUL();
    selectedOptionXRight = GetXLR();
}

std::string ECConsoleUIListBox::GetTextAtRow(int r) const {
    std::string text;
    int relativeRow = r - GetYUL();
    if (relativeRow >= 0 && relativeRow < GetHeight()) {
        int index = topVisibleRow + relativeRow;
        if (index >= 0 && index < choices.size()) {
            text = choices[index];
        }
    }
    return text;
}

int ECConsoleUIListBox::GetHighlightPosition(int &xLeft, int &xRight) const {
    int relativeIndex = indexChoice - topVisibleRow;
    if (relativeIndex >= 0 && relativeIndex < GetHeight()) {
        xLeft = GetXUL();
        xRight = GetXLR();
        return GetYUL() + relativeIndex;
    }
    return -1;
}

int ECConsoleUIListBox::GetIndexChoicePlease(){
    return indexChoice;
    }

std::string ECConsoleUIListBox::GetChoice() const { 
    if (selectedChoiceIndex >= 0 && selectedChoiceIndex < choices.size()) {
        return choices[selectedChoiceIndex];
    }
    return "";
}

bool ECConsoleUIListBox::IsHandlingKeys()const{return true;}