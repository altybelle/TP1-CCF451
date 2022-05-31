typedef struct EstadoBloqueado {
    int valor; /* TODO: Implementar o valor a ser utilizado */
    struct EstadoBloqueado *proximo;
} EstadoBloqueado;

void insere_ep(EstadoBloqueado**, int); /* Insere na fila */
EstadoBloqueado *remover_ep(EstadoBloqueado**); /* Remove item da fila */
void imprimir_eb(EstadoBloqueado*); /* Imprime a fila */ 