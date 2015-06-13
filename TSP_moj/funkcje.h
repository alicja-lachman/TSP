#ifndef FUNKCJE_H
#define FUNKCJE_H

float obliczKoszt(int rozmiar, int *rozwiazanie, float **macierzOdleglosci);
void sortowanie(int **rozwiazania, int liczbaMiast, int populacja, float **macierzOdleglosci);
int sprawdzPowtorzenia(int *chromosom,int iloscLiczb, int liczba);
int losowanie(int zakres);
int *losuj(int ilosc);
void generujRodzicow(int **rodzice, int iloscMiast, int iloscRodzicow);
void rozmnazanie(int **rodzice, int **pokolenie, int iloscRodzicow, int rozmiarGenu);
void przepisz(int **A, int **B, int iloscWierszy, int iloscKolumn);
void mutacja(int **pokolenie, int dlugoscGenu, int populacja,int iloscPowtorzen);

#endif