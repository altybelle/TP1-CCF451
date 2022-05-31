typedef struct EstadoPronto {
    int valor; /* TODO: Implementar o valor a ser utilizado */
    struct EstadoPronto *proximo;
} EstadoPronto;

void insere_ep(EstadoPronto**, int); /* Insere na fila */
void insere_prioridade_ep(EstadoPronto**, int); /* Insere com prioridade na fila */
EstadoPronto *remover_ep(EstadoPronto**); /* Remove item da fila */
void imprimir_ep(EstadoPronto*); /* Imprime a fila */ 