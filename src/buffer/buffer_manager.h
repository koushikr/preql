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

#ifndef BUFFER_MANAGER_H
#define	BUFFER_MANAGER_H
#include <cstdio>
#include <time.h>
#include "globals.h"
#ifndef BMGLOBAL
#define EXTERN extern
#else
#define EXTERN
#endif



/* Structures */
//page
typedef struct general_page
{
	long _page_number;
	unsigned long _priority;
	long _next_page;
	long _TFS;
	char _data[1];
}genpage;

//frame
typedef struct frame
{
	long _frameNo;
	char _dirty;
	long _pincount;
	long _db_index;
        time_t _last_access_time;
	genpage _inpage;
}_UNPAD frame;

//
typedef struct db_handler
{
	char _dbname[MAX_FILE_NAME];
	long _db_index;
	FILE *_db_fp;
}db_handler;


EXTERN void* bufferPool;
EXTERN long curDbOpen;

EXTERN long BUFFER_SIZE;
EXTERN long BUFF_CURSOR;
EXTERN long FRAME_SIZE;
EXTERN long FRAMES_NUM;

EXTERN FILE *fp;

EXTERN char gdbname[MAX_FILE_NAME];
EXTERN db_handler db_handle[MAX_DB_INDEX];



class Buffer_Pool{
	//Buffer related
	public:
	 static void InitBuffer(long page_size);
	 static void ReleaseBuffer();
};



class buffer_manager {
//private:

public:
    frame *curFrame;
    int frameNo;

/*------------- Constructor----------------- */
    buffer_manager();
/*------------- Private Prototypes----------------- */
// void Process_Options(int argc, char *argv[]);
//void Clear_Options();
char* concat (char *str1, char*str2);
char *AddExtension (char *dbname);

// Print the string only if the verbose is on
void PrintVerbose(const char *str);
// Reseting the string by memseting the size
void Reset_String(char *str,int size);
//For Testing GUI
//int Print_Gui_Options();
// For Functions under progress, delete when done
void FuncUnderProgress();

// void Compute_Params();
/*---------------Funtionalities Prototypes--------------- */

//DB related
 int CreateDB (char *dbname, long dbpages, long page_size);
 long OpenDB (char *dbname);
 void CloseDB (char *dbname);
 void DeleteDB (char *dbname);
 void IncrementDB (long page_number, long page_size);

//Page Related
 void ReadPage (char *dbname, long page_number);
 void WritePage (char *dbname, long page_number);
 void ResetPageHeaders(genpage* ipage);

 frame* ApplyReplacement();
 frame* LRUreplace();
 void Commit (char *dbname, long page_number);
 bool CommitCurrentFrame();
 void CommitAll (char *dbname);

//Frame Related
frame* GetFrame(char *dbname, long page_number);
frame* LoadFrame(long dbindex, long page_number);
void ResetFrame(frame *myframe);
void FlushFrame(frame *myframe);
long ExtractPageNo(frame *curFrame);
frame* GetFreeFrame();

//FOR TESTING
 void ShowFrame (long frame_number);
 void ShowFrames ();
 void PrintFrame(frame* curFrame);
/*---------------Buffer cursor prototypes--------------- */

frame* MoveNextFrame();
frame* MovePrevFrame();
frame* MoveToFrame(long frameno);
frame* FirstFrame();
frame* LastFrame();

/*---------------DB Handler prototypes--------------- */
long SearchDbHandler(char *dbname);

/*----------------------BlockStorage APIs-------------------*/
void ReadBlock(FILE *dbfp,long page_number,genpage* wpage);
void WriteBlock(FILE *dbfp,long page_number,genpage* rpage);

/*---------------------Buffer APIs----------------------------*/
genpage* BufferRead(char* dbname, long page_number);
genpage* BufferWrite(char* dbname, long page_number);
genpage* GetFreePage(char *dbname);
// Release page is for releasing the pincount
void ReleasePage(char* dbname, long page_number);
// Destroy page will completely reset the page and put it again into the free list
void DestroyPage (char *dbname, long page_number);
// [Sahil] This function will go under UI class
void ShowDatabases();
/*----------------------OTHER APIs---------------------*/

//void PrintVerbose(char *str);
//void Reset_String(char *str,int size);
//char* concat(char *str1, char*str2);
//char* AddExtension(char *dbname);
//void FuncUnderProgress();

};


#endif	/* BUFFER_MANAGER_H */
