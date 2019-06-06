/* 
 * File:   DBOverlay.cpp
 * Author: saghai
 * 
 * Created on November 20, 2010, 11:57 AM
 */

#include "DBOverlay.h"

using namespace std;

unsigned long mask = 0x80000000;

DBOverlay::DBOverlay(){
    
}
DBOverlay::DBOverlay(genpage* ipage, long ipriority) {
    
    dbpage = ipage;
    curSlotNo = 0;
    moveCursor(REV_CURSOR, PSET, sizeof(long));
    numSlots = (long*)index_cursor;
    slotinfo = NULL;

    moveCursor(REV_CURSOR, CURRSET, sizeof(slot_index));
    CFS_index = (slot_index *)index_cursor;
    
    if ( ipage->_priority != ipriority )
    {
        printf("\nIts a new page altogether");
        ipage->_priority = ipriority;
        initializeDB();
    }
}


unsigned long DBOverlay::computeSize(mega_struct* irequest)
{
    unsigned long totalsize=0, actualSize=0, space_req = 0;
    for (int i=0; i< irequest->NumPattr ; i++)
    {
        totalsize = totalsize + irequest->Pattr[i]->length;
        if (irequest->Pattr[i]->type == VARCHAR)
              actualSize = actualSize + strlen((char *)irequest->Pattr[i]->value);
        else
              actualSize = actualSize + irequest->Pattr[i]->length;
    }

    int total_slot_map_bytes = 0, no_of_slot_map = 0;

    no_of_slot_map = irequest->NumPattr;
    total_slot_map_bytes = no_of_slot_map * sizeof (int);

    space_req = actualSize + total_slot_map_bytes;
    return space_req;
}

void DBOverlay::initializeDB()
{
    *numSlots = 0;
    updateCFS(INITCFS);
    dbpage->_TFS = getCFS();
    CFS_index -> point = 0;
}

void DBOverlay::moveCursor(int cur_type, int cur_pos, long mbytes)
{
    if ( cur_pos == PSET )
    {

        if ( cur_type == FWD_CURSOR )
          icursor = &(dbpage->_data[0]);
        
        else
          index_cursor = &(dbpage->_data[PG_DATASIZE - 1]);
    }

    if ( cur_pos == SLOTSET )
    {
        moveCursor(REV_CURSOR, PSET, sizeof(long) + sizeof(slot_index));
    }

    if ( cur_type == FWD_CURSOR )
       icursor = icursor + mbytes;
    else
       index_cursor = index_cursor - mbytes;

}

void DBOverlay::updateCFS(long newVal)
{
    CFS_index->size = newVal;
    printf("\nCFS updated to %ld", newVal);
}

void DBOverlay::updateDataCursor()
{
    moveCursor(FWD_CURSOR, PSET, slotinfo->point);
}


void DBOverlay::gotoSlot(long slotno)
{
    if (slotno < 0 || slotno > getNumberOfSlots())
    {
        printf("\nERROR:: SLOT access number invalid");
        return;
    }
    moveCursor(REV_CURSOR, SLOTSET, slotno*sizeof(slot_index));
    slotinfo = (slot_index*)index_cursor;
    curSlotNo = slotno;
}

bool DBOverlay::checkDeleted()
{
    if (slotinfo->size < 0)
        return true;

    return false;
}

int DBOverlay::newSlot(unsigned long size)
{
    if(size > getCFS())
    {
        printf("\nINSERT::Insufficent Space to insert, performing defragmentation on the DBpage");
        defragment();

        if (size <= getCFS())
            cout << ("\nINSERT::Space fit for new addition now, proceeding...") << endl;
        else
        {
            cout << "There seems to be problem with the addition please check again: " << endl;
            return(ERROR);
        }
            
    }
    if (getNumberOfSlots() != 0)
    {
        lastSlot();

    }
    else
    {
        moveCursor(REV_CURSOR, SLOTSET, 0);
        slotinfo = (slot_index*)index_cursor;
    }

    moveCursor(REV_CURSOR, CURRSET, sizeof(slot_index));
    slotinfo = (slot_index*)index_cursor;
    
    slotinfo->size = size;
    slotinfo->point = getCFSpoint();
    CFS_index->point = CFS_index->point + size;
    updateCFS(getCFS() - (size + sizeof(slot_index)));
    incrementSlot();
    curSlotNo = getNumberOfSlots();
    dbpage->_TFS = dbpage->_TFS - (size + sizeof(slot_index));
    cout << "\nDB::Created New slot with size: " << size << ", New slotno: " << getNumberOfSlots() << endl;
}

