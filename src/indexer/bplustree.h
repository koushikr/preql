/*
 * File:   bplustree.h
 * Author: koushik
 *
 * Created on 17 September, 2010, 8:34 PM
 */

#include "includefiles.h"

using namespace std;

#ifndef _BPLUSTREE_H
#define	_BPLUSTREE_H

extern char dbname[10];

class genpageclass{
public:
    buffer_manager *bm;

    genpageclass(char *data_in_page);
    virtual ~genpageclass();

    long getPageNumber(); // get the PageNumber of the current page
    //int getPrevPageNumber(); // get the Previous Page Number
    //int getNextPageNumber(); // get the Next Page Number
    void setPageNumber(long PageNumber); // set the current pageNumber to the given pageNumber
    //void setPrevPageNumber(int PageNumber); // set the previous pageNumber to the given pageNumber
    //void setNextPageNumber(int PageNumber); // set the next pageNumber to the given pageNumber

    //int getPageType(); // get the type of the Page
    //void setPageType(int pageType); // set the type of the Page..


    long getPriority();
    void setPriority(long priority);

    long getTFS();
    void setTFS(long TFS); // TFS is total free space

    char getData();
    void setData(char data);

    int getnextpagenumber();
    void setnextpagenumber(long next_page_number);

//    std::string convertingrawdatatostring();
    /* To read into a string directly is difficult, there will be whitespaces line breaks and stuff
     * So to read into some string and access that string instead of directly accessing the members
     * the above function has defined
     */

    genpage gph; // A gph variable, which will contain the page type and stuff
    char *indexhdrdata; // This will contain pagedata
   // byte b;

    void genpageHeaderPrinttoString();
};


class indexheaderclass{
public:
    indexheaderclass();
    buffer_manager *bm;
    void openindexheaderpage(int indexheaderclassnumber);
    virtual ~indexheaderclass();

    //initializebuffermanager();
    /*
     * This will create New header page and initialize it with
     * 1. Number of Colums
     * 2. Column Types(ARRAY)
     * 3. COLUMN SIZES(ARRAY)
     * 4. TOTAL KEY SIZE
     */
    int createindexheaderclass(int indexattributecount, int keyformats[], int keysizes[]);
    // The above one is the only API I give to you.. to create an indexheader...

        int getpagenumberofroot();
        int getfanoutoftree();

    	int getleafcountmax();
	void setleafcountmax(int leafcountmaxrecords);
	int gettreeheight();

	void setpagenumberofroot(int pageno);
	void settreeheight(int treeheight);
	int getPageNumber();
	void setfanoutoftree(int fanout);

	int getcolcount();
        void setcolcount(int newcolcount);

	int getsizeofkey();
	void setsizeofkey(int newsize); // Not of much use this function..

	int getNumberOfKeys();
	void setNumberOfKeys(int numberOfKeys);

        // UI testing
        void indexheaderclassUserInterface();

	int *colformat; // gives me the type of cols..
	int *sizeofcols;

        // Buffer Objects for temp access

//        Buffer_Pool buffpool;
//        buffer_manager buff;

        void setTFS(int TFS, int pageNumber);
        void coldumpfirst();
        void indexheadertoString();

    typedef struct indexhdr{
        genpage gph;
        int rootpage; // rootpage from where the tree starts to be built.
        int indexnodefanout; // fanout of the tree and would be calculated dynamically
        int treeheight; // height of the tree
        int leafnodefanout; // This would identify the maximum number of records that you can have in the leaf.. identical to leaf's fanout..
        int keysize; // total size of the key
        int keycount; // Total number of keys in this tree..
        int colcount; // total number of cols on which I'm indexing..
    } indexstr;
    char *indexheaderdata;
    // Create an instance of indexstr
    indexstr indexhdrstr;
};

class IndexNode{
public:
    buffer_manager *bm;
    typedef struct indnode{
        genpage gphStruct;
        int leftpagevalue;
        int rightpagevalue;
        int noOfKeys;
        int level;
        int parentpagevalue;
        int indexheaderclasspageNumber;
    }indexnodestr;
    indexnodestr indexnodehdrstr;
    indexheaderclass *indexhdr;
    char *indexnodedata;

    IndexNode();
    void openIndexNode(int indexpagevalue);
    void openindexnodewithindexheader(indexheaderclass *indexheaderclass, int indexpagevalue);
    int getindexheaderclassNumber();

