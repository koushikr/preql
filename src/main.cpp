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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits>

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "SysTableOverlay.h"
#include "DBOverlay.h"
#include "SysColumnOverlay.h"
#include "Utils.h"
#include "MegaStruct.h"


#define SIMPLE 0
#define COMPLEX 1
//#include <strstream>

using namespace std;

//int Verbose_Flag;
#define TESTPAGE 29

bool select_flag;

typedef std::vector<mega_struct> mega_list;
buffer_manager buffer1;
Database db;

/*Declarations*/
//UI functions Declarations
int PrintTypeofQueryMenu();
int Print_Main_options();
int Print_DB_Gui_Options();
int PrintSQLqueryMenu();
int Print_Buffer_Gui_Options();
int Print_Gui_Options();

//SQL functions declarations
int CreateTable();
mega_list BulkCreateTable();
int InsertTable();
int InstantInsertTable();
int BulkInsert();
int SelectTable();
int  Rec_insert_Cond(mega_struct *mega);
int Delete_record();
int DeleteTable();
int DescribeTable();
int showTables();

//Other functions declarations
int Showslot();
void Clear_Options();
void Process_Options(int argc,char *argv[]);


// Main Function
int main(int argc,char *argv[])
{
    

        //string temp;
        Clear_Options();
        //printf("========== %d",sizeof(dp_page));

        // Get choice option for testing GUI
        int opt,i, cont = 0;
        char aks_db_name[MAX_FILE_NAME];
        long numpages, status, initsize;
        //Verbose_Flag = FSET;
        // Process the command prompt options
        Process_Options(argc,argv);
        Replace_Policy = LRU;
        // Give opt some high value to exit
        opt=20;

        buffer1.PrintVerbose("MAIN:: The program is in verbose mode");
        //long ff;
        //ff = ((PG_DATASIZE - sizeof(dp_page))/sizeof(de_struct));
        //printf("\nde----------%ld\n",ff);
        printf("\n\t\tBUFFER MANAGER");
        printf("\n\t\t--------------\n");
        printf("Size for the buffer Manager(in KB): ");
        scanf("%ld",&initsize);
        Buffer_Pool::InitBuffer(initsize);
        //buffer1.InitBuffer(initsize);
        strcpy(Current_Open_DB_Name, "\0");
        int option = 10, main_opt = 10, buffer_opt = 20, db_opt = 20, sql_opt = 20;
        bool check_exit = false;
        int result;
        mega_struct *mega_str;
        mega_list m;
        do {
            if(check_exit == true) break;
            main_opt = Print_Main_options();
            switch(main_opt){
                case 1:
                    //Buffer_Manager
                    do{
                        buffer_opt = Print_Buffer_Gui_Options();
                        switch(buffer_opt){
                            // Create DB
                        case 1:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\t\nEnter the name for the new database(max 16chars): ");
                                scanf("\t%s",aks_db_name);
                                printf("\t\nEnter the number of DB pages: ");
                                scanf("\t%ld",&numpages);
                                buffer1.CreateDB (aks_db_name, numpages, PAGESIZE);
                                break;

                        // Delete DB
                        case 2:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the new database(max 16chars): ");
                                scanf("%s",aks_db_name);
                                buffer1.DeleteDB (aks_db_name);
                                break;

                        // Increment DB
                        case 3:
                                printf("\nEnter the number of DB pages for increamenting: ");
                                scanf("%ld",&numpages);
                                buffer1.IncrementDB (numpages, PAGESIZE);
                                break;

                        // Read Page
                        case 4:
                                // use the current DB and page num will be stored in numpages
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to be read: ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the page number: ");
                                scanf("%ld",&numpages);
                                buffer1.ReadPage (aks_db_name, numpages);
                                break;

                        // Write Page
                        case 5:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to be read: ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the page number: ");
                                scanf("%ld",&numpages);
                                buffer1.WritePage (aks_db_name, numpages);
                                break;

                        // Show Frame
                        case 6:
                                // Here numpages takes form of frame number
                                printf("\nEnter the frame number: ");
                                scanf("%ld",&numpages);
                                buffer1.ShowFrame(numpages);
                                break;

                        // Show Frames
                        case 7:
                                buffer1.ShowFrames();
                                break;

                        // Commit
                        case 8:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to commit: ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the page number: ");
                                scanf("%ld",&numpages);
                                buffer1.Commit(aks_db_name, numpages);
                                break;

                        // Commit All
                        case 9:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to commit: ");
                                scanf("%s",aks_db_name);
                                buffer1.CommitAll(aks_db_name);
                                break;

			// Release Buffer and Exit
                        case 10:
                                buffer1.CommitAll(Current_Open_DB_Name);
                                Buffer_Pool::ReleaseBuffer();
                                break;

                        // Open the DB
                        case 11:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to open: ");
                                scanf("%s",aks_db_name);
                                status = buffer1.OpenDB (aks_db_name);
                                if (status==ERROR)
                                        printf("\nError has occured from OpenDB");

                                break;

                        //Print all the entries in Db Handler
                        case 12:
                                if (curDbOpen == 0)
                                        printf("\nThe DB Table Index is Empty");
                                else
                                {
                                        printf("\n----------Printing DB Handler entries--------------");
                                        for (i=0;i<curDbOpen;i++)
                                        {
                                                printf("\nIndex: %d",i+1);
                                                printf("\nDb Name: %s",db_handle[i]._dbname);
                                                printf("\nDb Index: %ld",db_handle[i]._db_index);
                                                printf("\n\n");
                                        }
                                }
                                break;

                         //go back to main menu
                         case 13:

                                break;

                         default:
                             printf("\tERROR:: Unknown Option\n");


                        }

                    }while(buffer_opt != 13);
                    break;

                case 2:
                    //DAtabase Module
                    do{
                        if(check_exit == true) break;//break to exit
                        db_opt = Print_DB_Gui_Options();
                        switch(db_opt){

                            case 1:
                                //Create DB
				buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the new database(max 16chars): ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the number of DB pages: ");
                                scanf("%ld",&numpages);
                                db.Create_DB (aks_db_name, numpages, PAGESIZE);
                                break;

                            case 2:
                                //useDB

                                char dbname[NAME_LENGTH];
                                printf("\nEnter the name of the database to be used\n");
                                scanf("%s",dbname);
                                db.Use_DB(dbname);
                                break;

                            case 3:
                                //SQL module
                                do{

                                    sql_opt = PrintSQLqueryMenu();
                                    switch(sql_opt){

                                        case 1:
                                            //CREATE MENU

                                            result = CreateTable();
                                            if(result == 0){
                                                printf("\nsuccess");
                                                 break;
                                            }
                                            
                                        case 2:
                                            //INSTANT INSERT MENU

                                            //InstantInsertTable();
                                            break;

                                        case 3:
                                            //INSERT MENU
                                            InsertTable();
                                            cout <<endl;
                                            cout <<"One record inserted"<< endl;
                                            cout << endl;
                                            cout << endl;
                                            Utils::pressEnter();
                                            break;

                                        case 4:
                                            //delete records from table
                                            //PrintMegaStructure(mega);
                                            Delete_record();
                                            cout << endl;
                                            cout << endl;
                                            Utils::pressEnter();
                                            break;
                                        
                                        case 5:
                                            //Show tables
                                            showTables();
                                            cout << endl;
                                            cout << endl;
                                            Utils::pressEnter();
                                            break;

                                        case 6:
                                            //Select table
                                            SelectTable();
                                            cout << endl;
                                            cout << endl;
                                            Utils::pressEnter();
                                            break;
                                       
                                        case 7:
                                            //Bulk CReate table
                                            m = BulkCreateTable();
                                            for(i = 0; i< m.size();i++){
                                            mega_str = &m[i];
                                            result = db.Create_Table(mega_str);
                                            }
                                            if(result == 0){
                                               printf("\nsuccess");
                                               break;
                                            }

                                    case 8:
                                        //Show slot
                                            //Showslot();
                                            BulkInsert();
                                            break;

                                    case 9:
                                        //Describe table
                                            DescribeTable();
                                            cout << endl;
                                            cout << endl;
                                            Utils::pressEnter();
                                            break;
                                    case 10:
                                        //go to database module menu
                                            break;


                                    default:
                                            printf("\tERROR:: Unknown Option\n");

                                    }
                                }while(sql_opt != 10);

                                break;

                            case 4:
                                //Commit All
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to commit: ");
                                scanf("%s",aks_db_name);
                                buffer1.CommitAll(aks_db_name);
                                break;

                            case 5:
                                //Release buffer and exit
                                buffer1.CommitAll(Current_Open_DB_Name);
                                Buffer_Pool::ReleaseBuffer();
                                check_exit = true;
                                break;
                                
                            case 6:
                                //GO to main menu
                                break;
                            default:
                                printf("\tERROR:: Unknown Option\n");




                        }

                    }while(db_opt != 6 );

                    break;

                case 3:
                    //exit from main print menu
                    break;
                default:
                     printf("\tERROR:: Unknown Option\n");

            }
               

        }while(main_opt !=3);

	
	return 0;
}



