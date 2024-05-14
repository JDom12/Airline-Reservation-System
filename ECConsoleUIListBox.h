//
//  ECConsoleUIListBox.h
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#ifndef ECConsoleUIListBox_h
#define ECConsoleUIListBox_h

#include <string>
#include <vector>
#include <iostream>
#include <functional>

#include "ECConsoleUIItem.h"

//*****************************************************************************
// Console UI list box: several rows (items) to choose from

class ECConsoleUIListBox : public ECConsoleUIItem
{
public:
    // specifiy the portion of the view for this list box
    ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR ): ECConsoleUIItem(xUL, yUL, xLR, yLR), indexChoice(0), topVisibleRow(0), selectedOptionRow(-1), selectedOptionXLeft(-1), selectedOptionXRight(-1), selectedChoiceIndex(0) 
    {}    //std::cout << "List Box Initialized: UL=(" << xUL << "," << yUL << "), LR=(" << xLR << "," << yLR << ")\n";};
    
    // Add a choice item
    void AddChoice(const std::string &text);
    
    // Choose an item
    void Choose(int rIndex);
    
    // Get the chosen one
    std::string GetChoice() const ;

    
    int GetIndexChoicePlease();
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const;

    // Are there any other function you might need to override?

    bool IsHandlingKeys() const;

    void HdlKeyUp();

    void HdlKeyDown();

    void HdlKeyEnter() override;
    
    int GetSelectedOptionRow() const { return selectedOptionRow; }
    int GetSelectedOptionXLeft() const { return selectedOptionXLeft; }
    int GetSelectedOptionXRight() const { return selectedOptionXRight; }

    void ClearChoices(){choices.clear();}

    int GetChoicesCount() {return choices.size();}

private:
    std::vector<std::string> choices;
    int indexChoice;
    int topVisibleRow;
    bool isOptionSelected;
    int selectedOptionRow;
    int selectedOptionXLeft;
    int selectedOptionXRight;
    int selectedChoiceIndex;
};

#endif /* ECConsoleUIListBox_h */
