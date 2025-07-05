#pragma once 

#include <vector>
#include "corretor.h"
#include "imovel.h"

/**
 * Função principal que orquestra todo o processo de agendamento.
 * * Esta função primeiro distribui os imóveis entre os corretores avaliadores
 * e depois calcula a rota otimizada (vizinho mais próximo) para cada um,
 * imprimindo a agenda formatada diretamente na saída padrão.
 */
void gerarEImprimirAgenda(std::vector<Corretor>& corretores, std::vector<Imovel>& imoveis);