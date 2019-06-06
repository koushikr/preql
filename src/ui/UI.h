/*
 * Copyright 2019 Koushik R <rkoushik.14@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

