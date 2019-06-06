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

#ifndef DPPAGEOVERLAY_H
#define	DPPAGEOVERLAY_H
#include "db.h"
#include "globals.h"
#include "SysTableOverlay.h"
#include "buffer_manager.h"

const long dp_page_space = (PG_DATASIZE -sizeof(dp_page));
const long maxDE = dp_page_space/sizeof(de_struct);

class DPPageOverlay {
public:
    genpage *dpPage;

    genpage *temp_dpPage;

    genpage *dbPage;

    genpage *systabPage;

    genpage *dpSearchPage;
    
    //DPPageOverlay();
    DPPageOverlay(genpage* pg);
    
    ~DPPageOverlay();

    int CreateDPPage();

    long getDPHeaderDECount();

    long getMaxTFSwithinDE();

    int setDPHeaderDECount(long count);

    int setMaxTFSwithinDE(long max_tfs);
    //de_struct* FindFreeDE();


    //Search Functions
    de_struct* DE_Search_by_dbPageNumber(long dbPageNumber);

    long DP_Search_by_TFS(long space_req);

    de_struct* DE_Search_by_TFS(long space_req);

    int DE_Update();

    de_struct* GetLastUsedDE();

    long GetLastDPPage(long tid);

    de_struct* DE_Add();

    int DE_Delete(de_struct *de, mega_struct *mega);

    void PrintDPPage();

    void ShowError();




};

#endif	/* DPPAGEOVERLAY_H */

