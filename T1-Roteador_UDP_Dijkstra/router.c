#include "router.h"

#define DEBUG

Router router[N_ROT];
Table r_table[N_ROT];

void create_router(int r_ID){
  FILE *file = fopen("roteador.config", "r");

  if (file){
    for (int i = 0; fscanf(file, "%d %d %s", &router[i].id, &router[i].port, router[i].ip) != EOF; i++);

    fclose(file);

    #ifdef DEBUG
    for(int i = 0; i < N_ROT; i++)
      printf("%d %d %s\n", router[i].id, router[i].port, router[i].ip);
    #endif
  }
}

void create_links(int tab[N_ROT][N_ROT]){
  int x, y, peso;
  FILE *file = fopen("enlaces.config", "r");

  if (file){
    for (int i = 0; fscanf(file, "%d %d %d", &x, &y, &peso) != EOF; i++){
      tab[x][y] = peso;
      tab[y][x] = peso;
    }

    fclose(file);

    #ifdef DEBUG
    for(int i = 0; i < N_ROT; i++){
      for (int j = 0; j < N_ROT; j++)
        printf("%2d ", tab[i][j]);
      printf("\n");
    }
    #endif
  }
}

void dijkstra(int tab_rot[N_ROT][N_ROT], int start){
  int open[N_ROT], dist[N_ROT], prev[N_ROT];    // Vércices ainda não visitados, distâncias e anteriores
  int aux_s = start, nrot = N_ROT;

  memset(dist, 1123456, sizeof(int) * nrot);
  memset(prev, -1, sizeof(int) * nrot);
  memset(open, 1123456, sizeof(int) * nrot);
}

int main(){
  int tab_rot[N_ROT][N_ROT];

  memset(tab_rot, -1, sizeof(int) * N_ROT * N_ROT);

  create_router(0);
  printf("\n");
  create_links(tab_rot);

  int aux = 0;
  while(aux < N_ROT){
    dijkstra(tab_rot, i);
    i++;
  }

  return 0;
}
