#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<bool> Hamming;

int S = 40;

int A1 = 0;
int A2 = 1;
float Tb = 0.1;
float N = 4;
float f = N * (1 / Tb);
float f1 = 10;
float f2 = 20;
vector<int>m;
vector<float>t;
vector<float> sygnosnyza;
vector<float> sygnosnyzp;
vector<float> sygnosnyzf0;
vector<float> sygnosnyzf1;
vector<float> zaa;
vector<float> zff;
vector<float> zpp;

vector<int>demodulacja_1;
vector<int>demodulacja_2;
vector<int>demodulacja_3;

vector<int>demodulacja_1_Ham;
vector<int>demodulacja_2_Ham;
vector<int>demodulacja_3_Ham;

vector<int>d;
vector<int>d2;
vector<int>d3;



vector<bool> S2BS(char in[], int swicz, int length)  //String To Binary Stream 
{

	vector<bool> vec;
	//little endian
	if (swicz == 0)
	{

		cout << "Little Endian:" << endl;
		for (int j = 0; j < length; j++)
		{
			int bits[8], i;
			for (i = 0; i < 8; i++)
				bits[i] = ((1 << i) & in[j]) != 0 ? 1 : 0;
			for (i = 7; i >= 0; i--)
			{
				cout << bits[i];
				vec.push_back(bits[i]);
			}
			cout << " ";
		}
	}
	else
	{
		cout << "Big Endian" << endl;
		for (int j = 0; j < length; j++)
		{
			int bits[8], i;
			for (i = 0; i < 8; i++)
			{
				bits[i] = ((1 << i) & in[j]) != 0 ? 1 : 0;
				cout << bits[i];
				vec.push_back(bits[i]);
			}
			cout << " ";

		}
	}
	return vec;
}

void Hamm(vector<bool> vec, int pakiet) //FUNCKCJA GENERUJACA KOD HAMMINGA
{
	int d[4];
	if (pakiet == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			d[i] = vec[i];
		}
	}
	else
	{
		int n = 0;
		for (int i = 4; i < 8; i++)
		{
			d[n] = vec[i];
			n++;
		}
	}

	Hamming.push_back((d[0] + d[1] + d[3]) % 2);
	Hamming.push_back((d[0] + d[2] + d[3]) % 2);
	Hamming.push_back(d[0]);
	Hamming.push_back((d[1] + d[2] + d[3]) % 2);
	Hamming.push_back(d[1]);
	Hamming.push_back(d[2]);
	Hamming.push_back(d[3]);
}

void Negacja(vector<int>& vec, int index) //NEGACJA JEDNEGO BITU
{
	vec[index - 1] = !vec[index - 1];
}

void Dekoder(vector<int> vec) //DEKODER KODU HAMMINGA
{
	
	int p1 = (vec[0] + vec[2] + vec[4] + vec[6]) % 2;
	int p2 = (vec[1] + vec[2] + vec[5] + vec[6]) % 2;
	int p3 = (vec[3] + vec[4] + vec[5] + vec[6]) % 2;
	int n = p1 + p2 * 2 + p3 * 4;
	if (n > 0)
	{
		cout << "blad na pozycji: " << n << endl;
		Negacja(vec, n);
	}
	d.push_back(vec[2]);
	d.push_back(vec[4]);
	d.push_back(vec[5]);
	d.push_back(vec[6]);
	
}

void Dekoder2(vector<int> vec) //DEKODER KODU HAMMINGA
{

	int p1 = (vec[0] + vec[2] + vec[4] + vec[6]) % 2;
	int p2 = (vec[1] + vec[2] + vec[5] + vec[6]) % 2;
	int p3 = (vec[3] + vec[4] + vec[5] + vec[6]) % 2;
	int n = p1 + p2 * 2 + p3 * 4;
	if (n > 0)
	{
		cout << "blad na pozycji: " << n << endl;
		Negacja(vec, n);
	}
	d2.push_back(vec[2]);
	d2.push_back(vec[4]);
	d2.push_back(vec[5]);
	d2.push_back(vec[6]);

}

