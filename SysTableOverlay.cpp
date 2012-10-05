//SysTableOverlay.cpp
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "SysTableOverlay.h"
#include "DPPageOverlay.h"
//#include "DPPageOverlay.cpp"

SysTableOverlay::SysTableOverlay(genpage* pg){
    printf("\n inside the constructor");

    printf("priority  %ld",pg->_priority);

    systabPage = pg;

    if(pg->_priority != SYS_TABLE_PRIORITY){

            CreateSystablePage();
    }
}

SysTableOverlay::~SysTableOverlay() {
    systabPage = NULL;
}


void SysTableOverlay::CreateSystablePage(){

    printf("\n inside the createsystablepage");

    SysTableHeader *sth;

    sth =(SysTableHeader *)systabPage->_data;

    sys_table_entry *st;

    //systabPage = newSysTablePage;
    systabPage->_priority = SYS_TABLE_PRIORITY;

    systabPage->_next_page = -1;
    
    //sth = newSysTablePage->_data;
    sth->numberofTables = 0;

    sth->tableindex = 0;

    systabPage->_TFS = systabPage->_TFS - sizeof(SysTableHeader);
   
}


sys_table_entry* SysTableOverlay::AddSysTableEntry(mega_struct *mega, long DP_Page_Num){

    //Variables
    buffer_manager bm;
    genpage *masterpg;
    master_header *master_head;
    SysTableHeader *sth;
    long num_tables;

    //Check for Duplicates
    if( FindSysTableEntry(mega) != NULL){

        printf("\n---u r an ass...table already exists\n");

        return NULL;
    }
    printf("\ninside addsystable");

    masterpg = bm.BufferWrite(Current_Open_DB_Name, DB_HEADER_PAGE);

    master_head = (master_header *)(masterpg->_data);

    num_tables = master_head->num_tables;

    master_head->num_tables = master_head->num_tables + 1;

    printf("\nmhp--- %ld",master_head->last_systab_Page);

    //if first and last page are not same
    if(master_head->last_systab_Page != systabPage->_page_number){

        //release firstpage and get last page
        bm.ReleasePage(Current_Open_DB_Name,systabPage->_page_number);

        //bm.Commit(Current_Open_DB_Name,systabPage->_page_number);
        systabPage = bm.BufferWrite(Current_Open_DB_Name, master_head->last_systab_Page);

    }
    
    sth = (SysTableHeader *)systabPage->_data;

    //when last page is filled to the brim
    if(sth->numberofTables == maxnoOfentries){
        
            genpage *newPage = bm.GetFreePage(Current_Open_DB_Name);

            long pageNumber = newPage->_page_number;

            printf("\n pagenum = %ld",pageNumber);

            systabPage->_next_page = pageNumber;

            bm.ReleasePage(Current_Open_DB_Name,systabPage->_page_number);

            //bm.Commit(Current_Open_DB_Name,systabPage->_page_number);

            systabPage = newPage;

            CreateSystablePage();

            sth = (SysTableHeader *)systabPage->_data;
    }
    
    sys_table_entry *st;

    st = (sys_table_entry *)((systabPage->_data) + sizeof(SysTableHeader));

    st = st + (sth->numberofTables);
    //int count = 0;
    //while(st->is_deleted == 1 && count < maxnoOfentries){
        
    //    st++;
    //   count++;
    //}
    //printf("\nst->isdel %d",st->is_deleted);
    master_head->last_systab_Page =  systabPage->_page_number;

    printf("\n--->> %ld",systabPage->_page_number);

    printf("\nmhp--- %ld",master_head->last_systab_Page);

    //release MASTER DB HEADR
    bm.ReleasePage(Current_Open_DB_Name, DB_HEADER_PAGE);

    //bm.Commit(Current_Open_DB_Name, DB_HEADER_PAGE);

    //update PAGE TFS
    systabPage->_TFS = systabPage->_TFS - sizeof(sys_table_entry);

    //update table header
    sth->numberofTables = sth->numberofTables + 1;

    sth->tableindex = sth->tableindex + 1;

    //populate st
    strcpy(st->tablename, mega->Table);

    st->TID = num_tables;
    //st->first_DP_Page_Number = -1;
    //st->last_DP_Page_Number = -1;


    st->first_DP_Page_Number = DP_Page_Num;
    
    st->last_DP_Page_Number = DP_Page_Num;
    //assign a fresh DP Page
    /*
    genpage *newDPPage;
    newDPPage = bm.GetFreePage(Current_Open_DB_Name);
    DPPageOverlay DPnavigator(newDPPage);

    st->first_DP_Page_Number = DPnavigator.dpPage->_page_number;
    st->last_DP_Page_Number = DPnavigator.dpPage->_page_number;
//
    bm.ReleasePage(Current_Open_DB_Name,newDPPage->_page_number);
    bm.Commit(Current_Open_DB_Name,newDPPage->_page_number);
    */
    printf("sth--->> %ld\n",sth->numberofTables);
    
    //bm.ReleasePage(Current_Open_DB_Name, systabPage->_page_number);
    //bm.Commit(Current_Open_DB_Name, systabPage->_page_number);

    return st;
}


