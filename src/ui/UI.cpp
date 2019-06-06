/* 
 * File:   UI.cpp
 * Author: anmol
 * 
 * Created on 5 December, 2010, 7:00 PM
 */

#include "UI.h"
#include <string.h>
#include <iomanip>


UI::UI() {
}

UI::UI(const UI& orig) {
}

UI::~UI() {
}
//void UI::PrintData(mega_struct* mega);
void UI::PrintData(mega_struct* mega)
{
    int entryType;
    int i;

    cout << endl;
    for ( i=0; i<mega->NumPattr; i++)
    {
        entryType = mega->Pattr[i]->type;

        switch (entryType)
        {
            case INT:
                cout << std::setw(20) << std::left << *((int*)mega->Pattr[i]->value) << " ";
                break;
            case FLOAT:
                cout << std::setw(20) << std::left << *((float*)mega->Pattr[i]->value) << " ";
                break;
            case VARCHAR:
                cout << std::setw(20) << std::left << (char*)mega->Pattr[i]->value << " ";
                //printf("%s\t\t",(char*)mega->Pattr[i]->value);
                break;
            case CHAR:
                cout << std::setw(20) << std::left << (char*)mega->Pattr[i]->value << " ";
                break;
            default:
                cout << "UI ERROR:: Unrecognized Type" << " ";
        }
    }

    cout <<"---";
    
    for ( i=0; i<mega->NumSattr; i++)
    {
        entryType = mega->Sattr[i]->type;

        switch (entryType)
        {
            case INT:
                cout << std::setw(20) << std::left << *((int*)mega->Sattr[i]->value) << " ";
                break;
            case FLOAT:
                cout << std::setw(20) << std::left << *((float*)mega->Sattr[i]->value) << " ";
                break;
            case VARCHAR:
                cout << std::setw(20) << std::left << (char*)mega->Pattr[i]->value << " ";
                //printf("%s\t\t",(char*)mega->Sattr[i]->value);
                break;
            case CHAR:
                cout << std::setw(20) << std::left << (char*)mega->Sattr[i]->value << " ";
                break;
            default:
                cout << "UI ERROR:: Unrecognized Type" << "\t\t";
        }
    }
    cout << endl;
}

void UI::PrintColumns(mega_struct* mega)
{
    cout << endl;
    long printSize=0;

    for ( int i=0; i<mega->NumPattr; i++)
    {
        cout << std::setw(20) << std::left << mega->Pattr[i]->attr_name << " ";
    }

    cout <<"---";

    for ( int i=0; i<mega->NumSattr; i++)
    {
        cout << std::setw(20) << std::left << mega->Sattr[i]->attr_name << " ";
    }

    cout << endl << endl;
    
}

void UI::PrintSchema(mega_struct *mega){

    cout << std::setw(15) << std::left << "Field" <<" "<< std::setw(15) << std::left << "Type" <<" "<< std::setw(15) << std::left <<
            std::setw(15) << std::right << "Null" <<" "<< std::setw(15) << std::right << "Key" <<" "<< std::setw(15) << std::right <<
            "Default" << endl << endl;

    for ( int i=0; i<mega->NumPattr; i++)
    {
        cout << std::setw(15) << std::left << mega->Pattr[i]->attr_name << " ";
        if(mega->Pattr[i]->type == 1 ){

            cout << std::setw(15) << std::left << "INT" << " ";
        }else if(mega->Pattr[i]->type == 2 ){

            cout <<std::left << "VARCHAR("<< mega->Pattr[i]->length<< std::setw(5) << std::left<<")" << " ";
        }else if(mega->Pattr[i]->type == 3 ){

            cout << std::left << "CHAR("<<mega->Pattr[i]->length<< std::setw(8) << std::left<< ")" << " ";
        }else if(mega->Pattr[i]->type == 4 ){

            cout << std::setw(15) << std::left << "FLOAT" << " ";
        }
        if(mega->Pattr[i]->IsNull == true){
        
            cout << std::setw(15) << std::right <<"TRUE"  << " ";
        }
        else{
        
            cout << std::setw(15) << std::right <<"FALSE"  << " ";
        }
        if(mega->Pattr[i]->IsPrimary == true){
        
            cout << std::setw(15) << std::right <<"TRUE" ;
        }
        else{

            cout << std::setw(15) << std::right <<"FALSE"  << " ";
        }
        cout <<endl;

    }
    

}