#include "WeWy.h"
#include "Funkcje.h"


// Funkcja kt�ra dostaje arkunety oraz ich ilo�� i sprawdza czy wpisa�a� co� po -o je�li nie to "Nie podano warto�ci paramart�w"
std::string NumerStolika(const int& argc, char* argv[]) {
    std::string n;
    if (argc == 1) {
        n = "0";
        return n;
        std::cout << "Nie podano warto�ci paramart�w";
    }
    else {
        for (int i = 1; i < argc; ++i) {
            std::string param_in{ argv[i] };
            if (param_in == "-s") {
                n = argv[i + 1];
                return n;
            }
            else {
                std::cout << "B��dny parametr";
            }
        }
    }
}


// fukncja do otwierania pliku oraz zapisaywania do struktry a potem t� struktur� zapisuje do wektora i w wektorze
// zbieramy wszystkie struktury by mie� wszystkie dane razem i ��two po nich si� przemieszcza� oraz nimi zarz�dza�, 
// by mie� je wszystkie w jednym miejsu
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

    //Wy�wietlanie zawarto�ci listy czyli pliku

    plik.close(); //zamkni�cie pliku
};


// funkcja kt�ra po zebraniu wszystkich danych do wektora, po kolei wpisuje do pliku 
void ZapisDoPliku(std::vector<Zamowienie>& Zam�wienie, int& argc, char* argv[]) {
    std::ofstream plik_wyj;
    plik_wyj.open("zamowienie.txt");
    if (plik_wyj.is_open()) {
        plik_wyj << "Stolik nr " << NumerStolika(argc, argv) << std::endl;
        for (size_t j = 0; j < Zam�wienie.size(); j++)
        {
            plik_wyj << Zam�wienie[j].nazwa_przedm << "          " << Zam�wienie[j].cena_przedm << "\n";
        }
    }
    plik_wyj.close(); //zamkni�cie pliku}
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