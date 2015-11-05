/* 
 * File:   main.c
 * Author: Luiz Otavio
 *
 * Created on October 26, 2015, 5:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

typedef struct message_st {
    char message[MAX];
    int pair_id;
    int order;
    struct message_st *prox;
} Message;

typedef struct pair_st {
    int pair_id;
    int last_msg;
    Message *msg_head, *msg_last;
    struct pair_st *prox;
} Conv;

typedef struct cont_st {
    Conv *conv_head, *conv_last;
} Container;

Conv* createConvMid(Conv* conv, int pair_id){

    //criamos uma nova conversa e a inserimos
    //logo após à 'conv' recebida como parâmetro
    
    Conv * aux;
    aux = (Conv *) malloc(sizeof(Conv));
    aux->pair_id = pair_id;
    
    aux->prox = conv->prox;
    conv->prox = aux;
    
    return aux;
}

Conv* selectConv(Container* root, int pair_id){

    Conv *aux;
    int id;
    
    //vamos pegar um 'aux' com a primeira conversa após a cabeça
    aux = root->conv_head->prox;
    
    //verifica já existe a conversa entre os pares 'pair_id'.
    while(aux != NULL){
        
        if(aux->pair_id == pair_id){
            return aux;
        } 
        if(aux->prox != NULL && aux->prox->pair_id > pair_id){
            //ou seja, como temos um container de conversas ordenado crescente,
            //ao percorremos ele e chegamos a uma conversa com 'pair_id' maior,
            //o que queremos não existe e necessitamos inseri-lo no meio da lista. 
            //Dessa meneira facilitará a inserção.
            
            //o método abaixo cria e já retorna a 'conv' nova ordenada
            return createConvMid(aux, pair_id);        
        }
        aux = aux->prox;
    }
    
    //se o programa chegar aqui, é porque não existe e ela deve ser criada no final.
    //logo devemos criar uma nova no final e retorna-la.
    
    //utilizarei o próprio 'aux' que não será mais utilizado
    //alocamos memória para ele
    aux = (Conv *) malloc(sizeof(Conv));
    //falamos que ele é o último elemento da lista
    aux->pair_id = pair_id;
    root->conv_last->prox = aux;
    root->conv_last = aux;
    //e então o retornamos
    return aux;
}


void insOnConvMid(Message* msg, int ord, char* message, int pair_id){

    //criamos a nova célula Mensagem
    Message * aux;
    aux = (Message *) malloc(sizeof(Message));
    //e atribuímos os dados à ela
    aux->order = ord;
    strcpy(aux->message, message);
    aux->pair_id = pair_id;
    
    //fazemos então a troca de referências para
    // "inserirmos" a nova mesagem na lista
    aux->prox = msg->prox;
    msg->prox = aux;
}

void insOnConv(Conv* conv, int ord, char* msg){
    
    //Devemos aqui encontrar onde encaixar a mesagem
    //de forma que todas fiquem ordenadas pela ordem 'ord'
    
    Message* aux;
    
    if(conv->msg_head == NULL){
        //aloca posição para o header da mensagem caso 
        //ela não exista.
        conv->msg_head = (Message *) malloc(sizeof(Message));
        conv->msg_head->order = MAX;
        conv->msg_last = conv->msg_head;
    }
    
    //aqui começamos da cabeça da lista, pois,
    //sempre compararemos com o prox,
    //ficando mais fácil assim inserir o item já ordenado.
    aux = conv->msg_head;
    
    //então verificamos se a célula mensagem 
    //deve ser inserida no meio da lista.
    while(aux != NULL){
        if(aux->prox != NULL && aux->prox->order > ord){
            insOnConvMid(aux, ord, msg, conv->pair_id);
            //matamos a função aqui com um 'return'
            //pois já fora inserido a mensagem na lista
            return;
        }
        aux = aux->prox;
    }

    //caso não entre no 'if' acima, a mensagem tem maior ordem
    //logo deverá ser inserida no final da lista.
    
    //atribuindo os valores:
    aux = (Message *) malloc(sizeof(Message));
    strcpy(aux->message, msg);
    aux->order = ord;
    aux->pair_id = conv->pair_id;
    
    //"inserindo" no final da lista:
    conv->msg_last->prox = aux;
    conv->msg_last = aux;
}

void sendMessages(Container *root){

    // As prioridade ao enviar as mensagens são:
    //   1 -> Quantidade de mensagens enviadas pelo par.
    // caso empate:  
    //   2 -> ID do par
    
    Conv* aux;
    
    aux = root->conv_head->prox;
    
    while(aux != NULL){
        
        
    
    }
    
    
    
    
    
    
    

}



int main(int argc, char** argv) {

    int lot_number, k, pair_id, ord;
    char str[MAX], msg[MAX];
    Container *root;
    Conv *conv;

    root = (Container *) malloc(sizeof (Container));

    root->conv_head = (Conv *) malloc(sizeof (Conv));
    root->conv_last = root->conv_head;
    root->conv_last->pair_id = MAX;

    // --- blocos de leitura de stdin ---
    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d", &k);
    fflush(stdin);

    fgets(str, sizeof (str), stdin);
    sscanf(str, "%*[^0-9]%d", &lot_number);
    fflush(stdin);

    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d;%d;%[^\n]s", &pair_id, &ord, msg);
    fflush(stdin);
    //  --- ---- ---- --- ---- --- ----
    
    while (lot_number != -1) {
	while (strcmp(str, "Fim\n") != 0) {

            // >>>>>>>> Recebendo Cada Mensagem do Lote <<<<<<
            
	    // - Primeiro, selecionamos a conversa (Conv)
            conv = selectConv(root, pair_id);
            // - Agora inserimos a mesagem 'msg' na conversa
            insOnConv(conv, ord, msg);
            
            
	    fgets(str, sizeof (str), stdin);
	    sscanf(str, "%d;%d;%[^\n]s", &pair_id, &ord, msg);
	    fflush(stdin);
	}
        
        // aqui já temos o Container 'root' com todas
        // as Conversas ordenadas por 'pair_id' com
        // todas as mensagens, dentro de cada, ordenadas
        // por 'ord'.
        
        
        // >>>>>>>> Enviando as Mensagens do Lote <<<<<<
       // sendMessages(root);

        
        
        
	fgets(str, sizeof (str), stdin);
	sscanf(str, "%*[^0-9]%d", &lot_number);
	fflush(stdin);
        
        // essa condição abaixo está longe de 
        // ser a mais elegante. Porém tive MUITOS
        // problemas com regex/scanf do C
        // que resolvi deixar assim, pois, também não é o foco.
        if(str[0] == '-' && str[1] == '1'){
           break; 
        }
        //caso não passe na condição acima,
        //continua a leitura de um novo bloco de mensagens.
	fgets(str, sizeof (str), stdin);
	sscanf(str, "%d;%d;%[^\n]s", &pair_id, &ord, msg);
	fflush(stdin);
    }
    return (EXIT_SUCCESS);
}





































/*

 
10
Lote 1
3;2;Estou fazendo agora
0;1;Ol´a, tudo bem com vocˆe?
1;2;N˜ao
1;1;Vocˆe vem jantar hoje?
0;2;Tudo sim e vocˆe?
1;3;Vou ter que trabalhar at´e mais tarde
2;4;se vocˆe lembrar
3;1;Conseguiu fazer o TP?
3;3;Esta muito f´acil
Fim
Lote 2
2;2;Vou
2;3;leva na aula amanha
0;3;Tudo bem tbm
4;2;Parab´ens! Que dia vamos comemorar?
2;1;Vai precisar da grana?
4;1;Passei no vestibular!
3;4;Esta mesmo
Fim
-1
 
 
 */