void Clear_Options()
{
	Verbose_Flag = FRSET;
}

void Process_Options(int argc,char *argv[])
{
	int i;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			switch (toupper(argv[i][1]))
			{
				case 'V':
					Verbose_Flag = FSET;
					break;

				default:
					printf("\n Unknown Option ");
					printf("\n");
					exit(ERROR);
			}
		}
		i++;
	}
}

int Print_Main_options(){
    int get_opt;
    printf("\n\n\n\t\t================\n");
    printf("\t\t1. BUFFER MANAGER");
    printf("\n\n\n\t\t================\n");
    printf("\t\t2. DATABASE MODULE");
    printf("\n\n\n\t\t================\n");
    printf("\t\t3. FINISH PROGRAM");
    printf("\n\nEnter your option(1-3):: ");
    scanf("%d",&get_opt);
    return (get_opt);



}
int Print_Buffer_Gui_Options()
{
        int get_opt;

        printf("\n\n\t Buffer Manager Testing Module \n");
        printf("\t ----------------------------- \n");
        printf("\n\n");
        printf("\t List of Options: \n");
        printf("\t 1. Create DB: \n");
        printf("\t 2. Delete DB: \n");
        printf("\t 3. Increment DB: \n");
        printf("\t 4. Read Page: \n");
        printf("\t 5. Write Page: \n");
        printf("\t 6. Show Frame: \n");
        printf("\t 7. Show Frames: \n");
        printf("\t 8. Commit: \n");
        printf("\t 9. Commit All: \n");
        printf("\t 10. Release Buffer and Exit: \n");
        printf("\t 11. OpenDB: \n");
        printf("\t 12. Print DB Index: \n");
        printf("\t 13. Go Back to Previous menu: \n");
        printf("\t ----------------------------- \n\n");
        
        printf("Enter your option(1-13):: ");
        scanf("%d",&get_opt);
        return (get_opt);
}

