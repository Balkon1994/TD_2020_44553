#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
vector<int>TTL;
vector<int>CLK;
vector<int>MAN;
vector<int>NRZI;
vector<int>BAMI;
vector<float>t;

void wypis(vector <int> wypis, ofstream& file ) {
	float t0 = 0;
	float dt = (1.0 / 100);
	float time = t0;
	float n = 0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			file << time << " " << wypis[i] << endl; 
			n++;
			time = t0 + (n * dt);
		}
	}
}

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


int main()
{
	//S2BS
	char tab[] = "tommy";
	cout << tab;
	cout << endl;
	int length = sizeof(tab) - 1;
	auto BinaryVector = S2BS(tab, 1, length);
	cout << endl;

	//wygenerowanie syg TTL
	for (int i = 0; i < 16; i++)
	{
		if (BinaryVector[i] == 0)
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
	//for (int i = 0; i < 32; i++)
	//    cout << TTL[i];

	//wygenerowanie sygna³u CLK
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			CLK.push_back(1);
		else
			CLK.push_back(0);
	}

	//NRZI
	NRZI.push_back(0);
	for (int i = 1; i < 32; i++)
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
	cout << endl;


	//BAMI
	BAMI.push_back(0);
	BAMI.push_back(0);
	int temp = -1;
	for (int i = 2; i < 32; i++)
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

	//MAN diff
	MAN.push_back(0);
	MAN.push_back(-1);
	for (int i = 2; i < 32; i++)
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

	//do pliku
	ofstream file("Clock.txt");
	wypis(CLK, file);
	file.close();

	ofstream file1("TTL.txt"); 
	wypis(TTL, file1);
	file1.close();

	ofstream file2("MAN.txt");
	wypis(MAN, file2);
	file2.close();

	ofstream file3("NRZI.txt");
	wypis(NRZI, file3);
	file3.close();

	ofstream file4("BAMI.txt");
	wypis(BAMI, file4);
	file4.close();


	ofstream fileD("Dekoder.txt");
	//dekoder TTL to pierwsze 16 bitow z BinaryVector
	fileD << "Dekoder TTL" << endl;
	for (int i = 0; i < 16; i++)
	{
		fileD << BinaryVector[i];
	}

	//dekoder NRZI
	fileD << endl;
	fileD << "Dekoder NRZI" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (i % 2 == 0)
		{
			if (NRZI[i] == 1 && NRZI[i + 2] == -1)
				fileD << 1;
			else if (NRZI[i] == -1 && NRZI[i + 2] == 1)
				fileD << 1;
			else
				fileD << 0;
		}
	}
	fileD << 0;

	//dekoder BAMI
	fileD << endl;
	fileD << "Dekoder BAMI" << endl;
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
		{
			if (BAMI[i] == 1)
				fileD << 1;
			else if (BAMI[i] == -1)
				fileD << 1;
			else
				fileD << 0;
		}
	}

	//dekoder MAN
	fileD << endl;
	fileD << "Dekoder MAN diff" << endl;
	fileD << 0;
	for (int i = 0; i < 31; i++)
	{
		if (CLK[i] == 0 && CLK[i + 1] == 1)
		{
			if (MAN[i] == MAN[i + 1])
				fileD << 1;
			else
				fileD << 0;
		}
	}
	fileD.close();
}