    static int getIndexNodeHeaderSize();
    int createnewindexNode(indexheaderclass *indexheaderclass_);
    int insertinindex(const char *key, int leftpagevalue, int rightpagevalue);
    void insertinindexfirst(const char* key, int leftpagevalue);
    void insertinindexlast(const char* key, int leftpagevalue);

    int searchinindex(const char *key); // Will return the right page number

    int getIndexNodeLevel();
    void setIndexNodeLevel(int level);

    int getParentofIndexNode();
    void setParentofIndexNode(int parentpagevalue);

    int getNoOfKeysInIndexNode();
    void setNoOfKeysInIndexNode(int noOfKeys);

    int getleftpagevalueOfIndexNode();
    void setleftpagevalueOfIndexNode(int leftpagevalue);

    int getrightpagevalueOfIndexNode();
    void setrightpagevalueOfIndexNode(int rightpagevalue);

    int getPageNumber();

    void keyshift(const char* oldKey, const char* newKey);
    int editkeybeforepagenumber(int pageNumber, const char *oldKey, const char *newKey);

    int getleftandrightpagevaluestothegivenpagenumber(int pageNumber, int &leftSibling, int &rightSibling);

    int deleteinindexwithflagset(const char *key, int deleteflag, std::vector <int> &deletedPages);

    void keyaftergivenpagenumber(int pageNumber, char* key);
    void keybeforegivenpagenumber(int pageNumber, char* key);

    void removethekeyatthefrontofindexnode();
    void removethekeyattheendofindexnode();

    void getthekeyatthefrontofindexnode(char *key); // that key value will be stored in Key
    void getthekeyattheendofindexnode(char *key); // that key value will be stored in key

    void getpagenumberbetweenleftpageandrightpage(int leftPage, int rightPage, char* key);

    int indexnodefirstpage();
    int indexnodelastpage();

    void getallpagenumbersunderindexnode(std::vector<int> &pagenumbers);

    // It will get the set of all leafpages into the leafpage vector
    void getleafset(std::vector<int> &leafPages);

    void getindexandleafpages(std::vector<int> &leafPages, std::vector<int> &indexPages);

    int createflag;

    virtual ~IndexNode();

    // IndexNode print functions

    void printindex();
    void indexNodeToString();
};

class LeafNode{
public:
    buffer_manager *bm;
    LeafNode();
    LeafNode(int LeafPageNumber);
    int getindexheaderclasspagenumber();
    LeafNode(indexheaderclass *indexheaderclass, int leafPageNumber);
    virtual ~LeafNode();

    int createnewleafnode(indexheaderclass *indexheaderclass_);
    int insertinleaf(const char *key, RID rid);

    int searchinleafkeyonly(const char *key); // O on success.. 1 on failure..
    int searchinleaf(const char *key, RID rid); // 0 in success ...1 on failure..2 if same key found but different rid..

    int deleteinleaf(const char *key, RID givenRid, std::vector<int> &deletedPages);

    void getKey(int keyNumber, char* key1);
    void getKeyAndRID(int keyNumber, char* key1, RID &rid);

    int keyComponly(char *key1, char *key2);

    int getLevelofNode();
    void setLevelofNode(int level);

    int getparentpagevalue();
    void setparentpagevalue(int parentpagevalue);

    int getNoOfRecordsInNode();
    void setNoOfRecordsInNode(int noOfRecords);

    int getrightpagevalue();
    void setrightpagevalue(int rightpagevalue);

    int getLeftPageNumber();
    void setleftpagevalue(int leftpagevalue);

    int compareRIDs(RID rid1, RID rid2); // Return 0 on same rids.. 1 otherwise..
    int getPageNumber();

    void getFirstKey(char *FirstKey, RID &rid);
    void getFirstKey(char *Firstkey);
    void getLastKey(char *LastKey, RID &rid);

    void getFirstKeyOnly(char *fkey);
    void getParentkey(char *pkey);

    int searchKeyInLeafNode(const char *key, std::vector<RID> &RIDvector);

    int searchkeyinLeafNodewithOperator(const char *key, int operatorvalue, std::vector<RID> &RIDVector, std::vector<string> &KeyVector);


    int keyandridinbetweenkeys(const char* firstKey,const char* secondKey,std::vector<RID> &RIDVector,std::vector<string> &keyVector);
    void getridkeysets(std::vector<RID> &RIDVector,std::vector<string> &keyVector);

    static int getLeafNodeHeaderSize();
    int createflag;

    // print Functions

    void print();
    void printleafnode();
    void printkeyat(int keyposition);

