/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2020 KCiR  */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/
#include<stdio.h>
#include<string.h>
#include"struktury.h"
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define BLAD 1                   // błąd wywołania progrmau
#define BRAK_PLIKU 2             // nie udało się otworzyć pliku

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wyb�r, do tego ustawia na 1 pola dla opcji, ktore  */
/*	poprawnie wystapily w linii wywolania programu,                     */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;         */
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne                */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                         */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

void zeruj_opcje(t_opcje *opcje){           // funkcja opuszczająca wszystkie flagi przechowywujące informacje o tym które filtry zastosować i ustawia domyślne uchwyty do plików na NULL
    opcje -> plik_we = NULL;
    opcje -> plik_wy = NULL;
    opcje -> negatyw = 0;
    opcje -> progowanie = 0;
    opcje -> konturowanie = 0;
    opcje -> wyswietlenie =0 ;
    opcje -> w_prog = 0;
    opcje -> lustro = 0;
    opcje -> konwersja = 0;
    
}
int czytaj_opcje(int argc, char *argv[], t_opcje *opcje){
    char *nazwa_pliku_we, *nazwa_pliku_wy;
    int prog;
    zeruj_opcje(opcje);
    opcje -> plik_wy = stdout;        // jeśli nie podano opcji -o

    for (int i = 1; i < argc; i++){
        if(argv[i][0] != '-')
            return BLAD;
        switch(argv[i][1]){   
            case 'i' :               // wczytanie nazwy pliku 
                if(++i < argc){      // przejśnie za przełącznik -i w celu odczytania nazwy pliku
                    nazwa_pliku_we = argv[i];     // odczytanie nazwy pliku 
                    if(strcmp(nazwa_pliku_we, "-") == 0)    // jeśli nazwa pliku jest "-" to wczyatj nazwe ze standowego wejścia 
                        opcje -> plik_we = stdin;
                    else
                        opcje -> plik_we = fopen(nazwa_pliku_we, "r"); // jeśli nie to otwórz plik taki jak podany za -i     
                }
                else
                    return BLAD;
                break;
            case 'o':               // zapisz pliku
            if(++i < argc){
                nazwa_pliku_wy = argv[i];
                opcje->nazwa = argv[i];
                if(strcmp(nazwa_pliku_wy, "-") == 0)
                    opcje -> plik_wy = stdout;
                else
                    opcje -> plik_wy = fopen(nazwa_pliku_wy, "w");
            }
            else
                return BLAD;
            break;
            case 'p':              // zapalenie flagi progowanie i wczytanie wartości progu 
            if(++i < argc){
                if(sscanf(argv[i], "%d", &prog) == 1){
                    opcje -> progowanie = 1;
                    opcje -> w_prog = prog;
                }
                else
                    return BLAD;

            }
            else
                return BLAD;
            break;   

            case 'n':             // podniesienie  flagi negatywowania 
            opcje -> negatyw = 1;
            break;

            case 'k':             // podniesienie flagi konturowania 
            opcje -> konturowanie = 1;
            break;

            case 'd':             // podniesienie  flagi wyświetlania 
            opcje -> wyswietlenie = 1;
            break;

            case 'l':             // podniesnienie flagi odbicia lustrzanego 
            opcje -> lustro = 1;
            break;

            case 'r':
            opcje -> konwersja = 1;
            break;

            default :             // błędny argument wywołania, szczególy w module asercja.c
            return BLAD;
            break;
        }      
    }
    if(opcje -> plik_we != NULL)
        return W_OK;
    else
        return BRAK_PLIKU;       // nie udało się otworzyc pliku szczególy w module asercja.c
        return BLAD;
    opcje->nazwa = nazwa_pliku_wy; 
    printf("%s", opcje->nazwa);
       

}