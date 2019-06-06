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

#ifndef SYSCOLUMNOVERLAY_H
#define	SYSCOLUMNOVERLAY_H
#include "db.h"
#include "DBOverlay.h"

typedef struct Column_Entry
{
    int length;
    int type;
    long ppos;
    bool is_primary;
    bool is_null;
    bool def_default;
    char column_name[NAME_LENGTH];
    char default_value[1];
}_UNPAD column_mask;


class SysColumnOverlay:public DBOverlay
   
{
public:
   // genpage *sysColumnPage;
    long* TID;
    unsigned int* no_columns;
    column_mask *icolumn;
    
    SysColumnOverlay();
    SysColumnOverlay(genpage *pg, long ipriority);

    ~SysColumnOverlay();

    static unsigned long computeSize(mega_struct *mega);

    void updateDataPtr();

    void gotoNextCol();

    long CreateSyscolumnPage(genpage *newSysColumnPage);

    RID AddSysColumnEntry(mega_struct *mega, long tid, unsigned long space_req);

    long DeleteSysColumnEntry();

    void PrintSysColumn();

    void FillmegaStruct(mega_struct *mega);

    int FillAttributeNames(mega_struct *mega);

    

    void SelectiveFillmegaStruct(mega_struct *mega);

    bool FindTable(long tid);
    
    void ShowError();
    


};


#endif	/* SYSCOLUMNOVERLAY_H */

