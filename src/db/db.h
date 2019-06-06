/* 
 * File:   db.h
 * Author: anmol
 *
 * Created on 26 October, 2010, 4:04 PM
 */

#ifndef DB_H
#define	DB_H
#include "globals.h"
#include "buffer_manager.h"
//#include "SysTableOverlay.h"
#include <time.h>
#include <vector>
#include <string>

#define TYPE_LENGTH 50
#define NAME_LENGTH 50
#define DB_HEADER_PAGE 1
#define SYS_TABLE_PAGE 2
#define SYS_COLUMN_DP_PAGE 3
#define SYS_INDEX_PAGE 4
#define DB_HEADER_ID 0




extern char Current_Open_DB_Name[50];

enum PagePriority {
    DB_HEADER_PRIORITY = 0,
    SYS_TABLE_PRIORITY,
    SYS_COLUMN_PRIORITY,
    SYS_INDEX_PRIORITY,
    DP_PRIORITY,
    DB_PAGE_PRIORITY,
    INDEX_PAGE_PRIORITY
};

typedef std::vector<std::string> Strings;

typedef struct Attribute
{
    char attr_name[NAME_LENGTH];
    int length;
    int type;
    long ppos;
    void *value;
    bool IsPrimary;
    bool IsNull;
}Attribute;

typedef struct select_Condition{

    void* value;
    int type;

}condition;

typedef std::vector<Attribute*> Vattribute;

typedef std::vector<char*> Vstring;

typedef std::vector<condition*> Vcond;

typedef struct DatabaseHeaderPage
{
    char dbName[NAME_LENGTH];
    //buffer requires
    long NumPages;
    long PageSize;
    int IncrementSize;
    //db requires
    long last_systab_Page;
    long last_syscol_Page;
    long last_sysindex_Page;
    //long First_DP_Page;
    long num_tables;

}master_header;

typedef struct Record_Identifier
{
    long pageno;
    long slotno;
}RID;

typedef struct TableHeaderPage
{
    long Table_ID;
    long DP_Page_Number;
    

}table_header;

//structure for the DP page
//will have the DE entries

typedef struct DP_structure{
    long next_DP;
    long DE_number;
    long max_TFS_withinTheDP;


}dp_page;

typedef struct dbPage_header
{
    
    long _TFS;
}dbPage_header;

//stored at the bottom of the db page
typedef struct SlotDirectory
{
    long SlotID;
    long SlotSize;

}SlotDirectory;

typedef struct SlotTail
{
    long CFS;
    long no_of_slots;
    
}slot_tail;

typedef struct DE_struct{
    long page_num;
    long page_TFS;

}de_struct;

typedef struct MegaStructure{
    int NumTable;
    //Strings Table;
    char Table[NAME_LENGTH];
    long NumPattr;
    Vattribute Pattr;
    //Attribute *Pattr;
    long NumSattr;
    Vattribute Sattr;
    //Attribute *Sattr;
    Vcond Condition;
    int Relation;

}mega_struct;

typedef struct SystemTableHeader{
    long tableindex;
    long numberofTables;
}SysTableHeader;

typedef struct SystemTableEntry{
    char tablename[NAME_LENGTH];
    long TID;
    //long table_index;
    //long tableHeader;
    long first_DP_Page_Number;
    long last_DP_Page_Number;
    RID col_rid;
    int is_deleted; //1 for yes 0 for no

}sys_table_entry;

typedef struct SystemColumnHeader{
    long columnindex;
    long numberofColumns;

}SysColumnHeader;

typedef struct SystemColumnEntry{
    char column_name[NAME_LENGTH];
    long TID;
    long CID;
    //char *type;
    long length;
    long num_columns;
    char *column_type;
    long ppos;
    bool isNULL;
    char *DefaultValue;
    int is_deleted;

 }sys_column_entry;

typedef struct SystemIndex{

}sys_index;

class Database {
//private:

public:
    //static long current_table_id;
    //sql functions
    genpage *masterDBHeader;
    genpage *sysColDP;
    genpage *sysTabPage;
    genpage *sysCol_dbPage;
    genpage *sysIndexPage;
    genpage *DBPage;
    genpage *DPPage;
    genpage *tempDPPage;

    Database();
    ~Database();
    
    long Use_DB(char *_db_Name);

    int Create_DB(char *_db_Name, long _db_pages, long _page_Size);

    int Create_Table( mega_struct *mega);
    
    int DeleteTable(mega_struct *mega);

    int Insert_Table(mega_struct *mega);

    int Bulk_Insert_Table(mega_struct *mega);

    int Select_Table(mega_struct *mega);

    int Filter_select_Table(mega_struct *mega);

    int Delete_DB(char *_db_Name);

    int Delete_from_Table(mega_struct *mega);

    int Describe_Table(mega_struct *mega);
    
    //page templates
    int Create_TableHeader_Page(genpage *page);



    //view functions
    int ShowDBPage();

    int ShowDatabases();

    int ShowHeaderPage();

    int ShowSysTable();

    int ShowSysColumn();

    int ShowSysIndex();
    
    int ShowDPPage();

    
    

    //int Delete_DB(char *_db_Name);

};

//extern long Database::current_table_id;





#endif	/* DB_H */

