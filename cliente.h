#pragma once

#include <string>

class Cliente {
private:
    static int nextId; // static variable makes nextId shared across all instances
    int id;
    std::string telefone;
    std::string nome;

public:
    Cliente(const std::string& telefone, const std::string& nome);

    // Getters
    int getId() const;
    std::string getTelefone() const;
    std::string getNome() const;
};
