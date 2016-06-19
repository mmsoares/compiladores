#include "tac.h"
#include "hash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern  FILE    *outputFile;

int data = 0;
int text = 0;

void printTextSection() {
	if(text == 0) {
		fprintf(outputFile, ".text\n");
	}
	text++;
}

void printDataSection() {
	if(data == 0) {
		fprintf(outputFile, ".data\n");
	}
	data++;
}

void generateAssembler(TAC_NODE* list) {
	int asciiValue;
	double doubleValue;
	int boolValue;

	while(list){
		switch(list->type){
			case TAC_DECLARACAO_VARIAVEL:
					printDataSection();
					fprintf(outputFile,"\t.globl	%s\n", list->result->text);
					fprintf(outputFile,"\t.type %s, @object\n",list->result->text);
					fprintf(outputFile,"\t.size %s, 4\n",list->result->text);
					fprintf(outputFile,"%s:\n",list->result->text);

					switch(list->result->dataType){
						case DT_INT:
						case DT_REAL:
							fprintf(outputFile,"\t.long	%s\n",list->operator1->text);
							break;
						case DT_CHAR:
							asciiValue = (int) list->operator1->text[0];
							fprintf(outputFile,"\t.byte %d\n", asciiValue);
							break;
						case DT_BOOL:
							boolValue = strcmp(list->operator1->text, "FALSE") == 0 ? 0 : 1;
							fprintf(outputFile,"\t.byte %d\n", boolValue); 
							break;
					}
					break;
				
				case TAC_DECLARACAO_VETOR_VAZIO:
					printDataSection();
					fprintf(outputFile,"\t.comm	vetor,%d,4\n", 4*(atoi(list->operator1->text)));
					break;

				case TAC_DECLARACAO_VETOR:
					printDataSection();
					fprintf(outputFile,"\t.globl	%s\n", list->result->text);
					fprintf(outputFile,"\t.type %s, @object\n",list->result->text);
					fprintf(outputFile,"\t.size %s, %d\n",list->result->text,4*(atoi(list->operator1->text)));
					fprintf(outputFile,"%s:\n",list->result->text);
					break;

				case TAC_VECTOR_ASSIGN:
					switch(list->result->dataType){
						case DT_INT:
						case DT_REAL:
							fprintf(outputFile,"\t.long	%s\n",list->operator1->text);
							break;
						case DT_CHAR:
							asciiValue = (int) list->operator2->text[0];
							fprintf(outputFile,"\t.byte %d\n", asciiValue);
							break;
						case DT_BOOL:
							boolValue = strcmp(list->operator2->text, "FALSE") == 0 ? 0 : 1;
							fprintf(outputFile,"\t.byte %d\n", boolValue); 
							break;
					}
					break;

				case TAC_COMECO_FUNCAO:
						printTextSection();
					
					break;
				case TAC_ATRIBUICAO:
						printTextSection();
						switch(list->operator1->type) {
							case SYMBOL_IDENTIFIER:
							case SYMBOL_TEMP:
							case SYMBOL_LABEL:
								fprintf(outputFile, "\tmovl %s(%%rip), %%eax\n", list->operator1->text);
								fprintf(outputFile, "\tmovl %%eax, %s(%%rip)\n", list->result->text);
								break;
							default:
								fprintf(outputFile, "\tmovl $%s, %s(%%rip)\n", list->operator1->text, list->result->text);
								break;
						}
		}

		list = list->next;
	}
}

