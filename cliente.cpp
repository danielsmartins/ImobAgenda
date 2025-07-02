#include "cliente.h"

int Cliente::nextId = 1;

// Constructor that initializes the Cliente object with a phone number and name
// and assigns a unique sequencial ID to each new Cliente instance.
Cliente::Cliente(const std::string& telefone, const std::string& nome)
    : id(nextId++), telefone(telefone), nome(nome) {
    
}

int Cliente::getId() const {
    return id;
}

std::string Cliente::getTelefone() const {
    return telefone;
}

std::string Cliente::getNome() const {
    return nome;
}