// TRNG.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

#define M_PI  3.14159265358979323846

void zerowanieTab(int **tabA, int **tabB, int **tabC, int **tablicaA, int **tablicaB, int **tabX, int **tabY, int **tabZ, int **tablicaX, int **tablicaY, 
	int macierzA, int macierzB, int macierzC, int macierzD, int macierzE);
void dispTab(int **tab, int macierz, string space);
string binSystem(int ** tab, int macierz, string wynik);
void lessVal(int ** tab, int **tab8, int macierz);
void decValue(int ** tab, int macierz);

int main()
{
	POINT P;
	int n = 64, k = 5000, wier = 4, kol = 4;
	int kolB = 0, wierB = 0;

	int macierzA = 64, macierzB = 16, macierzC = 8, macierzD = 4, macierzE = 2;

	int **tabA = new int*[macierzA], **tabX = new int*[macierzA];
	int **tabB = new int*[macierzB], **tabY = new int*[macierzB];
	int **tabC = new int*[macierzC], **tabZ = new int*[macierzC];
	int **tablicaA = new int*[macierzD], **tablicaX = new int*[macierzD];
	int **tablicaB = new int*[macierzE], **tablicaY = new int*[macierzE];
	//int tabB[16][16], tabY[16][16];
	//int tabA[64][64], tabX[64][64];
	int pierwotny_x, pierwotny_y, wynik_x, wynik_y;
	int pointer = 0, blok = 4;
	int parzystaPo, parzystaPrzed;
	double a = GetSystemMetrics(SM_CXSCREEN);
	double b = GetSystemMetrics(SM_CYSCREEN);
	double dzielnik_x = a/64, dzielnik_y = b/64;
	string space = " ", wynik = "";

	for (int i = 0; i < macierzA; ++i) {
		tabA[i] = new int [macierzA];
		tabX[i] = new int [macierzA];
		if (i < macierzB) {
			tabB[i] = new int[macierzB];
			tabY[i] = new int[macierzB];
		}
		if (i < macierzC) {
			tabC[i] = new int[macierzC];
			tabZ[i] = new int[macierzC];
		}
		if (i < macierzD) {
			tablicaA[i] = new int[macierzD];
			tablicaX[i] = new int[macierzD];
		}
		if (i < macierzE) {
			tablicaB[i] = new int[macierzE];
			tablicaY[i] = new int[macierzE];
		}
	}

	zerowanieTab(tabA, tabB, tabC, tablicaA, tablicaB, tabX, tabY, tabZ, tablicaX, tablicaY, macierzA, macierzB, macierzC, macierzD, macierzE);

	//ilość próbek:
	while (pointer < 100){
		if (GetCursorPos(&P)) {
			pierwotny_x = int(P.x/dzielnik_x);
			pierwotny_y = int(P.y/dzielnik_y);

			wynik_x = (P.x + P.y) %n;
			wynik_y = abs(int(P.y + k * sin(n / (2 * M_PI))) % n);

			cout << wynik_x << endl << wynik_y; //wyświetlanie pozycji X i Y myszki

			tabX[pierwotny_x][pierwotny_y] = 1;
			tabA[wynik_x][wynik_y] = 1;

			pointer++;

			system("cls");
		}
	}
	
	cout << "before postprocessing 64x64: \n";
	dispTab(tabX, macierzA, "");

	cout << "\nafter postprocessing 64x64: \n";
	dispTab(tabA, macierzA, "");
	
	while (wierB < 16) {
		while (kolB < 16) {
			parzystaPo = 0;
			parzystaPrzed = 0;
			for (int i = (wier - 4); i < wier; ++i) {
				for (int j = (kol - 4); j < kol; ++j) {
					if (tabA[i][j] == 1)
						parzystaPo++;
					if (tabX[i][j] == 1)
						parzystaPrzed++;
				}
			}
			tabY[wierB][kolB] = parzystaPrzed % 2;
			tabB[wierB][kolB] = parzystaPo % 2;
			kol += 4;
			kolB++;
		}
		wier += 4;
		kol = 4;
		kolB = 0;
		wierB++;
	}

	cout << "\n\nbefore postprocessing 16x16: \n";
	dispTab(tabY, macierzB, space);

	cout << "\nafter postprocessing16x16: \n";
	dispTab(tabB, macierzB, space);
	
	//cout << "\nWynik w systemie dwojkowym przed entropia: \n" << binSystem(tabY, macierzB, wynik);

	//zamiana na wartosc 8 bitowa
	lessVal(tabB, tabC, macierzC);
	lessVal(tabY, tabZ, macierzC);

	cout << endl << "before postprocessing 8x8: ";
	decValue(tabZ, macierzC);
	dispTab(tabZ, macierzC, space);

	cout << endl << "after postprocessing 8x8: ";
	decValue(tabC, macierzC);
	dispTab(tabC, macierzC, space);

	//zamiana na wartosc 4 bitowa
	lessVal(tabC, tablicaA, macierzD);
	lessVal(tabZ, tablicaX, macierzD);

	cout << endl << "before postprocessing 4x4: ";
	decValue(tablicaX, macierzD);
	dispTab(tablicaX, macierzD, space);

	cout << endl << "after postprocessing 4x4: ";
	decValue(tablicaA, macierzD);
	dispTab(tablicaA, macierzD, space);

	//zamiana na wartosc 2 bitowa
	lessVal(tablicaA, tablicaB, macierzE);
	lessVal(tablicaX, tablicaY, macierzE);

	cout << endl << "before postprocessing 4x4: ";
	decValue(tablicaY, macierzE);
	dispTab(tablicaY, macierzE, space);

	cout << endl << "after postprocessing 4x4: ";
	decValue(tablicaB, macierzE);
	dispTab(tablicaB, macierzE, space);
	

	for (int i = 0; i < macierzA; i++) {
		delete[] tabA[i];
		delete[] tabX[i];
		if (i < macierzB) {
			delete[] tabB[i];
			delete[] tabY[i];
		}
		if (i < macierzC) {
			delete[] tabC[i];
			delete[] tabZ[i];
		}
		if (i < macierzD) {
			delete[] tablicaA[i];
			delete[] tablicaX[i];
		}
		if (i < macierzE) {
			delete[] tablicaB[i];
			delete[] tablicaY[i];
		}
	}

	delete[] tabA;
	delete[] tabB;
	delete[] tabC;
	delete[] tablicaA;
	delete[] tablicaB;
	delete[] tabX;
	delete[] tabY;
	delete[] tabZ;
	delete[] tablicaX;
	delete[] tablicaY;

	system("Pause");
	return 0;
}

