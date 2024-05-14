//
//  ECConsoleUITextField.h
//  
//
//  Created by Yufeng Wu on 5/24/23.
//

#ifndef ECConsoleUITextField_h
#define ECConsoleUITextField_h

#include <string>
#include <vector>
#include <iostream>

#include "ECConsoleUIItem.h"
class ECTextViewImp;

//*****************************************************************************
// Console UI list box: several rows (items) to choose from

class ECConsoleUITextField : public ECConsoleUIItem
{
public:
    // specifiy the starting point of the text field
    ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len):ECConsoleUIItem(xpos,ypos,xpos+len+1, ypos), isEditable(true), isActive(false), fieldText(""){textView = pTextView;};
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const;

    // Are there any other function you might need to override?

    void HandleBackspace();
    void HandleCtrlC();
    void HandleCharInput(char c);
    virtual void HdlKeyEnter();
    virtual bool IsHandlingKeys() const { return isEditable; }
    void HdlOtherKey();
    
    
private:
    bool isEditable;
    bool isActive;
    std::string fieldText;
    ECTextViewImp *textView;
};

#endif /* ECConsoleUITextField_h */
