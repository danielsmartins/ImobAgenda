#include "corretor.h"
#include "imovel.h" 


int Corretor::nextId = 1;

Corretor::Corretor(const std::string& telefone, bool avaliador, double lat, double lng, const std::string& nome)
    : id(nextId++), nome(nome), telefone(telefone), avaliador(avaliador), lat(lat), lng(lng) {
    
}

// --- Implementação dos Getters ---

int Corretor::getId() const {
    return this->id;
}


const std::string& Corretor::getNome() const {
    return this->nome;
}


const std::string& Corretor::getTelefone() const {
    return this->telefone;
}

bool Corretor::isAvaliador() const {
    return this->avaliador;
}

double Corretor::getLat() const {
    return this->lat;
}

double Corretor::getLng() const {
    return this->lng;
}


const std::vector<Imovel*>& Corretor::getImoveisParaAvaliar() const {
    return this->imoveisParaAvaliar;
}

// --- Implementação dos Modificadores ---

// Adiciona um ponteiro de Imovel à lista de avaliação do corretor.
void Corretor::addImovelParaAvaliar(Imovel* imovel) {
    this->imoveisParaAvaliar.push_back(imovel);
}
