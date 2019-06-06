/* 
 * File:   DBOverlay.h
 * Author: saghai
 *
 * Created on November 20, 2010, 11:57 AM
 */


#include "db.h"
#include "UI.h"
#include "math.h"
#include "cstring"
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "vector"
#include "stack"
#ifndef DBOVERLAY_H
#define	DBOVERLAY_H

#define PSET 0
#define CURRSET 1
#define SLOTSET 2

#define FWD_CURSOR 1
#define REV_CURSOR 2

//[sahil] This should go in globlas.h
#define BYTESIZE 8

#define INITCFS (PG_DATASIZE - (sizeof(long) + sizeof(slot_index) + 1))

// [Anmol] take note This should go in db.h

// [Anmol] take note This should go in db.h

typedef struct vAttr_Entry{
    char *val;
    long size;
    bool bool_var_size;
}vattr;

typedef struct Record
{
    char *dataptr;
    unsigned int size;
}record;


// [Anmol] take note This should go in db.h


typedef struct Slot_Index_Item{
    unsigned long point;
    unsigned long size;
}slot_index;


class DBOverlay {
protected:
    
public:
    genpage *dbpage;
    char *icursor;
    char *index_cursor;
    slot_index *slotinfo;
    long TFS;
    long *numSlots;
    slot_index *CFS_index;
    std::stack<condition*> mystack;

    //To Calculate Slot_Index size
    static long getSlotIndexSize();

    // Maintaing state of the DbPage
    long curSlotNo;
    char *dataCursor;
    unsigned int *mapCursor;
    unsigned int dataOffset;
    unsigned int mapOffset;
    unsigned int fixedDataOffset;

    void moveCursor(int cur_type, int cur_pos, long mbytes);
    void updateCFS(long newVal);
    // [sahil] this function should go in static utilities
    // The definations has been changed 
    int maxNoBits(unsigned long ip);
    unsigned long wInverseMask(unsigned long ip, int bits_req, int offset);
    unsigned long rInverseMask(unsigned long ip, int bits_req, int offset);

    //construcor
    DBOverlay();
    DBOverlay(genpage *ipage, long ipriority);


    static unsigned long computeSize(mega_struct *irequest);
    // API's for Slot access
    void firstSlot();
    void lastSlot();
    int newSlot(unsigned long size);
    void getCurSlotPointer();
    void getCurSlotSpace();
    void gotoSlot(long slotno);
    void nextSlot();
    void prevSlot();
    void decrementSlot();
    void incrementSlot();
    long getNumberOfSlots();
    bool checkDeleted();
    void updateDataCursor();


    // Slot insertion and retrieval and navigation through slot map (smap)
    void initSmap();
    int getCurSmap();
    void gotoNextSmap();
    void gotoPrevSmap();
    void newSmap(unsigned int val);
    void gotoSmap(int ppos);
    int getSmap(int ppos);

    //Record Navigation and Insertion
    void initRecordCursor(int numMaps);
    void setupRecordCursor();
    char* getRecord(int ppos, record *fillrec);
    void setRecord(void *rec, int size);
    char* getCurRecord();
    char* getNextRecord();

    long getTFS();
    long getCFS();
    long getCFSpoint();
    
    void initializeDB();
    long getOffset(long slotNumber);
    long getOffset(RID myRid);
    long write_slot(std::vector<vattr> irequest);
    long get_num_slots();


    // Advanced versions of the read and insert slot which uses bitmaps to save slot map space
    int adv_read_slot(long slotno, std::vector<vattr>& irequest);
    int adv_insert_slot(std::vector<vattr> irequest);

    // Normal insert and read slots which use integer slot map
    bool evaluate_condition(mega_struct *irequest);
    bool eval(condition *c1, condition *c2, condition *op, mega_struct *irequest);
    int read_slot(long slotno, mega_struct *irequest);
    int read_cur_slot(mega_struct *irequest);
    int selective_read_cur_slot(mega_struct *irequest);
    int insert_slot(mega_struct *irequest, unsigned long space_req);
    int select_all(mega_struct *irequest);
    long delete_all(mega_struct *irequest);
    bool delete_cur_slot(mega_struct *irequest);
    bool delete_slot(long slotNumber, mega_struct *irequest);
    int delete_sequential(mega_struct *irequest);

    long defragment();
    
    virtual ~DBOverlay();

};

#endif	/* DBOVERLAY_H */
