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

#include "bplustree.h"

char dbname[10];


using namespace std;

// #########################################################################################################
// ################################## All getter setter methods go here####################################
// ########################################################################################################

long genpageclass::getPageNumber(){
    return gph._page_number;
}

long genpageclass::getPriority(){
    return gph._priority;
}

long genpageclass::getTFS(){
    return gph._TFS;
}

void genpageclass::setPageNumber(long PageNumber){
    gph._page_number=PageNumber;
    memcpy(indexhdrdata,&gph,sizeof(genpage));
}

void genpageclass::setPriority(long priority){
   gph._priority=priority;
    memcpy(indexhdrdata,&gph,sizeof(genpage));
}

void genpageclass::setTFS(long TFS){
    gph._TFS=TFS;
    memcpy(indexhdrdata,&gph,sizeof(genpage));
}

int genpageclass::getnextpagenumber(){
    int pageno =(int) (gph._next_page);
    return pageno;
}

void genpageclass::setnextpagenumber(long next_page_number){
    gph._next_page = next_page_number;
        memcpy(indexhdrdata,&gph,sizeof(genpage));
}


// Indexheader getter setters

int indexheaderclass::getleafcountmax(){
   //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.leafnodefanout;
}

void indexheaderclass::setleafcountmax(int maxNoOfRecordsInLeaf){
    indexhdrstr.leafnodefanout=maxNoOfRecordsInLeaf;
    memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
}

int indexheaderclass::getpagenumberofroot(){
  //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.rootpage;
}

int indexheaderclass::getfanoutoftree(){
   //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.indexnodefanout;
}

int indexheaderclass::gettreeheight(){
   //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.treeheight;
}

int indexheaderclass::getNumberOfKeys(){
   //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.keycount;
}

void indexheaderclass::setNumberOfKeys(int numberOfKeys){
    indexhdrstr.keycount=numberOfKeys;
    memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
}

void indexheaderclass::settreeheight(int treeheight){
    indexhdrstr.treeheight=treeheight;
    memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
}

void indexheaderclass::setpagenumberofroot(int pageno){
    indexhdrstr.rootpage=pageno;
    memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
}

int indexheaderclass::getPageNumber(){
   //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.gph._page_number;
}

void indexheaderclass::setfanoutoftree(int fanout){
    indexhdrstr.indexnodefanout=fanout;
    memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
}

int indexheaderclass::getcolcount(){
    //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.colcount;
}

int indexheaderclass::getsizeofkey(){
    //memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    return indexhdrstr.keysize;
}

void indexheaderclass::setsizeofkey(int newsize){
   indexhdrstr.keysize = newsize;
   memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
}

void indexheaderclass::setcolcount(int newcolcount){
    indexhdrstr.colcount=newcolcount;
    memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
}

// IndexNode getter setters

int IndexNode::getIndexNodeHeaderSize(){
    return sizeof(indexnodestr);
}

int IndexNode::getIndexNodeLevel(){
   // memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
    return indexnodehdrstr.level;
}

void IndexNode::setIndexNodeLevel(int level){
    indexnodehdrstr.level=level;
    memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
}

int IndexNode::getNoOfKeysInIndexNode(){
   //memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
    return indexnodehdrstr.noOfKeys;
}

void IndexNode::setNoOfKeysInIndexNode(int noOfKeys){
    indexnodehdrstr.noOfKeys=noOfKeys;
    memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
}

int IndexNode::getParentofIndexNode(){
    //memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
    return indexnodehdrstr.parentpagevalue;
}

void IndexNode::setParentofIndexNode(int parentpagevalue){
    indexnodehdrstr.parentpagevalue=parentpagevalue;
    memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
}

int IndexNode::getleftpagevalueOfIndexNode(){
    //memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
    return indexnodehdrstr.leftpagevalue;
}

void IndexNode::setleftpagevalueOfIndexNode(int leftpagevalue){
    indexnodehdrstr.leftpagevalue=leftpagevalue;
    memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
}

int IndexNode::getrightpagevalueOfIndexNode(){
    //memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
    return indexnodehdrstr.rightpagevalue;
}

void IndexNode::setrightpagevalueOfIndexNode(int rightpagevalue){
    indexnodehdrstr.rightpagevalue=rightpagevalue;
    memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
}

int IndexNode::getPageNumber(){
    //memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
    return indexnodehdrstr.gphStruct._page_number;
}

// Leafnode getters/setters
int LeafNode::getLeafNodeHeaderSize(){
    return sizeof(leafnodestr);
}

int LeafNode::getindexheaderclasspagenumber(){
    //memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    return leafnodehdrstr.indexheaderclassNumber;
}

int LeafNode::getPageNumber(){
    //memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    return leafnodehdrstr.gph._page_number;
}

int LeafNode::getLevelofNode(){
    //memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    return leafnodehdrstr.level;
}

void LeafNode::setLevelofNode(int level){
    leafnodehdrstr.level=level;
    memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
}

int LeafNode::getNoOfRecordsInNode(){
    //memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    return leafnodehdrstr.noOfRecords;
}

void LeafNode::setNoOfRecordsInNode(int noOfRecords){
    leafnodehdrstr.noOfRecords=noOfRecords;
    memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
}

int LeafNode::getparentpagevalue(){
    //memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    return leafnodehdrstr.parentpagevalue;
}

int LeafNode::getLeftPageNumber(){
    //memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    return leafnodehdrstr.leftpagevalue;
}

int LeafNode::getrightpagevalue(){
    //memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    return leafnodehdrstr.rightpagevalue;
}

void LeafNode::setparentpagevalue(int parentpagevalue){
    leafnodehdrstr.parentpagevalue=parentpagevalue;
    memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
}

void LeafNode::setleftpagevalue(int leftpagevalue){
    leafnodehdrstr.leftpagevalue=leftpagevalue;
    memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
}

void LeafNode::setrightpagevalue(int rightpagevalue){
    leafnodehdrstr.rightpagevalue=rightpagevalue;
    memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
}
//###########################################################################################################
//######################################End of Getters/Setters###############################################
//###########################################################################################################



// ##############################################################################################

// ################################## Functions to Access the General Page Header################################
//#################################################################################################

genpageclass::genpageclass(char* data_in_page){
    indexhdrdata=data_in_page;
   // memcpy(&gph,indexhdrdata,sizeof(gphStruct));
    memcpy(&gph, indexhdrdata, sizeof(genpage));
}

genpageclass::~genpageclass(){
    // Destructor by default..
    // Nothing needs to be done for the moment!
}


//
//genpageclass::getPageType(){
//    return gph.pageType;
//}
//
//void genpageclass::setPageNumber(int PageNumber)
//{
//    gph.PageNumber=PageNumber;
//    memcpy(indexhdrdata,&gph,sizeof(gphStruct));
//}
//
//void genpageclass::setNextPageNumber(int PageNumber){
//    gph.nextPageNumber=PageNumber;
//    memcpy(indexhdrdata,&gph,sizeof(gphStruct));
//}
//
//void genpageclass::setPageType(int pageType){
//    gph.pageType=pageType;
//    memcpy(indexhdrdata,&gph,sizeof(gphStruct));
//}


//################################################################################
// ################################### General Page Header Functions Done#####################3
//##################################################################################################


// ========================================================================================================
//==========================================================================================================


//################################################################################
// ################################### Functions to Access IndexHeader Page Detials#####################3
//##################################################################################################


indexheaderclass::indexheaderclass(){
    //Default Constructor Calling..
        //buff = new buffer_manager();
//    long sampleSize =200;
  //      Buffer_Pool::InitBuffer(sampleSize);
    bm = new buffer_manager();
}


void indexheaderclass::openindexheaderpage(int indexheaderclassnumber){
    cout<<"Opening Index Header Page with Pagenumber:"<< indexheaderclassnumber;

        //buff = new buffer_manager();
    //long sampleSize =200;
     //Buffer_Pool::InitBuffer(sampleSize);
     //buffer_manager buff1;
    //buff.InitBuffer(200); //Instance of buffer manager and initializing it!

    // pagegeneral *pdata=buff.BufferWrite("dbname",indexheaderclassnumber);

    genpage *pdata=bm->BufferWrite(dbname,indexheaderclassnumber);
    indexheaderdata=(char *)pdata;


    // Now reading this page into the frame table along with the data in the page
    //buffermanager->ReadPage("dbname", indexheaderclassnumber);
    // In the above function the value in data has to be read into the variable indexhdrdata // Have to check with Sahil, this!
    // Also pass indexnodedata to it.. this page has to be read..
    // Once the data is read into indexnodedata then the indexnodedata structure should be read into the indexstructure in memory

    memcpy(&indexhdrstr, indexheaderdata, sizeof(indexstr));

    // The above thing will copy the indexnodedata into the indexHeader variable..
    coldumpfirst();
    //bufferspecific code=============
    //bm->ReleasePage(dbname,getPageNumber());
    ////bm->Commit(dbname,getPageNumber());
}

indexheaderclass::~indexheaderclass(){
    // The destructor .. A page has to be unpinned here... Have to talk to Sahil abotut this, tonight!
   // buffer_manager buffmanager = new buffer_manager();
   // I need an instance from the buffer manager to call the release page..
    bm->ReleasePage(dbname,indexhdrstr.gph._page_number);
    //bm->Commit(dbname,indexhdrstr.gph._page_number);
}

int indexheaderclass::createindexheaderclass(int indexattributecount, int keyformats[], int keysizes[]){
    // Get a free page from the buffer Manager..
    // Once you get a freepage from the buffer, then fill use the arguments to fill up the structure elements
    // and write it back onto the page..

   // buffmanager.InitBuffer(200); //Instance of buffer manager and initializing it!
   //buffer_manager *buff=new buffer_manager();
    int keySize = 0;
    for(int keycounter=0; keycounter < indexattributecount; keycounter++){
        keySize = keySize + keysizes[keycounter];
    }
    int indexheaderpagenumber=0;
    
    genpage *pdata=bm->GetFreePage(dbname);
    indexheaderdata=(char *)pdata;

    memcpy(&indexhdrstr,indexheaderdata,sizeof(indexstr));
    // This memcpy actually copies the pagenumber and tfs into the header structure.. no need to change it..
    int currentPageSizeunderUse= PAGESIZE;

    /*If required the priority could be changed.. */
    indexhdrstr.gph._priority=TYPE_INDEX_HEADER_PAGE; // Might have to be assigned and reassigned later..
    indexhdrstr.keysize=keySize;
    int maxrecordcount = (int) floor((currentPageSizeunderUse - (LeafNode::getLeafNodeHeaderSize()))/ (double) (keySize+RIDSIZE)); // RID_LENGTH IS RIDSIZE

    indexhdrstr.leafnodefanout= maxrecordcount;

    int calfanout = (int) floor((currentPageSizeunderUse - (IndexNode::getIndexNodeHeaderSize()))/ (double)(keySize+4));
    indexhdrstr.indexnodefanout= calfanout;

    indexhdrstr.rootpage=-1; // The root page number should change on the first insert.. Initially, it shall be -1
    indexhdrstr.treeheight=0;
    indexhdrstr.keycount=0;
    indexhdrstr.colcount=indexattributecount;
    indexheaderpagenumber = indexhdrstr.gph._page_number;
    //memcpy(pdata->_data,&indexhdr,sizeof(indexstr));
    memcpy(indexheaderdata,&indexhdrstr,sizeof(indexstr));
    int position=sizeof(indexstr);

    for(int i=0; i<indexattributecount; i++){
        //memcpy(&pdata->_data[position],  &keyformats[i], sizeof(int));
        memcpy(&indexheaderdata[position],&keyformats[i],sizeof(int));
        position=position+sizeof(int);
    }

    for(int i=0; i<indexattributecount; i++){
       // memcpy(&pdata->_data[position],  &keysizes[i], sizeof(int));
        memcpy(&indexheaderdata[position],&keysizes[i],sizeof(int));
        position=position+sizeof(int);
    }
    int dummyTFS=PAGESIZE-position;
    indexhdrstr.gph._TFS=dummyTFS;
    //memcpy(pdata->_data,&indexhdr,sizeof(indexhdr));

//dupl tester for 1st stage execution===============
    //buff.Commit(dbname,indexhdr.gph._page_number);
    //buff.ReleasePage(dbname,indexhdr.gph._page_number);

    // Setting the TFS variable..
   // setTFS(dummyTFS,indexhdr.gph._page_number);
    //===================================
    //duplcoldumpfirst(indexhdr.gph._page_number);
    coldumpfirst();
    //bm->ReleasePage(dbname,getPageNumber());
    ////bm->Commit(dbname,getPageNumber());
    return indexheaderpagenumber;
}

/*void indexheaderclass::setTFS(int TFS, int pageNumber){
    buffer_manager *buff=new buffer_manager();
    genpage *pdata=buff->WritePage(dbname,pageNumber);
    indexhdr.gph._TFS=TFS;
    memcpy(pdata->_data,&indexhdr,sizeof(indexhdr));
    memcpy(indexheaderdata,&indexhdr,sizeof(indexhdr));
    buff->ReleasePage(dbname,pageNumber);
    buff->Commit(dbname, pageNumber);
}*/

void indexheaderclass::coldumpfirst(){
    int position=sizeof(indexstr);

    colformat=new int[indexhdrstr.colcount];

    cout<<"No of Columns"<<indexhdrstr.colcount;
    cout<<"position"<<position;

    for (int i=0; i<indexhdrstr.colcount; i++){
        memcpy(&colformat[i],&indexheaderdata[position],sizeof(int));
        position=position+sizeof(int);
    }

    sizeofcols=new int[indexhdrstr.colcount];
    cout<<"No of Columns"<<indexhdrstr.colcount;

    for(int i=0; i<indexhdrstr.colcount;i++){
        memcpy(&sizeofcols[i],&indexheaderdata[position],sizeof(int));
        position=position+sizeof(int);
    }

}
/*
//duplorary coldumpfirst function
void indexheaderclass::duplcoldumpfirst(int pageNumber){
    buffer_manager *buff=new buffer_manager();
    genpage *pdata=buff.BufferWrite(dbname,pageNumber);
    indexheaderdata=pdata->_data;
    int position=sizeof(indexstr);
    colformat=new int[indexhdr.numberOfColumns];

    cout<<"No of Columns"<<indexhdr.numberOfColumns;
    cout<<"position"<<position;

    for (int i=0; i<indexhdr.numberOfColumns; i++){
        memcpy(&colformat[i],&indexheaderdata[position],sizeof(int));
        position=position+sizeof(int);
    }

    sizeofcols=new int[indexhdr.numberOfColumns];
    cout<<"No of Columns"<<indexhdr.numberOfColumns;

    for(int i=0; i<indexhdr.numberOfColumns;i++){
        memcpy(&sizeofcols[i],&indexheaderdata[position],sizeof(int));
        position=position+sizeof(int);
    }
    buff.ReleasePage(dbname,pageNumber);
}*/


// UI for testing..

void indexheaderclass::indexheaderclassUserInterface(){
    cout << "\n\tIndex Header Page User Interface"<<endl;
    cout<<"\n--------------------------------------"<<endl;

    cout <<"\tIndex Header Page Number is  --- "<<getPageNumber()
            <<endl;

    cout <<"\tRoot Page Number is --- "<<getpagenumberofroot()
            <<endl;

    cout <<"\t IndexNode fanout is --- " <<getfanoutoftree()
            <<endl;

    cout <<"\t Leaf Node Fanout is! --- " << getleafcountmax()
            <<endl;

    cout <<"\t Height of the tree --- "<<gettreeheight()
            <<endl;

   cout <<"\t Number of Columns in Index --- " <<getcolcount()
            <<endl;

   cout<<"\t Key Size is --- " <<getsizeofkey()
          <<endl;

   cout <<"\t Number of Keys are -- " <<getNumberOfKeys()
            <<endl;

/*
    for(int i=0; i<getcolcount(); i++){
        char columntype[10];
        memset(columntype,'\0',10);

        switch(colformat[i]){
            case 1: // 1 for integer
                memcpy(columntype, "INTEGER", sizeof("INTEGER"));
                break;
            case 2: // 2 for float
                memcpy(columntype,"FLOAT",sizeof("FLOAT"));
                break;
            case 3: // 3 for double
                memcpy(columntype, "DOUBLE", sizeof("DOUBLE"));
                break;
            case 4: // 4 for long
                memcpy(columntype, "LONG", sizeof("LONG"));
                break;
            case 5: // 5 for varchar
                memcpy(columntype, "VARCHAR", sizeof("VARCHAR"));
                break;
        }
        cout << "\t Column Types [field"<<i + 1 << "]=========="
                <<columntype<<endl; */

        cout << "\t ----------------------------------------------END INDEXHEADER"<<endl;
 //   }
}


//################################################################################
// ###################################End of Index Header Page#####################3
//##################################################################################################


//###################################################################################################################
// ###################################Dummy Functions for Bplustree - Junk function section#####################
//##################################################################################################

int BplusTree::keyComp(const char* key1, const char* key2, int colcnt, indexheaderclass *indexHeader) {
	int position = 0;
	int intKey1 = 0, intKey2 = 0;
	long longKey1 = 0, longKey2 = 0;
	float floatKey1 = 0.0, floatKey2 = 0.0, diff = 0.0;
	double doubleKey1 = 0.0, doubleKey2 = 0.0, ddiff = 0.0;

	for (int i = 0; i < colcnt; i++) {
		int colType = indexHeader->colformat[i];
                int colSize = indexHeader->sizeofcols[i];
		switch (colType) {
		case KEY_IS_INT:
			//			cout << "\nINTEGER TYPE" << endl;
			memcpy(&intKey1, &key1[position], 4);
			memcpy(&intKey2, &key2[position], 4);
			if (intKey1 > intKey2) {
				return HIT_RETURN;
			} else if (intKey1 < intKey2) {
				return -1;
			}
			break;
		case KEY_IS_FLOAT:
			//			cout << "\nFLOAT TYPE" << endl;
			memcpy(&floatKey1, &key1[position], sizeof(float));
			memcpy(&floatKey2, &key2[position], sizeof(float));
                        if(floatKey1 > floatKey2){
                            return HIT_RETURN;
                        }
                        else if(floatKey1 < floatKey2){
                            return -1;
                        }
                        break;
                        
		case KEY_IS_DOUBLE:
			//			cout << "\nDOUBLE TYPE" << endl;
			memcpy(&doubleKey1, &key1[position], sizeof(double));
			memcpy(&doubleKey2, &key2[position], sizeof(double));
			if (doubleKey1 > doubleKey2) {
				return HIT_RETURN;
			} else if (doubleKey1 < doubleKey2) {
				return -1;
			}
			break;
		case KEY_IS_LONG:
			memcpy(&longKey1, &key1[position], sizeof(long));
			memcpy(&longKey2, &key2[position], sizeof(long));
			if (longKey1 > longKey2) {
				return HIT_RETURN;
			} else if (longKey1 < longKey2) {
				return -1;
			}
			break;
		case KEY_IS_VARCHAR:
			//			cout << "\nVARCHAR TYPE" << endl;
			if (strncmp(&key1[position], &key2[position],indexHeader->sizeofcols[i]) > 0) {
				return HIT_RETURN;
			} else if (strncmp(&key1[position], &key2[position],indexHeader->sizeofcols[i]) < 0) {
				return -1;
			}
			break;

		default:
			//			cout << "DEFAULT IS VARCHAR TYPE" << endl;
			if (strncmp(&key1[position], &key2[position],
					indexHeader->sizeofcols[i]) > 0) {
				return HIT_RETURN;
			} else if (strncmp(&key1[position], &key2[position], indexHeader->sizeofcols[i]) < 0) {
				return -1;
			}
                        break;
	}
                position = position + indexHeader->sizeofcols[i];
    }
   return PHAT_RETURN;
}

void BplusTree::printKey(const char *key, indexheaderclass* bplustreeindexhdrclassptr){
	int indexattributecount = bplustreeindexhdrclassptr->getcolcount();
	int position = 0;
	for (int i = 0; i < indexattributecount; i++) {
		int colType = bplustreeindexhdrclassptr->colformat[i];
		int intKey;
		float floatKey;
		double doubleKey;
		long longKey;
                int vcs = bplustreeindexhdrclassptr->sizeofcols[i];
		char vc1[vcs];
		char vc2[vcs];
		switch (colType) {
		case KEY_IS_INT: //1 for int
			memcpy(&intKey, &key[position], sizeof(int));
			cout << intKey;
			break;
		case KEY_IS_FLOAT: // 2 for float
			memcpy(&floatKey, &key[position], sizeof(float));
			cout << floatKey;
			break;
		case KEY_IS_DOUBLE: // 3 for double
			memcpy(&doubleKey, &key[position], sizeof(double));
			cout << doubleKey;
			break;
		case KEY_IS_LONG: // 4 for long
			memcpy(&longKey, &key[position], sizeof(long));
			cout << longKey;
			break;
		case KEY_IS_VARCHAR:
			memcpy(vc1, &key[position], vcs);
			cout << vc1;
			break;
		default:
			memcpy(vc2, &key[position],vcs);
			cout << vc2;
			break;
		}
		position = position + vcs;
	}
}
// IndexNode dummy functions........#################################################################################
//#################################################################################################################

void IndexNode::getthekeyatthefrontofindexnode(char* key){
    int position=IndexNode::getIndexNodeHeaderSize();
    position=position+sizeof(int);
    memcpy(key,&indexnodedata[position],indexhdr->getsizeofkey());
}

void IndexNode::getthekeyattheendofindexnode(char* key){
    int position=IndexNode::getIndexNodeHeaderSize();
    position=position+ (getNoOfKeysInIndexNode() * (sizeof(int) + indexhdr->getsizeofkey()));
    position=position - indexhdr->getsizeofkey();
    memcpy(key,&indexnodedata[position],indexhdr->getsizeofkey());
}

int IndexNode::indexnodefirstpage(){
    int position=IndexNode::getIndexNodeHeaderSize();
    int numberOfthePage;
    memcpy(&numberOfthePage,&indexnodedata[position],sizeof(int));
    return numberOfthePage;
}

int IndexNode::indexnodelastpage(){
    int position=IndexNode::getIndexNodeHeaderSize();
    position=position+ (getNoOfKeysInIndexNode() * (sizeof(int) + indexhdr->getsizeofkey()));
    int numberOfPage;
    memcpy(&numberOfPage,&indexnodedata[position],sizeof(int));
    return numberOfPage;
}

void IndexNode::keyaftergivenpagenumber(int pageNumber, char* key){
    int position=IndexNode::getIndexNodeHeaderSize();
    int pageNumberdup;
    char list[indexhdr->getsizeofkey()];
    int count;
    for(count =0; count<getNoOfKeysInIndexNode(); count++){
        memcpy(&pageNumberdup,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);
        memcpy(list,&indexnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();

        if(pageNumberdup == pageNumber){
            memcpy(key,list,indexhdr->getsizeofkey());
            break;
        }
    }

    if(count == getNoOfKeysInIndexNode()){
        memcpy(key,list,indexhdr->getsizeofkey());
    }
}

void IndexNode::keybeforegivenpagenumber(int pageNumber, char* key){
    int position=IndexNode::getIndexNodeHeaderSize();
    int pageNumberdup;
    char list[indexhdr->getsizeofkey()];
    memcpy(&pageNumberdup,&indexnodedata[position],sizeof(int));

    position = position + sizeof(int);

    if(pageNumberdup == pageNumber){
        key = NULL;
    }else{
        for(int count =0; count<getNoOfKeysInIndexNode(); count++){
            memcpy(list,&indexnodedata[position],indexhdr->getsizeofkey());
            position = position + indexhdr->getsizeofkey();
            memcpy(&pageNumberdup,&indexnodedata[position],sizeof(int));
            position = position + sizeof(int);
             if(pageNumberdup == pageNumber){
                memcpy(key,list,indexhdr->getsizeofkey());
                 break;
                }
        }
    }
}
void IndexNode::getpagenumberbetweenleftpageandrightpage(int leftPage, int rightPage, char* key){
    int position=IndexNode::getIndexNodeHeaderSize();
    int leftpagevalue,rightpagevalue;
    char list[indexhdr->getsizeofkey()];

    for(int i=0; i<getNoOfKeysInIndexNode(); i++){
        memcpy(&leftpagevalue,&indexnodedata[position],sizeof(int));
        position=position+sizeof(int);
        memcpy(list,&indexnodedata[position],indexhdr->getsizeofkey());
        position=position+indexhdr->getsizeofkey();
        memcpy(&rightpagevalue,&indexnodedata[position],sizeof(int));
        if(leftPage == leftpagevalue && rightPage == rightpagevalue){
            memcpy(key, list, indexhdr->getsizeofkey());
            break;
        }
    }
}

// replaces oldkey by newkey
void IndexNode::keyshift(const char* oldKey, const char* newKey){
    int position = IndexNode::getIndexNodeHeaderSize();

    position = position + sizeof(int);

    char list[indexhdr->getsizeofkey()];
    int searchHIT_RETURN=0;
    for(int count=0; count<indexnodehdrstr.noOfKeys;count++){
        memcpy(list,&indexnodedata[position],indexhdr->getsizeofkey());
        int comparevalue = BplusTree::keyComp(list,oldKey, indexhdr->getcolcount(),indexhdr);
        if(comparevalue==0){
            memcpy(&indexnodedata[position],newKey,indexhdr->getsizeofkey());
            searchHIT_RETURN=1;
            break;
        }
        position = position + indexhdr->getsizeofkey(); // Bypass the key
        position = position + sizeof(int); // bypass the pagenumber
    }
    if(searchHIT_RETURN==0){
        if(indexhdr->gettreeheight() >= getIndexNodeLevel() && getParentofIndexNode() != -1){
            IndexNode indexNode;
            indexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
            indexNode.keyshift(oldKey,newKey);
        }
    }
//return HIT_RETURN;
}

// Gets all the leafpages under the called indexnode..
void IndexNode::getleafset(std::vector<int>& leafPages){
    int indexnodelevel;
    int position=getIndexNodeHeaderSize();

    indexnodelevel=getIndexNodeLevel();

    int pagenumberdupl;

    for(int count=0; count <indexnodehdrstr.noOfKeys; count++){
        memcpy(&pagenumberdupl,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);
        position = position + indexhdr->getsizeofkey();

        if(indexnodelevel > 1){
            IndexNode indexNode;
            indexNode.openindexnodewithindexheader(indexhdr,pagenumberdupl);
            indexNode.getleafset(leafPages);
        }
        if(indexnodelevel == 1){
            leafPages.push_back(pagenumberdupl);
        }
    }
}

int IndexNode::getleftandrightpagevaluestothegivenpagenumber(int pageNumber, int& leftSibling, int& rightSibling){
    int position = IndexNode::getIndexNodeHeaderSize();
    int currentLeftPage = -1;
    int currentRightPage = -1;
    int previousLeftPage = -1;

    //int searchflag = 0;

    for(int i=0; i<getNoOfKeysInIndexNode(); i++){
        memcpy(&currentLeftPage,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);
        position = position + indexhdr->getsizeofkey();

        memcpy(&currentRightPage,&indexnodedata[position],sizeof(int));

        if(currentLeftPage == pageNumber){
            leftSibling = previousLeftPage;
            rightSibling = currentRightPage;
            return HIT_RETURN;
        }
        previousLeftPage = currentLeftPage;
    }
    leftSibling = previousLeftPage;
    rightSibling = -1;
    return HIT_RETURN;
}

void IndexNode::removethekeyatthefrontofindexnode(){
    int position = IndexNode::getIndexNodeHeaderSize();

    char keyset[getNoOfKeysInIndexNode() - 1][indexhdr->getsizeofkey()];
    int pagenumberset[getNoOfKeysInIndexNode()];
    int counter=0;

    position = position + sizeof(int);
    position = position + indexhdr->getsizeofkey();

    for(int i=1; i<getNoOfKeysInIndexNode(); i++){
        memcpy(&pagenumberset[counter],&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);

//        memcpy(&pagenumberset[counter],&indexnodedata[position],sizeof(int));
//        position = position + sizeof(int);

        memcpy(&keyset[counter],&indexnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();

        counter ++;
    }

    memcpy(&pagenumberset[counter],&indexnodedata[position],sizeof(int));

    position = IndexNode::getIndexNodeHeaderSize();

    for(int i=0; i<counter; i++){
        memcpy(&indexnodedata[position],&pagenumberset[i],sizeof(int));
        position = position + sizeof(int);

        memcpy(&indexnodedata[position],keyset[i],indexhdr->getsizeofkey());
        position = position +indexhdr->getsizeofkey();
    }

    memcpy(&indexnodedata[position],&pagenumberset[counter],sizeof(int));
    setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
}


void IndexNode::removethekeyattheendofindexnode(){
    int keycount = getNoOfKeysInIndexNode();
    keycount = keycount - 1;
    setNoOfKeysInIndexNode(keycount);
}

// LeafNode dummyfunctions.... ######################################################################################
//#############################################################################################################

void LeafNode::getKey(int keyNumber, char* key1){
    int position= getLeafNodeHeaderSize();
    position = position + keyNumber * (indexhdr->getsizeofkey() + RIDSIZE); // RID_LENGTH VALUE IS RIDSIZE
    memcpy(key1, &leafnodedata[position], sizeof(indexhdr->getsizeofkey()));

}

void LeafNode::getKeyAndRID(int keyNumber, char* key1, RID& rid){
    int position=getLeafNodeHeaderSize();
    position = position + keyNumber * (indexhdr->getsizeofkey() + RIDSIZE); // RID_LENGTH VALUE IS RIDSIZE
    memcpy(key1, &leafnodedata[position],sizeof(indexhdr->getsizeofkey()));
    position = position + indexhdr->getsizeofkey();
    memcpy(&rid,&leafnodedata[position],RIDSIZE); // RID_LENGTH IS RIDSIZE
}

int LeafNode::keyComponly(char* key1, char* key2){
    return strcmp(key1,key2);
}


void LeafNode::getFirstKey(char* FirstKey, RID& rid){
    int position=LeafNode::getLeafNodeHeaderSize();
    memcpy(FirstKey,&leafnodedata[position],sizeof(indexhdr->getsizeofkey()));
    position=position + indexhdr->getsizeofkey();
    memcpy(&rid,&leafnodedata[position],RIDSIZE);//RIDSIZE is the length of RID
}

void LeafNode::getFirstKeyOnly(char* fkey){
    int position=LeafNode::getLeafNodeHeaderSize();
    memcpy(fkey,&leafnodedata[position],sizeof(indexhdr->getsizeofkey()));
}

void LeafNode::getLastKey(char* LastKey, RID& rid){
    int position=LeafNode::getLeafNodeHeaderSize();
    position = position + (getNoOfRecordsInNode() - 1) * (indexhdr->getsizeofkey() + RIDSIZE); // RID_LEN is RIDSIZE
    memcpy(LastKey,&leafnodedata[position],sizeof(indexhdr->getsizeofkey()));
    position = position + indexhdr->getsizeofkey();
    memcpy(&rid,&leafnodedata[position],RIDSIZE);//RIDSIZE is the length of RID
}

void LeafNode::getParentkey(char* pkey){
    int directparent=getparentpagevalue();
    if(directparent!=-1){ // If the parent exists..
        IndexNode indexNode;
        indexNode.openindexnodewithindexheader(indexhdr,directparent);
        indexNode.keybeforegivenpagenumber(getPageNumber(),pkey);
    }
}

int LeafNode::compareRIDs(RID rid1, RID rid2){
    if(rid1.pageNumber == rid2.pageNumber && rid1.slotNumber == rid2.slotNumber)
        return PHAT_RETURN;
    else
        return HIT_RETURN;
}


// Given the first key and the second key, this function gets the values of keys and rids between them!

int LeafNode::keyandridinbetweenkeys(const char* firstKey, const char* secondKey, std::vector<RID>& RIDVector, std::vector<string>& keyVector){
    int position = LeafNode::getLeafNodeHeaderSize();
    char keyvalue[indexhdr->getsizeofkey()];
    RID rid;
    int flag = 0;
    for(int i=0; i<leafnodehdrstr.noOfRecords;i++){
        memcpy(keyvalue,&leafnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();

        memcpy(&rid, &leafnodedata[position],RIDSIZE);
        if ((BplusTree::keyComp(keyvalue, firstKey, indexhdr->getcolcount(), indexhdr) == 0
				|| BplusTree::keyComp(keyvalue, firstKey,indexhdr->getcolcount(), indexhdr) == 1)
				&& (BplusTree::keyComp(keyvalue, secondKey, indexhdr->getcolcount(), indexhdr)
						== 0 || BplusTree::keyComp(keyvalue, secondKey,indexhdr->getcolcount(),
						indexhdr) == -1)){
            RIDVector.push_back(rid);
            string str(keyvalue, indexhdr->getsizeofkey());
            keyVector.push_back(str);
            str.clear();
            position = position + RIDSIZE;
            flag = 1;
        }else{
            position = position + RIDSIZE;
            flag = 0;
        }
    }
    return flag;
}

void LeafNode::getFirstKey(char* Firstkey){
    int position = LeafNode::getLeafNodeHeaderSize();
    memcpy(Firstkey,&leafnodedata[position],indexhdr->getsizeofkey());
}

// Get me all the keys and rids in the current page.. I'm in.. ok, thank you!

void LeafNode::getridkeysets(std::vector<RID>& RIDVector, std::vector<string>& keyVector){
    int position = LeafNode::getLeafNodeHeaderSize();
    char keylistholder[indexhdr->getsizeofkey()];
    RID duplridholder;

    for(int loopcounter=0; loopcounter<getNoOfRecordsInNode(); loopcounter++){
        memcpy(keylistholder,&leafnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();
        memcpy(&duplridholder,&leafnodedata[position],RIDSIZE); // RID Length is RIDSIZE..
        position = position + RIDSIZE; // RID length is RIDSIZE..
        RIDVector.push_back(duplridholder);
        string mystring(keylistholder,indexhdr->getsizeofkey());
        keyVector.push_back(mystring);
        mystring.clear();
    }
}

//################################################################################
// ###################################Dummy Functions end here - Or may I say? Junk functions have actually ended!#####################
//##################################################################################################


//################################################################################
// ###################################Leaf Node Functions#####################3
//##################################################################################################

LeafNode::LeafNode(){
    createflag=FALSE;
    bm = new buffer_manager();
}


LeafNode::LeafNode(int LeafPageNumber){

    //long sampleSize =200;
     //Buffer_Pool::InitBuffer(sampleSize);
     bm = new buffer_manager();
    genpage *pdata=bm->BufferWrite(dbname,LeafPageNumber);
    leafnodedata=(char *)pdata;

    memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
    int indexheaderclassNumber=getindexheaderclasspagenumber();

    indexhdr=new indexheaderclass();
    indexhdr->openindexheaderpage(indexheaderclassNumber);
    createflag=TRUE;
}

LeafNode::LeafNode(indexheaderclass* indexheaderclass, int leafPageNumber){

    //long sampleSize=200;
    //Buffer_Pool::InitBuffer(sampleSize);
    bm = new buffer_manager();
    createflag=FALSE; //Header hasn't been created HERE..
    indexhdr=indexheaderclass;

    genpage *pdata=bm->BufferWrite(dbname,leafPageNumber);
    leafnodedata=(char *)pdata;

    memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));
}

LeafNode::~LeafNode(){
    bm->ReleasePage(dbname,leafnodehdrstr.gph._page_number);
    //bm->Commit(dbname,leafnodehdrstr.gph._page_number);
    if(createflag==TRUE){
        delete indexhdr;
    }
}

// Creating a Leaf Page

int LeafNode::createnewleafnode(indexheaderclass* bplustreeindexhdrclassptr){
    genpage *pdata=bm->GetFreePage(dbname);
    leafnodedata=(char *)pdata;

    memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));

    leafnodehdrstr.gph._priority= TYPE_LEAF_PAGE;
    //leafnodehdrstr.gph._page_number=pdata->_page_number;
    /*Above not needed for the fact that the structure is anyways being copied .. */
    leafnodehdrstr.level=0; // Leaf Node would be at level 0
    leafnodehdrstr.noOfRecords=0; // Initial number of records are apparently 0

    leafnodehdrstr.parentpagevalue=-1;
    leafnodehdrstr.leftpagevalue=-1;
    leafnodehdrstr.rightpagevalue=-1;

    leafnodehdrstr.indexheaderclassNumber=bplustreeindexhdrclassptr->getPageNumber();

    memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
    indexhdr=bplustreeindexhdrclassptr;

    if(indexhdr->getpagenumberofroot() == -1){
      //  cout<<"The rootpage of this is -1, so nothing has been done so far.. so adding this as the root";
        indexhdr->setpagenumberofroot(getPageNumber());
    }
    return HIT_RETURN;
}

