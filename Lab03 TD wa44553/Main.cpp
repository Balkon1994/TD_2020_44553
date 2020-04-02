#include <iostream>
#include<fstream>
#include<math.h>

using namespace std;
float X;
float Y;

float A = 5;
float B = 5;
float C = 3;


int N = 553;
float TAB[1000];
float PR[553];
float PI[553];


float M[553];
float Mi[553];
float f[553];

void TonProsty(int N,float A, float B, float C, float TAB[]) {
	ofstream zapis2("dane1.txt");
	for (float i = 0; i < N; i++) {
		int k = i;
		Y = sin((2 * 3.14) * (5 * (i * 1 / 1000)) + +(3.14 * C));
		TAB[k] = Y;
		zapis2 << (i * 1 / 1000) << " " << Y << endl;
	
	};
	zapis2.close();
}

void DFT(float TAB[], int N) {

	for (int k = 1; k <= 553; k++) {
		for (int i = 0; i < 553; i++) {

			PR[k - 1] += TAB[i] * cos(-2 * (3.14 * k * i) / N);
			PI[k - 1] += TAB[i] * sin(-2 * (3.14 * k * i) / N);

		}

	};
}


int main() 
{

	TonProsty(N,A, B, C, TAB);
	DFT(TAB, N);

	ofstream zapis("dane.txt");
	ofstream zapis2("dane2.txt");
	for (int k = 0; k < N; k++) {
	
		
		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k*((1/0.553)));
		
		
		
		zapis << f[k] << " " << Mi[k] << endl;
		zapis2 << f[k] << " " << M[k] << endl;

		
		
	};
	zapis.close();
	zapis2.close();




};