int Print_DB_Gui_Options(){
    int get_opt;

        printf("\n\n\t Database Testing Module \n");
        printf("\t ----------------------------- \n");
        printf("\t 1. Create_DB: \n");
        printf("\t 2. Use_DB: \n");
        printf("\t 3. SQL commands: \n");
        printf("\t 4. Commit All: \n");
        printf("\t 5. Release Buffer and Exit: \n");
        printf("\t 6. Go Back to Previous menu: \n");
        printf("\t ----------------------------- \n\n");
        printf("Enter your option(1-6):: ");
        printf("\n\n");
        scanf("%d",&get_opt);
        return (get_opt);



}

int PrintSQLqueryMenu(){
    int option;
    printf("\n\n\t SQL Query Module \n");
    printf("\t ----------------------------- \n");
    printf("\t1. Create Table Query: \n");
    printf("\t2. Instant Insert into Table: \n");
    printf("\t3. Insert Into Table: \n");
    printf("\t4. Delete from Table: \n");
    printf("\t5. Print systable: \n");
    printf("\t6. Select * from Table: \n");
    printf("\t7. Bulk create Tables: \n");
    printf("\t8. Bulk Insert Records: \n");
    printf("\t9. Describe Table: \n");
    printf("\t10. flush Query and go back to previous menu \n");
    //printf("1. Create Table Query \n");
    printf("\t ----------------------------- \n\n");
    printf("\n\n");
    printf("\tEnter Option(1-10):: ");
    scanf("%d",&option);
    return (option);
    
}