    void leafNodetoString();

typedef struct lfnode{
        genpage gph;
        int leftpagevalue;
        int rightpagevalue;
        int level;
        int noOfRecords;
        int parentpagevalue;
        int indexheaderclassNumber;
    } leafnodestr;
    leafnodestr leafnodehdrstr;
    indexheaderclass *indexhdr;
    char *leafnodedata;
};

class BplusTree{
public:
    buffer_manager *bm;
    BplusTree();

    virtual ~BplusTree();

    static int keyComp(const char* key1, const char* key2, int colcnt, indexheaderclass *indexHeader_);
    static void printKey(const char* key, indexheaderclass *indexheaderclass_);

    int searchInBplusTree(const char *key); // Gives the starting page number with this key. z

    // ==================================================================================================
    // ===================================BPLUS APIs=====================================================
    // ==================================================================================================

    void initIndex(int indexheaderclassNumber); // Opens the required index with rootpagenumber as indexheaderclassnumber
    int insertIntoBplusTree(const char *key, RID &rid); // Insert Key into bplustree
    int deleteFromBplusTree(const char *key, RID &rid); // Delete key from bplustree

    int searchKeyInBPlusTree(const char* key, std::vector<RID> &RIDVector); // Given a key get the rids only in that leaf node corresponding to the key..

    void deleteIndex(int indexPageNumber); // To drop the index


   	 // Get all the rids and keys in the leaf nodes..
    void getRIDS(std::vector<RID> &RIDVector,std::vector<string> &keyVector);

    // =====================================================================================================
    // ==============================================End of Normal APIs=====================================
    //======================================================================================================


    // Range Insert Functions.. basically used for testing the treee.. The following functions are completely fpr testing purposes..
    // Functions for Range Operations.. .

    // Given a leafpagenumber and range.. it searches for the RIDs and keys in that range..



   // Get the keyrid range in the specific range specified by key1 and key2..
    void bplusSearchRangeKeyInLeafNode(int leafPageNumber,
			const char* key1, const char* key2,
			std::vector<RID> &RIDVector, std::vector<string> &keyVector);


    // Given a key, it gets all RIDs corresponding to that key..
    int searchKeyInBPlusTreeallRIDs(const char* key, std::vector<RID>& RIDVector);

     void getKEYRIDRange(int startLeafPage, const char* totalKey1,
		const char* totalKey2, std::vector<RID> &RIDVector, std::vector<
				string> &keyVector);

    // SAme as above range search but it's with an operator
    // 1 for equal to operator
    // 2 for greater than..
    // 3 for greater than equal to
    // 4 for less than
    // 5 for less than or equal to..
    void bplusSearchRangeKeyInLeafNodewithOperator(int leafPageNumber,
			const char* keyvalue, int operatorvalue,
			std::vector<RID> &RIDVector, std::vector<string> &keyVector);


    void rangecheckfunctionforint(int range1, int range2, int incrementfactor);
    void rangecheckfunctionforfloat(float range1, float range2, float incrementfactor);
    void rangecheckfunctionfordouble(double range1, double range2, double incrementfactor);
    void rangecheckfunctionforlong(long range1, long range2, long incrementfactor);
    void rangedumpinsertfunction(int totkeycount);

    // Delete Range Functions..basically used for testing the tree..

    void rangedeletecheckforint(int range1, int range2);
    void rangedeletecheckforfloat(float range1, float range2);
    void rangedeletecheckfordouble(double range1, double range2);
    void rangedeletecheckforlong(long range1, long range2);

    // Functions for UI print..

    int checkifthegivenpagenumberispresentintheindexpage(std::vector<int> indexPageVector,int PageNumber);
    int checkifthegivenpagenumberispresentintheleafpage (std::vector<int> leafPageVector, int PageNumber);

    // Core print functions

    int print();
    void mainprintbplustree(int indexheaderclassNumber);
    void printindleaf();
    /*For this the following four functions have to be implemented*/
    void printindex(int pageno);
    void printleaf(int pageno);
    void getLeafandIndexPages(std::vector<int> &leafPages,
			std::vector<int> &indexPages);
    //=============================End of two stubs that are required for indexnode/leafnode

    void mainfunctionforinsertrecord();
    void mainfunctionofinsertrecordforarange();
    void mainfunctionfordeleterecord();
    void mainfunctionfordeleterecordinarange();
    void mainfunctionforsearchrecord();
    void mainfunctionforrangesearchrecord();
    void fanoutprint();


indexheaderclass *bplustreeindexhdrclassptr;

};




#endif	/* _BPLUSTREE_H */
