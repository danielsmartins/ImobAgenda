#pragma once

#include <string>


enum class TipoImovel {
    Casa,
    Apartamento,
    Terreno
};

class Imovel {
private:
    static int nextId;

    int id;
    TipoImovel tipo;
    int proprietarioId;
    double lat;
    double lng;
    std::string endereco;
    double preco;

public:
    // Construtor
    Imovel(TipoImovel tipo, int propId, double lat, double lng, const std::string& endereco, double preco);

    // --- Getters ---
    int getId() const;
    TipoImovel getTipo() const;
    int getProprietarioId() const;
    double getLat() const; 
    double getLng() const; 
    const std::string& getEndereco() const;
    double getPreco() const;
};


