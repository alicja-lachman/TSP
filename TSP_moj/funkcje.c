#include "funkcje.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

/* Funkcja obliczajaca koszt podrozy pomiedzy poszczegolnymi miastami */
/* zgodnie z kolejnosci¹ zawart¹ w chromosomie */
float obliczKoszt(int iloscMiast, int *chromosom, float **macierzOdleglosci)
{
	int i;
    float koszt;

	koszt = 0;
	for(i = 0; i<(iloscMiast-1); i++)
	{
		koszt = koszt + macierzOdleglosci[chromosom[i]][chromosom[i+1]];
	}
	koszt = koszt + macierzOdleglosci[chromosom[i]][chromosom[0]];
	return koszt;
}



/*funkcja sortuj¹ca rosn¹co rozwi¹zania(chromosomy) wed³ug ich kosztów */
/* sortowanie przez wybór */
void sortowanie(int **rozwiazania, int liczbaMiast, int populacja, float **macierzOdleglosci)
{
int i,j,min;
int *temp;
	
	for(j=0; j < (populacja-1); j++)
	{   
		min=j;
		for(i=j+1; i <populacja; i++)
	    {
			if (obliczKoszt(liczbaMiast,rozwiazania[i],macierzOdleglosci) < obliczKoszt(liczbaMiast,rozwiazania[min],macierzOdleglosci))
			{
				min=i;
			}
				temp = rozwiazania[min];
				rozwiazania[min] = rozwiazania[j];
				rozwiazania[j] = temp;
			
		}
	}
}



/*funkcja sprawdzajaca, czy do chromosu nie wylosowano powtarzajacego sie genu (numeru miasta)*/
int sprawdzPowtorzenia(int *chromosom,int iloscLiczb, int liczba)
{
	int i;

	if(iloscLiczb <= 0)
    return 0;
	
	for (i=0; i<iloscLiczb; i++)
	{
        if(chromosom[i] == liczba)
        return 1;       
    } 
    return 0;
}

/*funkcja zwracajaca losow¹ liczbe z zakresu <0;zakres-1> */
int losowanie(int zakres)
{         
    return(rand()%zakres);
}


/* funkcja zwracajaca wskaznik na tablice wylosowanych rozwiazan */
/* liczby (kolejnosc odwiedzanych miast) nie mog¹ siê powtarzac */
int *losuj(int ilosc)
{
int *wylosowaneLiczby; 
int ileWylosowanych;
int liczba;
    
    ileWylosowanych=0;              /*licznik ilosci wylosowanych liczb */
	wylosowaneLiczby=(int*)malloc((sizeof(int))*ilosc);  /*alokacja pamieci na tablice liczb */

    do               /* losowanie kolejnych liczb oraz sprawdzanie, czy nie ma powtorzen */
    {
		liczba = losowanie(ilosc);
		if(sprawdzPowtorzenia(wylosowaneLiczby,ileWylosowanych,liczba)==0)
        {
            wylosowaneLiczby[ileWylosowanych]=liczba;
            ileWylosowanych++;
        }
    }while (ileWylosowanych<ilosc);   
    
	return wylosowaneLiczby;
}

/*funkcja generuj¹ca pierwsze pokolenie rozwi¹zan - rodziców */
void generujRodzicow(int **rodzice, int iloscMiast, int iloscRodzicow)
{
int i;

	srand(time(NULL));       /*inicjalizacja zarodka dla funkcji rand */
	for(i=0; i<iloscRodzicow; i++)
	{    
		rodzice[i] = losuj(iloscMiast);  /*i-ty rodzic wskazuje na wylosowane rozwiazanie*/
	}
}

/* funkcja rozmnazajaca, dzialajaca na podstawie krzy¿owania z porz¹dkowaniem */
void rozmnazanie(int **rodzice, int **pokolenie, int iloscRodzicow, int rozmiarGenu)
{
int i,j,k,l,temp;
int *uzyte, iloscUzytych;    

    srand(time(NULL));              /*inicjalizacja zarodka funkcji rand */
	uzyte=(int*)malloc(sizeof(int)*rozmiarGenu); /*alokacja pamieci na tablice uzytych elementow */
		
	pokolenie[0]=(int*)malloc(sizeof(int)*rozmiarGenu);  
											 		
	for(i=0; i<rozmiarGenu; i++)               /*pierwszym osobnikiem nowego pokolenia */
	(pokolenie[0])[i] = (rodzice[0])[i];     /*staje sie najlepszy osobnik ze starego pokolenia */


	for(i=1; i<iloscRodzicow; i++)    /*reszta pokolenia powstaje przez krzyzowanie */
	{	
		iloscUzytych=0;
		pokolenie[i]=(int*)malloc(sizeof(int)*rozmiarGenu);
		k=(rand()%(iloscRodzicow/2));    /*k jest losowa liczba z zakresu <0;(iloscRodzicow/2)-1> aby krzyzowaæ tylko lepsze osobniki z puli rodzicow */
		l=((rand()%2)+3);                /*l jest losow¹ liczb¹*/
		
		for(j=0; j<(rozmiarGenu/l); j++)  
		{
			(pokolenie[i])[iloscUzytych] = (rodzice[k])[j];
			uzyte[iloscUzytych] = (rodzice[k])[j];
			iloscUzytych++;
		}

		k=(rand()%(iloscRodzicow/2));
	    do
	    {
			if(j==rozmiarGenu){
			j=0;
			}

			temp=(rodzice[k])[j];

			if(sprawdzPowtorzenia(uzyte,iloscUzytych,temp) == 0)
			{	
				(pokolenie[i])[iloscUzytych] = (rodzice[k])[j];
				uzyte[iloscUzytych] = (rodzice[k])[j];
				iloscUzytych++;
			}
			j++;

		} while(iloscUzytych<rozmiarGenu);
	}
}

/* funkcja przepisuj¹ca dane z dwuwymiarowej tablicy A do dwuwymiarowej tablicy B */
void przepisz(int **A, int **B, int iloscWierszy, int iloscKolumn)
{
	int i,j;
	for(i=0; i<iloscWierszy; i++)
	{
		for(j=0; j<iloscKolumn; j++)
		{
			(B[i])[j] = (A[i])[j];
		}
	}
}


/*funkcja dokonujaca mutacji. okreslona jest ilosc mutacji [ilosc powtorzen] w danym pokoleniu  */
void mutacja(int **pokolenie, int dlugoscGenu, int populacja,int iloscPowtorzen)
{  
	int a,b,c,i,j,temp;

	for(i=0; i<iloscPowtorzen; i++)    /*i okresla ilosc mutacji w pokoleniu*/
		{   
	
		srand(time(NULL));    /*inicjalizacja zarodka funkcji rand */

		for(j=0; j<populacja; j++)
		{
			a = (rand()%(populacja-1)+1);  /*wylosowanie liczby z zakresu <1;populacja-1*/
			b = rand()%dlugoscGenu;        /*najlepszy osobnik nie bedzie mutowany! */
			c= rand()%dlugoscGenu;
			
			temp = (pokolenie[a])[b];
			(pokolenie[a])[b] = (pokolenie[a])[c];
			(pokolenie[a])[c] = temp;	
		}
		}
}