// ===================Defining gettrs and setters first=============================
//=====================Some dupllate/dummy functions would also be defined here=========================


/*
int LeafNode::searchinleafkeyonly(const char* key){
    int recordcount;
    int position = LeafNode::getLeafNodeHeaderSize();
    char list[indexhdr->getsizeofkey()];
    recordcount=getNoOfRecordsInNode();
    int flagvalue=1;

    for(int loopcounter = 0; loopcounter < recordcount; loopcounter++){
        memcpy(list,&leafnodedata[position],indexhdr->getsizeofkey());
        int comparevalue = BplusTree::keyComp(list,key,indexohdr);
        if(comparevalue == 0){
            return PHAT_RETURN;
        }
        position = position + indexhdr->getsizeofkey();
        position = position + RIDSIZE; // RID length has to be bypassed as well..
    }
    return HIT_RETURN;
}*/

int LeafNode::searchinleaf(const char* key, RID rid){
    int recordcount;
    int position = LeafNode::getLeafNodeHeaderSize();
    char list[indexhdr->getsizeofkey()];

   RID ridfound;
    recordcount=getNoOfRecordsInNode();
    int flagvalue=1;

    int dummycompare = -1;

    for(int loopcounter = 0; loopcounter < recordcount; loopcounter++){
        memcpy(list,&leafnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();
        memcpy(&ridfound, &leafnodedata[position],RIDSIZE);
        int comparevalue = BplusTree::keyComp(list,key,indexhdr->getcolcount(),indexhdr);
        if(comparevalue == 0 && compareRIDs(rid,ridfound)!=0){
            flagvalue = OTHER_RETURN;
        }

        if(comparevalue == 0 && compareRIDs(rid,ridfound)==0){
            return PHAT_RETURN;
        }

        if(comparevalue == -1){
            dummycompare = -1;
        }
        //position = position + indexhdr->getsizeofkey();
        position = position + RIDSIZE; // RID length has to be bypassed as well..
    }
    if(dummycompare == -1){
        return OTHER_RETURN;
    }
    return flagvalue;
}


int LeafNode::insertinleaf(const char* key, RID rid){
//    cout<<"This deals with insertion in leafnodes";
//    cout<<"The number of records already in this leafnode are"<<getNoOfRecordsInNode();
//    cout<<"Initial page number is"<<getPageNumber();
//    cout<<"the key size for this is.. "<<indexhdr->getsizeofkey();

    int i=0;
    char keylist[indexhdr->getsizeofkey()]; // space sufficient to hold a single key..

    /* If the number of records in leafnode is equal to the maximum number of records.. that is no space available..
     * 1) See if there is any leaf node if ther is not, create a leafnode and insertit and make it a root
     * 2) If there's just one laefnode and if there's freespace insert into it and return
     * 3) If there's just one leafnode and if it's full, split it.. move half the keys into the other node.. create
     *    an indexnode for the split and put the newkey and the next key in the indexnode
     * 4) If there are inserts now, that requires the leafnodes under an indexnode to be split again, do the split
     *    and adjust the pagenumbers accordingly.. left and right pointers basically..
     * 5) If there is a split required in the indexnode.. that will be handled in insertinindexnode..
     *
     */
    
    int numberofrecords = leafnodehdrstr.noOfRecords;
    int leafcountfanout = indexhdr->getleafcountmax();
    if(numberofrecords < leafcountfanout){ // start first if..
        // This loop is executed when the number of records present are less than fanout.. that is there is
        // space to accomodate the new records..
//        cout<<"The leafnode has enough space to hold the new records...."
//           <<"So the operation is straight forward.. "<<endl;
        int tempps = getLeafNodeHeaderSize();
        for(i=0; i<numberofrecords; i++){

            memcpy(keylist,&leafnodedata[tempps],indexhdr->getsizeofkey());
            //getKey(i,keylist); // Get key at position i and save it in keylist.. keylist is a [] of keysize.
            int dummyvalue = indexhdr->colformat[i+1];
            int comparevalue = -1;
            //comparevalue=BplusTree::keyComp(keylist,key,indexhdr->getcolcount(),indexhdr);
            if(BplusTree::keyComp(keylist,key,indexhdr->getcolcount(),indexhdr) ==1){
                break;
            }
            tempps = tempps + indexhdr->getsizeofkey() + RIDSIZE;
        } /// End of getting key and comparision.
        if(leafnodehdrstr.noOfRecords==0){  // If the node is empty direct insert..
      //      cout<<"Node is empty, no records so far..so inserting directly here.."<<endl;
            int position = LeafNode::getLeafNodeHeaderSize();
            memcpy(&leafnodedata[position],key,indexhdr->getsizeofkey());

            position = position + indexhdr->getsizeofkey();
            memcpy(&leafnodedata[position],&rid,RIDSIZE); // RIDSIZE is rid length

            leafnodehdrstr.noOfRecords++;

            memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
            //buffer specific code
            //---------------------------------------
//            int relpage = getPageNumber();
//            bm->ReleasePage(dbname,relpage);
//            //bm->Commit(dbname,relpage);
            //----------------------------------------
        }else{
            if(leafnodehdrstr.noOfRecords==i){
                // Node has no key that is less than the current key
                // This means to say that the new key should be inserted at the end of the leafnode...
        //        cout<<"Inserting the new key at the end of the leafnode.. "<<endl;
                int position = LeafNode::getLeafNodeHeaderSize();
                position = position + (leafnodehdrstr.noOfRecords * (indexhdr->getsizeofkey() + RIDSIZE));

                memcpy(&leafnodedata[position],key,indexhdr->getsizeofkey());
                position=position+indexhdr->getsizeofkey();

                memcpy(&leafnodedata[position],&rid,RIDSIZE);

                leafnodehdrstr.noOfRecords++;

                memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
                   //buffer specific code
            //---------------------------------------
//            int relpage1 = getPageNumber();
//            bm->ReleasePage(dbname,relpage1);
//            //bm->Commit(dbname,relpage1);
            //----------------------------------------

            }else{
          //      cout<<"Insert at the beginning or in the middle..."<<endl;

                char prevfirst[indexhdr->getsizeofkey()];
                char dupldummy[indexhdr->getsizeofkey()];

                getFirstKeyOnly(dupldummy);
                getParentkey(prevfirst);
                int duplcharsize=leafnodehdrstr.noOfRecords * (indexhdr->getsizeofkey() + RIDSIZE);
                char duplchar[duplcharsize];
                int position = LeafNode::getLeafNodeHeaderSize();

                position = position + i * (indexhdr->getsizeofkey() + RIDSIZE);

                //int memcpysizer= (leafnodehdrstr.noOfRecords - (i)) * (indexhdr->getsizeofkey() + RIDSIZE);
               // int dup = i;
               // i = memcpysizer;
               // i = dup;
                memcpy(duplchar,&leafnodedata[position],(leafnodehdrstr.noOfRecords - (i)) * (indexhdr->getsizeofkey() + RIDSIZE));

                memcpy(&leafnodedata[position],key,indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();

                memcpy(&leafnodedata[position],&rid,RIDSIZE);
                position = position + RIDSIZE;

                memcpy(&leafnodedata[position],duplchar,(leafnodehdrstr.noOfRecords - (i)) * (indexhdr->getsizeofkey() + RIDSIZE));
                leafnodehdrstr.noOfRecords++;
                memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));
                // Insert at the beginning and push into indexnode - below if loop..
                if(i == 0 && getparentpagevalue() != -1){
                    IndexNode indexNode;
                    indexNode.openindexnodewithindexheader(indexhdr,getparentpagevalue());

                    //int compval=BplusTree::keyComp(prevfirst,key,indexhdr->getcolcount(),indexhdr);

                    if(BplusTree::keyComp(prevfirst,key,indexhdr->getcolcount(),indexhdr) !=0 ){
                        indexNode.keyshift(prevfirst,key);
                    }
                    // Buffer Specific Code..
                    //===========================================================
                    //int relpage = indexNode.getPageNumber();
                    //bm->ReleasePage(dbname,relpage);
                    ////bm->Commit(dbname,relpage);
                    //=============================================================
                }
            }
        }
    //buffer specific code..
       //-----------------
            //int relpage1 = getPageNumber();
            //bm->ReleasePage(dbname,relpage1);
            ////bm->Commit(dbname,relpage1);
        //------------------
    return HIT_RETURN;
    }else if(numberofrecords == leafcountfanout){ // There is not enough space to insert in the leaf node.. so here we gotta be splitting.
    int advanceleftleafpage=0, advancerightleafpage=0; // would help in advancing leaf pages..
    char advancekeyathalf[indexhdr->getsizeofkey()]; // same as above..
    char keylistrecords[leafnodehdrstr.noOfRecords + 1][indexhdr->getsizeofkey()]; // used to hold all th keys.
    int searchflag = 0;

    RID dummyRIDS[leafnodehdrstr.noOfRecords + 1]; // same as the number of keys of course

    int counterval=0;

    int position=LeafNode::getLeafNodeHeaderSize();
    for(int i=0; i<leafnodehdrstr.noOfRecords;  i++){
        memcpy(keylistrecords[counterval],&leafnodedata[position],indexhdr->getsizeofkey());
        position= position + indexhdr->getsizeofkey(); // move the position to the RID..

        memcpy(&dummyRIDS[counterval],&leafnodedata[position],RIDSIZE); // Size of rid is RIDSIZE

        //int comparevalue = BplusTree::keyComp(keylistrecords[counterval],key,indexhdr->getcolcount(),indexhdr);

        if(BplusTree::keyComp(keylistrecords[counterval],key,indexhdr->getcolcount(),indexhdr) == 1 && searchflag==0){
            char dupllist[indexhdr->getsizeofkey()];
            RID duplrid;
            memcpy(dupllist,keylistrecords[counterval],indexhdr->getsizeofkey()); // The list of keys is found in dupllist
            duplrid=dummyRIDS[counterval]; // The rid which is found less than is copied into duplrid;
            memcpy(keylistrecords[counterval],key,indexhdr->getsizeofkey());
            dummyRIDS[counterval]= rid;
            counterval++;
            memcpy(keylistrecords[counterval],dupllist,indexhdr->getsizeofkey());
            dummyRIDS[counterval]=duplrid;
            searchflag=1;
        }
        position = position + RIDSIZE; // Length of RID is RIDSIZE
        counterval++;
    } // end of for..
    if(searchflag==0){ // meaning we've reached the end without finding a match..
        memcpy(keylistrecords[counterval],key,indexhdr->getsizeofkey());
        memcpy(&dummyRIDS[counterval],&rid,RIDSIZE);// RIDSIZE is the length of the RID;
        counterval++;
    }
    // that is copying all the key, rids to an array done.. now insertion has to be done!
    // Till here I will have the records including the one to be inserted in order
    // that is keylistrecords would contain the list of keyrecords in order..
    // and dummyRIDs would contain all the records in the order.. depending on the key order that is..
    // Next up is splitting and setting up page numbers..

    position = LeafNode::getLeafNodeHeaderSize();
    leafnodehdrstr.noOfRecords=0;
    // Now we have to store the first half of the keys one by one..
    //cout<<"Storing the first half of the keys one by one.... "<<endl;

    for(int i=0; i<counterval/2; i++){
        memcpy(&leafnodedata[position],keylistrecords[i],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();

        memcpy(&leafnodedata[position],&dummyRIDS[i],RIDSIZE); // RIDSIZE is the length of the RID..
        position = position + RIDSIZE; // RID LENGTH = RIDSIZE
        leafnodehdrstr.noOfRecords++;
    } // End of first for.. that is first half saved..  in the current node only..

    LeafNode newNode;

    newNode.createnewleafnode(indexhdr);

    //cout<<"The pagenumber of the new leaf node is.. "<<newNode.getPageNumber();
    advanceleftleafpage=leafnodehdrstr.gph._page_number;
    advancerightleafpage=newNode.getPageNumber();
    memcpy(advancekeyathalf,keylistrecords[counterval/2],indexhdr->getsizeofkey());


    if(leafnodehdrstr.rightpagevalue != -1){
        LeafNode rightLeaf(indexhdr,leafnodehdrstr.rightpagevalue);
        rightLeaf.setleftpagevalue(newNode.getPageNumber());

        // bufferspecific code for right leaf..
        //bm->ReleasePage(dbname,rightLeaf.getPageNumber());
        ////bm->Commit(dbname,rightLeaf.getPageNumber());
        //============buffer code for this ends here..
    }

    newNode.setrightpagevalue(leafnodehdrstr.rightpagevalue);
    newNode.setleftpagevalue(leafnodehdrstr.gph._page_number);

    // dummy code for checking
    leafnodehdrstr.rightpagevalue = newNode.getPageNumber();
//    int dumpo = LeafNode::getLeafNodeHeaderSize();
//    memcpy(leafnodedata,&leafnodehdrstr,dumpo);
    // ===============End of dummy code..
    memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));

    // Now the second half is remaining
    // These remaining half should be stored in the new leaf node..
    //cout<<"Saving the remaining half into the new leaf node..."<<endl;

    for(int i=counterval/2; i<counterval; i++){
        newNode.insertinleaf(keylistrecords[i],dummyRIDS[i]);
    }

    // Savind done.. now parent checking has to be done!
    // checking if the current node has any parent..
    /* If there is no parent
     * create a new indexnode
     * and make it as it's parent..
     */
   // the pagenumbers used so far are.. getpagenumber and newnode.getpagenumber.. to be released..


    if(leafnodehdrstr.parentpagevalue != -1){
//        cout<<"this means to say that, the current leafnode has a parent node"
//                <<"hence the values shall be advanced to the parent node.. "
//                <<"advancing them therefore..."<<endl;

        IndexNode indexNode1;
        indexNode1.openindexnodewithindexheader(indexhdr,leafnodehdrstr.parentpagevalue);
        newNode.setparentpagevalue(leafnodehdrstr.parentpagevalue); // Same as  indexNode1.getPageNumber()

        indexNode1.insertinindex(advancekeyathalf,advanceleftleafpage,advancerightleafpage);

        memcpy(&leafnodehdrstr,leafnodedata,sizeof(leafnodestr));

        setrightpagevalue(newNode.getPageNumber());
        setleftpagevalue(leafnodehdrstr.leftpagevalue);
    }else{ // No parent there... so create one and make it the parent..
//        cout<<"Checking if the current node has any parent.. "
//                <<"if not create another indexnode"
//                <<"and make it the leafnode's parent..."
//                <<endl;

//        cout<<"New IndexNode being created..."<<endl;

        IndexNode newindexNode;
        newindexNode.createnewindexNode(indexhdr);
        int indexpageno=newindexNode.getPageNumber();
  //      cout<<"New indexnode page number... "<<indexpageno;

    //    cout<<"leftpage number after promotion..."<<advanceleftleafpage; // advanceleftpagevalue contains the pagenumber of the original leafnode from which the split was done!
      //  cout<<"rightpage number after promotion..."<<advancerightleafpage; // advance rightpagevalue contains the pagenumber of the node that has been added as new!

        newindexNode.insertinindex(advancekeyathalf,advanceleftleafpage,advancerightleafpage);

        leafnodehdrstr.parentpagevalue=indexpageno;
        memcpy(leafnodedata,&leafnodehdrstr,sizeof(leafnodestr));

        // the setting has already been done before - But no idea why it is not working.. without the following two lines
        // needs a recheck..
        setrightpagevalue(newNode.getPageNumber());
        setleftpagevalue(leafnodehdrstr.leftpagevalue);
       // newNode.setparentpagevalue(indexpageno);
    } // End of minor if-else -- that is parent settind done till here


    return HIT_RETURN;
  } // end of else...
}


int LeafNode::deleteinleaf(const char* key, RID givenRid,
		std::vector<int> &deletedPages) {
	//say given key is not found in any other indexNode
	int currentNoOfRecords = getNoOfRecordsInNode();
//	cout<< "In Leaf page : "<<getPageNumber();
//	cout<<"current number of nodes in this node : "<<currentNoOfRecords;
        double ceilvalue1 = indexhdr->getleafcountmax() / 2;

        if(currentNoOfRecords - 1 < ceil(ceilvalue1)){
            //ohh leaf node does not have enough number of keys so do either shifting or merge
        //    cout<<"This page does not have enough number of keys so do either shifting or merge";
            int parentvalue = getparentpagevalue();
            if(parentvalue != -1){
                // parent page value is not equal to -1 so that means to say that there is some parent existing..
                IndexNode indexNode;
                indexNode.openindexnodewithindexheader(indexhdr, getparentpagevalue());
                int leftSibling, rightSibling;
          //      cout<<"current page number "<<getPageNumber();
                indexNode.getleftandrightpagevaluestothegivenpagenumber(getPageNumber(), leftSibling, rightSibling);
            //    cout<<"left page number "<<leftSibling<<"  right page number "<<rightSibling;

                // values have been retrieved checks will have to be performed..
                if (rightSibling != -1) {//if there is right sibling
              //      cout<<"Checking with right page";
                    LeafNode leafNode(indexhdr, rightSibling);
                    int noOfRecordsInRightPage = leafNode.getNoOfRecordsInNode();
                //    cout<<"no of records in right page"<<noOfRecordsInRightPage;
                    double ceilvalue2 = indexhdr->getleafcountmax()/2;
                    if ((noOfRecordsInRightPage - 1) >= ceil(ceilvalue2)) {
                            //rotate keys from right (right sibling) to left (current node)
                  //          cout<<"Right page more than half number of keys so rotate some keys from right page number";
                            char firstKey[indexhdr->getsizeofkey()];
                            RID rid;
                            leafNode.getFirstKey(firstKey, rid);
                            leafNode.deleteinleaf(firstKey, rid, deletedPages);
                            insertinleaf(firstKey, rid);
                            deleteinleaf(key, givenRid, deletedPages);
                            return HIT_RETURN;
                    } else if (leftSibling != -1) {
                            //right sibling does not have enough keys so check with left sibling
                    //        cout<<"right page is not available and left is available";
                      //      cout<<"checking with left page number";
                            LeafNode leafNode1(indexhdr, leftSibling);
                            int noOfRecordsInLeftPage = leafNode1.getNoOfRecordsInNode();
                        //    cout<<"no of records in left page "<<noOfRecordsInLeftPage;
                            double ceilvalue3 = indexhdr->getleafcountmax()/2;
                            if ((noOfRecordsInLeftPage - 1) >= ceil(ceilvalue3)){
                                    //rotate keys from left to right
                          //          cout<<"left page has more than enough number of keys so we can rotate some keys from left page to current page";
                                    char lastKey[indexhdr->getsizeofkey()];
                                    RID rid;
                                    leafNode1.getLastKey(lastKey, rid);

                                    leafNode1.deleteinleaf(lastKey, rid, deletedPages);

                                    insertinleaf(lastKey, rid);
                                    deleteinleaf(key, givenRid, deletedPages);
                                    //getLastKey(lastKey, rid);

                                    return HIT_RETURN;
                            } else {
                                    //there is not enough number of keys in both left and right siblings
                                    //merge with one of the siblings (right)here
//                                cout<<"Merging with the one of the siblings - Right, in this case. ";
//                                cout<<"Neither the right, nor the left page have got enough nodes..";
                                    deletedPages.push_back(getPageNumber());
                                    int position = LeafNode::getLeafNodeHeaderSize();
                                    char keyvals[indexhdr->getleafcountmax()][indexhdr->getsizeofkey()];
                                    RID rids[indexhdr->getleafcountmax()];
                                    int counterval = 0;
                                    char dupl[indexhdr->getsizeofkey()];
                                    RID duplRid;
                                    for (int i = 0; i < getNoOfRecordsInNode(); i++) {
                                            memcpy(dupl, &leafnodedata[position],
                                                            indexhdr->getsizeofkey());
                                            position = position + indexhdr->getsizeofkey();
                                            memcpy(&duplRid, &leafnodedata[position], RIDSIZE);

                                            if (((BplusTree::keyComp(dupl, key, indexhdr->getcolcount(),
                                                            indexhdr) != 0) && (compareRIDs(
                                                            givenRid, duplRid) != 0))
                                                            || ((BplusTree::keyComp(dupl, key,indexhdr->getcolcount(),
                                                                            indexhdr) == 0)
                                                                            && (compareRIDs(givenRid, duplRid)
                                                                                            != 0))) {

                                                    memcpy(keyvals[counterval], dupl,
                                                                    indexhdr->getsizeofkey());
                                                    memcpy(&rids[counterval], &leafnodedata[position],
                                                                    RIDSIZE);
                                                    counterval++;
                                            }
                                            position = position + RIDSIZE;
                                    }
                               //     cout<<"Moving all keys except deleting key to right page";

                                    for (int i = 0; i < counterval; i++) {
                                            leafNode.insertinleaf(keyvals[i], rids[i]);
                                    }

                                 //   cout<<"Deleting key from the index Node";
                                    IndexNode indexNode;
                                    indexNode.openindexnodewithindexheader(indexhdr, getparentpagevalue());
                                    char keyToDelete[indexhdr->getsizeofkey()];
                                    indexNode.keybeforegivenpagenumber(getPageNumber(),keyToDelete);

                                    char firstKey[indexhdr->getsizeofkey()];
                                    leafNode.getFirstKey(firstKey);
                                    indexNode.editkeybeforepagenumber(leafNode.getPageNumber(), key, firstKey);

                                    indexNode.deleteinindexwithflagset(keyToDelete, FALSE, deletedPages);
                                    //					char firstKey[indexhdr->getsizeofkey()];
                                    //						indexNode.indexNodeOnlyprint();
                                    leafNode.getFirstKey(firstKey);

                                    indexNode.keyshift(key, firstKey);
                                    //						cout << "\n DELETION ENDS HERE" << endl;

                            }
                    } else {

                            //their is no left leaf page number and right leaf page does not enough number of keys
                            //DO merging with right page number
//                            cout<<"There is no left page number and right leaf page does not enough number of keys";
//                            cout<<"Merging with right page number"<<endl;

                            deletedPages.push_back(getPageNumber());
                            int position = LeafNode::getLeafNodeHeaderSize();
                            char keyvals[indexhdr->getleafcountmax()][indexhdr->getsizeofkey()];
                            RID rids[indexhdr->getleafcountmax()];
                            int counterval = 0;
                            char dupl[indexhdr->getsizeofkey()];
                            for (int i = 0; i < getNoOfRecordsInNode(); i++) {
                                    RID duplRid;
                                    memcpy(dupl, &leafnodedata[position],indexhdr->getsizeofkey());
                                    position = position + indexhdr->getsizeofkey();
                                    memcpy(&duplRid, &leafnodedata[position], RIDSIZE);


                                    if (((BplusTree::keyComp(dupl, key, indexhdr->getcolcount(),indexhdr)
                                                    != 0) && (compareRIDs(givenRid, duplRid) != 0))
                                                    || ((BplusTree::keyComp(dupl, key,indexhdr->getcolcount(),
                                                                    indexhdr) == 0) && (compareRIDs(
                                                                    givenRid, duplRid) != 0))) {
                                            memcpy(keyvals[counterval], dupl,
                                                            indexhdr->getsizeofkey());
                                            memcpy(&rids[counterval], &leafnodedata[position], RIDSIZE); // RIDSIZE is RID_LEN
                                            counterval++;
                                    }
                                    position = position + RIDSIZE;
                            }

//                            cout<<"Moving all keys from current node to right node"<<endl;
                            for (int i = 0; i < counterval; i++) {

                                    leafNode.insertinleaf(keyvals[i], rids[i]);
                            }

  //                          cout<<"Deleting required key from index node (its parent node)";
                            IndexNode indexNode;
                            indexNode.openindexnodewithindexheader(indexhdr, getparentpagevalue());
                            if (counterval >= 0) {
                                    indexNode.keyshift(key, keyvals[0]);
                            }
                            char keyToDelete[indexhdr->getsizeofkey()];
                            indexNode.keyaftergivenpagenumber(getPageNumber(),
                                            keyToDelete);

    //                        cout<<"KEY TO DELETE "<<keyToDelete;
                            char firstKey[indexhdr->getsizeofkey()];
                            leafNode.getFirstKey(firstKey);

                            indexNode.editkeybeforepagenumber(
                                            leafNode.getPageNumber(), key, firstKey);
                            indexNode.deleteinindexwithflagset(keyToDelete, TRUE,
                                            deletedPages);

                            int pageNumber =indexNode.indexnodefirstpage();
                            LeafNode leafNode11(indexhdr, pageNumber);
                            leafNode11.getFirstKey(firstKey);
                            indexNode.keyshift(key, firstKey);
                    }
            }else if (leftSibling != -1) {//if there is no rightsibling but their is a left sibling
                //SO ROTATE WITH LEFT SIBLING IF POSSIBLE
      //          cout<<"Their is no right node so check with left page for rotating or merging";
                LeafNode leafNode(indexhdr, leftSibling);
                int noOfRecordsInLeftSibling = leafNode.getNoOfRecordsInNode();
        //        cout<<"no of records in left node"<<noOfRecordsInLeftSibling;
                if ((noOfRecordsInLeftSibling - 1) >= ceil(
                                indexhdr->getleafcountmax() / 2)) {
                        //left sibling has enough number of keys
                        //rotate keys from left to right
          //              cout<<"left node has more than half of the keys so rotate with left page number";
                        char lastKey[indexhdr->getsizeofkey()];
                        RID rid;
                        leafNode.getLastKey(lastKey, rid);
            //            cout<<"FIRST KEY "<<lastKey<<"  "<<rid.pageNumber<<"  "<<rid.slotNumber;
                        leafNode.deleteinleaf(lastKey, rid, deletedPages);
                        cout<<"Inserting key"<<endl;
                        BplusTree::printKey(lastKey,indexhdr);
                        insertinleaf(lastKey, rid);
                        deleteinleaf(key, givenRid, deletedPages);
                    //    getFirstKey(lastKey, rid);
              //          cout<<"FIRST Key-----------"<<lastKey<<"  "<<rid.pageNumber<<"  "<<rid.slotNumber;
                        return HIT_RETURN;
                } else {

                //        cout<<"left page does not havve enough number of keys ";
                  //      cout<<"merge with left page";
                        deletedPages.push_back(getPageNumber());
                        int position = LeafNode::getLeafNodeHeaderSize();
                        char keyvals[indexhdr->getleafcountmax()][indexhdr->getsizeofkey()];
                        RID rids[indexhdr->getleafcountmax()];
                        int counterval = 0;
                        char dupl[indexhdr->getsizeofkey()];
                        for (int i = 0; i < getNoOfRecordsInNode(); i++) {
                                RID duplRid;
                                memcpy(dupl, &leafnodedata[position],
                                                indexhdr->getsizeofkey());
                                position = position + indexhdr->getsizeofkey();
                                memcpy(&duplRid, &leafnodedata[position], RIDSIZE);


                                if (((BplusTree::keyComp(dupl, key, indexhdr->getcolcount(),indexhdr)
                                                != 0) && (compareRIDs(givenRid, duplRid) != 0))
                                                || ((BplusTree::keyComp(dupl, key,indexhdr->getcolcount(),
                                                                indexhdr) == 0) && (compareRIDs(
                                                                givenRid, duplRid) != 0))) {
                                        memcpy(keyvals[counterval], dupl,
                                                        indexhdr->getsizeofkey());
                                        memcpy(&rids[counterval], &leafnodedata[position],
                                                        RIDSIZE);
                                        counterval++;
                                }

                                position = position + RIDSIZE;
                        }

                    //    cout<<"moving all the keys from current page to left page";
                        for (int i = 0; i < counterval; i++) {

                                leafNode.insertinleaf(keyvals[i], rids[i]);
                        }
                    //    cout<<"delete corresponding key from index node (from its parent)";
                        IndexNode indexNode;
                        indexNode.openindexnodewithindexheader(indexhdr, getparentpagevalue());
                        char keyToDelete[indexhdr->getsizeofkey()];
                       // indexNode.keybeforegivenpagenumber(getPageNumber(),keyToDelete);
                       indexNode.keyaftergivenpagenumber(getPageNumber(),keyToDelete);

                    //    cout<<"KEY TO DELETE "<<keyToDelete;
                        indexNode.deleteinindexwithflagset(keyToDelete, FALSE,
                                        deletedPages);

                        char firstKey[indexhdr->getsizeofkey()];

                        //indexNode.indexNodeOnlyprint(); //koushik has to revisit this later..

                        leafNode.getFirstKey(firstKey);
                        indexNode.keyshift(key, firstKey);
                }
             }
        }else{
                // parent page value is -1 that is there is no parent at all.
                // cout<<"if it does not have any parent";
                int treeheight = indexhdr->gettreeheight();
                int treelevel = getLevelofNode();
                if(treelevel == treeheight){
                    // the level of tree is equal to the tree height.. the following loop runs
                    int position = LeafNode::getLeafNodeHeaderSize();
                    char duplKey[indexhdr->getsizeofkey()];
                    RID duplRid;
                    int found = 0, i;
                    for (i = 0; i < getNoOfRecordsInNode(); i++) {
                        memcpy(duplKey, &leafnodedata[position],
                                        indexhdr->getsizeofkey());
                        position = position + indexhdr->getsizeofkey();
                        memcpy(&duplRid, &leafnodedata[position], RIDSIZE);
                        position = position + RIDSIZE;

                        if (BplusTree::keyComp(duplKey, key,indexhdr->getcolcount(), indexhdr)
                                        == 0 && compareRIDs(duplRid, givenRid) == 0) {
                                found = 1;
                                break;
                        }
                    }
                     i = i+1;
                    if (found == 1 && i == getNoOfRecordsInNode()) {
                        setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);
                        if (getNoOfRecordsInNode() == 0) {
                                deletedPages.push_back(getPageNumber());
                   //             cout<<"if number of records are 0 make root as -1";
                                indexhdr->setpagenumberofroot(-1);
                                indexhdr->settreeheight(0);
                        }
                        return HIT_RETURN;
                    }
                     i = i -1;
                     if (found == 1) {
                            int oldposition = position - (indexhdr->getsizeofkey()
                                            + RIDSIZE);
                            char dupl[(getNoOfRecordsInNode() - i - 1)
                                            * (indexhdr->getsizeofkey() + RIDSIZE)];
                            memcpy(dupl, &leafnodedata[position], (getNoOfRecordsInNode()
                                            - i - 1) * (indexhdr->getsizeofkey() + RIDSIZE));
                            memcpy(&leafnodedata[oldposition], dupl, (getNoOfRecordsInNode()
                                            - i - 1) * (indexhdr->getsizeofkey() + RIDSIZE));
                            setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);
                            if (getNoOfRecordsInNode() == 0) {
                                    deletedPages.push_back(getPageNumber());
                     //               cout<<"if number of records are 0 make root as -1";
                                    indexhdr->setpagenumberofroot(-1);
                                    indexhdr->settreeheight(0);
                            }

                            return HIT_RETURN;
                    }
                } // end of else level of tree is equal to treeheight..
            }// end of parentpagevalue == -1 else
         return HIT_RETURN;
        }// end of currentnoofrecords < fillout factor check if..
        else{
            // this means to say that current number of records are greater than ceal value
        //so do the deletion safely without any problem..
            //cout<<"the node can be deleted... "<<endl;
		int position = LeafNode::getLeafNodeHeaderSize();
		char duplKey[indexhdr->getsizeofkey()];
		RID duplRid;
		int found = 0, i;
		for (i = 0; i < getNoOfRecordsInNode(); i++) {
			memcpy(duplKey, &leafnodedata[position], indexhdr->getsizeofkey());
			position = position + indexhdr->getsizeofkey();
			memcpy(&duplRid, &leafnodedata[position], RIDSIZE); // Rid length is RIDSIZE
			position = position + RIDSIZE;
			//			dummykeyComp(duplKey, key);
			if (BplusTree::keyComp(duplKey, key, indexhdr->getcolcount(), indexhdr) == 0
					&& compareRIDs(duplRid, givenRid) == 0) {
				found = 1;
				break;
			}
		}
		if (found == 1 && i == getNoOfRecordsInNode() - 1) {
			setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);
			return HIT_RETURN;
                        // that is, the key that has to be deleted is the last element
		}
                if (found == 1) {
			int oldposition = position - (indexhdr->getsizeofkey() + RIDSIZE);
			char dupl[(getNoOfRecordsInNode() - i - 1) * (indexhdr->getsizeofkey() + RIDSIZE)];
			memcpy(dupl, &leafnodedata[position], (getNoOfRecordsInNode() - i - 1) * (indexhdr->getsizeofkey() + RIDSIZE));
			memcpy(&leafnodedata[oldposition], dupl, (getNoOfRecordsInNode() - i - 1) * (indexhdr->getsizeofkey() + RIDSIZE));
			setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);

              //          cout<<"PARENT PAGE NUMBER "<<getparentpagevalue();
			int levelOfTree = indexhdr->gettreeheight();
			int currentPage = getPageNumber();
			if (levelOfTree != 0) {
				IndexNode indexNode;
                                indexNode.openindexnodewithindexheader(indexhdr, getparentpagevalue());
				char keyshifter[indexhdr->getsizeofkey()];
				getFirstKeyOnly(keyshifter);
				indexNode.keyshift(key, keyshifter);
			}
			return HIT_RETURN;
		} // end of found if..
        } // end of else ..that is end of record check for ceil value.. deletion done safely full return..
        return HIT_RETURN;
}

