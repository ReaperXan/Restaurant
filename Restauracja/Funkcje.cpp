#include "Funkcje.h"
#include "WeWy.h"

// funkcja do zmiany z typu string na int
int restaurant::ZmianaTypuNaInt(const std::string& name) {
    std::stringstream stream;
    int n;
    stream << name;
    stream >> n;
    return n;
}

// funkcja do zmiany z typu string na double
double restaurant::ZmianaTypuNaFloat(const std::string& name) {
    std::stringstream stream;
    double n;
    stream << name;
    stream >> n;
    return n;
}


// przekazujemy stworzony w main wektor ListaPozycji by pobraæ kazd¹ strukturê zapisan¹ w tym wektorze
// by z nich tylko zabraæ kategoriê ka¿dej pozycji z pliku i w wektorze
// Kategorie bêdziemy zapisywaæ ka¿d¹ kategoriê pomimo powtórzeñ
// poczym posortujemy i zlikwidujemy powtórzenia 
// na koñcu wyœwietlamy kategorie bez powtórzeñ 
void restaurant::WyswietlenieKategorii(std::vector<Menu>& ListaPozycji, std::vector<std::string>& Kategorie) {

    //dodawanie ze wszystkich struktur/pozycji menu kategorii do wektora by zebraæ je razem i potem wywaliæ powtórzenia
    for (size_t i = 0; i < ListaPozycji.size(); i++)
    {
        Kategorie.push_back(ListaPozycji[i].kategoria);
    }

    //wywalanie duplikatów - wyt³umaczone masz to w jednym z przydatnych linków 
    std::sort(Kategorie.begin(), Kategorie.end());
    auto end = std::unique(Kategorie.begin(), Kategorie.end());

    Kategorie.erase(end, Kategorie.end());

    // wyœwietlenie menu (kategrii bez powtórzeñ)
    std::cout << "--------Menu--------\n";
    for (size_t i = 0; i < Kategorie.size(); i++)
    {
        std::cout << (i + 1) << " " << Kategorie[i] << std::endl;
    }
    std::cout << std::endl << 0 << " z³ó¿ zamówienie \n\n";
    std::cout << "r Wyczyœæ zamówienie \n\n";
    std::cout << "k Poka¿ personel \n\n";
    std::cout << "z Poka¿ zamowienie \n\n";
}


