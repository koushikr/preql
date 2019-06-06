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
/* Source code for buffer manager */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

using namespace std;
#define BMGLOBAL
#define GLOBAL
#include "globals.h"
#include "buffer_manager.h"


/* ----------------------------BUFFER MANAGER APIs----------------------------------- */

// Buffer related
void Buffer_Pool::InitBuffer(long memsize)
{
	buffer_manager BM;
	if ( Verbose_Flag == FSET )
		printf("Initializing the Buffer Pool for %ld KB\n",memsize);

	FRAME_SIZE = sizeof(frame) + PG_DATASIZE - 1;
	FRAMES_NUM = ((memsize*KB)/FRAME_SIZE);
	BUFFER_SIZE = FRAMES_NUM*FRAME_SIZE;
	if ( Verbose_Flag == FSET )
		printf("Number of Frames Created: %ld\n",FRAMES_NUM);

	bufferPool = malloc(BUFFER_SIZE);

	// Initializing the frames
	printf("InitBuffer:: Initializing the Frames");
	long i;
	frame* curFrame;
        curFrame = BM.FirstFrame();
	for (i=1;i<=FRAMES_NUM;i++)
	{
		curFrame->_frameNo = i;
		curFrame->_dirty = 'n';
		curFrame->_pincount = 0;
		curFrame->_db_index = 0;
		curFrame->_inpage._page_number = -1;
		curFrame->_inpage._priority = 999;
		curFrame->_inpage._TFS = PG_DATASIZE;
		BM.Reset_String(curFrame->_inpage._data, PG_DATASIZE);
                curFrame = BM.MoveNextFrame();
	}

	curDbOpen = 0;
}

void Buffer_Pool::ReleaseBuffer()
{
	free(bufferPool);
}

// Buffer Manager Constructor

buffer_manager::buffer_manager()
{
    curFrame = (frame*)(bufferPool);
    frameNo = 0;
}


// Database Related
int buffer_manager::CreateDB (char *dbname, long dbpages, long page_size)
{
	dbname = AddExtension(dbname);

	char fulldbname[MAX_FULL_PATH];
	strcpy(fulldbname, concat(DBPATH, dbname));

	fp = fopen ( fulldbname , "rb" );

	if (fp != NULL)
	{
		printf ("\nDatabase %s already exists",dbname);
		fp = NULL;
		return 1;
	}
	else
	{
		fp = fopen ( fulldbname , "wb" );
		printf("\nfulldbname =%s\n",fulldbname);
		if (fp == NULL)
		{
			printf("\nDatabase %s cannot be created",dbname);
			return 1;
		}
		else
		{
			long i;
			for(i=0; i<(dbpages * page_size); i++)
	        	fwrite( "\0", sizeof(char), 1, fp );

			if (Verbose_Flag == FSET)
				printf("\n Database %s created successfully",dbname);

			// To create pages on the disk for the database
			rewind(fp);
			void* new_page_buffer;
			genpage* new_page;
			new_page_buffer = malloc(page_size);
			new_page = (genpage *)new_page_buffer;
			/* create the first page
					This is the Block 0 of the database and contains the following information in the order
					Page No: -> long -> 4 bytes
					Priority: -> long -> 4 bytes
			*/
			new_page->_page_number = 1;
			new_page->_priority = 0; //Highest Priority to the first page
			new_page->_next_page = 5;
			new_page->_TFS = PG_DATASIZE;
			sprintf(new_page->_data, "%ld", dbpages);
			WriteBlock(fp,1,new_page);

			for( i=2; i<=dbpages; i++)
			{
                            new_page->_page_number = i;
                            ResetPageHeaders(new_page);
				if (i==dbpages)
					new_page->_next_page = -1;
				else
					new_page->_next_page = i+1;
				WriteBlock(fp,i,new_page);
			}

			new_page = NULL;
			free(new_page_buffer);
			return 0;
		}
	}
}

