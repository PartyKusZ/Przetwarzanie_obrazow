#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktury.h"
#include"pliki_zapisz_odczyty_wyswietl.h"
#define DL_LINII 1024
/*Funkcja czytaj odczytuje i zapisuje wszystkie informacje o obrazie ("numer magiczny" wymiary i głębie odcieni) i*/
/*alokuje pamięć dla pikseli*/
int czytaj(t_obraz *obraz, t_opcje *opcje){
    char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
    int znak;                /* zmienna pomocnicza do czytania komentarzy */
    int koniec=0;            /* czy napotkano koniec danych w pliku */
    obraz->p2 = 0;
    obraz->p3 = 0;
    
    /* Sprawdzenie "numeru magicznego" - powinien by� P2 lub P3 */
    fgets(buf,DL_LINII,opcje->plik_we)==NULL;      /* Wczytanie pierwszej linii pliku do bufora */
        koniec=1;                /* Nie udalo sie? Koniec danych! */
        if(buf[0] == 'P' && buf[1] == '2' && koniec == 1){

        }
        else{
            if(buf[0] == 'P' && buf[1] == '3' && koniec == 1){

            }
            else{
                
                fprintf(stderr,"Blad: to nie jest obraz PGM\\PPM\n");
                exit(EXIT_FAILURE);
            }
        }
  

    
  
    if(buf[1] == '2')          // określenie z jakim typem obrazów mamy do czyenia
        obraz->p2 = 1;
    if(buf[1] == '3')
        obraz->p3 = 1;
        
        

  /* Pominiecie komentarzy */
    do {
        if ((znak=fgetc(opcje->plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
            if (fgets(buf,DL_LINII,opcje->plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	            koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }   else {
            ungetc(znak,opcje->plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */
                                    
    if (fscanf(opcje->plik_we,"%d %d %d",&(obraz->wym_x),&(obraz->wym_y),&(obraz->odcieni))!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
    
    exit(EXIT_FAILURE);
   
  }
 

  // zaalokowanie dynamiczne pamięci i zapisanie obrazu do pamięci 
    if(obraz->p2 == 1){
        obraz->piksele = (int*)malloc(obraz->wym_x * obraz->wym_y * sizeof(int));      // powołanie do życia tablicy jednowymiarowej szytej na miarę (funkcja malloc jest wspaniałym krawcem :)  ) 
        if(obraz->piksele == NULL){            // jeśli się nie udało przydzielić pamięci to poinformuje i zamknie program
            fprintf(stderr,"Nie udalo sie przydzielic pameci");
             exit(EXIT_FAILURE);
        }
        for (int i = 0; i < obraz->wym_x * obraz->wym_y; i++) // zapisanie obrazu do tablicy 
            fscanf(opcje->plik_we, "%d", &(obraz->piksele[i]));
    }
    else{
        obraz->piksele = (int*) malloc(3 * obraz->wym_x * obraz->wym_y * sizeof(int));   // tutaj dzieje się to samo tylko 3 razy większe (dla ppm oczywiście)
        if(obraz->piksele == NULL){
            fprintf(stderr,"Nie udalo sie przydzielic pameci");
             exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 3 * obraz->wym_x * obraz->wym_y; i++)
            fscanf(opcje->plik_we, "%d", &(obraz->piksele[i]));
    }

    fclose(opcje->plik_we);                             // zmaknięcie pliku wejściowego  
        
}
/*Funkja zapisz zapisuje wszystkie informacje o obrazie i jego piksele po przetworzeniu do nowego pliku*/
void zapisz(t_obraz *obraz, t_opcje *opcje){
    if(obraz->p2 == 1){
        fprintf(opcje->plik_wy, "P2\n");                                   // wpisanie do pliku parametrów obrazu
        fprintf(opcje->plik_wy, "%d\n%d\n%d\n", obraz->wym_x, obraz->wym_y, obraz->odcieni);
        for(int i = 0; i < obraz->wym_x * obraz->wym_y; i++)
            fprintf(opcje->plik_wy, "%d\t", obraz->piksele[i]);            // wpisanie do pliku piskeli
        free(obraz->piksele);                                              // zwolnienie pamieci 
    }
    if(obraz->p3 == 1){                                                    // tutaj to samo tylko że dla ppm
        fprintf(opcje->plik_wy, "P3\n");
        fprintf(opcje->plik_wy, "%d\n%d\n%d\n", obraz->wym_x, obraz->wym_y, obraz->odcieni);
        for(int i = 0; i < 3 * obraz->wym_x * obraz->wym_y; i++)
            fprintf(opcje->plik_wy, "%d\t", obraz->piksele[i]);
        free(obraz->piksele);    
    }
    fclose(opcje->plik_wy);                                                 // zamkcięcie pliku wyjściowego 
    if(opcje->wyswietlenie == 1)                                            // jeśli została podniesiona flaga -d
       wyswietl(opcje);                                                     // to wyświetl owoc swej ciężkiej pracy 
}
/*wyświelta zapisany obraz*/
void wyswietl(t_opcje *opcje) {                                             
 
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,opcje->nazwa);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}