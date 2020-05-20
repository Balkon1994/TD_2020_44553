#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
void wypiszSEDEC(vector<bool>SEDEC, ofstream& file) {
	for (int i = 0; i < 8; i++)
	{
		file << SEDEC[i];
	}
	file << " ";

}

vector<bool> S2BS(char in[], int swicz, int length)  //FUNKCJA ZMIENIAJ¥CA NAPIS W SYGNA£
{

	vector<bool> vec;
	//LITTLE ENDIAN
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
		//BIG ENDIAN
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

void Negowanie(vector<bool>& vec, int index)
{
	vec[index - 1] = !vec[index - 1];
}
void Negowanie2(vector<bool>& vec, int index, int index2)
{
	vec[index - 1] = !vec[index - 1];
	vec[index2 - 1] = !vec[index2 - 1];
}

vector<bool>Kodowanie(vector<bool> vec, int czworka)
{
	int d[4];
	if (czworka == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			d[i] = vec[i];
		}
	}
	if(czworka==1)
	{
		int n = 0;
		for (int i = 4; i < 8; i++)
		{
			d[n] = vec[i];
			n++;
		}
	}
	if(czworka==2)
	{
		int n = 0;
		for (int i = 8; i < 12; i++)
		{
			d[n] = vec[i];
			n++;
		}
	}
	if(czworka==3)
	{
		int n = 0;
		for (int i = 12; i < 16; i++)
		{
			d[n] = vec[i];
			n++;
		}
	}
	vector<bool> Hamming;
	Hamming.push_back((d[0] + d[1] + d[3]) % 2);
	Hamming.push_back((d[0] + d[2] + d[3]) % 2);
	Hamming.push_back(d[0]);
	Hamming.push_back((d[1] + d[2] + d[3]) % 2);
	Hamming.push_back(d[1]);
	Hamming.push_back(d[2]);
	Hamming.push_back(d[3]);
	return Hamming;
}

vector<bool>SEDEC(vector<bool> vec){
	bool temp=(vec[0] + vec[1] + vec[2] + vec[3] + vec[4] + vec[5] + vec[6]) % 2;
	vec.push_back(temp);
	return vec;
}

vector<bool> Dekodowanie(vector<bool> vec)
{

	int p1 = (vec[0] + vec[2] + vec[4] + vec[6]) % 2;
	int p2 = (vec[1] + vec[2] + vec[5] + vec[6]) % 2;
	int p3 = (vec[3] + vec[4] + vec[5] + vec[6]) % 2;
	int n = p1 + p2 * 2 + p3 * 4;
	if (n > 0)
	{
		cout << "blad na pozycji: " << n << endl;
		vec[n - 1] = !vec[n - 1];
	}
	
	vector<bool>d;
	d.push_back(vec[2]);
	d.push_back(vec[4]);
	d.push_back(vec[5]);
	d.push_back(vec[6]);
	return d;
}

vector<bool> Dekodowanie2(vector<bool> vec)
{

	int p1 = (vec[0] + vec[2] + vec[4] + vec[6]) % 2;
	int p2 = (vec[1] + vec[2] + vec[5] + vec[6]) % 2;
	int p3 = (vec[3] + vec[4] + vec[5] + vec[6]) % 2;
	int n = p1 + p2 * 2 + p3 * 4;
	if (n > 0)
	{
		cout << "blad na pozycji: " << n << endl;
		vec[n - 1] = !vec[n - 1];
		bool temp = (vec[0] + vec[1] + vec[2] + vec[3] + vec[4] + vec[5] + vec[6]) % 2;
		if (temp != vec[7]) {
			cout << "wystepuje podwojny blad i nie da sie tego naprawic" << endl;
			
		}
		
	}

	vector<bool>d;
	d.push_back(vec[2]);
	d.push_back(vec[4]);
	d.push_back(vec[5]);
	d.push_back(vec[6]);
	return d;
}

