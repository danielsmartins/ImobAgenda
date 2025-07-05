#include "agenda.h"

#include <iostream>
#include <vector>
#include <string>

// Garante que constantes matemáticas como M_PI sejam definidas pela biblioteca cmath.
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
    for (Corretor& corretor : corretores) {
        if (corretor.isAvaliador()) {
            avaliadores.push_back(&corretor);
        }
    }

    if (avaliadores.empty()) {
        return;
    }

    std::sort(imoveis.begin(), imoveis.end(), [](const Imovel& a, const Imovel& b) {
        return a.getId() < b.getId();
    });

    size_t avaliador_idx = 0;
    for (Imovel& imovel : imoveis) {
        avaliadores[avaliador_idx]->addImovelParaAvaliar(&imovel);
        avaliador_idx = (avaliador_idx + 1) % avaliadores.size();
    }
}

// --- Função Principal de Agendamento ---

void gerarEImprimirAgenda(std::vector<Corretor>& corretores, std::vector<Imovel>& imoveis) {
    distribuirImoveis(corretores, imoveis);

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

        std::vector<Imovel*> rotaNaoVisitada = corretor.getImoveisParaAvaliar();
        double localAtualLat = corretor.getLat();
        double localAtualLng = corretor.getLng();
        int tempoTotalMinutos = 9 * 60;

        while (!rotaNaoVisitada.empty()) {
            Imovel* proximoImovel = nullptr;
            double menorDistancia = std::numeric_limits<double>::max();
            auto itMaisProximo = rotaNaoVisitada.begin();

            for (auto it = rotaNaoVisitada.begin(); it != rotaNaoVisitada.end(); ++it) {
                double dist = haversine(localAtualLat, localAtualLng, (*it)->getLat(), (*it)->getLng());
                if (dist < menorDistancia) {
                    menorDistancia = dist;
                    proximoImovel = *it;
                    itMaisProximo = it;
                }
            }
            
            // -------- A CORREÇÃO ESTÁ AQUI --------
            // Trocamos round() por uma conversão direta para int, que TRUNCA o valor.
            // Ex: 2.9 minutos se tornam 2 minutos.
            int tempoDeslocamento = menorDistancia * TEMPO_DESLOCAMENTO_MIN_POR_KM;
            
            tempoTotalMinutos += tempoDeslocamento;

            int hora = tempoTotalMinutos / 60;
            int minuto = tempoTotalMinutos % 60;
            std::cout << std::setfill('0') << std::setw(2) << hora << ":"
                      << std::setw(2) << minuto << " Imóvel " << proximoImovel->getId() << std::endl;
            
            tempoTotalMinutos += DURACAO_AVALIACAO_MIN;

            localAtualLat = proximoImovel->getLat();
            localAtualLng = proximoImovel->getLng();

            rotaNaoVisitada.erase(itMaisProximo);
        }
    }
}
