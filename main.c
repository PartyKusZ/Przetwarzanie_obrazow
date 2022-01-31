/* Jakub Kusz, Wrocław, 04.01.2021r.
Przetwarzanie obrazów 2
Kompilacja diablo: cc -xc99 -Xc -lm main.c asercja.c filtry.c opcje.c pliki_zapisz_odczyty_wyswietl.c
Kompliacja Panamint: gcc -std=c99 -pedantic -Wall main.c asercja.c filtry.c opcje.c pliki_zapisz_odczyty_wyswietl.c*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"filtry.h"
#include"struktury.h"
#include"opcje.h"
#include"pliki_zapisz_odczyty_wyswietl.h"
#include"asercja.h"
int main(int argc, char *argv[]){
    t_opcje opcje;
    t_obraz obraz;
    asercja(czytaj_opcje(argc, argv, &opcje));        // odczytanie opcji i sprawdzenie waruknów asercji
    czytaj(&obraz, &opcje);                           // wczytanie obrazu do pamięci 
    filtruj(&obraz, &opcje);                          // nałożenie filtrów 
    zapisz(&obraz, &opcje);                           // zapisanie do nowego pliku 
}


/*****************************************************************************************************************/
/*                                                                                                               */
/*                                              SPRAWOZDANIE                                                     */ 
/*                                                                                                               */
/*  1. Testy                                                                                                     */
/*       Przyjęta przezemnie metodologia testowania programu wyglądała  w następujący sposób:                    */
/*          - wywołanie danej funkcji progamu,                                                                   */
/*          - odcena rezultatów.                                                                                 */
/*       Obrazy testowe zostały dołączone do archiwum.                                                           */     
/*       1.1. negatywowanie:                                                                                     */  
/*            a) obraz pgm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.pgm -n -o Lenan.pgm                                           */ 
/*               obraz został prawidłowo poddany operacji negatywowania i zapisany do nowego pliku               */
/*            b) obraz ppm:                                                                                      */ 
/*               sposób wywołania: ./a.out -i Lena.ppm -n -o Lenan.ppm                                           */
/*               obraz został prawidłowo poddany operacji negatywowania i zapisany do nowego pliku               */
/*       1.2. konturowanie:                                                                                      */
/*            a) obraz pgm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.pgm -k -o Lenak.pgm                                           */ 
/*               obraz został prawidłowo poddany operacji konturowania i zapisany do nowego pliku                */ 
/*            b) obraz ppm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.ppm -k -o Lenak.ppm                                           */ 
/*               obraz został prawidłowo poddany operacji konturowania i zapisany do nowego pliku                */
/*       1.3. odbicie luatrzane:                                                                                 */
/*            a) obraz pgm:                                                                                      */     
/*               sposób wywołania: ./a.out -i Lena.pgm -l -o Lenal.pgm                                           */
/*               obraz został prawidłowo poddany operacji odbicia lustrzanego i zapisany do nowego pliku         */    
/*            b) obraz ppm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.ppm -l -o Lenal.ppm                                           */
/*               obraz został prawidłowo poddany operacji odbicia lustrzanego i zapisany do nowego pliku         */
/*       1.4. progowanie:                                                                                        */ 
/*            a) obraz pgm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.pgm -p 50 -o Lenap.pgm                                        */ 
/*               obraz został prawidłowo poddany operacji progowania i zapisany do nowego pliku                  */
/*            b) obraz ppm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.ppm -p 50 -o Lenap.ppm                                        */
/*               obraz został prawidłowo poddany operacji progowania i zapisany do nowego pliku                  */ 
/*                                                                                                               */
/*               Filtr progowania działa prawidłowo dla wszystich wartości progu.                                */
/*               Opcja -d pozwalająca na wyswietlenie odbrazu tu po dokonaniu jego zapisu również w każdym       */ 
/*               w każdym przypadku działa prawidłowo.                                                           */
/*       1.5. konwersja:                                                                                         */
/*            a) obraz pgm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.pgm -r -o Lenar.pgm                                           */
/*               funkcja nie zostaje wywołana, ponieważ obraz jest czarno-biały                                  */
/*            b) obraz ppm:                                                                                      */
/*               sposób wywołania: ./a.out -i Lena.ppm -r -o Lenar.ppm                                           */
/*               obraz prawidłowo został przekonwertowany na czarno-biały
/*       1.6. Testy zabezpieczenia funkcji czytaj_opcje przed błędnymi sposobami wywołania                       */                      
/*            a) zapisanie opcji -i łącznie z nazwą:                                                             */
/*               sposób wywołania: ./a.out -iLena.pgm -p 50 -o Lenap.pgm                                         */ 
/*               Program informuje o niepowodzeniu przy otwarciu pliku i wyświetla instrukcje o poprawym sposobie*/ 
/*               wywołania.                                                                                      */
/*            b) zapisanie opcji -o łącznie z nazwą:                                                             */ 
/*               soposób wywołania: ./a.out -i Lena.pgm -p 50 -oLenap.pgm                                        */
/*               Program informuje o błędnym wywolaniu                                                           */ 
/*            c) zapisanie -p łącznie z wartością prosentową progu:                                              */ 
/*               soposób wywołania: ./a.out -i Lena.pgm -p50 -o Lenap.pgm                                        */
/*               Program informuje o błędnym wywolaniu                                                           */ 
/*            d) zapianie jakiejkolwiek opcji bez "-" z przodu:                                                  */ 
/*               sposób wywołania: ./a.out i Lena.pgm -p 50 -oLenap.pgm                                          */
/*               Program informuje o błędnym wywolaniu                                                           */
/*            e) opcja -i-:                                                                                      */
/*               Program reaguje prawidłowo i oczekuje podania obrazu na standardowowym wyjściu                  */ 
/*            f) opcja -o-:                                                                                      */
/*               Program reaguje prawidłowo i wypisuje obraz na standardowe wyjście                              */ 
/*       1.7. Wadliwy obraz                                                                                      */
/*            W razie braku "numeru magicznego" zostaniemu o tym poinformowani, w razie braku wymiaru bądź       */ 
/*            wymiarów lub ilości odcieni również otrzymamy stosowny komunikat, program nie wykona się.                                 */ 
/*                                                                                                               */ 
/*                                                                                                               */  
/*       2. Wnioski                                                                                              */
/*          Program jest odpowiednio zabezpieczony przed błędbym wywołaniem i w razie ów wywołania wyświetla     */
/*          instrukcje pouczającą o poprawnym sposobie wywołania. Informuje również o obłędach w obrazie         */ 
/*          stosownymi komunikatami. Program spełnia postawione przed nim wymagania i z powodzeniem dokonuje     */
/*          wszystkich operacji filtrowania obrazów.                                                             */
/*                                                                                                               */ 
/*                                                                                                               */ 
/*****************************************************************************************************************/