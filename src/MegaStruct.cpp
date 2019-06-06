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

#include "MegaStruct.h"

MegaStruct::MegaStruct() {
}

MegaStruct::MegaStruct(const MegaStruct& orig) {
}

MegaStruct::~MegaStruct() {
}

mega_struct* MegaStruct::Initialize()
{
    mega_struct *mega;
    mega = (mega_struct *)malloc( sizeof(mega_struct) );
    return mega;
}

void MegaStruct::Allocate(mega_struct* mega)
{
   int i, len;
   if(mega->Relation != DELETE){
   for ( i=0; i<mega->NumPattr; i++)
   {
       len = mega->Pattr[i]->length;
       if ( len )
       {
           mega->Pattr[i]->value = malloc(len);
           memset ( (char *)(mega->Pattr[i]->value), NULL, len );
       }
   }
   }

   for ( i=0; i<mega->NumSattr; i++)
   {
       len = mega->Sattr[i]->length;
       if ( len )
       {
           mega->Sattr[i]->value = malloc(len);
           memset ( (char *)(mega->Sattr[i]->value), NULL, len );
       }
   }
}

void MegaStruct::Clean(mega_struct* mega)
{
    int i, len;
    if(mega->Relation != DELETE){
   for ( i=0; i<mega->NumPattr; i++)
   {
       len = mega->Pattr[i]->length;
       if ( len )
       {
           memset ( (char *)(mega->Pattr[i]->value), NULL, len );
       }
   }
    }
   for ( i=0; i<mega->NumSattr; i++)
   {
       len = mega->Sattr[i]->length;
       if ( len )
       {
           memset ( (char *)(mega->Sattr[i]->value), NULL, len );
       }
   }
}

void MegaStruct::Destroy(mega_struct** mega)
{
    int i, len;
    mega_struct *dmega;
    dmega = *mega;

    if ( dmega == NULL )
        return;


   for ( i=0; i<dmega->NumPattr; i++)
   {
       len = dmega->Pattr[i]->length;
       if ( len )
       {
           void *tmp;
           tmp = dmega->Pattr[i]->value;
           dmega->Pattr[i]->value = NULL;
           free(tmp);
       }
   }

    while(dmega->Pattr.size() > 0){
        dmega->Pattr.pop_back();
    }
   for ( i=0; i<dmega->NumSattr; i++)
   {
       len = dmega->Sattr[i]->length;
       if ( len )
       {
           void *tmp;
           tmp = dmega->Sattr[i]->value;
           dmega->Sattr[i]->value = NULL;
           free(tmp);
       }
   }
     while(dmega->Sattr.size() > 0){
        dmega->Sattr.pop_back();
    }

    while(dmega->Condition.size() > 0){
        dmega->Condition.pop_back();
    }
    *mega = NULL;
    free (dmega);
}