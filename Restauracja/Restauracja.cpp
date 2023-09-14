
#include "Struktury.h"
#include "Funkcje.h"
#include "WeWy.h"


// int argc, char* argv[] oznacza obsługę argumentów wprowadzanych w koncoli 
int main(int argc, char* argv[])
{
    // ustawienie by polskie znaki się wyświetlały w konsoli
    setlocale(LC_CTYPE, "Polish");

    restaurant restracja;
    // wektor do przechowywania każej zawartosći struktury przypisanej w momęcie czytania z pliku 
    // i dospiwania właśnie do tej struktury 
    std::vector<Menu>ListaPozycji;

    // wywołanie funkcji dot. czytania z pliku
    CzytaniePliku("baza.txt", ListaPozycji);

    // wektor do kórego będziemy zapisywać kategorie
    std::vector<std::string>Kategorie;

    // wywołanie funkcji dot. kategorii
    restracja.WyswietlenieKategorii(ListaPozycji, Kategorie);


    // wektor do późniejszej zapisania pozycji 
    std::vector<Menu>Kategoria_wybrana;

    // wektor do zapisania danych dot. zamówienia, co dodał użytkownik do struktury (co wybrał)
    std::vector<Zamowienie>Zamówienie;

    // wywołanie funkcji dot. tworzenia zamówienia
    // przekazujemy tu wszelkie wektory z kótrych później pobieramy dane lub do np. wektora Zamówienia zapisuemy
    // wszystko co wybrał użytkwnik, argc oraz argv są po to by przekazać je do wywołania funkcji ZapisDoPliku
    // która zaś te argc oraz argv przekazuje do funkcji która je wykorzystuje by sprawdzić co wpisałaś w 
    // w argumentach wywołania funkcji i pobiera z tamtąd wartość która okresla nr stolika 
    restracja.TworzenieZamowienia(ListaPozycji, Kategorie, Kategoria_wybrana, Zamówienie, argc, argv);




}

