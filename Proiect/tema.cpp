#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Autobuz {
private:
    static int nrAutobuze;
    const int idAutobuz;
    int capacitate;
    int nrPersoaneImbarcate;
    char* producator;

public:
    Autobuz() : idAutobuz(++nrAutobuze), capacitate(50), nrPersoaneImbarcate(0) {
        producator = new char[strlen("Necunoscut") + 1];
        strcpy(producator, "Necunoscut");
    }

    Autobuz(int _capacitate, int _nrPersoaneImbarcate, const char* _producator)
        : idAutobuz(++nrAutobuze) {
        if (_capacitate > 0 && _nrPersoaneImbarcate >= 0 && _nrPersoaneImbarcate <= _capacitate) {
            capacitate = _capacitate;
            nrPersoaneImbarcate = _nrPersoaneImbarcate;
            producator = new char[strlen(_producator) + 1];
            strcpy(producator, _producator);
        }
        else {
            capacitate = 0;
            nrPersoaneImbarcate = 0;
            producator = new char[strlen("Invalid") + 1];
            strcpy(producator, "Invalid");
            cout << "Parametri invalizi: nrPersoaneImbarcate (" << _nrPersoaneImbarcate
                << ") este mai mare decat capacitatea (" << _capacitate << ") sau valorile sunt negative." << endl;
        }
    }

    ~Autobuz() {
        cout << "Destructorul a fost apelat" << endl;
        delete[] producator;
    }

    Autobuz(const Autobuz& other) : idAutobuz(++nrAutobuze) {
        capacitate = other.capacitate;
        nrPersoaneImbarcate = other.nrPersoaneImbarcate;
        producator = new char[strlen(other.producator) + 1];
        strcpy(producator, other.producator);
    }

    Autobuz& operator=(const Autobuz& other) {
        if (this == &other) return *this;

        capacitate = other.capacitate;
        nrPersoaneImbarcate = other.nrPersoaneImbarcate;

        delete[] producator;
        producator = new char[strlen(other.producator) + 1];
        strcpy(producator, other.producator);

        return *this;
    }

    int getCapacitate() const {
        return capacitate;
    }

    void setCapacitate(int _capacitate) {
        if (_capacitate > 0) {
            capacitate = _capacitate;
        }
    }

    int getNrPersoaneImbarcate() const {
        return nrPersoaneImbarcate;
    }

    void setNrPersoaneImbarcate(int _nrPersoaneImbarcate) {
        if (_nrPersoaneImbarcate >= 0 && _nrPersoaneImbarcate <= capacitate) {
            nrPersoaneImbarcate = _nrPersoaneImbarcate;
        }
    }

    friend ostream& operator<<(ostream& out, const Autobuz& a) {
        out << a.idAutobuz << "; " << a.capacitate << "; " << a.nrPersoaneImbarcate << "; " << a.producator;
        return out;
    }

    int getNumarLocuriLibere() const {
        return capacitate - nrPersoaneImbarcate;
    }

    operator int() const {
        return nrPersoaneImbarcate;
    }

    bool operator>(const Autobuz& other) const {
        return this->capacitate > other.capacitate;
    }
};

int Autobuz::nrAutobuze = 0;

int main() {
    cout << "Constructor FARA parametri:" << endl;
    Autobuz a1;
    cout << "Autobuz: " << a1 << endl;

    cout << "\nConstructor CU parametri:" << endl;
    Autobuz a2(60, 30, "Mercedes");
    cout << "Autobuz: " << a2 << endl;

    cout << "\nConstructor CU parametri dar valori invalide" << endl;
    Autobuz a3(-10, 50, "InvalidBus");
    cout << "Autobuz: " << a3 << endl;

    cout << "\nConstructor de copiere" << endl;
    Autobuz a4 = a2;
    cout << "copie a Autobuzului a2: " << a4 << endl;

    cout << "\nOperator de asignare" << endl;
    a1 = a4;
    cout << "dupa asignare, a1: " << a1 << endl;

    cout << "\nGetters si setters:" << endl;
    cout << "Capacitate initiala in a2: " << a2.getCapacitate() << endl;
    a2.setCapacitate(40);
    cout << "Capacitate setata in a2: " << a2.getCapacitate() << endl;

    cout << "Persoane imbarcate initial in a2: " << a2.getNrPersoaneImbarcate() << endl;
    a2.setNrPersoaneImbarcate(50);
    cout << "Persoane imbarcate dupa setter in a2: " << a2.getNrPersoaneImbarcate() << endl;

    cout << "\nTest operator '<<'" << endl;
    cout << "Detalii a2: " << a2 << endl;

    cout << "\nTestare getNumarLocuriLibere" << endl;
    cout << "Locuri libere in a2: " << a2.getNumarLocuriLibere() << endl;

    cout << "\nTestare operator de cast la int" << endl;
    int persoaneInA2 = int(a2);
    cout << "Numar persoane in a2 (cast la int): " << persoaneInA2 << endl;

    cout << "\nTestare operator comparare '>'" << endl;
    if (a1 > a2) {
        cout << "Autobuzul a1 are capacitate mai mare ca autobuzul a2." << endl;
    }

    cout << "\nTestare destructor la iesirea din scope" << endl;
    {
        Autobuz tempAutobuz(40, 20, "TemporaryBus");
        cout << "Temporary Autobuz: " << tempAutobuz << endl;
        cout << "Se iese din scope-ul pentru tempAutobuz" << endl;
    }
    return 0;
}
