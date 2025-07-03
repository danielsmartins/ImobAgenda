#include "corretor.h"

int Corretor::nextId = 1;

 Corretor::Corretor(const std::string& telefone, bool avaliador, double latitude, double longitude, const std::string& nome):
  id(nextId++), avaliador(avaliador), latitude(latitude), longitude(longitude), telefone(telefone), nome(nome)
{};

int Corretor::getId() const {
    return id;
}


double Corretor::getLatitude() const {
    return latitude;
};
double Corretor::getLongitude() const {
    return longitude;
};
std::string Corretor::getTelefone() const{
    return telefone;
};
std::string Corretor::getNome() const{
    return nome;
};
bool Corretor::isAvaliador() const{
    return avaliador;
};