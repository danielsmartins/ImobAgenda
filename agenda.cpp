#include "agenda.h"

#include <iostream>
#include <vector>
#include <string>


#define _USE_MATH_DEFINES 
#include <cmath>      

#include <algorithm>
#include <iomanip>
#include <limits>

// --- Constantes Globais do Algoritmo ---
constexpr double EARTH_R = 6371.0;
const int DURACAO_AVALIACAO_MIN = 60;
const int TEMPO_DESLOCAMENTO_MIN_POR_KM = 2;

// --- Funções Auxiliares ---


// Função para calcular a distância entre dois pontos
double haversine(double lat1, double lon1, double lat2, double lon2) {
    auto deg2rad = [](double d) { return d * M_PI / 180.0; };
    double dlat = deg2rad(lat2 - lat1);
    double dlon = deg2rad(lon2 - lon1);
    double a = std::pow(std::sin(dlat / 2), 2) +
               std::cos(deg2rad(lat1)) * std::cos(deg2rad(lat2)) *
               std::pow(std::sin(dlon / 2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_R * c;
}

void distribuirImoveis(std::vector<Corretor>& corretores, std::vector<Imovel>& imoveis) {
    std::vector<Corretor*> avaliadores;
    // Filtra os corretores que são avaliadores
    for (Corretor& corretor : corretores) {
        if (corretor.isAvaliador()) {
            avaliadores.push_back(&corretor);
        }
    }

    if (avaliadores.empty()) {
        return;
    }

    // ordena em ordem crescente de ID os imoveis
    std::sort(imoveis.begin(), imoveis.end(), [](const Imovel& a, const Imovel& b) {
        return a.getId() < b.getId();
    });

    size_t avaliador_idx = 0;
    for (Imovel& imovel : imoveis) {
        avaliadores[avaliador_idx]->addImovelParaAvaliar(&imovel); // adiciona o ponteiro do imóvel ao corretor avaliador
        avaliador_idx = (avaliador_idx + 1) % avaliadores.size(); 
    }
}

// --- Função Principal de Agendamento ---

void gerarEImprimirAgenda(std::vector<Corretor>& corretores, std::vector<Imovel>& imoveis) {
    distribuirImoveis(corretores, imoveis); // distribui os imoveis entre os corretores avaliadores

    bool primeiraAgendaImpressa = false;
    for (Corretor& corretor : corretores) {
        if (!corretor.isAvaliador() || corretor.getImoveisParaAvaliar().empty()) {
            continue;
        }

        if (primeiraAgendaImpressa) {
            std::cout << std::endl;
        }
        
        std::cout << "Corretor " << corretor.getId() << std::endl;
        primeiraAgendaImpressa = true;

        std::vector<Imovel*> rotaNaoVisitada = corretor.getImoveisParaAvaliar(); // array de ponteiros para os imóveis que o corretor precisa visitar
        double localAtualLat = corretor.getLat();
        double localAtualLng = corretor.getLng(); //cria um copia dos imoveis e define a localização inicial do corretor
        int tempoTotalMinutos = 9 * 60; // Inicia as 9:00 

        while (!rotaNaoVisitada.empty()) {
            Imovel* proximoImovel = nullptr; 
            double menorDistancia = std::numeric_limits<double>::max(); // Inicializa a menor distância com o maior valor possível
            auto itMaisProximo = rotaNaoVisitada.begin();       // Iterador para o imóvel mais próximo

            for (auto it = rotaNaoVisitada.begin(); it != rotaNaoVisitada.end(); ++it) {
                double dist = haversine(localAtualLat, localAtualLng, (*it)->getLat(), (*it)->getLng());
                if (dist < menorDistancia) {
                    menorDistancia = dist; 
                    proximoImovel = *it; // guarda o ponteiro do próximo imóvel
                    itMaisProximo = it; // guarda a posição do iterador mais próximo na lista
                }
            }
            
           
            int tempoDeslocamento = menorDistancia * TEMPO_DESLOCAMENTO_MIN_POR_KM;
            
            tempoTotalMinutos += tempoDeslocamento;

            int hora = tempoTotalMinutos / 60;
            int minuto = tempoTotalMinutos % 60;
            std::cout << std::setfill('0') << std::setw(2) << hora << ":"  // setfill('0') é usado para preencher com zeros à esquerda e setw(2) garante que sempre teremos dois dígitos
                      << std::setw(2) << minuto << " Imóvel " << proximoImovel->getId() << std::endl;
            
            tempoTotalMinutos += DURACAO_AVALIACAO_MIN; // adiona o tempo gasto na avaliação

            localAtualLat = proximoImovel->getLat();
            localAtualLng = proximoImovel->getLng(); // atualiza a loc do corretor

            rotaNaoVisitada.erase(itMaisProximo); // remove o imóvel visitado da lista de imóveis a visitar
        }
    }
}