//
//void LeafNode::print(){
//    int position = LeafNode::getLeafNodeHeaderSize();
//
//    cout<<"Current Leaf Page =================>"<<getPageNumber()<<endl;
//    cout<<"Parent Page Number=================>"<<getparentpagevalue()<<endl;
//    cout<<"Number of Records in Leaf Node=================>"<<getNoOfRecordsInNode()<<endl;
//    cout<<"Left Page Number =================>"<<getLeftPageNumber()<<endl;
//    cout<<"Right Page Number =================>"<<getrightpagevalue()<<endl;
//
//    char keyset[indexhdr->getsizeofkey()];
//    RID rid;
//
//    for(int loopcounter = 0; loopcounter < leafnodehdrstr.noOfRecords; loopcounter++){
//        memcpy(keyset,&leafnodedata[position],indexhdr->getsizeofkey());
//        position = position + indexhdr->getsizeofkey();
//
//        memcpy(&rid, &leafnodedata[position], RIDSIZE); // Length of RID Is RIDSIZE........
//        BplusTree::printKey(keyset,indexhdr);
//        cout<<"PageNumber--------------------------------"
//                <<rid.pageNumber<<"Slot Number............................."<<rid.slotNumber<<endl;
//
//        position = position + RIDSIZE; //Size of RID is RIDSIZE.............
//    }
//}

void LeafNode::printleafnode(){
    cout<<endl;
    cout<<"Leaf Node UI"<<endl;
    cout<<"============="<<endl;
    cout<<"\tCurrent Leaf Page Number   ======="<<getPageNumber()<<endl;
    cout<<"\tParent Page Nymber         ======="<<getparentpagevalue()<<endl;
    cout<<"\tRecords in Leaf Node       ======="<<getNoOfRecordsInNode()<<endl;

    cout<<"\nThe Records in Leaf Node are";
    cout<<"\n============================="<<endl;
    cout<<endl;
    char key[indexhdr->getsizeofkey()];
    RID rid;
    int position = LeafNode::getLeafNodeHeaderSize();
    for(int loopcounter = 0; loopcounter < leafnodehdrstr.noOfRecords; loopcounter++){
        memcpy(key,&leafnodedata[position],indexhdr->getsizeofkey()); // RID leangth is RIDSIZE...
        position = position + indexhdr->getsizeofkey();
        cout<<"The key at position {"<<loopcounter<<"} is ===";
        BplusTree::printKey(key, indexhdr);
        memcpy(&rid,&leafnodedata[position],RIDSIZE);
        cout<<"\nPage Number is     ==="<<rid.pageNumber;
        cout<<"\n Slot Number is    ==="<<rid.slotNumber<<endl;
        position = position + RIDSIZE; // Rid length is RIDSIZE..
    }

    cout<<"End of Leaf Node Records"<<endl;
    cout<<"========================="<<endl;

    cout<<"The Left and Right Page Numbers to this Leaf Node are"<<endl;
    cout<<"-----------------------------------------------------"<<endl;

    cout<<"Left Leaf Page Number    ===="<<getLeftPageNumber()<<endl;
    cout<<"Right Leaf Page Number   ===="<<getrightpagevalue()<<endl;
}

int LeafNode::searchKeyInLeafNode(const char* key, std::vector<RID>& RIDvector){
    int position = LeafNode::getLeafNodeHeaderSize();
    char keyset[indexhdr->getsizeofkey()];
    RID rid;
    int flag = 0;
    int recordcount = leafnodehdrstr.noOfRecords;
    for(int i=0; i<recordcount; i++){
        memcpy(keyset,&leafnodedata[position],indexhdr->getsizeofkey());


        int comparevalue = BplusTree::keyComp(key,keyset, indexhdr->getcolcount(),indexhdr);
        if(comparevalue == 0){
            // meaning we found a key match
            flag = 1;
        }
        position = position + indexhdr->getsizeofkey(); // bypassing the key

        if(flag == 1){
            memcpy(&rid,&leafnodedata[position],RIDSIZE); // copying the rid into rid..
            RIDvector.push_back(rid);
        }else{
            return PHAT_RETURN;
        }
        position = position + RIDSIZE;
    }
    return HIT_RETURN;
}

