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
#include "SysTableOverlay.h"
#include "SysColumnOverlay.h"
#include "DPPageOverlay.h"
#include "Utils.h"
#include "MegaStruct.h"

extern bool select_flag;

//extern buffer_manager buffer1;



//buffer_manager buffer1;
/*
int Database::Create_DP_Page(){
    
}
*/
char Current_Open_DB_Name[50];
//long Database::current_table_id = 0;
Database::Database(){

    cout << "\nDefault Constructor initiated for database" << endl;
    masterDBHeader = NULL;
    sysColDP = NULL;
    sysTabPage = NULL;
    sysCol_dbPage = NULL;
    sysIndexPage = NULL;
    DPPage = NULL;
}

Database::~Database(){
    
}

int Database::Create_DB(char *_db_Name,long _db_pages,long _page_size){

    long tid;

    buffer_manager bm;

    master_header *db;

    mega_struct *mega;

    int SuccessDB;

    //Calling Buffer's CreateDB
    SuccessDB = bm.CreateDB (_db_Name, _db_pages, _page_size);
    printf("\nsuccessDB = %d\n",SuccessDB);
    
    if(!SuccessDB)
    {
         /*request DBHEADERPAGE*/
        masterDBHeader = bm.BufferWrite(_db_Name,DB_HEADER_PAGE);

        masterDBHeader->_priority = DB_HEADER_PRIORITY;

        masterDBHeader->_TFS = PG_DATASIZE - sizeof(master_header);

        db = (master_header *)(masterDBHeader->_data);//buffer is using first 4 bytes

        strcpy(db->dbName, _db_Name);
        
        db->last_systab_Page = SYS_TABLE_PAGE;

        db->last_syscol_Page=SYS_COLUMN_DP_PAGE;

        db->last_sysindex_Page = SYS_INDEX_PAGE;

        db->num_tables = 1;
      
        bm.ReleasePage(_db_Name, DB_HEADER_PAGE);

        masterDBHeader = NULL;
	//bm.Commit(_db_Name, DB_HEADER_PAGE);

        /*request next page for SYS_TABLE*/
        sysTabPage = bm.BufferWrite(_db_Name, SYS_TABLE_PAGE);

        SysTableOverlay *sysTableNavigator = new SysTableOverlay(sysTabPage);

        bm.ReleasePage(_db_Name, SYS_TABLE_PAGE);

        //bm.Commit(_db_Name, SYS_TABLE_PAGE);
        sysTabPage = NULL;

        //copying dbname in the opendb variable
        strcpy(Current_Open_DB_Name,_db_Name);

        //set the first syscolumn DP
        sysColDP = bm.BufferWrite(_db_Name,SYS_COLUMN_DP_PAGE);

        DPPageOverlay *sysColDPNavigator = new DPPageOverlay(sysColDP);

        mega = (mega_struct *)malloc(sizeof(mega_struct));

        strcpy(mega->Table,"sysColumn");

        sys_table_entry *st;
        st = sysTableNavigator->AddSysTableEntry(mega, sysColDP->_page_number);

        tid = st->TID;

        bm.ReleasePage(_db_Name, SYS_COLUMN_DP_PAGE);

       // bm.Commit(_db_Name, SYS_COLUMN_PAGE);
        sysColDP = NULL;
        
	printf("\nCreate DB is almost complete\n");

        //request next page for SYS_INDEX


//        pg = bm.BufferWrite(_db_Name,SYS_INDEX_PAGE);
//        pg->_priority = SYS_INDEX_PRIORITY;
//        bm.ReleasePage(_db_Name,SYS_INDEX_PAGE);
//	 bm.Commit(_db_Name, SYS_INDEX_PAGE);

        return 0;


    }
    else
    {
	printf("\n u r unlucky...some error occured");
        return 1;
    }
}

/* printing functions */

int Database::ShowDBPage(){
}
int Database::ShowHeaderPage(){
}


int Database::ShowSysTable(){
    
    buffer_manager bm;
    
    genpage *pg_sys = bm.BufferRead(Current_Open_DB_Name,SYS_TABLE_PAGE);
        
    SysTableOverlay *systab = new SysTableOverlay(pg_sys);

    printf("\nhello1");

    systab->PrintSysTable();

    bm.ReleasePage(Current_Open_DB_Name, systab->systabPage->_page_number);
       // bm.Commit(Current_Open_DB_Name, systab->systabPage->_page_number);
}


int Database::ShowSysColumn(){
}
int Database::ShowSysIndex(){
}
int Database::ShowDPPage(){
}

int Database::ShowDatabases(){

}


