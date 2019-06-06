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

#ifndef SYSTABLEOVERLAY_H
#define	SYSTABLEOVERLAY_H
#include "globals.h"
#include "db.h"
#include "buffer_manager.h"


const long page_space = (PG_DATASIZE -sizeof(SysTableHeader));
const long maxnoOfentries = page_space/sizeof(sys_table_entry);

class SysTableOverlay {

public:
    genpage *systabPage;
    genpage *lastsystabPage;
    genpage *searchPage;
    genpage *deletePage;
    //SysTableOverlay();
    SysTableOverlay(genpage *pg);
    ~SysTableOverlay();
    void CreateSystablePage();
    sys_table_entry* AddSysTableEntry(mega_struct *mega, long DP_Page_Num);
    sys_table_entry* FindSysTableEntry(mega_struct *mega);
    sys_table_entry* FindSystableEntrybyID(long TID);
    long DeleteSysTableEntry(mega_struct *mega);
    void PrintSysTable();
    void ShowError();


private:
    sys_table_entry* RecursiveFind(mega_struct *mega);
    sys_table_entry* RecursiveFindbyID(long tid);

};

#endif	/* SYSTABLEOVERLAY_H */

