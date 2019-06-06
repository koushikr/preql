/* 
 * File:   UI.h
 * Author: anmol
 *
 * Created on 5 December, 2010, 7:00 PM
 */


#ifndef UI_H
#define	UI_H

#include "globals.h"
#include "db.h"
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

class UI {
public:
    UI();
    UI(const UI& orig);
    virtual ~UI();

    // Static Functions
    static void PrintData(mega_struct *mega);
    static void PrintColumns(mega_struct *mega);
    static void PrintSchema(mega_struct *mega);
private:

};
//extern void UI::PrintData(mega_struct* mega);
#endif	/* UI_H */

