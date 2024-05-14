//
//  ECConsoleUITextField.cpp
//  
//
//  Created by Yufeng Wu on 5/24/23.
//

#include "ECConsoleUITextField.h"
#include "ECTextViewImp.h"

using namespace std;

// ECConsoleUITextField
std::string ECConsoleUITextField::GetTextAtRow(int r) const {
    if (r == GetYUL()) {
        return ":" + fieldText;
    }
    return "";
}

int ECConsoleUITextField::GetHighlightPosition(int &xLeft, int &xRight) const {
    if (isEditable || isActive) {
        xLeft = GetXUL() + 1;
        xRight = GetXUL() + 1 + fieldText.length();
        return GetYUL();
    }
    return -1;
}

void ECConsoleUITextField::HandleBackspace() {
    if (isEditable && !fieldText.empty())
    {
        fieldText.pop_back();
        textView->SetCursorX(GetXUL() + 1 + fieldText.length());
        textView->Refresh();
    }
}

void ECConsoleUITextField::HandleCtrlC() {
    if (isEditable) {
        isActive = false;
        textView->SetCursorX(GetXUL() - 1);
    }
}

void ECConsoleUITextField::HandleCharInput(char c) {
    if (isEditable)
    {
        fieldText += c;
        textView->SetCursorX(GetXUL() + 1 + fieldText.length());
        textView->Refresh();
    }
}

void ECConsoleUITextField::HdlKeyEnter() {
    if (isEditable) {
        isActive = true; // Set the flag to indicate active state
        textView->SetCursorX(GetXUL() + 1 + fieldText.length());
        textView->SetCursorY(GetYUL());
        textView->Refresh();
    }
}

void ECConsoleUITextField::HdlOtherKey()
{
    if (isEditable)
    {
        int keyPressed = textView->GetPressedKey();
        if (isprint(keyPressed))
        {
            char c = static_cast<char>(keyPressed);
            HandleCharInput(c);
        }
        else if (keyPressed == BACKSPACE)
        {
            HandleBackspace();
        }
        else if (keyPressed == CTRL_C)
        {
            HandleCtrlC();
        }
    }
}