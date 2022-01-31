#include<stdio.h>
#include<stdlib.h>
#include"asercja.h"

/******************************************************************************************/
/*  Funcja asercja obsługuje błędy bloku wczytywania argumrntów wywołania progrmau.       */
/*  Zdecydowałem się na takie rozwiązanie z tego względu, że umieszczenie wszystkich      */
/*  informacji dotyczących sposobu wywoływania programu w module opcje.c znacząco         */
/*  zmniejszyło by czytelność i przejrzustość kodu. Tutaj znajduję się dokładny opis      */
/*  sposobu wywołania programu z danymi parametrami. Informacje o innch błędach zostały   */
/*  umiesczone w odpowiednich dla nich modułach, ponieważ nie wplywają na czytelność kodu */
/******************************************************************************************/

void asercja(int a){
    switch(a){
        case 0:
        break;
        case 1:
        fprintf(stderr,"Bledne wywolanie programu\n");
        fprintf(stderr,"-i <nazwa_pliku> nazwa pliku do wczytania (jeśli zamiast nazwy podany będzie znak '-' to zamiast z pliku obraz powinien być wczytywany ze standardowego wejścia)\n");
        fprintf(stderr,"-o <nazwa_pliku> nazwa pliku do zapisu (jeśli zamiast nazwy podany będzie znak '-' to zamiast do pliku obraz powinien być wypisany na standardowym wyjściu)\n");
        fprintf(stderr,"-d obraz po przetworzeniu powinien zostać wyświetlony\n");
        fprintf(stderr,"-n negatyw\n");
        fprintf(stderr,"-p <próg> progowanie z progiem o zadanej wartości procentowej\n");
        fprintf(stderr,"-k konturowanie\n");
        fprintf(stderr,"-l odbicie lustrzane\n");
        fprintf(stderr,"-r konwersja obrazu PGM na PPM ");
        fprintf(stderr,"kolejnosc podania argumentow wywolania jest dowolna\n ");
        exit(EXIT_FAILURE);
        break;
        case 2:
        fprintf(stderr,"Nie udalo sie otworzyc pliku\n");
        exit(EXIT_FAILURE);
        break;

    }
}