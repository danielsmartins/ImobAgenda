#pragma once

#include <string>

class Corretor {
private:
    static int nextId; // static variable makes nextId shared across all instances

    int id;
    bool avaliador;
    double latitude;
    double longitude;
    std::string telefone;
    std::string nome;

    public:
    Corretor(const std::string& telefone, bool avaliador, double latitude, double longitude, const std::string& nome);

    // Getters
    int getId() const;
    bool isAvaliador() const;
    double getLatitude() const;
    double getLongitude() const;
    std::string getTelefone() const;
    std::string getNome() const;
};