long Database::Use_DB(char *_db_Name){
    buffer_manager bm;

    int i = bm.OpenDB(_db_Name);
    if(i != ERROR)
    {
        strcpy(Current_Open_DB_Name, _db_Name);
    }
    return i;
}




int Database::Create_Table( mega_struct *mega){

    char *is_null = "\0";

    long tid;

    sys_table_entry *sys_col_st, *table_st;

    de_struct *de;

    dp_page *dph;

    buffer_manager bm;

    if(!strcmp(Current_Open_DB_Name, is_null))
     {
        printf("\nNo Database is currently in use\n");

        return ERROR;
     }

     else
     {
     
        genpage *pg_sys = bm.BufferWrite(Current_Open_DB_Name,SYS_TABLE_PAGE);
        
        SysTableOverlay systab(pg_sys);

        sys_col_st = systab.FindSystableEntrybyID(1);//search page is again opened in write mode in the function

        //sysColDP = bm.BufferRead(Current_Open_DB_Name,sys_col_st->first_DP_Page_Number);

        long sys_col_tableDP = sys_col_st->first_DP_Page_Number;

        //two pages are open searchPage and systabPage
        table_st = systab.AddSysTableEntry(mega, -1);

        //now systabPage is open or lastsystabPage is open
       
        //Entry into sysColumns
        //Page# 3 is SYSCOL DP PAGE

        //Add DE to SysColDP
        long rec_length = 0;

        rec_length += DBOverlay::getSlotIndexSize();

        rec_length = SysColumnOverlay::computeSize(mega);

        // traverse to appropriate syscolDP Page

          while(1){

                sysColDP = bm.BufferRead(Current_Open_DB_Name, sys_col_tableDP);

                dp_page *dpheader = (dp_page *)(sysColDP->_data) ;

                if(dpheader->max_TFS_withinTheDP >= rec_length || sysColDP->_next_page == -1){

                    long tempPagenum = sysColDP->_page_number;

                    bm.ReleasePage(Current_Open_DB_Name, tempPagenum);

                    sysColDP = bm.BufferWrite(Current_Open_DB_Name, tempPagenum);//opening the DPPage in write mode

                    break;
                }
                else{

                    sys_col_tableDP = sysColDP->_next_page;

                }


            }


         DPPageOverlay DPNavigator(sysColDP);

        de = DPNavigator.DE_Search_by_TFS(rec_length);

        if(de == NULL){

            tempDPPage = bm.GetFreePage(Current_Open_DB_Name);//open a fresh DP Page in write mode
            DPNavigator.dpPage->_next_page = tempDPPage->_page_number;

            bm.ReleasePage(Current_Open_DB_Name, DPNavigator.dpPage->_page_number);//release the penultimate DP Page

            DPNavigator.dpPage = tempDPPage;
            DPNavigator.CreateDPPage();

            //PLEASE CHECK ONCE
            DPNavigator.DE_Add();

            sys_col_st->last_DP_Page_Number = tempDPPage->_page_number;
        }

        else if(de->page_num == -1){

            DPNavigator.dbPage = bm.GetFreePage(Current_Open_DB_Name);

            //de->page_TFS = de->page_TFS - rec_length;//update TFS
            
            de->page_num = DPNavigator.dbPage->_page_number;
            //de->page_TFS = de->page_TFS - rec_length;//update TFS
        }

        else{

            //de->page_TFS = de->page_TFS - rec_length;//update TFS

            DPNavigator.dbPage = bm.BufferWrite(Current_Open_DB_Name,de->page_num);

        }

        SysColumnOverlay sysCol(DPNavigator.dbPage, SYS_COLUMN_PRIORITY);
        
        RID rid;

        rid = sysCol.AddSysColumnEntry(mega, table_st->TID , rec_length);
        
        //adding the column rid to sysindex to ease access

        table_st->col_rid = rid;

        long max_tfs_entry;

        dph = (dp_page *)DPNavigator.dpPage->_data;

        max_tfs_entry = dph->max_TFS_withinTheDP;
        
        if(de->page_TFS == max_tfs_entry){
            
             de->page_TFS = DPNavigator.dbPage->_TFS;

             long max_tfs = DPNavigator.getMaxTFSwithinDE();
            
             DPNavigator.setMaxTFSwithinDE(max_tfs);
        }

        else{

            de->page_TFS = DPNavigator.dbPage->_TFS;
        }
        
        if (sysCol.FindTable(table_st->TID) == true){

            sysCol.PrintSysColumn();
        }

        printf("\n in db's create  1\n");
        UI::PrintColumns(mega);

        bm.ReleasePage(Current_Open_DB_Name, DPNavigator.dpPage->_page_number);//release the syscolumn dpPage

        bm.ReleasePage(Current_Open_DB_Name, DPNavigator.dbPage->_page_number);
        
       // bm.ReleasePage(Current_Open_DB_Name,sys_col_st->last_DP_Page_Number);

         //release and Commit systable pages
        if(systab.searchPage->_page_number != systab.systabPage->_page_number){

            bm.ReleasePage(Current_Open_DB_Name,systab.searchPage->_page_number);

            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
        }
        else
            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);

       
     }
    return SUCCESS;
     }

