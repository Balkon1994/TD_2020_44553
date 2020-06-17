
#define _USE_MATH_DEFINES

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <bitset>
#include <iostream>
#include <vector>
#include <complex>
#include <sstream>
#include <time.h>
using namespace std;

double alf = 0.1;

template <typename T>
void draw(T* x, T* y, int ilosc, string napis)
{

	ofstream zapis(napis + ".txt");

	for (int i = 0; i < ilosc; i++)
	{
		zapis << x[i] << " " << y[i] << endl;

	}
	zapis.close();
}


string reverse(string const& s)
{
	string rev;
	for (int i = s.size() - 1; i >= 0; i--) {
		rev = rev.append(1, s[i]);
	};

	return rev;
}

string tobyte(string a) {


	int length = a.length();
	int** tab = new int* [length];
	string bit;

	for (int i = 0; i < length; i++)
	{
		bitset<8> b = (bitset<8>)(int(a[i]));
		string c = b.to_string();
		bit += reverse(c);
	}
	return bit;
}



void reverseStr(string& str)
{
	int n = str.length();

	for (int i = 0; i < n / 2; i++)
		swap(str[i], str[n - i - 1]);
}

string convert(char data, bool reverse = false)
{
	bitset<8> bite = (bitset<8>)(int)data;
	string reverseorder = bite.to_string();
	if (reverse)
	{
		reverseStr(reverseorder);
		return reverseorder;
	}
	return bite.to_string();
}