long buffer_manager::OpenDB (char *dbname)
{
	FILE *localfp;
	char *qdbname;

	if (curDbOpen == MAX_DB_INDEX)
	{
		PrintVerbose("OpneDB:: Cannot open DB Index Full");
		return (ERROR);
	}

	// If the db handler is not full
	qdbname = AddExtension(dbname);
	char fulldbname[MAX_FULL_PATH];
	strcpy(fulldbname, concat(DBPATH, qdbname));
	printf("\nOpenDB:: FullDbName: %s",fulldbname);
	localfp = fopen ( fulldbname , "rb+" );

	if (localfp == NULL)
		return (ERROR);

	PrintVerbose("OpenDB:: Database opened and indexed");

	strcpy(db_handle[curDbOpen]._dbname, dbname);
	db_handle[curDbOpen]._db_fp = localfp;
	db_handle[curDbOpen]._db_index = curDbOpen+1;
	curDbOpen++;

	return db_handle[curDbOpen-1]._db_index;
}

void buffer_manager::DeleteDB (char *dbname)
{
	FuncUnderProgress();
}
 void buffer_manager::IncrementDB (long page_number, long page_size)
{
        
}
//Page Related
void buffer_manager::ReadPage (char *dbname, long page_number)
{
	frame *myframe;
	myframe = GetFrame(dbname,page_number);
        myframe->_last_access_time = time(NULL);
	printf("\nReading pageNo: %ld from the database: %s\n", page_number, dbname);
	puts(myframe->_inpage._data);
}
void buffer_manager::WritePage (char *dbname, long page_number)
{
	frame *myframe;
	genpage *mypage;
	long storesize;
	char *inputdata, *startread;
	inputdata = ( char*)malloc( PG_DATASIZE );
	Reset_String(inputdata,PG_DATASIZE);
	myframe = GetFrame(dbname,page_number);
	mypage = &(myframe->_inpage);

	if (mypage->_TFS == 0)
	{
		PrintVerbose("No Free Space In the Page");
		return;
	}

	startread = mypage->_data + ( PG_DATASIZE - mypage->_TFS );
	myframe->_dirty='y';
        myframe->_last_access_time = time(NULL);
	printf("\nEnter the data: ");
	fflush(stdin);
	scanf("%s",inputdata);
	storesize = mypage->_TFS - strlen(inputdata);
	if(storesize < 0)
	{
		storesize = mypage->_TFS;
		mypage->_TFS = 0;
	}
	else
	{
		storesize = strlen(inputdata);
		mypage->_TFS = mypage->_TFS - storesize;
	}
	strncpy(startread, inputdata, storesize);
	free(inputdata);
}

 bool buffer_manager::CommitCurrentFrame()
 {

     // NOTE::There is no check in this function to check whether the frame has valid page instated, this should be taken care in the calling function
        FILE* myfp;
        long dbindex;
        bool status = false;
        dbindex = curFrame->_db_index;
        if (curFrame->_dirty == 'y')
            {
                    PrintVerbose("Commit:: Change found in Page, saved to Storage");
                    myfp = db_handle[dbindex-1]._db_fp;
                    WriteBlock(myfp, curFrame->_inpage._page_number, &(curFrame->_inpage));
                    curFrame->_dirty = 'n';
                    status = true;
            }
            else
            {
                    PrintVerbose("Commit:: No Change Found in the Page");
            }

        return status;

 }

void buffer_manager::Commit (char *dbname, long page_number)
{
	long dbindex, framecount;
	dbindex = SearchDbHandler(dbname);
	frame *myframe;
	FILE* myfp;
	if(dbindex==ERROR)
	{
		PrintVerbose("Commit:: DB not Open, Nothing to Commit");
		return;
	}

	for( framecount = 1; framecount <= FRAMES_NUM; framecount++)
	{
		myframe = MoveToFrame(framecount);
		if (myframe->_db_index == dbindex)
		{
			if ( ExtractPageNo(myframe) == page_number )
			{
				PrintVerbose("Commit:: Page Found to be Commited");
				if (myframe->_dirty == 'y')
				{
					PrintVerbose("Commit:: Change found in Page, saved to Storage");
					myfp = db_handle[dbindex-1]._db_fp;
					WriteBlock(myfp,page_number,&(myframe->_inpage));
                                        myframe->_dirty = 'n';
				}
				else
				{
					PrintVerbose("Commit:: No Change Found in the Page");
				}

				return;
			}
		}
	}

}
void buffer_manager::CommitAll (char *dbname)
{
	long dbindex, framecount, found;
	dbindex = SearchDbHandler(dbname);
	frame *myframe;
	found = 0;
	if(dbindex==ERROR)
	{
		PrintVerbose("DB not Open, Nothing to Commit");
		return;
	}

        myframe = FirstFrame();
	for( framecount = 1; framecount <= FRAMES_NUM; framecount++)
	{
		if (myframe->_db_index == dbindex)
		{
                    if (CommitCurrentFrame() == true)
                        found++;
		}
                myframe = MoveNextFrame();
	}

	printf("\n%ld pages commited to the storage",found);
}

