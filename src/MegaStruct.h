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
#ifndef MEGASTRUCT_H
#define	MEGASTRUCT_H

#include "stdlib.h"
#include "string.h"
#include "db.h"


class MegaStruct {
public:
    MegaStruct();
    MegaStruct(const MegaStruct& orig);
    // Initialization would create a memory for the megastructure and return with initial values
    static mega_struct* Initialize();
    // Allocate will allocate the length specified in Pattr and Sattr
    static void Allocate(mega_struct* mega);
    // Clean will reinitialize the holders in Pattr and Sattr
    static void Clean(mega_struct* mega);
    // This will free up all the used memory, address of the mega structure pointer has to be passed to it
    static void Destroy( mega_struct **mega );
    virtual ~MegaStruct();
private:

};

#endif	/* MEGASTRUCT_H */
