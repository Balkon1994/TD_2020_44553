#include <iostream>
#include<fstream>
#include<math.h>

const int N = 553;
using namespace std;
float X; //Wszystkie zmienne, które s¹ wynikami lub elementami funkcji z zadania 1
float Y;
float Z;
float U;
float V;
float P1;
float P2;
float P3;

float A = 5; //Ustawienie A,B,C po indeksie
float B = 5;
float C = 3;
float Pi = 3.141592653589793238462643383279; //Ustawienie liczny Pi
float fs = 1000;//Czêstotliwoœæ
float fs1 = 1000;//Czêstotliowœæ do wykresów z zadania 2


float TAB[N]; //Tablica dla wartoœci funkcji  
float TAB2[N]; //Tablice wyników po OdwrotnymDFT
float TAB3[N]; // Tablica po urojonych wartosæiach po odwrtonymDFT
float PR[N]; //Tablica realnych wartoœæi po DFT
float PI[N]; // Tablica urojonych wartoœci po DFT


float M[N]; //Tablica wartoœæi M[k]
float Mi[N]; //Tablica wartoœci Mi[k]
float f[N];

void TonProsty(int N,float fs,float A, float B, float C, float TAB[]) {
	ofstream zapis2("dane1.txt");
	for (float i = 0; i < N; i++) {
		int k = i;
		Y = sin((2 * Pi) * (B * (i * 1 / fs)) + +(Pi * C));
		TAB[k] = Y;
		zapis2 << (i * 1 / fs) << " " << Y << endl;
	
	};
	zapis2.close();
}

void DFT(float TAB[], int N) {
	for (int i = 0; i < N; i++) {

		PR[0] += TAB[i] * cos(-2 * (Pi * 1 * i) / N);
		PI[0] += TAB[i] * sin(-2 * (Pi * 1 * i) / N);

	}
	for (int k = 1; k <= N; k++) {
		for (int i = 0; i < N; i++) {

			PR[k] += TAB[i] * cos(-2 * (Pi * k * i) / N);
			PI[k] += TAB[i] * sin(-2 * (Pi * k * i) / N);

		}

	};
}

void OdwrotnyDFT(float TAB[],float TAB2[], int N) {
	ofstream zapisIDFT("dane_IDFT.txt");
	for (int k = 1; k <= N; k++) {
		for (int i = 0; i < N; i++) {

			TAB[k] += PR[i] * cos(2 * (Pi * k * i) / N);
			TAB2[k] += PI[i] * sin(2 * (Pi * k * i) / N);

		}
		TAB[k] = TAB[k] / N;
		
		TAB2[k] = TAB2[k] / N;
		zapisIDFT<< TAB[k] << " " << TAB2[k] << endl;
	};
	zapisIDFT.close();
}
//wykres X
void WyprowadzenieX(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		X = A * ((i / fs) * (i / fs)) + B * (i / fs) + C;
		TAB[k] = X;

	}
}
//wykres Y
void WyprowadzenieY(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		X = A * ((i / fs) * (i / fs)) + B * (i / fs) + C;
		Y = (2 * (X * X)) + 12 * cos(i / fs);
		TAB[k] = Y;

	}
}
//wykres Z
void WyprowadzenieZ(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		X = A * ((i / fs) * (i / fs)) + B * (i / fs) + C;
		Y = (2 * (X * X)) + 12 * cos(i / fs);
		Z = sin((2 * Pi) * 7 * (i / fs)) * X - 0.2 * log10(abs(Y) + Pi);
		TAB[k] = Z;

	}
}
//wykres U
void WyprowadzenieU(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		X = A * ((i / fs) * (i/fs)) + B * (i/fs) + C;
		Y = (2 * (X * X)) + 12 * cos(i /fs);
		Z = sin((2 * Pi) * 7 * (i / fs)) * X - 0.2 * log10(abs(Y) + 3.14);
		U = sqrt(abs(Y * Y * Z)) - 1.8 * sin(0.4 * (i / fs) * Z * X);
		TAB[k] = U;

	}
}
//wykresV
void WyprowadzenieV(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		X = A * ((i / fs) * (i / fs)) + B * (i / fs) + C;
		Y = (2 * (X * X)) + 12 * cos(i / fs);
		Z = sin((2 * 3.14) * 7 * (i / fs)) * X - 0.2 * log10(abs(Y) + 3.14);
		U = sqrt(abs(Y * Y * Z)) - 1.8 * sin(0.4 * (i / fs) * Z * X);
		float t = i / fs;
		if (t < 0.22 && t >= 0) {
			V = (1 - 7 * t) * sin((2 * 3.14 * t * 10) / (t + 0.04));
			TAB[k] = V;
		};
		if (t < 0.7 && t >= 0.22) {
			V = 0.63 * t * sin(125 * t);
			TAB[k] = V; 
		};
		if (t < 1 && t >= 0.7) {

			V = 1 / (0.662 * t) + 0.77 * sin(8 * t);
			TAB[k] = V;
		};
	

	}
}
//wykresP1
void WyprowadzenieP1(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		float t = i / fs;

		for (float Ni = 1; Ni <= 2; Ni++) {
			P1 = P1 + (cos(12 * t * (Ni * Ni)) + cos((16 * t) * Ni)) / Ni * Ni;

		}
		TAB[k] = P1;

	}
}
//wykresP2
void WyprowadzenieP2(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		float t = i / fs;

		for (float Ni = 1; Ni <= 4; Ni++) {
			P2 = P2 + (cos(12 * t * (Ni * Ni)) + cos((16 * t) * Ni)) / Ni * Ni;

		}
		TAB[k] = P2;

	}
}
//wykresP3
void WyprowadzenieP3(int N,float fs, float TAB[]) {
	for (float i = 0; i <= N; i++) {
		int k = i;
		float t = i / fs;

		for (float Ni = 1; Ni <= A*B; Ni++) {
			P3 = P3 + (cos(12 * t * (Ni * Ni)) + cos((16 * t) * Ni)) / Ni * Ni;

		}
		TAB[k] = P3;

	}
}

