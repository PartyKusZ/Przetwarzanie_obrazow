#include<stdio.h>
#include<string.h>

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define BLAD 1  
#define BRAK_PLIKU 2  
void zeruj_opcje(t_opcje *opcje);
int czytaj_opcje(int argc, char *argv[], t_opcje *opcje);
