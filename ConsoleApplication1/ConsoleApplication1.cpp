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

	while (pointer < 100){
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

	while (wierB <= 16) {
		while (kolB <= 16) {
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
			cout << wierB << endl;
		}
		wier += 4;
		kol = 0;
		kolB = 0;
		wierB++;
	}


	cout << endl;
	cout << endl;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++)
			cout << tabB[i][j] << " ";
		cout << endl;
	}
	
	string wynikk = "";
	unsigned int liczba_losowa;
	cout << "Wynik w systemie dwojkowym : " << endl;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			ostringstream ss;
			ss << TabB[i][j];
			string wynikk = ss.str();
			cout << wynikk;

		}
	}
	cout << endl;
	unsigned long long liczba_los = 0;
	unsigned long long mnoznik = 1;
	for (int i = 15; i >= 0; i--)
	{
		for (int j = 15; j >= 0; j--)
		{
			liczba_los += (TabB[i][j] * mnoznik);
			mnoznik *= 2;

		}
	}
	cout << "Liczba wylosowana : ";
	cout << liczba_los << endl;

	system("Pause");
	return 0;
}



/*
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include <cstdlib>
#include <math.h>

using namespace std;

#define M_PI  3.14159265358979323846

int main()
{
	POINT P;
	int n = 64, k = 5000, temp = 4;
	int TabA[64][64], TabB[16][16];
	int wynik_x, wynik_y;
	int pointer = 0;
	int blok = 4;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			TabA[i][j] = 0;
			if (i < 16 && j < 16)
				TabB[i][j] = 0;
		}
	}

	while (pointer <= 100) {
		if (GetCursorPos(&P)) {

			wynik_x = (P.x + P.y) % n;
			wynik_y = abs(int(P.y + k * sin(n / (2 * M_PI))) % n);

			cout << wynik_x;
			cout << wynik_y;

			TabA[wynik_x][wynik_y] = 1;

			pointer++;

			system("cls");
		}
	}


	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++)
			cout << TabA[i][j];
		cout << endl;
	}



	int wynik = 0, parzyste = 0;
	int nowe_i = 0;
	int nowe_j = 0;
	int przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 4; j < 8; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 8; j < 12; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 12; j < 16; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 16; j < 20; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 20; j < 24; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 24; j < 28; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 28; j < 32; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 32; j < 36; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 36; j < 40; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 40; j < 44; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 44; j < 48; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 48; j < 52; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 52; j < 56; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 56; j < 60; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}
	nowe_i = 0;
	nowe_j++;
	przejscie_poziom = 0;
	while (przejscie_poziom < 64)
	{
		for (int i = przejscie_poziom; i < przejscie_poziom + 4; i++)
		{
			for (int j = 60; j < 64; j++)
			{
				wynik = wynik + TabA[i][j];
				parzyste = wynik % 2;

			}

		}
		TabB[nowe_i][nowe_j] = parzyste;
		wynik = 0;
		parzyste = 0;
		nowe_i++;
		przejscie_poziom = przejscie_poziom + 4;
	}



	cout << endl << "TabA 2 " << endl;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			cout << TabB[j][i] << " ";
		}
		cout << endl;
	}


	string wynikk = "";
	unsigned int liczba_losowa;
	cout << "Wynik w systemie dwojkowym : " << endl;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			ostringstream ss;
			ss << TabB[i][j];
			string wynikk = ss.str();
			cout << wynikk;

		}
	}
	cout << endl;
	unsigned long long liczba_los = 0;
	unsigned long long mnoznik = 1;
	for (int i = 15; i >= 0; i--)
	{
		for (int j = 15; j >= 0; j--)
		{
			liczba_los += (TabB[i][j] * mnoznik);
			mnoznik *= 2;

		}
	}
	cout << "Liczba wylosowana : ";
	cout << liczba_los << endl;


	system("Pause");
	return 0;
}

*/

/*

#include "stdafx.h"
#include <iostream>
#include <sstream>
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

	while (pointer < 100) {
		if (GetCursorPos(&P)) {
			wynik_x = (P.x + P.y) % n;
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

	while (wierB <= 16) {
		while (kolB <= 16) {
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
			cout << wierB << endl;
		}
		wier += 4;
		kol = 0;
		kolB = 0;
		wierB++;
	}


	cout << endl;
	cout << endl;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++)
			cout << tabB[i][j] << " ";
		cout << endl;
	}

	string wynikk = "";
	unsigned int liczba_losowa;
	cout << "System dwojkowy : " << endl;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			ostringstream ss;
			ss << tabB[i][j];
			string wynikk = ss.str();
			cout << wynikk;

		}
	}
	cout << endl;
	unsigned long long liczba_los = 0;
	unsigned long long mnoznik = 1;
	for (int i = 15; i >= 0; i--)
	{
		for (int j = 15; j >= 0; j--)
		{
			liczba_los += (tabB[i][j] * mnoznik);
			mnoznik *= 2;

		}
	}
	cout << "Liczba wylosowana : ";
	cout << liczba_los << endl;

	system("Pause");
	return 0;
}

*/
