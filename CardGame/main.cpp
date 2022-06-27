#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

#define DLA_CZLOWIEKA 1

void wyswietlanie(int karta, int liczba_kart) {
    if (karta < liczba_kart / 4)
        cout << "S|";
    else if (karta < liczba_kart / 2)
        cout << "K|";
    else if (karta < 3 * liczba_kart / 4)
        cout << "T|";
    else
        cout << "P|";

    switch (karta % (liczba_kart / 4)) {
    case 0:
        cout << "A  ";
        break;
    case 1:
        cout << "K  ";
        break;
    case 2:
        cout << "Q  ";
        break;
    case 3:
        cout << "J  ";
        break;
    case 4:
        cout << "10 ";
        break;
    case 5:
        cout << "9  ";
        break;
    case 6:
        cout << "8  ";
        break;
    case 7:
        cout << "7  ";
        break;
    case 8:
        cout << "6  ";
        break;
    case 9:
        cout << "5  ";
        break;
    case 10:
        cout << "4  ";
        break;
    case 11:
        cout << "3  ";
        break;
    case 12:
        cout << "2  ";
        break;

    }
}
void wyswietlanie_reki(int* gracz1, int* gracz2, int liczba_kart, int liczba_kart_gracza1) {
    cout << endl;
    if (liczba_kart_gracza1 == 0)
        cout << "Pusta reka";
    else {
        for (int i = 0; i < liczba_kart_gracza1; i++)
            wyswietlanie(gracz1[i], liczba_kart);
        cout << endl;

    }
    if (liczba_kart - liczba_kart_gracza1 == 0)
        cout << "Pusta reka";
    else {
        for (int i = 0; i < liczba_kart - liczba_kart_gracza1; i++)
            wyswietlanie(gracz2[i], liczba_kart);
        cout << endl;

    }
    cout << endl;
}

void losowe_karty(int ile_kart, int* karty_do_potasowania) {
    int pozycja;
    int* deck_kart = new int[ile_kart];
    for (int i = 0; i < ile_kart; i++)
        deck_kart[i] = karty_do_potasowania[i];
    for (int i = 0; i < ile_kart; i++) {
        pozycja = rand() % (ile_kart - i);
        karty_do_potasowania[i] = deck_kart[pozycja];
        deck_kart[pozycja] = deck_kart[ile_kart - i - 1];

    }
    delete[] deck_kart;
}