int CreateTable(){

    mega_struct *imega;

    int i;

    char str[NAME_LENGTH];

    char dataType[NAME_LENGTH];

    imega = MegaStruct::Initialize();

    printf("\tEnter name of the table \n");

    scanf("\t%s",str);

    strcpy(imega->Table, str);
    
    printf("\tEnter the number of columns\n");

    scanf("\t%ld",&(imega->NumPattr));

    Attribute *a;

    
        
    for(i = 0; i< imega->NumPattr; i++){

        a = (Attribute *)malloc(sizeof(Attribute));
        
        printf("\tEnter Column# %d name\n",i);

        

        a->ppos = (i + 1);

        a->value = NULL;

        scanf("\t%s",a->attr_name);

        printf("\tEnter column type\n");

        scanf("\t%s", dataType);

        // Fill in the dataType

        if ( strcmp(dataType, "INT") == 0 )

            a->type = INT;

        else if ( strcmp(dataType, "VARCHAR") == 0 )

            a->type = VARCHAR;

        else if ( strcmp(dataType, "CHAR") == 0 )

            a->type = CHAR;

        else if ( strcmp(dataType, "FLOAT") == 0 )

            a->type = FLOAT;

        else

            a->type = VARCHAR;


        // Erase The DataType

        memset(dataType,'\0',NAME_LENGTH);

        printf("\tEnter length\n");

        scanf("\t%d",&(a->length));

        if(a->type == INT){

            a->length = sizeof(int);
          
        }

        if(a->type == FLOAT){

            a->length = sizeof(float);

        }

        printf("\tEnter 0 if primary key attribute else enter 1\n");

        //cout << "\t";

        cin >> a->IsPrimary;
        
        a->value = (char *)malloc(a->length*sizeof(char));

        a->ppos = i+1;

        a->IsNull = false;

        imega->Pattr.push_back(a);

    }

    imega->Relation = CREATE;


    printf("\n in main's create\n");
    UI::PrintColumns(imega);

    db.Create_Table(imega);

    MegaStruct::Destroy(&imega);

    return 0;

}


mega_list BulkCreateTable(){

    mega_list m;
    
    mega_struct imega;

    long number_of_tables, i;

    char *str, *str1;

    printf("\tEnter number of the table \n");

    scanf("\t%ld",&number_of_tables);

    Attribute *a;

    

    for(i = 0 ; i < number_of_tables ; i++){

        a = (Attribute *)malloc(sizeof(Attribute));

        a->ppos = (i + 1);

        a->value = NULL;

        strcpy(a->attr_name,"c1");

        a->type = INT;

        a->IsPrimary = 1;

        a->length = sizeof(int);

        str = (char *)malloc(NAME_LENGTH * sizeof(char));

        str1 = (char *)malloc(NAME_LENGTH * sizeof(char));

        Utils::itoa(i,str1,10);

        strcpy(str,"t");
    
        strcat(str,str1);
    
        strcpy(imega.Table,str);

        free(str);
     
        imega.NumPattr = 1;

        imega.Pattr.push_back(a);

        imega.Relation = CREATE;

        m.push_back(imega);

    }

    return m;

}


int BulkInsert(){
    
    mega_struct *imega;

    imega = MegaStruct::Initialize();

    printf("\n Enter the table name\n");

    scanf("%s",imega->Table);

    imega->Relation = INSERT;

    db.Bulk_Insert_Table(imega);

    MegaStruct::Destroy(&imega);

    return 0;

}

//void InstantInsertTable()
//{
//    int i;
//    int dataType;
//    char *data;
//    for(i = 0; i< mega->NumPattr; i++){
//
//        /*        if (mega->Pattr[i].value != NULL)
//        {
//            void *freeptr;
//            freeptr = mega->Pattr[i].value;
//            free(freeptr);
//            mega->Pattr[i].value = NULL;
//        }
//         */
//        memset(mega->Pattr[i].value,NULL,mega->Pattr[i].length);
//
//        printf("\tEnter column value for Column Name: %s \n", mega->Pattr[i].attr_name);
//        dataType =  mega->Pattr[i].type;
//        data = (char*)mega->Pattr[i].value;
//        //data = (char*)malloc(mega->Pattr[i].length * sizeof(char));
//        //memset(data,NULL,mega->Pattr[i].length);
//        switch (dataType)
//        {
//            case INT:
//                scanf("\t%d", (int *)data);
//                break;
//            case FLOAT:
//                scanf("\t%f", (float *)data);
//                break;
//            case CHAR:
//                scanf("\t%s", (char *)data);
//                break;
//            case VARCHAR:
//                scanf("\t%s", (char *)data);
//                break;
//        }
//        //mega->Pattr[i].value = data;
//    }
//
//    buffer_manager bm;
//    DBOverlay *dbp;
//    genpage *mypage;
//    mypage = bm.BufferWrite(Current_Open_DB_Name,TESTPAGE);
//
//    dbp = new DBOverlay(mypage, DB_PAGE_PRIORITY);
//    long rec_length;
//    rec_length = DBOverlay::computeSize(mega);
//    dbp->insert_slot(mega,rec_length);
//
//    bm.ReleasePage(Current_Open_DB_Name, mypage->_page_number);
//    //bm.Commit(Current_Open_DB_Name,mypage->_page_number);
//}