void DBOverlay::firstSlot()
{
    gotoSlot(1);
    curSlotNo = 1;
}

void DBOverlay::prevSlot()
{
    gotoSlot(curSlotNo - 1);
}


void DBOverlay::nextSlot()
{
    moveCursor(REV_CURSOR, CURRSET, sizeof(slot_index));
    slotinfo = (slot_index*)index_cursor;
    curSlotNo = curSlotNo + 1;
}

void DBOverlay::lastSlot()
{
    curSlotNo = getNumberOfSlots();
    gotoSlot(curSlotNo);
}

long DBOverlay::getSlotIndexSize(){

    return sizeof(slot_index);

}

long DBOverlay::getNumberOfSlots()
{
    long number_of_slots;

    number_of_slots = *numSlots;
    return number_of_slots;
}

long DBOverlay::getCFS()
{
    return CFS_index->size;
}

long DBOverlay::getCFSpoint()
{
    return CFS_index->point;
}

void DBOverlay::incrementSlot()
{
    *numSlots = *numSlots + 1;
}

void DBOverlay::decrementSlot()
{
    (*numSlots)--;
}

//------------------SLOT map Implementations------------------------//

void DBOverlay::initSmap()
{
    mapCursor = (unsigned int*)icursor;
    mapOffset=0;
}
int DBOverlay::getCurSmap()
{
    //cout << "Returning Offset: " << *mapCursor;
    return *mapCursor;
}
void DBOverlay::gotoNextSmap()
{
    mapCursor++;
    mapOffset = mapOffset + sizeof(unsigned int);
}
void DBOverlay::gotoPrevSmap()
{
    mapCursor--;
    mapOffset = mapOffset - sizeof(unsigned int);
}
void DBOverlay::newSmap(unsigned int val)
{
    *mapCursor = val;
    cout << "Input Offset: " << val << endl;
    mapCursor++;
    mapOffset = mapOffset + sizeof(unsigned int);
}
int DBOverlay::getSmap(int ppos)
{
    initSmap();
    int i;
    for (i=1; i<ppos; i++)
    {
        mapCursor++;
        mapOffset = mapOffset + sizeof(unsigned int);
    }
    //cout << "Returning Offset: " << *mapCursor << endl;
    return *mapCursor;
}

//-------------------------Record Navigation and Insertion------------------------------//
void DBOverlay::initRecordCursor(int numMaps)
{
        initSmap();
        fixedDataOffset = 0;
      dataCursor = icursor;
      dataOffset = numMaps*sizeof(int);
      dataCursor = dataCursor + ( dataOffset );
      fixedDataOffset = dataOffset;

}

void DBOverlay::setupRecordCursor()
{
    initSmap();
    fixedDataOffset = 0;
    dataOffset = getCurSmap();
    dataCursor = icursor + dataOffset;
    fixedDataOffset = dataOffset;
}

