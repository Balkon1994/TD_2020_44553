#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<bool> Hamming;

vector<int>TTL;
vector<int>CLK;
vector<int>MAN;
vector<int>NRZI;
vector<int>BAMI;
vector<bool>d;


vector<bool> S2BS(char in[], int swicz, int length)  //String To Binary Stream 
{

	vector<bool> vec;
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

void Negacja(vector<bool>& vec, int index) //NEGACJA JEDNEGO BITU
{
	vec[index - 1] = !vec[index - 1];
}

void Dekoder(vector<bool> vec) //DEKODER KODU HAMMINGA
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

void BS2S(vector<bool> in) //BINARY TO STRING 
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

int main()
{
	//**S2BS**//
	char tab[] = "ALA MA KOTA";
	cout << tab;
	cout << endl;
	int length = sizeof(tab) - 1;
	auto BinaryVector = S2BS(tab, 1, length);
	cout << endl;

	//**kodowanie Hamming**//
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

	//**modulacja**//
	//wygenerowanie syg TTL
	for (int i = 0; i < Hamming.size(); i++)
	{
		if (Hamming[i] == 0)
		{
			TTL.push_back(0);
			TTL.push_back(0);
		}
		else
		{
			TTL.push_back(1);
			TTL.push_back(1);
		}
	}
	//wygenerowanie sygna³u CLK
	for (int i = 0; i < TTL.size(); i++)
	{
		if (i % 2 == 0)
			CLK.push_back(1);
		else
			CLK.push_back(0);
	}
	//NRZI
	NRZI.push_back(0);
	for (int i = 1; i < TTL.size(); i++)
	{
		if (CLK[i] == 0 && CLK[i - 1] == 1)
		{
			if (TTL[i] == 0 && NRZI[i - 1] == 0)
				NRZI.push_back(0);
			else if (TTL[i] == 1 && NRZI[i - 1] == 0)
				NRZI.push_back(-1);
			else if (TTL[i] == 1 && NRZI[i - 1] == -1)
				NRZI.push_back(1);
			else if (TTL[i] == 1 && NRZI[i - 1] == 1)
				NRZI.push_back(-1);
			else
				NRZI.push_back(NRZI[i - 1]);
		}
		else
			NRZI.push_back(NRZI[i - 1]);
	}

	//BAMI
	BAMI.push_back(0);
	BAMI.push_back(0);
	int temp = -1;
	for (int i = 2; i < TTL.size(); i++)
	{

		if (CLK[i] == 1 && CLK[i - 1] == 0)
		{
			if (TTL[i] == 0)
				BAMI.push_back(0);
			if (TTL[i] == 1)
			{
				BAMI.push_back(temp);
				temp = temp * (-1);
			}
		}
		else
			BAMI.push_back(BAMI[i - 1]);
	}

	//MAN 
	MAN.push_back(0);
	MAN.push_back(-1);
	for (int i = 2; i < TTL.size(); i++)
	{
		if (CLK[i] == 1 && CLK[i - 1] == 0)
		{
			if (TTL[i] == 0)
				MAN.push_back(MAN[i - 1] * (-1));
			else if (TTL[i] == 1)
				MAN.push_back(MAN[i - 1]);
		}
		else
			MAN.push_back(MAN[i - 1] * (-1));
	}

	ofstream file("kodowanieCLK.txt");
	float t0 = 0;
	float dt = (1.0 / 100);
	float time = t0;
	float n = 0;
	for (int i = 0; i < TTL.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{

			file << time << " " << CLK[i] << endl;
			n++;
			time = t0 + (n * dt);
		}
	}
	file.close();

	ofstream file2("kodowanieTTL.txt");
	t0 = 0;
	dt = (1.0 / 100);
	time = t0;
	n = 0;
	for (int i = 0; i < TTL.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{

			file2 << time << " " << TTL[i] << endl;
			n++;
			time = t0 + (n * dt);
		}
	}
	file2.close();

	ofstream file3("kodowanieNRZI.txt");
	t0 = 0;
	dt = (1.0 / 100);
	time = t0;
	n = 0;
	for (int i = 0; i < TTL.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{

			file3 << time << " " << NRZI[i] << endl;
			n++;
			time = t0 + (n * dt);
		}
	}
	file3.close();

	ofstream file4("kodowanieBAMI.txt");
	t0 = 0;
	dt = (1.0 / 100);
	time = t0;
	n = 0;
	for (int i = 0; i < TTL.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{

			file4 << time << " " << BAMI[i] << endl;
			n++;
			time = t0 + (n * dt);
		}
	}
	file4.close();

	ofstream file5("kodowanieMAN.txt");
	t0 = 0;
	dt = (1.0 / 100);
	time = t0;
	n = 0;
	for (int i = 0; i < TTL.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{

			file5 << time << " " << MAN[i] << endl;
			n++;
			time = t0 + (n * dt);
		}
	}
	file5.close();



	cout << "WYKRESY TTL/NRZI/BAMI/MAN ZOSTALY ZAPISANE DO PLIKOW TXT" << endl;
	//**demodulacja**//
	int wybor=0;
	cout << "WYBIERZ DEMODULACJE" << endl;
	cout << "(1)NRZI (2)BAMI (3)MAN " << endl;
	cin >> wybor;
	vector<bool> z;
	if (wybor == 1)
	{
		cout << "Dekoder NRZI" << endl;
		for (int i = 0; i < NRZI.size() - 2; i++)
		{
			if (i % 2 == 0)
			{
				if (NRZI[i] == 1 && NRZI[i + 2] == -1)
				{
					cout << 1;
					z.push_back(1);
				}
				else if (NRZI[i] == -1 && NRZI[i + 2] == 1)
				{
					cout << 1;
					z.push_back(1);
				}
				else
				{
					cout << 0;
					z.push_back(0);
				}
			}
		}
		cout << 0;
		z.push_back(0);
	}
	//dekoder BAMI
	if (wybor == 2)
	{
		cout << "Dekoder BAMI" << endl;
		for (int i = 0; i < BAMI.size(); i++)
		{
			if (i % 2 == 0)
			{
				if (BAMI[i] == 1)
				{
					cout << 1;
					z.push_back(1);
				}
				else if (BAMI[i] == -1)
				{
					cout << 1;
					z.push_back(1);
				}
				else
				{
					cout << 0;
					z.push_back(0);
				}
			}
		}
	}
	//dekoder MAN
	if (wybor == 3)
	{
		cout << "Dekoder MAN" << endl;
		cout << 0;
		z.push_back(0);
		for (int i = 0; i < MAN.size() - 1; i++)
		{
			if (CLK[i] == 0 && CLK[i + 1] == 1)
			{
				if (MAN[i] == MAN[i + 1])
				{
					cout << 1;
					z.push_back(1);
				}
				else
				{
					cout << 0;
					z.push_back(0);
				}
			}
		}
	}
	cout << endl;

	//**dekodowanie**//
	cout << "Dekodowanie kanalowe:" << endl;
	for (int i = 0; i < z.size() / 7; i++)
	{
		vector<bool> bit;
		for (int j = 0; j < 7; j++)
		{
			bit.push_back(z[j + (i * 7)]);
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
	//**BS2S**//
	for (int i = 0; i < d.size() / 8; i++)
	{
		vector<bool> znak;
		for (int j = 0; j < 8; j++)
		{
			znak.push_back(d[j + (i * 8)]);
		}
		BS2S(znak);
	}


}