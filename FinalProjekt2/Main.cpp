#include "Main.h"

void main()
{
	srand(time(NULL));
	TSP *tsp = new TSP();
	int wyb, ilosc_miast, rep;
	double dlugoscTab, warunekK;
	string filename;
	int counter;
	bool a = true;
	int *route;
	int Blad;

	Timer * Time = new Timer();
	while (a)
	{
		cout <<
			"1- Wczytaj koordynaty z pliku\n"
			"2- Wczytaj macierz z pliku\n"
			"3- Wygeneruj losowo\n"
			"4- Algorytm Tabu Search\n"
			"0- Exit\n";
		cin >> wyb;
		switch (wyb)
		{
		case 1:
			cout << "Podaj nazwe pliku:\n >>";
			cin >> filename;
			cout << "Wyszwietliacz wczytany plik?\n1-Tak,2-Nie\n >>";
			cin >> counter;
			tsp->ReadFromFileK(filename, counter);
			break;
		case 2:
			cout << "Podaj nazwe pliku:\n >>";
			cin >> filename;
			cout << "Wyszwietliacz wczytany plik?\n1-Tak,2-Nie\n >>";
			cin >> counter;
			tsp->ReadFromFileM(filename, counter);
			break;
		case 3:
			cout << "Podaj ilosc miast:\n >>";
			cin >> ilosc_miast;
			cout << "Wyszwietliacz wczytany plik?\n1-Tak,2-Nie\n >>";
			cin >> counter;
			tsp->RandomData(ilosc_miast, counter);
			break;
		case 4:
			cout << "Podaj parametry(wpisanie -1 spowoduje dobranie ich automatycznie" << endl;
			cout << "Ilosc repetycji:\n>>";
			cin >> rep;
			cout << "Ilosc dlugosc tabu:\n>>";
			cin >> dlugoscTab;
			cout << "Warunek krytyczny:\n>>";
			cin >> warunekK;
			cout << "\nNajbardziej znane rozwiązania\n"
				"TSP: \n"
				"a280 : 2579\n"
				"bays29 : 2020\n"
				"berlin52 : 7542\n"
				"pr1002 : 259045\n"

				"\nATSP: \n"
				"ft53 : 6905\n"
				"ftv33 : 1286\n"
				"ftv55 : 1608\n";

			cout << "\nOptymalne Rozwiazanie:\n>>";
			cin >> Blad;
			for (int i = 0; i < 10; i++)
			{
				Time->startTimer();
				route = tsp->TabuSearch(rep, dlugoscTab, warunekK);
				Time->ZapiszDoPlikuEndTimer(0, "Czas wykonanaia Algorytmu");
				tsp->Print(route, Blad);
			}
			break;
		case 0:
			a = false;
			break;
		}
	}
}