char* DBOverlay::getRecord(int ppos, record *fillrec)
{
    unsigned int lOffset=0, rOffset=0, recSize=0;
    char *retData;
    lOffset = getSmap(ppos);

    gotoNextSmap();
    if ( mapOffset >= fixedDataOffset )
    {
        rOffset = slotinfo->size;
        gotoPrevSmap();
    }
    else
    {
        rOffset = getCurSmap();
    }

    dataCursor = icursor + lOffset;
    dataOffset = lOffset;
    
    recSize = rOffset - lOffset;
    fillrec->dataptr = dataCursor;
    fillrec->size = recSize;
    /*
    retData = (char *)malloc( recSize*sizeof(char) );
    memset(retData, NULL ,recSize);

    memcpy(retData, dataCursor, recSize);
     */
    return NULL;
}
void DBOverlay::setRecord(void *rec, int size)
{
    if ( mapOffset >= fixedDataOffset )
    {
        cout << "ERROR:: No of records Exhausted";
    }
    newSmap(dataOffset);
    dataOffset = dataOffset + size;
    memcpy(dataCursor, (char*)rec, size);
    dataCursor = dataCursor + size;
}


bool DBOverlay::evaluate_condition(mega_struct* irequest)
{
    
    if(irequest->Condition.size() == 0){
        return true;
    }
    else{
    
        condition *c1, *c2, *op;
        for(int i = 0; i < irequest->Condition.size(); i++){

            if(irequest->Condition[i]->type == COLUMN || irequest->Condition[i]->type == LITERAL ){

                mystack.push(irequest->Condition[i]);
            }
            else{

                op = irequest->Condition[i];

                c1 = mystack.top();

                mystack.pop();

                c2 = mystack.top();

                mystack.pop();

                bool result = eval(c2, c1, op, irequest);

                condition *res = (condition *)malloc(sizeof(condition));

                if(result == true){

                    res->value = (int *)malloc(sizeof(int));

                    *(int *)res->value = 1;

                    res->type = BOOLEAN;
                }
                else{

                    res->value = (int *)malloc(sizeof(int));

                    *(int *)res->value = 0;

                    res->type = BOOLEAN;

                }

                mystack.push(res);



            }

        }

        int truth_value = *(int *)mystack.top()->value;

        if(truth_value == 1){

            return true;
        }
        else
            return false;

    }
    
    
}

