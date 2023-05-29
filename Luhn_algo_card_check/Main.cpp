#include <iostream>
using namespace std;


int ispravan_unos(long long kartica);
int duzina_broja(long long kartica);
int checksum(long long kartica, int duzina);
int provjera_izdavatelja(long long kartica, int duzina);


int main(void) {

	long long kartica;
	cout << "Unesite broj kartice: ";
	cin >> kartica;


	int duzina = duzina_broja(kartica);
	int rezultat = checksum(kartica, duzina);
	int vrsta_kart = provjera_izdavatelja(kartica, duzina);

	if ((rezultat % 10) != 0)
	{
		cout << "Invalid card number";
	}

	else if ((vrsta_kart == 0) && (rezultat % 10 == 0))
	{
		cout << "Nepoznat izadavtelj kartice.";
	}

	else if ((vrsta_kart == 1) && (rezultat % 10 == 0))
	{
		cout << "AMEX";
	}

	else if ((vrsta_kart == 2) && (rezultat % 10 == 0))
	{
		cout << "MASTER";
	}

	else if ((vrsta_kart == 3) && (rezultat % 10 == 0))
	{
		cout << " VISA";
	};

	return 0;
}

// Promt za unos ispravnog broja
int ispravan_unos(long long kartica)
{

	int duzina2 = duzina_broja(kartica);
	bool dobar = true;


	if (duzina2 < 13 || duzina2 > 16)
	{
		dobar = !dobar;
		do
		{
			cout << "Unijeli ste broj neispravne duzine. Unesite ponovno: ";
			cin >> kartica;
			duzina2 = duzina_broja(kartica);
			dobar = (duzina2 > 12 && duzina2 < 17);
		} while (dobar == false);
	}
	return 0;
}

// Raèuna dužinu unesenog broja
int duzina_broja(long long kartica)
{
	long long kartica2 = kartica;
	int duzina = 0;
	do
	{
		kartica2 = kartica2 / 10;
		duzina++;
	} while (kartica2 > 0);

	return duzina;
}
// Checksum
int checksum(long long kartica, int duzina)
{

	long long kartica3 = kartica;
	int sum_all = 0;


	for (int i = 0; i < duzina; i++)

	{
	
		int black_magics = 100;
		int here_be_dragons = 10;

		int par_nepar = kartica3 % black_magics;
		int broj_za_zbrojit = par_nepar % here_be_dragons;
		int broj_za_pomnozit = par_nepar / here_be_dragons;

		broj_za_pomnozit = broj_za_pomnozit * 2;

		if (broj_za_pomnozit > 9)
		{
			int prvi = broj_za_pomnozit % here_be_dragons;
			int drugi = broj_za_pomnozit / here_be_dragons;
			sum_all = sum_all + broj_za_zbrojit + prvi + drugi;
		}
		else
		{
			sum_all = sum_all + broj_za_pomnozit + broj_za_zbrojit;
		}

		kartica3 = kartica3 / 100;
	}

	return sum_all;
}

// Provjerava vrstu kartice - super referencu sam našao na paypalu: 
// https://developer.paypal.com/api/nvp-soap/payflow/integration-guide/test-transactions/#standard-test-cards
// Npr. 5673598276138003 prolazi checksum, ali nije uopæe valjana kartica niti jedne banke pa treba uzeti u obzir

int provjera_izdavatelja(long long kartica, int duzina)
{
	long long kartica_lokalno = kartica;
	long long prva_dva = 0;
	int vrsta;

	for (int i = 0; i < duzina - 2; i++)

	{
		kartica_lokalno = kartica_lokalno / 10;
		prva_dva = kartica_lokalno;
	}

	if ((prva_dva == 37 || prva_dva == 34) && (duzina == 15))
	{
		vrsta = 1; //Amex
	}

	else if ((prva_dva >= 51) && (prva_dva <= 55) && (duzina == 16))
	{
		vrsta = 2; //Master
	}

	else if ((prva_dva / 10 == 4) && (duzina == 16 || duzina == 13))
	{
		vrsta = 3; //Visa
	}

	else
	{
		vrsta = 0;
	};

	return vrsta;
}