frame* buffer_manager::ApplyReplacement()
{
    // Choose from the replacement options
    switch (Replace_Policy)
    {
        case LRU:
            curFrame = LRUreplace();
            break;
    }

    CommitCurrentFrame();
    return curFrame;
}


frame* buffer_manager::LRUreplace()
{
    // Start searching from 1st frame
    time_t leastTime;
    frame* leastFrame;
    long framecount;

    FirstFrame();
    leastFrame = NULL;

    leastTime = time(NULL);

    for( framecount = 1; framecount <= FRAMES_NUM; framecount++)
    {
        if ( curFrame->_db_index != 0 && curFrame->_pincount == 0)
        {
            if (curFrame->_last_access_time < leastTime )
            {
                leastFrame = curFrame;
                leastTime = curFrame->_last_access_time;
            }
        }
        MoveNextFrame();
    }

    if (leastFrame != NULL)
    {
        cout << "\n Least Time: " << leastTime << endl;
        cout << "\n Frame No to be replaced: " << leastFrame->_frameNo << endl;
        curFrame = leastFrame;
    }
    else
        cout << "\nERROR: No Frame to free in Buffer Manager" << endl;
    
    return leastFrame;
}

//Frames Related

frame* buffer_manager::GetFrame(char *dbname, long page_number)
{
	// Only Interfaces with the DB Handler
	long dbindex, status;
	frame* retframe;
	// Check whether the specified db is indexed in db_handler
	dbindex = SearchDbHandler(dbname);
	if (dbindex == ERROR)
	{
		printf("\nPTEST:: The dbindex not found");
		OpenDB (dbname);

		dbindex = SearchDbHandler(dbname);
		retframe = LoadFrame(dbindex, page_number);
		return retframe;
	}

	// Search for the frame in BufferPool
	long framecount;
	for (framecount = 1; framecount <= FRAMES_NUM; framecount++)
	{
		retframe = MoveToFrame(framecount);
		if (retframe->_db_index != 0)
		{
			if (page_number == ExtractPageNo(retframe))
			{
				PrintVerbose("GetFrame:: Frame Found in the Buffer Pool");
				return retframe;
			}
		}
	}

	PrintVerbose("GetFrame:: Frame Not in the Buffer Pool, Asking To Load...");
	retframe = LoadFrame(dbindex, page_number);
	return retframe;

}

frame* buffer_manager::LoadFrame(long dbindex, long page_number)
{
	// Interfaces with the storage
	PrintVerbose("LoadFrame:: Trying to load the frame in Buffer Manager");
	frame *retFrame;
	FILE *localfp;
	localfp = db_handle[dbindex-1]._db_fp;
	// Replacement Algorithm comes here
	retFrame = GetFreeFrame();
        ResetFrame(retFrame);
	ReadBlock(localfp, page_number, (genpage*) (&(retFrame->_inpage)));
	retFrame->_db_index = dbindex;
	return retFrame;
}

void buffer_manager::ResetFrame(frame* myframe)
{
    myframe->_db_index = 0;
    myframe->_dirty = 'n';
    myframe->_last_access_time = time(NULL);
    myframe->_pincount = 0;
}

void buffer_manager::FlushFrame(frame *myframe)
{
	myframe->_dirty = 'n';
	myframe->_pincount = 0;
	myframe->_db_index = 0;
	myframe->_inpage._page_number = -1;
	myframe->_inpage._priority = 999;
	myframe->_inpage._TFS = 0;
	Reset_String(myframe->_inpage._data, PG_DATASIZE);
}

