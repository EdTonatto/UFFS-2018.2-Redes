#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define QUEUE_SIZE 93              // Tamanho das filas dos roteadores
#define MESSAGE_SIZE 100           // Mensagens são limitadas a 100 caracteres
#define MAX_ROT 50
#define INF 500

#define MESSAGE 0
#define DIST_VECTOR 1
#define ACK 2

typedef struct{                     // Estrutura dos roteadores
  int id, port;                     // ID e porta do roteador
  char ip[30];
}Router;

typedef struct{                     // Estrutura dos pacotes
  int msg_id;
  int source, destination, type;    // Header (Origem, Destino e tipo da mensagem)
  char content[MESSAGE_SIZE];       // Mensagem
  Dist_Vector dv;
}Package;

typedef struct{
  int source[MAX_ROT];
  int cost[MAX_ROT];
}Dist_Vector;

typedef struct{                     // Estrutura das tabelas de roteamentos
  int cost;
  int next;
}Table;

typedef struct{
  int port;
  char ip[30];
}Neighbors;