// Tworzenie zamówienia
// przekazujemy wszystkie wektory dziêki którym bêdziemy pobieraæ dane, sprawdzaæ je i zapisywac do stróktur 
// poczym te struktury zapisujemy do wektora Zamówienie, argc oraz argv s¹ przekazywane tylko by przekazaæ siê dalej w funkcji zapisDoPliku
// Pobieramy tutaj wartoœc od u¿ytkownika, zale¿nie co wpisa³ to wykonujemy polecenie 
// jeœli u¿ytkownik wybra³ wartoœæ która jest prypisana do którejœ kategorii to pobieramy pokolei wszystkie linie z tej kategorii 
// z wektora ListaPozycji i zapisujemy je do struktury poczym ca³¹ strukturê wpychamy do wektora i tak do momêtu gdy nie bêdzie
// wszystkich lini z danej kategorii, po zapisaniu wyœwietlamy wszystkie te dania czy piæka z danej kategorii 
// pozwalamy u¿ytkownikkowi wybrac co chce zamówiæ i to co wybierze zapisujemy do struktury zamowienie a póŸiej ca³¹
// strukturê do wektora zamówienie 
void restaurant::TworzenieZamowienia(std::vector<Menu>& ListaPozycji, std::vector<std::string>& Kategorie, std::vector<Menu>& Kategoria_wybrana, std::vector<Zamowienie>& Zamówienie, int& argc, char* argv[]) {

    std::string wybor;
    std::cin >> wybor;

    // sprawdzamy czy wpisana przed chwil¹ wartoœc jest zerem jeœli tak to koniec i wywo³aj plik koñcowy
    if (wybor == "0") {
        ZapisDoPliku(Zamówienie, argc, argv);
        std::cout << "\nZ³o¿y³aœ/eœ zamównienie\n";
    
    // czyszczenie wektora z zamówieniem (usuwanie wszystkiego co doda³ uzytkownik)
    // koñczenie programu
    }
    else if (wybor == "r") {
        Zamówienie.clear();
        std::cout << "\nWyczyœcia³aœ/es zamównienie\n";
    }
    else if (wybor == "k") {
        std::cout << "\nDostepny personel\n";
         WczytanieZPliku("personel.txt");
    }
    else if (wybor == "z") {
        std::cout << "\nAktualne Zamówienie\n";
        WczytanieZamowienia("zamowienie.txt");
    }
    else {

        // przywo³anie strutur (przypisanie ¿e struktura bêdzie wywo³ywania pod nazw¹ pozycja np. pozycja.cena)
        Menu pozycja;
        Zamowienie pozycja_zam;

        // wyczyszczenie wekora by przy ka¿dym wywo³aniu wyœwietla³y siê tylko Kategoria któr¹ u¿ytkowik aktualnie wybra³ a nie 
        // wszystkie nawet te które wczeœniej zosta³y wybrane.
        Kategoria_wybrana.clear();

        // sprawdzenie czy wybór u¿ytkownika jest warotœci¹ któr¹ mo¿na znaleŸæ w wekorze kategoria +1 jest dlatego by zacz¹æ od 1 
        // bo jeœli by tego nie by³o to zaczyna³o by siê liczniee od 0
        if (ZmianaTypuNaInt(wybor) < Kategorie.size() + 1) {
            std::cout << "--------" << Kategorie[ZmianaTypuNaInt(wybor) - 1] << " -------- \n";
            for (size_t i = 0; i < ListaPozycji.size(); i++)
            {

                // dodanie do struktury pozycji które równaj¹ siê kategori¹ z tym co u¿ytkownik wybra³
                // poczym wpychamy ca³¹ strukturê do wektora
                if (ListaPozycji[i].kategoria == Kategorie[ZmianaTypuNaInt(wybor) - 1]) {
                    pozycja.nazwa = ListaPozycji[i].nazwa;
                    pozycja.cena = ListaPozycji[i].cena;
                    pozycja.opis = ListaPozycji[i].opis;
                    pozycja.id = ListaPozycji[i].id;
                    Kategoria_wybrana.push_back(pozycja);
                }
            }

            //wyœwietlenie zawartoœci wektora z zapisanymi kategoriami
            for (size_t j = 0; j < Kategoria_wybrana.size(); j++)
            {
                std::cout << j + 1 << " " << Kategoria_wybrana[j].nazwa << "          " << Kategoria_wybrana[j].cena << "; " << Kategoria_wybrana[j].opis << "\n";
            }
            std::cout << "\n0 powrót" << std::endl;
            std::string wybor_poz;

            // pozwolenie u¿ytkonikowi na wybór przedmiotu który chce zamówiæ 
            // dopuki nie wpisze 0
            while (ZmianaTypuNaInt(wybor_poz) != 0) {
                std::cin >> wybor_poz;
                
                // sprawdzenie czy wybór u¿ytkownika jest warotœci¹ któr¹ mo¿na znaleŸæ w wekorze kategoria +1 jest dlatego by zacz¹æ od 1 
                // bo jeœli by tego nie by³o to zaczyna³o by siê liczniee od 0 oraz sprawdzenie czy nie jest wpisana wartoœæ 0
                // jeœli by by³¹ to jest spoza zakresu gdy¿ zaczynamy jak pisa³em wczeœniej od 1
                if (ZmianaTypuNaInt(wybor_poz) < Kategoria_wybrana.size() + 1 && ZmianaTypuNaInt(wybor_poz) != 0) {

                    // zapisanie danych wybranych przez u¿ytkownika do struktury i póŸniej do wektora
                    pozycja_zam.id_przedm = Kategoria_wybrana[ZmianaTypuNaInt(wybor_poz) - 1].id;
                    pozycja_zam.nazwa_przedm = Kategoria_wybrana[ZmianaTypuNaInt(wybor_poz) - 1].nazwa;
                    pozycja_zam.cena_przedm = Kategoria_wybrana[ZmianaTypuNaInt(wybor_poz) - 1].cena;
                    Zamówienie.push_back(pozycja_zam);
                }
            }

            // sprawdzenie czy wpisana wartoœæ to 0 jeœli tak to wywo³aj funkcjê która wyœwietla menu 
            // oraz po wybraniu kategorii w funkcji WyswietlenieKategorii
            // przechodzi do wywo³ania samej siebie by znów pozwoliæ u¿ytkownikowi na dopisanie czegoœ do zamówienia
            // po prostu wykonuje siê jeszcze raz 
            if (ZmianaTypuNaInt(wybor_poz) == 0) {
                /*for (size_t j = 0; j < Zamówienie.size(); j++)
                {
                    std::cout << j + 1 << " " << Zamówienie[j].nazwa_przedm << "          " << Zamówienie[j].cena_przedm << "\n";
                }*/
                WyswietlenieKategorii(ListaPozycji, Kategorie);
                TworzenieZamowienia(ListaPozycji, Kategorie, Kategoria_wybrana, Zamówienie, argc, argv);
            }
        }
        else {
            std::cout << "B³êdna kategoria";
        }
    }
}
