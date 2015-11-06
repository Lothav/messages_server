/* 
 * File:   header.h
 * Author: root
 *
 * Created on 6 de Novembro de 2015, 01:17
 */

#ifndef HEADER_H
#define	HEADER_H

#define MAX 500




    //  --------- TADS ----------- 

    // Container:
    // estrutura responsável por fornecer a referência
    // para as Conversas

    typedef struct cont_st {
	Conv *conv_head, *conv_last;
    } Container;

    // Conv:
    // contém dados agrupados de cada conversa
    // e fornece os ponteiros para as mensagens

    typedef struct conv_st {
	int pair_id;
	int last_msg;
	int k;
	Message *msg_head, *msg_last;
	struct conv_st *prox;
    } Conv;


    // estrutura responsável por armazenar as mensagens

    typedef struct message_st {
	char message[MAX];
	int pair_id;
	int order;
	struct message_st *prox;
    } Message;

    //  ---------  ----------- 

    
    // --------  FUNÇÕES -----------
    
    // Cria uma conversa no meio da lista de Conversas (container)
    Conv* createConvMid(Conv* conv, int pair_id);

    // Seleciona e retorna a conversa selecionada a partir
    // do 'pair_id' da mensagem.
    Conv* selectConv(Container* root, int pair_id);

    // Insere uma Mensage no meio da lista de conversas.
    void insOnConvMid(Message* msg, int ord, char* message, int pair_id);

    // Após selecionada a conversa, insere a mensagem nela.
    void insOnConv(Conv* conv, int ord, char* msg);

    // Pega a quantidade de mensagens enviadas da conversa que
    // menos enviou mensagens (menor valor de envio de mensagens).
    int getMinMens(Container *root);
    
    // Envia as mensagens -> "Envios:"
    void sendMessages(Container *root);
    
    // Mostra na tela as "Listas:"
    void printLists(Container* root);
    
    // Mostra na tela os "Contadores:"
    void printCounts(Container* root);
    
    // Adiciona +1 ao k de todas as conversas.
    void addKonConvs(Container* root);

    // Desaloca conversa a partir do k.
    void desalocateConv(Container* root, int k);  


#endif	/* HEADER_H */

