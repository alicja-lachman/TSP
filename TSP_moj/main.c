
#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <conio.h>


int main(int argc, char* argv[])
{
   if (argc!=3)
   {
		printf("Bledna ilosc parametrow!\nNacisnij dowolny klawisz, aby zakonczyc");
		getch();
   }

   else
   {
      FILE *plikIN,*plikOUT;
	  int liczbaMiast,i,j,populacja,iloscPokolen;
	  int **rodzice;
	  int **pokolenie;
	  float **macierzOdleglosci;
	  float dystans;
 
	  plikIN = fopen(argv[1],"r");
  
	  if (plikIN == NULL) 
	  {
		printf("Blad otwarcia pliku!\nNacisnij dowolny klawisz, aby zakonczyc");
		getch();
		return 1;
	  }
 
	  printf("Zaczynam czytac plik z danymi\n");
	
	  while(feof(plikIN) == 0)
	  {

		if (fscanf(plikIN,"%d",&liczbaMiast)!=1)  /*sprawdzenie formatu pliku wejsciowego */
		{
			printf("Nieprawidlowy format pliku!\n Nacisnij dowolny klawisz aby zakonczyc");
			getch();
			return 1;
		} else
		{
		printf("Liczba miast: %d\n",liczbaMiast);
		fscanf(plikIN, "%d",&populacja);
		printf("Ilosc osobnikow w populacji: %d\n",populacja);
		fscanf(plikIN, "%d",&iloscPokolen);
		printf("Ilosc pokolen: %d\n",iloscPokolen);

		macierzOdleglosci=(float**)malloc(sizeof(float*)*liczbaMiast);  /*alokacja pamiêci na tablicê wskaznikow na wskazniki*/
     
		for (i=0;i<liczbaMiast;i++)
		{  
			macierzOdleglosci[i]=(float*)malloc(sizeof(float)*(liczbaMiast));
		    for(j=0;j<liczbaMiast;j++)
			{
				fscanf(plikIN,"%f",&dystans);
			    macierzOdleglosci[i][j]=dystans;
			}
		}
	  }
 
	  fclose(plikIN);

	  rodzice=(int**)malloc(sizeof(int*)*populacja);
	  pokolenie=(int**)malloc(sizeof(int*)*populacja);

	  generujRodzicow(rodzice, liczbaMiast, populacja);
	  sortowanie(rodzice, liczbaMiast, populacja, macierzOdleglosci);
	  plikOUT = fopen(argv[2],"w");
	  for (i=0;i<iloscPokolen;i++)
	  {
		 rozmnazanie(rodzice, pokolenie, populacja, liczbaMiast);
		 sortowanie(pokolenie, liczbaMiast, populacja, macierzOdleglosci);
	   
		 if (i%1000==0)
		 printf("Najkrotsza trasa w %d pokoleniu: %f\n",i,obliczKoszt(liczbaMiast,pokolenie[0],macierzOdleglosci));
		 fprintf (plikOUT, "%f\n",obliczKoszt(liczbaMiast,pokolenie[0],macierzOdleglosci)); 
	     mutacja(pokolenie,liczbaMiast,populacja);
	     przepisz(pokolenie,rodzice,populacja,liczbaMiast);
      } 
	 fclose(plikOUT);
	 printf("Najlepsze rozwiazanie o koszcie %f to:\n",obliczKoszt(liczbaMiast,pokolenie[0],macierzOdleglosci));
     printf("[ ");             /*wypisanie najlepszego rozwiazania */
  
     for (i=0;i<liczbaMiast;i++)
     {
	   printf("%d ",rodzice[0][i]);
     }
     printf("]");
     

 
     for(i = 0; i < liczbaMiast; i++)  /*zwalnianie pamiêci*/
     {
	   free(macierzOdleglosci[i]);
     }
     free(macierzOdleglosci);
  
	 for(i = 0; i < populacja; i++)
     {
	   free(rodzice[i]);
	   free(pokolenie[i]);
     }
	
     free(rodzice);
     free(pokolenie);
     getch();
   
     return 0;
   }
 }
}