int InsertTable(){

    mega_struct *imega;

    char table_name[NAME_LENGTH];

    imega = MegaStruct::Initialize();

    printf("\tEnter the table name\n");

    scanf("\t%s",table_name);

    strcpy(imega->Table,table_name);

    imega->Relation = INSERT;
    
    db.Insert_Table(imega);

    MegaStruct::Destroy(&imega);

    return 0;

}

int SelectTable(){

    mega_struct *imega;

    int option;

    Attribute *a;

    imega = MegaStruct::Initialize();

    char tablename[NAME_LENGTH];
    
    printf("\tEnter table name to be printed\n");

    scanf("\t%s",tablename);
    
    strcpy(imega->Table,tablename);

    imega->NumPattr = 0;

    printf("\tEnter column names to be projected\n");

    int count = 0;

    int test = 1;

    select_flag = false;

//inputting Projection attributes
    while(1){

        count++;

        printf("\tEnter column # %d name\n", count);

        a = (Attribute *)malloc(sizeof(Attribute));

        scanf("%s", a->attr_name);

        if(strcmp(a->attr_name,"*") == 0){

            //SET  select_flag

            select_flag = true;

            free(a);

            break;
        }

        imega->Pattr.push_back(a);

        imega->NumPattr = imega->NumPattr + 1;

        printf("\tDo you wish to enter more columns... enter 1 for 'yes' and 0 for 'no'\n");

        scanf("%d",&test);

        if(test != 1)
        {
            break;
        }
    }

    //fill sattr ----- select attributes
    //set number of select attributes to zero initially
    imega->NumSattr = 0;

    //filling conditions in postfix order
    printf("\nDo you wish to enter conditions? 1 for yes or 0 for no\n");

    scanf("%d",&option);

    if(option == 1){

        Rec_insert_Cond(imega);


        //checking if the order is indeed postfix..
        
        printf("\n");
       
        for(int j = 0; j < imega->Condition.size(); j++){

            if(imega->Condition[j]->type != COLUMN){
            
                printf("%s\t", (char *)imega->Condition[j]->value);

            }
            else{

                int p = *(int *)imega->Condition[j]->value;

                printf("%s\t",imega->Sattr[p-1]->attr_name);
            }
                
        }

    }

    imega->Relation = SELECT;
    
    db.Select_Table(imega);

    MegaStruct::Destroy(&imega);

    return 0;

}

int Rec_insert_Cond(mega_struct *mega){

    int type;

    condition *cond;

    bool cond_set = false;

    Attribute *a;

    char *op_name1 = NULL , *op_name2 = NULL, *op = NULL;

    printf("\n Enter type of first operand 0. SIMPLE     1. COMPLEX\n");

    scanf("%d",&type);

    if(type == SIMPLE){

        printf("\n the first operand type is simple \n");

        cond = (condition *)malloc(sizeof(condition));

        printf("\n Enter first operand type-----> 0. COLUMN    1. LITERAL    2. OPERATOR\n");

        scanf("%d",&(cond->type));
        
        printf("\n Enter first operand name\n");
            
        op_name1 = (char *)malloc(NAME_LENGTH * sizeof(char));

        scanf("%s", op_name1);

        if(cond->type == COLUMN){

            a = (Attribute *)malloc(sizeof(Attribute));

            strcpy(a->attr_name,op_name1);

            for(int i = 0; i < mega->Sattr.size(); i++){

                if(strcmp(op_name1, mega->Sattr[i]->attr_name) == 0){

                    cond->value = (int *)malloc(sizeof(int));

                    *(int*)cond->value = i;

                    cond_set = true;

                }


            }

            mega->Sattr.push_back(a);

            mega->NumSattr = mega->NumSattr + 1;

            if(cond_set == false){

                cond->value = (int *)malloc(sizeof(int));

                *(int*)cond->value = mega->Sattr.size();
            }
            
        }
       else if(cond->type != COLUMN){
            cond->value = (char *)malloc(NAME_LENGTH * sizeof(char));
            strcpy((char*)cond->value, op_name1);
            //mega->Condition.push_back(cond);
        }
        mega->Condition.push_back(cond);

    }
    else
    {
        printf("\n the first operand type is complex \n");

        Rec_insert_Cond(mega);
    }



    printf("\n Enter type of second operand 0. SIMPLE     1. COMPLEX\n");

    scanf("%d",&type);

    if(type == SIMPLE){

        printf("\n the second operand type is simple \n");

        cond = (condition *)malloc(sizeof(condition));

        printf("\n Enter second operand type-----> 0. COLUMN    1. LITERAL    2. OPERATOR\n");

        scanf("%d",&(cond->type));

        printf("\n Enter second operand name\n");

        op_name2 = (char *)malloc(NAME_LENGTH * sizeof(char));

        scanf("%s", op_name2);

        if(cond->type == COLUMN){

            a = (Attribute *)malloc(sizeof(Attribute));

            strcpy(a->attr_name,op_name2);

            for(int i = 0; i < mega->Sattr.size(); i++){

                if(strcmp(op_name1, mega->Sattr[i]->attr_name) == 0){

                    cond->value = (int *)malloc(sizeof(int));

                    *(int*)cond->value = i;

                    cond_set = true;

                }
            }

            mega->Sattr.push_back(a);

            mega->NumSattr = mega->NumSattr + 1;

            if(cond_set == false){

                cond->value = (int *)malloc(sizeof(int));

                *(int*)cond->value = mega->Sattr.size();
            }
  
            
        }

         else{

            cond->value = (char *)malloc(NAME_LENGTH * sizeof(char));

            strcpy((char*)cond->value, op_name2);

            //mega->Condition.push_back(cond);
        }
        mega->Condition.push_back(cond);


        
    }
    else
    {

        printf("\n the second operand type is complex \n");

        Rec_insert_Cond(mega);
    }


    printf("\n Enter operator \n");

    op = (char *)malloc(NAME_LENGTH * sizeof(char));

    scanf("%s",op);

    cond = (condition *)malloc(sizeof(condition));

    cond->value = (char *)malloc(NAME_LENGTH * sizeof(char));
        
    strcpy((char*)cond->value,op);

    cond->type = OPERATOR;

    mega->Condition.push_back(cond);

    if(op != NULL){
    
        free(op);
    }
    if(op_name1 != NULL){
    
        free(op_name1);
    }
    if(op_name2 != NULL){
    
        free(op_name2);
    }

    return 0;

}