void Dekoder3(vector<int> vec) //DEKODER KODU HAMMINGA
{

	int p1 = (vec[0] + vec[2] + vec[4] + vec[6]) % 2;
	int p2 = (vec[1] + vec[2] + vec[5] + vec[6]) % 2;
	int p3 = (vec[3] + vec[4] + vec[5] + vec[6]) % 2;
	int n = p1 + p2 * 2 + p3 * 4;
	if (n > 0)
	{
		cout << "blad na pozycji: " << n << endl;
		Negacja(vec, n);
	}
	d3.push_back(vec[2]);
	d3.push_back(vec[4]);
	d3.push_back(vec[5]);
	d3.push_back(vec[6]);

}

void BS2S(vector<int> in) //BINARY TO STRING 
{
	int a1 = in[0];
	int a2 = in[1];
	int a3 = in[2];
	int a4 = in[3];
	int a5 = in[4];
	int a6 = in[5];
	int a7 = in[6];
	int a8 = in[7];
	int suma = (1 * a1) + (2 * a2) + (4 * a3) + (8 * a4) + (16 * a5) + (32 * a6) + (64 * a7) + (128 * a8);
	char litera = suma;
	cout << litera;
}

void za(int swicz)
{
	ofstream file("za.txt");
	for (int i = 0; i < m.size(); i++)
	{
		if (m[i] == 0)
			zaa.push_back(A1 * sin(2 * M_PI * f * t[i]));

		else
			zaa.push_back(A2 * sin(2 * M_PI * f * t[i]));
		sygnosnyza.push_back(A2 * sin(2 * M_PI * f * t[i]));
		file << t[i] << " " << zaa[i] << endl;
		
	}
	file.close();

}

void zf(int swicz)
{
	ofstream file("zf.txt");
	for (int i = 0; i < m.size(); i++)
	{
		if (m[i] == 0)
			zff.push_back(A2 * sin(2 * M_PI * f1 * t[i]));
		else
			zff.push_back(A2 * sin(2 * M_PI * f2 * t[i]));

		sygnosnyzf0.push_back(A2 * sin(2 * M_PI * f1 * t[i]));
		sygnosnyzf1.push_back(A2 * sin(2 * M_PI * f2 * t[i]));

		file << t[i] << " " << zff[i] << endl;
		
	}
	file.close();
}

void zp(int swicz)
{
	ofstream file("zp.txt");
	for (int i = 0; i < m.size(); i++)
	{
		if (m[i] == 0)
			zpp.push_back(A2 * sin(2 * M_PI * f * t[i]));
		else
			zpp.push_back(A2 * sin(2 * M_PI * f * t[i] + M_PI));

		sygnosnyzp.push_back(A2 * sin(2 * M_PI * f * t[i] + M_PI));

		file << t[i] << " " << zpp[i] << endl;
		
	}
	file.close();
}

vector<int> demodulacja(vector<float> func, vector<float> sinfo, float h)
{
	//mnozenie
	ofstream plik1("xt.txt");
	vector<float> funcxsinfo;
	for (int i = 0; i < func.size(); i++)
	{
		funcxsinfo.push_back(func[i] * sinfo[i]);
		plik1 << t[i] << " " << funcxsinfo[i] << endl;
	}
	plik1.close();
	//wyliczenie calki
	ofstream plik2("calka.txt");
	float suma = 0;
	vector<double> calka;
	for (int i = 0; i < funcxsinfo.size(); i++)
	{
		if (i % S == 0)
		{
			suma = 0;
		}
		suma = suma + funcxsinfo[i];
		calka.push_back(suma);
		plik2 << t[i] << " " << calka[i] << endl;
	}
	plik2.close();

	//sygnm
	vector<int> mpodem;
	ofstream plik3("m.txt");
	{
		for (int i = 0; i < calka.size(); i++)
		{

			if (calka[i] > h)
				mpodem.push_back(1);
			else if ((i != calka.size() - 1) && (calka[i + 1] > h))
				mpodem.push_back(1);
			else
				mpodem.push_back(0);
			plik3 << t[i] << " " << mpodem[i] << endl;
		}
	}

	return mpodem;
}

