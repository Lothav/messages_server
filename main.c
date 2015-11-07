/* 
 * File:   main.c
 * Author: Luiz Otavio
 *
 * Created on October 26, 2015, 5:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


#define MAX 500


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

	//  - número do Lote
	printf("Lote_%d:\n", lot_number);
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