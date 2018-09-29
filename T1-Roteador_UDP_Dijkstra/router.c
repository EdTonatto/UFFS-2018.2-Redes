#include "router.h"

Router router[N_ROT];
Table r_table[N_ROT];
int count_table = 0;

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

int verify(int *v, int value){
  for(int i = 0; i < N_ROT; i++)
    if(v[i] == value)
      return 1;
  return 0;
}

void removev(int *v, int value){
  for(int i = 0; i < N_ROT; i++)
    if(v[i] == value)
      v[i] = -1;
}

int findsminor(int *v, int *open){
  int aux = 0, minor = 1123456;

  for(int i = 0; i < N_ROT; i++)
    if(v[i] != 0 && v[i] < minor && verify(open, i)){
      minor = v[i];
      aux = i;
    }

  return aux;
}

void dijkstra(int tab_rot[N_ROT][N_ROT], int start){
  int open[N_ROT], dist[N_ROT], prev[N_ROT];    // Vércices ainda não visitados, distâncias e anteriores
  int aux_s = start, nrot = N_ROT;

  for(int i = 0; i < nrot; i++){
    open[i] = i;
    prev[i] = i;
    dist[i] = 112345;
  }

  dist[start] = 0;

  while(nrot >= 0){
    for(int i = 0; i < N_ROT; i++){
      if (tab_rot[aux_s][i] > 0 && verify(open, i) && (dist[i] > (tab_rot[aux_s][i] + dist[aux_s]))){
        dist[i] = tab_rot[aux_s][i] + dist[aux_s];
        prev[i] = aux_s;
      }
    }
    removev(open, aux_s);
    nrot--;
    aux_s = findsminor(dist, open);
  }
  backtracking(start, prev);
}

void backtracking(int start, int prev[N_ROT]){
  int a, x = 0, aux = 0, destination =  N_ROT - 1, path[N_ROT];

  if(destination == start)
    destination = 0;

  while(aux < N_ROT){
    a = aux;
    while(destination != start){
      destination = a;
      path[x] = destination;
      if(prev[destination] == start){
        r_table[start].path[aux] = path[x];
        break;
      }
      x++;
      a = prev[destination];
    }
    if(destination == start)
      r_table[start].path[destination] = start;

    count_table++;
    x = 0;
    aux++;
    destination = aux;
  }
}

void pathcost(int start, int tab_rot[N_ROT][N_ROT]){
  for(int i = 0; i < N_ROT; i++)
    r_table[start].cost[i] = tab_rot[start][i];
}

int main(){
  int tab_rot[N_ROT][N_ROT];

  memset(tab_rot, -1, sizeof(int) * N_ROT * N_ROT);

  create_router(0);
  printf("\n");
  create_links(tab_rot);

  int aux = 0;
  while(aux < N_ROT){
    dijkstra(tab_rot, aux);
    aux++;
  }

  for(int i = 0; i < N_ROT; i++){
    pathcost(i, tab_rot);
  }

  printf("Mostrando qual é o proximo roteador que deve se ir para chegar ao destino desejado:\n");
  for(int i = 0; i < N_ROT; i++){
    for(int j = 0; j < N_ROT; j++)
      printf("r_table[start].path[ROT] | r_table[%d].path[%d] = %d | Custo = %d\n", i, j, r_table[i].path[j], r_table[i].cost[j]);
    printf("\n");
  }



  return 0;
}