bool DBOverlay::eval(condition *c1, condition *c2, condition *op, mega_struct *irequest){

    bool result = false;

    if(strcmp((char *)op->value,"=") == 0){

        if(c1->type == COLUMN && c2->type == LITERAL){

            int index = *(int *)c1->value;

            index--;
            
            if(irequest->Sattr[index]->type == INT){

                int i_literal = atoi((char*)c2->value);
                
                if(*(int *)irequest->Sattr[index]->value == i_literal){
                    
                    result =  true;
                }
                else result =  false;

            }else if(irequest->Sattr[index]->type == FLOAT){

                int f_literal = atof((char*)c2->value);
                
                if(*(float *)irequest->Sattr[index]->value == f_literal){
                    
                    result =  true;
                }
                else result = false;
            }
            else{
                if(strcmp((char*)irequest->Sattr[index]->value, (char*)c2->value) == 0){
                    result = true;
                }
                else result = false;
            }


        }

    }else if(strcmp((char *)op->value,"<") == 0){

         if(c1->type == COLUMN && c2->type == LITERAL){

            int index = *(int *)c1->value;

            index--;

            if(irequest->Sattr[index]->type == INT){

                int i_literal = atoi((char*)c2->value);

                if(*(int *)irequest->Sattr[index]->value < i_literal){

                    result = true;
                }
                else result = false;

            }else if(irequest->Sattr[index]->type == FLOAT){

                int f_literal = atof((char*)c2->value);

                if(*(float *)irequest->Sattr[index]->value < f_literal){

                    result = true;
                }
                else result = false;
            }
            else{
                if(strcmp((char*)irequest->Sattr[index]->value, (char*)c2->value) < 0){
                    result = true;
                }
                else result = false;
            }


        }

    }else if(strcmp((char *)op->value,"<=") == 0){

         if(c1->type == COLUMN && c2->type == LITERAL){

            int index = *(int *)c1->value;

            index--;

            if(irequest->Sattr[index]->type == INT){

                int i_literal = atoi((char*)c2->value);

                if(*(int *)irequest->Sattr[index]->value <= i_literal){

                    result = true;
                }
                else result =  false;

            }else if(irequest->Sattr[index]->type == FLOAT){

                int f_literal = atof((char*)c2->value);

                if(*(float *)irequest->Sattr[index]->value <= f_literal){

                    result = true;
                }
                else result = false;
            }
            else{
                if(strcmp((char*)irequest->Sattr[index]->value, (char*)c2->value) <= 0){
                    result = true;
                }
                else result = false;
            }


        }

    }else if(strcmp((char *)op->value,">") == 0){

         if(c1->type == COLUMN && c2->type == LITERAL){

            int index = *(int *)c1->value;

            index--;

            if(irequest->Sattr[index]->type == INT){

                int i_literal = atoi((char*)c2->value);

                if(*(int *)irequest->Sattr[index]->value > i_literal){

                    result = true;
                }
                else result = false;

            }else if(irequest->Sattr[index]->type == FLOAT){

                int f_literal = atof((char*)c2->value);

                if(*(float *)irequest->Sattr[index]->value > f_literal){

                    result = true;
                }
                else result = false;
            }
            else{
                if(strcmp((char*)irequest->Sattr[index]->value, (char*)c2->value) > 0){
                    result = true;
                }
                else result = false;
            }


        }

    }else if(strcmp((char *)op->value,">=") == 0){

         if(c1->type == COLUMN && c2->type == LITERAL){

            int index = *(int *)c1->value;

            index--;
            
            if(irequest->Sattr[index]->type == INT){

                int i_literal = atoi((char*)c2->value);

                if(*(int *)irequest->Sattr[index]->value >= i_literal){

                    result = true;
                }
                else result = false;

            }else if(irequest->Sattr[index]->type == FLOAT){

                int f_literal = atof((char*)c2->value);

                if(*(float *)irequest->Sattr[index]->value >= f_literal){

                    result = true;
                }
                else result = false;
            }
            else{
                if(strcmp((char*)irequest->Sattr[index]->value, (char*)c2->value) >= 0){
                    result = true;
                }
                else result = false;
            }


        }

    }else if(strcmp((char *)op->value,"AND") == 0){

        if(c1->type == BOOLEAN && c2->type == BOOLEAN){

            int truth_val = (*(int*)c1->value) * (*(int*)c2->value);

            if(truth_val == 1){
                result = true;
            }
            else
                result = false;

        }

    }else if(strcmp((char *)op->value,"OR") == 0){

         if(c1->type == BOOLEAN && c2->type == BOOLEAN){

            int truth_val = (*(int*)c1->value) + (*(int*)c2->value);

            if(truth_val == 0){
                result = false;
            }
            else
                result = true;

        }

    }



    return result;
}


int DBOverlay::insert_slot(mega_struct *irequest, unsigned long space_req)
{
//    unsigned long totalsize=0, actualSize=0, space_req = 0;
//    for (int i=0; i< irequest->NumPattr ; i++)
//    {
//        totalsize = totalsize + irequest->Pattr[i].length;
//        if (irequest->Pattr[i].type == VARCHAR)
//              actualSize = actualSize + strlen((char *)irequest->Pattr[i].value);
//        else
//              actualSize = actualSize + irequest->Pattr[i].length;
//    }
//
    int total_slot_map_bytes = 0, no_of_slot_map = 0;

    no_of_slot_map = irequest->NumPattr;
    total_slot_map_bytes = no_of_slot_map * sizeof (int);

    newSlot(space_req);
    cout << "TEST:: NEW SLOT || Slot Offset: " << slotinfo->point << " || Slot size: " << slotinfo->size << endl;
    unsigned int recSize=0;

    updateDataCursor();

    initRecordCursor( no_of_slot_map );
    for( int i=0; i < irequest->NumPattr; i++)
    {
        if (irequest->Pattr[i]->type == VARCHAR)
        {
            recSize = strlen( (char*)irequest->Pattr[i]->value );
        }
        else
        {
            recSize = irequest->Pattr[i]->length;

        }

        setRecord( (char*)irequest->Pattr[i]->value, recSize);
    }



}

