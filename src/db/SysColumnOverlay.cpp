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

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "DBOverlay.h"

using namespace std;

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "SysColumnOverlay.h"
#include "DPPageOverlay.h"
#define COL_DP 2

SysColumnOverlay::SysColumnOverlay(){
    
}
   
SysColumnOverlay::SysColumnOverlay(genpage *pg, long ipriority):DBOverlay(pg,ipriority){
    TID = NULL;
    no_columns = NULL;
    icolumn = NULL;
}

SysColumnOverlay::~SysColumnOverlay(){
        
}

//this will add a new dbpage to the syscolumn DPs
//long SysColumnOverlay::CreateSyscolumnPage(genpage *newSysColumnPage){
//    //this is actually a DB Page which is created by DBPage Overlay
//
//    sysColumnPage = newSysColumnPage;
//    sysColumnPage->_priority = SYS_COLUMN_PRIORITY;
//    //get syscolumn DPPAGE i.e, page#2
//    //buffer_manager bm;
//    //SysColumnHeader *sysColHead;
//    //sysColHead = (SysColumnHeader *)sysColumnPage->_data;
//    //genpage *pg = bm.WritePage(Current_Open_DB_Name, SYS_COLUMN_PAGE);
//
//
//}


unsigned long SysColumnOverlay::computeSize(mega_struct* mega)
{
    unsigned long space_req=0, numPattr=0;
    unsigned int i;
    numPattr = mega->NumPattr;
    space_req = 2*sizeof(long); // For TID and no of columns
    space_req = space_req + (numPattr)*(sizeof(column_mask)-sizeof(char));
    for (i=0;i<numPattr;i++)
    {
        /*if (mega->Pattr[i].value != NULL)
        {
            space_req = space_req + mega->Pattr[i].length;
        }
         */
    }
    return space_req;

}

void SysColumnOverlay::updateDataPtr()
{
    updateDataCursor();
    TID = (long*)icursor;
    no_columns = (unsigned int *)(TID + 1);
    icolumn = (column_mask *)(no_columns + 1);

}

void SysColumnOverlay::gotoNextCol()
{
    char *myptr;
    myptr = (char *)icolumn;

    if (icolumn->def_default == true)
    {
        myptr = myptr + icolumn->length;
    }

    myptr = myptr + sizeof(column_mask) - 1;
    icolumn = (column_mask *)myptr;
}

RID SysColumnOverlay::AddSysColumnEntry(mega_struct *mega, long tid, unsigned long space_req){
    
//    unsigned long space_req=0, numPattr=0;
//    unsigned int i;
    char *myptr;
//    numPattr = mega->NumPattr;
//    space_req = 2*sizeof(long); // For TID and no of columns
//    space_req = space_req + (numPattr)*(sizeof(column_mask)-sizeof(char));
//    for (i=0;i<numPattr;i++)
//    {
//        /*if (mega->Pattr[i].value != NULL)
//        {
//            space_req = space_req + mega->Pattr[i].length;
//        }
//         */
//    }
    unsigned long numPattr = 0;
    int i;
    numPattr = mega->NumPattr;
    newSlot(space_req);
    updateDataPtr();

    *TID = tid;
    *no_columns = numPattr;

    myptr = (char*)icolumn;
    Attribute *a;
    // Go ahead store the schema
    for (i=0; i<numPattr; i++)
    {
        
        a = mega->Pattr.at(i);
        icolumn->def_default = false;
        memcpy(icolumn->column_name, a->attr_name, NAME_LENGTH);
        icolumn->is_null = a->IsNull;
        icolumn->is_primary = a->IsPrimary;
        icolumn->ppos = i + 1;
        icolumn->length = a->length;
/*
        if (mega->Pattr[i].value != NULL)
        {
            icolumn->def_default = true;
            memcpy(icolumn->default_value, (char*)mega->Pattr[i].value, mega->Pattr[i].length);
            myptr = myptr + mega->Pattr[i].length;
        }
 */

        icolumn->type = a->type;

        myptr = myptr + sizeof(column_mask) - 1;
        icolumn = (column_mask *)myptr;
    }

    // Returning the RID
    RID retRid;
    retRid.pageno = dbpage->_page_number;
    retRid.slotno = curSlotNo;
    return retRid;
//    if(sysColumnPage == 0){
//        ShowError();
//        return -1;
//    }
}


bool SysColumnOverlay::FindTable(long tid)
{
    firstSlot();

    for (int i=0; i<getNumberOfSlots(); i++)
    {
        updateDataPtr();
        if ( *TID == tid )
        {
            return true;
        }
        nextSlot();
    }
    firstSlot();
    return false;
}


long SysColumnOverlay::DeleteSysColumnEntry(){
//    if(sysColumnPage == 0){
//        ShowError();
//        return -1;
//    }
    
}

void SysColumnOverlay::PrintSysColumn(){

    cout << "TID: " << *TID << endl;
    cout << "No of Cols: " << *no_columns << endl;

    for (unsigned int i=0; i< *no_columns; i++)
    {
        cout << endl;
        cout << "Name of Column: " << icolumn->column_name << endl;
        cout << "Type: " << icolumn->type << endl;
        cout << "PPOS: " << icolumn->ppos << endl;
        cout << "Length: " << icolumn->length << endl;
        cout << "IsNull: " << icolumn->is_null << endl;
        cout << "IsPrimary: " << icolumn->is_primary << endl;
        cout << "IsDefault: " << icolumn->def_default << endl;

        gotoNextCol();
    }
    
}

int SysColumnOverlay::FillAttributeNames(mega_struct *mega){

    Attribute *b;

    for (unsigned int i=0; i< *no_columns; i++)
    {

        b = (Attribute *)malloc(sizeof(Attribute));

        strcpy(b->attr_name, icolumn->column_name);

        mega->Pattr.push_back(b);

        gotoNextCol();
    }

    mega->NumPattr = *no_columns;

    return 0;
}

void SysColumnOverlay::FillmegaStruct(mega_struct *mega){


        for(int j = 0; j< mega->NumPattr; j++){

             updateDataPtr();
            for (unsigned int i=0; i< *no_columns; i++){


                if(strcmp(mega->Pattr[j]->attr_name,icolumn->column_name)== 0){

                    mega->Pattr[j]->type = icolumn->type;

                    mega->Pattr[j]->ppos = icolumn->ppos;

                    mega->Pattr[j]->length = icolumn->length;

                    mega->Pattr[j]->IsNull =  icolumn->is_null;

                    mega->Pattr[j]->IsPrimary = icolumn->is_primary;

                    break;
                }

                printf("\nnlength = %d\n ", mega->Pattr[j]->length);
                printf("\nni_column length = %d\n ", icolumn->length);
                printf("\nnType = %d\n ", icolumn->type);
            gotoNextCol();

            }

           
    
        }

         for(int j = 0; j< mega->NumSattr; j++){

            for (unsigned int i=0; i< *no_columns; i++){


                if(strcmp(mega->Sattr[j]->attr_name,icolumn->column_name)== 0){

                    mega->Sattr[j]->type = icolumn->type;

                    mega->Sattr[j]->ppos = icolumn->ppos;

                    mega->Sattr[j]->length = icolumn->length;

                    mega->Sattr[j]->IsNull =  icolumn->is_null;

                    mega->Sattr[j]->IsPrimary = icolumn->is_primary;

                }
            gotoNextCol();

            }


        }

   
}




void SysColumnOverlay::ShowError(){
    printf("\n the syscolumn page is not initialized..stop!!\n");
}
