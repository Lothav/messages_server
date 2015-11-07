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

// estrutura responsável por armazenar as mensagens

typedef struct message_st {
    char message[MAX];
    int pair_id;
    int order;
    struct message_st *prox;
} Message;

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

// Container:
// estrutura responsável por fornecer a referência
// para as Conversas

typedef struct cont_st {
    Conv *conv_head, *conv_last;
} Container;

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


/*
 
20
Lote 1
11;2;It depends how you define life
5;1;Who are you?
4;1;What is your favorite book?
7;12;How do you work?
Fim
Lote 2
12;2;Go ahead and ask.
0;3;I'm also good.
10;1;What does YOLO mean?
Fim
Lote 3
1;1;Hello
12;1;Can I ask you a question?
1;3;How are you doing?
Fim
Lote 4
9;1;Are you a programmer?
8;7;Beautiful is better than ugly.
Fim
Lote 5
2;1;How are you doing?
8;17;Unless explicitly silenced.
Fim
Lote 6
8;10;Complex is better than complicated.
0;5;Yes it is.
8;20;Although that way may not be obvious at first unless you're Dutch.
2;2;I am doing well, how about you?
5;10;I wish I was The Mad Hatter.
Fim
Lote 7
8;19;There should be one-- and preferably only one --obvious way to do it.
1;2;Hi
Fim
Lote 8
1;4;I am doing well.
5;6;It's not your powers of observation I doubt, but merely the paradoxical nature of asking a masked man who is. But tell me, do you like music?
Fim
Lote 9
8;12;Sparse is better than dense.
7;3;What else is delicious?
5;2;Who? Who is but a form following the function of what
8;11;Flat is better than nested.
Fim
Lote 10
9;2;I am a programmer
8;23;If the implementation is hard to explain, it's a bad idea.
Fim
Lote 11
7;10;What is it like?
0;4;That's good to hear.
4;3;So what's your favorite color?
5;3;What are you then?
8;18;In the face of ambiguity, refuse the temptation to guess.
Fim
Lote 12
8;6;Do you know all of it?
7;5;Or something
8;13;Readability counts.
Fim
Lote 13
7;2;No it is not. The cake is delicious.
7;8;Are you a robot?
3;1;Have you heard the news?
1;10;Could I borrow a cup of sugar?
7;14;Complex is better than complicated.
Fim
Lote 14
8;14;Special cases aren't special enough to break the rules.
11;4;Is that a definition or an oppinion?
Fim
Lote 15
5;11;You're entirely bonkers. But I'll tell you a secret. All the best people are.
6;2;What are you working on?
Fim
Lote 16
9;5;I use Python quite a bit myself.
7;11;What is it that you want to know?
Fim
Lote 17
1;9;What is your question?
1;7;Can I help you with anything?
7;7;What do you want to know?
7;4;Nothing
8;1;Complex is better than complicated.
Fim
Lote 18
1;5;That is good to hear
11;3;Life is the condition that distinguishes organisms from inorganic matter, including the capacity for growth, reproduction, functional activity, and continual change preceding death.
2;4;That's good.
7;1;The cake is a lie.
6;1;I am working on a project
Fim
Lote 19
0;2;I am doing well, how about you?
8;22;Although never is often better than right now.
10;2;It means you only live once. Where did you hear that?
Fim
Lote 20
8;3;In the face of ambiguity, refuse the temptation to guess.
2;3;I am also good.
Fim
Lote 21
10;3;I heard somebody say it.
8;4;It seems your familiar with the Zen of Python
1;8;Yes, I have a question.
Fim
Lote 22
0;1;Good morning, how are you?
8;24;If the implementation is easy to explain, it may be a good idea.
7;9;Yes I am.
11;1;Did I ever live?
4;4;Blue
Fim
Lote 23
8;9;Simple is better than complex.
9;8;It has many inconsistencies.
8;15;Although practicality beats purity.
8;21;Now is better than never.
Fim
Lote 24
5;8;What kind of movies do you like?
8;8;Explicit is better than implicit.
5;9;Alice in Wonderland
8;25;Namespaces are one honking great idea. Let's do more of those!
Fim
Lote 25
8;16;Errors should never pass silently.
1;13;No problem
8;2;Simple is better than complex.
1;6;Yes it it.
4;2;I can't read.
Fim
Lote 26
8;5;I am.
5;5;I can see that.
7;13;Its complicated.
Fim
Lote 27
3;2;What good news?
5;4;A man in a mask.
1;11;I'm sorry, but I don't have any.
8;26;I agree.
9;3;What languages do you like to use?
Fim
Lote 28
5;7;I like seeing movies.
6;3;I am baking a cake.
9;4;I use Python, Java and c++ quite often.
Fim
Lote 29
9;7;What annoys you?
9;6;I'm not incredibly fond of Java.
Fim
Lote 30
1;12;Thank you anyway
7;6;Tell me about your self.
Fim
-1


 
 */