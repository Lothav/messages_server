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
    int k;
    Message *msg_head, *msg_last;
    struct pair_st *prox;
} Conv;

typedef struct cont_st {
    Conv *conv_head, *conv_last;
} Container;

Conv* createConvMid(Conv* conv, int pair_id) {

    //criamos uma nova conversa e a inserimos
    //logo após à 'conv' recebida como parâmetro

    Conv * aux;
    aux = (Conv *) malloc(sizeof (Conv));
    aux->pair_id = pair_id;

    aux->prox = conv->prox;
    conv->prox = aux;

    return aux;
}

Conv* selectConv(Container* root, int pair_id) {

    Conv *aux;
    int id;

    //vamos pegar um 'aux' com a primeira conversa após a cabeça
    aux = root->conv_head;

    //verifica já existe a conversa entre os pares 'pair_id'.
    while (aux != NULL) {

	if (aux->pair_id == pair_id) {
	    return aux;
	}
	if (aux->prox != NULL && aux->prox->pair_id > pair_id) {
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
    aux = (Conv *) malloc(sizeof (Conv));
    //falamos que ele é o último elemento da lista
    aux->pair_id = pair_id;
    root->conv_last->prox = aux;
    root->conv_last = aux;
    aux->prox = NULL;
    aux->msg_head = NULL;
    aux->msg_last = aux->msg_head;
    aux->last_msg = 0;
    aux->k = 0;

    //e então o retornamos
    return aux;
}

void insOnConvMid(Message* msg, int ord, char* message, int pair_id) {

    //criamos a nova célula Mensagem
    Message * aux;
    aux = (Message *) malloc(sizeof (Message));
    //e atribuímos os dados à ela
    aux->order = ord;
    strcpy(aux->message, message);
    aux->pair_id = pair_id;

    //fazemos então a troca de referências para
    // "inserirmos" a nova mesagem na lista
    aux->prox = msg->prox;
    msg->prox = aux;
}

void insOnConv(Conv* conv, int ord, char* msg) {

    //Devemos aqui encontrar onde encaixar a mesagem
    //de forma que todas fiquem ordenadas pela ordem 'ord'

    Message* aux;

    if (conv->msg_head == NULL) {
	//aloca posição para o header da mensagem caso 
	//ela não exista.
	conv->msg_head = (Message *) malloc(sizeof (Message));
	conv->msg_head->order = MAX;
	conv->msg_last = conv->msg_head;
    }

    // zeramos o k da conversa pois ela trocou uma mensagem
    conv->k = 0;

    //aqui começamos da cabeça da lista, pois,
    //sempre compararemos com o prox,
    //ficando mais fácil assim inserir o item já ordenado.
    aux = conv->msg_head;

    //então verificamos se a célula mensagem 
    //deve ser inserida no meio da lista.
    while (aux != NULL) {
	if (aux->prox != NULL && aux->prox->order > ord) {
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
    aux = (Message *) malloc(sizeof (Message));
    strcpy(aux->message, msg);
    aux->order = ord;
    aux->pair_id = conv->pair_id;

    //"inserindo" no final da lista:
    conv->msg_last->prox = aux;
    conv->msg_last = aux;
    aux->prox = NULL;
}

int getMinMens(Container *root) {

    Conv * aux;
    int min_mens = MAX;

    aux = root->conv_head->prox;

    while (aux != NULL) {

	if (
		// SE
		// a conversa não está vazia
		aux->msg_head->prox != NULL &&
		// e a última mensagem enviada coincide com o menor valor de mensagem encontrado	
		aux->last_msg < min_mens &&
		// e a ordem da primeira mensagem da conversa é igual
		// ao contador de mens enviadas + 1.
		aux->msg_head->prox->order == aux->last_msg + 1) {
	    // então a menor mensagem é essa.
	    min_mens = aux->last_msg;
	}
	aux = aux->prox;
    }
    //retorna ela
    return min_mens;
}

void sendMessages(Container *root) {

    // As prioridade ao enviar as mensagens são:
    //   1 -> Quantidade de mensagens enviadas pelo par.
    // caso empate:  
    //   2 -> ID do par

    Conv* aux, *find_min_answ;
    Message* to_send;

    // min_answ representa a quantidade de envios
    // do par que trocou menos mensagens.
    int min_answ = 0;

    // para verificação se o 'min_answ' precisa ser calculado novamente
    int re_min_answ = 1;


    printf("Envios:\n");

    // percorrendo as conversas:
    aux = root->conv_head->prox;
    while (aux != NULL) {


	// aqui procuramos pelo menor valor de mensagens enviadas,
	// ou seja, esse valor será igual à quantidade de envios
	// da conversa com menos envios.
	if (re_min_answ == 1) {
	    min_answ = getMinMens(root);
	    // após encontramos o min_answ, setemos 0 na verificação,
	    // para que só seja feita novamente quando uma mensagem
	    // for enviada.
	    re_min_answ = 0;
	}
	to_send = aux->msg_head->prox;

	// se a ordem da mensagem for a menor quantidade + 1
	// e se a quantidade de mensagens enviadas pela conversa for a menor
	// ela é enviada.

	if (// Se
		// a conversa não está vazia e
		to_send != NULL &&
		// e a ordem da primeira mensagem da conversa é igual
		// ao contador de mens enviadas + 1 e
		to_send->order == aux->last_msg + 1 &&
		// a quantidade de mensagens enviadas pela conversa condiz com
		// o 'min_answ'
		min_answ == aux->last_msg) {

	    // imprime os dados da mensagem na tela
	    printf("%d;%d;%s\n", to_send->pair_id, to_send->order, to_send->message);
	    // muda a cabeça da lista para a mensagem após a que foi enviada
	    aux->msg_head->prox = to_send->prox;
	    if (to_send->prox == NULL) {
		aux->msg_last = aux->msg_head;
	    }
	    // já que a mensagem fora enviada, podemos/devemos liberar o espaço alocado
	    free(to_send);
	    // é adicionado +1 na contagem de mensagens enviadas pela Conv
	    aux->last_msg++;

	    // Parte importante:
	    // após enviar uma mensagem, todo o while deve recomeçar
	    // pois pode ter uma conversa pra trás que será a próx
	    // a enviar, logo :
	    aux = root->conv_head->prox;

	    // faço 'min_answ' = MAX para que ele encontre novamente o menor.
	    min_answ = MAX;
	    // ativo a verificação de 'min_answ'
	    re_min_answ = 1;
	}
	// caso o 're_min_answ' == 1, é porque eu estou reiniciando o loop
	// logo, essa linha deve ser desprezada.
	if (re_min_answ == 0) {
	    aux = aux->prox;
	}
    }

}

void printLists(Container* root) {


    // Aqui mostramos na tela as mensagens em blocos
    // como especificado no TP
    // separados por Conv e ordenadas por
    // sua ordem (ord).

    Conv* aux_conv;
    Message* aux_msg;

    aux_conv = root->conv_head->prox;

    printf("Listas:\n");

    while (aux_conv != NULL) {

	printf("Par_%d:[", aux_conv->pair_id);

	aux_msg = aux_conv->msg_head->prox;

	while (aux_msg != NULL) {

	    if (aux_msg->prox != NULL) {
		printf("(%d,%s),", aux_msg->order, aux_msg->message);
	    } else {
		printf("(%d,%s)", aux_msg->order, aux_msg->message);
	    }
	    aux_msg = aux_msg->prox;
	}
	printf("]\n");
	aux_conv = aux_conv->prox;
    }
}

void printCounts(Container* root) {

    // Imprime os contadores como 
    // especificado no TP

    Conv *aux;

    aux = root->conv_head->prox;

    printf("Contadores:\n");

    while (aux != NULL) {
	printf("Par_%d:%d\n", aux->pair_id, aux->last_msg);
	aux = aux->prox;
    }
}

void addKonConvs(Container* root) {

    // adiciona 1 à todos os k's

    Conv *k_count;
    k_count = root->conv_head->prox;
    while (k_count != NULL) {
	k_count->k++;
	k_count = k_count->prox;
    }
}

void desalocateConv(Container* root, int k) {

    Conv *aux, *ant;

    aux = root->conv_head->prox;
    ant = root->conv_head;

    while (aux != NULL) {
	// o k da conversa atingiu o k informado
	if (aux->k == k) {
	    ant->prox = aux->prox;
	    // após 'pularmos' o aux, damos um free nele:
	    free(aux);
	}
	// salva o aux como 'ant' para podermos 'pular'
	// o 'aux' quando encontrado o que tenha k igual.
	ant = aux;
	aux = aux->prox;
    }
}

int main(int argc, char** argv) {

    int lot_number, k, pair_id, ord;
    char str[MAX], msg[MAX];
    Container *root;
    Conv *conv;

    // Alocamos e atribuímos os valores para "root"
    // que será nosso 'container' geral.
    //
    // Chamei de 'container' o TAD mair que engloba todos os outros
    // Ele é reponsável por fornecer os ponteiros para às Conversas
    root = (Container *) malloc(sizeof (Container));
    root->conv_head = (Conv *) malloc(sizeof (Conv));
    root->conv_last = root->conv_head;
    root->conv_last->pair_id = MAX;
    root->conv_last->prox = NULL;

    // ---- blocos de leitura de stdin -----
    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d", &k);
    fflush(stdin);

    if (k < 1 || k > 1000) {
	return (EXIT_FAILURE);
    }

    fgets(str, sizeof (str), stdin);
    sscanf(str, "%*[^0-9]%d", &lot_number);
    fflush(stdin);

    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d;%d;%[^\n]s", &pair_id, &ord, msg);
    fflush(stdin);
    //  --- ---- ---- --- ---- --- ----

    while (lot_number != -1) {

	// Primeira ação do loop:
	//  - somar k em 1 em todas às conversas.
	// Aquelas que receberem uma mensagem terão
	// seu k zerado.
	addKonConvs(root);

	while (strcmp(str, "Fim\n") != 0) {

	    // >>>>>>>> Recebendo Cada Mensagem do Lote <<<<<<

	    // - Primeiro, selecionamos a conversa (Conv)
	    conv = selectConv(root, pair_id);
	    // - Agora inserimos a mesagem 'msg' na conversa 'conv'
	    insOnConv(conv, ord, msg);


	    fgets(str, sizeof (str), stdin);
	    sscanf(str, "%d;%d;%[^\n]s", &pair_id, &ord, msg);
	    fflush(stdin);
	}

	// aqui já temos o Container 'root' com todas
	// as Conversas ordenadas por 'pair_id' com
	// todas as mensagens, dentro de cada, ordenadas
	// por sua ordem 'ord'.


	// Desalocando Conversa caso seu k chegue no k informado
	desalocateConv(root, k);


	// >>>>>>>> Enviando as Mensagens do Lote <<<<<<

	//  - mostra as listas na tela como especificado.
	printLists(root);
	//  - envia as mensagens seguindo às ordens de prioridade.
	sendMessages(root);
	//  - mostra a quantidade de mensage de cada par
	printCounts(root);



	// -------------------------------------------
	// Fim do bloco de stdout
	// Agora verifiquemos se mais lotes serão inseridos 
	// ou se o programa acaba.

	fgets(str, sizeof (str), stdin);
	sscanf(str, "%*[^0-9]%d", &lot_number);
	fflush(stdin);

	// essa condição abaixo está longe de 
	// ser a mais elegante. Porém tive MUITOS
	// problemas com regex/scanf do C
	// que resolvi deixar assim, pois, também 
	// acredito não ser o foco.
	if (str[0] == '-' && str[1] == '1') {
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