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

int main(int argc, char** argv) {
    
    int k, lot_number;
    char lot[11], msg[MAX];
    char id[11],aux2[11];
    List *root[50];
       
    scanf("%d", &k);
    if( k < 1 || k > 1000 ){
        printf("\n k is out of bounds");
        return (EXIT_FAILURE);
    }
  
    scanf("%s", lot);
    while(lot != "-1"){
        scanf("%d", &lot_number);
        scanf(" %[^;];%[^;];%[^\n]", id, aux2, msg);
        
        while(msg != "Fim"){
            
            if(root[atoi(id)] == NULL){
          
                root[atoi(id)] = (List *) malloc(sizeof(List));                
                root[atoi(id)]->prox = NULL;
            }
 
           insertOnList(root[atoi(id)], id, aux2, msg);
           scanf(" %[^;];%[^;];%[^\n]", id, aux2, msg);
        }
        scanf("%s", lot);
    }
    
    
    return (EXIT_SUCCESS);
}

