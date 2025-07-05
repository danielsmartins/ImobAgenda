#pragma once

#include <string>

class Cliente {
private:
    static int nextId; // variavel estática compartilhada por todas as instâncias de Cliente
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