int DBOverlay::read_slot(long slotno, mega_struct *irequest)
{
    gotoSlot(slotno);
    updateDataCursor();

    cout << "TEST:: Slot No: " << slotno << " || Slot Offset: " << slotinfo->point << " || Slot size: " << slotinfo->size << endl;

    unsigned long totalsize=0;
    for (int i=0; i< irequest->NumPattr ; i++)
    {
        totalsize = totalsize + irequest->Pattr[i]->length;
    }

    int total_slot_map_bytes = 0, no_of_slot_map = 0;

    no_of_slot_map = irequest->NumPattr;
    total_slot_map_bytes = no_of_slot_map * sizeof (int);

    setupRecordCursor();

    for( int i=0; i < irequest->NumPattr; i++)
    {
       /* if ( irequest->Pattr[i].value != NULL )
        {
            cout << "Freeing the pointer :) " << endl;
            void *freeptr;
            freeptr = irequest->Pattr[i].value;
            free (freeptr);
            irequest->Pattr[i].value = NULL;
        }
        */
        memset(irequest->Pattr[i]->value,NULL,irequest->Pattr[i]->length);
        record retRecord;
        retRecord.dataptr = NULL;
        retRecord.size = 0;
        getRecord(irequest->Pattr[i]->ppos, &retRecord);
        //irequest->Pattr[i].value = getRecord(irequest->Pattr[i].ppos);
        memcpy(irequest->Pattr[i]->value,retRecord.dataptr,retRecord.size);
    }

    UI::PrintData(irequest);
}

 int DBOverlay::read_cur_slot(mega_struct *irequest)
 {
    updateDataCursor();
    setupRecordCursor();

    if (!checkDeleted())
    {

        for( int i=0; i < irequest->NumPattr; i++)
        {
            //irequest->Pattr[i]->value = malloc((irequest->Pattr[i]->length) * (sizeof(char)));
            memset(irequest->Pattr[i]->value,NULL,irequest->Pattr[i]->length);
            record retRecord;
            retRecord.dataptr = NULL;
            retRecord.size = 0;
            getRecord(irequest->Pattr[i]->ppos, &retRecord);
            //irequest->Pattr[i].value = getRecord(irequest->Pattr[i].ppos);
            memcpy(irequest->Pattr[i]->value,retRecord.dataptr,retRecord.size);
        }

        for( int i=0; i < irequest->NumSattr; i++)
        {
            //irequest->Pattr[i]->value = malloc((irequest->Pattr[i]->length) * (sizeof(char)));
            memset(irequest->Sattr[i]->value,NULL,irequest->Sattr[i]->length);
            record retRecord;
            retRecord.dataptr = NULL;
            retRecord.size = 0;
            getRecord(irequest->Sattr[i]->ppos, &retRecord);
            //irequest->Pattr[i].value = getRecord(irequest->Pattr[i].ppos);
            memcpy(irequest->Sattr[i]->value,retRecord.dataptr,retRecord.size);
        }

    }

 }

  int DBOverlay::selective_read_cur_slot(mega_struct *irequest)
 {
    updateDataCursor();
    setupRecordCursor();

    if (!checkDeleted())
    {

       for( int i=0; i < irequest->NumSattr; i++)
        {
            //irequest->Pattr[i]->value = malloc((irequest->Pattr[i]->length) * (sizeof(char)));
            memset(irequest->Sattr[i]->value,NULL,irequest->Sattr[i]->length);
            record retRecord;
            retRecord.dataptr = NULL;
            retRecord.size = 0;
            getRecord(irequest->Sattr[i]->ppos, &retRecord);
            //irequest->Pattr[i].value = getRecord(irequest->Pattr[i].ppos);
            memcpy(irequest->Sattr[i]->value,retRecord.dataptr,retRecord.size);
        }

    }

 }

 int DBOverlay::select_all(mega_struct *irequest)
 {
     long iter;
     
     firstSlot();

     for ( iter=1; iter<=getNumberOfSlots(); iter++ )
     {
        read_cur_slot(irequest);
        if ( !checkDeleted() )
        {
            if(evaluate_condition(irequest)){
        
            UI::PrintData(irequest);

            }
        }
        nextSlot();
     }
 }

  int DBOverlay::delete_sequential(mega_struct *irequest)
 {
     long iter;

     firstSlot();

     for ( iter=1; iter<=getNumberOfSlots(); iter++ )
     {
        //read_cur_slot(irequest);
        //if(evaluate_condition(irequest)){

            delete_cur_slot(irequest);

        //}
        nextSlot();
     }
 }