int Database::Insert_Table(mega_struct* mega){

//    mega_struct *mega;
    char *is_null = "\0";
    
    buffer_manager bm;

    sys_table_entry *st;

    long tid;

    de_struct *de;

    bool dp_exhaust = false;

    int i;

    int dataType;

    char *data;
    
    dp_page *dph;

    //get TID
    //get Syscolumn
    //Check Schema
    //get To the DP Page


    if(!strcmp(Current_Open_DB_Name, is_null)){
                
        printf("\nNo Database is currently in use\n");
        
        return ERROR;

     }

    else{

        char table_name[NAME_LENGTH];

        strcpy(table_name, mega->Table);

        //go to systable
        //search for table name
        sysTabPage = bm.BufferWrite(Current_Open_DB_Name,SYS_TABLE_PAGE);

        SysTableOverlay systab(sysTabPage);//systab.systabPage open in write mode

        st = systab.FindSysTableEntry(mega);//systab.searchpage open in write mode....both may be same

        tid = st->TID;

        RID rid;

        rid = st->col_rid;

        sysCol_dbPage = bm.BufferRead(Current_Open_DB_Name,rid.pageno);//directly open the syscolumn's dbpage containing col_info

        SysColumnOverlay syscol(sysCol_dbPage,SYS_COLUMN_PRIORITY);

        syscol.gotoSlot(rid.slotno);

        syscol.updateDataPtr();

        syscol.FillAttributeNames(mega);

        syscol.FillmegaStruct(mega);

        MegaStruct::Allocate(mega);

        for(i = 0; i< mega->NumPattr; i++){

            //memset(mega->Pattr[i]->value,NULL,mega->Pattr[i]->length);

            printf("Enter column value for Column Name: %s \n", mega->Pattr[i]->attr_name);

            dataType =  mega->Pattr[i]->type;

            data = (char*)mega->Pattr[i]->value;
       
            switch (dataType)
            {
                case INT:
                    scanf("%d", (int *)data);
                    break;
                case FLOAT:
                    scanf("%f", (float *)data);
                    break;
                case CHAR:
                    scanf("%s", (char *)data);
                    break;
                case VARCHAR:
                    scanf("%s", (char *)data);
                    break;
            }
        //mega->Pattr[i].value = data;
        }

        //record length problem

        long rec_length = 0;

        rec_length = rec_length + DBOverlay::getSlotIndexSize();

        rec_length = rec_length + DBOverlay::computeSize(mega);

        //find appropriate DP Page and DE and get the DBPage
        long tableDP = st->first_DP_Page_Number;

        if(tableDP == -1){
            //allocate a new DPPage

            DPPage = bm.GetFreePage(Current_Open_DB_Name);//DPPage open in write mode

            //DPPageOverlay dpNavigator(DPPage);

            st->first_DP_Page_Number = DPPage->_page_number;

            st->last_DP_Page_Number = DPPage->_page_number;

            //tableDP = dpNavigator.dpPage->_page_number;
        }

        else{
            //traverse to the appropriate DP Page
            while(1){

                DPPage = bm.BufferRead(Current_Open_DB_Name, tableDP);
        
                dp_page *dpheader = (dp_page *)(DPPage->_data) ;

                if(dpheader->max_TFS_withinTheDP >= rec_length || DPPage->_next_page == -1){

                    long tempPagenum = DPPage->_page_number;

                    bm.ReleasePage(Current_Open_DB_Name, tempPagenum);

                    DPPage = bm.BufferWrite(Current_Open_DB_Name, tempPagenum);//opening the DPPage in write mode

                    break;
                }
                else{

                    tableDP = DPPage->_next_page;

                }


            }

        }
            DPPageOverlay dpNavigator(DPPage);

            de = dpNavigator.DE_Search_by_TFS(rec_length);

        if(de == NULL){

            tempDPPage = bm.GetFreePage(Current_Open_DB_Name);//open a fresh DP Page in write mode
            dpNavigator.dpPage->_next_page = tempDPPage->_page_number;

            bm.ReleasePage(Current_Open_DB_Name, dpNavigator.dpPage->_page_number);//release the penultimate DP Page

            dpNavigator.dpPage = tempDPPage;
            dpNavigator.CreateDPPage();

            de = dpNavigator.DE_Add();
            st->last_DP_Page_Number = dpNavigator.dpPage->_page_number;

            DBPage = bm.BufferWrite(Current_Open_DB_Name,de->page_num);//open the DB Page in write mode for insertion^^^
           // bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);
        }

        if(de->page_num == -1){

            //allocate a db page to de
            DBPage = bm.GetFreePage(Current_Open_DB_Name);//^^^
            de->page_num = DBPage->_page_number;
           // bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);

        }
        else{

        DBPage = bm.BufferWrite(Current_Open_DB_Name, de->page_num);//^^^
       // bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);

        }


        DBOverlay dbNavigator(DBPage, DB_PAGE_PRIORITY);

        dbNavigator.insert_slot(mega,rec_length);



        // resetting maxTFS in DP header if needed and setting the de->TFS

        long max_tfs_entry;

        dph = (dp_page *)dpNavigator.dpPage->_data;

        max_tfs_entry = dph->max_TFS_withinTheDP;

         if(de->page_TFS == max_tfs_entry){

             de->page_TFS = dbNavigator.dbpage->_TFS;

             long max_tfs = dpNavigator.getMaxTFSwithinDE();

             dpNavigator.setMaxTFSwithinDE(max_tfs);

         }
         else{

            de->page_TFS = dbNavigator.dbpage->_TFS;
         }

        //release syscol dbpage
        bm.ReleasePage(Current_Open_DB_Name,sysCol_dbPage->_page_number);
        //release DP Page
        bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);
        //release DB Page
        bm.ReleasePage(Current_Open_DB_Name,dbNavigator.dbpage->_page_number);
        //release Systable Pages
        if(systab.searchPage->_page_number != systab.systabPage->_page_number){

            bm.ReleasePage(Current_Open_DB_Name,systab.searchPage->_page_number);

            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
        }
        else
            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);

         return 0;

    }


}

