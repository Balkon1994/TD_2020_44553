#include <iostream>
#include<fstream>
#include<math.h>

using namespace std;

int main() {

	int A=5;
	int B=5;
	int C=3;
	float X;
	float Y;
	float Z;
	float U;
	float V;
	float P;
	float wynik=0;
	//////// Wyprowadzenie X ////////////////////
	ofstream zapis("dane.txt");
	for (float i = -100; i <= 100; i++) {
		
		Y = A*((i/10)*(i/10)) + B * (i/10) + C;
		zapis << i/10 << " " << Y << endl;

	}
		zapis.close();

	////// Wyprowadzenie Y ////////////////////
	ofstream zapis2("dane2.txt");
	for (float i = 0; i <= 22050; i++) {

			X = A * ((i / 22050) * (i / 22050)) + B * (i / 10) + C;
			Y = (2 * (X*X)) + 12 * cos(i / 22050);
			zapis2 << i / 22050 << " " << Y << endl;

	}
	zapis2.close();
	//////Wyprowadzenie Z ///////////////
	ofstream zapis3("dane3.txt");
	for (float i = 0; i <= 22050; i++) {

		X = A * ((i / 22050) * (i / 22050)) + B * (i / 10) + C;
		Y = (2 * (X * X)) + 12 * cos(i / 22050);
		Z = sin((2 * 3.14) * 7 * (i / 22050)) * X - 0.2 * log10(abs(Y) + 3.14);
		zapis3 << i / 22050 << " " << Z << endl;

	}
	zapis3.close();
	////Wyprowadzenie U//////////////
	ofstream zapis4("dane4.txt");
	for (float i = 0; i <= 22050; i++) {

		X = A * ((i / 22050) * (i / 22050)) + B * (i / 10) + C;
		Y = (2 * (X * X)) + 12 * cos(i / 22050);
		Z = sin((2 * 3.14) * 7 * (i / 22050)) * X - 0.2 * log10(abs(Y) + 3.14);
		U = sqrt(abs(Y * Y * Z)) - 1.8 * sin(0.4 * (i / 22050) * Z * X);
		zapis4 << i / 22050 << " " << U << endl;

	}
	zapis4.close();

	////Wyprowadzenie Z//////////////
	ofstream zapis5("dane5.txt");
	for (float i = 0; i <= 22050; i++) {

		X = A * ((i / 22050) * (i / 22050)) + B * (i / 10) + C;
		Y = (2 * (X * X)) + 12 * cos(i / 22050);
		Z = sin((2 * 3.14) * 7 * (i / 22050)) * X - 0.2 * log10(abs(Y) + 3.14);
		U = sqrt(abs(Y * Y * Z)) - 1.8 * sin(0.4 * (i / 22050) * Z * X);
		float t = i / 22050;
		if (t < 0.22 && t >= 0) {
			V = (1 - 7 * t) * sin((2 * 3.14 * t * 10) / (t + 0.04));
			zapis5 << i / 22050 << " " << V << endl;
		};
		if (t < 0.7 && t >= 0.22) {
			V = 0.63 * t * sin(125 * t);
			zapis5 << i / 22050 << " " << V << endl;
		};
		if (t < 1 && t >= 0.7) {

			V = 1/(0.662*t)+0.77*sin(8*t);
			zapis5 << i / 22050 << " " << V << endl;
		};
	}
	zapis5.close();
//////////Wyznaczenie p jako wynik////////////////////////
	ofstream zapis6("dane6.txt");
	for (float i = 0; i <= 22050; i++) {
		
		float t = i / 22050;

		for (float N = 1; N <= 2; N++) {
			wynik = wynik + (cos(12 * t * (N * N)) + cos((16 * t) * N))/N*N;
			
		}
		zapis6 << i / 22050 << " " << wynik << endl;
	}
	zapis6 << endl;
	for (float i = 0; i <= 22050; i++) {

		float t = i / 22050;
	
		for (float N = 1; N <= 4; N++) {
			wynik = wynik + (cos(12 * t * (N * N)) + cos((16 * t) * N)) / N * N;

		}
		zapis6 << i / 22050 << " " << wynik << endl;
	}
	zapis6 << endl;
	for (float i = 0; i <= 22050; i++) {

		float t = i / 22050;
		
		for (float N = 1; N <=A*B ; N++) {
			wynik = wynik + (cos(12 * t * (N * N)) + cos((16 * t) * N)) / N * N;

		}
		zapis6 << i / 22050 << " " << wynik << endl;
	}
	zapis6.close();
};