vector<int> demodulacja2(vector<float> func, vector<float> sinfo0, vector<float> sinfo1, float h)
{
	//mnozenie
	ofstream plik1("xt20.txt");
	vector<float> funcxsinfo0;
	vector<float> funcxsinfo1;
	for (int i = 0; i < func.size(); i++)
	{
		funcxsinfo0.push_back(func[i] * sinfo0[i]);
		plik1 << t[i] << " " << funcxsinfo0[i] << endl;
	}


	ofstream plik2("xt21.txt");
	for (int i = 0; i < func.size(); i++)
	{
		funcxsinfo1.push_back(func[i] * sinfo1[i]);
		plik2 << t[i] << " " << funcxsinfo1[i] << endl;
	}
	plik2.close();

	//wyliczenie calki
	vector<double> calka0;
	vector<double> calka1;
	ofstream plik3("calka20.txt");
	float suma = 0;
	for (int i = 0; i < funcxsinfo0.size(); i++)
	{
		if (i % S == 0)
		{
			suma = 0;
		}
		suma = suma + funcxsinfo0[i];
		calka0.push_back(suma);
		plik3 << t[i] << " " << calka0[i] << endl;
	}
	plik3.close();


	ofstream plik4("calka21.txt");
	suma = 0;
	for (int i = 0; i < funcxsinfo1.size(); i++)
	{
		if (i % S == 0)
		{
			suma = 0;
		}
		suma = suma + funcxsinfo1[i];
		calka1.push_back(suma);
		plik4 << t[i] << " " << calka1[i] << endl;
	}
	plik4.close();

	//roznica calek
	vector<double> roznica;
	ofstream plik5("roznica.txt");
	for (int i = 0; i < calka1.size(); i++)
	{
		roznica.push_back(calka1[i] - calka0[i]);
		plik5 << t[i] << " " << roznica[i] << endl;
	}

	//sygnm
	vector<int> mpodem;
	ofstream plik6("m20.txt");
	{
		for (int i = 0; i < roznica.size(); i++)
		{
			
			if(roznica[i] > 19.999) {
				mpodem.push_back(1);
				
			}
			else if (roznica[i] < -20.4) {
				mpodem.push_back(0);
			}
			
			/*
			if (roznica[i] > 0)
				mpodem.push_back(1);
			else if ((i != roznica.size() - 1) && (roznica[i + 1] > h))
				mpodem.push_back(1);
			else
				mpodem.push_back(0);
			plik6 << t[i] << " " << mpodem[i] << endl;
			*/
		}
	}
	plik6.close();

	return mpodem;
}