int Database::Bulk_Insert_Table(mega_struct* mega){



    //    mega_struct *mega;
    char *is_null = "\0";

    buffer_manager bm;

    sys_table_entry *st;

    long tid;

    de_struct *de;

    bool dp_exhaust = false;

    int i;

    int dataType;

    char *data;

    dp_page *dph;

    //get TID
    //get Syscolumn
    //Check Schema
    //get To the DP Page


    if(!strcmp(Current_Open_DB_Name, is_null)){

        printf("\nNo Database is currently in use\n");

        return ERROR;

     }

    else{

        char table_name[NAME_LENGTH];

        strcpy(table_name, mega->Table);

        //go to systable
        //search for table name
        sysTabPage = bm.BufferWrite(Current_Open_DB_Name,SYS_TABLE_PAGE);

        SysTableOverlay systab(sysTabPage);//systab.systabPage open in write mode

        st = systab.FindSysTableEntry(mega);//systab.searchpage open in write mode....both may be same

        tid = st->TID;

        RID rid;

        rid = st->col_rid;

        sysCol_dbPage = bm.BufferRead(Current_Open_DB_Name,rid.pageno);//directly open the syscolumn's dbpage containing col_info

        SysColumnOverlay syscol(sysCol_dbPage,SYS_COLUMN_PRIORITY);

        syscol.gotoSlot(rid.slotno);

        syscol.updateDataPtr();

        syscol.FillAttributeNames(mega);

        syscol.FillmegaStruct(mega);

        MegaStruct::Allocate(mega);


                
                //insert multiple values

        unsigned long no_of_rows;

        char *str, *str1;

        long pagenum = 0;

        printf("\nhello....now enter no. of values to be inserted\n");
        
        scanf("%ld",&no_of_rows);

        for(unsigned long j = 0; j < no_of_rows; j++){
            

            printf("\n\ninserting row no. %ld\n\n",j);

            if(j == 54657){
                printf("\n\nyou re beautiful\n",j);
            }

            str = (char *)malloc(NAME_LENGTH * sizeof(char));

            str1 = (char *)malloc(NAME_LENGTH * sizeof(char));

            Utils::itoa(j,str1,10);

            strcpy(str,"Anmol");

            strcat(str,str1);

            int num_val = 110;

            float float_val = 110.0;

            

            for(i = 0; i< mega->NumPattr; i++){

                dataType =  mega->Pattr[i]->type;

                data = (char*)mega->Pattr[i]->value;
               
                switch (dataType)
                {
                    case INT:
                        //scanf("%d", (int *)data);
                        memcpy((int *)data, &num_val, sizeof(int));
                        break;
                    case FLOAT:
                        //scanf("%f", (float *)data);
                        memcpy((float *)data, &float_val, sizeof(float));
                        break;
                    case CHAR:
                        //scanf("%s", (char *)data);
                        strcpy((char *)data, str);
                        break;
                    case VARCHAR:
                        //scanf("%s", (char *)data);
                        strcpy((char *)data, str);
                        break;
                }
        
            }

            //record length problem

            long rec_length = 0;

            rec_length = rec_length + DBOverlay::getSlotIndexSize();

            rec_length = rec_length + DBOverlay::computeSize(mega);

            //find appropriate DP Page and DE and get the DBPage
            long tableDP = st->first_DP_Page_Number;

            if(tableDP == -1){
            //allocate a new DPPage

                DPPage = bm.GetFreePage(Current_Open_DB_Name);//DPPage open in write mode

                //DPPageOverlay dpNavigator(DPPage);

                st->first_DP_Page_Number = DPPage->_page_number;

                st->last_DP_Page_Number = DPPage->_page_number;

                //tableDP = dpNavigator.dpPage->_page_number;
            }

            else{
                //traverse to the appropriate DP Page
                while(1){

                    DPPage = bm.BufferRead(Current_Open_DB_Name, tableDP);
        
                    dp_page *dpheader = (dp_page *)(DPPage->_data) ;

                   // printf("\nmax_space in a DE in DP = %ld\n",dpheader->max_TFS_withinTheDP);

                    if(dpheader->max_TFS_withinTheDP >= rec_length || DPPage->_next_page == -1){

                        if(dpheader->max_TFS_withinTheDP < rec_length){
                            printf("\nDPPage exhausted\n");
                        }

                        long tempPagenum = DPPage->_page_number;

                        bm.ReleasePage(Current_Open_DB_Name, tempPagenum);

                        DPPage = bm.BufferWrite(Current_Open_DB_Name, tempPagenum);//opening the DPPage in write mode

                        break;
                    }
                
                    else{

                    tableDP = DPPage->_next_page;

                    }


                }

            }
            DPPageOverlay dpNavigator(DPPage);

            de = dpNavigator.DE_Search_by_TFS(rec_length);

            if(de == NULL){

                tempDPPage = bm.GetFreePage(Current_Open_DB_Name);//open a fresh DP Page in write mode
                dpNavigator.dpPage->_next_page = tempDPPage->_page_number;

                bm.ReleasePage(Current_Open_DB_Name, dpNavigator.dpPage->_page_number);//release the penultimate DP Page

                dpNavigator.dpPage = tempDPPage;
                dpNavigator.CreateDPPage();

                

                de = dpNavigator.DE_Add();
                st->last_DP_Page_Number = dpNavigator.dpPage->_page_number;

                DBPage = bm.BufferWrite(Current_Open_DB_Name,de->page_num);//open the DB Page in write mode for insertion^^^
                // bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);
            }

            if(de->page_num == -1){

                //allocate a db page to de
                DBPage = bm.GetFreePage(Current_Open_DB_Name);//^^^

                de->page_num = DBPage->_page_number;


                printf("\nde->page_num = %ld",de->page_num);
                //bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);

            }
            else{

                DBPage = bm.BufferWrite(Current_Open_DB_Name, de->page_num);//^^^
                //bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);
                printf("\nde->page_num = %ld",de->page_num);
            }


            DBOverlay dbNavigator(DBPage, DB_PAGE_PRIORITY);

            dbNavigator.insert_slot(mega,rec_length);

            MegaStruct::Clean(mega);


            // resetting maxTFS in DP header if needed and setting the de->TFS

            long max_tfs_entry;

            dph = (dp_page *)dpNavigator.dpPage->_data;

            max_tfs_entry = dph->max_TFS_withinTheDP;

            if(de->page_TFS == max_tfs_entry){

                de->page_TFS = dbNavigator.dbpage->_TFS;

                long max_tfs = dpNavigator.getMaxTFSwithinDE();



                dpNavigator.setMaxTFSwithinDE(max_tfs);

            }
            else{

            de->page_TFS = dbNavigator.dbpage->_TFS;
            }

            
            //release DP Page
            bm.ReleasePage(Current_Open_DB_Name,dpNavigator.dpPage->_page_number);
            //release DB Page
            bm.ReleasePage(Current_Open_DB_Name,dbNavigator.dbpage->_page_number);
            //release Systable Pages
      
        }
        
        //release syscol dbpage
        bm.ReleasePage(Current_Open_DB_Name,sysCol_dbPage->_page_number);

        if(systab.searchPage->_page_number != systab.systabPage->_page_number){

                bm.ReleasePage(Current_Open_DB_Name,systab.searchPage->_page_number);

                bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
            }
            else
                bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);

        return 0;

    }
}