frame * buffer_manager::GetFreeFrame()
{
	long i;
	frame* curFrame;
	PrintVerbose("FreeFrame:: Trying To locate a free frame");

        curFrame = FirstFrame();
	for (i=1;i<=FRAMES_NUM;i++)
	{
		if (curFrame->_db_index == 0)
		{
			PrintVerbose("FreeFrame:: FREE Frame found");
			return curFrame;
		}
                curFrame = MoveNextFrame();
	}

        PrintVerbose("FreeFrame:: No FREE Frame found, Applying Replacement");
        curFrame = ApplyReplacement();
	return curFrame;
}

long buffer_manager::ExtractPageNo(frame *curFrame)
{
	return curFrame->_inpage._page_number;
}
void buffer_manager::ShowFrame(long frame_number)
{
	frame* curFrame;
	curFrame = MoveToFrame(frame_number);
	PrintFrame(curFrame);
}
void buffer_manager::ShowFrames()
{
	long i;
	frame* curFrame;
	PrintVerbose("\n------Printing the frames-----\n\n");

	curFrame = FirstFrame();
	PrintFrame(curFrame);
	for (i=1;i<FRAMES_NUM;i++)
	{
		curFrame = MoveNextFrame();
		PrintFrame(curFrame);
	}
}

void buffer_manager::PrintFrame(frame* curFrame)
{
	printf("\nFrame: %ld",curFrame->_frameNo);
	printf("\nDirty: %c",curFrame->_dirty);
	printf("\nPincount: %ld",curFrame->_pincount);
	printf("\nDB Index: %ld",curFrame->_db_index);
        printf("\nTime of Last Access: %ld",curFrame->_last_access_time);
	printf("\nPage->page no: %ld",curFrame->_inpage._page_number);
	printf("\nPage->priority: %ld",curFrame->_inpage._priority);
	printf("\nPage->next page: %ld",curFrame->_inpage._next_page);
	printf("\nPage->TFS: %ld",curFrame->_inpage._TFS);
	printf("\n");
}

/*---------------------Buffer Cursor Functions---------------*/
frame* buffer_manager::MoveNextFrame()
{
	long curFrameNum;
	curFrameNum = curFrame->_frameNo;
	if (curFrameNum == FRAMES_NUM)
	{
		PrintVerbose("NavFrames:: Frames Exhausted, Moving the the First Frame");
                curFrame = (frame*)(bufferPool);
		return curFrame;
	}
	else
	{
                curFrame = (frame *)(bufferPool + curFrameNum*FRAME_SIZE);
                return curFrame;
	}
}

frame* buffer_manager::MovePrevFrame()
{
	long curFrameNum;
	curFrameNum = curFrame->_frameNo;
	if (curFrameNum == 1)
	{
		PrintVerbose("NavFrames:: This is the first frame, Moving the the Last Frame");
		return MoveToFrame(FRAMES_NUM);
	}
	else
	{
		return MoveToFrame(curFrameNum-1);
	}
}

frame* buffer_manager::MoveToFrame(long frameno)
{
    
    if (frameno > FRAMES_NUM)
		PrintVerbose("NavFrames:: Illegal Frame Number");
    else
    {
        curFrame = (frame *)(bufferPool + (frameno-1)*FRAME_SIZE);
        return curFrame;
    }	
}

frame* buffer_manager::FirstFrame()
{
    curFrame = (frame*)(bufferPool);
    return curFrame;
}

frame* buffer_manager::LastFrame()
{
	return MoveToFrame(FRAMES_NUM);
}

/*----------------------DB Handler APIs-------------------*/
long buffer_manager::SearchDbHandler(char *dbname)
{
	int i;
	for(i=0; i<curDbOpen; i++)
	{
		if (strcmp(db_handle[i]._dbname, dbname) == 0)
			return (db_handle[i]._db_index);
	}
	PrintVerbose("SearchHandler:: Db not Indexed");
	return (ERROR);
}

/*---------------------Buffer APIs----------------------------*/

genpage* buffer_manager::BufferRead(char* dbname, long page_number)
{
	frame* myframe;
	myframe = GetFrame(dbname, page_number);
        myframe->_last_access_time = time(NULL);
        /*
	if (myframe->_pincount == -1)
	{
		printf("\nPage cannot be served. Its in write mode");
		return NULL;
	}
         */
	myframe->_pincount = myframe->_pincount + 1;
	return &(myframe->_inpage);
}

