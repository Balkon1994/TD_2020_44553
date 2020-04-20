#include <iostream>
#include<fstream>
#include<math.h>

const int N = 5000; //N dla Za
const int N2 = 5000; //N dla Zp
using namespace std;

float P;

float A = 5; //Ustawienie A,B,C po indeksie
float B = 5;
float C = 3;
float Pi = 3.141592653589793238462643383279; //Ustawienie liczny Pi
float Am = 4; //Amplituda 
float fs = 5000;//Czêstotliwoœæ
float fn2 = 800;
float fn = 800;//Czêstotliowœæ 2


float TAB[N]; //Tablica dla wartoœci funkcji  
float PR[N]; //Tablica realnych wartoœci po DFT
float PI[N]; // Tablica odwrotnych wartoœci po DFT
float ZA1[N]; //Tablica po ZA
float ZP1[N]; 
float ZA2[N]; 
float ZP2[N]; 
float ZA3[N]; 
float ZP3[N]; 
double width[7]; //Tablica szerokoœci pasma



float M[N]; //Tablica wartoœæi M[k]
float Mi[N]; //Tablica wartoœci Mi[k]
float f[N]; //Tablica wartoœci Fk

void DFT(float TAB[], int N) {
	for (int i = 0; i < N; i++) {

		PR[0] += TAB[i] * cos(2 * (Pi * 1 * i) / N);
		PI[0] += TAB[i] * sin(2 * (Pi * 1 * i) / N);
		
	}
	PR[0] = PR[0] / N;
	PI[0] = PI[0] / N;
	for (int k = 1; k <= N; k++) {
		for (int i = 0; i < N; i++) {

			PR[k] += TAB[i] * cos(2 * (Pi * k * i)/N);
			PI[k] += TAB[i] * sin(2 * (Pi * k * i)/N);

		}
		PR[k] = PR[k] / N;
		PI[k] = PI[k] / N;


	};
}

void WyprowadzenieP(int N, float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		float t = ((i *Am)/ fs);

		for (float Ni = 1; Ni <= 4; Ni++) {
			P = P + (cos(12 * t * (Ni * Ni)) + cos((16 * t) * Ni)) / (Ni * Ni);

		}
		TAB[k]= P;

	}
}


void WyprowadzeniaZA(float N,float K, float fn,float ZA[], float TAB[] ) {
	
	for (int i = 0; i <= N; i++) {
		float t = ((i * Am) / fs);
		ZA[i] = (K * TAB[i] + 1) * cos(2 * Pi *t *fn);
	}
}

void WyprowadzeniaZP(float N, float K, float fn, float ZP[], float TAB[]) {
	for (int i = 0; i <= N; i++) {
		float t = ((i * Am) / fs);
		ZP[i] = cos(2 * Pi *(fn*(1/fs)) + (K * TAB[i]));
	}
}
double min(float M[], float f[], int N) //Funkcja min
{
	float min = M[N / 2];

	for (int i = 0; i < N/2; i++)
	{
		if (M[i] >= -3 && M[i] != 0)
		{
			if (M[i] < min)
			{
				min = f[i];
			}
		}
	}

	return min;
}
double max(float M[], float f[], int N) //Funkcja max
{
	float max = M[0];

	for (int i = 0; i < N/2 ; i++)
	{
		if (M[i] >= -3 && M[i] != 0)
		{
			if (M[i] > max)
			{
				max = f[i];
			}
		}
	}

	return max;
}