bool DBOverlay::delete_cur_slot(mega_struct* irequest)
 {
     updateDataCursor();

     /*If the current slot is not deleted then evaluate the condition and proceed to delete*/
     if ( !checkDeleted() )
     {
         if (evaluate_condition(irequest) == true)
            {
                memset(icursor, NULL, slotinfo->size);
                dbpage->_TFS = dbpage->_TFS - slotinfo->size;
                slotinfo->size = -(slotinfo->size);

                if (curSlotNo == getNumberOfSlots())
                {
                    int countDeleted;
                    countDeleted = 1;
                    prevSlot();

                    while(checkDeleted())
                    {
                        countDeleted = countDeleted + 1;
                        prevSlot();
                        decrementSlot();

                        if (getNumberOfSlots() == 0)
                            break;
                    }

                    // Update CFS after mass deletion
                    unsigned long restoredSize;
                    restoredSize = CFS_index->size;
                    if (getNumberOfSlots() > 0)
                    {
                        CFS_index->point = slotinfo->point + slotinfo->size;
                        CFS_index->size = PG_DATASIZE - CFS_index->point;
                        restoredSize = CFS_index->size - restoredSize;
                    }
                    cout << "\nTEST::Cleaned " << countDeleted << " decayed slots and restored: " << restoredSize << " bytes " << endl;

                }


                decrementSlot();


                return true;
         }
     }
     return false;
}

// bool DBOverlay::delete_cur_slot(mega_struct* irequest)
// {
//     updateDataCursor();
//
//
//     /*If the current slot is not deleted then evaluate the condition and proceed to delete*/
//     if ( !checkDeleted() )
//     {
//         if (evaluate_condition(irequest) == true)
//            {
//                memset(icursor, NULL, slotinfo->size);
//                dbpage->_TFS = dbpage->_TFS - slotinfo->size;
//                slotinfo->size = -(slotinfo->size);
//
//                if (curSlotNo == getNumberOfSlots())
//                {
//                    int countDeleted;
//                    countDeleted = 0;
//                    prevSlot();
//
//                    while(checkDeleted())
//                    {
//                        countDeleted = countDeleted + 1;
//                        prevSlot();
//                        decrementSlot();
//
//                        if (curSlotNo == 1)
//                            break;
//                    }
//
//                }
//
//
//                decrementSlot();
//
//
//                return true;
//            }
//     }
//
//     return false;
// }

 bool DBOverlay::delete_slot(long slotNumber, mega_struct *irequest)
 {
     gotoSlot(slotNumber);
     if (delete_cur_slot(irequest))
         return true;

     return false;
 }

 long DBOverlay::delete_all(mega_struct* irequest)
 {
     long count, iter;

     count = 0;
     firstSlot();
     
     for ( iter=1; iter<=getNumberOfSlots(); iter ++)
     {
         selective_read_cur_slot(irequest);
         if (delete_cur_slot(irequest))
             count++;

         nextSlot();
     }

     firstSlot();
     return count;
 }


