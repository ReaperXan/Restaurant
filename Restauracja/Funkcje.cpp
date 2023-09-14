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


// przekazujemy stworzony w main wektor ListaPozycji by pobra� kazd� struktur� zapisan� w tym wektorze
// by z nich tylko zabra� kategori� ka�dej pozycji z pliku i w wektorze
// Kategorie b�dziemy zapisywa� ka�d� kategori� pomimo powt�rze�
// poczym posortujemy i zlikwidujemy powt�rzenia 
// na ko�cu wy�wietlamy kategorie bez powt�rze� 
void restaurant::WyswietlenieKategorii(std::vector<Menu>& ListaPozycji, std::vector<std::string>& Kategorie) {

    //dodawanie ze wszystkich struktur/pozycji menu kategorii do wektora by zebra� je razem i potem wywali� powt�rzenia
    for (size_t i = 0; i < ListaPozycji.size(); i++)
    {
        Kategorie.push_back(ListaPozycji[i].kategoria);
    }

    //wywalanie duplikat�w - wyt�umaczone masz to w jednym z przydatnych link�w 
    std::sort(Kategorie.begin(), Kategorie.end());
    auto end = std::unique(Kategorie.begin(), Kategorie.end());

    Kategorie.erase(end, Kategorie.end());

    // wy�wietlenie menu (kategrii bez powt�rze�)
    std::cout << "--------Menu--------\n";
    for (size_t i = 0; i < Kategorie.size(); i++)
    {
        std::cout << (i + 1) << " " << Kategorie[i] << std::endl;
    }
    std::cout << std::endl << 0 << " z�� zam�wienie \n\n";
    std::cout << "r Wyczy�� zam�wienie \n\n";
    std::cout << "k Poka� personel \n\n";
    std::cout << "z Poka� zamowienie \n\n";
}