int Database::Select_Table(mega_struct *mega){

    char *is_null = "\0";
   // mega_struct *mega;
     // genpage *stPg, *scDP, *tabDP, *dbPg;

    buffer_manager bm;

    sys_table_entry *st;

    long tid;

    de_struct *de;
   
    bool found = false, exit = false;

    //get table id from systable
    //fill schema from syscolumn

    if(!strcmp(Current_Open_DB_Name, is_null)){

        printf("\nNo Database is currently in use\n");

        return ERROR;

     }
    else{

        char table_name[NAME_LENGTH];

        strcpy(table_name, mega->Table);

        //go to systable
        //search for table name
        sysTabPage = bm.BufferRead(Current_Open_DB_Name,SYS_TABLE_PAGE);

        SysTableOverlay systab(sysTabPage);//systab.syatabPage is open in read mode

        st = systab.FindSysTableEntry(mega);//systab.searchpage is open in write mode

        tid = st->TID;

        RID rid;

        rid = st->col_rid;

        sysCol_dbPage = bm.BufferRead(Current_Open_DB_Name,rid.pageno);//directly open the syscolumn's dbpage containing col_info

        SysColumnOverlay syscol(sysCol_dbPage,SYS_COLUMN_PRIORITY);

        syscol.gotoSlot(rid.slotno);

        syscol.updateDataPtr();

        if(select_flag == true){
            cout << "\nSelect all" << endl;
            syscol.FillAttributeNames(mega);
        }

        syscol.FillmegaStruct(mega);

        MegaStruct::Allocate(mega);

        UI::PrintColumns(mega);

        bool flag = false;

        DPPage = bm.BufferRead(Current_Open_DB_Name,st->first_DP_Page_Number);//open table's first DP Page in read mode

        while(1)
        {
                DPPageOverlay TableDP(DPPage);

                de = (de_struct *)(TableDP.dpPage->_data + sizeof(dp_page));

                for(int i = 0 ; i < maxDE ; i++){

                    if(de->page_num == -1){
                        flag = true;
                        break;
                    }


                    
                    DBPage = bm.BufferRead(Current_Open_DB_Name, de->page_num);
                    DBOverlay DBNav(DBPage, DB_PAGE_PRIORITY);
                    DBNav.select_all(mega);
                    bm.ReleasePage(Current_Open_DB_Name,DBPage->_page_number);
                    MegaStruct::Clean(mega);
                    //break;
                    de++;

                }
                if(flag == true){
                break;
                }
                long next_dp = DPPage->_next_page;
                if ( next_dp != -1)
                {
                    bm.ReleasePage(Current_Open_DB_Name, DPPage->_page_number);
                    DPPage = bm.BufferRead(Current_Open_DB_Name, next_dp);
                }
                else
                    break;



        }

        //release DPPage
        bm.ReleasePage(Current_Open_DB_Name, DPPage->_page_number);

        bm.ReleasePage(Current_Open_DB_Name, sysCol_dbPage->_page_number);

        //release Systable Pages
        if(systab.searchPage->_page_number != systab.systabPage->_page_number){

            bm.ReleasePage(Current_Open_DB_Name,systab.searchPage->_page_number);

            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
        }
        else
            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);


        return 0;
    }
    
    
    
}