int DBOverlay::adv_insert_slot(std::vector<vattr> irequest)
{
    unsigned long totalsize=0, space_req = 0, total_slot_map_bytes = 0, actualSize=0;
    /* totalsize stores the maximum recordlength, i.e. max size of schema
     * space_req stores the space of the map + record on disk
     * recordSize stores the size on the disk of the particular record
     */
    int bitsreq=0, no_of_slot_map = 0;

    for (int i=0; i< irequest.size() ; i++)
    {
        totalsize = totalsize + irequest[i].size;
        if (irequest[i].bool_var_size == true)
              actualSize = actualSize + strlen(irequest[i].val);
        else
              actualSize = actualSize + irequest[i].size;
    }

    bitsreq = maxNoBits(totalsize);
    
    no_of_slot_map = irequest.size();

    int packing_in_long;
    packing_in_long = sizeof(long)*8 / bitsreq;
    // Packing in long stores number of encrypted data entries in 4 bytes

    total_slot_map_bytes = (no_of_slot_map / packing_in_long) * sizeof(long);

    int residual;
    residual = no_of_slot_map % packing_in_long;

     total_slot_map_bytes = total_slot_map_bytes + ( (residual*bitsreq) / 8 );
    if ((residual*bitsreq) % 8)
        total_slot_map_bytes++;

    space_req = actualSize + total_slot_map_bytes;
    
    newSlot(space_req);
    
    long insertOffset=0, recSize=0;
    char *insertCursor;
    unsigned long *mapCursor;
    int mapOffset = 0;
    
    moveCursor(FWD_CURSOR, PSET, slotinfo->point);
    
    mapCursor = (unsigned long*)icursor;
    cout << "TEST::Initial cursor value: " << hex << *mapCursor << endl;
    insertCursor = icursor;
    insertCursor = insertCursor + total_slot_map_bytes;

    // Reset the slot map to 0 all values
    for(int i=0; i<total_slot_map_bytes; i++)
    {
        *icursor = 0;
        icursor++;
    }

     icursor = (char *)mapCursor;

    for( int i=0; i < irequest.size(); i++)
    {
        if (irequest[i].bool_var_size == true)
        {           
            recSize = strlen(irequest[i].val);
        }
        else
        {
            recSize = irequest[i].size;
            
        }

        if (mapOffset >= packing_in_long)
            {
                mapCursor++;
                mapOffset = 0;
            }


        memcpy(insertCursor, irequest[i].val, recSize);
        insertCursor = insertCursor + recSize;
        insertOffset = insertOffset + recSize;

        *mapCursor = *mapCursor + wInverseMask(insertOffset, bitsreq, mapOffset);
        cout << "\nTEST::Offset inserted: " << hex << insertOffset << endl;
        cout << "TEST::Map cursor value: " << hex << *mapCursor << endl;

        mapOffset++;

            
    }
    
}

int DBOverlay::adv_read_slot(long slotno, std::vector<vattr>& irequest){
    
    gotoSlot(slotno);
    cout << "\nTEST::Slot pointing to offset: " << slotinfo->point ;
    moveCursor(FWD_CURSOR, PSET, slotinfo->point);

    long readOffset=0, recSize=0;
    char *readCursor;
    unsigned long *mapCursor;

    readCursor = icursor;
    mapCursor = (unsigned long *)icursor;

    int map_offset = 0;

        unsigned long totalsize=0, total_slot_map_bytes = 0, actualSize=0;
    /* totalsize stores the maximum recordlength, i.e. max size of schema
     * space_req stores the space of the map + record on disk
     * recordSize stores the size on the disk of the particular record
     */

            int bitsreq=0, no_of_slot_map = 0;

    for (int i=0; i< irequest.size() ; i++)
    {
        totalsize = totalsize + irequest[i].size;
        if (irequest[i].bool_var_size == true)
              actualSize = actualSize + strlen(irequest[i].val);
        else
              actualSize = actualSize + irequest[i].size;
    }

    bitsreq = maxNoBits(totalsize);
    no_of_slot_map = irequest.size();

        int packing_in_long;
    packing_in_long = sizeof(long)*8 / bitsreq;
    // Packing in long stores number of encrypted data entries in 4 bytes

    total_slot_map_bytes = (no_of_slot_map / packing_in_long) * sizeof(long);

    int residual;
    residual = no_of_slot_map % packing_in_long;

     total_slot_map_bytes = total_slot_map_bytes + ( (residual*bitsreq) / 8 );
    if ((residual*bitsreq) % 8)
        total_slot_map_bytes++;


    readCursor = readCursor + total_slot_map_bytes;

    /*
 *     // DUMB Print
    cout << "\nDumb Print: " << endl;
    for (int j=0;j<actualSize;j++)
    {
        cout << *readCursor;
        readCursor++;
    }
    cout << endl;
*/
     for( int i=0; i < irequest.size(); i++)
    {

        if ( map_offset >= packing_in_long)
        {
            mapCursor++;
            map_offset = 0;
        }


        unsigned long map_value;
        map_value =  rInverseMask(*mapCursor, bitsreq, map_offset);
        recSize = map_value - readOffset;
        //cout << "\n Offset retrieved: " << map_value << endl;

        map_offset++;



        char *recData;
        recData = (char *)malloc(recSize*(sizeof(char)));

        memcpy(recData,readCursor,recSize);
        irequest[i].val = recData;
        readCursor = readCursor + recSize;
        readOffset = readOffset + recSize;
    }

    
}


