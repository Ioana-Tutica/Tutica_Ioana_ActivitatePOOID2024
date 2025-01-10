#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Carte {
private:
    const int id;
    static int nrCarti;
    string titlu;
    int nrCapitole;
    float* preturiCapitole;

public:
    Carte() : id(++nrCarti) {
        this->titlu = "Necunoscut";
        this->nrCapitole = 0;
        this->preturiCapitole = nullptr;
    }

    Carte(string _titlu, int nrCapitole, const float* preturi) : id(++nrCarti) {
        this->titlu = _titlu;
        this->nrCapitole = nrCapitole;
        this->preturiCapitole = new float[nrCapitole];
        for (int i = 0; i < nrCapitole; i++) {
            this->preturiCapitole[i] = preturi[i];
        }
    }

    Carte(const Carte& c) : id(++nrCarti) {
        this->titlu = c.titlu;
        this->nrCapitole = c.nrCapitole;
        this->preturiCapitole = new float[c.nrCapitole];
        for (int i = 0; i < c.nrCapitole; i++) {
            this->preturiCapitole[i] = c.preturiCapitole[i];
        }
    }

    Carte& operator=(const Carte& c) {
        if (this != &c) {
            this->titlu = c.titlu;
            this->nrCapitole = c.nrCapitole;
            if (this->preturiCapitole != nullptr) {
                delete[] this->preturiCapitole;
            }
            this->preturiCapitole = new float[c.nrCapitole];
            for (int i = 0; i < c.nrCapitole; i++) {
                this->preturiCapitole[i] = c.preturiCapitole[i];
            }
        }
        return *this;
    }

    Carte operator+=(float pret) {
        this->nrCapitole++;
        float* aux = new float[this->nrCapitole];
        for (int i = 0; i < this->nrCapitole - 1; i++) {
            aux[i] = this->preturiCapitole[i];
        }
        aux[this->nrCapitole - 1] = pret;
        if (this->preturiCapitole != nullptr) {
            delete[] this->preturiCapitole;
        }
        this->preturiCapitole = aux;
        return *this;
    }

    ~Carte() {
        if (this->preturiCapitole != nullptr) {
            delete[] this->preturiCapitole;
        }
    }

    void afisare() const {
        cout << "Carte: " << this->titlu << ", cu " << this->nrCapitole 
             << " capitole. Preturi capitole:";
        for (int i = 0; i < this->nrCapitole; i++) {
            cout << " " << this->preturiCapitole[i];
        }
        cout << endl;
    }