/*void insertMessages(Pair *pair, int id, int order, char* msg) {

    Pair *aux;

    if (pair->msg_head == NULL || pair->msg_head->prox == NULL) {
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

    int a, has, b, high;

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
	    high = MIN;
	    
	    aux_msg = pair_root->msg_head->prox;
		while (aux_msg != NULL) {
		    if(aux_msg->order > high){
			high = aux_msg->order;
		    }
		    aux_msg = aux_msg->prox;
		}
	    
	    printf("Par_%d:[", a);
	    for (b = 0; b < 50; b++) {
		
		aux_msg = pair_root->msg_head;

		while (aux_msg != NULL) {
		    if (aux_msg->order == b) {
			if (aux_msg->order == high) {
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

    int a, has, b, c, lowest_msg, low_order;

    pair_root = root->pair_head;


    printf("Envios:\n");

    for (c = 0; c < 50; c++) {

	for (a = 0; a < 50; a++) {
	    has = 0;

	    pair_root = root->pair_head->prox;
	    lowest_msg = MAX;
	    while (pair_root->prox != NULL) {
		if (pair_root->last_msg < lowest_msg) {
		    lowest_msg = pair_root->last_msg;
		}
		pair_root = pair_root->prox;
	    }

	    pair_root = root->pair_head->prox;

	    while (pair_root != NULL) {
		if (pair_root->pair_id == a) {
		    has = 1;
		    break;
		}
		pair_root = pair_root->prox;
	    }
	    
	    if (has == 1) {
		for (b = 0; b < 50; b++) {
		    aux_msg = pair_root->msg_head->prox;
		    while (aux_msg != NULL) {
			if (aux_msg->order == b) {
			    if (pair_root->last_msg <= lowest_msg && pair_root->last_msg == aux_msg->order-1) {
				printf("%d;%d;%s\n", a, b, aux_msg->message);
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

    while (lot_number != -1) {
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
	sscanf(str, "%*[^0-9]%d", &lot_number);
	fflush(stdin);

	fgets(str, sizeof (str), stdin);
	sscanf(str, "%d;%d;%[^\n]s", &id, &ord, msg);
	fflush(stdin);
    }
    return (EXIT_SUCCESS);
}*/