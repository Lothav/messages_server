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
    struct list_st *prox;
    Message message;
}List;

void insertOnList(List *root, char* pair_id, char* order, char* msg){

    List *new;
    
    new = (List *) malloc(sizeof(List));
    new->message.order = atoi(order);
    new->message.pair_id = atoi(pair_id);
    strcpy(new->message.message, msg);
    new->prox = NULL;
    
    while(root->prox != NULL){
        root = root->prox;
    }
    root->prox = new;
}

void sendMessages(List *root[]){
    
   // while(root[] != NULL){
	printf("Par_%d:", root[0]->message.order);
//    }
}

int main(int argc, char** argv) {
    
    int k, lot_number;
    char lot[11], str[MAX], msg[MAX];
    char id[11],ord[11];
    List *root[50]={NULL};
       
    scanf("%d", &k);
    if( k < 1 || k > 1000 ){
        return (EXIT_FAILURE);
    }
  
    scanf("%s", lot);
    while(lot != "-1"){
        scanf("%d", &lot_number);
	
	fflush(stdin);
	fgets(msg,510,stdin);
	fflush(stdin);
        if(strcmp(msg,"Fim\n")==0) break;
        sscanf(msg,"%d;%d;%[^\n]s",&id, &ord, msg);
	
        //scanf(" %[^;];%[^;];%[^\n]", id, aux2, msg);
	
	
        while(strcmp(lot, "-1\n") != 0){
	    while(strcmp(str,"Fim\n") != 0){
            
		if(root[atoi(id)] == NULL){
          
		    root[atoi(id)] = (List *) malloc(sizeof(List));                
		    root[atoi(id)]->prox = NULL;
		}
		
		insertOnList(root[atoi(id)], id, ord, msg);
		fflush(stdin);
		fgets(str,510,stdin);
		fflush(stdin);
		sscanf(str,"%d;%d;%[^\n]s",&id, &ord, msg);
	    }
	    sendMessages(root);
	    scanf("%s", lot);
	}
        
    }
    return (EXIT_SUCCESS);
}

