#ifndef EXECUTOR_INSTRUCOES_H_
#define EXECUTOR_INSTRUCOES_H_

#include "../TabelaPCB/TabelaPCB.h"
#include "../GerenciadorProcessos/GerenciadorProcessos.h"

void executar_instrucao(Tempo*, CPU*, EstadoEmExecucao*, TabelaPCB*, EstadoPronto*, EstadoBloqueado*, Processo*);

#endif // EXECUTOR_INSTRUCOES_H_