/* begin standard C headers. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

void hashInit(void){
	int i;
	for(i=0;i<HASH_SIZE;++i)
		Table[i] = NULL;
}

int hashAddress(char *text){
	int address = 1;
	int i;
	for(i=0 ;i<strlen(text);++i)
		address = (address * text[i]%HASH_SIZE + 1);
	return address - 1;
}

HASH_NODE *hashFind(char *text){
	int address = hashAddress(text);
	HASH_NODE *node;

	for(node = Table[address]; node; node->next){
		if(strcmp(node->text,text)==0){
			return node;
		}
	}

	return NULL;
}

HASH_NODE *hashInsert(char *text, int type){

	HASH_NODE *newnode;
	if(hashFind(text)!= NULL){
		return hashFind(text);
	}
	int address = hashAddress(text);
	newnode = (HASH_NODE *) calloc(1,sizeof(HASH_NODE));
	newnode->type = type;
	newnode->text = calloc(strlen(text)+1,sizeof(char));
	strcpy(newnode->text,text);
	newnode->dataType = DT_UNDEFINED;
	newnode->nature = NATURE_UNDEFINED;
	newnode->next = Table[address];
	Table[address] = newnode;

	return newnode;
	
}

void hashPrint(void){
	int i;
	HASH_NODE *node = 0;
	for(i=0;i<HASH_SIZE;i++)
		for(node = Table[i];node;node = node->next)
			printf("Table[%d] = type: %d, value: %s, dataType: %d, nature: %d\n",i,node->type, node->text, node->dataType, node->nature);
	
}