int LeafNode::searchkeyinLeafNodewithOperator(const char* key, int operatorvalue, std::vector<RID>& RIDVector, std::vector<string>& KeyVector){
    int position = LeafNode::getLeafNodeHeaderSize();
    char keyset[indexhdr->getsizeofkey()];
    RID rid;
    int flag = 0;
    switch(operatorvalue){
        case EQ: // Operator 1 stands for equal to..
            for(int i=0; i<getNoOfRecordsInNode(); i++){
                memcpy(keyset,&leafnodedata[position],indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();
                if(BplusTree::keyComp(keyset,key,indexhdr->getcolcount(),indexhdr)==0){
                    flag = 1;
                    memcpy(&rid,&leafnodedata[position],RIDSIZE); // Size of RID is RIDSIZE
                    position = position + RIDSIZE;
                    RIDVector.push_back(rid);
                    string mystring(keyset,indexhdr->getsizeofkey());
                    KeyVector.push_back(mystring);
                    //string dummystring = KeyVector.back();
                    mystring.clear();
                }else {
                    position = position + RIDSIZE;
                    flag = 1;
                }
            }
            break;
        case GT: // greater than operator..
            for(int i=0; i<getNoOfRecordsInNode(); i++){
                memcpy(keyset,&leafnodedata[position],indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();
                if(BplusTree::keyComp(keyset,key,indexhdr->getcolcount(),indexhdr)==1){
                    flag = 1;
                    memcpy(&rid,&leafnodedata[position],RIDSIZE); // Size of RID is RIDSIZE
                    position = position + RIDSIZE;
                    RIDVector.push_back(rid);
                    string mystring(keyset,indexhdr->getsizeofkey());
                    KeyVector.push_back(mystring);
                    //string dummystring = KeyVector.back();
                    mystring.clear();
                }else {
                    position = position + RIDSIZE;
                    flag = 1;
                }
            }
            break;
        case GTEQ: // greater than or equal to operator..
            for(int i=0; i<getNoOfRecordsInNode(); i++){
                memcpy(keyset,&leafnodedata[position],indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();
                if((BplusTree::keyComp(keyset,key,indexhdr->getcolcount(),indexhdr)==1)
                        || (BplusTree::keyComp(keyset,key,indexhdr->getcolcount(),indexhdr) == 0) ){
                    flag = 1;
                    memcpy(&rid,&leafnodedata[position],RIDSIZE); // Size of RID is RIDSIZE
                    position = position + RIDSIZE;
                    RIDVector.push_back(rid);
                    string mystring(keyset,indexhdr->getsizeofkey());
                    KeyVector.push_back(mystring);
                    //string dummystring = KeyVector.back();
                    mystring.clear();
                }else {
                    position = position + RIDSIZE;
                    flag = 1;
                }
            }
            break;
        case LT: // less than operator..
            for(int i=0; i<getNoOfRecordsInNode(); i++){
                memcpy(keyset,&leafnodedata[position],indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();
                if(BplusTree::keyComp(keyset,key,indexhdr->getcolcount(),indexhdr)== -1){
                    flag = 1;
                    memcpy(&rid,&leafnodedata[position],RIDSIZE); // Size of RID is RIDSIZE
                    position = position + RIDSIZE;
                    RIDVector.push_back(rid);
                    string mystring(keyset,indexhdr->getsizeofkey());
                    KeyVector.push_back(mystring);
                    //string dummystring = KeyVector.back();
                    mystring.clear();
                }else {
                    position = position + RIDSIZE;
                    flag = 1;
                }
                position = position + RIDSIZE;
            }
            break;
        case LTEQ://less than or equal to operator..
            for(int i=0; i<getNoOfRecordsInNode(); i++){
                memcpy(keyset,&leafnodedata[position],indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();
                if((BplusTree::keyComp(keyset,key,indexhdr->getcolcount(),indexhdr)== -1)
                        || (BplusTree::keyComp(keyset,key,indexhdr->getcolcount(),indexhdr) == 0) ){
                    flag = 1;
                    memcpy(&rid,&leafnodedata[position],RIDSIZE); // Size of RID is RIDSIZE
                    position = position + RIDSIZE;
                    RIDVector.push_back(rid);
                    string mystring(keyset,indexhdr->getsizeofkey());
                    KeyVector.push_back(mystring);
                    //string dummystring = KeyVector.back();
                    mystring.clear();
                }else {
                    position = position + RIDSIZE;
                    flag = 1;
                }
            }
            break;
    }
    return flag;
}


//################################################################################
// ###################################End of Leaf Node FUnctions#####################3
//##################################################################################################


//################################################################################
// ###################################Index Node Functions#####################3
//##################################################################################################

IndexNode::IndexNode(){
    // Default Constructor for IndexNode
    createflag=FALSE;
    bm = new buffer_manager();
}

void IndexNode::openIndexNode(int indexpagevalue){

   // long sampleSize =200;
    // Buffer_Pool::InitBuffer(sampleSize);
     //buffer_manager buff1;
    //buff.InitBuffer(200); //Instance of buffer manager and initializing it!

    // pagegeneral *pdata=buff.BufferWrite("dbname",indexheaderclassnumber);

    genpage *pdata=bm->BufferWrite(dbname,indexpagevalue);
    indexnodedata=(char *)pdata;

    memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
   // int indexheaderclassNumber=indexnodehdrstr.indexheaderclassNumber;
    int indexheaderclasspageNumber = indexnodehdrstr.indexheaderclasspageNumber;
    indexhdr=new indexheaderclass();
    indexhdr->openindexheaderpage(indexheaderclasspageNumber);
    createflag=TRUE;
    //bm->ReleasePage(dbname,indexPageNumber);
}

void IndexNode::openindexnodewithindexheader(indexheaderclass* indexheaderclass, int indexpagevalue){
   // long sampleSize=200;
     //    Buffer_Pool::InitBuffer(sampleSize);
    createflag=FALSE;
    indexhdr=indexheaderclass;
    indexnodedata=NULL;

    genpage *pdata=bm->BufferWrite(dbname,indexpagevalue);
    indexnodedata=(char *)pdata;

    memcpy(&indexnodehdrstr,indexnodedata,IndexNode::getIndexNodeHeaderSize());
    //bm->ReleasePage(dbname,indexPageNumber);
}

IndexNode::~IndexNode(){

    bm->ReleasePage(dbname,indexnodehdrstr.gphStruct._page_number);
    //bm->Commit(dbname,indexnodehdrstr.gphStruct._page_number);
    if(createflag==TRUE){
        delete indexhdr;
    }
}

int IndexNode::createnewindexNode(indexheaderclass* bplustreeindexhdrclassptr){
    genpage *pdata=bm->GetFreePage(dbname);
    indexnodedata=(char *)pdata;

    memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));

    indexnodehdrstr.gphStruct._priority=TYPE_INDEX_PAGE;
    indexnodehdrstr.leftpagevalue=-1;
    indexnodehdrstr.rightpagevalue=-1;
    indexnodehdrstr.level=1; // This is the minimum level for indexnodes
    indexnodehdrstr.noOfKeys=0;
    indexnodehdrstr.parentpagevalue=-1;
    //memcpy(pdata->_data, &indexnodehdrstr, sizeof(indexnodestr));
    memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));

    indexhdr=bplustreeindexhdrclassptr;
    //int dummyTFS = PAGESIZE -
//    //bm->Commit(dbname,getPageNumber());
 //   bm->ReleasePage(dbname,getPageNumber());

    return HIT_RETURN;
}

//int IndexNode::insertinindex(const char* key, int leftpagevalue, int rightpagevalue){
//    cout<<"CurrentIndexPageNumber"<<getPageNumber();
//    cout<<"The values received from the function are ==========";
//    cout<<"Left Page Number"<<leftpagevalue<<endl;
//    cout<<"Right Page Number"<<rightpagevalue<<endl;
//    cout<<"Key:============"<<key<<endl;
//
//    // Have the current index pagenumber, open it for writing
//
//    int rootlevel = indexhdr->gettreeheight();
//    // First step would be checking if the root height is zero or not
//    // zero meaning there's no rootnode whatsoever and there is only this node..
//    // .hence would be a striagh forward insert.
//    if(rootlevel != 0){
//        // This means to say that there's already an indexnode existing..
//        // The steps would be..
//        // Checking for the fanout.. if the number of keys are less than fanout.. just do a direct insert
//        // and adjust the pagenumbers subsequently..
//        // if the number of nodes are greater than fanout.. use recursion to set up another indexnode.. and split this up..
//        // the process begins here..
//
//        cout<<"There is already one another indexnode that is existent"
//                <<"So we'll basically see for the fanout and then do the insertion accordingly.."
//                <<"the process begins now.. "<<endl;
//
//        int indexnodefanout = indexhdr->getfanoutoftree();
//        int keycount = indexnodehdrstr.noOfKeys;
//
//        if(keycount == indexnodefanout){
//            // If the number of keys are exactly equal to fanout..
//            // a split has to be done and another indexnode has to be created to point to these two indexnodes..
//            cout<<"Dear Mr.koushik, indexnode isn't that huge,try creating another node, you lazybone!!!!!";
//            cout<<"Distribute it into two indexnodes you lazybone!.......... ";
//            cout<<"Koushik says, oh yes why not!  ";
//
//            char keyvals[indexnodehdrstr.noOfKeys + 1][indexhdr->getsizeofkey()];
//            int pagenovals[indexnodehdrstr.noOfKeys + 2];
//            int counterval=0;
//            int position= IndexNode::getIndexNodeHeaderSize();
//
//            int ticker;
//            int flag=0;
//
//            for(ticker=0; ticker<indexnodehdrstr.noOfKeys;ticker++){
//                char duplKey[indexhdr->getsizeofkey()];
//                int leftdupl, rightdupl;
//                memcpy(&leftdupl,&indexnodedata[position],sizeof(int));
//                position=position+sizeof(int);
//
//                memcpy(&duplKey,&indexnodedata[position],indexhdr->getsizeofkey());
//                position=position+indexhdr->getsizeofkey();
//
//                memcpy(&rightdupl,&indexnodedata[position],indexhdr->getsizeofkey());
//
//                int comparevalue2=BplusTree::keyComp(duplKey,key, indexhdr->getcolcount(),indexhdr);
//
//                if(comparevalue2 == 1 && flag == 0){
//                    memcpy(keyvals[counterval],key,indexhdr->getsizeofkey());
//                    pagenovals[counterval] = leftpagevalue;
//                    counterval++;
//
//                    pagenovals[counterval] = rightpagevalue;
//                    flag=1;
//                }
//
//                memcpy(keyvals[counterval],duplKey,indexhdr->getsizeofkey());
//
//                if(flag == 0){
//                    pagenovals[counterval] = leftdupl;
//                }
//
//                counterval++;
//                pagenovals[counterval]=rightdupl;
//            }
//
//            if(flag == 0){
//                memcpy(keyvals[counterval],key,indexhdr->getsizeofkey());
//                counterval++;
//                pagenovals[counterval]=rightpagevalue;
//            }
//            // Now I have stuff in sorted order.. I have to just split it open and insert from here..
//            indexnodehdrstr.noOfKeys=0;
//
//            position=sizeof(indexnodestr);
//
//            int loopcounter;
//            cout<<"Here mr.koushik the late latif, has to insert half the keys in one index node=======";
//            for(loopcounter=0; loopcounter<counterval/2; loopcounter++){
//                memcpy(&indexnodedata[position],&pagenovals[loopcounter],sizeof(int));
//                position = position+sizeof(int);
//                if(indexnodehdrstr.level == 1){
//                    LeafNode leafNode(indexhdr,pagenovals[loopcounter]);
//                    leafNode.setparentpagevalue(getPageNumber());
//                }else{
//                    IndexNode indexNode;
//                    indexNode.openindexnodewithindexheader(indexhdr,pagenovals[loopcounter]);
//                    indexNode.setParentofIndexNode(getPageNumber());
//                }
//
//                memcpy(&indexnodedata[position],keyvals[loopcounter],indexhdr->getsizeofkey());
//                position = position + indexhdr->getsizeofkey();
//                indexnodehdrstr.noOfKeys++;
//            }
//
//            memcpy(&indexnodedata[position], &pagenovals[loopcounter],sizeof(int));
//            if(indexnodehdrstr.level == 1){
//                LeafNode leafNode(indexhdr,pagenovals[loopcounter]);
//                leafNode.setparentpagevalue(getPageNumber());
//            }else{
//                IndexNode indexNode;
//                indexNode.openindexnodewithindexheader(indexhdr,pagenovals[loopcounter]);
//                indexNode.setParentofIndexNode(getPageNumber());
//            }
//            IndexNode indexNode;
//            indexNode.createnewindexNode(indexhdr);
//            cout<<"New Index Page Number is ========="<<indexNode.getPageNumber();
//            indexNode.setIndexNodeLevel(indexnodehdrstr.level);
//            if(indexnodehdrstr.rightpagevalue != -1){
//                IndexNode indexNode1;
//                indexNode1.openindexnodewithindexheader(indexhdr,indexnodehdrstr.rightpagevalue);
//                indexNode1.setleftpagevalueOfIndexNode(indexNode.getPageNumber());
//            }
//
//            indexNode.setleftpagevalueOfIndexNode(getPageNumber());
//            indexNode.setrightpagevalueOfIndexNode(indexnodehdrstr.rightpagevalue);
//            setrightpagevalueOfIndexNode(indexNode.getPageNumber());
//
//            // Half keys inserted.. the rest half should be inserted into the new node..
//                        cout<<"The remaining keys have to be inserted into the new index node ----- ";
//
//            for(loopcounter=counterval/2 + 1; loopcounter<counterval; loopcounter++){
//                char keyShift[indexhdr->getsizeofkey()];
//                int leftShift, rightShift;
//
//                memcpy(keyShift,keyvals[loopcounter],indexhdr->getsizeofkey());
//                memcpy(&leftShift,&pagenovals[loopcounter],sizeof(int));
//                memcpy(&rightShift,&pagenovals[loopcounter + 1],sizeof(int));
//
//                indexNode.insertinindex(keyShift,leftShift,rightShift);
//
//                if(indexnodehdrstr.level == 1){
//                    LeafNode leafNode(indexhdr,leftShift);
//                    leafNode.setparentpagevalue(indexNode.getPageNumber());
//
//                    LeafNode leafNode1(indexhdr,rightShift);
//                    leafNode1.setparentpagevalue(indexNode.getPageNumber());
//
//
//                }else{
//                    IndexNode duplIndexNode;
//                    duplIndexNode.openindexnodewithindexheader(indexhdr,leftShift);
//                    duplIndexNode.setParentofIndexNode(indexNode.getPageNumber());
//
//                    IndexNode duplIndexNode2;
//                    duplIndexNode2.openindexnodewithindexheader(indexhdr,rightShift);
//                    duplIndexNode2.setParentofIndexNode(indexNode.getPageNumber());
//                }
//            }
//            char advancekeyathalfs[indexhdr->getsizeofkey()];
//            int advanceleft, advanceright;
//
//            advanceleft=getPageNumber();
//            advanceright=indexNode.getPageNumber();
//            memcpy(advancekeyathalfs,keyvals[counterval/2],indexhdr->getsizeofkey());
//
//              if(indexhdr->gettreeheight() == indexnodehdrstr.level){
//                cout<<"A new index Node has to be created.... ";
//                cout<<"This new indexnode should be made the root......";
//
//                /*
//                IndexNode indexNode1;
//                indexNode1.createnewindexNode(indexhdr);
//                indexNode1.setleftpagenumber(getPagenumber());
//                indexNode1.setrightpagenumber(advanceright);
//                 */
//
//                IndexNode indexNode1;
//                indexNode1.createnewindexNode(indexhdr);
//                indexhdr->setpagenumberofroot(indexNode1.getPageNumber());
//                indexhdr->settreeheight(indexhdr->gettreeheight() + 1);
//                int level=indexhdr->gettreeheight();
//
//                indexNode1.setIndexNodeLevel(level); // Key height increased by one level.
//                // Now keys have to be advanced by one level!
//
//                indexNode1.insertinindex(advancekeyathalfs,advanceleft,advanceright);
//
//                indexnodehdrstr.parentpagevalue = indexNode1.getPageNumber();
//                indexnodehdrstr.leftpagevalue = -1;
//                indexnodehdrstr.rightpagevalue = indexNode.getPageNumber();
//
//                memcpy(indexnodedata,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
//                indexNode.setParentofIndexNode(indexNode1.getPageNumber());
//                indexNode.setleftpagevalueOfIndexNode(getPageNumber());
//            }
//            else{
//                // Moving left pagenumber, rt pagenumber and key to the parent of this indexnode..
//
//                IndexNode indexNode;
//                indexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                cout<<"Values have to be promoted now!";
//
//                indexNode.insertinindex(advancekeyathalfs,advanceleft,advanceright);
//                return HIT_RETURN;
//            }
//            return HIT_RETURN;
//        }else{
//            // this is keycount not equal to fanout, in other sense keycount is less than fanout..
//            // When keycount is less than fanout.. we do a direct insert..
//            // nothing to bother about..
//            // to do the insert, the algorithm goes like this..
//            // first locate the key in the sorted order
//            // find the position..
//            // right shift the right hand keys by one
//            // insert the new key at that position
//            // adjust the pagenumbers of leafnodes..
//            // and maintain links in the leafnode.. or leafpages..
//
//            int position = IndexNode::getIndexNodeHeaderSize();
//            int nodecount = indexnodehdrstr.noOfKeys;
//            int traversalcount;
//            int leftdupl, rightdupl;
//            int keyspace = indexhdr->getsizeofkey();
//            char keydupl[keyspace];
//            // check if the number of keys in the indexnode are zero..
//            // if they are, just insert directly and adjust the left and right pointers..
//            if(nodecount == 0){
//                // that is the number of children in this node are zero
//                // hence insert direclty..
//                // after insertion just change the header variables..
//                // setting up the leafpagenumbers first and then there would be insertion
//
//                LeafNode leftpage(indexhdr,leftpagevalue);
//                LeafNode rightpage(indexhdr,rightpagevalue);
//                int currentpage = getPageNumber();
//                leftpage.setparentpagevalue(currentpage);
//                rightpage.setparentpagevalue(currentpage);
//
//                // page values have been set.. start with insertion..
//                // first inserting the left page of it..
//                memcpy(&indexnodedata[position],&leftpagevalue,sizeof(int));
//                position = position + sizeof(int);
//
//                // next up is key insertion
//                memcpy(&indexnodedata[position],key,keyspace);
//                position = position + keyspace;
//
//                // next up is rightpagevalue insertion
//                memcpy(&indexnodedata[position],&rightpagevalue, sizeof(int));
//
//                //setting the headervariables right
//                indexnodehdrstr.noOfKeys = indexnodehdrstr.noOfKeys + 1;
//
//                //writing it back into the indexnodepage
//                int copysizer = IndexNode::getIndexNodeHeaderSize();
//                memcpy(&indexnodedata[position],&indexnodehdrstr,copysizer);
//
//                return HIT_RETURN;
//            }
//            for(traversalcount = 0; traversalcount < nodecount; traversalcount++){
//
//                // copying the leftpagevalue
//                memcpy(&leftdupl,&indexnodedata[position],sizeof(int));
//                position = position + sizeof(int);
//
//                // copying the key value..
//                memcpy(keydupl,key,keyspace);
//                position = position + keyspace;
//
//                // copying the right pagevalue
//                memcpy(&rightdupl,&indexnodedata[position],sizeof(int));
//
//                /*
//                    char keyvals[indexnodehdrstr.noOfKeys][indexhdr->getsizeofkey()];
//
//                    int pagenovals[indexnodehdrstr.noOfKeys - count + 1];
//
//                    int duplosition= IndexNode::getIndexNodeHeaderSize() + count * (sizeof(int) + indexhdr->getsizeofkey());
//
//                 */
//
//                int comparevalue = BplusTree::keyComp(keydupl,key,indexhdr->getcolcount(),indexhdr);
//
//                if(comparevalue == 1){
//                    // this is compare value equal to 1
//                    // that is keydupl > dupl that is dupl has found it's position to be inserted.. so do direct insert..
//                    cout<<"Inserting at location"<<traversalcount;
//                    char keyvals[indexnodehdrstr.noOfKeys][indexhdr->getsizeofkey()];
//
//                    int pagenovals[indexnodehdrstr.noOfKeys - traversalcount + 1];
//
//                    int duplposition= IndexNode::getIndexNodeHeaderSize() + traversalcount * (sizeof(int) + indexhdr->getsizeofkey());
//
//                    int i;
//
//                    cout<<"Shifting remainingkeys from the position"<<traversalcount<<"to one step on the rightside====";
//
//                    for(i=traversalcount; i<indexnodehdrstr.noOfKeys; i++){
//                        memcpy(&pagenovals[i], &indexnodedata[duplposition], sizeof(int));
//                        duplposition=duplposition+sizeof(int);
//                        // cout <<"PageNumbers"<<pagenovals[i];
//                        memcpy(&keyvals[i],&indexnodedata[duplposition],indexhdr->getsizeofkey());
//                        //cout<<"Keys============"<<keyvals[i];
//                        duplposition=duplposition+indexhdr->getsizeofkey();
//                    }
//                    memcpy(&pagenovals[i], &indexnodedata[duplposition],sizeof(int));
//                    position= IndexNode::getIndexNodeHeaderSize() + traversalcount * (sizeof(int) + indexhdr->getsizeofkey());
//
//                    memcpy(&indexnodedata[position], &leftpagevalue, sizeof(int));
//      //              memcpy(&pdata->_data[position],&leftpagevalue,sizeof(int));
//
//                    position=position+sizeof(int);
//
//                    memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
//        //            memcpy(&pdata->_data[position],key,indexhdr->getsizeofkey());
//
//                    position=position+indexhdr->getsizeofkey();
//
//                    memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
//          //          memcpy(&pdata->_data[position],&rightpagevalue,sizeof(int));
//
//                    position=position+sizeof(int);
//                    memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
//                    int indexlevel;
//                    indexlevel = indexnodehdrstr.level; // getting the level of indexnode..
//                    if(indexlevel == 1){
//                        // buffer specific code
//                        //=====================================
//            //            //bm->Commit(dbname,getPageNumber());
//              //          bm->ReleasePage(dbname,getPageNumber());
//                        //======================================
//                        cout<<"Left and Right Parent"<<leftpagevalue<<"Right"<<rightpagevalue;
//                        cout<<"Parent is=="<<getPageNumber();
//                        LeafNode leafNode1(indexhdr,leftpagevalue);
//                        LeafNode leafNode2(indexhdr,rightpagevalue);
//                        LeafNode leafNode3(indexhdr,leftdupl);
//                        LeafNode leafNode4(indexhdr,rightdupl);
//
//                        leafNode1.setleftpagevalue(leafNode3.getLeftPageNumber());
//                        leafNode1.setrightpagevalue(rightpagevalue);
//                        leafNode2.setleftpagevalue(leftpagevalue);
//                        leafNode2.setrightpagevalue(rightdupl);
//                        leafNode4.setleftpagevalue(rightpagevalue);
//                        leafNode1.setparentpagevalue(getPageNumber());
//                        leafNode2.setparentpagevalue(getPageNumber());
//                    }else{
//                                                                        // buffer specific code
//                        //=====================================
//                //        //bm->Commit(dbname,getPageNumber());
//                  //      bm->ReleasePage(dbname,getPageNumber());
//                        //===============================================================
//                        IndexNode indexNode1;
//                        indexNode1.openindexnodewithindexheader(indexhdr,leftpagevalue);
//                        IndexNode indexNode2;
//                        indexNode2.openindexnodewithindexheader(indexhdr,rightpagevalue);
//                        IndexNode indexNode3;
//                        indexNode3.openindexnodewithindexheader(indexhdr,leftdupl);
//                        IndexNode indexNode4;
//                        indexNode4.openindexnodewithindexheader(indexhdr,rightdupl);
//
//                        indexNode1.setleftpagevalueOfIndexNode(indexNode3.getleftpagevalueOfIndexNode());
//                        indexNode1.setrightpagevalueOfIndexNode(rightpagevalue);
//                        indexNode2.setleftpagevalueOfIndexNode(leftpagevalue);
//                        indexNode2.setrightpagevalueOfIndexNode(rightdupl);
//                        indexNode4.setleftpagevalueOfIndexNode(rightpagevalue);
//                        indexNode1.setParentofIndexNode(getPageNumber());
//                        indexNode2.setParentofIndexNode(getPageNumber());
//                    }
//                                        // Buffer Specific code
//                    //pdata=bm->BufferWrite(dbname,getPageNumber());
//                    //=====================================================
//
//                    for(int j=traversalcount; j<indexnodehdrstr.noOfKeys; j++){
//                        memcpy(&indexnodedata[position],&keyvals[j],indexhdr->getsizeofkey());
//                      //  memcpy(&pdata->_data[position],&keyvals[i],indexhdr->getsizeofkey());
//
//                        position=position+indexhdr->getsizeofkey();
//
//                        memcpy(&indexnodedata[position],&pagenovals[j+1],sizeof(int));
//                        //memcpy(&pdata->_data[position],&pagenovals[j+1],sizeof(int));
//
//                        position=position+sizeof(int);
//                    }
//
//                    indexnodehdrstr.noOfKeys++;
//                    cout<<"Increase no of keys by one new count is ----"<<indexnodehdrstr.noOfKeys;
//                    memcpy(indexnodedata,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
//                    //memcpy(pdata->_data,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
//                    //position=IndexNode::getIndexNodeHeaderSize();
//                    ////bm->Commit(dbname,getPageNumber());
//                    //bm->ReleasePage(dbname,getPageNumber());
//                    return HIT_RETURN;
//                } // that is comparevalue == 1 is done for good!
//            } // end of for loop checked for all the nodes..
//            if(traversalcount == nodecount){
//                // that is the traversal has been done.. but a suitable node to shift hasn't been located
//                // meaning this has to be inserted at the end of the indexpage..
//                // the insertion follows..
//                // in here the node is full meaning.. insertion in here should also affect the above indexnode..
//                // here full meaning we have reached the end without finding a match.. but not fanout full.. fanout full is
//                // handled in the opening of this if loop
//                int position = IndexNode::getIndexNodeHeaderSize();
//                int levelofnode = getIndexNodeLevel();
//                if(levelofnode != 1){
//                    IndexNode indexNode1;
//                    indexNode1.openindexnodewithindexheader(indexhdr,leftpagevalue);
//                    IndexNode indexNode2;
//                    indexNode2.openindexnodewithindexheader(indexhdr,rightpagevalue);
//
//                    indexNode1.setParentofIndexNode(getPageNumber());
//                    indexNode2.setParentofIndexNode(getPageNumber());
//                    indexNode2.setleftpagevalueOfIndexNode(leftpagevalue);
//
//                    indexNode1.setrightpagevalueOfIndexNode(rightpagevalue);
//
//                    if(indexNode2.getrightpagevalueOfIndexNode()!=-1){
//                        IndexNode indexNode3;
//                        indexNode3.openindexnodewithindexheader(indexhdr,indexNode2.getrightpagevalueOfIndexNode());
//                        indexNode3.setleftpagevalueOfIndexNode(rightpagevalue);
//                    }
//                }else{ // this else is the level equal to 1 looper..
//                    LeafNode leftpage(indexhdr,leftpagevalue);
//                    LeafNode rightpage(indexhdr,rightpagevalue);
//                    int currentpage = getPageNumber();
//                    rightpage.setleftpagevalue(leftpagevalue);
//                    leftpage.setparentpagevalue(currentpage);
//                    rightpage.setparentpagevalue(currentpage);
//                    leftpage.setrightpagevalue(rightpagevalue);
//
//                    if(rightpage.getrightpagevalue()!=-1){
//                        // that is another rightpage exists so linking to it also
//                        int nextright = rightpage.getrightpagevalue();
//                        LeafNode nextrightpage(indexhdr,nextright);
//                        nextrightpage.setleftpagevalue(rightpagevalue);
//                    }
//                }
//
//                // now do the normal insertion..
//                // inserting leftpage first..
//                memcpy(&indexnodedata[position], &leftpagevalue,sizeof(int));
//                position=position+sizeof(int);
//
//                // inserting keynext..
//                memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
//                position=position+indexhdr->getsizeofkey();
//
//                // inserting right page next..
//                memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
//
//                // updating keys;
//                indexnodehdrstr.noOfKeys++;
//
//                // writing back to page..
//                memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
//            }
//        }// end of if-else part.. meaning end of < fanout loop..
//        return HIT_RETURN;
//    } // end of level of root not equal to zero loop.. direct insert to follow in the below else..
//    else{ // meaning the level of root is zero and there's no other parent node.. other than this node..
//        // Here would be a straightforward insert.. this means that the level of root is zero..
//        cout<<"We gotta make this node the parent... of the indexnode..";
//        indexhdr->setpagenumberofroot(getPageNumber());
//
//        // this node has to be made the rootnode and it should point to the two indexpages given. leftpagenumber and rightpagenumber..
//        int newheightoftree = indexhdr->gettreeheight() + 1;
//        indexhdr->settreeheight(newheightoftree);
//        // height has been set.
//
//        // Now the process is straight forward.. just insert the key off..
//        // before inserting the key just adjust the parents ofleafnode..
//        LeafNode leftpage(indexhdr,leftpagevalue);
//        LeafNode rightpage(indexhdr,rightpagevalue);
//
//        // setting their parents to the current index node
//        int currentpage = getPageNumber();
//        leftpage.setparentpagevalue(currentpage);
//        rightpage.setparentpagevalue(currentpage);
//
//        // now parent setting has been done.. just proceed with the insert process..
//
//        int position = IndexNode::getIndexNodeHeaderSize();
//        int copysize = position;
//
//        // left pagenumber insert here..
//        memcpy(&indexnodedata[position],&leftpagevalue,sizeof(int));
//        position = position + sizeof(int);
//
//        // key insert here
//        int keysize = indexhdr->getsizeofkey();
//        memcpy(&indexnodedata[position],key,keysize);
//        position = position + keysize;
//
//        // rightpagenumber insert here
//        memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
//
//        // inserts done.. now set the number of keys heere..
//        indexnodehdrstr.noOfKeys = indexnodehdrstr.noOfKeys + 1;
//
//        memcpy(indexnodedata,&indexnodehdrstr,copysize);
//
//        return HIT_RETURN;
//    }
//}

int IndexNode::insertinindex(const char* key, int leftpagevalue, int rightpagevalue){
//    cout<<"CurrentIndexPageNumber"<<getPageNumber();
//    cout<<"The values received from the function are ==========";
//    cout<<"Left Page Number"<<leftpagevalue<<endl;
//    cout<<"Right Page Number"<<rightpagevalue<<endl;
//    cout<<"Key:============"<<key<<endl;

    // Have the current index pagenumber, open it for writing


    int levelOfRoot=indexhdr->gettreeheight();
    if (levelOfRoot==0){
    //    cout<<"Making this indexnode as the root of the tree and inserting into this node itself";
        indexhdr->setpagenumberofroot(indexnodehdrstr.gphStruct._page_number);
        indexhdr->settreeheight(indexhdr->gettreeheight() + 1);
//==================================================================================================
   //     indexhdr->dupupdateRootPage(indexnodehdrstr.gphStruct._page_number,getPageNumber());
     //   indexhdr->dupupdateHeightOftheTree((indexhdr->gettreeheight() + 1),getPageNumber());
        // Opening a new page to write
       // genpage *pdata=buffmgr.BufferWrite(dbname,getPageNumber());
        // I have to move IndexNodeHeader size to put any data..
//========================================================================================================
        int position= sizeof(indexnodestr);


        memcpy(&indexnodedata[position], &leftpagevalue, sizeof(int));
        //memcpy(&pdata->_data[position],&leftpagevalue, sizeof(int));
        position=position+sizeof(int);

        memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
        //memcpy(&pdata->_data[position],key,indexhdr->getsizeofkey());
        position=position+indexhdr->getsizeofkey();

        memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
        //memcpy(&pdata->_data[position],&rightpagevalue, sizeof(int));

        indexnodehdrstr.noOfKeys=indexnodehdrstr.noOfKeys + 1;

        memcpy(indexnodedata,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
        //memcpy(pdata->_data,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());

//        buffmgr.Commit(dbname,getPageNumber());
  //      buffmgr.ReleasePage(dbname,getPageNumber());


        LeafNode leafNode(indexhdr,leftpagevalue);
        leafNode.setparentpagevalue(getPageNumber());
        LeafNode leafNode1(indexhdr,rightpagevalue);
        leafNode1.setparentpagevalue(getPageNumber());

        //===============================================================
        //dupsetparentpagevalue for leafnodes will  have to be called..
        //================================================================

        //buffmgr.ReleasePage(dbname,getPageNumber());
        return HIT_RETURN;
    }
    else{
        // If already an indexnode exists..
      //  cout<<"No of keys in the existing indexnode are... "<<indexnodehdrstr.noOfKeys;
      //  cout<<"-------------------------------------";
        if(indexnodehdrstr.noOfKeys != indexhdr->getfanoutoftree()){ // even not equal to can be used..
//            cout<<"The number of keys are less than fanout======="
//                    <<"Therefore this indexnode has enough space to accomodate the new key====="
//                    <<"Hence insert the new key in this node itself....";

            int dupLeftPage, dupRightPage;
            char dupKey[indexhdr->getsizeofkey()];
            int position=IndexNode::getIndexNodeHeaderSize();
            int count;
    //        genpage *pdata=buffmgr.BufferWrite(dbname,getPageNumber());
            //int dummycompare;
            for(count=0; count<indexnodehdrstr.noOfKeys; count++){
                memcpy(&dupLeftPage, &indexnodedata[position],sizeof(int));
                position=position+sizeof(int);
	/*
		memcpy(dupKey,&indexnodedata[position],indexhdr->getsizeofkey());
                position=position+indexhdr->getsizeofkey();

                memcpy(&dupRightPage,&indexnodedata[position],indexhdr->getsizeofkey());
		    char keyvals[indexnodehdrstr.noOfKeys][indexhdr->getsizeofkey()];

                    int pagenovals[indexnodehdrstr.noOfKeys - count + 1];

                    int dupposition= IndexNode::getIndexNodeHeaderSize() + count * (sizeof(int) + indexhdr->getsizeofkey());


	*/


                memcpy(dupKey,&indexnodedata[position],indexhdr->getsizeofkey());
                position=position+indexhdr->getsizeofkey();

                memcpy(&dupRightPage,&indexnodedata[position],indexhdr->getsizeofkey());

              //  int compvalue=BplusTree::keyComp(dupKey, key, indexhdr->getcolcount(), indexhdr);

                if(BplusTree::keyComp(dupKey, key, indexhdr->getcolcount(), indexhdr) ==1 || BplusTree::keyComp(dupKey, key, indexhdr->getcolcount(), indexhdr) == 0){
                    //cout<<"Inserting at location"<<count;
                    char keyvals[indexnodehdrstr.noOfKeys][indexhdr->getsizeofkey()];

                    int pagenovals[indexnodehdrstr.noOfKeys - count + 1];

                    int dupposition= IndexNode::getIndexNodeHeaderSize() + count * (sizeof(int) + indexhdr->getsizeofkey());

                    int i;

                    //cout<<"Shifting remainingkeys from location"<<count<<"to one step on the rightside====";

                    for(i=count; i<indexnodehdrstr.noOfKeys; i++){
                        memcpy(&pagenovals[i], &indexnodedata[dupposition], sizeof(int));
                        dupposition=dupposition+sizeof(int);
                        // cout <<"PageNumbers"<<pagenovals[i];
                        memcpy(&keyvals[i],&indexnodedata[dupposition],indexhdr->getsizeofkey());
                        //cout<<"Keys============"<<keyvals[i];
                        dupposition=dupposition+indexhdr->getsizeofkey();
                    }
                    memcpy(&pagenovals[i], &indexnodedata[dupposition],sizeof(int));
                    position= IndexNode::getIndexNodeHeaderSize() + count * (sizeof(int) + indexhdr->getsizeofkey());

                    memcpy(&indexnodedata[position], &leftpagevalue, sizeof(int));
      //              memcpy(&pdata->_data[position],&leftpagevalue,sizeof(int));

                    position=position+sizeof(int);

                    memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
        //            memcpy(&pdata->_data[position],key,indexhdr->getsizeofkey());

                    position=position+indexhdr->getsizeofkey();

                    memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
          //          memcpy(&pdata->_data[position],&rightpagevalue,sizeof(int));

                    position=position+sizeof(int);
                    memcpy(&indexnodehdrstr,indexnodedata,sizeof(indexnodestr));
                    int dummyposition = 0;
                    int indexlevel;
                    indexlevel = indexnodehdrstr.level; // getting the level of indexnode..
                    if(indexlevel == 1){
                        // buffer specific code
                        //=====================================
            //            buffmgr.Commit(dbname,getPageNumber());
              //          buffmgr.ReleasePage(dbname,getPageNumber());
                        //======================================
                      //  cout<<"Left and Right Parent"<<leftpagevalue<<"Right"<<rightpagevalue;
                      //  cout<<"Parent is=="<<getPageNumber();
                        LeafNode leafNode1(indexhdr,leftpagevalue);
                        LeafNode leafNode2(indexhdr,rightpagevalue);
                        LeafNode leafNode3(indexhdr,dupLeftPage);
                        LeafNode leafNode4(indexhdr,dupRightPage);

                        leafNode1.setleftpagevalue(leafNode3.getLeftPageNumber());
                        leafNode1.setrightpagevalue(rightpagevalue);
                        leafNode2.setleftpagevalue(leftpagevalue);
                        leafNode2.setrightpagevalue(dupRightPage);
                        leafNode4.setleftpagevalue(rightpagevalue);
                        leafNode1.setparentpagevalue(getPageNumber());
                        leafNode2.setparentpagevalue(getPageNumber());
                    }
                    else{
                                                // buffer specific code
                        //=====================================
                //        buffmgr.Commit(dbname,getPageNumber());
                  //      buffmgr.ReleasePage(dbname,getPageNumber());
                        //===============================================================
                        IndexNode indexNode1;
                        indexNode1.openindexnodewithindexheader(indexhdr,leftpagevalue);
                        IndexNode indexNode2;
                        indexNode2.openindexnodewithindexheader(indexhdr,rightpagevalue);
                        IndexNode indexNode3;
                        indexNode3.openindexnodewithindexheader(indexhdr,dupLeftPage);
                        IndexNode indexNode4;
                        indexNode4.openindexnodewithindexheader(indexhdr,dupRightPage);

                        indexNode1.setleftpagevalueOfIndexNode(indexNode3.getleftpagevalueOfIndexNode());
                        indexNode1.setrightpagevalueOfIndexNode(rightpagevalue);
                        indexNode2.setleftpagevalueOfIndexNode(leftpagevalue);
                        indexNode2.setrightpagevalueOfIndexNode(dupRightPage);
                        indexNode4.setleftpagevalueOfIndexNode(rightpagevalue);
                        indexNode1.setParentofIndexNode(getPageNumber());
                        indexNode2.setParentofIndexNode(getPageNumber());
                    }
                    // Buffer Specific code
                    //pdata=buffmgr.BufferWrite(dbname,getPageNumber());
                    //=====================================================
                    for(int j=count; j<indexnodehdrstr.noOfKeys; j++){
                        memcpy(&indexnodedata[position],&keyvals[j],indexhdr->getsizeofkey());
                      //  memcpy(&pdata->_data[position],&keyvals[i],indexhdr->getsizeofkey());

                        position=position+indexhdr->getsizeofkey();

                        memcpy(&indexnodedata[position],&pagenovals[j+1],sizeof(int));
                        //memcpy(&pdata->_data[position],&pagenovals[j+1],sizeof(int));

                        position=position+sizeof(int);
                    }

                    indexnodehdrstr.noOfKeys++;
                    //cout<<"Increase no of keys by one new count is ----"<<indexnodehdrstr.noOfKeys;
                    memcpy(indexnodedata,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
                    //memcpy(pdata->_data,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
                    position=IndexNode::getIndexNodeHeaderSize();
                    //buffmgr.Commit(dbname,getPageNumber());
                    //buffmgr.ReleasePage(dbname,getPageNumber());
                    return HIT_RETURN;
                }
                //dummycompare = compvalue;
            }

            if(indexnodehdrstr.noOfKeys==0){
                position=IndexNode::getIndexNodeHeaderSize();
                //pdata=buffmgr.BufferWrite(dbname,getPageNumber());

                memcpy(&indexnodedata[position],&leftpagevalue,sizeof(int));
                //memcpy(&pdata->_data[position],&leftpagevalue,sizeof(int));
                position=position+sizeof(int);

                memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
                //memcpy(&pdata->_data[position],key,indexhdr->getsizeofkey());
                position=position+indexhdr->getsizeofkey();

                memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
                //memcpy(&pdata->_data[position],&rightpagevalue,sizeof(int));

                indexnodehdrstr.noOfKeys++;

                memcpy(indexnodedata, &indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
                //memcpy(pdata->_data,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());

                LeafNode leafnode1(indexhdr,leftpagevalue);
                leafnode1.setparentpagevalue(getPageNumber());
                LeafNode leafnode2(indexhdr,rightpagevalue);
                leafnode2.setparentpagevalue(getPageNumber());
                return HIT_RETURN;
            }
            if(count==indexnodehdrstr.noOfKeys){ 
                // we haven't found any key greater than the to be inserted key
                // hence the to be inserted key has to be inserted at the end of the indexnode....
//                if(dummycompare == 0){
//                            position=IndexNode::getIndexNodeHeaderSize() + (indexnodehdrstr.noOfKeys * (indexhdr->getsizeofkey() + sizeof(int)));
//                        if(getIndexNodeLevel() == 1){
//                            LeafNode leafNode1(indexhdr,leftpagevalue);
//                            LeafNode leafNode2(indexhdr,rightpagevalue);
//
//                            leafNode2.setleftpagevalue(leftpagevalue);
//                            leafNode1.setparentpagevalue(getPageNumber());
//                            leafNode2.setparentpagevalue(getPageNumber());
//
//                            leafNode1.setrightpagevalue(rightpagevalue);
//
//                            if(leafNode2.getrightpagevalue() != -1){
//                                LeafNode leafNode3(indexhdr,leafNode2.getrightpagevalue());
//                                leafNode3.setleftpagevalue(rightpagevalue);
//                            }
//                        }else{
//                            IndexNode indexNode1;
//                            indexNode1.openindexnodewithindexheader(indexhdr,leftpagevalue);
//                            IndexNode indexNode2;
//                            indexNode2.openindexnodewithindexheader(indexhdr,rightpagevalue);
//
//                            indexNode1.setParentofIndexNode(getPageNumber());
//                            indexNode2.setParentofIndexNode(getPageNumber());
//                            indexNode2.setleftpagevalueOfIndexNode(leftpagevalue);
//
//                            indexNode1.setrightpagevalueOfIndexNode(rightpagevalue);
//
//                            if(indexNode2.getrightpagevalueOfIndexNode()!=-1){
//                                IndexNode indexNode3;
//                                indexNode3.openindexnodewithindexheader(indexhdr,indexNode2.getrightpagevalueOfIndexNode());
//                                indexNode3.setleftpagevalueOfIndexNode(rightpagevalue);
//                            }
//                        }
//
//                        memcpy(&indexnodedata[position], &leftpagevalue,sizeof(int));
//                        position=position+sizeof(int);
//
//                        memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
//                        position=position+indexhdr->getsizeofkey();
//
//                        memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
//                        indexnodehdrstr.noOfKeys++;
//
//                        memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
//                        return HIT_RETURN;
//                }
                position=IndexNode::getIndexNodeHeaderSize() + (indexnodehdrstr.noOfKeys * (indexhdr->getsizeofkey() + sizeof(int)));
                if(getIndexNodeLevel() == 1){
                    LeafNode leafNode1(indexhdr,leftpagevalue);
                    LeafNode leafNode2(indexhdr,rightpagevalue);

                    leafNode2.setleftpagevalue(leftpagevalue);
                    leafNode1.setparentpagevalue(getPageNumber());
                    leafNode2.setparentpagevalue(getPageNumber());

                    leafNode1.setrightpagevalue(rightpagevalue);

                    if(leafNode2.getrightpagevalue() != -1){
                        LeafNode leafNode3(indexhdr,leafNode2.getrightpagevalue());
                        leafNode3.setleftpagevalue(rightpagevalue);
                    }
                }else{
                    IndexNode indexNode1;
                    indexNode1.openindexnodewithindexheader(indexhdr,leftpagevalue);
                    IndexNode indexNode2;
                    indexNode2.openindexnodewithindexheader(indexhdr,rightpagevalue);

                    indexNode1.setParentofIndexNode(getPageNumber());
                    indexNode2.setParentofIndexNode(getPageNumber());
                    indexNode2.setleftpagevalueOfIndexNode(leftpagevalue);

                    indexNode1.setrightpagevalueOfIndexNode(rightpagevalue);

                    if(indexNode2.getrightpagevalueOfIndexNode()!=-1){
                        IndexNode indexNode3;
                        indexNode3.openindexnodewithindexheader(indexhdr,indexNode2.getrightpagevalueOfIndexNode());
                        indexNode3.setleftpagevalueOfIndexNode(rightpagevalue);
                    }
                }

                memcpy(&indexnodedata[position], &leftpagevalue,sizeof(int));
                position=position+sizeof(int);

                memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
                position=position+indexhdr->getsizeofkey();

                memcpy(&indexnodedata[position],&rightpagevalue,sizeof(int));
                indexnodehdrstr.noOfKeys++;

                memcpy(indexnodedata,&indexnodehdrstr,sizeof(indexnodestr));
            }
            return HIT_RETURN;
        }else{
//            cout<<"Dear Mr.koushik, indexnode isn't that huge,try creating another node, you lazybone!!!!!";
//            cout<<"Distribute it into two indexnodes you lazybone!.......... ";
//            cout<<"Koushik says, oh yes why not!  ";

            char keyvals[indexnodehdrstr.noOfKeys + 1][indexhdr->getsizeofkey()];
            int pagenovals[indexnodehdrstr.noOfKeys + 2];
            int counterval=0;
            int position= IndexNode::getIndexNodeHeaderSize();

            int ticker;
            int flag=0;

            for(ticker=0; ticker<indexnodehdrstr.noOfKeys;ticker++){
                char dupKey[indexhdr->getsizeofkey()];
                int leftdup, rightdup;
                memcpy(&leftdup,&indexnodedata[position],sizeof(int));
                position=position+sizeof(int);

                memcpy(&dupKey,&indexnodedata[position],indexhdr->getsizeofkey());
                position=position+indexhdr->getsizeofkey();

                memcpy(&rightdup,&indexnodedata[position],indexhdr->getsizeofkey());

                //int comparevalue2=BplusTree::keyComp(dupKey,key, indexhdr->getcolcount(),indexhdr);

                if(BplusTree::keyComp(dupKey,key, indexhdr->getcolcount(),indexhdr) == 1 || BplusTree::keyComp(dupKey,key, indexhdr->getcolcount(),indexhdr) == 0){
                    if(flag == 0){
                        memcpy(keyvals[counterval],key,indexhdr->getsizeofkey());
                        pagenovals[counterval] = leftpagevalue;
                        counterval++;

                        pagenovals[counterval] = rightpagevalue;
                        flag=1;
                    }
                    
                }

                memcpy(keyvals[counterval],dupKey,indexhdr->getsizeofkey());

                if(flag == 0){
                    pagenovals[counterval] = leftdup;
                }

                counterval++;
                pagenovals[counterval]=rightdup;
            }
            if(flag == 0){
                memcpy(keyvals[counterval],key,indexhdr->getsizeofkey());
                counterval++;
                pagenovals[counterval]=rightpagevalue;
            }

            indexnodehdrstr.noOfKeys=0;

            position=sizeof(indexnodestr);
            int loopcounter;
            //cout<<"Here mr.koushik the late latif, has to insert half the keys in one index node=======";
            
            for(loopcounter=0; loopcounter<counterval/2; loopcounter++){
                memcpy(&indexnodedata[position],&pagenovals[loopcounter],sizeof(int));
                position = position+sizeof(int);
                if(indexnodehdrstr.level == 1){
                    LeafNode leafNode(indexhdr,pagenovals[loopcounter]);
                    leafNode.setparentpagevalue(getPageNumber());
                }else{
                    IndexNode indexNode;
                    indexNode.openindexnodewithindexheader(indexhdr,pagenovals[loopcounter]);
                    indexNode.setParentofIndexNode(getPageNumber());
                }

                memcpy(&indexnodedata[position],keyvals[loopcounter],indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();
                indexnodehdrstr.noOfKeys++;
            }

            memcpy(&indexnodedata[position], &pagenovals[loopcounter],sizeof(int));
            if(indexnodehdrstr.level == 1){
                LeafNode leafNode(indexhdr,pagenovals[loopcounter]);
                leafNode.setparentpagevalue(getPageNumber());
            }else{
                IndexNode indexNode;
                indexNode.openindexnodewithindexheader(indexhdr,pagenovals[loopcounter]);
                indexNode.setParentofIndexNode(getPageNumber());
            }
            IndexNode indexNode;
            indexNode.createnewindexNode(indexhdr);
            //cout<<"New Index Page Number is ========="<<indexNode.getPageNumber();
            indexNode.setIndexNodeLevel(indexnodehdrstr.level);
            if(indexnodehdrstr.rightpagevalue != -1){
                IndexNode indexNode1;
                indexNode1.openindexnodewithindexheader(indexhdr,indexnodehdrstr.rightpagevalue);
                indexNode1.setleftpagevalueOfIndexNode(indexNode.getPageNumber());
            }

            indexNode.setleftpagevalueOfIndexNode(getPageNumber());
            indexNode.setrightpagevalueOfIndexNode(indexnodehdrstr.rightpagevalue);
            setrightpagevalueOfIndexNode(indexNode.getPageNumber());

            //cout<<"The remaining keys have to be inserted into the new index node ----- ";

            for(loopcounter=counterval/2 + 1; loopcounter<counterval; loopcounter++){
                char keyShift[indexhdr->getsizeofkey()];
                int leftShift, rightShift;

                memcpy(keyShift,keyvals[loopcounter],indexhdr->getsizeofkey());
                memcpy(&leftShift,&pagenovals[loopcounter],sizeof(int));
                memcpy(&rightShift,&pagenovals[loopcounter + 1],sizeof(int));

                indexNode.insertinindex(keyShift,leftShift,rightShift);

                if(indexnodehdrstr.level == 1){
                    LeafNode leafNode(indexhdr,leftShift);
                    leafNode.setparentpagevalue(indexNode.getPageNumber());

                    LeafNode leafNode1(indexhdr,rightShift);
                    leafNode1.setparentpagevalue(indexNode.getPageNumber());


                }else{
                    IndexNode dupIndexNode;
                    dupIndexNode.openindexnodewithindexheader(indexhdr,leftShift);
                    dupIndexNode.setParentofIndexNode(indexNode.getPageNumber());

                    IndexNode dupIndexNode2;
                    dupIndexNode2.openindexnodewithindexheader(indexhdr,rightShift);
                    dupIndexNode2.setParentofIndexNode(indexNode.getPageNumber());
                }
            }

            char advancekeyathalfs[indexhdr->getsizeofkey()];
            int advanceleft, advanceright;

            advanceleft=getPageNumber();
            advanceright=indexNode.getPageNumber();
            memcpy(advancekeyathalfs,keyvals[counterval/2 + 1],indexhdr->getsizeofkey());

            if(indexhdr->gettreeheight() == indexnodehdrstr.level){
//                cout<<"A new index Node has to be created.... ";
//                cout<<"This new indexnode should be made the root......";

                /*
                IndexNode indexNode1;
                indexNode1.createnewindexNode(indexhdr);
                indexNode1.setleftpagenumber(getPagenumber());
                indexNode1.setrightpagenumber(advanceright);
                 */

                IndexNode indexNode1;
                indexNode1.createnewindexNode(indexhdr);
                indexhdr->setpagenumberofroot(indexNode1.getPageNumber());
                indexhdr->settreeheight(indexhdr->gettreeheight() + 1);
                //int level=indexhdr->gettreeheight();

                indexNode1.setIndexNodeLevel(indexhdr->gettreeheight()); // Key height increased by one level.
                // Now keys have to be advanced by one level!

                indexNode1.insertinindex(advancekeyathalfs,advanceleft,advanceright);

                indexnodehdrstr.parentpagevalue = indexNode1.getPageNumber();
                indexnodehdrstr.leftpagevalue = -1;
                indexnodehdrstr.rightpagevalue = indexNode.getPageNumber();

                memcpy(indexnodedata,&indexnodehdrstr,IndexNode::getIndexNodeHeaderSize());
                indexNode.setParentofIndexNode(indexNode1.getPageNumber());
                indexNode.setleftpagevalueOfIndexNode(getPageNumber());
            }
            else{
                // Moving left pagenumber, rt pagenumber and key to the parent of this indexnode..

                IndexNode indexNode;
                indexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                //cout<<"Values have to be promoted now!";

                indexNode.insertinindex(advancekeyathalfs,advanceleft,advanceright);
                return HIT_RETURN;
            }
        }
    }
    return HIT_RETURN;
}


int IndexNode::searchinindex(const char* key){
    int position=IndexNode::getIndexNodeHeaderSize();
    char list[indexhdr->getsizeofkey()];
    int leftpagevalue,rightpagevalue;
  //  cout<<"The key count is ... "<<indexnodehdrstr.noOfKeys;
    int keycount = IndexNode::getNoOfKeysInIndexNode();
    for(int count=0; count<IndexNode::getNoOfKeysInIndexNode(); count++){
        memcpy(&leftpagevalue,&indexnodedata[position],sizeof(int));
        position=position+sizeof(int);
        memcpy(list,&indexnodedata[position],indexhdr->getsizeofkey());
        position=position+indexhdr->getsizeofkey();
        memcpy(&rightpagevalue,&indexnodedata[position],sizeof(int));
        int comparevalue=BplusTree::keyComp(list,key,indexhdr->getcolcount(),indexhdr);
//
       if(comparevalue == 0){
        //   cout<<"The value that is going to be returned for compare value zero is.. "<<leftpagevalue;
            return leftpagevalue;
       }

        if(comparevalue == 1){
            return leftpagevalue;
        }
    }
    memcpy(&rightpagevalue,&indexnodedata[position],sizeof(int));
    //position= position + sizeof(int);
    return rightpagevalue;
}

int IndexNode::editkeybeforepagenumber(int pageNumber, const char* oldKey, const char* newKey){
    int position = sizeof(indexnodestr);
    int loopcounter = 0;
    int recordcount = getNoOfKeysInIndexNode();
    int keysize = indexhdr->getsizeofkey();
    char comparekey[keysize];
    int comparepagevalue;
    int colcount = indexhdr -> getcolcount();
    for(loopcounter = 0; loopcounter < recordcount; loopcounter++){
        memcpy(&comparepagevalue,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);
        memcpy(comparekey,&indexnodedata[position],keysize);

        if(comparepagevalue == pageNumber){
            // Page number found.. check for key and replace..

            int comparevalue = BplusTree::keyComp(comparekey,oldKey,colcount,indexhdr);
            //int comparevalue = strcmp(comparekey,oldKey);
            if(comparevalue == 0){ // Key match found.. replace key
                memcpy(&indexnodedata[position],newKey,keysize);
                return HIT_RETURN;
            }
        }

        position = position + keysize;
    }
}

void IndexNode::insertinindexfirst(const char* key, int leftpagevalue){
    int position=IndexNode::getIndexNodeHeaderSize();
    char dupkeys[getNoOfKeysInIndexNode()][indexhdr->getsizeofkey()];
    int dupPageNumber[getNoOfKeysInIndexNode()+1];

    int count=0;
    for(int value=0;value<getNoOfKeysInIndexNode();value++){
        memcpy(&dupPageNumber[count],&indexnodedata[position],sizeof(int));
        position=position+sizeof(int);
        memcpy(dupkeys[count],&indexnodedata[position],indexhdr->getsizeofkey());
        position=position+indexhdr->getsizeofkey();
        count++;
    }
    memcpy(&dupPageNumber[count],&indexnodedata[position],sizeof(int));
    position=IndexNode::getIndexNodeHeaderSize();

    memcpy(&indexnodedata[position],&leftpagevalue,sizeof(int));
    position=position+sizeof(int);

    memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
    position=position+indexhdr->getsizeofkey();

    for(int val=0;val<count;val++){
        memcpy(&indexnodedata[position],&dupPageNumber[val],sizeof(int));
        position=position+sizeof(int);
        memcpy(&indexnodedata[position],dupkeys[val],indexhdr->getsizeofkey());
        position=position+indexhdr->getsizeofkey();
    }

    memcpy(&indexnodedata[position],&dupPageNumber[count],sizeof(int));
    setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);

    if(getIndexNodeLevel() == 1){
        LeafNode leafNode1(indexhdr,leftpagevalue);
        leafNode1.setparentpagevalue(getPageNumber());
    }else{
        IndexNode indexNode1;
        indexNode1.openindexnodewithindexheader(indexhdr,leftpagevalue);
        indexNode1.setParentofIndexNode(getPageNumber());
    }
}

void IndexNode::insertinindexlast(const char* key, int rightpagevalue){
    int position = IndexNode::getIndexNodeHeaderSize();
    //int lastPage=indexnodelastpage();

    for (int i=0; i<getNoOfKeysInIndexNode(); i++){
        position=position+sizeof(int)+indexhdr->getsizeofkey();
    }

    position=position+sizeof(int);
    memcpy(&indexnodedata[position],key,indexhdr->getsizeofkey());
    position=position+indexhdr->getsizeofkey();
    memcpy(&indexnodedata[position], &rightpagevalue,sizeof(int));
    setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);

    if(getIndexNodeLevel() == 1){
        LeafNode leafNode(indexhdr,rightpagevalue);
        leafNode.setparentpagevalue(getPageNumber());
    }else{
        IndexNode indexNode;
        indexNode.openindexnodewithindexheader(indexhdr,rightpagevalue);
        indexNode.setParentofIndexNode(getPageNumber());
    }
}


//int IndexNode::deleteinindexwithflagset(const char* key, int flag, std::vector<int>& deletedPages){
//    cout<<"In Index Node right now==========";
//    cout<<"The task is to delete the key ========="<<key<<"============="<<endl;
//
//    cout<<"The number of keys in this node"<<getNoOfKeysInIndexNode();
//    // flag is used to identify which side I'm merging
//    // it is TRUE if the left sibling doesn't exist and I'm merging on the right.
//    // that means to say, if it is the first leafnode under the indexnode that I'm trying to merge with the leaf node..
//    int position=IndexNode::getIndexNodeHeaderSize();
//    char duplKey[indexhdr->getsizeofkey()];
//    int leftpageno, rightpageno;
//    int loopcounter;
//    for(loopcounter=0; loopcounter< getNoOfKeysInIndexNode(); loopcounter++){
//        memcpy(&leftpageno,&indexnodedata[position],sizeof(int));
//        position = position + sizeof(int);
//
//        memcpy(duplKey, &indexnodedata[position],indexhdr->getsizeofkey());
//        position = position + indexhdr->getsizeofkey();
//
//        memcpy(&rightpageno,&indexnodedata[position],sizeof(int));
//
//        int comparevalue = BplusTree::keyComp(key,duplKey,indexhdr->getcolcount(),indexhdr);
//        if(comparevalue == 0){
//            break;
//        }
//    }
//    // here loopcounter will have the numberth of key .. in a sense 1st key, 2nd key etc.. match basically..
//    char keyvals[indexhdr->getfanoutoftree()][indexhdr->getsizeofkey()];
//    int duplPagenos[indexhdr->getfanoutoftree() + 1];
//
//    int counterval=0;
//    int positionnew = position;
//
//    for(int j=loopcounter+1; j < getNoOfKeysInIndexNode(); j++){
//        memcpy(&duplPagenos[counterval],&indexnodedata[positionnew],sizeof(int));
//        positionnew=positionnew + sizeof(int);
//
//        memcpy(&keyvals[counterval],&indexnodedata[positionnew],indexhdr->getsizeofkey());
//        positionnew = positionnew + indexhdr->getsizeofkey();
//
//        counterval=counterval+1;
//    }
//    // essentially copying the second half that's all. the pagenumber-key sets after the matched key..
//    // Countervalue essentially says how many key-pagenumber sets  are present after the to be deleted node in the indexnode..
//    memcpy(&duplPagenos[counterval],&indexnodedata[positionnew],sizeof(int));
//    cout<<"Every key and pagenumber value other than the to be deleted key and pagenumber have been"
//            <<"collected into the arrays.. now we'll use the flag value to see if the node is the first leaf or not"
//            <<"Weirdest of bplus tree deletes may be, but gut feeling that it should work, at least it did work on paper"
//            <<endl;
//    cout<<"Now that the initial adjustments are done == just delete the key from the index node==";
//    if(flag == TRUE){
//        position = position - indexhdr->getsizeofkey() - sizeof(int); // restoring to initial position..
//        int arrived=0;
//        // arrived will remain 0 if the following for loop won't get executed
//        // that means to say that the counterval is zero.. that is the number of key-pagenumber sets after the matched record are zero..
//        for(int i=0; i<counterval; i++){ // counterval is the number of keypagenumber sets.. after the matched node..
//            memcpy(&indexnodedata[position],&duplPagenos[i],sizeof(int));
//            position = position + sizeof(int);
//
//            memcpy(&indexnodedata[position],&keyvals[i],indexhdr->getsizeofkey());
//            position = position + indexhdr->getsizeofkey();
//
//            arrived = 1;
//
//            if(i==0){ // It gets executed for only the first time.. din't know how to check, so put off i==0;
//                if(getIndexNodeLevel() == 1){
//                    LeafNode leafNode1(indexhdr,leftpageno);
//                    LeafNode newleafNode(indexhdr,duplPagenos[i]);
//                    newleafNode.setleftpagevalue(leafNode1.getPageNumber());
//
//                    if(leafNode1.getLeftPageNumber() != -1){
//                        LeafNode leftNode(indexhdr,leafNode1.getLeftPageNumber());
//                        leftNode.setrightpagevalue(newleafNode.getPageNumber());
//                    }
//                }else{
//                    IndexNode indexNode1;
//                    indexNode1.openindexnodewithindexheader(indexhdr,leftpageno);
//                    IndexNode newindexNode;
//                    newindexNode.openindexnodewithindexheader(indexhdr,duplPagenos[i]);
//                    newindexNode.setleftpagevalueOfIndexNode(indexNode1.getleftpagevalueOfIndexNode());
//
//                    if(indexNode1.getleftpagevalueOfIndexNode() != -1){
//                        IndexNode oldIndexNoderight;
//                        oldIndexNoderight.openindexnodewithindexheader(indexhdr,indexNode1.getleftpagevalueOfIndexNode());
//                        oldIndexNoderight.setrightpagevalueOfIndexNode(newindexNode.getPageNumber());
//                    }
//                }
//            }
//        }
//
//        memcpy(&indexnodedata[position],&duplPagenos[counterval],sizeof(int));
//        setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
//
//        // The number of keys has to be decreased by a count of 1..
//
//        if(arrived == 0){
//            if(getIndexNodeLevel() == 1){
//                cout<<"The page number that is going to be removed is.. "<<leftpageno;
//                int newpagenumber = duplPagenos[counterval];
//
//                LeafNode leafNode(indexhdr,leftpageno);
//                LeafNode newleafNode(indexhdr,newpagenumber);
//                newleafNode.setleftpagevalue(leafNode.getLeftPageNumber());
//
//                if(leafNode.getLeftPageNumber() != -1){
//                    LeafNode oldrightNode(indexhdr,leafNode.getLeftPageNumber());
//                    oldrightNode.setrightpagevalue(newleafNode.getPageNumber());
//                }
//            }else{
//                IndexNode indexNode1;
//                indexNode1.openindexnodewithindexheader(indexhdr,leftpageno);
//                IndexNode newIndexNode;
//                newIndexNode.openindexnodewithindexheader(indexhdr,duplPagenos[counterval]);
//
//                newIndexNode.setleftpagevalueOfIndexNode(indexNode1.getleftpagevalueOfIndexNode());
//                if(indexNode1.getleftpagevalueOfIndexNode() != -1){
//                    IndexNode oldIndexNode;
//                    oldIndexNode.openindexnodewithindexheader(indexhdr,indexNode1.getleftpagevalueOfIndexNode());
//                    oldIndexNode.setrightpagevalueOfIndexNode(newIndexNode.getPageNumber());
//                }
//            }
//        }
//    }else{
//        /*
//
//                int lastpageposition = IndexNode::getIndexNodeHeaderSize();
//                int valuecount = getNoOfKeysInIndexNode() * (sizeof(int) + indexhdr->getsizeofkey());
//                lastpageposition = lastpageposition + valuecount;
//                int newLastPageno = 0;
//                memcpy(&newLastPageno,&indexnodedata[lastpageposition],sizeof(int));
//
//                duplPagenos[counterval] = newLastPageno;
//*/
//        if(counterval == 0){
//            setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
//
//            if(getIndexNodeLevel() == 1){
//                // Finding out for the last page number..
//
//                int lastpageposition = IndexNode::getIndexNodeHeaderSize();
//                int valuecount = getNoOfKeysInIndexNode() * (sizeof(int) + indexhdr->getsizeofkey());
//                lastpageposition = lastpageposition + valuecount;
//                int newLastPageno = 0;
//                memcpy(&newLastPageno,&indexnodedata[lastpageposition],sizeof(int));
//
//                duplPagenos[counterval] = newLastPageno;
//
//                LeafNode leafNode(indexhdr,rightpageno);
//                LeafNode newleafNode(indexhdr,newLastPageno);
//
//                newleafNode.setrightpagevalue(leafNode.getrightpagevalue());
//
//                if(leafNode.getrightpagevalue() != -1){
//                    LeafNode pageonright(indexhdr,leafNode.getrightpagevalue());
//                    pageonright.setleftpagevalue(newLastPageno);
//                }
//            }else {
//                IndexNode indexNode1;
//                indexNode1.openindexnodewithindexheader(indexhdr,rightpageno);
//
//                // finding the last pagenumber ..
//
//                int lastpageposition1 = sizeof(indexnodestr);
//                int valuecount2 = getNoOfKeysInIndexNode() * (sizeof(int) + indexhdr->getsizeofkey());
//                lastpageposition1 = lastpageposition1 + valuecount2;
//                int newLastPageno = 0;
//                memcpy(&newLastPageno,&indexnodedata[lastpageposition1],sizeof(int));
//
//
//                duplPagenos[counterval] = newLastPageno;
//
//                IndexNode newIndexNode;
//                newIndexNode.openindexnodewithindexheader(indexhdr,newLastPageno);
//                newIndexNode.setrightpagevalueOfIndexNode(indexNode1.getrightpagevalueOfIndexNode());
//
//                if(getNoOfKeysInIndexNode() == 0){
//                    duplPagenos[counterval] = newLastPageno;
//                }
//
//                if(indexNode1.getrightpagevalueOfIndexNode() != -1){
//                    IndexNode oldIndexNode;
//                    oldIndexNode.openindexnodewithindexheader(indexhdr,getrightpagevalueOfIndexNode());
//                    oldIndexNode.setleftpagevalueOfIndexNode(newLastPageno);
//                }
//            }
//        } else {
//            // counterval is not equal to 0 this is! ===
//            /*
//            for(int i=0; i<counterval; i++){
//                memcpy(&indexnodedata[position],&duplPagenos[i],sizeof(int));
//                position = position + sizeof(int);
//                memcpy(&indexnodedata[position],&keyvals[i],indexhdr->getsizeofkey());
//                position = position + indexhdr->getsizeofkey();
//
//             }*/
//            position = position - indexhdr->getsizeofkey();
//            position = position - sizeof(int);
//
//            memcpy(&duplPagenos[0],&indexnodedata[position],sizeof(int));
//
//            for(int i=0; i<counterval; i++){
//                memcpy(&indexnodedata[position],&duplPagenos[i],sizeof(int));
//                position = position + sizeof(int);
//                memcpy(&indexnodedata[position],&keyvals[i],indexhdr->getsizeofkey());
//                position = position + indexhdr->getsizeofkey();
//
//                if(getIndexNodeLevel() == 1){
//                    if(i!=0){
//                        LeafNode leafNode(indexhdr,duplPagenos[i - 1]);
//                        LeafNode newleafNode(indexhdr,duplPagenos[i]);
//
//                        newleafNode.setleftpagevalue(leafNode.getPageNumber());
//                        newleafNode.setrightpagevalue(duplPagenos [i +1]);
//                    }else{
//                        LeafNode leafNode(indexhdr,duplPagenos[i]);
//                        leafNode.setrightpagevalue(duplPagenos[i + 1]);
//                    }
//                } else{
//                    //IndexNode newIndexNode;
//                    //newIndexNode.openindexnodewithindexheader(indexhdr,duplPagenos[i]);
//                    if(i!=0){
//                        IndexNode indexNode;
//                        indexNode.openindexnodewithindexheader(indexhdr,duplPagenos[i - 1]);
//                        IndexNode newIndexNode;
//                        newIndexNode.openindexnodewithindexheader(indexhdr,duplPagenos[i]);
//
//                        newIndexNode.setleftpagevalueOfIndexNode(indexNode.getPageNumber());
//                        newIndexNode.setrightpagevalueOfIndexNode(duplPagenos [i + 1]);
//                    }else{
//                        IndexNode indexNode;
//                        indexNode.openindexnodewithindexheader(indexhdr,duplPagenos[i]);
//                        indexNode.setrightpagevalueOfIndexNode(duplPagenos[i + 1]);
//                    }
//                }
//            }
//
//            memcpy(&indexnodedata[position],&duplPagenos[counterval],sizeof(int));
//            setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
//
//
//            if(getIndexNodeLevel() == 1){
//                LeafNode leafNode(indexhdr,duplPagenos[counterval]);
//                leafNode.setleftpagevalue(duplPagenos[counterval - 1]);
//            }else{
//                IndexNode indexNode;
//                indexNode.openindexnodewithindexheader(indexhdr,duplPagenos[counterval]);
//                indexNode.setleftpagevalueOfIndexNode(duplPagenos[counterval - 1]);
//            }
//            // ================The execution block for flag == FALSE ends here..----------=====
//        }
//    }
//
//    if(getNoOfKeysInIndexNode() == 0){
//        cout<<"The number of childs in this page is equal to 0"
//                <<"Hence delete this page.. and.. "
//                <<"make it's child as the root.."<<endl;
//
//        deletedPages.push_back(getPageNumber());
//
//        if(getIndexNodeLevel() == 1){
//            indexhdr->setpagenumberofroot(duplPagenos[counterval]);
//            LeafNode leafNode1(indexhdr,duplPagenos[counterval]);
//            leafNode1.setparentpagevalue(-1);
//            indexhdr->settreeheight(0);
//        }else{
//            indexhdr->setpagenumberofroot(duplPagenos[counterval]);
//            IndexNode indexNode1;
//            indexNode1.openindexnodewithindexheader(indexhdr,duplPagenos[counterval]);
//            indexNode1.setParentofIndexNode(-1);
//            indexhdr->settreeheight(indexNode1.getIndexNodeLevel());
//        }
//        return HIT_RETURN;
//    }
//
//    //=======================The deletion operation has been complete=======================
//    //===================Now, there will be checking for if the tree  will have to be merged
//    // ====================Or it has to be shiftingd.. ====== or just do nothing
//    // The pain in the ass part begins here... god be with me, till I finish it! thank you!
//    float ceilvalue = (double)(indexhdr->getfanoutoftree() / 2);
//    if(getNoOfKeysInIndexNode() >= ceil(ceilvalue)){
//        cout<<"It's fine, there are nodes till fill out factor.. "<<endl;
//    }else{
//        cout<<"Merging or rotation in b+ tree should happen. check left page and right page for that"<<endl;
//        int righter = -1;
//        int lefter = -1;
//
//        if(getParentofIndexNode() != -1){
//            IndexNode newNode;
//            newNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());// newnode is the Parentnode..
//            newNode.getleftandrightpagevaluestothegivenpagenumber(getPageNumber(),lefter,righter);
//            cout<<"Dummmmmmmmmmmer========================"<<endl;
//        }
//
//        cout<<"Right Page Number =========== "<<righter
//                <<"Left Page Number ============"<<lefter<<endl;
//
//        if(righter != -1){
//            cout<<"Checking for a possibility to shifting the right page.. "<<endl;
//
//            IndexNode rightIndexNode;
//            rightIndexNode.openindexnodewithindexheader(indexhdr,righter);
//            double celiedvalue = (double)(indexhdr->getfanoutoftree() / 2);
//            if((rightIndexNode.getNoOfKeysInIndexNode() - 1)>= ceil(celiedvalue)){
//                cout<<"The rightpage has more than half of the keys.. "
//                        <<"So shifting or move keys from the right page.. "<<endl;
//
//                char keyblocker[indexhdr->getsizeofkey()];
//                char firstKeyonright[indexhdr->getsizeofkey()];
//
//                rightIndexNode.getthekeyatthefrontofindexnode(firstKeyonright);
//
//                int shiftingpgno;
//
//                shiftingpgno=rightIndexNode.indexnodefirstpage();
//
//                if(getParentofIndexNode()!=-1){
//                    IndexNode parentIndexNode;
//                    parentIndexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                    parentIndexNode.getpagenumberbetweenleftpageandrightpage(getPageNumber(),righter,keyblocker);
//
//                    // inserting the keyblocker at the end of indexnode
//
//                    int insertposition = IndexNode::getIndexNodeHeaderSize();
//
//                    for(int dummylooper=0; dummylooper<getNoOfKeysInIndexNode(); dummylooper++){
//                        insertposition = insertposition + sizeof(int);
//                        insertposition = insertposition + indexhdr->getsizeofkey();
//                    }
//                    /*
//                   if(getIndexNodeLevel() == 1){
//                        LeafNode shiftingLeafNode(indexhdr,shiftingpgno);
//                        shiftingLeafNode.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode shiftingIndexNode;
//                        shiftingIndexNode.openindexnodewithindexheader(indexhdr,shiftingpgno);
//                        shiftingIndexNode.setParentofIndexNode(getPageNumber());
//                    }
//
//                    cout<<"Left most keys in the right node has to be pushed to the parent node.. "<<endl;
//                    parentIndexNode.keyshift(keyblocker,firstKeyonright);
//                    rightIndexNode.removethekeyatthefrontofindexnode(); // The key has to be deleted after it has been moved to the parent..
//                }*/
//
//                    insertposition = insertposition + sizeof(int); // have to insert here..
//
//                    memcpy(&indexnodedata[insertposition],keyblocker,indexhdr->getsizeofkey());
//                    insertposition = insertposition + indexhdr->getsizeofkey();
//                    memcpy(&indexnodedata[insertposition],&shiftingpgno,sizeof(int));
//                    int setkeyvalue = getNoOfKeysInIndexNode() + 1;
//                    setNoOfKeysInIndexNode(setkeyvalue);
//
//                    int leveldupl = getIndexNodeLevel();
//                    if(leveldupl == 1){
//                        LeafNode leafnode1(indexhdr,shiftingpgno);
//                        leafnode1.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode indexnode1;
//                        indexnode1.openindexnodewithindexheader(indexhdr,shiftingpgno);
//                        indexnode1.setParentofIndexNode(shiftingpgno);
//                    }
//
//                    // --- inserting at the end of indexnode done..
//                    if(getIndexNodeLevel() == 1){
//                        LeafNode shiftingLeafNode(indexhdr,shiftingpgno);
//                        shiftingLeafNode.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode shiftingIndexNode;
//                        shiftingIndexNode.openindexnodewithindexheader(indexhdr,shiftingpgno);
//                        shiftingIndexNode.setParentofIndexNode(getPageNumber());
//                    }
//
//                    cout<<"Left most keys in the right node has to be pushed to the parent node.. "<<endl;
//                   // parentIndexNode.keyshift(keyblocker,key);
//                    //rightIndexNode.removethekeyattheendofindexnode();
//                    parentIndexNode.keyshift(keyblocker,firstKeyonright);
//                    rightIndexNode.removethekeyatthefrontofindexnode(); // The key has to be deleted after it has been moved to the parent..
//                }
//            }else if (lefter != -1){
//                cout<<"Left page is available but not right.. so shifting the keys left page only.. ======="<<endl;
//                IndexNode leftIndexNode;
//                leftIndexNode.openindexnodewithindexheader(indexhdr,lefter);
//
//                if((leftIndexNode.getNoOfKeysInIndexNode() - 1)>= ceil(indexhdr->getfanoutoftree() / 2)){
//                    char keyblocker[indexhdr->getsizeofkey()];
//                    char lastkeyinleft[indexhdr->getsizeofkey()];
//                    leftIndexNode.getthekeyattheendofindexnode(lastkeyinleft);
//                    int shiftingpageno;
//
//                    shiftingpageno=leftIndexNode.indexnodelastpage();
//
//                    if(getParentofIndexNode() != -1){
//                        //int firstinsertposition = IndexNode::getIndexNodeHeaderSize();
//                        //char firstkeyset[getNoOfKeysInIndexNode()][indexhdr->getsizeofkey()];
//                        //int firstpagenumberset[getNoOfKeysInIndexNode()+1];
//                        IndexNode parentIndexNode;
//                        parentIndexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                        parentIndexNode.getpagenumberbetweenleftpageandrightpage(lefter,getPageNumber(),keyblocker);
//                        parentIndexNode.keyshift(keyblocker,lastkeyinleft);
//                    }
//
//                    // Insert the keyblocker with shiftingpageno at the beginning of the index node==========================
//                    int firstinsertposition = IndexNode::getIndexNodeHeaderSize();
//                    char firstkeyset[getNoOfKeysInIndexNode()][indexhdr->getsizeofkey()];
//                    int firstpagenumberset[getNoOfKeysInIndexNode()+1];
//
//                    int firstcounter=0;
//                    for(int valuefirst=0; valuefirst<getNoOfKeysInIndexNode(); valuefirst++){
//                        memcpy(&firstpagenumberset[firstcounter],&indexnodedata[firstinsertposition],sizeof(int));
//                        firstinsertposition = firstinsertposition + sizeof(int);
//                        memcpy(&firstkeyset[firstcounter],&indexnodedata[firstinsertposition],indexhdr->getsizeofkey());
//                        firstinsertposition = firstinsertposition + indexhdr->getsizeofkey();
//                        firstcounter = firstcounter + 1;
//                    }
//
//                    memcpy(&firstpagenumberset[firstcounter],&indexnodedata[firstinsertposition],sizeof(int));
//                    firstinsertposition = sizeof(indexnodestr);
//
//                    memcpy(&indexnodedata[firstinsertposition],&shiftingpageno,sizeof(int));
//                    firstinsertposition = firstinsertposition + sizeof(int);
//
//                    memcpy(&indexnodedata[firstinsertposition],keyblocker,indexhdr->getsizeofkey());
//                    firstinsertposition = firstinsertposition + indexhdr->getsizeofkey();
//
//                    for(int val=0; val<firstcounter; val++){
//                        memcpy(&indexnodedata[firstinsertposition],&firstpagenumberset[val],sizeof(int));
//                        firstinsertposition = firstinsertposition + sizeof(int);
//                        memcpy(&indexnodedata[firstinsertposition],firstkeyset[val],indexhdr->getsizeofkey());
//                        firstinsertposition = firstinsertposition + indexhdr->getsizeofkey();
//                    }
//
//                    memcpy(&indexnodedata[firstinsertposition],&firstpagenumberset[firstcounter],sizeof(int));
//                    setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);
//
//                    if(getIndexNodeLevel() == 1){
//                        LeafNode leafnode33(indexhdr,shiftingpageno);
//                        leafnode33.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode indexnode33;
//                        indexnode33.openindexnodewithindexheader(indexhdr,shiftingpageno);
//                        indexnode33.setParentofIndexNode(getPageNumber());
//                    }
//                    // Insertion at the beginning done.. ===========================================
//                    if(getIndexNodeLevel() == 1){
//                        LeafNode shiftingleafNode(indexhdr,shiftingpageno);
//                        shiftingleafNode.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode shiftingIndexNode;
//                        shiftingIndexNode.openindexnodewithindexheader(indexhdr,shiftingpageno);
//                        shiftingIndexNode.setParentofIndexNode(getPageNumber());
//                    }
//                }else{
//                    int newkeycount1 = getNoOfKeysInIndexNode();
//                    newkeycount1 = newkeycount1 - 1;
//                    setNoOfKeysInIndexNode(newkeycount1);
//                    // Deletion and rotation end here.. and we are merging it here first..
//                    cout<<"Rotation and deletion are done.. it is found that none of the pages have enough space.. "
//                            <<"so merge them!"<<endl;
//
//                    cout<<"Merging them with the right page number=============="<<endl;
//
//                    deletedPages.push_back(getPageNumber());
//
//                    char keyblock[indexhdr->getsizeofkey()];
//                    if(getParentofIndexNode()!=-1){
//                        IndexNode parentNewNode;
//                        parentNewNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                        parentNewNode.getpagenumberbetweenleftpageandrightpage(getPageNumber(),getrightpagevalueOfIndexNode(),keyblock);
//                    }
//
//                    int pagenumberoftheattachedpage;
//                    pagenumberoftheattachedpage=rightIndexNode.indexnodefirstpage();
//
//                    char keyvals[getNoOfKeysInIndexNode() + 1][indexhdr->getsizeofkey()];
//                    int duplPagenos[getNoOfKeysInIndexNode() + 1];
//                    int counterval=0;
//                    int position = IndexNode::getIndexNodeHeaderSize();
//                    cout<<"Moving all the keys from the right node to the current node ==="<<endl;
//
//                    cout<<"Deleting current Node along with it ==="<<endl;
//
//                    for(int i=0; i<getNoOfKeysInIndexNode(); i++){
//                        memcpy(&duplPagenos[counterval],&indexnodedata[position],sizeof(int));
//                        position = position + sizeof(int);
//                        memcpy(keyvals[counterval],&indexnodedata[position],indexhdr->getsizeofkey());
//                        position = position + indexhdr->getsizeofkey();
//                        counterval = counterval + 1;
//                    }
//
//                    memcpy(&duplPagenos[counterval],&indexnodedata[position],sizeof(int));
//                    memcpy(keyvals[counterval],keyblock,indexhdr->getsizeofkey());
//
//               for(int i=counterval; i>=0; i--){
//                        // insert keyvals[i] and duplpagenos[i] at the beginnning of indexnodes continuously in this loop
//                        // the insertion process begins here ===============================
//		    int firstinsertposition1 = IndexNode::getIndexNodeHeaderSize();
//                    char firstkeyset1[getNoOfKeysInIndexNode()][indexhdr->getsizeofkey()];
//                    int firstpagenumberset1[getNoOfKeysInIndexNode()+1];
//
//                    int firstcounter1=0;
//                    for(int valuefirst1=0; valuefirst1<getNoOfKeysInIndexNode(); valuefirst1++){
//                        memcpy(&firstpagenumberset1[firstcounter1],&indexnodedata[firstinsertposition1],sizeof(int));
//                        firstinsertposition1 = firstinsertposition1 + sizeof(int);
//                        memcpy(&firstkeyset1[firstcounter1],&indexnodedata[firstinsertposition1],indexhdr->getsizeofkey());
//                        firstinsertposition1 = firstinsertposition1 + indexhdr->getsizeofkey();
//                        firstcounter1 = firstcounter1 + 1;
//                    }
//
//                    memcpy(&firstpagenumberset1[firstcounter1],&indexnodedata[firstinsertposition1],sizeof(int));
//                    firstinsertposition1 = sizeof(indexnodestr);
//
//                    memcpy(&indexnodedata[firstinsertposition1],&duplPagenos[i],sizeof(int));
//                    firstinsertposition1 = firstinsertposition1 + sizeof(int);
//
//                    memcpy(&indexnodedata[firstinsertposition1],keyvals[i],indexhdr->getsizeofkey());
//                    firstinsertposition1 = firstinsertposition1 + indexhdr->getsizeofkey();
//
//                    for(int val1=0; val1<firstcounter1; val1++){
//                        memcpy(&indexnodedata[firstinsertposition1],&firstpagenumberset1[val1],sizeof(int));
//                        firstinsertposition1 = firstinsertposition1 + sizeof(int);
//                        memcpy(&indexnodedata[firstinsertposition1],firstkeyset1[val1],indexhdr->getsizeofkey());
//                        firstinsertposition1 = firstinsertposition1 + indexhdr->getsizeofkey();
//                    }
//
//                    memcpy(&indexnodedata[firstinsertposition1],&firstpagenumberset1[firstcounter1],sizeof(int));
//                    setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);
//
//                    if(getIndexNodeLevel() == 1){
//                        LeafNode leafnode44(indexhdr,duplPagenos[i]);
//                        leafnode44.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode indexnode44;
//                        indexnode44.openindexnodewithindexheader(indexhdr,duplPagenos[i]);
//                        indexnode44.setParentofIndexNode(getPageNumber());
//                    }
//
//                        // the insertion process ends her e============================
//
//              }
//                    if(getParentofIndexNode() != -1){
//                        IndexNode parentNode;
//                        parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                        parentNode.deleteinindexwithflagset(keyblock,TRUE,deletedPages);
//                    }
//                }
//            }else{
//                // do merging with right page here..
//                cout<<"Left page doesn't exist == hence merging with right page.. "<<endl;
//
//                deletedPages.push_back(getPageNumber());
//
//                char keyblock[indexhdr->getsizeofkey()];
//
//                if(getParentofIndexNode() != -1){
//                    IndexNode parentNode;
//                    parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                    parentNode.getpagenumberbetweenleftpageandrightpage(getPageNumber(),getrightpagevalueOfIndexNode(),keyblock);
//                }
//
//                int shiftingpageno;
//                shiftingpageno =rightIndexNode.indexnodefirstpage();
//                char keyvals[getNoOfKeysInIndexNode() + 1][indexhdr->getsizeofkey()];
//                int duplPagenos[getNoOfKeysInIndexNode() + 1];
//                int counterval=0;
//                int position = IndexNode::getIndexNodeHeaderSize();
//
//                cout<<"Moving all keys from current node to the right node.. "<<endl;
//                for(int i=0; i<getNoOfKeysInIndexNode(); i++){
//                   memcpy(&duplPagenos[counterval],&indexnodedata[position],sizeof(int));
//                   position = position + sizeof(int);
//                   memcpy(keyvals[counterval],&indexnodedata[position],indexhdr->getsizeofkey());
//                   position = position + indexhdr->getsizeofkey();
//                   counterval = counterval + 1;
//                }
//                    memcpy(&duplPagenos[counterval],&indexnodedata[position],sizeof(int));
//                    memcpy(keyvals[counterval],keyblock,indexhdr->getsizeofkey());
//
//                    //for(int valuefirst2=0; valuefirst2<getNoOfKeysInIndexNode(); valuefirst2++){
//                      //  memcpy(&firstpagenumberset2[firstcounter2],&indexnodedata[firstinsertposition2],sizeof(int));
//                       // firstinsertposition2 = firstinsertposition2 + sizeof(int);
//                       // memcpy(&firstkeyset2[firstcounter2],&indexnodedata[firstinsertposition2],indexhdr->getsizeofkey());
//                       // firstinsertposition2 = firstinsertposition2 + indexhdr->getsizeofkey();
//                       // firstcounter2 = firstcounter2 + 2;
//                    //}
//               for(int i=counterval; i>=0; i--){
//                        // inserting all the value in the indexnode - insertatfirst procedure
//                    int firstinsertposition2 = IndexNode::getIndexNodeHeaderSize();
//                    char firstkeyset2[getNoOfKeysInIndexNode()][indexhdr->getsizeofkey()];
//                    int firstpagenumberset2[getNoOfKeysInIndexNode()+2];
//
//                    int firstcounter2=0;
//
//                    for(int valuefirst2=0; valuefirst2<getNoOfKeysInIndexNode(); valuefirst2++){
//                        memcpy(&firstpagenumberset2[firstcounter2],&indexnodedata[firstinsertposition2],sizeof(int));
//                        firstinsertposition2 = firstinsertposition2 + sizeof(int);
//                        memcpy(&firstkeyset2[firstcounter2],&indexnodedata[firstinsertposition2],indexhdr->getsizeofkey());
//                        firstinsertposition2 = firstinsertposition2 + indexhdr->getsizeofkey();
//                        firstcounter2 = firstcounter2 + 2;
//                    }
//
//                    memcpy(&firstpagenumberset2[firstcounter2],&indexnodedata[firstinsertposition2],sizeof(int));
//                    firstinsertposition2 = sizeof(indexnodestr);
//
//                    memcpy(&indexnodedata[firstinsertposition2],&duplPagenos[i],sizeof(int));
//                    firstinsertposition2 = firstinsertposition2 + sizeof(int);
//
//                    memcpy(&indexnodedata[firstinsertposition2],keyvals[i],indexhdr->getsizeofkey());
//                    firstinsertposition2 = firstinsertposition2 + indexhdr->getsizeofkey();
//
//                    for(int val2=0; val2<firstcounter2; val2++){
//                        memcpy(&indexnodedata[firstinsertposition2],&firstpagenumberset2[val2],sizeof(int));
//                        firstinsertposition2 = firstinsertposition2 + sizeof(int);
//                        memcpy(&indexnodedata[firstinsertposition2],firstkeyset2[val2],indexhdr->getsizeofkey());
//                        firstinsertposition2 = firstinsertposition2 + indexhdr->getsizeofkey();
//                    }
//
//                    memcpy(&indexnodedata[firstinsertposition2],&firstpagenumberset2[firstcounter2],sizeof(int));
//                    setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 2);
//
//                    if(getIndexNodeLevel() == 1){
//                        LeafNode leafnode55(indexhdr,duplPagenos[i]);
//                        leafnode55.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode indexnode55;
//                        indexnode55.openindexnodewithindexheader(indexhdr,duplPagenos[i]);
//                        indexnode55.setParentofIndexNode(getPageNumber());
//                    }
//                        // ------------ insertion of values done!
//
//               }
//                    if(getParentofIndexNode() != -1){
//                        IndexNode parentNode;
//                        parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                        parentNode.deleteinindexwithflagset(keyblock,TRUE,deletedPages);
//                    }                  // Merging is done here..
//            }
//        }else if(lefter != -1){
//            cout<<"Checking left page values == = ";
//            IndexNode indexNodeleft;
//            indexNodeleft.openindexnodewithindexheader(indexhdr,lefter);
//            if((indexNodeleft.getNoOfKeysInIndexNode() - 1) >= ceil(indexhdr->getfanoutoftree() /2 )){
//                cout<<"Left page has more number of keys so shifting keys from left page"<<endl;
//                char keyblock[indexhdr->getsizeofkey()];
//                char lastkeyinLeaf[indexhdr->getsizeofkey()];
//
//                indexNodeleft.getthekeyattheendofindexnode(lastkeyinLeaf);
//                int shiftingpageno;
//                shiftingpageno = indexNodeleft.indexnodelastpage();
//
//                if(getParentofIndexNode() != -1){
//                    IndexNode parentnewNode;
//                    parentnewNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                    parentnewNode.getpagenumberbetweenleftpageandrightpage(lefter,getPageNumber(),keyblock);
//                    cout<<"Seperating key is === "<<keyblock;
//                    parentnewNode.keyshift(keyblock,lastkeyinLeaf);
//                }
//
//                // Inserting keyblock and shiftingpagenumber at the beginning of the indexnode
//                    		    int firstinsertposition3 = IndexNode::getIndexNodeHeaderSize();
//                    char firstkeyset3[getNoOfKeysInIndexNode()][indexhdr->getsizeofkey()];
//                    int firstpagenumberset3[getNoOfKeysInIndexNode()+3];
//
//                    int firstcounter3=0;
//                    for(int valuefirst3=0; valuefirst3<getNoOfKeysInIndexNode(); valuefirst3++){
//                        memcpy(&firstpagenumberset3[firstcounter3],&indexnodedata[firstinsertposition3],sizeof(int));
//                        firstinsertposition3 = firstinsertposition3 + sizeof(int);
//                        memcpy(&firstkeyset3[firstcounter3],&indexnodedata[firstinsertposition3],indexhdr->getsizeofkey());
//                        firstinsertposition3 = firstinsertposition3 + indexhdr->getsizeofkey();
//                        firstcounter3 = firstcounter3 + 3;
//                    }
//
//                    memcpy(&firstpagenumberset3[firstcounter3],&indexnodedata[firstinsertposition3],sizeof(int));
//                    firstinsertposition3 = sizeof(indexnodestr);
//
//                    memcpy(&indexnodedata[firstinsertposition3],&shiftingpageno,sizeof(int));
//                    firstinsertposition3 = firstinsertposition3 + sizeof(int);
//
//                    memcpy(&indexnodedata[firstinsertposition3],keyblock,indexhdr->getsizeofkey());
//                    firstinsertposition3 = firstinsertposition3 + indexhdr->getsizeofkey();
//
//                    for(int val3=0; val3<firstcounter3; val3++){
//                        memcpy(&indexnodedata[firstinsertposition3],&firstpagenumberset3[val3],sizeof(int));
//                        firstinsertposition3 = firstinsertposition3 + sizeof(int);
//                        memcpy(&indexnodedata[firstinsertposition3],firstkeyset3[val3],indexhdr->getsizeofkey());
//                        firstinsertposition3 = firstinsertposition3 + indexhdr->getsizeofkey();
//                    }
//
//                    memcpy(&indexnodedata[firstinsertposition3],&firstpagenumberset3[firstcounter3],sizeof(int));
//                    setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 3);
//
//                    if(getIndexNodeLevel() == 1){
//                        LeafNode leafnodeRIDSIZERIDSIZE(indexhdr,shiftingpageno);
//                        leafnodeRIDSIZERIDSIZE.setparentpagevalue(getPageNumber());
//                    }else{
//                        IndexNode indexnodeRIDSIZERIDSIZE;
//                        indexnodeRIDSIZERIDSIZE.openindexnodewithindexheader(indexhdr,shiftingpageno);
//                        indexnodeRIDSIZERIDSIZE.setParentofIndexNode(getPageNumber());
//                    }
//
//                // Insertion at the beginning done!
//
//                if(getIndexNodeLevel()== 1){
//                    LeafNode shiftingleafNode(indexhdr,shiftingpageno);
//                    shiftingleafNode.setparentpagevalue(getPageNumber());
//                }else{
//                    IndexNode shiftingIndexNode;
//                    shiftingIndexNode.openindexnodewithindexheader(indexhdr,shiftingpageno);
//                    shiftingIndexNode.setParentofIndexNode(getPageNumber());
//                }
//
//                indexNodeleft.setNoOfKeysInIndexNode(indexNodeleft.getNoOfKeysInIndexNode() - 1); // remove
//            }else{
//                cout<<"Left page doesn't have enough number of keys ====="
//                        <<"So merge with left page number ====="
//                        <<endl;
//                deletedPages.push_back(getPageNumber());
//
//                char Keyblock[indexhdr->getsizeofkey()];
//
//                if(getParentofIndexNode() != -1){
//                    IndexNode parentIndexNode;
//                    parentIndexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                    parentIndexNode.getpagenumberbetweenleftpageandrightpage(getleftpagevalueOfIndexNode(),getPageNumber(),Keyblock);
//                }
//
//                // Finding the first page in indexnode
//                int indexnodefirstpageposition = 0;
//                indexnodefirstpageposition = indexnodefirstpageposition + sizeof(indexnodestr);
//                int shiftingpageno = 0;
//                memcpy(&shiftingpageno,&indexnodedata[indexnodefirstpageposition],sizeof(int));
//
//
//                char keyvals[getNoOfKeysInIndexNode() + 1][indexhdr->getsizeofkey()];
//                int duplPagenos[getNoOfKeysInIndexNode() + 1];
//                int counterval=0;
//                int position = IndexNode::getIndexNodeHeaderSize();
//                memcpy(keyvals[counterval],Keyblock,indexhdr->getsizeofkey());
//
//                cout<<"Moving all keys from current node into left node==="<<endl;
//                for(int i=0; i<getNoOfKeysInIndexNode(); i++){
//                   memcpy(&duplPagenos[counterval],&indexnodedata[position],sizeof(int));
//                   position = position + sizeof(int);
//                   memcpy(keyvals[counterval],&indexnodedata[position],indexhdr->getsizeofkey());
//                   position = position + indexhdr->getsizeofkey();
//                   counterval = counterval + 1;
//                }
//                    memcpy(&duplPagenos[counterval],&indexnodedata[position],sizeof(int));
//
//                    // inserting keyblock at the end of indexnode..
//                       int insertposition2 = sizeof(indexnodestr);
//                     //int lastPage=indexnodelastpage();
//
//                        for (int i=0; i<getNoOfKeysInIndexNode(); i++){
//                                insertposition2=insertposition2+sizeof(int)+indexhdr->getsizeofkey();
//                         }
//
//                        insertposition2=insertposition2+sizeof(int);
//                        memcpy(&indexnodedata[insertposition2],Keyblock,indexhdr->getsizeofkey());
//                        insertposition2=insertposition2+indexhdr->getsizeofkey();
//                        memcpy(&indexnodedata[insertposition2], &duplPagenos[0],sizeof(int));
//                        setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);
//
//                         if(getIndexNodeLevel() == 1){
//                         LeafNode leafNode11(indexhdr,duplPagenos[0]);
//                          leafNode11.setparentpagevalue(getPageNumber());
//                         }else{
//                         IndexNode indexNode11;
//                         indexNode11.openindexnodewithindexheader(indexhdr,duplPagenos[0]);
//                          indexNode11.setParentofIndexNode(getPageNumber());
//                         }
//                    // -- insertion at the end is done..
//                    for(int i=0; i<counterval; i++){
//                        // start inserting at the end of indexnode
//                        int insertposition3 = sizeof(indexnodestr);
//
//                        for(int counter2=0; counter2<getNoOfKeysInIndexNode(); counter2++){
//                            insertposition3 = insertposition3 + sizeof(int);
//                            memcpy(&indexnodedata[insertposition3],keyvals[i],indexhdr->getsizeofkey());
//
//                            insertposition3 = insertposition3 + indexhdr->getsizeofkey();
//                            memcpy(&indexnodedata[insertposition3],&duplPagenos[i+1],sizeof(int));
//                            setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);
//
//                            if(getIndexNodeLevel() ==1){
//                                LeafNode leafnode22(indexhdr,duplPagenos[i+1]);
//                                leafnode22.setparentpagevalue(getPageNumber());
//                            }else{
//                                IndexNode indexnode22;
//                                indexnode22.openindexnodewithindexheader(indexhdr,duplPagenos[i+1]);
//                                indexnode22.setParentofIndexNode(getPageNumber());
//                            }
//                        }
//                    }
//                        // === Insertion at the end of the indexnode is done.. basically a push back this is!
//
//                    if(getParentofIndexNode() != -1){
//                        IndexNode parentNode;
//                        parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
//                        parentNode.deleteinindexwithflagset(Keyblock,FALSE,deletedPages);
//                    }
//
//                    cout<<"Merging H[IT]opefully done!===:P:P:P == Such a pain in ass..best bit of programming I have done this is..sigh!"
//                            <<"If god has been with me, I would see this line again - Meaning, the function has been HIT_RETURNfully executed.. Oh god bless me!"<<endl;
//
//            }
//        }
//
//    }
//    return HIT_RETURN;
//}

int IndexNode::deleteinindexwithflagset(const char* key, int flag, std::vector<int>& deletedPages){
    //cout<<"In Index Node right now==========";
    //cout<<"The task is to delete the key ========="<<key<<"============="<<endl;

    //cout<<"The number of keys in this node"<<getNoOfKeysInIndexNode();

    int position=IndexNode::getIndexNodeHeaderSize();
    char dupKey[indexhdr->getsizeofkey()];
    int leftpageno, rightpageno;
    int loopcounter;
    for(loopcounter=0; loopcounter< getNoOfKeysInIndexNode(); loopcounter++){
        memcpy(&leftpageno,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);

        memcpy(dupKey, &indexnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();

        memcpy(&rightpageno,&indexnodedata[position],sizeof(int));

        int comparevalue = BplusTree::keyComp(key,dupKey,indexhdr->getcolcount(),indexhdr);
        if(comparevalue == 0){
            break;
        }
    }
    char dupKeys[indexhdr->getfanoutoftree()][indexhdr->getsizeofkey()];
    int dupPagenos[indexhdr->getfanoutoftree() + 1];

    int dupCount=0;
    int positionnew = position;

    for(int j=loopcounter+1; j < getNoOfKeysInIndexNode(); j++){
        memcpy(&dupPagenos[dupCount],&indexnodedata[positionnew],sizeof(int));
        positionnew=positionnew + sizeof(int);

        memcpy(&dupKeys[dupCount],&indexnodedata[positionnew],indexhdr->getsizeofkey());
        positionnew = positionnew + indexhdr->getsizeofkey();

        dupCount=dupCount+1;
    }

    memcpy(&dupPagenos[dupCount],&indexnodedata[positionnew],sizeof(int));

    //cout<<"Now that the initial adjustments are done == just delete the key from the index node==";
    if(flag == TRUE){
        position = position - indexhdr->getsizeofkey() - sizeof(int); // restoring to initial position..
        int arrived=0;
        for(int i=0; i<dupCount; i++){
            memcpy(&indexnodedata[position],&dupPagenos[i],sizeof(int));
            position = position + sizeof(int);

            memcpy(&indexnodedata[position],&dupKeys[i],indexhdr->getsizeofkey());
            position = position + indexhdr->getsizeofkey();

            arrived = 1;

            if(i==0){
                if(getIndexNodeLevel() == 1){
                    LeafNode leafNode1(indexhdr,leftpageno);
                    LeafNode newleafNode(indexhdr,dupPagenos[i]);
                    newleafNode.setleftpagevalue(leafNode1.getPageNumber());


                    if(leafNode1.getLeftPageNumber() != -1){
                        LeafNode oldrightNode(indexhdr,leafNode1.getLeftPageNumber());
                        oldrightNode.setrightpagevalue(newleafNode.getPageNumber());
                    }
                }else{
                    IndexNode indexNode1;
                    indexNode1.openindexnodewithindexheader(indexhdr,leftpageno);
                    IndexNode newindexNode;
                    newindexNode.openindexnodewithindexheader(indexhdr,dupPagenos[i]);
                    newindexNode.setleftpagevalueOfIndexNode(indexNode1.getleftpagevalueOfIndexNode());

                    if(indexNode1.getleftpagevalueOfIndexNode() != -1){
                        IndexNode oldIndexNoderight;
                        oldIndexNoderight.openindexnodewithindexheader(indexhdr,indexNode1.getleftpagevalueOfIndexNode());
                        oldIndexNoderight.setrightpagevalueOfIndexNode(newindexNode.getPageNumber());
                    }
                }
            }
        }

        memcpy(&indexnodedata[position],&dupPagenos[dupCount],sizeof(int));
        setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);

        // The number of keys has to be decreased by a count of 1..

        if(arrived == 0){
            if(getIndexNodeLevel() == 1){
              //  cout<<"The page number that is going to be removed is.. "<<leftpageno;
                int newpagenumber = dupPagenos[dupCount];

                LeafNode leafNode(indexhdr,leftpageno);
                LeafNode newleafNode(indexhdr,newpagenumber);
                newleafNode.setleftpagevalue(leafNode.getLeftPageNumber());

                if(leafNode.getLeftPageNumber() != -1){
                    LeafNode oldrightNode(indexhdr,leafNode.getLeftPageNumber());
                    oldrightNode.setrightpagevalue(newleafNode.getPageNumber());
                }
            }else{
                IndexNode indexNode1;
                indexNode1.openindexnodewithindexheader(indexhdr,leftpageno);
                IndexNode newIndexNode;
                newIndexNode.openindexnodewithindexheader(indexhdr,dupPagenos[dupCount]);

                newIndexNode.setleftpagevalueOfIndexNode(indexNode1.getleftpagevalueOfIndexNode());
                if(indexNode1.getleftpagevalueOfIndexNode() != -1){
                    IndexNode oldIndexNode;
                    oldIndexNode.openindexnodewithindexheader(indexhdr,indexNode1.getleftpagevalueOfIndexNode());
                    oldIndexNode.setrightpagevalueOfIndexNode(newIndexNode.getPageNumber());
                }
            }
        }
    }else{
        if(dupCount == 0){
            setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);

            if(getIndexNodeLevel() == 1){
                // Finding out for the last page number..
                int newLastPageno = indexnodelastpage();
                dupPagenos[dupCount] = newLastPageno;

                LeafNode leafNode(indexhdr,rightpageno);
                LeafNode newleafNode(indexhdr,newLastPageno);

                newleafNode.setrightpagevalue(leafNode.getrightpagevalue());

                if(leafNode.getrightpagevalue() != -1){
                    LeafNode pageonright(indexhdr,leafNode.getrightpagevalue());
                    pageonright.setleftpagevalue(newLastPageno);
                }
            }else {
                IndexNode indexNode1;
                indexNode1.openindexnodewithindexheader(indexhdr,rightpageno);
                int newLastPageno = indexnodelastpage();
                dupPagenos[dupCount] = newLastPageno;

                IndexNode newIndexNode;
                newIndexNode.openindexnodewithindexheader(indexhdr,newLastPageno);
                newIndexNode.setrightpagevalueOfIndexNode(indexNode1.getrightpagevalueOfIndexNode());

                if(getNoOfKeysInIndexNode() == 0){
                    dupPagenos[dupCount] = newLastPageno;
                }

                if(indexNode1.getrightpagevalueOfIndexNode() != -1){
                    IndexNode oldIndexNode;
                    oldIndexNode.openindexnodewithindexheader(indexhdr,getrightpagevalueOfIndexNode());
                    oldIndexNode.setleftpagevalueOfIndexNode(newLastPageno);
                }
            }
        } else {
            // dupcount is not equal to 0 this is! ===
            position = position - indexhdr->getsizeofkey();
            position = position - sizeof(int);

            memcpy(&dupPagenos[0],&indexnodedata[position],sizeof(int));

            for(int i=0; i<dupCount; i++){
                memcpy(&indexnodedata[position],&dupPagenos[i],sizeof(int));
                position = position + sizeof(int);
                memcpy(&indexnodedata[position],&dupKeys[i],indexhdr->getsizeofkey());
                position = position + indexhdr->getsizeofkey();

                if(getIndexNodeLevel() == 1){
                    if(i!=0){
                        LeafNode leafNode(indexhdr,dupPagenos[i - 1]);
                        LeafNode newleafNode(indexhdr,dupPagenos[i]);

                        newleafNode.setleftpagevalue(leafNode.getPageNumber());
                        newleafNode.setrightpagevalue(dupPagenos [i +1]);
                    }else{
                        LeafNode leafNode(indexhdr,dupPagenos[i]);
                        leafNode.setrightpagevalue(dupPagenos[i + 1]);
                    }
                } else{
                    if(i!=0){
                        IndexNode indexNode;
                        indexNode.openindexnodewithindexheader(indexhdr,dupPagenos[i - 1]);
                        IndexNode newIndexNode;
                        newIndexNode.openindexnodewithindexheader(indexhdr,dupPagenos[i]);

                        newIndexNode.setleftpagevalueOfIndexNode(indexNode.getPageNumber());
                        newIndexNode.setrightpagevalueOfIndexNode(dupPagenos [i + 1]);
                    }else{
                        IndexNode indexNode;
                        indexNode.openindexnodewithindexheader(indexhdr,dupPagenos[i]);
                        indexNode.setrightpagevalueOfIndexNode(dupPagenos[i + 1]);
                    }
                }
            }

            memcpy(&indexnodedata[position],&dupPagenos[dupCount],sizeof(int));
            setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);


            if(getIndexNodeLevel() == 1){
                LeafNode leafNode(indexhdr,dupPagenos[dupCount]);
                leafNode.setleftpagevalue(dupPagenos[dupCount - 1]);
            }else{
                IndexNode indexNode;
                indexNode.openindexnodewithindexheader(indexhdr,dupPagenos[dupCount]);
                indexNode.setleftpagevalueOfIndexNode(dupPagenos[dupCount - 1]);
            }
            // ================The execution block for flag == FALSE ends here..----------=====
        }
    }

    if(getNoOfKeysInIndexNode() == 0){
        //cout<<"The number of childs in this page is equal to 0"
          //      <<"Hence delete this page.. and.. "
            //    <<"make it's child as the root.."<<endl;

        deletedPages.push_back(getPageNumber());

        if(getIndexNodeLevel() == 1){
            indexhdr->setpagenumberofroot(dupPagenos[dupCount]);
            LeafNode leafNode1(indexhdr,dupPagenos[dupCount]);
            leafNode1.setparentpagevalue(-1);
            indexhdr->settreeheight(0);
        }else{
            indexhdr->setpagenumberofroot(dupPagenos[dupCount]);
            IndexNode indexNode1;
            indexNode1.openindexnodewithindexheader(indexhdr,dupPagenos[dupCount]);
            indexNode1.setParentofIndexNode(-1);
            indexhdr->settreeheight(indexNode1.getIndexNodeLevel());
        }
        return HIT_RETURN;
    }

    //=======================The deletion operation has been complete=======================
    //===================Now, there will be checking for if the tree  will have to be merged
    // ====================Or it has to be rotated.. ====== or just do nothing
    // The pain in the ass part begins here... god be with me, till I finish it! thank you!
    float ceilvalue = (double)(indexhdr->getfanoutoftree() / 2);
    if(getNoOfKeysInIndexNode() >= ceil(ceilvalue)){
        //cout<<"It's fine, there are nodes till fill out factor.. "<<endl;
    }else{
        //cout<<"Merging or rotation in b+ tree should happen. check left page and right page for that"<<endl;
        int righter = -1;
        int lefter = -1;

        if(getParentofIndexNode() != -1){
            IndexNode newNode; // newnode is the Parentnode..
            newNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
            newNode.getleftandrightpagevaluestothegivenpagenumber(getPageNumber(),lefter,righter);
        }

        //cout<<"Right Page Number =========== "<<righter
          //      <<"Left Page Number ============"<<lefter<<endl;

        if(righter != -1){
            //cout<<"Checking for a possibility to rotate the right page.. "<<endl;

            IndexNode rightIndexNode;
            rightIndexNode.openindexnodewithindexheader(indexhdr,righter);
            double celiedvalue = (double)(indexhdr->getfanoutoftree() / 2);
            if((rightIndexNode.getNoOfKeysInIndexNode() - 1)>= ceil(celiedvalue)){
                //cout<<"The rightpage has more than half of the keys.. "
                  //      <<"So rotate or move keys from the right page.. "<<endl;

                char keyblocker[indexhdr->getsizeofkey()];
                char firstKeyonright[indexhdr->getsizeofkey()];

                rightIndexNode.getthekeyatthefrontofindexnode(firstKeyonright);

                int rotatepgno;

                rotatepgno=rightIndexNode.indexnodefirstpage();

                if(getParentofIndexNode()!=-1){
                    IndexNode parentIndexNode;
                    parentIndexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                    parentIndexNode.getpagenumberbetweenleftpageandrightpage(getPageNumber(),righter,keyblocker);

                    insertinindexlast(keyblocker,rotatepgno);
                    if(getIndexNodeLevel() == 1){
                        LeafNode rotateLeafNode(indexhdr,rotatepgno);
                        rotateLeafNode.setparentpagevalue(getPageNumber());
                    }else{
                        IndexNode rotateIndexNode;
                        rotateIndexNode.openindexnodewithindexheader(indexhdr,rotatepgno);
                        rotateIndexNode.setParentofIndexNode(getPageNumber());
                    }

                  //  cout<<"Left most keys in the right node has to be pushed to the parent node.. "<<endl;
                    parentIndexNode.keyshift(keyblocker,firstKeyonright);
                    rightIndexNode.removethekeyatthefrontofindexnode(); // The key has to be deleted after it has been moved to the parent..
                }
            }else if (lefter != -1){
                //cout<<"Left page is available but not right.. so rotating left page only.. ======="<<endl;
                IndexNode leftIndexNode;
                leftIndexNode.openindexnodewithindexheader(indexhdr,lefter);

                if((leftIndexNode.getNoOfKeysInIndexNode() - 1)>= ceil(indexhdr->getfanoutoftree() / 2)){
                    char keyblocker[indexhdr->getsizeofkey()];
                    char lastkeyinleft[indexhdr->getsizeofkey()];
                    leftIndexNode.getthekeyattheendofindexnode(lastkeyinleft);
                    int rotatepageno;

                    rotatepageno=leftIndexNode.indexnodelastpage();

                    if(getParentofIndexNode() != -1){
                        IndexNode parentIndexNode;
                        parentIndexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                        parentIndexNode.getpagenumberbetweenleftpageandrightpage(lefter,getPageNumber(),keyblocker);
                        parentIndexNode.keyshift(keyblocker,lastkeyinleft);
                    }
                    insertinindexfirst(keyblocker,rotatepageno);

                    if(getIndexNodeLevel() == 1){
                        LeafNode rotateleafNode(indexhdr,rotatepageno);
                        rotateleafNode.setparentpagevalue(getPageNumber());
                    }else{
                        IndexNode rotateIndexNode;
                        rotateIndexNode.openindexnodewithindexheader(indexhdr,rotatepageno);
                        rotateIndexNode.setParentofIndexNode(getPageNumber());
                    }
                }else{
                    leftIndexNode.removethekeyattheendofindexnode();
                    // Deletion and rotation ends here.. and we are merging it here first..
                    //cout<<"Rotation and deletion are done.. it is found that none of the pages have enough space.. "
                      //      <<"so merge them!"<<endl;

                    //cout<<"Merging them with the right page number=============="<<endl;

                    deletedPages.push_back(getPageNumber());

                    char keyblock[indexhdr->getsizeofkey()];
                    if(getParentofIndexNode()!=-1){
                        IndexNode parentNewNode;
                        parentNewNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                        parentNewNode.getpagenumberbetweenleftpageandrightpage(getPageNumber(),getrightpagevalueOfIndexNode(),keyblock);
                    }

                    int pagenumberoftheattachedpage;
                    pagenumberoftheattachedpage=rightIndexNode.indexnodefirstpage();

                    char dupKeys[getNoOfKeysInIndexNode() + 1][indexhdr->getsizeofkey()];
                    int dupPagenos[getNoOfKeysInIndexNode() + 1];
                    int dupCount=0;
                    int position = IndexNode::getIndexNodeHeaderSize();
                  //  cout<<"Moving all the keys from the right node to the current node ==="<<endl;

                   // cout<<"Deleting current Node along with it ==="<<endl;

                    for(int i=0; i<getNoOfKeysInIndexNode(); i++){
                        memcpy(&dupPagenos[dupCount],&indexnodedata[position],sizeof(int));
                        position = position + sizeof(int);
                        memcpy(dupKeys[dupCount],&indexnodedata[position],indexhdr->getsizeofkey());
                        position = position + indexhdr->getsizeofkey();
                        dupCount = dupCount + 1;
                    }

                    memcpy(&dupPagenos[dupCount],&indexnodedata[position],sizeof(int));
                    memcpy(dupKeys[dupCount],keyblock,indexhdr->getsizeofkey());

                    for(int i=dupCount; i>=0; i--){
                        rightIndexNode.insertinindexfirst(dupKeys[i],dupPagenos[i]);
                    }
                    if(getParentofIndexNode() != -1){
                        IndexNode parentNode;
                        parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                        parentNode.deleteinindexwithflagset(keyblock,TRUE,deletedPages);
                    }
                }
            }else{
                // do merging with right page here..
                //cout<<"Left page doesn't exist == hence merging with right page.. "<<endl;

                deletedPages.push_back(getPageNumber());

                char keyblock[indexhdr->getsizeofkey()];

                if(getParentofIndexNode() != -1){
                    IndexNode parentNode;
                    parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                    parentNode.getpagenumberbetweenleftpageandrightpage(getPageNumber(),getrightpagevalueOfIndexNode(),keyblock);
                }

                int rotatepageno;
                rotatepageno =rightIndexNode.indexnodefirstpage();
                char dupKeys[getNoOfKeysInIndexNode() + 1][indexhdr->getsizeofkey()];
                int dupPagenos[getNoOfKeysInIndexNode() + 1];
                int dupCount=0;
                int position = IndexNode::getIndexNodeHeaderSize();

              //  cout<<"Moving all keys from current node to the right node.. "<<endl;
                for(int i=0; i<getNoOfKeysInIndexNode(); i++){
                   memcpy(&dupPagenos[dupCount],&indexnodedata[position],sizeof(int));
                   position = position + sizeof(int);
                   memcpy(dupKeys[dupCount],&indexnodedata[position],indexhdr->getsizeofkey());
                   position = position + indexhdr->getsizeofkey();
                   dupCount = dupCount + 1;
                }
                    memcpy(&dupPagenos[dupCount],&indexnodedata[position],sizeof(int));
                    memcpy(dupKeys[dupCount],keyblock,indexhdr->getsizeofkey());

                    for(int i=dupCount; i>=0; i--){
                        rightIndexNode.insertinindexfirst(dupKeys[i],dupPagenos[i]);
                    }
                    if(getParentofIndexNode() != -1){
                        IndexNode parentNode;
                        parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                        parentNode.deleteinindexwithflagset(keyblock,TRUE,deletedPages);
                    }                  // Merging is done here..
            }
        }else if(lefter != -1){
            //cout<<"Checking left page values == = ";
            IndexNode indexNodeleft;
            indexNodeleft.openindexnodewithindexheader(indexhdr,lefter);
            if((indexNodeleft.getNoOfKeysInIndexNode() - 1) >= ceil(indexhdr->getfanoutoftree() /2 )){
                //cout<<"Left page has more number of keys so rotate keys from left page"<<endl;
                char keyblock[indexhdr->getsizeofkey()];
                char lastkeyinLeaf[indexhdr->getsizeofkey()];

                indexNodeleft.getthekeyattheendofindexnode(lastkeyinLeaf);
                int rotatepageno;
                rotatepageno = indexNodeleft.indexnodelastpage();

                if(getParentofIndexNode() != -1){
                    IndexNode parentnewNode;
                    parentnewNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                    parentnewNode.getpagenumberbetweenleftpageandrightpage(lefter,getPageNumber(),keyblock);
                    //cout<<"Seperating key is === "<<keyblock;
                    parentnewNode.keyshift(keyblock,lastkeyinLeaf);
                }
                insertinindexfirst(keyblock,rotatepageno);

                if(getIndexNodeLevel()== 1){
                    LeafNode rotateleafNode(indexhdr,rotatepageno);
                    rotateleafNode.setparentpagevalue(getPageNumber());
                }else{
                    IndexNode rotateIndexNode;
                    rotateIndexNode.openindexnodewithindexheader(indexhdr,rotatepageno);
                    rotateIndexNode.setParentofIndexNode(getPageNumber());
                }

                indexNodeleft.removethekeyattheendofindexnode();
            }else{
                //cout<<"Left page doesn't have enough number of keys ====="
                  //      <<"So merge with left page number ====="
                    //    <<endl;
                deletedPages.push_back(getPageNumber());

                char Keyblock[indexhdr->getsizeofkey()];

                if(getParentofIndexNode() != -1){
                    IndexNode parentIndexNode;
                    parentIndexNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                    parentIndexNode.getpagenumberbetweenleftpageandrightpage(getleftpagevalueOfIndexNode(),getPageNumber(),Keyblock);
                }

                int rotatepageno = indexnodefirstpage();
                char dupKeys[getNoOfKeysInIndexNode() + 1][indexhdr->getsizeofkey()];
                int dupPagenos[getNoOfKeysInIndexNode() + 1];
                int dupCount=0;
                int position = IndexNode::getIndexNodeHeaderSize();
                memcpy(dupKeys[dupCount],Keyblock,indexhdr->getsizeofkey());

                //cout<<"Moving all keys from current node into left node==="<<endl;
                for(int i=0; i<getNoOfKeysInIndexNode(); i++){
                   memcpy(&dupPagenos[dupCount],&indexnodedata[position],sizeof(int));
                   position = position + sizeof(int);
                   memcpy(dupKeys[dupCount],&indexnodedata[position],indexhdr->getsizeofkey());
                   position = position + indexhdr->getsizeofkey();
                   dupCount = dupCount + 1;
                }

                    memcpy(&dupPagenos[dupCount],&indexnodedata[position],sizeof(int));
                    indexNodeleft.insertinindexlast(Keyblock,dupPagenos[0]);

                    for(int i=0; i<dupCount; i++){
                        indexNodeleft.insertinindexlast(dupKeys[i],dupPagenos[i+1]);
                    }

                    if(getParentofIndexNode() != -1){
                        IndexNode parentNode;
                        parentNode.openindexnodewithindexheader(indexhdr,getParentofIndexNode());
                        parentNode.deleteinindexwithflagset(Keyblock,FALSE,deletedPages);
                    }

                          //cout<<"Merging H[IT]opefully done!===:P:P:P == Such a pain in ass..best bit of programming I have done this is..sigh!"
                           // <<"If god has been with me, I would see this line again - Meaning, the function has been HIT_RETURNfully executed.. Oh god bless me!"<<endl;

            }
        }

    }
    return HIT_RETURN;
}



void IndexNode::getallpagenumbersunderindexnode(std::vector<int>& pagenumbers){
    int level=getIndexNodeLevel();
    int position = getIndexNodeHeaderSize();
    int pageNumbervalue;

    for(int i=0; i< getNoOfKeysInIndexNode() + 1; i++){
        memcpy(&pageNumbervalue,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);
        position = position + indexhdr->getsizeofkey();

        if(level > 1){
            // Delete index Nodes..
            IndexNode indexNode;
            indexNode.openindexnodewithindexheader(indexhdr,pageNumbervalue);
            indexNode.getallpagenumbersunderindexnode(pagenumbers);
            pagenumbers.push_back(pageNumbervalue);
        }
        if(level == 1){
            pagenumbers.push_back(pageNumbervalue);
        }
    }
}
// UI Functions for Index Node start from here =================================

//
//void IndexNode::OnlyindexNodeprint(){
//    int position = IndexNode::getIndexNodeHeaderSize();
//    char keyset[indexhdr->getsizeofkey()];
//
//    int leftpagevalue, rightpagevalue;
//
//    for(int i=0; i<indexnodehdrstr.noOfKeys; i++){
//        memcpy(&leftpagevalue,&indexnodedata[position],sizeof(int));
//        position = position + sizeof(int);
//
//        memcpy(keyset,&indexnodedata[position],indexhdr->getsizeofkey());
//        position = position + indexhdr->getsizeofkey();
//        cout<<leftpagevalue<<""<<keyset<<"";
//    }
//
//    memcpy(&rightpagevalue,&indexnodedata[position],sizeof(int));
//    cout<<rightpagevalue<<endl;
//}

//void IndexNode::print(){
//    cout<<"Current Index Page Number==="<<getPageNumber()<<endl;
//    cout<<"The parent page numebr is ==="<<getParentofIndexNode()<<endl;
//    cout<<"The Left Page Number is ===="<<getleftpagevalueOfIndexNode();
//    cout<<"The Right Page Number is ==="<<getrightpagevalueOfIndexNode();
//    cout<<"The number of keys in Index Node ===="<<indexnodehdrstr.noOfKeys<<endl;
//    cout<<"The level of the node ======="<<getIndexNodeLevel()<<endl;
//
//    int leftpagevalue,rightpagevalue;
//
//    char keyvalue[indexhdr->getsizeofkey()];
//    int level = getIndexNodeLevel();
//
//    OnlyindexNodeprint();
////
////    int position = IndexNode::getIndexNodeHeaderSize();
////
////    for(int i=0; i<indexnodehdrstr.noOfKeys; i++){
////        memcpy(&leftpagevalue,&indexnodedata[position],sizeof(int));
////        position = position + sizeof(int);
////
////        memcpy(keyvalue,&indexnodedata[position],indexhdr->getsizeofkey());
////        position = position + indexhdr->getsizeofkey();
////
////        memcpy(&rightpagevalue, &indexnodedata[position],sizeof(int));
////
////        cout<<leftpagevalue<<""<<keyvalue<<""<<rightpagevalue<<endl;
////
////        /*if(level == 1){
////            LeafNode leafNode(indexhdr,leftpagevalue);
////            leafNode.print();
////            cout<<"============The leaf page following this page.. or the next leaf page you can call it is ===="<<endl;
////
////            LeafNode leafNode1(indexhdr,rightpagevalue);
////            leafNode1.print();
////        }*/
////
////        if(level == 1){
////            LeafNode leafNode(indexhdr,leftpagevalue);
////            leafNode.print();
////            cout<<"============The leaf page following this page.. or the next leaf page you can call it is ===="<<endl;
////
////            LeafNode leafNode1(indexhdr,rightpagevalue);
////            leafNode1.print();
////        }else{
////            IndexNode indexNode;
////            indexNode.openindexnodewithindexheader(indexhdr,leftpagevalue);
////            indexNode.print();
////            cout<<"===The next one would be ===="<<endl;
////            IndexNode indexNode1;
////            indexNode1.openindexnodewithindexheader(indexhdr,rightpagevalue);
////            indexNode1.print();
////        }
////    }
//}

void IndexNode::printindex(){

    cout<<"\nIndex Node UI"<<endl;
    cout<<"================"<<endl;

    cout<<"Current Index Page Number   ============"<<getPageNumber()<<endl;
    cout<<"Parent Page Number          ============"<<getParentofIndexNode()<<endl;
    cout<<"Level of Index Node         ============"<<getIndexNodeLevel()<<endl;
    cout<<"Number of Keys in IndexNode ============"<<indexnodehdrstr.noOfKeys<<endl;
    cout<<"The content in the Index Node is"<<endl;
    cout<<"================================="<<endl;
    cout<<"\nLeft Index Page Number     ==========="<<getleftpagevalueOfIndexNode()<<endl;
    cout<<"\nRight Index Page Number    ==========="<<getrightpagevalueOfIndexNode()<<endl;

    int position = IndexNode::getIndexNodeHeaderSize();
    int leftpageno;
    char keysize[indexhdr->getsizeofkey()];

    for(int i=0;i<getNoOfKeysInIndexNode(); i++){
        memcpy(&leftpageno,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);

        memcpy(keysize,&indexnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();

        cout<<leftpageno<<"==";
        cout<<"key value is  {";
        BplusTree::printKey(keysize,indexhdr);
        cout<<"}";
        cout<<"==";
    }

    memcpy(&leftpageno,&indexnodedata[position],sizeof(int));
    cout<<leftpageno<<"=="<<endl;

    cout<<"\t--------------------------------------------------"<<endl;
    cout<<"\tThat's pretty much the data in Index Node=="<<endl;

}


// find indexandleafnodes from the indexnode
void IndexNode::getindexandleafpages(std::vector<int>& leafPages, std::vector<int>& indexPages){
    int getnoofkeys = IndexNode::getNoOfKeysInIndexNode();
    int dumppage;
    int position = getIndexNodeHeaderSize();
    for(int i=0; i<getnoofkeys+1; i++){
        /*For all the keys present in the node
         * Get the pagenumbers and dumpinto indexpagesvector if they are indexpages
         * otherwise dump into leafpage vectors
         * depending on the type of page it is!
         */
             memcpy(&dumppage,&indexnodedata[position],sizeof(int));
             position = position + sizeof(int);
             position = position + indexhdr -> getsizeofkey();


             if(getIndexNodeLevel() > 1){
                 IndexNode indnode1;
                 indnode1.openindexnodewithindexheader(indexhdr,dumppage);
                 indnode1.getindexandleafpages(leafPages,indexPages);
                 indexPages.push_back(dumppage);
             }

             if(getIndexNodeLevel() == 1){
                 leafPages.push_back(dumppage);
             }
    }
}
//################################################################################
// ###################################End of Index Node Functions#####################3
//##################################################################################################


//################################################################################
// ###################################Original Bplus Functions#####################3
//##################################################################################################
BplusTree::BplusTree(){
    // constructor stub that's all..
}

void BplusTree::initIndex(int indexheaderclassNumber){
    bplustreeindexhdrclassptr = new indexheaderclass();
    bplustreeindexhdrclassptr->openindexheaderpage(indexheaderclassNumber);
}

BplusTree::~BplusTree(){
   // strcpy(dbname,"aksDB");
   // bm->CommitAll(dbname);
    delete bplustreeindexhdrclassptr;
}

int BplusTree::searchInBplusTree(const char* key){
     int rootpage=bplustreeindexhdrclassptr->getpagenumberofroot();
     int totalleveloftree=bplustreeindexhdrclassptr->gettreeheight();
     //int leafpage = -1;
     int currentpage=rootpage;
   //  cout<<"Going into for loop inside the search"<<endl;
   //  cout<<"The total level of tree is "<<totalleveloftree<<endl;
     int i;
     for(i=totalleveloftree; i>0; i=i-1){
         IndexNode indexNode;
         indexNode.openindexnodewithindexheader(bplustreeindexhdrclassptr,currentpage);
     //    cout<<"Going into the index node search..."<<endl;
         currentpage=indexNode.searchinindex(key);
     //    leafpage=currentpage;
     }
     return currentpage;
}

int BplusTree::insertIntoBplusTree(const char* key, RID& rid){
   // cout<<"\nInserting key"<<endl;
   // BplusTree::printKey(key,bplustreeindexhdrclassptr);
    if(bplustreeindexhdrclassptr->getpagenumberofroot() == -1){
       // cout<<"Nothing present---- so creating a leaf page initially -----"<<endl;
        LeafNode newleafNode;
        newleafNode.createnewleafnode(bplustreeindexhdrclassptr);
        //cout<<"Page number of the newly created page ------"<<newleafNode.getPageNumber();

        //char keyfresh[bplustreeindexhdrclassptr->getsizeofkey()];
      //  int returnvalue = newleafNode.searchinleaf(key,rid);
      //  if(returnvalue == PHAT_RETURN){
        //    cout<<"\nThere is already an element present with the same key and rid. So you can't insert anything"<<endl;
          //  return PHAT_RETURN;
       // }

        newleafNode.insertinleaf(key,rid);
        bplustreeindexhdrclassptr->setNumberOfKeys(bplustreeindexhdrclassptr->getNumberOfKeys() + 1);
    }else{
        int inserighternumberofleaf = searchInBplusTree(key);
        //cout<<"pageno. search for new key insertion ============="<<endl;
        //inserighternumberofleaf = searchInBplusTree(key);

        LeafNode leafNodenew(bplustreeindexhdrclassptr,inserighternumberofleaf);
        //int returnvalue = leafNodenew.searchinleaf(key,rid);
        //if(returnvalue == PHAT_RETURN){
          //  cout<<"\nThere is already an element present with the same key and rid. So you can't insert anything"<<endl;
            //return PHAT_RETURN;
        //}
        leafNodenew.insertinleaf(key,rid);
        bplustreeindexhdrclassptr->setNumberOfKeys(bplustreeindexhdrclassptr->getNumberOfKeys() + 1);
    }
    return HIT_RETURN;
}

int BplusTree::deleteFromBplusTree(const char* key, RID& rid){
   // cout<<"Deleting key from bplus tree"<<endl;

    if(bplustreeindexhdrclassptr->getpagenumberofroot() == -1){
        cout<<"Tree doesn't exist at all"<<endl;
        return PHAT_RETURN;
    }else{
        //cout<<"Finding the leaf page number.. "<<endl;
        int rootPageNumber = bplustreeindexhdrclassptr->getpagenumberofroot();
        //cout<<"Going into Bplustree search.. "<<endl;
        int leafPageNumber = searchInBplusTree(key);

        //cout<<"The leaf page number is .."<<leafPageNumber;

 //       LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
        int searchstatus=2;//leafNode.searchinleaf(key,rid);
 
        while(searchstatus == 2 && leafPageNumber != -1){
          //leafPageNumber = leafNode.getrightpagevalue();

            LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
            searchstatus=leafNode.searchinleaf(key,rid);

            if(searchstatus == 2){
                leafPageNumber = leafNode.getrightpagevalue();

                if(leafPageNumber == -1){
                    searchstatus=1;
                    break;
                }
            }
            

            //LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
            //searchstatus=leafNode.searchinleaf(key,rid);
         //  leafPageNumber = leafNode.getrightpagevalue();
        }
        if(searchstatus == 0 && leafPageNumber != -1){
            vector<int> deletedPages;

            LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
            leafNode.deleteinleaf(key,rid,deletedPages);

            bplustreeindexhdrclassptr->setNumberOfKeys(bplustreeindexhdrclassptr->getNumberOfKeys() - 1);

            int deletedPagesSize = deletedPages.size();
          //  cout<<"The size of deletedpages is"<<deletedPagesSize<<endl;
            //cout<<"The size of deleted pages is \t"<<deletedPagesSize<<endl;
            for(int i=0; i < deletedPagesSize; i++){
             //    cout<<"The deletedPages are"<<deletedPages.at(i)<<endl;
                 //bm->DestroyPage(dbname,deletedPages.at(i));
                 //bm->ReleasePage(dbname,deletedPages.at(i));
            }
            deletedPages.erase(deletedPages.begin(), deletedPages.begin() + deletedPagesSize);
        }else{
           // cout<<"The value of search status is.. "<<searchstatus;
            cout<<"Key not found.. "<<endl;
        }
    }
    return HIT_RETURN;
}

void BplusTree::deleteIndex(int indexPageNumber){
    int rootPageNumber = bplustreeindexhdrclassptr->getpagenumberofroot();
    std::vector<int> allPageNumbers;

    int heightofthetree = bplustreeindexhdrclassptr->gettreeheight();

    if(heightofthetree!=0 && rootPageNumber!=-1){
        IndexNode indexNode;
        indexNode.openindexnodewithindexheader(bplustreeindexhdrclassptr,rootPageNumber);
        indexNode.getallpagenumbersunderindexnode(allPageNumbers);
    }

    for(int i=0; i<allPageNumbers.size(); i++){
        cout<<"The pagenumber that has to be destroyed is"<<allPageNumbers.at(i)<<endl;
        bm->DestroyPage(dbname,allPageNumbers.at(i));
        bm->ReleasePage(dbname,allPageNumbers.at(i));
    }

    if(rootPageNumber!=-1){
        cout<<"The pagenumber that has to be destroyed is"<<rootPageNumber<<endl;
        bm->DestroyPage(dbname,rootPageNumber);
        bm->ReleasePage(dbname,rootPageNumber);
        cout<<"The pagenumber that has been destroyed is"<<rootPageNumber<<endl;
    }
}

int BplusTree::searchKeyInBPlusTree(const char* key, std::vector<RID>& RIDVector){
    if(bplustreeindexhdrclassptr->getpagenumberofroot() == -1){
        cout<<"Bplustree doesn't exist.. ";
        return HIT_RETURN;
    }

    int rootPageNumber = bplustreeindexhdrclassptr->getpagenumberofroot();
    int heightofthetree = bplustreeindexhdrclassptr->gettreeheight();

    if(heightofthetree == 0){
        LeafNode leafNode(bplustreeindexhdrclassptr,rootPageNumber);
        leafNode.searchKeyInLeafNode(key, RIDVector);
    }else{

        int leafPageNumber = searchInBplusTree(key);

        LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
        leafNode.searchKeyInLeafNode(key,RIDVector);
    }
    return HIT_RETURN;
}

int BplusTree::searchKeyInBPlusTreeallRIDs(const char* key, std::vector<RID>& RIDVector){
    if(bplustreeindexhdrclassptr->getpagenumberofroot() == -1){
        cout<<"Bplustree doesn't exist.. ";
        return HIT_RETURN;
    }
    int returnvalue = HIT_RETURN;
    int rootPageNumber = bplustreeindexhdrclassptr->getpagenumberofroot();
    int heightofthetree = bplustreeindexhdrclassptr->gettreeheight();

    if(heightofthetree == 0){

            LeafNode leafNode(bplustreeindexhdrclassptr,rootPageNumber);
            leafNode.searchKeyInLeafNode(key, RIDVector);
            //rootPageNumber = leafNode.getrightpagevalue();

    }else{
        // height of the tree is not zero that means there exists some index node..
        int leafPageNumber = searchInBplusTree(key);
        while(returnvalue == HIT_RETURN){
            LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
            returnvalue = leafNode.searchKeyInLeafNode(key, RIDVector);
            leafPageNumber = leafNode.getrightpagevalue();
        }
    }
    return HIT_RETURN;
}

void BplusTree::bplusSearchRangeKeyInLeafNode(int leafPageNumber, const char* key1, const char* key2, std::vector<RID>& RIDVector, std::vector<string>& keyVector){
    int flag=0;

    while(leafPageNumber!=-1){
     //   cout<<"Searching in next leaf pagenumber"<<endl;
        LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
        flag = leafNode.keyandridinbetweenkeys(key1,key2,RIDVector,keyVector);

        leafPageNumber=leafNode.getrightpagevalue();

        if(flag == 0){
            break;
        }
    }
}

void BplusTree::getRIDS(std::vector<RID>& RIDVector, std::vector<string>& keyVector){
    std::vector<int> leafPages;

    if(bplustreeindexhdrclassptr->gettreeheight() == 0){
        if(bplustreeindexhdrclassptr->getpagenumberofroot() != -1){
            leafPages.push_back(bplustreeindexhdrclassptr->getpagenumberofroot());
        }
    }else{
        int rootPageNumber = bplustreeindexhdrclassptr->getpagenumberofroot();
        IndexNode indexNode;
        indexNode.openindexnodewithindexheader(bplustreeindexhdrclassptr,rootPageNumber);
        indexNode.getleafset(leafPages);
    }

    for(int i=0; i<leafPages.size(); i++){
        if(leafPages.at(i) != -1){
            LeafNode leafNode(bplustreeindexhdrclassptr,leafPages.at(i));
            leafNode.getridkeysets(RIDVector,keyVector);
        }
    }

    RID rid;

    //cout<<"printing the searched result.. "<<endl;
    for(int i=0; i<RIDVector.size(); i++){
        rid = RIDVector.at(i);
        string mykeystring;
        mykeystring = keyVector.at(i);

      //  cout <<"The key is.. "<<endl;
       /// BplusTree::printKey(mykeystring.c_str(), bplustreeindexhdrclassptr);

      //  cout<<"\tPageNumber is =========="<< rid.pageNumber << "=======The slot number is ======="<<rid.slotNumber<<endl;
    }
}

void BplusTree::getKEYRIDRange(int startLeafPage, const char* totalKey1, const char* totalKey2, std::vector<RID>& RIDVector, std::vector<string>& keyVector){

    char keyset[bplustreeindexhdrclassptr->getsizeofkey()];
    RID rid;

    while(startLeafPage != -1){
        LeafNode leafNode(bplustreeindexhdrclassptr,startLeafPage);
        int i;
        int sizer = leafNode.getNoOfRecordsInNode();
        int initsizer = RIDVector.size();
        for(int i=0; i<leafNode.getNoOfRecordsInNode(); i++){
            memset(keyset,'\0',bplustreeindexhdrclassptr->getsizeofkey());
            leafNode.getKeyAndRID(i,keyset,rid);

            if (((BplusTree::keyComp(keyset, totalKey1,bplustreeindexhdrclassptr->getcolcount(),
					bplustreeindexhdrclassptr) == 1) || (BplusTree::keyComp(
					keyset, totalKey1,bplustreeindexhdrclassptr->getcolcount(), bplustreeindexhdrclassptr) == 0))
					&& ((BplusTree::keyComp(keyset, totalKey2, bplustreeindexhdrclassptr->getcolcount(),
							bplustreeindexhdrclassptr) == -1)
							|| (BplusTree::keyComp(keyset, totalKey2, bplustreeindexhdrclassptr->getcolcount(),
									bplustreeindexhdrclassptr) == 0))) {

                RIDVector.push_back(rid);
                string mykeystring(keyset,bplustreeindexhdrclassptr->getsizeofkey());
                keyVector.push_back(mykeystring);
            }

            if(BplusTree::keyComp(keyset,totalKey2,bplustreeindexhdrclassptr->getcolcount(),bplustreeindexhdrclassptr) == 1){
                break;
            }
        }

        if(i = leafNode.getNoOfRecordsInNode()){
            startLeafPage = leafNode.getrightpagevalue();
        }else{
            break;
        }
    }
    int ridsize = RIDVector.size();
    int keysizer = keyVector.size();
    keysizer = keysizer + 1;
}

// For checking if a given page number is existent in the array or not.. index w.r.t

int BplusTree::checkifthegivenpagenumberispresentintheindexpage(std::vector<int> indexPageVector, int PageNumber){

    for(int i=0; i<indexPageVector.size(); i++){
        if(indexPageVector.at(i) == PageNumber){
            return HIT_RETURN;
        }
    }
    return PHAT_RETURN;
}

// For checking if a given page number is existent in the array or not.. leaf w.r.t

int BplusTree::checkifthegivenpagenumberispresentintheleafpage(std::vector<int> leafPageVector, int PageNumber){

    for(int i=0; i<leafPageVector.size(); i++){
        if(leafPageVector.at(i) == PageNumber){
            return HIT_RETURN;
        }
    }
    return PHAT_RETURN;
}
//
void BplusTree::rangecheckfunctionforint(int range1, int range2, int incrementfactor){
    int key = range1, counterflag = 0;
    char keyset[bplustreeindexhdrclassptr->getsizeofkey()];
    memset(keyset, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
    RID rid;
 //   rid.pageNumber = 1;
 //   rid.slotNumber = 1;

    for(int i=0; key <= range2; i++){
        //cout<<"\nInserting key at position"<<i<<endl;
        memcpy(keyset,&key,sizeof(int));
        rid.pageNumber = i;
        rid.slotNumber = (unsigned short) i;
        insertIntoBplusTree(keyset,rid);
        //counterflag = counterflag + 1;
        key = key + incrementfactor;
    }
}

void BplusTree::rangecheckfunctionforfloat(float range1, float range2, float incrementfactor){
    float key = range1, counterflag = 0;
    char keyset[bplustreeindexhdrclassptr->getsizeofkey()];
    memset(keyset, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
    RID rid;

    for(int i=0; key <= range2; i++){
        memcpy(keyset,&key,sizeof(float));
        rid.pageNumber = i;
        rid.slotNumber = (unsigned short) i;
        insertIntoBplusTree(keyset,rid);
        //counterflag = counterflag + 1;
        key = key + incrementfactor;
    }
}

void BplusTree::rangecheckfunctionfordouble(double range1, double range2, double incrementfactor){
    double key = range1, counterflag = 0;
    char keyset[bplustreeindexhdrclassptr->getsizeofkey()];
    memset(keyset, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
    RID rid;

    for(int i=0; key <= range2; i++){
        memcpy(keyset,&key,sizeof(double));
        rid.pageNumber = i;
        rid.slotNumber = (unsigned short) i;
        insertIntoBplusTree(keyset,rid);
        //counterflag = counterflag + 1;
        key = key + incrementfactor;
    }
}

void BplusTree::rangecheckfunctionforlong(long range1, long range2, long incrementfactor){
    long key = range1, counterflag = 0;
    char keyset[bplustreeindexhdrclassptr->getsizeofkey()];
    memset(keyset, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
    RID rid;

    for(int i=0; key <= range2; i++){
        memcpy(keyset,&key,sizeof(long));
        rid.pageNumber = i;
        rid.slotNumber = (unsigned short) i;
        insertIntoBplusTree(keyset,rid);
        //counterflag = counterflag + 1;
        key = key + incrementfactor;
    }
}
// this rangedump function is for testing..
/*
void BplusTree::rangedumpinsertfunction(int totkeycount){
    if(totkeycount < 1000000){
        ifstream in("varchardump");

        if(!in){
            cout<<"Can't open the file"<<endl;
            cout<<"There is no such file called keys in the directory"<<endl;
        }else{
            int count = 0;
            int pagenumberrid = 0, slotnumberrid = 0;
            RID rid;

            char columns[bplustreeindexhdrclassptr->sizeofcols[0]];
            char duplkey[30];

            memset(duplkey,'\0', 30);
            char keyset[bplustreeindexhdrclassptr->sizeofcols[0]];

            while(in){
                in >> duplkey;
                in >> pagenumberrid;
                in >> slotnumberrid;

                rid.pageNumber = pagenumberrid;
                rid.slotNumber = (unsigned short)slotnumberrid;

                strncpy(keyset,duplkey,bplustreeindexhdrclassptr->sizeofcols[0]);
                insertIntoBplusTree(keyset,rid);
                count ++;
                if(count == totkeycount){
                    break;
                }
            }
            in.close();
        }
    }
}
*/

void BplusTree::rangedeletecheckforint(int range1, int range2){
    if(range1<range2){
        char keyset1[bplustreeindexhdrclassptr->getsizeofkey()];
        char keyset2[bplustreeindexhdrclassptr->getsizeofkey()];

        memset(keyset1, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
        memcpy(keyset1, &range1, sizeof(int));
        memcpy(keyset2, &range2, sizeof(int));

        int startingofleafpage = searchInBplusTree(keyset1);
        vector<RID> RIDVector;
        vector<string> KeyVector;

        getKEYRIDRange(startingofleafpage,keyset1,keyset2,RIDVector,KeyVector);

        RID rid;

        for(int i=0; i<RIDVector.size(); i++){
            rid = RIDVector.at(i);
            string keystring;
            keystring = KeyVector.at(i);
            deleteFromBplusTree(keystring.c_str(),rid);
        }
    }else{
        cout<<"\n\tPlease enter a valid key range.. range1 should be less than range2.. "<<endl;
    }
}

void BplusTree::rangedeletecheckforfloat(float range1, float range2){

    if(range1<range2){
        char keyset1[bplustreeindexhdrclassptr->getsizeofkey()];
        char keyset2[bplustreeindexhdrclassptr->getsizeofkey()];

        memset(keyset1, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
        memcpy(keyset1, &range1, sizeof(float));
        memcpy(keyset2, &range2, sizeof(float));

        int startingofleafpage = searchInBplusTree(keyset1);

        vector<RID> RIDVector;
        vector<string> KeyVector;

        getKEYRIDRange(startingofleafpage,keyset1,keyset2,RIDVector,KeyVector);

        RID rid;

        for(int i=0; i<RIDVector.size(); i++){
            rid = RIDVector.at(i);
            string keystring;
            keystring = KeyVector.at(i);
            deleteFromBplusTree(keystring.c_str(),rid);
        }
    }else{
        cout<<"\n\tPlease enter a valid key range.. range1 should be less than range2.. "<<endl;
    }
}

void BplusTree::rangedeletecheckfordouble(double range1, double range2){
    if(range1<range2){
        char keyset1[bplustreeindexhdrclassptr->getsizeofkey()];
        char keyset2[bplustreeindexhdrclassptr->getsizeofkey()];

        memset(keyset1, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
        memcpy(keyset1, &range1, sizeof(double));
        memcpy(keyset2, &range2, sizeof(double));

        int startingofleafpage = searchInBplusTree(keyset1);
        vector<RID> RIDVector;
        vector<string> KeyVector;

        getKEYRIDRange(startingofleafpage,keyset1,keyset2,RIDVector,KeyVector);

        RID rid;

        for(int i=0; i<RIDVector.size(); i++){
            rid = RIDVector.at(i);
            string keystring;
            keystring = KeyVector.at(i);
            deleteFromBplusTree(keystring.c_str(),rid);
        }
    }else{
        cout<<"\n\tPlease enter a valid key range.. range1 should be less than range2.. "<<endl;
    }
}

void BplusTree::rangedeletecheckforlong(long range1, long range2){
        if(range1<range2){
        char keyset1[bplustreeindexhdrclassptr->getsizeofkey()];
        char keyset2[bplustreeindexhdrclassptr->getsizeofkey()];

        memset(keyset1, '\0', bplustreeindexhdrclassptr->sizeofcols[0]);
        memcpy(keyset1, &range1, sizeof(long));
        memcpy(keyset2, &range2, sizeof(long));

        int startingofleafpage = searchInBplusTree(keyset1);
        vector<RID> RIDVector;
        vector<string> KeyVector;

        getKEYRIDRange(startingofleafpage,keyset1,keyset2,RIDVector,KeyVector);

        RID rid;

        for(int i=0; i<RIDVector.size(); i++){
            rid = RIDVector.at(i);
            string keystring;
            keystring = KeyVector.at(i);
            deleteFromBplusTree(keystring.c_str(),rid);
        }
    }else{
        cout<<"\n\tPlease enter a valid key range.. range1 should be less than range2.. "<<endl;
    }
}
//
//int BplusTree::print(){
//    int level=bplustreeindexhdrclassptr->gettreeheight();
//    int cpgno = bplustreeindexhdrclassptr->getpagenumberofroot();
//
//    if(level != 0){
//        while(cpgno!=-1){
//            IndexNode indexNode;
//            indexNode.openindexnodewithindexheader(bplustreeindexhdrclassptr,cpgno);
//        //    indexNode.print();
//            cpgno = indexNode.getrightpagevalueOfIndexNode();
//        }
//        level = level -1;
//    }else{
//        LeafNode leafNode(bplustreeindexhdrclassptr, bplustreeindexhdrclassptr->getpagenumberofroot());
//        leafNode.print();
//    }
//}
//
//void BplusTree::mainprintbplustree(int indexheaderclassNumber){
//    char ch='y';
//    while(ch=='y'){
//        cout<<"1. print IndexHeader Structure"<<endl;
//        cout<<"2. print IndexNode or LeafNode on choice"<<endl;
//        cout<<"3. Insert a Record in the Bplustree"<<endl;
//        cout<<"4. Search a Record in the Bplustree"<<endl;
//        cout<<"5. Set fanout of the tre..."<<endl;
//        cout<<"6. To print the tree"<<endl;
//        cout<<"7. To exit"<<endl;
//        cout<<"\n\n Please enter some input to start with bplustree processing";
//        int choice;
//        cin >> choice;
//        indexheaderclass indexheaderclassvar;
//        indexheaderclassvar.openindexheaderpage(indexheaderclassNumber);
//        switch(choice){
//            case 1:
//                cout<<"\n printing IndexNode header Structure"<<endl;
//                //indexheaderclass indexheaderclassvar(indexheaderclassNumber);
//                indexheaderclassvar.indexheaderclassUserInterface();
//                break;
//
//            case 2:
//                cout<<"\nprinting IndexNode or the LeafNode"<<endl;
//                printindleaf();
//                break;
//
//            case 3:
//                cout<<"\n Insert Record User Interface is selected"<<endl;
//                mainfunctionforinsertrecord();
//                break;
//
//            case 4:
//                cout <<"\n Search Record in the BPlustree"<<endl;
//                mainfunctionforsearchrecord();
//                break;
//
//            case 5:
//                cout<<"\n Setting the Fanout of the tree"<<endl;
//                fanoutprint();
//                break;
//
//            case 6:
//                cout<<"\n=================Bplustree print=======================\n"<<endl;
//                print();
//                break;
//
//            case 7:
//                cout<<"\n\n Exiting the BPlustree"<<endl;
//                break;
//
//            default:
//                cout<<"\n Choose from the given options properly \n"<<endl;
//                break;
//        }
//        if(choice!=7){
//            cout<<"\n You are in main indexagain..."<<endl;
//            cout<<"\n You have not chosen the correct choice"<<endl;
//            cout<<"\n Do you want to choose your options again"<<endl;
//            cout<<"\n Press y to continue"<<endl;
//            cin>>ch;
//        }else{
//            break;
//        }
//    }
//}

void BplusTree::fanoutprint(){
    int fanout_new;
    do{
        cout<<"\n\t Enter the Fanout of the Tree"<<endl;
        cin>>fanout_new;

        if(fanout_new<1){
            cout<<"\nFanout value entered is less than one.. enter your fanout properly \n"<<endl;
              int fanout_new;
               do{
                      cout<<"\n\t Enter the Fanout of the Tree"<<endl;
                      cin>>fanout_new;
                     if(fanout_new<1){
                          cout<<"\nFanout value entered is less than 1. Enter the fanout again properly\n"<<endl;
                         }
                 }while(fanout_new<1);
                bplustreeindexhdrclassptr->setfanoutoftree(fanout_new);
                bplustreeindexhdrclassptr->setleafcountmax(fanout_new);
                cout<<"\n Fanout value has been resetted to \t"<<fanout_new<<endl;
       }
    }while(fanout_new<1);
    bplustreeindexhdrclassptr->setfanoutoftree(fanout_new);
    bplustreeindexhdrclassptr->setleafcountmax(fanout_new);
    cout<<"\n Fanout value has been resetted to \t"<<fanout_new<<endl;
}

void BplusTree::bplusSearchRangeKeyInLeafNodewithOperator(int leafPageNumber, const char* keyvalue, int operatorvalue, std::vector<RID>& RIDVector, std::vector<string>& keyVector){
        int flag=1;
    if(operatorvalue == EQ){ // equal to operator..
        while(flag == 1){
            if(leafPageNumber!=-1){
                LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
                flag = leafNode.searchkeyinLeafNodewithOperator(keyvalue,operatorvalue,RIDVector,keyVector);
                if(flag == 1){
                    leafPageNumber = leafNode.getrightpagevalue();
                    //leafPageNumber = leafNode.getLeftPageNumber();
                }
                if(leafPageNumber == -1){
                    flag = 0;
                }
            }
            else{
                flag == 0;
            }
        }
    }else if(operatorvalue == GT){ //greater than operator..
        while(flag == 1){
            if(leafPageNumber!=-1){
                LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
                flag = leafNode.searchkeyinLeafNodewithOperator(keyvalue,operatorvalue,RIDVector,keyVector);
                if(flag == 1){
                    leafPageNumber = leafNode.getrightpagevalue();
                }
                if(leafPageNumber == -1){
                    flag = 0;
                }
            }
            else{
                flag == 0;
            }
        }
    }else if(operatorvalue == GTEQ){ // greater than or equal to operator
        while(flag == 1){
            if(leafPageNumber!=-1){
                LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
                flag = leafNode.searchkeyinLeafNodewithOperator(keyvalue,operatorvalue,RIDVector,keyVector);
                if(flag == 1){
                    leafPageNumber = leafNode.getrightpagevalue();
                }
                if(leafPageNumber == -1){
                    flag = 0;
                }
            }else{
                flag == 0;
            }
        }
    }else if(operatorvalue == LT){ // less than operator..
        while(flag == 1){
            if(leafPageNumber!=-1){
                LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
                flag = leafNode.searchkeyinLeafNodewithOperator(keyvalue,operatorvalue,RIDVector,keyVector);
                if(flag == 1){
                    leafPageNumber = leafNode.getrightpagevalue();
                }
                if(leafPageNumber == -1){
                    flag = 0;
                }
            }else{
                flag == 0;
            }
        }
    }else if(operatorvalue == LTEQ){ // less than or equal to operator..
        while(flag == 1){
            if(leafPageNumber!=-1){
                LeafNode leafNode(bplustreeindexhdrclassptr,leafPageNumber);
                flag = leafNode.searchkeyinLeafNodewithOperator(keyvalue,operatorvalue,RIDVector,keyVector);
                if(flag == 1){
                    leafPageNumber = leafNode.getrightpagevalue();
                }
                if(leafPageNumber == -1){
                    flag = 0;
                }
            }else{
                flag == 0;
            }
        }
    }
}

void BplusTree::printindex(int pageno){
    int flag = 1;
    do{
        IndexNode indexNode;
        indexNode.openindexnodewithindexheader(bplustreeindexhdrclassptr,pageno);
        indexNode.printindex();

        cout<<"\t 1. Index Page on the Left Side"<<endl;
        cout<<"\t 2. Index Page on the right Side"<<endl;
        cout<<"\t 3. Press 3 to exit"<<endl;

        cout<<"\tEnter the input.."<<endl;
        cin>>flag;

        switch(flag){
            case 1:
                pageno = indexNode.getleftpagevalueOfIndexNode();
                if(pageno == -1){
                    cout<<"\n\t Leaf Page Number is -1.. so no more pages left. bbye!"<<endl;
                }
                break;
            case 2:
                pageno = indexNode.getrightpagevalueOfIndexNode();
                if(pageno == -1){
                    cout<<"\t Leaf Page Number is -1.. so no more pages left.. bbye!"<<endl;
                }
                break;
            case 3:
                cout<<"\t You clicked on 3.. bbye from Indexdisplay.. tada!"<<endl;
                break;
            default:
                cout<<"Dear Mr.User! please choice the options correctly. "<<endl;
                break;
        }
    }while(flag != 3 && pageno != -1);
}

void BplusTree::printleaf(int pageno){
    int flag = 1;
    do{
        //IndexNode indexNode(bplustreeindexhdrclassptr,pageno);
        LeafNode leafNode(bplustreeindexhdrclassptr,pageno);
        //indexNode.printindex();
        leafNode.printleafnode();

        cout<<"\n\t 1. Print Left Leaf"<<endl;
        cout<<"\t 2. Print Right Leaf"<<endl;
        cout<<"\t 3. 3 to exit"<<endl;

        cout<<"\tEnter the input.."<<endl;
        cin>>flag;

        switch(flag){
            case 1:
                pageno = leafNode.getLeftPageNumber();
                if(pageno == -1){
                    cout<<"\t Leaf Page Number is -1.. so no more pages left.. bbye! muah!"<<endl;
                }
                break;
            case 2:
                pageno = leafNode.getrightpagevalue();
                if(pageno == -1){
                    cout<<"\t Leaf Page Number is -1.. so no more pages left.. bbye! muah!"<<endl;
                }
                break;
            case 3:
                cout<<"\t You clicked on 3.. cheerio!"<<endl;
                break;
            default:
                cout<<"Mr.blindo! please choice the options correctly. "<<endl;
                break;
        }
    }while(flag != 3 && pageno != -1);
}


void BplusTree::getLeafandIndexPages(std::vector<int>& leafPages, std::vector<int>& indexPages){
        // First we have to check the height of the tree
    // if the height of the tree is equal to zero
    // that means it's just a leafnode.. all you gotta do is, stack up using push_back

    // if the height of the tree is not zero.. then it's a non-leaf node -meaning an index node
    // if that's the case.. call getleafandindexpages function in indexnode recursively..

    int currentheight = bplustreeindexhdrclassptr->gettreeheight();
    int foremostpage = bplustreeindexhdrclassptr->getpagenumberofroot();
    if(currentheight == 0){
        if(foremostpage != -1){
            // the current page is the rootpage.. just stack up here
            leafPages.push_back(foremostpage);
        }
    }else{
        int foremostpage = bplustreeindexhdrclassptr->getpagenumberofroot();
        indexPages.push_back(foremostpage);
        IndexNode indexnode1;
        indexnode1.openindexnodewithindexheader(bplustreeindexhdrclassptr,foremostpage);
        indexnode1.getindexandleafpages(leafPages,indexPages);
    }
}

void BplusTree::printindleaf(){
    int inputindex = 1;
    int pageno = 1;
    int flag = 1;
    while(inputindex != 3 && pageno != -1){


            cout<<"\t 1. Print index nodes"<<endl;
            cout<<"\t 2. Print leaf nodes"<<endl;
            cout<<"\t 3. 3 to exit.. "<<endl;

            cout<<"\tEnter your choice "<<endl;
            cin>>inputindex;



        vector<int> LPVector;
        vector<int> IPVector;

        getLeafandIndexPages(LPVector,IPVector);

        switch (inputindex){
            case 1:
                 if(IPVector.size() > 0){
                       cout<<"\n The index pages of the tree are ===="<<endl;
                        for(int i=0; i<IPVector.size()-1; i++){
                            cout<<IPVector.at(i)<<"-----";
                        }
                        cout<<IPVector.at(IPVector.size()-1)<<endl;
                  }else
                       cout<<"\t\tNothing is present as index pages .. adios amigo!"<<endl;
                if(IPVector.size() >= 1){
                    do{

                            cout<<"\t Enter Index Node Page Number ==="<<endl;
                            cin>>pageno;

                        flag = checkifthegivenpagenumberispresentintheindexpage(IPVector,pageno);
                        if(flag == 0){
                            cout<<"\n The page number given is not indexpage.. next time better luck==="<<endl;
                        }
                    }while(flag == 0);
                    printindex(pageno);
                }
                break;
            case 2:
                if(LPVector.size() > 0){
                       cout<<"\n The Leaf pages of the tree are ===="<<endl;
                        for(int i=0; i<LPVector.size()-1; i++){
                            cout<<LPVector.at(i)<<"-----";
                        }
                        cout<<LPVector.at(LPVector.size()-1)<<endl;
                  }else
                       cout<<"\t\tNothing is present as leaf pages .. adios amigo!"<<endl;
                if(LPVector.size() >= 1){
                    do{
                            cout<<"\t Enter Leaf Node Page Number ==="<<endl;
                            cin>>pageno;

                        flag = checkifthegivenpagenumberispresentintheleafpage(LPVector,pageno);
                        if(flag == 0){
                            cout<<"\n The page number given is not leafpage.. next time better luck==="<<endl;
                        }
                    }while(flag == 0);
                    printleaf(pageno);
                }
                break;
            case 3:
                cout<<"\t You have pressed on 3.. you're gonna exit from this print index/leaf UI function.. "<<endl;
                break;
            default:
                cout<<"\t Please enter the input correctly.. 1/2/3"<<endl;
                break;
        }
    }
}


void BplusTree::mainfunctionforinsertrecord(){
    int colnumbers = bplustreeindexhdrclassptr->getcolcount();
    int sizeofkey = bplustreeindexhdrclassptr->getsizeofkey();
    char keysize[sizeofkey];
    memset(keysize,'\0',sizeofkey);
    int i=0, position = 0;
    int key0; float key1; double key2; long key3; RID rid;
    while(i<colnumbers){
        int colformat=bplustreeindexhdrclassptr->colformat[i];
        int size = bplustreeindexhdrclassptr->sizeofcols[i];
        char vc1[size], vc2[size];
        
        switch(colformat){
            case KEY_IS_INT: // case 1 is into working if colformat takes the value of 1.. that is integer
                cout<<"\n\tplease enter the Integer key that has to be inserted into tree ---"<<endl;
                cin>>key0;
                memcpy(&keysize[position],&key0,sizeof(int));
                break;
            case KEY_IS_FLOAT: // 2 is for float
                cout<<"\n\tplease enter the FLOAT key that has to be inserted into tree --- "<<endl;
                cin>>key1;
                memcpy(&keysize[position],&key1,sizeof(float));
                break;
            case KEY_IS_DOUBLE:// 3 is for double
                cout<<"\n\tplease enter the DOUBLE key that has to be inserted into tree..."<<endl;
                cin>>key2;
                memcpy(&keysize[position],&key2,sizeof(double));
                break;
            case KEY_IS_LONG: // 4 is for long
                cout<<"\n\tplease enter the LONG key that has to be inserted into tree...."<<endl;
                cin>>key3;
                memcpy(&keysize[position],&key3,sizeof(long));
                break;
            case KEY_IS_VARCHAR:
                cout<<"\n\tplease enter the VARCHAR key that has to be inserted into tree...."<<endl;
                cin>>vc1;
                memcpy(&keysize[position],vc1,size);
                break;
            default:
                cout<<"\n\tplease enter the DEFAULT (VARCHAR) key that has to be inserted into tree...."<<endl;
                cin>>vc2;
                memcpy(&keysize[position],vc2,size);
                break;
        }
        int movement = bplustreeindexhdrclassptr->sizeofcols[i];
        position = position + movement;
        i++;
    }
    cout<<"\n\tEnter page number.. "<<endl;
    cin>>rid.pageNumber;

    cout<<"\n\tEnter slot number..."<<endl;
    cin>>rid.slotNumber;

    insertIntoBplusTree(keysize,rid);
}

void BplusTree::mainfunctionofinsertrecordforarange(){
    int colnumber = bplustreeindexhdrclassptr->getcolcount();
    int i=0, position = 0;
    int startingrangeint, endingrangeint, incrementint;
    float startingrangefloat, endingrangefloat, incrementfloat;
    double startingrangedouble, endingrangedouble, incrementdouble;
    long startingrangelong, endingrangelong, incrementlong;
    int totalnumberofkeys;// For varchar
    int loopcounter =0;
    while(loopcounter < colnumber){
        int typeofcol = bplustreeindexhdrclassptr->colformat[i];
        switch(typeofcol){
            case KEY_IS_INT: // for integer
                cout<<"Enter the starting range"<<endl;
                cin>>startingrangeint;
                cout<<"Enter the ending range"<<endl;
                cin>>endingrangeint;
                cout<<"Enter the increment factor"<<endl;
                cin>>incrementint;
                time_t start, end, diff;
                time(&start);
                cout<<"\n The start time for this operation is.. "<<start<<endl;
                rangecheckfunctionforint(startingrangeint,endingrangeint,incrementint);
                time(&end);
                cout<<"\n The start time for this operation is.. "<<end<<endl;
                diff = difftime(end, start);
                cout<<"The time taken for operation is"<<diff<<endl;
                break;

            case KEY_IS_FLOAT: // for float
                cout<<"Enter the starting range"<<endl;
                cin>>startingrangefloat;
                cout<<"Enter the ending range"<<endl;
                cin>>endingrangefloat;
                cout<<"Enter the increment factor"<<endl;
                cin>>incrementfloat;
                rangecheckfunctionforfloat(startingrangefloat,endingrangefloat,incrementfloat);
                break;

            case KEY_IS_DOUBLE: // for double
                cout<<"Enter the starting range"<<endl;
                cin>>startingrangedouble;
                cout<<"Enter the ending range"<<endl;
                cin>>endingrangedouble;
                cout<<"Enter the increment factor"<<endl;
                cin>>incrementdouble;
                rangecheckfunctionfordouble(startingrangedouble,endingrangedouble,incrementdouble);
                break;

            case KEY_IS_LONG: // for long
                cout<<"Enter the starting range"<<endl;
                cin>>startingrangelong;
                cout<<"Enter the ending range"<<endl;
                cin>>endingrangelong;
                cout<<"Enter the increment factor"<<endl;
                cin>>incrementlong;
                rangecheckfunctionforlong(startingrangelong,endingrangelong,incrementlong);
                break;
        }
        loopcounter = loopcounter + 1;
    }
}

void BplusTree::mainfunctionfordeleterecord(){
    // main function for delete record.. has to be written yet! It will take time for lazybones to do it!
    int colnumbers = bplustreeindexhdrclassptr->getcolcount();
    int sizeofkey = bplustreeindexhdrclassptr->getsizeofkey();
    char keysize[sizeofkey];
    memset(keysize,'\0',sizeofkey);
    int i=0, position = 0;
    RID rid;
    while(i<colnumbers){
        int colformat=bplustreeindexhdrclassptr->colformat[i];
        int size = bplustreeindexhdrclassptr->sizeofcols[i];
        int key0; float key1; double key2; long key3;
        char vc1[size], vc2[size];
        cout<<"\n\tplease enter the key that has to be deleted from the tree.. "<<endl;
        switch(colformat){
            case KEY_IS_INT: // case 1 is into working if colformat takes the value of 1.. that is integer
                cin>>key0;
                memcpy(&keysize[position],&key0,sizeof(int));
                break;
            case KEY_IS_FLOAT: // 2 is for float
                cin>>key1;
                memcpy(&keysize[position],&key1,sizeof(float));
                break;
            case KEY_IS_DOUBLE:// 3 is for double
                cin>>key2;
                memcpy(&keysize[position],&key2,sizeof(double));
                break;
            case KEY_IS_LONG: // 4 is for long
                cin>>key3;
                memcpy(&keysize[position],&key3,sizeof(long));
                break;
            case KEY_IS_VARCHAR:
                cin>>vc1;
                memcpy(&keysize[position],vc1,size);
                break;
            default:
                cin>>vc2;
                memcpy(&keysize[position],vc2,size);
                break;
        }
        int movement = bplustreeindexhdrclassptr->sizeofcols[i];
        position = position + movement;
        i++;
    }
    cout<<"\n\tEnter page number which has to be deleted.. "<<endl;
    cin>>rid.pageNumber;

    cout<<"\n\t Enter slot number corresponding to the slot number that has to be deleted.. ..."<<endl;
    cin>>rid.slotNumber;

    deleteFromBplusTree(keysize,rid);
//    insertIntoBplusTree(keysize,rid);
}
//
void BplusTree::mainfunctionfordeleterecordinarange(){
    // main function for delete range has to be written it -- shall be done in december.. more or less!
    int colnumber = bplustreeindexhdrclassptr->getcolcount();
    int i=0, position = 0;
    int startingrangeint, endingrangeint, incrementint;
    float startingrangefloat, endingrangefloat, incrementfloat;
    double startingrangedouble, endingrangedouble, incrementdouble;
    long startingrangelong, endingrangelong, incrementlong;
    int loopcounter =0;
    while(loopcounter < colnumber){
        int typeofcol = bplustreeindexhdrclassptr->colformat[i];
        switch(typeofcol){
            case KEY_IS_INT: // for integer
                cout<<"Enter the starting range from where the int deletion should start"<<endl;
                cin>>startingrangeint;
                cout<<"Enter the ending range from till where the int deletion should go on"<<endl;
                cin>>endingrangeint;
                rangedeletecheckforint(startingrangeint,endingrangeint);
              //  rangecheckfunctionforint(startingrangeint,endingrangeint,incrementint);
                break;

            case KEY_IS_FLOAT: // for float
                cout<<"Enter the starting range for float deletion"<<endl;
                cin>>startingrangefloat;
                cout<<"Enter the ending range for float deletion"<<endl;
                cin>>endingrangefloat;
                rangedeletecheckforfloat(startingrangefloat,endingrangefloat);
               // rangecheckfunctionforfloat(startingrangefloat,endingrangefloat,incrementfloat);
                break;

            case KEY_IS_DOUBLE: // for double
                cout<<"Enter the starting range for double deletion"<<endl;
                cin>>startingrangedouble;
                cout<<"Enter the ending range for double deletion"<<endl;
                cin>>endingrangedouble;
                rangedeletecheckfordouble(startingrangedouble,endingrangedouble);
                //rangecheckfunctionfordouble(startingrangedouble,endingrangedouble,incrementdouble);
                break;

            case KEY_IS_LONG: // for long
                cout<<"Enter the starting range for long deletion"<<endl;
                cin>>startingrangelong;
                cout<<"Enter the ending range for long deletion"<<endl;
                cin>>endingrangelong;
                rangedeletecheckforlong(startingrangelong,endingrangelong);
                //rangecheckfunctionforlong(startingrangelong,endingrangelong,incrementlong);
                break;
        }
        loopcounter = loopcounter + 1;
    }
}

void BplusTree::mainfunctionforsearchrecord(){
   // main function for search along with operator option has to be written.. would be done later
    // This should be the same search using operator also ..
    // 1 for equal to, 2 greater than, 3 greater than equal to, 4 less than, 5 less than equal to..
    int keysize = bplustreeindexhdrclassptr->getsizeofkey();
    int position = 0;
    char fullkey[keysize];
    memset(fullkey,'\0',keysize);
    int colnumber = bplustreeindexhdrclassptr->getcolcount();
    int loopcounter =0;
    while(loopcounter < colnumber){
        int colformat=bplustreeindexhdrclassptr->colformat[loopcounter];
        int size = bplustreeindexhdrclassptr->sizeofcols[loopcounter];
        int key0; float key1; double key2; long key3;
        char vc1[size];
        memset(vc1,'\0',size);
        switch(colformat){
            case KEY_IS_INT: // first case for int..
                cout<<"Enter the integer key to be searched..."<<endl;
                cin>>key0;
                memcpy(&fullkey[position],&key0,sizeof(int));
                break;

            case KEY_IS_FLOAT: // second case for float
                cout<<"Enter the float key to be searched..."<<endl;
                cin>>key1;
                memcpy(&fullkey[position],&key1,sizeof(float));
                break;

            case KEY_IS_DOUBLE:
                cout<<"Enter the double key to be searched..."<<endl;
                cin>>key2;
                memcpy(&fullkey[position],&key2,sizeof(double));
                break;

            case KEY_IS_LONG:
                cout<<"Enter the long key to be searched..."<<endl;
                cin>>key3;
                memcpy(&fullkey[position],&key3,sizeof(long));
                break;

            case KEY_IS_VARCHAR:
                cout<<"Enter the varchar to be searched..."<<endl;
                cin>>vc1;
                int varcharsize = bplustreeindexhdrclassptr->sizeofcols[loopcounter];
                memcpy(&fullkey[position],vc1,sizeof(varcharsize));
                break;
        }
        int keysizeiterator  = bplustreeindexhdrclassptr->sizeofcols[loopcounter];
        position = position + keysizeiterator;
        loopcounter = loopcounter + 1;
    }

    // the key fullkey has been filled up now..the searchprocess should basically begin here..
    int inputoperator;
    cout<<"You have formed the key -- congratulations.. now select which one of the operators you would choose to"
            <<"use as a search basis"<<endl;
    do{
    cout<<"1. Equal to Operator (==)"<<endl;
    cout<<"2. Greater than Operator (>)"<<endl;
    cout<<"3. Greater than or equal top operator (>=)"<<endl;
    cout<<"4. Less then Operator..(<)"<<endl;
    cout<<"5. Less than or equal to operator (<=)"<<endl;
    cout<<"Please choose one of the operators to proceed"<<endl;
    cin>>inputoperator;
    }while(inputoperator>5);

    cout<<"The operator you chose to proceed with is...."<<inputoperator<<endl;

    int startleafpagenumber = searchInBplusTree(fullkey);
    cout<<"Passed one stage.. "<<endl;
    std::vector<RID> ridvec;
    std::vector<string> keyvec;

    bplusSearchRangeKeyInLeafNodewithOperator(startleafpagenumber,fullkey,inputoperator,ridvec,keyvec);

    // Now the search results will have to be displayed..
    // choosing a dummy RID for display
    cout<<"The size of rid vector is"<<ridvec.size();
    if(ridvec.size() != 0){
    RID displayrid;
    string displaykey;
    int looper=0;
    for(looper=0; looper<ridvec.size(); looper++){
        displayrid = ridvec.at(looper);
        displaykey = keyvec.at(looper);
        cout<<"The key value is =====================";
        BplusTree::printKey(displaykey.c_str(),bplustreeindexhdrclassptr);
        cout<<"The corresponding rid's page number and slot number are......... "
                <<displayrid.pageNumber<<"=====and====="<<displayrid.slotNumber<<"======respectively"<<endl;
    }
    }else{
        cout<<"The search resulted in zero results... try again!"<<endl;
    }
}

void BplusTree::mainfunctionforrangesearchrecord(){
    // this is basically the function for range search.. give first key and last key and I will get the keys in between..
     int keysize = bplustreeindexhdrclassptr->getsizeofkey();
    int position = 0;
    char fullkey[keysize];
    char fullkeyend[keysize];
    memset(fullkey,'\0',keysize);
    memset(fullkeyend,'\0',keysize);
    int colnumber = bplustreeindexhdrclassptr->getcolcount();
    int loopcounter =0;
    while(loopcounter < colnumber){
        int colformat=bplustreeindexhdrclassptr->colformat[loopcounter];
        int size = bplustreeindexhdrclassptr->sizeofcols[loopcounter];
        int key0, key00; float key1, key11; double key2, key22; long key3, key33;
        char vc1[size], vc2[size];
        memset(vc1,'\0',size);
        memset(vc2,'\0',size);
        switch(colformat){
            case KEY_IS_INT: // first case for int..
                cout<<"Enter the first integer key to be searched..."<<endl;
                cin>>key0;
                memcpy(&fullkey[position],&key0,sizeof(int));
                cout<<"Enter the last integer key to be searched..."<<endl;
                cin>>key00;
                memcpy(&fullkeyend[position],&key00,sizeof(int));
                break;

            case KEY_IS_FLOAT: // second case for float
                cout<<"Enter the first float key to be searched..."<<endl;
                cin>>key1;
                memcpy(&fullkey[position],&key1,sizeof(float));
                cout<<"Enter the last float key to be searched..."<<endl;
                cin>>key11;
                memcpy(&fullkeyend[position],&key11,sizeof(float));
                break;

            case KEY_IS_DOUBLE:
                cout<<"Enter the first double key to be searched..."<<endl;
                cin>>key2;
                memcpy(&fullkey[position],&key2,sizeof(double));
                cout<<"Enter the final double key to be searched..."<<endl;
                cin>>key22;
                memcpy(&fullkeyend[position],&key22,sizeof(double));
                break;

            case KEY_IS_LONG:
                cout<<"Enter the first long key to be searched..."<<endl;
                cin>>key3;
                memcpy(&fullkey[position],&key3,sizeof(long));
                cout<<"Enter the final long key to be searched..."<<endl;
                cin>>key33;
                memcpy(&fullkeyend[position],&key33,sizeof(long));
                break;

            case KEY_IS_VARCHAR:
                cout<<"Enter the varchar to be searched..."<<endl;
                cin>>vc1;
                int varcharsize = bplustreeindexhdrclassptr->sizeofcols[loopcounter];
                memcpy(&fullkey[position],vc1,sizeof(varcharsize));
                break;
        }
        int keysizeiterator  = bplustreeindexhdrclassptr->sizeofcols[loopcounter];
        position = position + keysizeiterator;
        loopcounter = loopcounter + 1;
    }
    int rangecheckcompare = BplusTree::keyComp(fullkeyend,fullkey,bplustreeindexhdrclassptr->getcolcount(),bplustreeindexhdrclassptr);

    if(rangecheckcompare > 0){
            int startleafpagenumber = searchInBplusTree(fullkey);
             std::vector<RID> ridvec;
             std::vector<string> keyvec;
             getKEYRIDRange(startleafpagenumber,fullkey,fullkeyend,ridvec,keyvec);
            // Now the search results will have to be displayed..
            // choosing a dummy RID for display
            if(ridvec.size() != 0){
                RID displayrid;
                string displaykey;
                int looper=0;
                for(looper=0; looper<ridvec.size(); looper++){
                    displayrid = ridvec.at(looper);
                    displaykey = keyvec.at(looper);
                    cout<<"\nThe key value is ===";
                    BplusTree::printKey(displaykey.c_str(),bplustreeindexhdrclassptr);
                    cout<<"\nThe corresponding rid's page number and slot number are == "
                        <<displayrid.pageNumber<<"==and=="<<displayrid.slotNumber<<"==respectively"<<endl;
                }
           }else{
                cout<<"The search resulted in zero results... try again!"<<endl;
            }
    }
    else{
        cout<<"Initial Range is greater than final range.. Error! recheck your ranges please.."<<endl;
    }
}
//################################################################################
// ###################################End of Bplus Functions#####################3
//##################################################################################################



// ================================= STRING STREAM FUNCTIONS ==========================================

void indexheaderclass::indexheadertoString(){
  std::ostringstream mystream;
    mystream.str("");
    mystream.clear();
    mystream << "\n\tIndex Header Page User Interface"<<endl;
    mystream<<"\n--------------------------------------"<<endl;

    mystream <<"\tIndex Header Page Number is  --- "<<getPageNumber()
            <<endl;

    mystream <<"\tRoot Page Number is --- "<<getpagenumberofroot()
            <<endl;

    mystream <<"\t IndexNode fanout is --- " <<getfanoutoftree()
            <<endl;

    mystream <<"\t Leaf Node Fanout is! --- " << getleafcountmax()
            <<endl;

    mystream <<"\t Height of the tree --- "<<gettreeheight()
            <<endl;

   mystream <<"\t Number of Columns in Index --- " <<getcolcount()
            <<endl;

   mystream<<"\t Key Size is --- " <<getsizeofkey()
          <<endl;

   mystream <<"\t Number of Keys are -- " <<getNumberOfKeys()
            <<endl;

/*
    for(int i=0; i<getcolcount(); i++){
        char columntype[10];
        memset(columntype,'\0',10);

        switch(colformat[i]){
            case 1: // 1 for integer
                memcpy(columntype, "INTEGER", sizeof("INTEGER"));
                break;
            case 2: // 2 for float
                memcpy(columntype,"FLOAT",sizeof("FLOAT"));
                break;
            case 3: // 3 for double
                memcpy(columntype, "DOUBLE", sizeof("DOUBLE"));
                break;
            case 4: // 4 for long
                memcpy(columntype, "LONG", sizeof("LONG"));
                break;
            case 5: // 5 for varchar
                memcpy(columntype, "VARCHAR", sizeof("VARCHAR"));
                break;
        }
        mystream << "\t Column Types [field"<<i + 1 << "]=========="
                <<columntype<<endl; */

        mystream << "\t ----------------------------------------------END INDEXHEADER"<<endl;
        cout << mystream.str();
}

void IndexNode::indexNodeToString(){
    std::ostringstream mystream;
    mystream.str("");
    mystream.clear();
    mystream<<"\nIndex Node UI"<<endl;
    mystream<<"================"<<endl;

    mystream<<"Current Index Page Number   ============"<<getPageNumber()<<endl;
    mystream<<"Parent Page Number          ============"<<getParentofIndexNode()<<endl;
    mystream<<"Level of Index Node         ============"<<getIndexNodeLevel()<<endl;
    mystream<<"Number of Keys in IndexNode ============"<<indexnodehdrstr.noOfKeys<<endl;
    mystream<<"The content in the Index Node is"<<endl;
    mystream<<"================================="<<endl;
    mystream<<"\nLeft Index Page Number     ==========="<<getleftpagevalueOfIndexNode()<<endl;
    mystream<<"\nRight Index Page Number    ==========="<<getrightpagevalueOfIndexNode()<<endl;

    int position = IndexNode::getIndexNodeHeaderSize();
    int leftpageno;
    char keysize[indexhdr->getsizeofkey()];

    for(int i=0;i<getNoOfKeysInIndexNode(); i++){
        memcpy(&leftpageno,&indexnodedata[position],sizeof(int));
        position = position + sizeof(int);

        memcpy(keysize,&indexnodedata[position],indexhdr->getsizeofkey());
        position = position + indexhdr->getsizeofkey();

        mystream<<leftpageno<<"==";
        mystream<<"key value is  {";
        BplusTree::printKey(keysize,indexhdr);
        mystream<<"}";
        mystream<<"==";
    }

    memcpy(&leftpageno,&indexnodedata[position],sizeof(int));
    mystream<<leftpageno<<"=="<<endl;

    mystream<<"\t--------------------------------------------------"<<endl;
    mystream<<"\tThat's pretty much the data in Index Node=="<<endl;

    cout << mystream.str();
}

void LeafNode::leafNodetoString(){
    std::ostringstream mystream;
    mystream.str("");
    mystream.clear();
    mystream<<endl;
    mystream<<"Leaf Node UI"<<endl;
    mystream<<"============="<<endl;
    mystream<<"\tCurrent Leaf Page Number   ======="<<getPageNumber()<<endl;
    mystream<<"\tParent Page Nymber         ======="<<getparentpagevalue()<<endl;
    mystream<<"\tRecords in Leaf Node       ======="<<getNoOfRecordsInNode()<<endl;

    mystream<<"\nThe Records in Leaf Node are";
    mystream<<"\n============================="<<endl;
    mystream<<endl;
    char key[indexhdr->getsizeofkey()];
    RID rid;
    int position = LeafNode::getLeafNodeHeaderSize();
    for(int loopcounter = 0; loopcounter < leafnodehdrstr.noOfRecords; loopcounter++){
        memcpy(key,&leafnodedata[position],indexhdr->getsizeofkey()); // RID leangth is RIDSIZE...
        position = position + indexhdr->getsizeofkey();
        mystream<<"The key at position {"<<loopcounter<<"} is ===";
        BplusTree::printKey(key, indexhdr);
        memcpy(&rid,&leafnodedata[position],RIDSIZE);
        mystream<<"\nPage Number is     ==="<<rid.pageNumber;
        mystream<<"\n Slot Number is    ==="<<rid.slotNumber<<endl;
        position = position + RIDSIZE; // Rid length is RIDSIZE..
    }

    mystream<<"End of Leaf Node Records"<<endl;
    mystream<<"========================="<<endl;

    mystream<<"The Left and Right Page Numbers to this Leaf Node are"<<endl;
    mystream<<"-----------------------------------------------------"<<endl;

    mystream<<"Left Leaf Page Number    ===="<<getLeftPageNumber()<<endl;
    mystream<<"Right Leaf Page Number   ===="<<getrightpagevalue()<<endl;

    cout << mystream.str();

   
}