long DBOverlay::defragment()
{
    firstSlot();

    long initCFS, finalCFS, iter;
    initCFS = getCFS();
    bool alert = false;
    unsigned long relocate_offset;
    /* alert informs whether the future undeleted slots have to be relocated*/
    for (iter = 1; iter <= getNumberOfSlots(); iter++)
    {
        relocate_offset = slotinfo->point;

        /* For undeleted slots if it does not have to be relocated, the could be relocation pointer is updated
          If it has to be relocated then the data is shifted and correspondingly the pointer is updated */
        if ( !checkDeleted() )
        {
            if (alert)
            {
                char *destptr;
                destptr = &( dbpage->_data[relocate_offset] );
                updateDataCursor();
                memcpy(destptr, icursor, slotinfo->size);
                cout << "\nRelocating the information in slot no: " << curSlotNo << " of size: " << slotinfo->size << " bytes from " << slotinfo->point << " to " << relocate_offset << endl;
                slotinfo->point = relocate_offset;
            }

            relocate_offset = slotinfo->point + slotinfo->size;
        }

        /* For deleted slots the relocation flag is set and the pointer to the deleted slot is set to the relocation offset
         *  and the size is put to zero, also CFS is updated
         */
        else
        {
            alert = true;
            slotinfo->point = relocate_offset;
            updateCFS( getCFS() - slotinfo->size );
            slotinfo->size = 0;
        }

    }

    CFS_index->point = relocate_offset;
    finalCFS = getCFS();
    // Return the defragmented space
    return (finalCFS - initCFS);
}


DBOverlay::~DBOverlay() {
}




//[sahil] This function should go under static utilities
int DBOverlay::maxNoBits(unsigned long ip)
{
	char counter=0;
        long mask = 0x80000000;
	unsigned long op;
	int i;
	for(i=1;i<=sizeof(long)*8;i++)
	{
		op = ip & mask;
		if(op)
			break;

		counter++;
		ip = ip << 1;
	}
	return ((sizeof(long)*8) - (int)(counter));
}

unsigned long DBOverlay::rInverseMask(unsigned long ip, int bits_req, int offset)
{
    unsigned long mymask = 0;
    int total_bits = sizeof(long)*8;
    ip = ip >> (total_bits - bits_req*(offset + 1));

    for (int i=0; i<bits_req; i++)
    {
        mymask = mymask + 1;
        mymask = mymask << 1;
    }
    mymask = mymask >> 1;
    //cout << "Mask created: " << mymask << endl;
    return (ip & mymask);
    
}
unsigned long DBOverlay::wInverseMask(unsigned long ip, int bits_req,int offset)
{
    // Offset is zero Index
    int total_bits = sizeof(long)*8;
    ip = ip << (total_bits - bits_req*(offset + 1) );
    return ip;
    
}
