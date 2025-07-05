#pragma once

#include <string>
#include <vector>

class Imovel;

class Corretor {
private:
    static int nextId;

    int id;
    std::string nome;
    std::string telefone;
    bool avaliador;
    double lat;
    double lng;
    
    // Vetor para guardar ponteiros para os imóveis atribuídos a este corretor.
    std::vector<Imovel*> imoveisParaAvaliar;

public:
    
    Corretor(const std::string& telefone, bool avaliador, double lat, double lng, const std::string& nome);

    //Getters
    int getId() const;
    const std::string& getNome() const;
    const std::string& getTelefone() const;
    bool isAvaliador() const;
    double getLat() const; 
    double getLng() const; 
    
    
    const std::vector<Imovel*>& getImoveisParaAvaliar() const;

    //Setters 
    
    // Adiciona um ponteiro de Imovel à lista de avaliação.
    void addImovelParaAvaliar(Imovel* imovel);
};

