// TRNG.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

#define M_PI  3.14159265358979323846

int main()
{
	POINT P;
	int n = 64, k = 5000, wier = 4, kol = 4;
	int tabA[64][64], tabB[16][16];
	int wynik_x, wynik_y;
	int pointer = 0, blok = 4;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			tabA[i][j] = 0;
			if (i < 16 && j < 16)
				tabB[i][j] = 0;
		}
	}

	while (pointer < 1000){
		if (GetCursorPos(&P)) {
			wynik_x = (P.x + P.y) %n;
			wynik_y = abs(int(P.y + k * sin(n / (2 * M_PI))) % n);

			cout << wynik_x;
			cout << wynik_y;

			tabA[wynik_x][wynik_y] = 1;

			pointer++;

			system("cls");
		}
	}

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++)
			cout << tabA[i][j];
		cout << endl;
	}

	int kolB = 0, wierB = 0;
	int tempK = 0, tempW = 0;
	int parzysta;

	while (wier < 64) {
		while (kol < 64) {
			parzysta = 0;
			for (int i = (wier - 4); i < wier; i++) {
				for (int j = (kol - 4); j < kol; j++) {
					if (tabA[i][j] == 1)
						parzysta++;
				}
			}
			kol += 4;
			tabB[wierB][kolB] = parzysta % 2;
			//cout << parzysta << " " << tabB[wierB][kolB] << " " << wier << " " << kol << endl;
			kolB++; //wyzerować przy nowej lini
		}
		wier += 4;
		//kol = 0;
		kolB = 0;
		wierB++;
		wier += 4;
	}


	cout << endl;
	cout << endl;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++)
			cout << tabB[i][j] << " ";
		cout << endl;
	}

	system("Pause");
	return 0;
}