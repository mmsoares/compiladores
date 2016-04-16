/* begin standard C headers. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

//implementação das funções como visto em aula



void hashInit(void){
	int i;
	for(i=0;i<HASH_SIZE;++i)
		Table[i] = 0;
}

int hashAddress(char *text){
	int address = 1;
	int i;
	for(i=0 ;i<strlen(text);++i)
		address = (address * text[i]%HASH_SIZE + 1);
	return address - 1;
}

HASH_NODE *hashFind(char *text){
	int i = 0;
	HASH_NODE *node;
	int address = hashAddress(text);
	for(node = Table[i]; node; node->next)
		if(strcmp(node->text,text))
			return node;
	return 0;
}

HASH_NODE *hashInsert(char *text, int type){

	HASH_NODE *newnode;
	if(newnode == hashFind(text))
		return newnode;
	int address = hashAddress(text);
	newnode = (HASH_NODE *) calloc(1,sizeof(HASH_NODE));
	newnode->type = type;
	newnode->text = calloc(strlen(text)+1,sizeof(char));
	strcpy(newnode->text,text);
	newnode->next = Table[address];
	Table[address] = newnode;

	return newnode;
	
}

void hashPrint(void){
	int i;
	HASH_NODE *node = 0;
	for(i=0;i<HASH_SIZE;i++)
		for(node = Table[i];node;node = node->next)
			printf("Table[%d] = type: %d, value: %s\n",i,node->type, node->text);
	
}
