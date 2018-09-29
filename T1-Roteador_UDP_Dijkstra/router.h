#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define QUEUE_SIZE 100     // Tamanho das filas dos roteadores
#define MESSAGE_SIZE 100  // Mensagens são limitadas a 100 caracteres
#define N_ROT 6           // Número de roteadores

typedef struct{                     // Estrutura dos pacotes
  int source, destination, id;    // Header
  char content[MESSAGE_SIZE];       // Mensagem
}Package;

typedef struct{                                             // Estrutura dos roteadores
  int id, port;                                             // ID e porta do roteador
  Package message_in[QUEUE_SIZE], message_out[QUEUE_SIZE];  // Filas do roteador
  char ip[30];
}Router;

typedef struct{                     // Estrutura das tabelas de roteamentos
  int cost[N_ROT];
  int path[N_ROT];
}Table;

void die(char *s);
void *receive(int id);
void create_message(int id);
void send_message(int this_id, int next_id);
void create_router(int r_ID);
void create_links(int tab[N_ROT][N_ROT]);
int  verify(int *v, int value);
void removev(int *v, int value);
int  findsminor(int *v, int *open);
void dijkstra(int tab_rot[N_ROT][N_ROT], int start);
void backtracking(int start, int prev[N_ROT]);
void pathcost(int start, int tab_rot[N_ROT][N_ROT]);
int  toint(char *str);
