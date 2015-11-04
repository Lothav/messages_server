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

typedef struct message_st {
    char message[MAX];
    int pair_id;
    int order;
    struct message_st *prox;
    struct message_st *ant;
} Message;

typedef struct pair_st {
    int pair_id;
    int last_msg;
    Message *msg_head, *msg_last;
    struct pair_st *prox;
} Pair;

typedef struct arr_st {
    Pair *pair_head, *pair_last;
} PairsArr;

void insertMessages(Pair *pair, int id, int order, char* msg) {

    Pair *aux;

    if (pair->msg_head == NULL) {
	pair->msg_head = (Message *) malloc(sizeof (Message));
	pair->msg_last = pair->msg_head;
	pair->msg_head->pair_id = MAX;
	pair->msg_head->order = MAX;
    }

    pair->msg_last->prox = (Message *) malloc(sizeof (Message));
    pair->msg_last->prox->ant = pair->msg_last;
    pair->msg_last->prox->ant->prox = pair->msg_last->prox;

    pair->msg_last = pair->msg_last->prox;
    pair->pair_id = id;
    strcpy(pair->msg_last->message, msg);
    pair->msg_last->pair_id = id;
    pair->msg_last->order = order;

}

void printLists(PairsArr *root) {

    Pair *pair_root;
    Message *aux_msg;

    int a, has, b;

    pair_root = root->pair_head;

    printf("Listas:\n");

    for (a = 0; a < 50; a++) {
	has = 0;
	pair_root = root->pair_head;

	while (pair_root != NULL) {
	    if (pair_root->pair_id == a) {
		has = 1;
		break;
	    }
	    pair_root = pair_root->prox;
	}

	if (has == 1) {
	    printf("Par_%d:[", a);
	    for (b = 0; b < 50; b++) {
		aux_msg = pair_root->msg_head;
		while (aux_msg != NULL) {
		    if (aux_msg->order == b) {
			if (aux_msg->prox == NULL) {
			    printf("(%d,%s)", b, aux_msg->message);
			} else {
			    printf("(%d,%s), ", b, aux_msg->message);
			}
		    }
		    aux_msg = aux_msg->prox;
		}
	    }
	    printf("]\n");
	}
    }
}

void printSends(PairsArr *root) {

    Pair *pair_root;
    Message *aux_msg, *swit, *loop;

    int a, has, b, c, lowest_msg = MAX, low_order;

    pair_root = root->pair_head;


    printf("Envios:\n");

    for (c = 0; c < 50; c++) {

	for (a = 0; a < 50; a++) {
	    has = 0;

	    pair_root = root->pair_head;

	    while (pair_root->prox != NULL) {
		low_order = MAX;
		loop = pair_root->prox->msg_head;
		while (loop->prox != NULL) {
		    if (loop->order < low_order) {
			low_order = loop->order;
		    }
		    loop = loop->prox;
		}

		if (pair_root->last_msg <= lowest_msg && low_order == pair_root->last_msg + 1) {
		    lowest_msg = pair_root->last_msg;
		}
		pair_root = pair_root->prox;
	    }

	    pair_root = root->pair_head;

	    while (pair_root->prox != NULL) {
		if (pair_root->pair_id == a) {
		    has = 1;
		    break;
		}
		pair_root = pair_root->prox;
	    }

	    if (has == 1) {
		for (b = 0; b < 50; b++) {
		    aux_msg = pair_root->msg_head;
		    while (aux_msg != NULL) {
			if (aux_msg->order == b) {
			    if (pair_root->last_msg <= lowest_msg) {
				printf("%d %d %s\n", a, b, aux_msg->message);
				aux_msg->ant->prox = aux_msg->prox;
				if (aux_msg->prox != NULL) {
				    aux_msg->prox->ant = aux_msg->ant;
				}
				pair_root->last_msg++;

			    }
			}
			aux_msg = aux_msg->prox;
		    }
		}
	    }
	}
	lowest_msg++;
    }
}

void printCounts(PairsArr *root) {

    Pair *paux;
    int a;

    printf("Contadores:\n");
    for (a = 0; a < 50; a++) {
	paux = root->pair_head->prox;
	while (paux != NULL) {
	    if (paux->pair_id == a) {
		printf("Par_%d:%d\n", a, paux->last_msg);
	    }
	    paux = paux->prox;
	}
    }
}

int main(int argc, char** argv) {

    int lot_number;
    char lot[11], str[MAX], msg[MAX];
    int id, ord, is_new, head_c = 0, k;
    PairsArr *root, *head, *queue;
    Pair *auxP;

    root = (PairsArr *) malloc(sizeof (PairsArr));

    root->pair_head = (Pair *) malloc(sizeof (Pair));
    root->pair_last = root->pair_head;
    root->pair_head->pair_id = MAX;

    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d", &k);
    fflush(stdin);

    fgets(str, sizeof (str), stdin);
    sscanf(str, "%*[^0-9]%d", &lot_number);
    fflush(stdin);

    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d;%d;%[^\n]s", &id, &ord, msg);
    fflush(stdin);

    while (k != -1) {
	while (strcmp(str, "Fim\n") != 0) {

	    auxP = root->pair_head;
	    is_new = 1;
	    while (auxP->prox != NULL) {
		if (auxP->pair_id == id) {
		    is_new = 0;
		    break;
		}
		auxP = auxP->prox;
	    }

	    if (auxP->pair_id == id && auxP->prox == NULL) {
		is_new = 0;
	    }

	    if (is_new == 1) {
		auxP->prox = (Pair *) malloc(sizeof (Pair));
		auxP = auxP->prox;
	    }

	    insertMessages(auxP, id, ord, msg);

	    fgets(str, sizeof (str), stdin);
	    sscanf(str, "%d;%d;%[^\n]s", &id, &ord, msg);
	    fflush(stdin);
	}
	printLists(root);
	printSends(root);
	printCounts(root);

	fgets(str, sizeof (str), stdin);
	sscanf(str, "%d", &k);
	fflush(stdin);

	fgets(str, sizeof (str), stdin);
	sscanf(str, "%*[^0-9]%d", &lot_number);
	fflush(stdin);

	fgets(str, sizeof (str), stdin);
	sscanf(str, "%d;%d;%[^\n]s", &id, &ord, msg);
	fflush(stdin);
    }
    return (EXIT_SUCCESS);
}