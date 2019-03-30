// TRNG.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

#define M_PI  3.14159265358979323846

void zerowanieTab(int **tabA, int **tabB, int **tabY, int **tabX, int macierzA, int macierzB);
void dispTab(int **tab, int macierz, string space);

int main()
{
	POINT P;
	int n = 64, k = 5000, wier = 4, kol = 4;

	int macierzA = 64, macierzB = 16;


	int **tabA = new int*[macierzA], **tabX = new int*[macierzA];
	int **tabB = new int*[macierzB], **tabY = new int*[macierzB];
	//int tabB[16][16], tabY[16][16];
	//int tabA[64][64], tabX[64][64];
	int pierwotny_x, pierwotny_y, wynik_x, wynik_y;
	int pointer = 0, blok = 4;
	int kolB = 0, wierB = 0;
	int parzystaPo, parzystaPrzed;
	double a = GetSystemMetrics(SM_CXSCREEN);
	double b = GetSystemMetrics(SM_CYSCREEN);
	double dzielnik_x = a/64, dzielnik_y = b/64;
	string space = " ", wynikPrzed = "";

	for (int i = 0; i < macierzA; ++i) {
		tabA[i] = new int [macierzA];
		tabX[i] = new int [macierzA];
		if (i < macierzB) {
			tabB[i] = new int[macierzB];
			tabY[i] = new int[macierzB];
		}
	}

	zerowanieTab(tabA,tabB,tabX,tabY, macierzA, macierzB);

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
	
	string ;
	
	cout << "\nWynik w systemie dwojkowym przed entropia: \n";
	for (int i = 0; i < 16; ++i){
		for (int j = 0; j < 16; ++j){
			ostringstream ss;
			ss << tabY[i][j];
			wynikPrzed = ss.str();
			cout << wynikPrzed;
		}
	}
	cout << endl;
	unsigned long long liczba_los = 0;
	unsigned long long mnoznik = 1;
	for (int i = 15; i >= 0; --i){
		for (int j = 15; j >= 0; --j){
			liczba_los += (tabB[i][j] * mnoznik);
			mnoznik *= 2;
		}
	}
	cout << "Liczba wylosowana : ";
	cout << liczba_los << endl;

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

void zerowanieTab(int **tabA, int **tabB, int **tabY, int **tabX, int macierzA, int macierzB) {
	for (int i = 0; i < macierzA; ++i) {
		for (int j = 0; j < macierzA; ++j) {
			tabA[i][j] = 0;
			tabY[i][j] = 0;
			if (i < macierzB && j < macierzB) {
				tabB[i][j] = 0;
				tabX[i][j] = 0;
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

//zliczanie wartości co 8 bitów i następnie dodawanie ich