sys_table_entry* SysTableOverlay::FindSysTableEntry(mega_struct *mega){
    //genpage *pg;
    buffer_manager bm;

    sys_table_entry* ret;

    searchPage = systabPage;

    ret = RecursiveFind(mega);

    long searchpg = searchPage->_page_number;

    if(searchPage->_page_number != systabPage->_page_number){

        bm.ReleasePage(Current_Open_DB_Name,searchPage->_page_number);

        searchPage = bm.BufferWrite(Current_Open_DB_Name,searchpg);
    }

    return ret;
}


// Complementary private function of FindSysTableEntry for recursive search
sys_table_entry* SysTableOverlay::RecursiveFind(mega_struct *mega)
{
     buffer_manager bm;

        int i;
    //pg = systabPage;
    sys_table_entry* st;

    st = (sys_table_entry *)((searchPage->_data) + sizeof(SysTableHeader));

    for(i = 0; i< maxnoOfentries ;i++){

        if(!strcmp(st->tablename, mega->Table)){

            return st;
        }
        else st++;
    }
    if(searchPage->_next_page!= -1){

        bm.ReleasePage(Current_Open_DB_Name,searchPage->_page_number);

        searchPage = bm.BufferRead(Current_Open_DB_Name, searchPage->_next_page);

        st = RecursiveFind(mega);
        
        return st;
    }
    else
       // bm.ReleasePage(Current_Open_DB_Name,systabPage->_page_number);
        return NULL;

}



sys_table_entry* SysTableOverlay::FindSystableEntrybyID(long tid){

    buffer_manager bm;

    sys_table_entry* ret;

    searchPage = systabPage;

    ret = RecursiveFindbyID(tid);

    long searchpg;

    searchpg = searchPage->_page_number;

      if(searchPage->_page_number != systabPage->_page_number){

            bm.ReleasePage(Current_Open_DB_Name,searchPage->_page_number);

            searchPage = bm.BufferWrite(Current_Open_DB_Name,searchpg);
      }

    return ret;
}

sys_table_entry* SysTableOverlay::RecursiveFindbyID(long tid)
{
     buffer_manager bm;

     int i;
    //pg = systabPage;
    sys_table_entry* st;

    st = (sys_table_entry *)((searchPage->_data) + sizeof(SysTableHeader));

    for(i = 0; i< maxnoOfentries ;i++){

        if((st->TID == tid)){

            return st;
        }

        else st++;
    }
    if(searchPage->_next_page!= -1){

        bm.ReleasePage(Current_Open_DB_Name,searchPage->_page_number);

        searchPage = bm.BufferRead(Current_Open_DB_Name, searchPage->_next_page);

        st = RecursiveFindbyID(tid);

        return st;
    }
    else
       // bm.ReleasePage(Current_Open_DB_Name,systabPage->_page_number);
        return NULL;

}

