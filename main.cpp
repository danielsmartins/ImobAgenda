#include <iostream>
#include <vector>
#include <string>

#include "corretor.h"
#include "cliente.h"
#include "imovel.h"
#include "agenda.h" 

// Função auxiliar para converter a string de tipo para o enum correspondente.
// Isso ajuda a manter o loop de leitura mais limpo.
TipoImovel stringParaTipoImovel(const std::string& tipoStr) {
    if (tipoStr == "Casa") return TipoImovel::Casa;
    if (tipoStr == "Apartamento") return TipoImovel::Apartamento;
    // Se não for nenhum dos dois, assume-se que é Terreno.
    return TipoImovel::Terreno;
}

int main() {
    // Otimiza a entrada e saída, desvinculando os fluxos C++ do C.
    // Essencial para processar arquivos grandes mais rapidamente.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // --- Entrada dos corretores ---
    int numCorretores;
    std::cin >> numCorretores;

    std::vector<Corretor> corretores;
    // Reserva espaço no vetor para evitar realocações, melhorando a performance.
    corretores.reserve(numCorretores); 

    for (int i = 0; i < numCorretores; i++) {
        std::string telefone;
        int avaliador_int;
        double lat, lon;
        std::string nome;

        std::cin >> telefone >> avaliador_int >> lat >> lon;
        std::getline(std::cin >> std::ws, nome); // lê o resto da linha e ignora espaços em branco

        // Constrói o objeto Corretor diretamente no vetor.
        corretores.emplace_back(telefone, avaliador_int == 1, lat, lon, nome);
    }

    // --- Entrada dos clientes ---
    int numClientes;
    std::cin >> numClientes;

    std::vector<Cliente> clientes;
    clientes.reserve(numClientes);

    for (int i = 0; i < numClientes; i++) {
        std::string telefone, nome;

        std::cin >> telefone;
        std::getline(std::cin >> std::ws, nome);

        // Constrói o objeto Cliente diretamente no vetor.
        clientes.emplace_back(telefone, nome);
    }

    // --- Entrada dos imóveis ---
    int numImoveis;
    std::cin >> numImoveis;

    std::vector<Imovel> imoveis;
    imoveis.reserve(numImoveis);

    for (int i = 0; i < numImoveis; ++i) {
        std::string tipoStr;
        int propId;
        double lat, lon, preco;
        std::string endereco;

        std::cin >> tipoStr >> propId >> lat >> lon >> preco;
        std::getline(std::cin >> std::ws, endereco);

        // Converte a string para o enum e constrói o objeto Imovel diretamente no vetor.
        imoveis.emplace_back(stringParaTipoImovel(tipoStr), propId, lat, lon, endereco, preco);
    }

    // --- Geração da Agenda ---
    // Chama a função principal que executa todo o algoritmo e imprime o resultado.
    gerarEImprimirAgenda(corretores, imoveis);

    return 0; // Finaliza o programa com sucesso.
}