genpage* buffer_manager::BufferWrite(char* dbname, long page_number)
{
	frame* myframe;
	long pincount;
	myframe = GetFrame(dbname, page_number);
	pincount = myframe->_pincount;
        myframe->_last_access_time = time(NULL);
	/*
        if (pincount > 0 || pincount == -1)
	{
		//printf("\nPage: %ld of database: %s is currently in use for the operation");
		return NULL;
	}
        */
	myframe->_dirty = 'y';
	myframe->_pincount = myframe->_pincount + 1;
	return &(myframe->_inpage);
}

genpage* buffer_manager::GetFreePage(char *dbname)
{
	genpage *headpage, *freepage;
	long headFreeNo;
	headpage = BufferWrite(dbname, HEADER_PAGE);
	headFreeNo = headpage->_next_page;
	if ( headFreeNo == EMPTY )
	{
		PrintVerbose("GetFreePage:: No more free pages available, increment the database");
		return NULL;
	}

	freepage = BufferWrite(dbname, headFreeNo);
	headpage->_next_page = freepage->_next_page;
        freepage->_next_page = -1;
        PrintVerbose("FREEPAGE:: Giving off a free page");
        ReleasePage(dbname,HEADER_PAGE);
        //Commit(dbname, HEADER_PAGE);
	return freepage;

}

void buffer_manager::ReleasePage(char* dbname, long page_number)
{
	frame* myframe;
	myframe = GetFrame(dbname, page_number);
	/*if (myframe->_pincount == -1)
		myframe->_pincount = 0;
	else
         */
		myframe->_pincount = myframe->_pincount - 1;
}

void buffer_manager::ResetPageHeaders(genpage* ipage)
 {
    ipage->_priority = 999;
    ipage->_TFS = PG_DATASIZE;
    Reset_String(ipage->_data, PG_DATASIZE);
 }

void buffer_manager::DestroyPage(char* dbname, long page_number)
{
    frame* myframe;
    genpage* mypage, *headr_page;

    myframe = GetFrame(dbname, page_number);
    mypage = &myframe->_inpage;
    ResetPageHeaders(mypage);
    myframe->_dirty = 'y';

    headr_page = BufferRead(dbname,1);
    mypage->_next_page = headr_page->_next_page;
    headr_page->_next_page = mypage->_page_number;

    ReleasePage(dbname, 1);
    Commit(dbname, mypage->_page_number);
}


/*----------------------BlockStorage APIs-------------------*/
void buffer_manager::ReadBlock(FILE *dbfp,long page_number,genpage* wpage)
{
	fseek(dbfp, (page_number-1)*PAGESIZE, SEEK_SET);
	fread(wpage, 1, PAGESIZE, dbfp);
}

void buffer_manager::WriteBlock(FILE *dbfp,long page_number,genpage* rpage)
{
	fseek(dbfp, (page_number-1)*PAGESIZE, SEEK_SET);
	fwrite((void *)rpage, 1, PAGESIZE, dbfp);
}
/*----------------------OTHER APIs---------------------*/

void buffer_manager::ShowDatabases()
{
    cout << endl << endl << "----------------Databases------------------" << endl;
    system("./listDb.sh");
}



void buffer_manager::PrintVerbose(const char *str)
{
	if ( Verbose_Flag == FSET )
	{
		printf("\n%s",str);
	}
}


void buffer_manager::Reset_String(char *str,int size)
{
	memset(str,'\0',size);
}

char* buffer_manager::concat(char *str1, char*str2)
{
	char *res;
	res = (char *)malloc((strlen(str1) + strlen(str2))*sizeof(char));
	strcpy (res, str1);
	strcat (res, str2);
	return res;
}

char* buffer_manager::AddExtension(char *dbname)
{
	char *dbnamext;
	dbnamext = ( char *)malloc((strlen(dbname) + 4)*sizeof(char));
	dbnamext = concat(dbname,".aks");
	return (dbnamext);
}

void buffer_manager::FuncUnderProgress()
{
	printf("\nWOWRER:: This function is under progress, it will take time for the lazy bones complete it :) \n");
}