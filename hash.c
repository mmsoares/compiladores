#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

int labelCounter = 0;
int tempCounter = 0;

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
	if(newnode = hashFind(text))
		return newnode;
	int address = hashAddress(text);
	newnode = calloc(1,sizeof(struct hash_node_struct));
	newnode->type = type;
	newnode->text = calloc(strlen(text)+1,sizeof(char));
	strcpy(newnode->text,text);
	newnode->dataType = DT_NOT_SET;
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

void hashFree(void) {
	int i;
	HASH_NODE *aux = 0;
	HASH_NODE *aux2 = 0;

	for(i=0;i<HASH_SIZE; i++) {
		aux = Table[i];

		while(aux != NULL) {
			aux2 = aux->next;
			free(aux);
			aux = aux2;
		}
	}
}

HASH_NODE* makeLabel() {
	char label[256];
	sprintf(label, "_label%d", labelCounter++);
	return hashInsert(label, SYMBOL_LABEL);
}

HASH_NODE* makeTemp() {
	char temp[256];
	sprintf(temp, "_temp%d", tempCounter++);
	return hashInsert(temp, SYMBOL_TEMP);
}