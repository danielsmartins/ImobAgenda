#include "corretor.h"
#include "imovel.h" // Incluímos aqui para que a classe Corretor saiba o que é um Imovel

// Inicializa o contador de ID estático. Ele é compartilhado por todos os objetos Corretor.
int Corretor::nextId = 1;

// Implementação do Construtor
// Usa a lista de inicialização de membros para atribuir os valores diretamente.
Corretor::Corretor(const std::string& telefone, bool avaliador, double lat, double lng, const std::string& nome)
    : id(nextId++), nome(nome), telefone(telefone), avaliador(avaliador), lat(lat), lng(lng) {
    // O corpo do construtor pode ficar vazio, pois todo o trabalho foi feito na lista de inicialização.
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