int main() {
	WyprowadzenieP(N, fs, TAB); //Wypisanie wartoœci po P
	ofstream zapisP("daneP.txt");
	for (int i = 0; i <= N; i++) {
		zapisP << (i*Am/N) << " " << TAB[i] << endl;
	}
	zapisP.close();

	WyprowadzeniaZA(N, 0.5, fn, ZA1, TAB); //Wypisanie wartoœci po ZA1
	ofstream zapisZA1("daneZA1.txt");
	for (int i = 0; i <= N; i++) {
		zapisZA1 << (i * Am / N) << " " << ZA1[i] << endl;
	}
	zapisZA1.close();
	WyprowadzeniaZA(N, 6, fn, ZA2, TAB);
	ofstream zapisZA2("daneZA2.txt"); //Wypisanie wartoœci po ZA2
	for (int i = 0; i <= N; i++) {
		zapisZA2 << (i * Am / N) << " " << ZA2[i] <<endl;
	}
	zapisZA2.close();
	WyprowadzeniaZA(N, 30, fn, ZA3, TAB); //Wypisanie wartoœci po ZA3
	ofstream zapisZA3("daneZA3.txt");
	for (int i = 0; i <= N; i++) {
		zapisZA3 << (i * Am / N) << " " << ZA3[i]<< endl;
	}
	zapisZA3.close();
	WyprowadzeniaZP(N, 1, fn, ZP1, TAB); //Wypisanie wartoœci po ZP1
	ofstream zapisZP1("daneZP1.txt");
	for (int i = 0; i <= N2; i++) {
		zapisZP1 << (i * Am / N) << " " << ZP1[i]<< endl;
	}
	zapisZP1.close();
	WyprowadzeniaZP(N, 2.5, fn, ZP2, TAB); //Wypisanie wartoœci po ZP2
	ofstream zapisZP2("daneZP2.txt");
	for (int i = 0; i <= N2; i++) {
		zapisZP2 << (i * Am / N) << " " << ZP2[i]<< endl;
	}
	zapisZP2.close();
	WyprowadzeniaZP(N, 30, fn, ZP3, TAB); //Wypisanie wartoœci po ZP3
	ofstream zapisZP3("daneZP3.txt");
	for (int i = 0; i <= N2; i++) {
		zapisZP3 << (i * Am / N) << " " << ZP3[i]<< endl;
	}
	zapisZP3.close();
	
	DFT(TAB, N);
	ofstream zapisPDFT("danePDFT.txt"); //Wypisanie wartoœci widma dla P

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapisPDFT << f[k] << " " << Mi[k] << endl;




	};
	
	width[0] = max(Mi, f, N) - min(Mi, f, N);
	zapisPDFT.close();

	DFT(ZP1, N);
	ofstream zapisZPDFT1("daneZPDFT1.txt"); //Wypisanie wartoœci widma dla ZP1

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapisZPDFT1 << f[k] << " " << Mi[k] << endl;




	};
	width[4] = max(Mi, f, N) - min(Mi, f, N);
	zapisZPDFT1.close();

	DFT(ZP2, N);
	ofstream zapisZPDFT2("daneZPDFT2.txt"); //Wypisanie wartoœci widma dla ZP2

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapisZPDFT2 << f[k] << " " << Mi[k] << endl;




	};
	width[5] = max(Mi, f, N) - min(Mi, f, N);
	zapisZPDFT2.close();

	DFT(ZP3, N);
	ofstream zapisZPDFT3("daneZPDFT3.txt"); //Wypisanie wartoœci widma dla ZP3

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapisZPDFT3 << f[k] << " " << Mi[k] << endl;




	};
	width[6] = max(Mi, f, N) - min(Mi, f, N);
	zapisZPDFT3.close();


	DFT(ZA1, N);
	ofstream zapisZADFT1("daneZADFT1.txt"); //Wypisanie wartoœci widma dla ZA1

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapisZADFT1 << f[k] << " " << M[k] << endl;




	};
	width[1] = max(Mi, f, N) - min(Mi, f, N);
	zapisZADFT1.close();

	DFT(ZA2, N);
	ofstream zapisZADFT2("daneZADFT2.txt"); //Wypisanie wartoœci widma dla ZA2

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapisZADFT2 << f[k] << " " << Mi[k] << endl;




	};
	width[2] = max(Mi, f, N) - min(Mi, f, N);
	zapisZADFT2.close();

	DFT(ZA3, N);
	ofstream zapisZADFT3("daneZADFT3.txt"); //Wypisanie wartoœci widma dla ZA3

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapisZADFT3 << f[k] << " " << Mi[k] << endl;




	};
	width[3] = max(Mi, f, N) - min(Mi, f, N); 
	zapisZADFT3.close();

	
	cout << "Szerokosci pasm W:" << endl;
	ofstream zapisW("daneW.txt"); //Otwarcie zapisu szerokoœci 
	for (int j = 0; j < 7; j++) {
		zapisW << width[j] << endl; 
	};
	zapisW.close();
	/* Szerokoœci:
69.0837
2287
124.292
545.558
119.302
2213
*/
};