void zerowanieTab(int **tabA, int **tabB, int **tabC, int **tablicaA, int **tablicaB, int **tabX, int **tabY, int **tabZ, int **tablicaX, 
	int **tablicaY, int macierzA, int macierzB, int macierzC, int macierzD, int macierzE) {
	for (int i = 0; i < macierzA; ++i) {
		for (int j = 0; j < macierzA; ++j) {
			tabA[i][j] = 0;
			tabX[i][j] = 0;
			if (i < macierzB && j < macierzB) {
				tabB[i][j] = 0;
				tabY[i][j] = 0;
			}
			if (i < macierzC && j < macierzC) {
				tabC[i][j] = 0;
				tabZ[i][j] = 0;
			}
			if (i < macierzD && j < macierzD) {
				tablicaA[i][j] = 0;
				tablicaX[i][j] = 0;
			}
			if (i < macierzE && j < macierzE) {
				tablicaB[i][j] = 0;
				tablicaY[i][j] = 0;
			}
		}
	}
}

void dispTab(int **tab, int macierz, string space) {
	for (int i = 0; i < macierz; ++i) {
		for (int j = 0; j < macierz; ++j)
			cout << tab[i][j] << space;
		cout << endl;
	}
}

string binSystem(int ** tab, int macierz, string wynik) {
	for (int i = 0; i < macierz; ++i) {
		for (int j = 0; j < macierz; ++j) {
			ostringstream ss;
			ss << tab[i][j];
			wynik = ss.str();
		}
	}
	return wynik;
}

void lessVal(int ** tab, int ** tabN, int macierz) {
	int kolNew = 0, wierNew = 0;
	int kolumna=2, wiersz=2;
	int licznik = 0;

	while (wierNew < macierz) {
		while (kolNew < macierz) {
			licznik = 0;
			for (int i = (wiersz -2); i < wiersz; ++i) {
				for (int j = (kolumna -2); j < kolumna; ++j) {
					if (tab[i][j] == 1)
						licznik++;
				}
			}
			tabN[wierNew][kolNew] = licznik % 2;
			kolumna += 2;
			kolNew++;
		}
		kolNew = 0;
		kolumna = 2;
		wiersz += 2;
		wierNew++;
	}
}

void decValue(int ** tab, int macierz) {
	unsigned long long liczba_los = 0;
	unsigned long long mnoznik = 1;
	for (int i = (macierz-1); i >= 0; --i) {
		for (int j = (macierz - 1); j >= 0; --j) {
			liczba_los += (tab[i][j] * mnoznik);
			mnoznik *= 2;
		}
	}
	cout << "Liczba wylosowana : " << liczba_los << endl;
}