void przesuniecie(int* gracz, int liczba_kart_gracza, int o_ile) {
    for (int i = 0; i < liczba_kart_gracza; i++) {
        if (i < liczba_kart_gracza - o_ile)
            gracz[i] = gracz[o_ile + i];
        else
            gracz[i] = -1;

    }
}
void zbior_kart(int* zwyciezca, int* looser, int liczba_kart, int liczba_kart_zwyciezcy, int bitwy, int gracz, int* wynik) {
    int a = 0;
    if (bitwy % 2 == 1) {
        a = 1;

    }
    int* schowek = new int[(bitwy + 1 + a) * 2];
    for (int i = 0; i < (bitwy + 1 + a) * 2; i++) {
        if (i < bitwy + 1 + a)
            schowek[i] = zwyciezca[i];
        else {
            schowek[i] = looser[i - (bitwy + 1 + a)];

        }

    }
    if (a == 1) {
        schowek[bitwy + 1] = -1;

    }

#ifdef DLA_CZLOWIEKA
    for (int i = 0; i < (bitwy + 1 + a) * 2; i++) {
        if (gracz == 1) {
            if (schowek[i] != -1) {
                if (i % 2 == 0 && i < bitwy + 1 + a)
                    wyswietlanie(schowek[i], liczba_kart);
                else if (i % 2 == 1 && i >= bitwy + 1 + a)
                    wyswietlanie(schowek[i], liczba_kart);
                else
                    cout << "###  ";

            }

        }
        else {
            if (i < bitwy + 1 + a) {
                if (schowek[i + bitwy + 1 + a] != -1)
                    if (i % 2 == 0)
                        wyswietlanie(schowek[i + bitwy + 1 + a], liczba_kart);
                    else
                        cout << "###  ";

            }
            else {
                if (schowek[i - bitwy - 1 - a] != -1)
                    if (i % 2 == 1)
                        wyswietlanie(schowek[i - bitwy - 1 - a], liczba_kart);
                    else
                        cout << "###  ";

            }

        }

        if (i == bitwy + a || i == (bitwy + 1 + a) * 2 - 1)
            cout << endl;

    }
#endif

    if (wynik[4] != 0)
        losowe_karty((bitwy + 1 + a) * 2, schowek);

    przesuniecie(zwyciezca, liczba_kart_zwyciezcy, bitwy + 1);
    przesuniecie(looser, liczba_kart - liczba_kart_zwyciezcy, bitwy + 1);
    int karty = 0;
    for (int i = 0; i < (bitwy + 1) * 2; i++) {
        if (schowek[i] != -1) {
            zwyciezca[liczba_kart_zwyciezcy - (bitwy + 1) + karty] = schowek[i];
            karty++;

        }

    }
    wynik[3] += karty / 2;
    delete[] schowek;
}
void zwycieztwo(int nr_gracza, int* wynik, int liczba_kart, int* liczba_kart_gracza1, int* gracz1, int* gracz2, int bitwy) {
    if (*liczba_kart_gracza1 != 0 && *liczba_kart_gracza1 != liczba_kart) {
        if (nr_gracza == 11) {
            if ((liczba_kart - *liczba_kart_gracza1 - 1) % 2 == 1)
                zbior_kart(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, *liczba_kart_gracza1, bitwy, 1, wynik);
            else
                zbior_kart(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, *liczba_kart_gracza1, bitwy - 1, 1, wynik);
#ifdef DLA_CZLOWIEKA
            wyswietlanie_reki(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, liczba_kart);
#endif

        }
        else if (nr_gracza == 12) {
            if ((*liczba_kart_gracza1 - 1) % 2 == 1)
                zbior_kart(gracz2 - bitwy, gracz1 - bitwy, liczba_kart, liczba_kart - *liczba_kart_gracza1, bitwy, 2, wynik);
            else
                zbior_kart(gracz2 - bitwy, gracz1 - bitwy, liczba_kart, liczba_kart - *liczba_kart_gracza1, bitwy - 1, 2, wynik);
#ifdef DLA_CZLOWIEKA
            wyswietlanie_reki(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, 0);
#endif

        }
        else if (nr_gracza == 10)
            zbior_kart(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, *liczba_kart_gracza1, bitwy, 1, wynik);
        else {
            zbior_kart(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, *liczba_kart_gracza1, bitwy, 1, wynik);
            cout << endl;

        }

    }

#ifdef DLA_CZLOWIEKA
    if (nr_gracza % 10 != 0) {
        cout << "Gracz " << nr_gracza % 10 << " wins";

    }
    else {
        cout << endl << "Remis";

    }
    cout << endl << endl;
#endif

    wynik[nr_gracza % 10] += 1;
    *liczba_kart_gracza1 = -1;
}
void bitwa(int* gracz1, int* gracz2, int liczba_kart, int* liczba_kart_gracza1, int bitwy, int* wynik) {
    if (gracz1[0] % (liczba_kart / 4) < gracz2[0] % (liczba_kart / 4)) {
        zbior_kart(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, *liczba_kart_gracza1, bitwy, 1, wynik);
        *liczba_kart_gracza1 += bitwy + 1;

    }
    else if (gracz1[0] % (liczba_kart / 4) > gracz2[0] % (liczba_kart / 4)) {
        zbior_kart(gracz2 - bitwy, gracz1 - bitwy, liczba_kart, liczba_kart - *liczba_kart_gracza1, bitwy, 2, wynik);
        *liczba_kart_gracza1 -= bitwy + 1;

    }
#ifdef DLA_CZLOWIEKA
    wyswietlanie_reki(gracz1 - bitwy, gracz2 - bitwy, liczba_kart, *liczba_kart_gracza1);
#endif  
}
void zamien_kolejnosc2_kart(int* gracz) {
    int schowek = gracz[0];
    gracz[0] = gracz[1];
    gracz[1] = schowek;
}
void wojna_C_madra(int* gracz1, int* gracz2, int liczba_kart, char* tryb_gry, int a) {
    if (tryb_gry[a] == 'l') {
        losowe_karty(2, gracz2);

    }
    else if (tryb_gry[a] == 'p') {
        if (gracz1[0] % (liczba_kart / 4) == gracz2[0] % (liczba_kart / 4))
            zamien_kolejnosc2_kart(gracz2);
        else if (gracz1[0] % (liczba_kart / 4) > gracz2[0] % (liczba_kart / 4) && gracz1[0] % (liczba_kart / 4) > gracz2[1] % (liczba_kart / 4))
            if (gracz2[0] % (liczba_kart / 4) < gracz2[1] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);


    }
    else if (tryb_gry[a] == 'w') {
        if (gracz1[0] % (liczba_kart / 4) == gracz2[1] % (liczba_kart / 4))
            zamien_kolejnosc2_kart(gracz2);
        else if (gracz1[0] % (liczba_kart / 4) > gracz2[0] % (liczba_kart / 4) && gracz1[0] % (liczba_kart / 4) > gracz2[1] % (liczba_kart / 4)) {
            if (gracz2[0] % (liczba_kart / 4) < gracz2[1] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);

        }
        else if (gracz1[0] % (liczba_kart / 4) > gracz2[1] % (liczba_kart / 4))
            zamien_kolejnosc2_kart(gracz2);
        else if ((gracz1[0] % (liczba_kart / 4) < gracz2[0] % (liczba_kart / 4) && gracz1[0] % (liczba_kart / 4) < gracz2[1] % (liczba_kart / 4)))
            if (gracz2[0] % (liczba_kart / 4) < gracz2[1] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);

    }
    else if (tryb_gry[a] == 't') {
        if (gracz1[0] % (liczba_kart / 4) < (liczba_kart + 4) / 8) {
            if ((gracz1[0] % (liczba_kart / 4) < gracz2[0] % (liczba_kart / 4) && gracz1[0] % (liczba_kart / 4) < gracz2[1] % (liczba_kart / 4)) || (gracz1[0] % (liczba_kart / 4) > gracz2[0] % (liczba_kart / 4) && gracz1[0] % (liczba_kart / 4) > gracz2[1] % (liczba_kart / 4))) {
                if (gracz2[0] % (liczba_kart / 4) < gracz2[1] % (liczba_kart / 4))
                    zamien_kolejnosc2_kart(gracz2);

            }
            else if (gracz1[0] % (liczba_kart / 4) > gracz2[1] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);
            else if (gracz1[0] % (liczba_kart / 4) == gracz2[1] % (liczba_kart / 4) && gracz1[2] % (liczba_kart / 4) > gracz2[2] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);
            else if (gracz1[0] % (liczba_kart / 4) == gracz2[1] % (liczba_kart / 4) && gracz1[2] % (liczba_kart / 4) == gracz2[2] % (liczba_kart / 4) && gracz1[4] % (liczba_kart / 4) > gracz2[4] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);
            else if (gracz1[0] % (liczba_kart / 4) == gracz2[0] % (liczba_kart / 4) && gracz1[2] % (liczba_kart / 4) < gracz2[2] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);

        }
        else
            if (gracz2[0] % (liczba_kart / 4) < gracz2[1] % (liczba_kart / 4))
                zamien_kolejnosc2_kart(gracz2);

    }
    else {
        cout << gracz1[0] << endl << gracz2[0] << " | " << gracz2[1] << endl;
        int ch;
        if ((ch = _getch()) == 'd') {
            zamien_kolejnosc2_kart(gracz2);

        }
        cout << endl << endl;

    }
}
void wojna(int* gracz1, int* gracz2, int liczba_kart, int* liczba_kart_gracza1, int bitwy, int* wynik, char* tryb_gry) {
    if (bitwy == 0 && tryb_gry[0] == 'C') {
        int a = wynik[4];
        if (a == 2 && gracz2[1] != -1) {
            wojna_C_madra(gracz1, gracz2, liczba_kart, tryb_gry, a);
            wynik[4] -= 1;

        }
        else if (a == 1 && gracz1[1] != -1) {
            wojna_C_madra(gracz2, gracz1, liczba_kart, tryb_gry, a);
            wynik[4] += 1;

        }

    }


    if (bitwy >= 1 && tryb_gry[0] == 'B') {
        if (*liczba_kart_gracza1 - bitwy - 1 < 0 && liczba_kart - *liczba_kart_gracza1 - bitwy - 1 < 0) {
            if (*liczba_kart_gracza1 > liczba_kart - *liczba_kart_gracza1) {
                gracz2[-1] = gracz1[-1];
                gracz2[0] = gracz1[0];
                przesuniecie(gracz1 - 1, liczba_kart - *liczba_kart_gracza1 - bitwy + 1, 2);
                *liczba_kart_gracza1 -= 2;
                zwycieztwo(1, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

            }
            else if (*liczba_kart_gracza1 < liczba_kart - *liczba_kart_gracza1) {
                gracz1[-1] = gracz2[-1];
                gracz1[0] = gracz2[0];
                przesuniecie(gracz2 - 1, liczba_kart - *liczba_kart_gracza1 - bitwy + 1, 2);
                *liczba_kart_gracza1 += 2;
                zwycieztwo(2, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

            }
            else {
                zwycieztwo(0, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

            }

        }
        else if (*liczba_kart_gracza1 - bitwy - 1 < 0) {
            if (*liczba_kart_gracza1 - bitwy - 1 == -1 && liczba_kart - *liczba_kart_gracza1 - bitwy - 1 >= 1) {
                gracz1[0] = gracz2[0];
                przesuniecie(gracz2, liczba_kart - *liczba_kart_gracza1 - bitwy, 1);
                *liczba_kart_gracza1 += 1;

                if (gracz1[0] % (liczba_kart / 4) != gracz2[0] % (liczba_kart / 4))
                    bitwa(gracz1, gracz2, liczba_kart, liczba_kart_gracza1, bitwy, wynik);
                else
                    zwycieztwo(2, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

            }
            else if (*liczba_kart_gracza1 - bitwy - 1 == -2 && liczba_kart - *liczba_kart_gracza1 - bitwy - 1 >= 2) {
                gracz1[-1] = gracz2[-1];
                gracz1[0] = gracz2[0];
                przesuniecie(gracz2 - 1, liczba_kart - *liczba_kart_gracza1 - bitwy + 1, 2);
                *liczba_kart_gracza1 += 2;

                if (gracz1[0] % (liczba_kart / 4) != gracz2[0] % (liczba_kart / 4))
                    bitwa(gracz1, gracz2, liczba_kart, liczba_kart_gracza1, bitwy, wynik);
                else
                    zwycieztwo(2, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

            }
            else
                zwycieztwo(2, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

        }
        else if (liczba_kart - *liczba_kart_gracza1 - bitwy - 1 < 0) {
            if (liczba_kart - *liczba_kart_gracza1 - bitwy - 1 == -1 && *liczba_kart_gracza1 - bitwy - 1 >= 1) {
                gracz2[0] = gracz1[0];
                przesuniecie(gracz1, *liczba_kart_gracza1 - bitwy, 1);
                *liczba_kart_gracza1 -= 1;

                if (gracz1[0] % (liczba_kart / 4) != gracz2[0] % (liczba_kart / 4))
                    bitwa(gracz1, gracz2, liczba_kart, liczba_kart_gracza1, bitwy, wynik);
                else
                    zwycieztwo(1, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

            }
            else if (liczba_kart - *liczba_kart_gracza1 - bitwy - 1 == -2 && *liczba_kart_gracza1 - bitwy - 1 >= 2) {
                gracz2[-1] = gracz1[-1];
                gracz2[0] = gracz1[0];
                przesuniecie(gracz1 - 1, *liczba_kart_gracza1 - bitwy + 1, 2);
                *liczba_kart_gracza1 -= 2;

                if (gracz1[0] % (liczba_kart / 4) != gracz2[0] % (liczba_kart / 4))
                    bitwa(gracz1, gracz2, liczba_kart, liczba_kart_gracza1, bitwy, wynik);
                else
                    zwycieztwo(1, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

            }
            else
                zwycieztwo(1, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

        }
        else {
            if (gracz1[0] % (liczba_kart / 4) != gracz2[0] % (liczba_kart / 4))
                bitwa(gracz1, gracz2, liczba_kart, liczba_kart_gracza1, bitwy, wynik);
            else
                wojna(gracz1 + 2, gracz2 + 2, liczba_kart, liczba_kart_gracza1, bitwy + 2, wynik, tryb_gry);

        }

    }
    else {
        if (*liczba_kart_gracza1 - bitwy - 1 < 0 && liczba_kart - *liczba_kart_gracza1 - bitwy - 1 < 0) {
            zwycieztwo(10, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

        }
        else if (*liczba_kart_gracza1 - bitwy - 1 < 0) {
            zwycieztwo(12, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

        }
        else if (liczba_kart - *liczba_kart_gracza1 - bitwy - 1 < 0) {
            zwycieztwo(11, wynik, liczba_kart, liczba_kart_gracza1, gracz1, gracz2, bitwy);

        }
        else {
            if (gracz1[0] % (liczba_kart / 4) != gracz2[0] % (liczba_kart / 4))
                bitwa(gracz1, gracz2, liczba_kart, liczba_kart_gracza1, bitwy, wynik);
            else
                wojna(gracz1 + 2, gracz2 + 2, liczba_kart, liczba_kart_gracza1, bitwy + 2, wynik, tryb_gry);

        }

    }
}
int wartosc_reki_miejsca(int liczba_kart, int liczba_kart_start) {
    if (liczba_kart > liczba_kart_start) {
        return liczba_kart + wartosc_reki_miejsca(liczba_kart - 4, liczba_kart_start);

    }
}


int main() {
    srand((unsigned int)time(NULL));
    char tryb_gry[3];
    int liczba_kart, liczba_testow;
    FILE* wartosc_reki;
    wartosc_reki = fopen("Wojna/wartosc_reki.txt", "w");
    FILE* liczba_ruchow;
    liczba_ruchow = fopen("Wojna/liczba_ruchow.txt", "w");
    

    if (liczba_ruchow == NULL || wartosc_reki == NULL) {
        cout << "nie powiodlo sie otwarcie pliku" << endl;
        return 1;
    }


    cout << "Wbierz tryb gry (t - automatyczne, cokolwiek innego - reczne):";
    cin >> tryb_gry[0];
    int testy = 1;
    if (tryb_gry[0] == 't')
        testy = 18;
    for (int k = 0; k < testy; k++) {
        if (testy != 1) {
            if (k < testy / 2) {
                tryb_gry[0] = 'A';
                liczba_kart = 52 - 4 * k;

            }
            else {
                tryb_gry[0] = 'B';
                liczba_kart = 52 - 4 * (k - testy / 2);

            }
            liczba_testow = 10000;

        }
        else {
            cout << "Wpisz liczbe kart w talii:";
            cin >> liczba_kart;
            cout << "Wpisz liczbe testow ktore chcesz przeprowadzic na tych kartach:";
            cin >> liczba_testow;
        }
        int liczba_testow_poczatkowa = liczba_testow;
        int wartosc_reki_pamiec = wartosc_reki_miejsca(liczba_kart, liczba_kart / 2);
        int* wartosc_reki_zwycieztwa = new int[wartosc_reki_pamiec];
        for (int i = 0; i < wartosc_reki_pamiec; i++)
            wartosc_reki_zwycieztwa[i] = 0;
        int wartosc_reki_max = wartosc_reki_miejsca(liczba_kart, 0);

        int* reka_gracza1 = new int[liczba_kart];
        int* reka_gracza2 = new int[liczba_kart];
        int wynik[5] = {
        };

        if (tryb_gry[0] == 'C') {
            cin >> tryb_gry[1] >> tryb_gry[2];
            wynik[4] = 2;

        }


        int liczba_ruchow_max = 0;
        int liczba_ruchow_min = 1000000;

        for (int i = 0; i < liczba_testow; i++) {

            int liczba_kart_gracza1 = liczba_kart / 2;
            int* kolejnosc_kart = new int[liczba_kart];
            for (int i = 0; i < liczba_kart; i++)
                kolejnosc_kart[i] = i;
            losowe_karty(liczba_kart, kolejnosc_kart);
            for (int i = 0; i < liczba_kart; i++) {
                if (i < liczba_kart / 2) {
                    reka_gracza1[i] = kolejnosc_kart[i];
                    reka_gracza1[i + liczba_kart / 2] = -1;

                }
                else {
                    reka_gracza2[i - liczba_kart / 2] = kolejnosc_kart[i];
                    reka_gracza2[i] = -1;

                }

            }
            delete[] kolejnosc_kart;

            int wartosc_reki = 0;
            for (int i = 0; i < liczba_kart_gracza1; i++) {
                wartosc_reki += (liczba_kart / 4 - (reka_gracza1[i] % (liczba_kart / 4)));

            }
            int wartosc_reki_wynik = wynik[1];

            int x = wynik[3];

#ifdef DLA_CZLOWIEKA
            wyswietlanie_reki(reka_gracza1, reka_gracza2, liczba_kart, liczba_kart_gracza1);
#endif

            while (liczba_kart_gracza1 != -1 && wynik[3] - x < 100000)
                wojna(reka_gracza1, reka_gracza2, liczba_kart, &liczba_kart_gracza1, 0, wynik, tryb_gry);
            if (wynik[3] - x >= 100000) {
                wynik[3] = x;
                liczba_testow++;

            }
            else {
                if (liczba_ruchow_max < wynik[3] - x)
                    liczba_ruchow_max = wynik[3] - x;
                if (liczba_ruchow_min > wynik[3] - x)
                    liczba_ruchow_min = wynik[3] - x;


            }
            if (wynik[1] - wartosc_reki_wynik != 0)
                wartosc_reki_zwycieztwa[wartosc_reki] += 1;
            else
                wartosc_reki_zwycieztwa[wartosc_reki_max - wartosc_reki] += 1;


        }
        if (testy != 1) {
            fprintf(liczba_ruchow, "%d \n%d     %d \n", (wynik[3] / liczba_testow_poczatkowa), liczba_ruchow_min, liczba_ruchow_max);
            for (int i = 0; i < wartosc_reki_pamiec; i++)
                fprintf(wartosc_reki, "%d \n", wartosc_reki_zwycieztwa[i]);
            fprintf(wartosc_reki, " \n\n\n\n\n\n");

        }
        else
            cout << "Wyniki:" << endl << "Remis: " << wynik[0] << endl << "Gracz 1 wins: " << wynik[1] << endl << "Gracz 2 wins: " << wynik[2] << endl << "Liczba ruchow: " << (float)(wynik[3] / liczba_testow_poczatkowa) << endl << "Zapetlenia: " << liczba_testow - liczba_testow_poczatkowa << endl;
        delete[] wartosc_reki_zwycieztwa;
        delete[] reka_gracza1;
        delete[] reka_gracza2;

    }
    fclose(liczba_ruchow);
    fclose(wartosc_reki);
    system("pause");

    return 0;
}