int Database::Filter_select_Table(mega_struct* mega){

       char *is_null = "\0";
   // mega_struct *mega;
     // genpage *stPg, *scDP, *tabDP, *dbPg;

    buffer_manager bm;

    sys_table_entry *st;

    long tid;

    de_struct *de;

    int i;

    int dataType;

    char *data;

    dp_page *dph;

    bool found = false, exit = false;

    //get table id from systable
    //fill schema from syscolumn

    if(!strcmp(Current_Open_DB_Name, is_null)){

        printf("\nNo Database is currently in use\n");

        return ERROR;

     }

    else{

        char table_name[NAME_LENGTH];

        strcpy(table_name, mega->Table);

        //go to systable
        //search for table name
        sysTabPage = bm.BufferRead(Current_Open_DB_Name,SYS_TABLE_PAGE);

        SysTableOverlay systab(sysTabPage);

        st = systab.FindSysTableEntry(mega);

        tid = st->TID;

        RID rid;

        rid = st->col_rid;

        sysCol_dbPage = bm.BufferRead(Current_Open_DB_Name,rid.pageno);

        SysColumnOverlay syscol(sysCol_dbPage,SYS_COLUMN_PRIORITY);

        syscol.gotoSlot(rid.slotno);

        syscol.updateDataPtr();

        syscol.FillmegaStruct(mega);

        UI::PrintColumns(mega);
//        cout << "TID for table: " << table_name << " is: " << tid << endl;
//        sysColDP = bm.BufferRead(Current_Open_DB_Name, SYS_COLUMN_DP_PAGE);
//
//        de = NULL;
//
//        while(1){
//
//            DPPageOverlay DPNavigator(sysColDP);
//
//            de = (de_struct *)(DPNavigator.dpPage->_data + sizeof(dp_page));
//
//            for(int i = 0; i< maxDE ; i++){
//
//                if(de->page_num == -1)
//                {
//                    goto exit_while;
//                }
//                else
//                {
//                    sysCol_dbPage = bm.BufferRead(Current_Open_DB_Name,de->page_num);
//
//                    SysColumnOverlay syscol(sysCol_dbPage, SYS_COLUMN_PRIORITY);
//                    found = syscol.FindTable(tid);
//                    if(found)
//                    {
//                        syscol.SelectiveFillmegaStruct(mega);
//                        //Print Schema and ask for the filter condition
//
//                        UI::PrintColumns(mega);
//                        goto exit_while;
//                    }
//
//                    bm.ReleasePage(Current_Open_DB_Name, sysCol_dbPage->_page_number);
//                }
//
//                de++;
//            }
//            long next_page_number = DPNavigator.dpPage->_next_page;
//
//            bm.ReleasePage(Current_Open_DB_Name, DPNavigator.dpPage->_page_number);
//
//            if(next_page_number == -1){
//                printf("\n syscolumn is empty God Damn it ");
//                return 1;
//            }
//
//            sysColDP = bm.BufferRead(Current_Open_DB_Name,next_page_number);
//
//            //DPNavigator(DPPage);
//
//        }
//
//        exit_while:

                bool flag = false;
//           if (found == false)
//               return 1;

            DPPage = bm.BufferRead(Current_Open_DB_Name,st->first_DP_Page_Number);

            do
            {
                DPPageOverlay TableDP(DPPage);

                de = (de_struct *)(TableDP.dpPage->_data + sizeof(dp_page));

                for(int i = 0 ; i < maxDE ; i++){

                    if(de->page_num == -1){
                        flag = true;
                        break;
                    }


                    DBPage = bm.BufferRead(Current_Open_DB_Name, de->page_num);
                    DBOverlay DBNav(DBPage, DB_PAGE_PRIORITY);
                    DBNav.select_all(mega);
                    de++;
                 }
                if(flag == true){
                break;
                }
                long next_dp = DPPage->_next_page;
                if ( next_dp != -1)
                {
                    bm.ReleasePage(Current_Open_DB_Name, DPPage->_page_number);
                    DPPage = bm.BufferRead(Current_Open_DB_Name, next_dp);
                }

            }while (DPPage->_next_page != -1);

            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
            bm.ReleasePage(Current_Open_DB_Name, systab.searchPage->_page_number);

            return 0;
    }


    
}
int Database::Describe_Table(mega_struct* mega){

         char *is_null = "\0";

         buffer_manager bm;

        sys_table_entry *st;

        long tid;

        //get table id from systable
        //fill schema from syscolumn

        if(!strcmp(Current_Open_DB_Name, is_null)){

            printf("\nNo Database is currently in use\n");

            return ERROR;

        }

        else{

            char table_name[NAME_LENGTH];

            strcpy(table_name, mega->Table);

            //go to systable
            //search for table name
            sysTabPage = bm.BufferRead(Current_Open_DB_Name,SYS_TABLE_PAGE);

            SysTableOverlay systab(sysTabPage);//systab.systabPage is open in read mode

            st = systab.FindSysTableEntry(mega);//or systab.searchPage is open in read mode

            tid = st->TID;

            RID rid;

            rid = st->col_rid;

            sysCol_dbPage = bm.BufferRead(Current_Open_DB_Name,rid.pageno);//syscol DB page is open in read mode

            SysColumnOverlay syscol(sysCol_dbPage,SYS_COLUMN_PRIORITY);

            syscol.gotoSlot(rid.slotno);

            syscol.updateDataPtr();

            syscol.PrintSysColumn();

//            syscol.FillAttributeNames(mega);
//
//            syscol.FillmegaStruct(mega);
//
//            UI::PrintSchema(mega);
            //UI::PrintColumns(mega);

            //release pages: syscol DB page
        bm.ReleasePage(Current_Open_DB_Name, sysCol_dbPage->_page_number);
        //release systabPages
        if(systab.searchPage->_page_number != systab.systabPage->_page_number){

            bm.ReleasePage(Current_Open_DB_Name,systab.searchPage->_page_number);

            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
        }
        else
            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);

        }



        return 0;
}
int Database::Delete_from_Table(mega_struct* mega){

     char *is_null = "\0";

         buffer_manager bm;

        sys_table_entry *st;

        long tid;

        de_struct *de;

        //get table id from systable
        //fill schema from syscolumn

        if(!strcmp(Current_Open_DB_Name, is_null)){

            printf("\nNo Database is currently in use\n");

            return ERROR;

        }

        else{

            char table_name[NAME_LENGTH];

            strcpy(table_name, mega->Table);

            //go to systable
            //search for table name
            sysTabPage = bm.BufferRead(Current_Open_DB_Name,SYS_TABLE_PAGE);

            SysTableOverlay systab(sysTabPage);//systab.systabPage open in read mode

            st = systab.FindSysTableEntry(mega);//systab.searchpage open in write mode

            tid = st->TID;

            RID rid;

            rid = st->col_rid;

            sysCol_dbPage = bm.BufferRead(Current_Open_DB_Name,rid.pageno);//sysCol_dbPage open in read mode

            SysColumnOverlay syscol(sysCol_dbPage,SYS_COLUMN_PRIORITY);

            syscol.gotoSlot(rid.slotno);

            syscol.updateDataPtr();

            syscol.FillmegaStruct(mega);


               bool flag = false;

               long temp_TFS;

               long max_tfs_entry;
//           if (found == false)
//               return 1;

            DPPage = bm.BufferWrite(Current_Open_DB_Name,st->first_DP_Page_Number);//DPPage open in write mode in order to delete

            do
            {
                DPPageOverlay TableDP(DPPage);

                de = (de_struct *)(TableDP.dpPage->_data + sizeof(dp_page));
                temp_TFS = de->page_TFS;
                for(int i = 0 ; i < maxDE ; i++){

                    if(de->page_num == -1){
                        flag = true;
                        break;
                    }

                    MegaStruct::Allocate(mega);

                    DBPage = bm.BufferWrite(Current_Open_DB_Name, de->page_num);//DB PAge opened in write mode

                    DBOverlay DBNav(DBPage, DB_PAGE_PRIORITY);

                    DBNav.delete_all(mega);

                    MegaStruct::Clean(mega);
                    
                    temp_TFS = de->page_TFS;

                    de->page_TFS = DBPage->_TFS;

                    bm.ReleasePage(Current_Open_DB_Name, DBPage->_page_number);//DBPage released

                    //update maximum TFS in DP Page now


                    dp_page *dph = (dp_page *)TableDP.dpPage->_data;

                    max_tfs_entry = dph->max_TFS_withinTheDP;

                    if(temp_TFS == max_tfs_entry){

                        long max_tfs = TableDP.getMaxTFSwithinDE();

                        TableDP.setMaxTFSwithinDE(max_tfs);
                    }

                    de++;
                 }
                if(flag == true){
                break;
                }
                long next_dp = DPPage->_next_page;
                if ( next_dp != -1)
                {
                    

                    bm.ReleasePage(Current_Open_DB_Name, DPPage->_page_number);
                    DPPage = bm.BufferWrite(Current_Open_DB_Name, next_dp);
                }

            }while (DPPage->_next_page != -1);

            //release sysCOl_Db page
            bm.ReleasePage(Current_Open_DB_Name,sysCol_dbPage->_page_number);
            //release DP Page
            bm.ReleasePage(Current_Open_DB_Name,DPPage->_page_number);

            //release systabPages
        if(systab.searchPage->_page_number != systab.systabPage->_page_number){

            bm.ReleasePage(Current_Open_DB_Name,systab.searchPage->_page_number);

            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);
        }
        else
            bm.ReleasePage(Current_Open_DB_Name, systab.systabPage->_page_number);



            return 0;
        }

}

int Database::DeleteTable(mega_struct *mega){

    buffer_manager bm;

    genpage *pg_sys = bm.BufferRead(Current_Open_DB_Name,SYS_TABLE_PAGE);

    SysTableOverlay *systab = new SysTableOverlay(pg_sys);

    systab->DeleteSysTableEntry(mega);

    bm.ReleasePage(Current_Open_DB_Name, systab->systabPage->_page_number);

   // bm.Commit(Current_Open_DB_Name, systab->systabPage->_page_number);
    return SUCCESS;
    
}

int Database::Delete_DB(char *_db_Name){

}