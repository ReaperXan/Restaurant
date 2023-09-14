#include "WeWy.h"
#include "Funkcje.h"


// Funkcja która dostaje arkunety oraz ich iloœæ i sprawdza czy wpisa³aœ coœ po -o jeœli nie to "Nie podano wartoœci paramartów"
std::string NumerStolika(const int& argc, char* argv[]) {
    std::string n;
    if (argc == 1) {
        n = "0";
        return n;
        std::cout << "Nie podano wartoœci paramartów";
    }
    else {
        for (int i = 1; i < argc; ++i) {
            std::string param_in{ argv[i] };
            if (param_in == "-s") {
                n = argv[i + 1];
                return n;
            }
            else {
                std::cout << "B³êdny parametr";
            }
        }
    }
}


// fukncja do otwierania pliku oraz zapisaywania do struktry a potem tê strukturê zapisuje do wektora i w wektorze
// zbieramy wszystkie struktury by mieæ wszystkie dane razem i ³¹two po nich siê przemieszczaæ oraz nimi zarz¹dzaæ, 
// by mieæ je wszystkie w jednym miejsu
restaurant restracja2;

void CzytaniePliku(std::string nazwa_pliku, std::vector<Menu>& ListaPozycji)
{
    Menu pozycja;
    std::ifstream plik;
    plik.open(nazwa_pliku);

    if (plik.is_open())
    {
        std::string linia;
        while (std::getline(plik, linia))
        {

            std::stringstream ss(linia);
            std::string id;
            std::string cena;

            std::getline(ss, id, ';');
            pozycja.id = restracja2.ZmianaTypuNaInt(id);
            std::getline(ss, pozycja.nazwa, ';');
            std::getline(ss, pozycja.kategoria, ';');
            std::getline(ss, cena, ';');
            pozycja.cena = restracja2.ZmianaTypuNaFloat(cena);
            std::getline(ss, pozycja.opis, ';');

            ListaPozycji.push_back(pozycja);
        }
    }

    //Wyœwietlanie zawartoœci listy czyli pliku

    plik.close(); //zamkniêcie pliku
};


// funkcja która po zebraniu wszystkich danych do wektora, po kolei wpisuje do pliku 
void ZapisDoPliku(std::vector<Zamowienie>& Zamówienie, int& argc, char* argv[]) {
    std::ofstream plik_wyj;
    plik_wyj.open("zamowienie.txt");
    if (plik_wyj.is_open()) {
        plik_wyj << "Stolik nr " << NumerStolika(argc, argv) << std::endl;
        for (size_t j = 0; j < Zamówienie.size(); j++)
        {
            plik_wyj << Zamówienie[j].nazwa_przedm << "          " << Zamówienie[j].cena_przedm << "\n";
        }
    }
    plik_wyj.close(); //zamkniêcie pliku}
}

void WczytanieZPliku(std::string filename1) 
{
    std::ifstream plik1;
    plik1.open(filename1);
    std::string wiersz1;
    while (!plik1.eof()){
        getline(plik1, wiersz1);
        std::cout<<wiersz1 << std::endl;
    }
    plik1.close();
}
void WczytanieZamowienia(std::string filename2)
{
    std::ifstream plik2;
    plik2.open(filename2);
    std::string wiersz2;
    while (!plik2.eof()) {
        getline(plik2, wiersz2);
        std::cout << wiersz2 << std::endl;
    }
    plik2.close();
}