int main()
{
	//S2BS
	char tab[] = "ALA MA KOTA";
	cout << tab;
	cout << endl;
	int length = sizeof(tab) - 1;
	auto BinaryVector = S2BS(tab, 1, length);
	cout << endl;

	for (int i = 0; i < BinaryVector.size() / 8; i++)
	{
		vector<bool> bit;
		for (int j = 0; j < 8; j++)
		{
			bit.push_back(BinaryVector[j + (i * 8)]);
		}
		Hamm(bit, 0);
		Hamm(bit, 1);
	}
	cout << "Kod Hamminga:" << endl;
	for (int i = 0; i < Hamming.size(); i++)
		cout << Hamming[i];
	cout << endl;

	for (int i = 0; i < BinaryVector.size(); i++) {
		BinaryVector[i] = Hamming[i];
	}
	for (int i = BinaryVector.size(); i < Hamming.size(); i++) {
		BinaryVector.push_back(Hamming[i]);
	}

	ofstream file1("sinfo.txt");
	float t0 = 0;
	float dt = (1.0 / 200);
	float time = t0;
	float n = 0;
	//sygnal informacyjny
	int stop = 1;
	for (int i = 0; i < BinaryVector.size(); i++)
	{
		for (int j = 0; j < S; j++)
		{
			m.push_back(BinaryVector[i]);
			t.push_back(time);

			file1 << time << " " << BinaryVector[i] << endl;
			n++;
			time = t0 + (n * dt);
		}
		
	}
	file1.close();

	//kluczowania
	za(1);
	zf(1);
	zp(1);
	cout << endl << endl;
	demodulacja_1=demodulacja(zpp, sygnosnyzp, 0.0001);
	cout << "DEMODULACJA PSK" << endl;
	for (int i = 0; i < demodulacja_1.size(); i++) {
		if (i == 0 || i % S == 0) {
			cout << demodulacja_1[i];
			demodulacja_1_Ham.push_back(demodulacja_1[i]);
		}
	}

	cout << endl;
	demodulacja_2 = demodulacja(zaa, sygnosnyza, 0.0001);
	cout << "DEMODULACJA ASK" << endl;
	for (int i = 0; i < demodulacja_2.size(); i++) {
		if (i == 0 || i % S == 0) {
			cout << demodulacja_2[i];
			demodulacja_2_Ham.push_back(demodulacja_2[i]);
		}
	}

	
	cout << endl;
	
	demodulacja_3=demodulacja2(zff, sygnosnyzf0, sygnosnyzf1, 0);
	cout << "DEMODULACJA FSK" << endl;
	for (int i = 0; i < demodulacja_3.size(); i++) {
		
		cout << demodulacja_3[i];
		demodulacja_3_Ham.push_back(demodulacja_3[i]);
		
	}

	cout << endl << endl;

	//dekodowanie//
	cout << "DEKODOWANIE KANALOWE PO PSK:" << endl;
	for (int i = 0; i < demodulacja_1_Ham.size() / 7; i++)
	{
		vector<int> bit;
		for (int j = 0; j < 7; j++)
		{
			bit.push_back(demodulacja_1_Ham[j + (i * 7)]);
		}
		Dekoder(bit);
	}

	int l = 1;
	for (int i = 0; i < d.size(); i++)
	{
		cout << d[i];
		if (l % 8 == 0)
			cout << " ";
		l++;
	}

	cout << endl;
	//BS2S//
	for (int i = 0; i < d.size() / 8; i++)
	{
		vector<int> znak;
		for (int j = 0; j < 8; j++)
		{
			znak.push_back(d[j + (i * 8)]);
		}
		BS2S(znak);
	}
	cout << endl;
	cout << endl;
	cout << "DEKODOWANIE KANALOWE PO ASK:" << endl;
	for (int i = 0; i < demodulacja_2_Ham.size() / 7; i++)
	{
		vector<int> bit2;
		for (int j = 0; j < 7; j++)
		{
			bit2.push_back(demodulacja_1_Ham[j + (i * 7)]);
		}
		Dekoder2(bit2);
	}

	l = 1;
	for (int i = 0; i < d2.size(); i++)
	{
		cout << d2[i];
		if (l % 8 == 0)
			cout << " ";
		l++;
	}

	cout << endl;
	//BS2S//
	for (int i = 0; i < d2.size() / 8; i++)
	{
		vector<int> znak;
		for (int j = 0; j < 8; j++)
		{
			znak.push_back(d2[j + (i * 8)]);
		}
		BS2S(znak);
	}

	cout << endl;
	cout << endl;
	cout << "DEKODOWANIE KANALOWE PO FSK:" << endl;
	for (int i = 0; i < demodulacja_3_Ham.size() / 7; i++)
	{
		vector<int> bit3;
		for (int j = 0; j < 7; j++)
		{
			bit3.push_back(demodulacja_3_Ham[j + (i * 7)]);
		}
		Dekoder3(bit3);
	}

	l = 1;
	for (int i = 0; i < d3.size(); i++)
	{
		cout << d3[i];
		if (l % 8 == 0)
			cout << " ";
		l++;
	}

	cout << endl;
	//BS2S//
	for (int i = 0; i < d3.size() / 8; i++)
	{
		vector<int> znak;
		for (int j = 0; j < 8; j++)
		{
			znak.push_back(d3[j + (i * 8)]);
		}
		BS2S(znak);
	}
	
	
}
