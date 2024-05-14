//
//  ECConsoleUIView.cpp
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#include "ECConsoleUIView.h"
#include "ECTextViewImp.h"
#include "ECConsoleUIItem.h"
#include "ECConsoleUIListBox.h"

#include <iostream>
using namespace std;

//*****************************************************************************
// Generic console UI view
// Displays some info on the screen, and then respond to user actions


ECConsoleUIView :: ECConsoleUIView(ECTextViewImp *pTextViewIn) : pTextView(pTextViewIn), indexActiveUI(0)
{
    // register with the view for listening to key events
    pTextView->Attach(this);
}

ECConsoleUIView :: ~ECConsoleUIView()
{
    for(unsigned int i=0; i<listUIItems.size(); ++i)
    {
        delete listUIItems[i];
    }
    pTextView->Detach(this);
}

// Add UI item
void ECConsoleUIView :: AddUIItem(ECConsoleUIItem *pUIItem)
{
    listUIItems.push_back(pUIItem);
}

// Display this view
void ECConsoleUIView :: Refresh()
{
    pTextView->InitRows();
    for(int r=0; r<GetRowNumInView(); ++r)
    {
        cout << r << endl;
        string row = ComposeRow(r);
        pTextView->AddRow( row );
    }
    // Deal with highlight part: check each item to see if they have part to highlight
    // fisrt clear all preivous color
    pTextView->ClearColor();
    
    // Set active item color
    if (indexActiveUI >= 0 && listUIItems[indexActiveUI]->IsHandlingKeys()) {
        ECConsoleUIListBox* activeListBox = dynamic_cast<ECConsoleUIListBox*>(listUIItems[indexActiveUI]);
        if (activeListBox != nullptr) {
            // Set general blue color for the active list box
            for (int r = activeListBox->GetYUL(); r <= activeListBox->GetYLR(); ++r) {
                pTextView->SetColor(r, activeListBox->GetXUL(), activeListBox->GetXLR(), TEXT_COLOR_BLUE);
            }
        }
    }

    // Set red color for the selected option in each list box
    for (unsigned int i = 0; i < listUIItems.size(); ++i) {
        ECConsoleUIListBox* listBox = dynamic_cast<ECConsoleUIListBox*>(listUIItems[i]);
        if (listBox != nullptr) {
            int selectedRow = listBox->GetSelectedOptionRow();
            int selectedXLeft = listBox->GetSelectedOptionXLeft();
            int selectedXRight = listBox->GetSelectedOptionXRight();
            if (selectedRow >= 0) {
                pTextView->SetColor(selectedRow, selectedXLeft, selectedXRight, TEXT_COLOR_RED);
            }
        }
    }
    
    // set highlight color
    for(unsigned int i=0; i<listUIItems.size(); ++i)
    {
        int xLeft = -1, xRight = -1;
        int r = listUIItems[i]->GetHighlightPosition( xLeft, xRight );
        if( r >= 0 )
        {
            if( xLeft < 0 || xRight < 0)
            {
                throw std::string("Hight part wrong!");
            }
            int rconv = r + listUIItems[i]->GetYUL();
            int xLconv = xLeft + listUIItems[i]->GetXUL();
            int xRconv = xRight + listUIItems[i]->GetXUL();
            pTextView->SetColor(rconv, xLconv, xRconv, TEXT_COLOR_RED);
        }
    }
    // Refresh
    pTextView->Refresh();
}

// Respond to key events
void ECConsoleUIView :: Update()
{
    int keyPressed = pTextView->GetPressedKey();
    if( indexActiveUI < 0 || indexActiveUI>=(int)listUIItems.size() )
    {
        // no active UI item, ignore the event
        return;
    }
    ECConsoleUIItem *pActiveUI = listUIItems[indexActiveUI];
    // use control-A to shift through active UI item
    if( keyPressed == CTRL_A )
    {
        // move to the next UI that accepts user input
        for(int i=0; i<(int)listUIItems.size(); ++i)
        {
            ++indexActiveUI;
            if(indexActiveUI >= (int)listUIItems.size() )
            {
                indexActiveUI = 0;
            }
            if( listUIItems[indexActiveUI]->IsHandlingKeys() )
            {
                break;
            }
        }
        pTextView->SetCursorX(listUIItems[indexActiveUI]->GetXUL() - 1);
        pTextView->SetCursorY(listUIItems[indexActiveUI]->GetYUL());
    }
    else if( keyPressed == ARROW_UP )
    {
        pActiveUI->HdlKeyUp();
    }
    else if( keyPressed == ARROW_DOWN )
    {
        pActiveUI->HdlKeyDown();
    }
    else if( keyPressed == ENTER )
    {
        pActiveUI->HdlKeyEnter();
    }
    else
    {
        pActiveUI->HdlOtherKey();
    }
    // ignore all other keys for now
    // Refresh
    Refresh();
}

// Compose a row in the view
std::string ECConsoleUIView :: ComposeRow(int r) const
{
    // check for all UI items
    string strText;
    
    int xl = GetRightmostUIItemAtRow(r);
    if( xl < 0 )
    {
        return strText;
    }
    // fill blanks with the length of this UI item
    for(int x=0; x<=listUIItems[xl]->GetXLR(); ++x)
    {
        strText += ' ';
    }
    
    for(unsigned int i=0; i<listUIItems.size(); ++i)
    {
        string strTextUI = listUIItems[i]->GetTextAtRow(r);
        // fill in the position
        for(int x=0; x<strTextUI.size(); ++x)
        {
            // convert to position
            int posUse = x + listUIItems[i]->GetXUL();
            if( posUse >= (int)strText.size() )
            {
                //strText[posUse] = strTextUI[x];
                throw string("Out of bound");
            }
            strText[posUse] = strTextUI[x];
        }
    }
    return strText;
}

// Get the number of rows in view
int ECConsoleUIView :: GetRowNumInView() const
{
    return pTextView->GetRowNumInView();
}

// Get the number of rows in view
int ECConsoleUIView :: GetColNumInView() const
{
    return pTextView->GetColNumInView();
}

// Is there a UI item in this row? if so, return the index of this UI item with the rightmost position; otehrwise, return -1
int ECConsoleUIView :: GetRightmostUIItemAtRow(int r) const
{
    int res = -1;
    int posRightmost = -1;
    for(unsigned int i=0; i<listUIItems.size(); ++i)
    {
        if( listUIItems[i]->IsIntersectingRow(r) )
        {
            int xRight = listUIItems[i]->GetXLR();
            if( xRight > posRightmost )
            {
                res = i;
                posRightmost = xRight;
            }
        }
    }
    return res;
}
