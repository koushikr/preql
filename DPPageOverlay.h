/* 
 * File:   DPPageOverlay.h
 * Author: anmol
 *
 * Created on 19 November, 2010, 11:49 AM
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