int DeleteTable(){
    mega_struct *imega;
    imega = MegaStruct::Initialize();
    char tablename[NAME_LENGTH];
    printf("\t\tEnter table name to be deleted\n");
    scanf("%s",tablename);
     //printf("hehe");
//     mega->Table =(char *)malloc(NAME_LENGTH * sizeof(char));
    strcpy(imega->Table,tablename);
   
    imega->Relation = DELETE;

    MegaStruct::Destroy(&imega);
    
    return 0;

}

int DescribeTable(){

    mega_struct *imega;
    imega = MegaStruct::Initialize();
    printf("\t\tEnter table name :");
    scanf("%s",imega->Table);
    imega->Relation = DESCRIBE;

    db.Describe_Table(imega);

    MegaStruct::Destroy(&imega);

    return 0;


}

int Delete_record(){

    mega_struct *imega;
    imega = MegaStruct::Initialize();
    printf("\t\tEnter table name :");
    scanf("%s",imega->Table);
    int option;
    imega->NumSattr = 0;

    //filling conditions in postfix order

    printf("\nDo you wish to enter conditions? 1 for yes or 0 for no\n");

    scanf("%d",&option);

    if(option == 1){

        Rec_insert_Cond(imega);



        printf("\n");
       // printf("size of vector is %d", imega->Condition.size());
        //int j;
        for(int j = 0; j < imega->Condition.size(); j++){
            if(imega->Condition[j]->type != COLUMN){

                printf("%s\t", (char *)imega->Condition[j]->value);

            }
            else{

                int p = *(int *)imega->Condition[j]->value;

                printf("%s\t",imega->Sattr[p-1]->attr_name);
            }

        }

    }

    imega->Relation = DELETE;

    db.Delete_from_Table(imega);

    MegaStruct::Destroy(&imega);

    return 0;

}

int showTables(){

    db.ShowSysTable();
    return 0;
}

//void Showslot(){
//    buffer_manager bm;
//    DBOverlay *dbp;
//
//    genpage *mypage;
//    mypage = bm.BufferWrite(Current_Open_DB_Name,TESTPAGE);
//
//    int slotno;
//    dbp = new DBOverlay(mypage, DB_PAGE_PRIORITY);
//    printf("\t\nEnter the slot No (%ld): ", dbp->getNumberOfSlots());
//    scanf("%d",&slotno);
//    dbp->read_slot(slotno,mega);
//
//    bm.ReleasePage(Current_Open_DB_Name, mypage->_page_number);
//    //bm.Commit(Current_Open_DB_Name,mypage->_page_number);
//
//}




