#include <iostream>
#include<fstream>
#include<math.h>

using namespace std;
float X;
float Y;

float A = 5;
float B = 5;
float C = 3;

int q = 16;

int main() {
	//Drukujemy punkty dla wykresu od 0 do 4 sekund
	ofstream zapis("dane.txt");
	for (float i = 0; i <= 4000; i++) {

		Y = sin((2 * 3.14) * (5*i/1000) + (3.14 * C));
		zapis << i / 1000 << " " << Y << endl;

	}
	zapis.close();
	//Drukujemy punkty kwantyzacju od 0 do 4 sekund dla wykresu 1
	ofstream zapis2("dane2.txt");
	for (float i = 0; i <= 4000; i++) {

		Y = sin((2 * 3.14) * (5 * i / 1000) + (3.14 * C));
		Y = Y * pow(2,q);
		zapis2 << i / 1000 << " " << Y << endl;

	}
	zapis2.close();
	//Tworzymy  wykres skwantyzowany dla wartoœci o po³owe mniejszych
	q = 8;
	ofstream zapis3("dane3.txt");
	for (float i = 0; i <= 4000; i++) {
		float Y;
		Y = sin((2 * 3.14) * (5 * i / 2000) + (3.14 * C));
		Y = Y * pow(2,q);
		
		zapis3 << i / 1000 << " " << Y << endl;

	}
	zapis3.close();


	

};