int main()
{
	
		char tab[] = "ST";
		cout << tab << endl;
		auto BinaryVector = S2BS(tab, 0, 2);
		cout << endl;
		auto haming1 = Kodowanie(BinaryVector, 0);
		auto haming2 = Kodowanie(BinaryVector, 1);
		auto haming3 = Kodowanie(BinaryVector, 2);
		auto haming4 = Kodowanie(BinaryVector, 3);

		cout << endl;
		cout << "Kod Hamminga z naszego wyrazenia:" << endl;
		cout << "[";
		for (int i = 0; i < 7; i++)
		{
			cout << haming1[i];
		}
		cout << "][";
		for (int i = 0; i < 7; i++)
		{
			cout << haming2[i];
		}
		cout << "]";
		cout << "[";
		for (int i = 0; i < 7; i++)
		{
			cout << haming3[i];
		}
		cout << "][";
		for (int i = 0; i < 7; i++)
		{
			cout << haming4[i];
		}
		cout << "]";
		cout << endl;
	
		auto SEDEC1 = SEDEC(haming1);
		auto SEDEC2 = SEDEC(haming2);
		auto SEDEC3 = SEDEC(haming3);
		auto SEDEC4 = SEDEC(haming4);
	
		int index = 6;
		int index2 = 2;
		cout << "Zanegowanie " << index << " bitu :" << endl;
		Negowanie(haming1, index);
		for (int i = 0; i < 7; i++)
		{
			cout << haming1[i];
		}
		cout << endl;
		cout << "Dekodowanie:";
		cout << endl;
		auto d1 = Dekodowanie(haming1);
		auto d2 = Dekodowanie(haming2);
		auto d3 = Dekodowanie(haming3);
		auto d4 = Dekodowanie(haming4);
		for (int i = 0; i < 4; i++)
		{
			cout << d1[i];
		}
		for (int i = 0; i < 4; i++)
		{
			cout << d2[i];
		}
		cout << " ";
		for (int i = 0; i < 4; i++)
		{
			cout << d3[i];
		}
		for (int i = 0; i < 4; i++)
		{
			cout << d4[i];
		}

		cout << endl;
		cout << endl;
		cout << "SEDEC:" << endl;
		cout << "[";
		for (int i = 0; i < 8; i++)
		{
			cout << SEDEC1[i];
		}
		cout << "]";
		cout << "[";
		for (int i = 0; i < 8; i++)
		{
			cout << SEDEC2[i];
		}
		cout << "]";
		cout << "[";
		for (int i = 0; i < 8; i++)
		{
			cout << SEDEC3[i];
		}
		cout << "]";
		cout << "[";
		for (int i = 0; i < 8; i++)
		{
			cout << SEDEC4[i];
		}
		cout << "]";
		Negowanie(SEDEC1, index);
		cout << endl;
		cout << "Zanegowanie " << index << " bitu" << endl;
	
		auto S11 = Dekodowanie2(SEDEC1);
		auto S22 = Dekodowanie2(SEDEC2);
		auto S33 = Dekodowanie2(SEDEC3);
		auto S44 = Dekodowanie2(SEDEC4);
		for (int i = 0; i < 4; i++)
		{
			cout << S11[i];
		}
		for (int i = 0; i < 4; i++)
		{
			cout << S22[i];
		}
		cout << " ";
		for (int i = 0; i < 4; i++)
		{
			cout << S33[i];
		}
		for (int i = 0; i < 4; i++)
		{
			cout << S44[i];
		}
		Negowanie2(SEDEC1, index, index2);
		cout << endl;
		cout << "Zanegowanie " << index << " bitu oraz "<< index2 << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << SEDEC1[i];
		}
		cout << endl;
		cout << "Dekodowanie SEDEC po 2 zmienionych bitach:";
		cout << endl;
		auto S1 = Dekodowanie2(SEDEC1);
		auto S2 = Dekodowanie2(SEDEC2);
		auto S3 = Dekodowanie2(SEDEC3);
		auto S4 = Dekodowanie2(SEDEC4);
		cout << "Nie da sie tego naprawic poniewaz doszlo do manipulacji na dwoch bitach"<<endl;
		for (int i = 0; i < 4; i++)
		{
			cout << S1[i];
		}
		for (int i = 0; i < 4; i++)
		{
			cout << S2[i];
		}
		cout << " ";
		for (int i = 0; i < 4; i++)
		{
			cout << S3[i];
		}
		for (int i = 0; i < 4; i++)
		{
			cout << S4[i];
		}
		cout << endl;
		cout << "Tak jak widac ostatni otrzymany kod po dekodowaniu jest zly";
		cout << endl;
		cout << endl;




	return 0;
}