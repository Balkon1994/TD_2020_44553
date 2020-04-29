#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int A1 = 0; //Amplituda A1
int A2 = 1; //Amplituda A2
int A = 1; //Amblituda A
float Tb = 0.1; //Szerokość bitu
float N = 2;
float f = 20; //f podstawowe
float f1 = 10; //f1
float f2 = 20;//f2
vector<int>m;
vector<float>t;
vector<float> sygnosnyza;
vector<float> sygnosnyzp;
vector<float> sygnosnyzf0;
vector<float> sygnosnyzf1;
vector<float> zaa;
vector<float> zff;
vector<float> zpp;

vector<bool> S2BS(char in[], int length)  //String To Binary Stream 
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

void za()
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

void zf()
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

void zp()
{
    ofstream file("zp.txt");
    for (int i = 0; i < m.size(); i++)
    {
        if (m[i] == 0)
            zpp.push_back(A2 * sin(2 * M_PI * f * t[i]));
        else
            zpp.push_back(A2 * sin(2 * M_PI * f * t[i] + M_PI));

        sygnosnyzp.push_back(A2 * sin(2 * M_PI * f * t[i]+M_PI));

        file << t[i] << " " << zpp[i] << endl;
       
    }
    file.close();
}

void demodulacjaASK(vector<float> func, vector<float> sinfo,float h)
{
    ofstream plik1("xt.txt");
    vector<float> funcxsinfo;
    for (int i = 0; i < func.size(); i++)
    {
        funcxsinfo.push_back(func[i] * sinfo[i]);
		if (funcxsinfo[i] < 0) {
			funcxsinfo[i] = 0;
		}
        plik1 << t[i] << " " << funcxsinfo[i] << endl;
    }
    plik1.close();

    ofstream plik2("pt.txt");
    float suma=0;
    vector<double> calka;
    for (int i = 0; i < funcxsinfo.size(); i++)
    {
        if (i % 20 == 0)
        {
            suma = 0;
        }
        suma = suma + funcxsinfo[i];
		if (suma < 0) {
			suma = 0;
		}
			
        calka.push_back(suma);
        plik2 << t[i] << " " << calka[i] << endl;
    }
    plik2.close();

   
    vector<int> mpodem;
    ofstream plik3("m.txt");
    {
        for (int i = 0; i < calka.size(); i++)
        {
        
            if (calka[i] > h)
                mpodem.push_back(1);
            else if ((i!=calka.size()-1)&& (calka[i + 1] > h))
                mpodem.push_back(1);
            else
                mpodem.push_back(0);
            plik3 << t[i] << " " << mpodem[i] << endl;
        }
    }
}

void demodulacjaPSK(vector<float> func, vector<float> sinfo, float h)
{
	
	ofstream plik1("xt2.txt");
	vector<float> funcxsinfo;
	for (int i = 0; i < func.size(); i++)
	{
		funcxsinfo.push_back(func[i] * sinfo[i]);
		
		plik1 << t[i] << " " << funcxsinfo[i] << endl;
	}
	plik1.close();
	
	ofstream plik2("pt2.txt");
	float suma = 0;
	vector<double> calka;
	for (int i = 0; i < funcxsinfo.size(); i++)
	{
		if (i % 20 == 0)
		{
			suma = 0;
		}
		suma = suma + funcxsinfo[i];
		

		calka.push_back(suma);
		plik2 << t[i] << " " << calka[i] << endl;
	}
	plik2.close();

	
	vector<int> mpodem;
	ofstream plik3("m2.txt");
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
}

void demodulacjaFSK(vector<float> func, vector<float> sinfo0, vector<float> sinfo1, float h)
{
    
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

    
    vector<double> calka0;
    vector<double> calka1;
    ofstream plik3("calka20.txt"); //Obliczenie całki X20
    float suma = 0;
    for (int i = 0; i < funcxsinfo0.size(); i++)
    {
        if (i % 20 == 0)
        {
            suma = 0;
        }
        suma = suma + funcxsinfo0[i];
        calka0.push_back(suma);
        plik3 << t[i] << " " << calka0[i] << endl;
    }
    plik3.close();


    ofstream plik4("calka21.txt"); //Obliczenie całki X21
    suma = 0;
    for (int i = 0; i < funcxsinfo1.size(); i++)
    {
        if (i % 20 == 0)
        {
            suma = 0;
        }
        suma = suma + funcxsinfo1[i];
        calka1.push_back(suma);
        plik4 << t[i] << " " << calka1[i] << endl;
    }
    plik4.close();

    //Obliczenie różnicy całek
    vector<double> roznica;
    ofstream plik5("roznica.txt");
    for (int i = 0; i < calka1.size(); i++)
    {
        roznica.push_back(calka1[i] - calka0[i]);
        plik5 << t[i] << " " << roznica[i] << endl;
    }

  
    vector<int> mpodem;
    ofstream plik6("m20.txt"); //Utworzenie sygnału M
    {
        for (int i = 0; i < roznica.size(); i++)
        {

            if (roznica[i] > h)
                mpodem.push_back(1);
            else if ((i != roznica.size() - 1) && (roznica[i + 1] > h))
                mpodem.push_back(1);
            else
                mpodem.push_back(0);
            plik6 << t[i] << " " << mpodem[i] << endl;
        }
    }
    plik6.close();
}

int main()
{
    //Zamiana sygnału wejściowego
    char tab[] = "tommy";
    cout << tab;
    cout << endl;
    int length = sizeof(tab) - 1;
    auto BinaryVector = S2BS(tab, length); 
   


    ofstream file1("sygnal.txt"); //Wypisanie sygnału wejściowego
    float t0 = 0;
    float dt = (1.0 / 1000);
    float time = t0;
    float n = 0;
    int stop = 1;
    for (int i = 0; i < BinaryVector.size(); i++)
    {
        for (int j = 0; j < 200; j++)
        {
            m.push_back(BinaryVector[i]);
            t.push_back(time);

            file1 << time << " " << BinaryVector[i] << endl;
            n++;
            time = t0 + (n * dt);
        }
        /*if (stop == 1 && i == 9)
            break;*/
    }
    file1.close();

    //Wywołanie Za,Zp,Zf
    za;
    zf;
    zp;
    //Demodulacje
    demodulacjaASK(zaa, sygnosnyza, 0.0001);
	demodulacjaPSK(zpp, sygnosnyzp, 0.0001);
    demodulacjaFSK(zff, sygnosnyzf0, sygnosnyzf1, 0.43);
	
