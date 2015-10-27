/* 
 * File:   main.c
 * Author: Luiz Otavio
 *
 * Created on October 26, 2015, 5:40 PM
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN 0 
#define MAX 500

typedef struct message_st{
    char message[MAX];
    int pair_id;
    int order;
    struct message_st *prox;
} message;

int main(int argc, char** argv) {
    
    message *root, *end;
    
    root = (message *) malloc(sizeof(message));
    end = (message *) malloc(sizeof(message));
    

    return (EXIT_SUCCESS);
}

