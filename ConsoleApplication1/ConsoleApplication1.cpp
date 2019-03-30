// TRNG.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

#define M_PI  3.14159265358979323846

void zerowanieTab(int **tabA, int **tabB, int **tabC, int **tabX, int **tabY, int **tabZ, int macierzA, int macierzB, int macierzC);
void dispTab(int **tab, int macierz, string space);
string binSystem(int ** tab, int macierz, string wynik);
void lessVal(int ** tab, int **tab8, int macierz);
void decValue(int ** tab, int macierz);

int main()
{
	POINT P;
	int n = 64, k = 5000, wier = 4, kol = 4;
	int kolB = 0, wierB = 0;

	int macierzA = 64, macierzB = 16, macierzC = 8;

	int **tabA = new int*[macierzA], **tabX = new int*[macierzA];
	int **tabB = new int*[macierzB], **tabY = new int*[macierzB];
	int **tabC = new int*[macierzC], **tabZ = new int*[macierzC];
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
	}

	zerowanieTab(tabA,tabB,tabC, tabX,tabY, tabZ, macierzA, macierzB, macierzC);

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
	
	cout << "Przed entropia: \n";
	dispTab(tabX, macierzA, "");

	cout << "\nPo entropii: \n";
	dispTab(tabA, macierzA, "");
	
	while (wierB <= 15) {
		while (kolB <= 15) {
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
			kol += 4;
			tabY[wierB][kolB] = parzystaPrzed % 2;
			tabB[wierB][kolB] = parzystaPo % 2;
			kolB++;
		}
		wier += 4;
		kol = 0;
		kolB = 0;
		wierB++;
	}

	cout << "\n\n16x16 przed entropii: \n";
	dispTab(tabY, macierzB, space);

	cout << "\n16x16 po entropia: \n";
	dispTab(tabB, macierzB, space);
	
	//cout << "\nWynik w systemie dwojkowym przed entropia: \n" << binSystem(tabY, macierzB, wynik);

	//zamiana na wartosc 8 bitowa
	lessVal(tabB, tabC, macierzB);
	lessVal(tabY, tabZ, macierzB);

	cout << endl << "przed entropia 8x8: ";
	decValue(tabZ, macierzC);
	dispTab(tabZ, macierzC, space);

	cout << endl << "po entropi ";
	decValue(tabC, macierzC);
	dispTab(tabC, macierzC, space);
	

	for (int i = 0; i < macierzA; i++) {
		delete[] tabA[i];
		delete[] tabX[i];
		if (i < macierzB) {
			delete[] tabB[i];
			delete[] tabY[i];
		}
	}

	delete[] tabA;
	delete[] tabB;
	delete[] tabX;
	delete[] tabY;

	system("Pause");
	return 0;
}

void zerowanieTab(int **tabA, int **tabB, int **tabC, int **tabX, int **tabY, int **tabZ, int macierzA, int macierzB, int macierzC) {
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

void lessVal(int ** tab, int ** tab8, int macierz) {
	int kolC = 0, wierC = 0;
	int kol8=2, wier8=2;
	int licznik = 0;

	while (wierC <= 3) {
		while (kolC <=3 ) {
			licznik = 0;
			for (int i = (wier8-2); i < wier8; ++i) {
				for (int j = (kol8-2); j < kol8; ++j) {
					cout << tab[i][j] << " ";
					if (tab[i][j] == 1)
						licznik++;
				}
			}
			cout << endl;
			tab8[wierC][kolC] = licznik % 2;
			kol8 += 2;
			kolC++;
		}
		kolC = 0;
		kol8 = 0;
		wier8 += 2;
		wierC++;
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

//zliczanie wartości co 8 bitów i następnie dodawanie ich