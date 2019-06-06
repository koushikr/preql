/* 
 * File:   SysTableOverlay.h
 * Author: anmol
 *
 * Created on 19 November, 2010, 3:04 AM
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

