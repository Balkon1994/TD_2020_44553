#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


float A1 = 1;
float A2 = 2;
float A = 2;
float Tb = 0.01;
float N = 2;
float f = 100;
float f1 = (N + 1) / Tb;
float f2 = (N + 5) / Tb;
vector<int>m;
vector<int>m1;
vector<int>mp;
vector<float>t;
vector<float>t1;
vector<float> zaa;
vector<float> zff;
vector<float> zpp;
vector<float> zaa1;
vector<float> zff1;
vector<float> zpp1;
//vector<float> fk;
//vector<float> fk2;
//vector<float> fk3;
vector<float> X_re;
vector<float> X_im;
vector<float> X_re2;
vector<float> X_im2;
vector<float> X_re3;
vector<float> X_im3;
vector<float> M;
vector<float> M_D;
vector<float> M2;
vector<float> M_D2;
vector<float> M3;
vector<float> M_D3;
float TAB[1000];
float fk[5000];
float fk2[5000];
float fk3[5000];
double min(vector<float> M, float f[], int size) //Funkcja min
{
	float min = M[size/2];
	int ind = 0;
	for (int i = 0; i < size / 2; i++)
	{

		
		if (M[i] < min && M[i]>0)
		{
			min = M[i];
			ind = i;
		}

	}
	min = f[ind - 3];
	return min;
}
double max(vector<float> M, float f[], int size) //Funkcja max
{
	float max = M[size/2];
	int ind = 0;
	for (int i = 1; i < size/2 ; i++)
	{


		if (M[i] > max && M[i] > 0)
		{
			max = M[i];
			ind = i;
		}

	}
	max =f[ind + 3];
	return max;
}

vector<bool> S2BS(char in[], int swicz,int length)  //String To Binary Stream 
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
        cout << "Big Endian"<<endl;
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

void dft(vector<float> X_re,vector<float>X_im,vector<float>t,vector<float> func, vector<float>M,vector<float>M_D,float fk[], ofstream& plik)
{

    float xr = 0;
    float xim = 0;
    int n;
    int k;
	
	int N = t.size();
	cout <<t.size();

	for (int j = 1; j <= N; j++)
    {
        xr = 0;
        xim = 0;
        for (int n = 0; n < N; n++)
        {
            xr = xr + (func[n] * cos((2 * M_PI * double(j) * double(n)) / N));
            xim = xim + (func[n] * sin((2 * M_PI * double(j) * double(n)) / N));
        }
        X_re.push_back(xr);
        X_im.push_back(xim);
 
		
    }
	cout << X_re.size() << endl;
    for (k = 0; k < X_re.size(); k++)
    {
        M.push_back(sqrt((X_re[k] * X_re[k]) + (X_im[k] * X_im[k])));
        M[k] = (M[k] * 2) / X_re.size();
        M_D.push_back(10 * log10(M[k]));
		fk[k] = k * (f / N);
        plik << k * (f / N) << " " << M_D[k]+30 << endl;
        
    }
}


vector<float> za( vector<int> m, vector<float> zaa, vector<float>t, ofstream& plik)
{
	cout << m.size();
	for (int i = 0; i < m.size(); i++)
	{
		
		if (m[i] == 0) {
				zaa.push_back(A1 * sin(2 * M_PI *f* t[i]));
				
		}
		else
		{
				zaa.push_back(A2 * sin(2 * M_PI * f * t[i]));
				
		}
		plik << t[i]*10 << " " << zaa[i] << endl;
		
	}

	return zaa;

	
}

vector<float> zf( vector<int> m,vector<float> zff, vector<float>t, ofstream& plik)
{
   
    for (int i = 0; i < m.size(); i++)
    {
		if (m[i] == 0) {
			zff.push_back(A * sin(2 * M_PI * f1 * t[i]));
		}
		else {
			zff.push_back(A * sin(2 * M_PI * f2 * t[i]));
		};
        plik << t[i]*10 << " " << zff[i] << endl;
        
    }
	return zff;
    
}

vector<float> zp( vector<int> m,vector<float> zpp, vector<float>t, ofstream& plik)
{
    
    for (int i = 0; i < m.size(); i++)
    {
        if (m[i] == 0)
            zpp.push_back(A * sin(2 * M_PI * f * t[i]));
        else
            zpp.push_back(A * sin(2 * M_PI * f * t[i]+M_PI));

        plik << t[i]*10 << " " << zpp[i] << endl;
        
    }
	return zpp;
}
int main()
{
    //S2BS
    char tab[] = "ST";
    cout << tab;
    cout << endl;
    int length = sizeof(tab) - 1;
    auto BinaryVector = S2BS(tab, 0, length);
    cout << endl;


    ofstream file1("sinfo.txt");
    float t0 = 0;
    float dt = (1.0 / 5000);
    float time=t0;
    float n = 0;
    //sygnal informacyjny
    int stop = 1;
	
    for (int i = 0; i < BinaryVector.size(); i++)
    {
        for (int j = 0; j < 500; j++)
        {
            m.push_back(BinaryVector[i]);
            t.push_back(time);
			
			file1 << time*10 << " " << BinaryVector[i] << endl;
			n++;
            
            time = (t0 + (n*dt))/10;
        }
        if (stop == 1 && i == 9)
            break;
    }
    file1.close();

	ofstream file1a("sinfo2.txt");
	t0 = 0;
	dt = (1.0 / 250);
	time = t0;
	n = 0;
	//sygnal informacyjny
	stop = 1;

	for (int i = 0; i < BinaryVector.size(); i++)
	{
		for (int j = 0; j <250; j++)
		{
			m1.push_back(BinaryVector[i]);
			t1.push_back(time);

			file1a << time << " " << BinaryVector[i] << endl;
			n++;
			time = (t0 + (n * dt)/10);
		}
		//if (stop == 1 && i == 9)
			//break;
	}
	file1a.close();

    //kluczowania
	ofstream file2("za.txt");
    za(m,zaa,t,file2);
	file2.close();


	ofstream file3("zf.txt");
	zf(m,zff,t, file3);
	file3.close();

	ofstream file4("zp.txt");
    zp(m,zaa,t,file4);
	file4.close();

	ofstream file2a("za2.txt");
	zaa1=za( m1,zaa1,t1,file2a);
	file2a.close();

	ofstream file3a("zf2.txt");
	zff1=zf(m1,zff1,t1,file3a);
	file3a.close();

	ofstream file4a("zp2.txt");
	zpp1=zp(m1,zpp1,t1,file4a);
	file4a.close();


	//LICZENIE DFT



	ofstream file5("zadft.txt");
    dft(X_re,X_im,t1,zaa1,M,M_D,fk,file5);
    file5.close();
	
    ofstream file6("zfdft.txt");
    dft(X_re2,X_im2,t1,zff1,M2,M_D2,fk2, file6);
    file6.close();

    
	ofstream file7("zpdft.txt");
    dft(X_re3, X_im3, t1, zpp1, M3, M_D3, fk3, file7);
    file7.close();
	
}