int main() 
{
	//DFT dla tonu prostego
	TonProsty(N,fs,A, B, C, TAB);
	DFT(TAB, N);
	OdwrotnyDFT(TAB2, TAB3, N);//Odwrotne DFT wyniki s¹ w pliki zapisIDFT


	ofstream zapis("dane1.txt");
	
	for (int k = 0; k < N; k++) {
	
		
		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k*(fs))/N;
		
		
		
		zapis << f[k] << " " << Mi[k] << endl;
		
	};
	zapis.close();
	

	WyprowadzenieX(N,fs1, TAB);
	DFT(TAB, N);//DFT dla X

	ofstream zapis2("dane2.txt");
	
	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis2 << f[k] << " " << Mi[k] << endl;
		



	};
	zapis2.close();




	WyprowadzenieY(N, fs1, TAB);
	DFT(TAB, N);//DFT dla Y

	ofstream zapis3("dane3.txt");
	
	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis3 << f[k] << " " << Mi[k] << endl;
	



	};
	zapis3.close();



	WyprowadzenieZ(N, fs1, TAB);
	DFT(TAB, N);//DFT dla Z

	ofstream zapis4("dane4.txt");
	
	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis4 << f[k] << " " << Mi[k] << endl;
	



	};
	zapis4.close();
	

	WyprowadzenieU(N, fs1, TAB);
	DFT(TAB, N);//DFT dla U

	ofstream zapis5("dane5.txt");
	
	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis5 << f[k] << " " << Mi[k] << endl;
	



	};
	zapis5.close();


	WyprowadzenieV(N, fs1, TAB);
	DFT(TAB, N);//DFT dla V

	ofstream zapis6("dane6.txt");
	
	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis6<< f[k] << " " << Mi[k] << endl;
	



	};
	zapis6.close();
	

	WyprowadzenieP1(N, fs1, TAB);
	DFT(TAB, N);//DFT dla P1

	ofstream zapis7("dane7.txt");
	
	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis7 << f[k] << " " << Mi[k] << endl;
	



	};
	zapis7.close();
	


	WyprowadzenieP2(N, fs1, TAB);
	DFT(TAB, N);//DFT dla P2

	ofstream zapis8("dane8.txt");

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis8 << f[k] << " " << Mi[k] << endl;
	



	};
	zapis8.close();



	WyprowadzenieP3(N, fs1, TAB);
	DFT(TAB, N);//DFT dla P3

	ofstream zapis9("dane9.txt");

	for (int k = 0; k < N; k++) {


		M[k] = sqrt((PR[k] * PR[k]) + (PI[k] * PI[k]));

		Mi[k] = 10 * (log10(M[k]));
		f[k] = (k * (fs)) / N;



		zapis9 << f[k] << " " << Mi[k] << endl;
		



	};
	zapis9.close();


	
};