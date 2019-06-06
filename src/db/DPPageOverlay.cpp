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

using namespace std;

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "DPPageOverlay.h"

DPPageOverlay::DPPageOverlay(genpage* pg){

    dpPage = pg;
    if(pg->_priority != DP_PRIORITY){
         CreateDPPage();
    }

}
DPPageOverlay::~DPPageOverlay(){
    
}
int DPPageOverlay::CreateDPPage(){

    printf("\ninside dp page create");

    //dpPage = newDPPage;
    dpPage->_priority = DP_PRIORITY;

    dpPage->_TFS = dpPage->_TFS - sizeof(dpPage);

    dp_page *dp;

    de_struct *de;

    dp = (dp_page *)dpPage->_data;

    dp->DE_number = 0;

    dp->max_TFS_withinTheDP = PG_DATASIZE;

    de = (de_struct *)((dpPage->_data) + sizeof(dp_page));
    
    for(int i = 0 ; i < maxDE ; i++)
    {
        de->page_TFS = PG_DATASIZE;

        de->page_num = -1;
        
        de++;
    }
    
    return SUCCESS;

}


long DPPageOverlay::getDPHeaderDECount(){

    de_struct *de;

    long count;

    de = (de_struct *)((dpPage->_data) + sizeof(dp_page));

    for(int i = 0 ; i < maxDE ; i++)
    {
        if(de->page_num != -1){
            
            count++;
        }
    }
    return count;

}
long DPPageOverlay::getMaxTFSwithinDE(){

    de_struct *de;

    dp_page *dpheader;

    long i;

    dpheader = (dp_page *)dpPage->_data;

    de = (de_struct *)((dpPage->_data) + sizeof(dp_page));

    long max_tfs = de->page_TFS;

    //for(long i=(PG_DATASIZE - sizeof(dp_page)/sizeof(de_struct)) ; i > 0 ; i--)

    //if(dpheader->DE_number == maxDE){

    for(i = 0 ; i < maxDE ; i++){
        
        if(de->page_TFS > max_tfs){

            max_tfs = de->page_TFS;
        }

        de++;
    }
   // }
    //else max_tfs = PG_DATASIZE;
    return max_tfs;

}


int DPPageOverlay::setDPHeaderDECount(long count){

    dp_page *dp;

    dp =(dp_page *) dpPage->_data;

    dp->DE_number = count;

    return SUCCESS;

}


int DPPageOverlay::setMaxTFSwithinDE(long max_tfs){

    dp_page *dp;

    dp = (dp_page *)dpPage->_data;

    dp->max_TFS_withinTheDP = max_tfs;

    return SUCCESS;
}


de_struct* DPPageOverlay::DE_Search_by_dbPageNumber(long dbPageNumber){
    
    
}

long DPPageOverlay::DP_Search_by_TFS(long TFS){



}


de_struct* DPPageOverlay::DE_Search_by_TFS(long space_req){//will return NULL if not found

    //variables
    buffer_manager bm;
    long i;
    de_struct* de;
    //de = NULL;
    dp_page *dph;

        dph = (dp_page *)(dpPage->_data);
        
        de = (de_struct *)((dpPage->_data) + sizeof(dp_page));

        for(i = 0 ; i < maxDE ; i++)
        {
            //printf("\nde->page_TFS = %ld",de->page_TFS );
            
            if(de->page_TFS >= space_req){

            return de;
            }
        de++;

        }

    return NULL;

    }


de_struct* DPPageOverlay::DE_Add(){

    //go to last DP_Page of tablename
    buffer_manager bm;

    de_struct *de;

    dp_page *dph;

    dph = (dp_page *)(dpPage->_data);

    dph->DE_number = dph->DE_number + 1;

    //get last DP Page and get a free page for the new de
    //genpage *pg = bm.BufferRead(Current_Open_DB_Name, SYS_TABLE_PAGE);

    //SysTableOverlay systab(pg);

    //sys_table_entry *st;

    //st = systab.FindSystableEntrybyID(tid);
    
    //dpPage = bm.BufferWrite(Current_Open_DB_Name, st->last_DP_Page_Number);

    //temp_dpPage = bm.GetFreePage(Current_Open_DB_Name);

    //dpPage->_next_page = temp_dpPage->_page_number;

    //bm.ReleasePage(Current_Open_DB_Name,dpPage->_page_number);

    //dpPage = temp_dpPage;

   // CreateDPPage();

    de = (de_struct *)((dpPage->_data) + sizeof(dp_page));

        //update systable entry against tid and update last dp page

    //dph = (dp_page *)(dpPage->_data);

  

    dbPage = bm.GetFreePage(Current_Open_DB_Name);//get a fresh db page

    de->page_num = dbPage->_page_number;

      //Check for it later
    de->page_TFS = dbPage->_TFS;

    bm.ReleasePage(Current_Open_DB_Name, dbPage->_page_number); //release the db page

    //dph->max_TFS_withinTheDP = getMaxTFSwithinDE();

    // set the last DP Page Number
    //st->last_DP_Page_Number = dpPage->_page_number;

    //bm.ReleasePage(Current_Open_DB_Name, dpPage->_page_number);
   // bm.Commit(Current_Open_DB_Name, dpPage->_page_number);
//
//     if(systab.searchPage->_page_number != systab.systabPage->_page_number){
//        bm.ReleasePage(Current_Open_DB_Name,systab.searchPage->_page_number);
//        bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
//        }
//        else
//            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);

    return de;

}




int DPPageOverlay::DE_Delete(de_struct* de, mega_struct *mega){
    //int i;
    de_struct* last_used_DE;
    //GET last DP Page from systable
    //go to last DP_Page of tablename
    buffer_manager bm;

    systabPage = bm.BufferRead(Current_Open_DB_Name, SYS_TABLE_PAGE);

    SysTableOverlay systab(systabPage);

    sys_table_entry *st;

    st = systab.FindSysTableEntry(mega);
    
    dpPage = bm.BufferWrite(Current_Open_DB_Name,st->last_DP_Page_Number);

    DPPageOverlay lastDP(dpPage);

    dp_page *dph;

    dph = (dp_page *)(lastDP.dpPage->_data);

    last_used_DE =(de_struct *)( lastDP.dpPage->_data + sizeof(dp_page) );

    //for(i = 0 ;i< dph->DE_number ; i++){

    //}

    //set the variable to the last used DE
    last_used_DE += dph->DE_number;

    last_used_DE--;
    
    dph->DE_number--;

    memcpy(de, last_used_DE, sizeof(de_struct));
    
    //last_used_DE=lastDP.GetLastUsedDE();

    //de->page_num = last_used_DE->page_num;
    //de->page_TFS = last_used_DE->page_TFS;

    //free last used de

    //last_used_DE->page_num = -1;
    //last_used_DE->page_TFS = PG_DATASIZE;
    bm.ReleasePage(Current_Open_DB_Name,lastDP.dpPage->_page_number);
   // bm.Commit(Current_Open_DB_Name,lastDP.dpPage->_page_number);
    return SUCCESS;

    
}
void DPPageOverlay::PrintDPPage(){

}

void DPPageOverlay::ShowError(){
    if(dpPage == NULL){
        printf("\n error: dpPage not set !! stop !!\n");
    }

}