string Hamming(string data)
{
	int** Matrix = new int* [data.length() * 2];
	int Matrix_tmp = 0;
	for (int k = 0; k < data.length(); k++)
	{
		string bity = convert(data[k], true);

		int G[7][4] = { {1,1,0,1},{1,0,1,1},{1,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
		int H[3][7] = { {1,0,1,0,1,0,1},{0,1,1,0,0,1,1,}, {0,0,0,1,1,1,1} };

		int* m_pakiet1 = new int[7];
		int* m_pakiet2 = new int[7];
		string pakiet1;
		string pakiet2;
		for (int i = 0; i < 4; i++)
		{
			pakiet1 += bity[i];
			pakiet2 += bity[4 + i];
		}

		for (int i = 0; i < 7; i++)
		{
			m_pakiet1[i] = 0;
			m_pakiet2[i] = 0;
		}

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_pakiet1[i] += G[i][j] * pakiet1[j];
				m_pakiet2[i] += G[i][j] * pakiet2[j];

			}
		}
		for (int i = 0; i < 7; i++)
		{
			m_pakiet1[i] = m_pakiet1[i] % 2;
			m_pakiet2[i] = m_pakiet2[i] % 2;
		}

		Matrix[Matrix_tmp++] = m_pakiet1;
		Matrix[Matrix_tmp++] = m_pakiet2;
	}

	string To_ret;

	for (int i = 0; i < data.length() * 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			To_ret.append(to_string(Matrix[i][j]));
		}
	}
	return To_ret;
}
string decoding(string paczki)
{
	int packs = paczki.length() / 7;
	int* pakiety7 = new int[7];
	int* sumy = new int[3];
	string pack4;
	int H[3][7] = { {1,0,1,0,1,0,1},{0,1,1,0,0,1,1,}, {0,0,0,1,1,1,1} };

	for (int i = 0; i < packs; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			pakiety7[j] = paczki[i * 7 + j] - '0';
			
		}
		pakiety7[3] = 1;
		for (int j = 0; j < 3; j++)
		{
			sumy[j] = 0;
			for (int k = 0; k < 7; k++)
			{
				sumy[j] += H[j][k] * pakiety7[k];
				
			}

		}

		int error_place = 0;

		for (int j = 0; j < 3; j++)
		{
			sumy[j] = sumy[j] % 2;
			
			error_place = error_place + pow(2, j) * sumy[j];
		}

		if (error_place != 0)
		{
			
			if (pakiety7[error_place - 1] == 0)
			{
				pakiety7[error_place - 1] = 1;
			}
			else
			{
				pakiety7[error_place - 1] = 0;
			}
		
		}

		pack4.append(to_string(pakiety7[2]));
		pack4.append(to_string(pakiety7[4]));
		pack4.append(to_string(pakiety7[5]));
		pack4.append(to_string(pakiety7[6]));


	}

	

	return pack4;

}
complex<double>* dft(double* tab, int n)
{
	complex<double>* array = new complex<double>[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			array[j] += polar(tab[i], -2 * M_PI * i * j / n);
	return array;
}

double zA(double t, double mt, int N, double tB)
{
	int A0 = 1;
	int A1 = 2;
	int fi = 0;
	double f = (double)N / tB;
	if (mt == 0)
	{
		return (A0 * sin(2 * M_PI * f * t + fi));

	}
	else if (mt == 1)
	{
		return (A1 * sin(2 * M_PI * f * t + fi));

	}

}


double zF(double t, double mt, int N, double tB)
{
	int A = 1;
	double f0 = (double)(N + 1) / tB;
	double f1 = (double)(N + 2) / tB; 
	int fi = 0;

	if (mt == 0)
	{
		return (A * sin(2 * M_PI * f0 * t + fi));
	}
	else if (mt == 1)

		return (A * sin(2 * M_PI * f1 * t + fi));


}

double zP(double t, double mt, int N, double tB)
{
	int A = 1;
	double f = (double)N / tB;
	int fi0 = 0;
	int fi1 = M_PI;

	if (mt == 0)

		return (A * sin(2 * M_PI * f * t + fi0));

	if (mt == 1)

		return (A * sin(2 * M_PI * f * t + fi1));

}

struct signal
{
public:
	int rozmiar;
	double* x;
	double* y;
};


signal sygnal_inf(double Tb, string bit, int freq)
{

	signal tmp;
	int rozmiar = bit.length() * Tb * freq;
	double* x = new double[rozmiar];
	double* y = new double[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		x[i] = (double)i / freq;

	}
	for (int i = 0; i < bit.length(); i++)
	{
		for (int j = i * Tb * freq; j < (i + 1) * Tb * freq; j++)
		{
			y[j] = (double)(bit[i] - '0');
		}

	

	}
	tmp.rozmiar = rozmiar;
	tmp.x = x;
	tmp.y = y;
	return tmp;

};


string strToChar(string str) {
	string parsed = "";
	int kant = 0;
	char suma = 0;
	for (int i = 0; i < str.length() / 8; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			if (str[kant] == '1')
			{
				suma += pow(2, 7 - j);

			}
			kant++;
		}
		parsed += suma;
		suma = 0;
	}

	return parsed;
}
int main()
{
	
	cout <<"ALA MA KOTA "<< tobyte("Ala ma kota") << endl;
	string dane_zabezpieczone = Hamming("Ala ma kota");
	cout << "KOD BINARNY " << dane_zabezpieczone << endl << endl;



	signal tmp = sygnal_inf(0.1, dane_zabezpieczone, 800);

	double* zAA = new double[tmp.rozmiar];
	double* zFF = new double[tmp.rozmiar];
	double* zFF2 = new double[tmp.rozmiar];
	double* zPP = new double[tmp.rozmiar];
	double* x1 = new double[tmp.rozmiar];
	double* x2 = new double[tmp.rozmiar];
	double tb = 0.1 * 800;
	double* konwersja = new double[dane_zabezpieczone.length()];
	double* zAAA = new double[tmp.rozmiar];
	double* zFFF = new double[tmp.rozmiar];
	double* zPPP = new double[tmp.rozmiar];
	double zmiennaA = 0;
	double zmiennaF = 0;
	double zmiennaF2 = 0;
	double zmiennaP = 0;

	double h = .8;
	double h2 = .5;
	double f0 = (double)(1 + 1) / 0.1;
	double f1 = (double)(1 + 2) / 0.1;
	

	for (int i = 0; i < tmp.rozmiar; i++)
	{
		zAA[i] = zA(tmp.x[i], tmp.y[i], 1, 0.1);
		zFF[i] = zF(tmp.x[i], tmp.y[i], 1, 0.1);
		zPP[i] = zP(tmp.x[i], tmp.y[i], 1, 0.1);
	}

	cout << "Podaj nasza alfe? Podstawowa to 0.1" << endl;
	cin >> alf;

	draw(tmp.x, zAA, tmp.rozmiar, "ASK");
	draw(tmp.x, zFF, tmp.rozmiar, "FSK");
	draw(tmp.x, zPP, tmp.rozmiar, "PSK");
	int k;
	cout << "Wybierz jakie widmo chcesz uzyskac" << endl;
	cout << "1 ASK" << endl;
	cout << "2 FSK" << endl;
	cout << "3 PSK" << endl;
	cout << "4 ASK z szumem" << endl;
	cout << "5 FSK z szumem" << endl;
	cout << "6 PSK z szumem" << endl;
	cin >> k;

	switch (k)
	{
		if (k = 1) {
			////zAA 

			complex<double>* wykres = dft(zAA, tmp.rozmiar);
			double* M = new double[tmp.rozmiar];

			for (int i = 0; i < tmp.rozmiar; i++)

			{
				M[i] = sqrt(pow(real(wykres[i]), 2) + pow(imag(wykres[i]), 2));
			}
			double* Ma = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				Ma[i] = 10 * log10(M[i]);
			}
			double* fkcz = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				fkcz[i] = (double)i * 800 / tmp.rozmiar;
				if (Ma[i] < 0)
				{
					Ma[i] = 0;
				}
			}

			draw(fkcz, Ma, tmp.rozmiar, "ASKwidmo");


			break;
		}

		if (k = 2) {
			////zFF

			complex<double>* wykresFF = dft(zFF, tmp.rozmiar);
			double* M = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)

			{
				M[i] = sqrt(pow(real(wykresFF[i]), 2) + pow(imag(wykresFF[i]), 2));
			}
			double* Ma = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				Ma[i] = 10 * log10(M[i]);
			}
			double* fkcz = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				fkcz[i] = (double)i * 800 / tmp.rozmiar;
				if (Ma[i] < 0)
				{
					Ma[i] = 0;
				}
			}

			draw(fkcz, Ma, tmp.rozmiar, "FSKwidmo");

			break;
		}

		if (k = 3) {

			////zPP
			complex<double>* wykresPP = dft(zPP, tmp.rozmiar);
			double* M = new double[tmp.rozmiar];

			for (int i = 0; i < tmp.rozmiar; i++)

			{
				M[i] = sqrt(pow(real(wykresPP[i]), 2) + pow(imag(wykresPP[i]), 2));
			}
			double* Ma = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				Ma[i] = 10 * log10(M[i]);
			}
			double* fkcz = new double[tmp.rozmiar];

			for (int i = 0; i < tmp.rozmiar; i++)
			{
				fkcz[i] = (double)i * 800 / tmp.rozmiar;
				if (Ma[i] < 0)
				{
					Ma[i] = 0;
				}
			}

			draw(fkcz, Ma, tmp.rozmiar, "PSKwidmo");
			break;
		}

		if (k = 4) {
			//SZUM-------------------------------------------------------
			
			double* zA_szum = new double[tmp.rozmiar];
			double* zF_szum = new double[tmp.rozmiar];
			double* zP_szum = new double[tmp.rozmiar];
			srand(time(0));
			const static int q = 15;
			const static float c1 = (1 << q) - 1;
			const static float c2 = ((int)(c1 / 3)) + 1;
			const static float c3 = 1.f / c1;
			float random = 0.f;
			float noise = 0.f;
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				random = ((float)rand() / (float)(RAND_MAX + 1));
				noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * (c3 * 1);

				zA_szum[i] = (zAA[i] * alf) + (noise * (1. - alf));
				zF_szum[i] = (zFF[i] * alf) + (noise * (1. - alf));
				zP_szum[i] = (zPP[i] * alf) + (noise * (1. - alf));
			}
			draw(tmp.x, zA_szum, tmp.rozmiar, "szumASK");
			draw(tmp.x, zF_szum, tmp.rozmiar, "szumFSK");
			draw(tmp.x, zP_szum, tmp.rozmiar, "szumPSK");

			////zAA 

			complex<double>* wykres = dft(zA_szum, tmp.rozmiar);
			double* M = new double[tmp.rozmiar];

			for (int i = 0; i < tmp.rozmiar; i++)

			{
				M[i] = sqrt(pow(real(wykres[i]), 2) + pow(imag(wykres[i]), 2));
			}
			double* Ma = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				Ma[i] = 10 * log10(M[i]);
			}
			double* fkcz = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				fkcz[i] = (double)i * 800 / tmp.rozmiar;
				if (Ma[i] < 0)
				{
					Ma[i] = 0;
				}
			}

			draw(fkcz, Ma, tmp.rozmiar, "ASKwidmoszum"); 

			break;
		}

		if (k = 5) {

			//SZUM-------------------------------------------------------
			
			double* zA_szum = new double[tmp.rozmiar];
			double* zF_szum = new double[tmp.rozmiar];
			double* zP_szum = new double[tmp.rozmiar];
			srand(time(0));
			const static int q = 15;
			const static float c1 = (1 << q) - 1;
			const static float c2 = ((int)(c1 / 3)) + 1;
			const static float c3 = 1.f / c1;
			float random = 0.f;
			float noise = 0.f;
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				random = ((float)rand() / (float)(RAND_MAX + 1));
				noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * (c3 * 1);

				zA_szum[i] = (zAA[i] * alf) + (noise * (1. - alf));
				zF_szum[i] = (zFF[i] * alf) + (noise * (1. - alf));
				zP_szum[i] = (zPP[i] * alf) + (noise * (1. - alf));
			}
			draw(tmp.x, zA_szum, tmp.rozmiar, "szumASK");
			draw(tmp.x, zF_szum, tmp.rozmiar, "szumFSK");
			draw(tmp.x, zP_szum, tmp.rozmiar, "szumPSK");

			////zFF
			complex<double>* wykresFF = dft(zF_szum, tmp.rozmiar);
			double* M = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)

			{
				M[i] = sqrt(pow(real(wykresFF[i]), 2) + pow(imag(wykresFF[i]), 2));
			}
			double* Ma = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				Ma[i] = 10 * log10(M[i]);
			}
			double* fkcz = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				fkcz[i] = (double)i * 800 / tmp.rozmiar;
				if (Ma[i] < 0)
				{
					Ma[i] = 0;
				}
			}

			draw(fkcz, Ma, tmp.rozmiar, "FSKwidmoszum");
			

			break;
		}

		if (k = 6) {

			//SZUM-------------------------------------------------------
			
			double* zA_szum = new double[tmp.rozmiar];
			double* zF_szum = new double[tmp.rozmiar];
			double* zP_szum = new double[tmp.rozmiar];
			srand(time(0));
			const static int q = 15;
			const static float c1 = (1 << q) - 1;
			const static float c2 = ((int)(c1 / 3)) + 1;
			const static float c3 = 1.f / c1;
			float random = 0.f;
			float noise = 0.f;
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				random = ((float)rand() / (float)(RAND_MAX + 1));
				noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * (c3 * 1);

				zA_szum[i] = (zAA[i] * alf) + (noise * (1. - alf));
				zF_szum[i] = (zFF[i] * alf) + (noise * (1. - alf));
				zP_szum[i] = (zPP[i] * alf) + (noise * (1. - alf));
			}
			draw(tmp.x, zA_szum, tmp.rozmiar, "szumASK");
			draw(tmp.x, zF_szum, tmp.rozmiar, "szumFSK");
			draw(tmp.x, zP_szum, tmp.rozmiar, "szumPSK");

			////zPP
			complex<double>* wykresPP = dft(zP_szum, tmp.rozmiar);
			double* M = new double[tmp.rozmiar];

			for (int i = 0; i < tmp.rozmiar; i++)

			{
				M[i] = sqrt(pow(real(wykresPP[i]), 2) + pow(imag(wykresPP[i]), 2));
			}
			double* Ma = new double[tmp.rozmiar];
			for (int i = 0; i < tmp.rozmiar; i++)
			{
				Ma[i] = 10 * log10(M[i]);
			}
			double* fkcz = new double[tmp.rozmiar];

			for (int i = 0; i < tmp.rozmiar; i++)
			{
				fkcz[i] = (double)i * 800 / tmp.rozmiar;
				if (Ma[i] < 0)
				{
					Ma[i] = 0;
				}
			}

			draw(fkcz, Ma, tmp.rozmiar, "PSKwidmoszum");
			break;
		}

	}


	
	//SZUM-------------------------------------------------------

	double* zA_szum = new double[tmp.rozmiar];
	double* zF_szum = new double[tmp.rozmiar];
	double* zP_szum = new double[tmp.rozmiar];
	srand(time(0));
	const static int q = 15;
	const static float c1 = (1 << q) - 1;
	const static float c2 = ((int)(c1 / 3)) + 1;
	const static float c3 = 1.f / c1;
	float random = 0.f;
	float noise = 0.f;
	for (int i = 0; i < tmp.rozmiar; i++)
	{
		random = ((float)rand() / (float)(RAND_MAX + 1));
		noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * (c3 * 1);

		zA_szum[i] = (zAA[i] * alf) + (noise * (1. - alf));
		zF_szum[i] = (zFF[i] * alf) + (noise * (1. - alf));
		zP_szum[i] = (zPP[i] * alf) + (noise * (1. - alf));
	}
	draw(tmp.x, zA_szum, tmp.rozmiar, "szumASK");
	draw(tmp.x, zF_szum, tmp.rozmiar, "szumFSK");
	draw(tmp.x, zP_szum, tmp.rozmiar, "szumPSK");

	///DEMODULACJA-------------------------------------------


	for (int i = 0; i < tmp.rozmiar; i++)
	{
		x1[i] = zF_szum[i] * 1 * sin(2 * M_PI * f0 * tmp.x[i] + 0);
		x2[i] = zF_szum[i] * 1 * sin(2 * M_PI * f1 * tmp.x[i] + 0);
	}


	for (int i = 0; i < dane_zabezpieczone.length(); i++)
	{
		zmiennaA = 0;
		zmiennaF = 0;
		zmiennaP = 0;
		for (int j = i * tb; j < (i + 1) * tb; j++)
		{
			zmiennaA += zA_szum[j];
			zAAA[j] = zmiennaA;
			zmiennaF += x1[j] - x2[j];
			zFFF[j] = zmiennaF;
			zmiennaP += zP_szum[j];
			zPPP[j] = zmiennaP;
		}
	}

	draw(tmp.x, zAAA, tmp.rozmiar, "zAAcalka");
	draw(tmp.x, zFFF, tmp.rozmiar, "zFFcalka");
	draw(tmp.x, zPPP, tmp.rozmiar, "zPPcalka");


	for (int i = 0; i < dane_zabezpieczone.length(); i++)
	{
		for (int j = i * tb; j < (i + 1) * tb; j++)
		{

			if (zAAA[j] > 30 * alf)
			{
				zAAA[j] = 1;
			}
			else
			{
				zAAA[j] = 0;
			}
		}
		zmiennaA = 0;
	}
	string bit_ask;
	for (int i = 0; i < dane_zabezpieczone.length(); i++)
	{
		int index = i * tb + 52;
		bit_ask.append(to_string((int)zAAA[index]));
	}
	//cout << bit_ask << endl;


	draw(tmp.x, zAAA, tmp.rozmiar, "zAAAcalka");

	for (int i = 0; i < dane_zabezpieczone.length(); i++)
	{
		for (int j = i * tb; j < (i + 1) * tb; j++)
		{

			if (zFFF[j] > 0.5)
			{
				zFFF[j] = 0;
			}
			else
				zFFF[j] = 1;
		}
		zmiennaF = 0;
	}
	draw(tmp.x, zFFF, tmp.rozmiar, "zFFFcalka");

	string bit_fsk;
	for (int i = 0; i < dane_zabezpieczone.length(); i++)
	{
		int index = i * tb + 52;
		bit_fsk.append(to_string((int)zFFF[index]));
	}

	for (int i = 0; i < dane_zabezpieczone.length(); i++)
	{
		for (int j = i * tb; j < (i + 1) * tb; j++)
		{
			if (zPPP[j] > 1)
			{
				zPPP[j] = 0;
			}
			else
				zPPP[j] = 1;
		}
		zmiennaP = 0;
	}
	draw(tmp.x, zPPP, tmp.rozmiar, "zPPPcalka");

	string bit_psk;
	for (int i = 0; i < dane_zabezpieczone.length(); i++)
	{
		int index = i * tb + 52;
		bit_psk.append(to_string((int)zPPP[index]));
	}

	cout << "ASK" << endl;
	cout << bit_ask << endl;
	cout << "FSK" << endl;
	cout << bit_fsk << endl;
	cout << "PSK" << endl;
	cout << bit_psk << endl;

	string dane_odebrane = decoding(bit_ask);
	string dane_odebrane1 = decoding(bit_fsk);
	string dane_odebrane2 = decoding(bit_psk);

	cout << "Napis po ASK" << endl;
	cout << dane_odebrane << endl;
	cout << strToChar(dane_odebrane) << endl;

	cout << "Napis po FSK" << endl;
	cout << dane_odebrane1 << endl;
	cout << strToChar(dane_odebrane1) << endl;

	cout << "Napis po PSK" << endl;
	cout << dane_odebrane2 << endl;
	cout << strToChar(dane_odebrane2);
	int BERask = 0;
	int BERfsk = 0;
	int BERpsk = 0;
	string bera = tobyte("Ala ma kota");


	for (int i = 0; i < bera.length(); i++)
	{
		if (dane_zabezpieczone[i] != dane_odebrane[i])
		{
			BERask++;
		}
	}
	for (int i = 0; i < bera.length(); i++)
	{
		if (dane_zabezpieczone[i] != dane_odebrane1[i])
		{
			BERfsk++;
		}
	}
	for (int i = 0; i < bera.length(); i++)
	{
		if (dane_zabezpieczone[i] != dane_odebrane2[i])
		{
			BERpsk++;
		}
	}
	cout << endl;
	cout << "BER dla ASK: " << BERask << endl;
	cout << "BER dla FSK: " << BERfsk<< endl;
	cout << "BER dla PSK: " << BERpsk << endl;

}