long SysTableOverlay::DeleteSysTableEntry(mega_struct *mega){

    buffer_manager bm;

    SysTableHeader *sth;

    sys_table_entry *st, *st1;

    st = FindSysTableEntry(mega);

    //RELEASE the read mode and get the WRITE mode
    long pageNumber = searchPage->_page_number;

    bm.ReleasePage(Current_Open_DB_Name,searchPage->_page_number);

    deletePage = bm.BufferWrite(Current_Open_DB_Name,pageNumber);

    //get master dbheader to get the last systable page
    genpage *masterpg;

    masterpg = bm.BufferWrite(Current_Open_DB_Name, DB_HEADER_PAGE);

    master_header *master_head;

    master_head = (master_header *)(masterpg->_data);

    //genpage *lastsystabPage;

    if(master_head->last_systab_Page != pageNumber){

        lastsystabPage = bm.BufferWrite(Current_Open_DB_Name, master_head->last_systab_Page);

    //SysTableOverlay sysTableNavigator(lastsystabPage);

    st1 = (sys_table_entry *)((lastsystabPage->_data) + sizeof(SysTableHeader));

    sth = (SysTableHeader *)lastsystabPage->_data;

    st1 = st1 + (sth->numberofTables);

    sth->numberofTables--;
    
    st1--;//last filled entry

    memcpy(st,st1, sizeof(sys_table_entry));

    bm.ReleasePage(Current_Open_DB_Name,lastsystabPage->_page_number);
    //bm.Commit(Current_Open_DB_Name,lastsystabPage->_page_number);

    }
    else{

        st1 = (sys_table_entry *)((deletePage->_data) + sizeof(SysTableHeader));

        sth = (SysTableHeader *)deletePage->_data;
    
    st1 = st1 + (sth->numberofTables);
    
    sth->numberofTables--;
    //while(st1->is_deleted){
    //    st1++;
    //}

    st1--;//last filled entry

    memcpy(st,st1, sizeof(sys_table_entry));

    //st1->is_deleted = 0;
    }

    bm.ReleasePage(Current_Open_DB_Name,pageNumber);

    //bm.Commit(Current_Open_DB_Name,pageNumber);

    bm.ReleasePage(Current_Open_DB_Name,masterpg->_page_number);
    
    //bm.Commit(Current_Open_DB_Name,masterpg->_page_number);
    
    //st1 =sysTableNavigator.systabPage
    //systabPage = bm.BufferWrite(Current_Open_DB_Name, master_header->last_systab_Page);


}

void SysTableOverlay::PrintSysTable(){

    buffer_manager bm;

    int i;

    SysTableHeader *sth;

    sys_table_entry *st;

    printf("\ncurrentdb :%s",Current_Open_DB_Name);

    //printf("\nnoof entry %ld",maxnoOfentries);

    //printf("\nsystablepagenumber %ld",systabPage->_page_number);

    while(1){

        sth =(SysTableHeader *)systabPage->_data;

        //printf("\n=====================================");

        //printf("\nno of tables = %ld",sth->numberofTables);

        //printf("\ntableindex = %ld",sth->tableindex);

        st = (sys_table_entry *)((systabPage->_data) + sizeof(SysTableHeader));

        
            for(i = 0;i< sth->numberofTables; i++){
            
                printf("\n");

                printf("\tSystablePAGEnum : %4ld",systabPage->_page_number);

                printf("\tTable name      : %10s",st->tablename);

                printf("\tTableID         : %4ld", st->TID);

//                printf("\tfirstDP         : %4ld", st->first_DP_Page_Number);
//
//                printf("\tlastDP          : %4ld", st->last_DP_Page_Number);
//
//                printf("\tsyscol_pgnum          : %4ld", st->col_rid.pageno);
//
//                printf("\tsyscol_slotnum          : %4ld", st->col_rid.slotno);

            
            st++;

            }

        if(systabPage->_next_page != -1){

            long pagenumber = systabPage->_next_page;

            bm.ReleasePage(Current_Open_DB_Name, systabPage->_page_number);

            systabPage = bm.BufferRead(Current_Open_DB_Name, pagenumber);
        }
        
        else
            break;

    }
}
