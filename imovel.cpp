#include "imovel.h"


int Imovel::nextId = 1;


Imovel::Imovel(TipoImovel tipo, int propId, double lat, double lng, const std::string& endereco, double preco)
    : id(nextId++), tipo(tipo), proprietarioId(propId), lat(lat), lng(lng), endereco(endereco), preco(preco) {
   
}

// getters

int Imovel::getId() const {
    return this->id;
}

TipoImovel Imovel::getTipo() const {
    return this->tipo;
}

int Imovel::getProprietarioId() const {
    return this->proprietarioId;
}

double Imovel::getLat() const {
    return this->lat;
}

double Imovel::getLng() const {
    return this->lng;
}


const std::string& Imovel::getEndereco() const {
    return this->endereco;
}

double Imovel::getPreco() const {
    return this->preco;
}
