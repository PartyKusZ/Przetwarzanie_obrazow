#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include"struktury.h"
#include"filtry.h"


/**************************************************/
/*  Tutaj znajdują się funkcje filtrujące obrazy, */
/*  blok ten skontruwany jest w taki sposób, iż   */
/*  funkcja filtruj na podstawie informacji o tym,*/
/*  które flagi są zapalone, wywołuje opdowiednie */
/*  funkcje filtrujące.                           */
/**************************************************/ 




void negatyw(t_obraz *obraz, t_opcje *opcje){
    if(obraz->p2 == 1){
        for(int i = 0; i < obraz->wym_x * obraz->wym_y; i++)      //pętla poruszająca się po  tablicy
        obraz->piksele[i]= obraz->odcieni - obraz->piksele[i];    //dokonanie operacji negatywyowania 
    }
    if(obraz->p3 == 1){
        for(int i = 0; i < 3 * obraz->wym_x * obraz->wym_y; i++)      //pętla poruszająca się po  tablicy
        obraz->piksele[i]= obraz->odcieni - obraz->piksele[i];    //dokonanie operacji negatywyowania
    }
}
void progowanie(t_obraz *obraz, t_opcje *opcje){
    int w ;
    w = obraz->odcieni * (opcje->w_prog / 100.0);        // przeliczenie wartości procentowej na wartość bezwzględną progu
     if(obraz->p2 == 1){
        for(int i = 0; i < obraz->wym_x * obraz->wym_y; i++){     // pętla poruszająca się po tablicy 
            if(obraz->piksele[i] <= w)                            // warunek progowania 
                obraz->piksele[i] = 0;
            else
                obraz->piksele[i] = obraz->odcieni;   
        }     
            
    }
    if(obraz->p3 == 1){
        for(int i = 0; i < 3 * obraz->wym_x * obraz->wym_y; i++){      // pętla poruszająca się po tablicy
              if(obraz->piksele[i] <= w)                               // warunek progowania
                obraz->piksele[i] = 0;
            else
                obraz->piksele[i] = obraz->odcieni;  
        }      
        
    }

}
void odbicie(t_obraz *obraz, t_opcje *opcje){
    
    
     if(obraz->p2 == 1){
         int buf;
         for(int i = 0; i < obraz->wym_y ; i++){           //pętla symulująca poruszanie się po kolumnach  tablicy
             int x = 0;                                    // pomocnicza zmienna pozwalająca na odczytywanie wartości tablicy od tyłu
             for(int j = 0; j < obraz->wym_x / 2 ; j++){   //pętla symulująca poruszanie się po wierszach tablicy
                 buf = obraz->piksele[(i * obraz->wym_x) + j];   // zapis danej wartości do bufora 
                 obraz->piksele[(i * obraz->wym_x) + j] = obraz->piksele[(i * obraz->wym_x) + (obraz->wym_x - 1) - x];  // przepisanie wartości "prawych" do "lewych"
                 obraz->piksele[(i * obraz->wym_x) + (obraz->wym_x - 1) - x] = buf;    // przepisanie wartości "lewych" do "prawych"
                x++;
             }
         }
          
     }
     if(obraz->p3 == 1){
        int buf;
         for(int i = 0; i < obraz->wym_y; i++){                //pętla symulująca poruszanie się po kolumnach  tablicy
             int x = 0;                                        // pomocnicza zmienna pozwalająca na odczytywanie wartości tablicy od tyłu
            for(int j = 0; j < 3 * obraz->wym_x / 2; j++){     //pętla symulująca poruszanie się po wierszach tablicy
                 buf = obraz->piksele[(3 * i * obraz->wym_x) + j];   // zapis danej wartości do bufora 
                 obraz->piksele[(3 * i * obraz->wym_x) + j] = obraz->piksele[(3 * i * obraz->wym_x) + (3 * obraz->wym_x - 1) - x];  // przepisanie wartości "prawych" do "lewych"
                 obraz->piksele[(3 * i * obraz->wym_x) + (3 * obraz->wym_x - 1) - x] = buf;    // przepisanie wartości "lewych" do "prawych"
                 x++;
            }
         }
         int buff;
         int t = 0;                                             // pomocnicza zmienna pozwalająca ustawić kolory w opdowiedniej kolejności(po pętli tworzącej lustrzane odbicnie kolory czerwony i niebieski są przestawione względem siebie)
         for(int k = 0; k < ( obraz->wym_x * obraz->wym_y) - 2; k++){
             buff = obraz->piksele[t];                         // przestawienie kolorów na właściwe miejsca
             obraz->piksele[t] = obraz->piksele[t + 2];
             obraz->piksele[t + 2] = buff;
             t = t + 3;
         }
         
     }
}
void konturowanie(t_obraz *obraz, t_opcje *opcje){
    if(obraz->p2 ==1){
        for(int i = 0; i < (obraz->wym_x * obraz->wym_y) - 1; i++)                // pętla poruszająca się po tablicy
            obraz->piksele[i] = abs(obraz->piksele[i + 1] - obraz->piksele[i]);  //operacja konturowania 
    }
    if(obraz->p3 == 1){
        
        for(int i = 0; i < (3 * obraz->wym_x * obraz->wym_y) - 1; i++)             // pętla poruszająca się po tablicy
            obraz->piksele[i] = abs(obraz->piksele[i + 3] - obraz->piksele[i]);    //operacja konturowania
    } 
}

void konwersja(t_obraz *obraz, t_opcje *opcje){                  // zamienia kolorowy obraz na czarno-biały
    if(obraz->p2 != 1){                       // funkcja wykona się jeśli obraz jest w formacie PPM
        obraz->p3 = 0;                        // zmieniamy flagi tak, aby podczas zapisu obraz zapisał się jako PGM
        obraz->p2 = 1;
        int buf[3];                           // pomocniczy bufor do obliczenia średniej z 3 kolorów 
        for(int i = 0; i < obraz->wym_x * obraz->wym_y; i++){           // pętla poruszająca się po obrazie 
            for(int j = 0; j < 3; j++){                                 // pętla, w której następuje zapis do buforu 
                buf[j] = obraz->piksele[(i * 3) + j];
            }
             
            obraz->piksele[i] = (buf[0] + buf[1] + buf[2]) / 3;       // obliczenie średniej i zapisanie do tablicy  
    }       /*Obraz po konwersji zapisywany jest do tej samej dużej tablicy dla obrazu PPM, lecz nie 
    stanowi to problemu, ponieważ zmieniłem flagę na p2 więc obraz zapisze się wg funkcji dla zapisu obrazu 
    P2, która jest tak skonstruowana, że pozwoli tylko na zapis piseli powstałych po przetworzeniu, a reszta
    nadmiarowych a zaraem niepotrzebnych pikseli zostanie pominięta  */  
  } 
}

    
    
void filtruj(t_obraz *obraz, t_opcje *opcje){       // funkcja decydująca o dokonaniu danego filtru 
    if(opcje->konturowanie == 1)
       konturowanie(obraz, opcje);
    if(opcje->lustro == 1)
        odbicie(obraz, opcje);
    if(opcje->negatyw == 1)
        negatyw(obraz, opcje);
    if(opcje->progowanie == 1)
        progowanie(obraz, opcje);
    if(opcje->konwersja == 1)
        konwersja(obraz, opcje);    
    if(opcje->wyswietlenie == 1);

}