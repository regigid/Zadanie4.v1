#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#pragma warning(disable : 4996)

using namespace std;

fstream logPlik;

void otworzL(string plikNazwa)
{
    logPlik.open(plikNazwa.c_str(), ios_base::app);
    if (!logPlik.good() == true)
    {
        cout << " BLAD! Nie mozna otworzyc pliku z logami programu." << endl;
    }
    zapiszL("Pliki z logami zostaly otwarte pomyslnie.");
}

void zamknijL(void)
{
    zapiszL("Zamknieto plik z logami.");
    logPlik.close();
}

void utworzPlik(const string nazwaPliku, const int licznik, const char wartosci)
{
    srand(time(NULL));
    ifstream mojPlik;

    const char innyZnak = 0x35;
    int lM[10] = {};
    bool kk = false;
    int temp = {};
    int k = 0;

    mojPlik.open(nazwaPliku);
    if (mojPlik)
    {
        zapiszL("Plik " + nazwaPliku + " juz istnieje.\n");
    }
    else {

        ofstream plik(nazwaPliku);

        if (nazwaPliku == "plik4.bin")
        {
            for (size_t i = 0; i < 10; i++)
            {
                do
                {
                    temp = rand() % licznik + 1;
                    for (size_t j = 0; j < 10; j++)
                    {
                        if (temp == lM[j]) {
                            kk = true;
                        }
                        else kk = false;
                    }

                } while (kk);
                lM[i] = temp;
            }
            sort(lM, lM + 10);

            for (size_t i = 0; i < 10; i++)
            {
                cout << lM[i] << ", ";
            }

            for (size_t i = 0; i < 11; i++)
            {
                if (i < 10) {
                    for (k; k < lM[i]; k++)
                    {
                        plik << wartosci;

                    }

                    plik << innyZnak;

                    k++;
                }
                else {
                    for (k; k < licznik; k++)
                    {
                        plik << wartosci;
                    }
                }
            }
        }
        else
        {

            for (size_t i = 0; i < licznik; i++)
            {
                plik << wartosci;
            }
        }

        string log = "GOTOWE: " + nazwaPliku + "\n";

        zapiszL(log);
        system("cls");

    }

}


struct wynikiBER
{
    clock_t czas1;
    clock_t czas2;
    float BER;
    double bledy;
    double ilosc;
};


uint8_t hammingDistance(uint8_t n1, uint8_t n2)
{
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}

wynikiBER oblicz(string sciezka1, string sciezka2)
{
    fstream f1, f2;
    wynikiBER wynik;

    wynik.czas1 = 0;
    wynik.czas2 = 0;
    wynik.BER = 0;
    wynik.bledy = 0;
    wynik.ilosc = 0;

    f1.open(sciezka1.c_str(), ios::binary | ios::in);
    f2.open(sciezka2.c_str(), ios::binary | ios::in);
    char a = 0x00;
    char b = 0x00;
    wynik.czas1 = clock();

    while (!f1.eof())
    {
        f1 >> a;
        f2 >> b;
        if (!f1.eof())
        {
            wynik.bledy += hammingDistance(a, b);
            wynik.ilosc += 8;
        }
    }

    wynik.BER = (float)wynik.bledy / wynik.ilosc;
    wynik.czas2 = clock();

    return wynik;
}


void drukowanieWynikow(wynikiBER wynik)
{
    stringstream wiad;
    wiad << "Program uzyskal nastepujace wyniki obliczen: " << endl;
    wiad << "Bit Error Rate: " << wynik.BER << endl;
    wiad << "Ilosc bitow: " << wynik.ilosc << endl;
    wiad << "Ilosc bledow: " << wynik.bledy << endl;
    wiad << "Czas obliczen: " << ((float)wynik.czas2 - wynik.czas1) / CLOCKS_PER_SEC << " sec " << endl;
    zapiszL(wiad.str());
}

int main(int argc, char* argv[])
{
    string sciezka1;
    string sciezka2;
    wynikiBER wynik;

    otworzL("log.txt");

    if (argc != 3)
    {
        char wybor;
        while (true)
        {
            cout << " Wybierz 1-0: " << endl << endl
                << " 1: Oblicz BER dla swoich plikow podajac ich sciezki." << endl
                << " 2: Wykonaj test1 z zadania IV " << endl
                << " 3: Wykonaj test2 z zadania IV " << endl
                << " 4: Wykonaj test3 z zadania IV " << endl
                << " 0: Wyjscie " << endl << endl;

            wybor = _getch();

            switch (wybor)
            {
            case '1':
            {
                cout << " Podaj sciezke do pierwszego pliku: ";
                cin >> sciezka1;
                cout << " Podaj sciezke do drugiego pliku: ";
                cin >> sciezka2;

                zapiszL("Obliczanie danych dla plikow.");
                wynik = oblicz(sciezka1, sciezka2);
                drukowanieWynikow(wynik);
            }
            break;

            case '2':
            {

                utworzPlik("case1_plik1.bin", 100, 0x55);
                utworzPlik("case1_plik2.bin", 100, 0x55);
                zapiszL("Obliczanie danych dla plikow.");
                wynik = oblicz("case_plik1.bin", "case1_plik2.bin");
                drukowanieWynikow(wynik);
            }
            break;

            case '3':
            {

                utworzPlik("case2_plik3.bin", 100, 0x55);
                utworzPlik("case2_plik4.bin", 100, 0x55);
                zapiszL("Obliczanie danych dla plikow.");
                wynik = oblicz("case2_plik3.bin", "case2_plik4.bin");
                drukowanieWynikow(wynik);
            }
            break;

            case '4':
            {

                utworzPlik("case3_plik5.bin", 419430400, 0x55);
                utworzPlik("case3_plik6.bin", 419430400, 0x50);
                zapiszL("Obliczanie danych.");
                wynik = oblicz("case3_plik5.bin", "case3_plik6.bin");
                drukowanieWynikow(wynik);
            }
            break;

            case '0':
                zamknijL();
                exit(0);
                break;

            default: cout << "Wybor nieprawidlowy." << endl;
            }
            cout << endl << endl;
            cout << "Wcisnij dowolny klawisz, by powrocic do menu glownego" << endl;
            _getch();
            system("cls");
        }
    }
    else
    {
        sciezka1 = argv[1];
        sciezka2 = argv[2];

        zapiszL("Obliczanie danych dla plikow.");
        wynik = oblicz(sciezka1, sciezka2);
        drukowanieWynikow(wynik);
        zamknijL();
        return 0;
    }



}

void zapiszL(string msg)
{
    string t;
    time_t currentTime = time(NULL);
    string txttime = (string)asctime(localtime(&currentTime));
    txttime = txttime.substr(0, txttime.length() - 1);
    t = (string)"T: " + txttime + " M: " + msg + "\n";
    logPlik << t.c_str();
    logPlik.flush();
    cout << t.c_str();
    cout.flush();
}
