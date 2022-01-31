#ifndef STRUKTURY_H
#define STRUKTURY_H

typedef struct {             // strukrura zawierająca informacje o obrazie
int wym_x, wym_y, odcieni;   // odpowiednio: wymiar x, wymiar y, głębia odcieni
int *piksele;                // wskaźnik na tablcie przechowywującą obraz 
int p2;
int p3;                 // z jakim typem obrazy mamy do czynienia 
} t_obraz;


typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,konturowanie,lustro,wyswietlenie,konwersja;      /* opcje */ 
  int w_prog;              /* wartosc progu dla opcji progowanie */ 
  char *nazwa;             // zmienna przechowywyująca nazwe pliku dla dla funkcji wyswietl
} t_opcje;
#endif