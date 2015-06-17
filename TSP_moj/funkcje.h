#ifndef FUNKCJE_H
#define FUNKCJE_H

int losowanie(int zakres);
int sprawdzPowtorzenia(int *chromosom,int iloscLiczb, int liczba);
int *losuj(int ilosc);
void generujRodzicow(int **rodzice, int iloscMiast, int iloscRodzicow);
float obliczKoszt(int rozmiar, int *rozwiazanie, float **macierzOdleglosci);
void sortowanie(int **rozwiazania, int liczbaMiast, int populacja, float **macierzOdleglosci);
void rozmnazanie(int **rodzice, int **pokolenie, int iloscRodzicow, int rozmiarGenu);
void mutacja(int **pokolenie, int dlugoscGenu, int populacja);
void przepisz(int **A, int **B, int iloscWierszy, int iloscKolumn);


#endif