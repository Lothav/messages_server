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

void insertOnList(List *root, Message *message){

    List *new;
    
    new = (List *) malloc(sizeof(List));
    new->message.order = message->order;
    new->message.pair_id = message->pair_id;
    new->prox = NULL;
    
    while(root->prox != NULL){    
        root = root->prox;
    }
    
    root->prox = new;
}

int main(int argc, char** argv) {
    
    List *root;
    Message *message;
    int k, lot_number;
    char lot[11], msg[MAX];
    char aux[11],aux2[11];
    
    scanf("%d", &k);
    if( k < 1 || k > 1000 ){
        printf("\n k is out of bounds");
        return (EXIT_FAILURE);
    }
    
    root = (List *) malloc(sizeof(List));    
  
    scanf("%s", lot);
    while(lot != "-1"){
        scanf("%d", &lot_number);
        scanf(" %[^;];%[^;];%[^\n]", aux, aux2, msg);
        
        while(msg != "Fim"){
            
           root->message.pair_id = atoi(aux);
           root->message.order = atoi(aux2);
           strcpy(root->message.message, msg);
           scanf(" %[^;];%[^;];%[^\n]", aux, aux2, msg);
        }  
    }
    
    
    return (EXIT_SUCCESS);
}

