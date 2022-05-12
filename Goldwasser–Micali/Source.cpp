#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
#include<ctime>
#include<vector>
using namespace std;
string alfabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789():; .,!?-'";
long long int prim(long long int x) {
	if ((x == 1) || (x == 2))
		return 1;
	if (x % 2 == 0)
		return 0;
	for (int i = 3; i <= sqrt((double)x); i += 2)
		if (x % i == 0)
			return 0;
	return 1;
}
long long int cmmdc(long long int x, long long int y)
{
	long long int cpy = y, rest;
	do {
		rest = x % y;
		x = y;
		y = rest;
	} while (rest != 0);
	if (x != 1)
		cout << "\nNumarul ales nu este prim cu numarul " << cpy << endl;
	return x;
}
long long int Inversul(long long int n) {
	long long int inv = 0;
	while (n != 0)
	{
		inv = inv * 10 + n % 10;
		n = n / 10;
	}
	return inv;
}
bool Este_rest_patratic(long long int n, long long int p)
{
	long long int cpy, x;
	cpy = n;
	n = n % p;
	for (x = 2; x < p; x++)
	{
		if ((x * x) % p == n)
			return 0;
	}
	return 1;
}
long long int Numar_binar(long long int n)
{
	long long int nr = 0, z = 1, r;
	while (n > 0) {
		r = n % 2;
		n = n / 2;
		nr = nr + r * z;
		z = z * 10;
	}
	return nr;
}
vector< long long int> Criptarea_mesajului(string line, long long int a, long long int N)
{
	long long int i, j, b = 0, c, nr, m, r, cpynr, cpynr2, k, x, n, Vector_binar[1000];
	vector< long long int > caracter_criptat;
	srand(time(NULL));
	for (i = 0; i < line.length(); i++)
		for (j = 0; j < 73; j++)
		{
			if (line[i] == alfabet[j])
			{
				cout << j+1 << " ";
				Vector_binar[b] = Numar_binar(j+1);
				b++;
			}
		}
	for (int i = 0; i < b; i++)
	{
		k = 0;
		m = 0;
		if (Vector_binar[i] % 10 != 0)
		{
			nr = Inversul(Vector_binar[i]);
		}
		else {
			nr = Vector_binar[i];
			cpynr = nr;
			cpynr2 = nr;
			if ((cpynr % 10) == 0)
				do {
					k++;
					cpynr = cpynr2 / pow(10, k);
					cpynr2 = nr;
				} while ((cpynr % 10) != 1);
		}
		nr = Inversul(Vector_binar[i]);
		while (nr != 0)
		{
			m = nr % 10;
			nr = nr / 10;
			if (m == 0)
			{
				r = rand() % (N - 2) + 2;
				c = (r * r) % N;
				caracter_criptat.push_back(c);
			}
			if (m == 1)
			{
				r = rand() % (N - 2) + 2;
				c = (a * r * r) % N;
				caracter_criptat.push_back(c);
			}
		}
		if (k > 0)
			do {
				m = 0;
				r = rand() % (N - 2) + 2;
				c = (r * r) % N;
				caracter_criptat.push_back(c);
				k--;
			} while (k != 0);
	}
	return caracter_criptat;
}
int Binar_Dec(int n)
{
	int nr = n, x = 0, k = 1;
	while (nr) {
		int c = nr % 10;
		nr = nr / 10;
		x += c * k;
		k = k * 2;
	}
	return x;
}
void Decriptarea_mesajului(vector<long long int> caracter_criptat, int p, int n, string line)
{
	int i, j, m, b = 0, nr, cpym, k, Vector_binar[1000], vcount[1000], dec, dec_bin[1000], x[1000], decrypted;
	for (i = 0; i < line.length(); i++)
		for (j = 0; j < 73; j++)
		{
			if (line[i] == alfabet[j])
			{
				j = j + 1;
				Vector_binar[b] = Numar_binar(j);
				b++;
			}
		}
	for (i = 0; i < b; i++)
	{
		int count = 0;
		while (Vector_binar[i] != 0)
		{
			Vector_binar[i] = Vector_binar[i] / 10;
			++count;
		}
		vcount[i] = count;
	}
	int cont = 0;
	for (int l = 0; l < b; l++)
	{
		int cpyvcount = vcount[l];
		dec = 0;
		for (int i = cont; i < (cpyvcount + cont); i++) {
			if (Este_rest_patratic(caracter_criptat[i], p) == 0)
				m = 0;
			else
				m = 1;
			dec = dec * 10 + m;
		}
		dec_bin[l] = dec;
		cont = cpyvcount + cont;
	}
	cout << endl << "Pozitiile decodate: ";
	for (int l = 0; l < b; l++) {
		x[l] = Binar_Dec(dec_bin[l]);
		cout << x[l] << " ";
	}
	cout << "\nMesajul decriptat: ";
	for (int l = 0; l < b; l++)
	{
		decrypted = x[l];
		cout << alfabet[decrypted-1];
	}
}
int main() {
	long long int N, p, q, a;
	vector< long long int> caracter_criptat;
	cout << "\nIntroduceti doua numere prime mai mari decat 1000: " << endl << "\nIntroduceti prima valoare: p = ";
	cin >> p;
	if (p <= 1000 || prim(p) == 0) do
	{
		cout << "\nNumarul ales nu corespunde criteriilor. Introduceti un element care indeplineste conditiile precedente: p = ";
		cin >> p;
	} while (p <= 1000 || prim(p) == 0);
	cout << endl << "Introduceti a doua valoare: q = ";
	cin >> q;
	if (q <= 1000 || prim(q) == 0) do
	{
		cout << "\nNumarul ales nu corespunde criteriilor. Introduceti un element care indeplineste conditiile precedente: q = ";
		cin >> q;
	} while (q <= 1000 || prim(q) == 0);
	cout << "\nValorile introduse " << p << " si " << q << " respecta criteriile anterioare. Cheia de criptare secreta este (p, q) = " << "(" << p << ", " << q << ").";
	N = p * q;
	cout << endl << "\nProdusul elementelor p si q este notat cu: N = " << p << " * " << q << " = " << N;
	cout << endl << "\nIntroduceti o valoare prima cu numerele p si q, inclusa in intervalul (0," << N << ").  ";
	cout << "Valoarea aleasa nu trebuie sa fie rest patratic modulo " << p << " sau rest patratic modulo " << q << ": a = ";
	cin >> a;
	if ((a <= 0) || (a >= N) || (cmmdc(a, p) != 1) || (cmmdc(a, q) != 1) || (Este_rest_patratic(a, p) == 0) || (Este_rest_patratic(a, q) == 0)) do
	{
		cout << "\nValoarea aleasa " << a << " nu respecta conditiile precedente. Introduceti un numar nou: a = ";
		cin >> a;
	} while ((a <= 0) || (a >= N) || (cmmdc(a, p) != 1) || (cmmdc(a, q) != 1) || (Este_rest_patratic(a, p) == 0) || (Este_rest_patratic(a, q) == 0));
	cout << "\nValoarea introdusa " << a << " respecta particularitatile anterioare. Cheia de criptare publica este (N,a) = (" << N << "," << a << ")" << endl << "\nMesajul introdus: ";
	string line = " ";
	fstream my_stream;
	std::cin.get();
	my_stream.open("Text.txt");
	getline(my_stream, line);
	my_stream.close();
	for (int i = 0; i < line.length(); i++)
		cout << line[i];
	cout << endl << "Pozitiile caracterelor: ";
	caracter_criptat = Criptarea_mesajului(line, a, N);
	cout << endl << "\nCodificarea se realizeaza prin intermediul criptosistemului Goldwasser_Micali: " << endl;
	cout << endl;
	cout << "[ ";
	for (int i = 0; i < caracter_criptat.size(); i++)
		cout << caracter_criptat[i] << " ";
	cout << "]" << endl;
	int n = caracter_criptat.size();
	Decriptarea_mesajului(caracter_criptat, p, n, line);
	cout << endl << endl;
	system("pause");
	return 0;
}
