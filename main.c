/* 
 * File:   main.c
 * Author: Luiz Otavio
 *
 * Created on October 26, 2015, 5:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 0
#define MAX 500

typedef struct message_st{
    char message[MAX];
    int pair_id;
    int order;
} Message;

typedef struct list_st{    
    Message message;
    struct list_st *prox;
}List;

typedef struct arr_st{
    int pair_id;
    int msg_sent_count;
    List *list;
    struct arr_st* prox;
}Arr;

void insertOnList(Arr *root, int id, int order, char* msg){
    
    List *aux;
    
    root->pair_id = id;
    aux = root->list;

    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->message.order = order;
    aux->message.pair_id = id;
    strcpy(aux->message.message, msg);
    aux->prox = (List *) malloc( sizeof(List) );
}


Arr* queueing(Arr *root){
   
    Arr *queue, *head;
    int id_count;
    
    head = (Arr *)malloc( sizeof(Arr) );
    id_count = 0;
    
    while(id_count < 30){
	while(root->prox != NULL){
	    queue = head;
	    while(queue->prox != NULL){
		queue = queue->prox;
	    }
	    if(root->pair_id == id_count){
		queue->pair_id = root->pair_id;
		queue->list = (List *) malloc( sizeof(List) );
		queue->list->message.order = root->list->message.order;
		strcpy(queue->list->message.message, root->list->message.message);
		queue->prox = (Arr *) malloc( sizeof(Arr) ); 
		queue = queue->prox;
	    }
	    root = root->prox;
	}
	id_count++;
    }
    return head;
}


void sendMessages(List *list, char* lot, int lote_number){
    
    //while(root != NULL){
	printf("%s_%d:\n", lot, lote_number);
    //}
}

int main(int argc, char** argv) {
    
    int k, lot_number;
    char lot[11], str[MAX], msg[MAX];
    int id, ord, is_new, head_c = 0;
    Arr *root, *head, *queue;
    
    root = NULL;
    head = NULL;
    
    scanf("%d", &k);
    if( k < 1 || k > 1000 ){
        return (EXIT_FAILURE);
    }

    head = (Arr *) malloc(sizeof(Arr));
    
    scanf("%s", lot);
    while(lot != "-1"){
	
        scanf("%d ", &lot_number);
	
	fgets(str, sizeof(str), stdin);
	fflush(stdin);
        if(strcmp(str,"Fim\n") == 0) break;
        sscanf(str,"%d;%d;%[^\n]s", &id, &ord, msg);
		
        while(strcmp(lot, "-1\n") != 0){
	    while(strcmp(str,"Fim\n") != 0){
            
		is_new = 1;
		root = head;
		if(root->pair_id == id){
		    is_new = 0;
		}
		
		while(root->prox != NULL){
		    if(root->pair_id == id){
			is_new = 0;
			break;
		    }
		    root = root->prox;
		}
		
		if(is_new == 1){
		    root->prox = (Arr *) malloc( sizeof(Arr) );
		    root->list = (List *) malloc( sizeof(List) );
		}
		
		insertOnList(root, id, ord, msg);
		scanf(" ");
		fgets(str, sizeof(str), stdin);
		fflush(stdin);
		sscanf(str,"%d;%d;%[^\n]s",&id, &ord, msg);
	    }
	   queue = queueing(root);
	    
	    //sendMessages(root->list, lot, lot_number);
	    scanf("%s", lot);
	}     
    }
    return (EXIT_SUCCESS);
}

