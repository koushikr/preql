/* 
 * File:   MegaStruct.h
 * Author: sahil
 *
 * Created on December 29, 2010, 1:33 AM
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