// Tworzenie zam�wienia
// przekazujemy wszystkie wektory dzi�ki kt�rym b�dziemy pobiera� dane, sprawdza� je i zapisywac do str�ktur 
// poczym te struktury zapisujemy do wektora Zam�wienie, argc oraz argv s� przekazywane tylko by przekaza� si� dalej w funkcji zapisDoPliku
// Pobieramy tutaj warto�c od u�ytkownika, zale�nie co wpisa� to wykonujemy polecenie 
// je�li u�ytkownik wybra� warto�� kt�ra jest prypisana do kt�rej� kategorii to pobieramy pokolei wszystkie linie z tej kategorii 
// z wektora ListaPozycji i zapisujemy je do struktury poczym ca�� struktur� wpychamy do wektora i tak do mom�tu gdy nie b�dzie
// wszystkich lini z danej kategorii, po zapisaniu wy�wietlamy wszystkie te dania czy pi�ka z danej kategorii 
// pozwalamy u�ytkownikkowi wybrac co chce zam�wi� i to co wybierze zapisujemy do struktury zamowienie a p�iej ca��
// struktur� do wektora zam�wienie 
void restaurant::TworzenieZamowienia(std::vector<Menu>& ListaPozycji, std::vector<std::string>& Kategorie, std::vector<Menu>& Kategoria_wybrana, std::vector<Zamowienie>& Zam�wienie, int& argc, char* argv[]) {

    std::string wybor;
    std::cin >> wybor;

    // sprawdzamy czy wpisana przed chwil� warto�c jest zerem je�li tak to koniec i wywo�aj plik ko�cowy
    if (wybor == "0") {
        ZapisDoPliku(Zam�wienie, argc, argv);
        std::cout << "\nZ�o�y�a�/e� zam�wnienie\n";
    
    // czyszczenie wektora z zam�wieniem (usuwanie wszystkiego co doda� uzytkownik)
    // ko�czenie programu
    }
    else if (wybor == "r") {
        Zam�wienie.clear();
        std::cout << "\nWyczy�cia�a�/es zam�wnienie\n";
    }
    else if (wybor == "k") {
        std::cout << "\nDostepny personel\n";
         WczytanieZPliku("personel.txt");
    }
    else if (wybor == "z") {
        std::cout << "\nAktualne Zam�wienie\n";
        WczytanieZamowienia("zamowienie.txt");
    }
    else {

        // przywo�anie strutur (przypisanie �e struktura b�dzie wywo�ywania pod nazw� pozycja np. pozycja.cena)
        Menu pozycja;
        Zamowienie pozycja_zam;

        // wyczyszczenie wekora by przy ka�dym wywo�aniu wy�wietla�y si� tylko Kategoria kt�r� u�ytkowik aktualnie wybra� a nie 
        // wszystkie nawet te kt�re wcze�niej zosta�y wybrane.
        Kategoria_wybrana.clear();

        // sprawdzenie czy wyb�r u�ytkownika jest warot�ci� kt�r� mo�na znale�� w wekorze kategoria +1 jest dlatego by zacz�� od 1 
        // bo je�li by tego nie by�o to zaczyna�o by si� liczniee od 0
        if (ZmianaTypuNaInt(wybor) < Kategorie.size() + 1) {
            std::cout << "--------" << Kategorie[ZmianaTypuNaInt(wybor) - 1] << " -------- \n";
            for (size_t i = 0; i < ListaPozycji.size(); i++)
            {

                // dodanie do struktury pozycji kt�re r�wnaj� si� kategori� z tym co u�ytkownik wybra�
                // poczym wpychamy ca�� struktur� do wektora
                if (ListaPozycji[i].kategoria == Kategorie[ZmianaTypuNaInt(wybor) - 1]) {
                    pozycja.nazwa = ListaPozycji[i].nazwa;
                    pozycja.cena = ListaPozycji[i].cena;
                    pozycja.opis = ListaPozycji[i].opis;
                    pozycja.id = ListaPozycji[i].id;
                    Kategoria_wybrana.push_back(pozycja);
                }
            }

            //wy�wietlenie zawarto�ci wektora z zapisanymi kategoriami
            for (size_t j = 0; j < Kategoria_wybrana.size(); j++)
            {
                std::cout << j + 1 << " " << Kategoria_wybrana[j].nazwa << "          " << Kategoria_wybrana[j].cena << "; " << Kategoria_wybrana[j].opis << "\n";
            }
            std::cout << "\n0 powr�t" << std::endl;
            std::string wybor_poz;

            // pozwolenie u�ytkonikowi na wyb�r przedmiotu kt�ry chce zam�wi� 
            // dopuki nie wpisze 0
            while (ZmianaTypuNaInt(wybor_poz) != 0) {
                std::cin >> wybor_poz;
                
                // sprawdzenie czy wyb�r u�ytkownika jest warot�ci� kt�r� mo�na znale�� w wekorze kategoria +1 jest dlatego by zacz�� od 1 
                // bo je�li by tego nie by�o to zaczyna�o by si� liczniee od 0 oraz sprawdzenie czy nie jest wpisana warto�� 0
                // je�li by by�� to jest spoza zakresu gdy� zaczynamy jak pisa�em wcze�niej od 1
                if (ZmianaTypuNaInt(wybor_poz) < Kategoria_wybrana.size() + 1 && ZmianaTypuNaInt(wybor_poz) != 0) {

                    // zapisanie danych wybranych przez u�ytkownika do struktury i p�niej do wektora
                    pozycja_zam.id_przedm = Kategoria_wybrana[ZmianaTypuNaInt(wybor_poz) - 1].id;
                    pozycja_zam.nazwa_przedm = Kategoria_wybrana[ZmianaTypuNaInt(wybor_poz) - 1].nazwa;
                    pozycja_zam.cena_przedm = Kategoria_wybrana[ZmianaTypuNaInt(wybor_poz) - 1].cena;
                    Zam�wienie.push_back(pozycja_zam);
                }
            }

            // sprawdzenie czy wpisana warto�� to 0 je�li tak to wywo�aj funkcj� kt�ra wy�wietla menu 
            // oraz po wybraniu kategorii w funkcji WyswietlenieKategorii
            // przechodzi do wywo�ania samej siebie by zn�w pozwoli� u�ytkownikowi na dopisanie czego� do zam�wienia
            // po prostu wykonuje si� jeszcze raz 
            if (ZmianaTypuNaInt(wybor_poz) == 0) {
                /*for (size_t j = 0; j < Zam�wienie.size(); j++)
                {
                    std::cout << j + 1 << " " << Zam�wienie[j].nazwa_przedm << "          " << Zam�wienie[j].cena_przedm << "\n";
                }*/
                WyswietlenieKategorii(ListaPozycji, Kategorie);
                TworzenieZamowienia(ListaPozycji, Kategorie, Kategoria_wybrana, Zam�wienie, argc, argv);
            }
        }
        else {
            std::cout << "B��dna kategoria";
        }
    }
}
