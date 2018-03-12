#include "Main.h"

TSP::TSP(int size) : Size(size), distances(new double*[size])//Konstruktor
{
	for (int i = 0; i < size; i++)
	{
		distances[i] = new double[size];
		fill_n(distances[i], size, MAX);
	}

}

TSP::~TSP()//Destruktor 
{
	if (distances != nullptr)
	{
		for (int i = 0; i < Size; i++)
		{
			if (distances[i] != nullptr)
			{
				delete distances[i];
			}
		}
		delete[] distances;
	}
}

int TSP::GetSize() const // Funkcja zwraca ilosc miast(Rozmiar)
{
	return this->Size;
}

void TSP::CopyTable(int *First, int *Second, int Size)//Funkcja Która kopijuje dane z jednej tablicy do drugiej 
{
	if (First == nullptr || Second == nullptr)
	{
		return;
	}
	for (int i = 0; i < Size; i++)
	{
		Second[i] = First[i];
	}
}

void TSP::ReadFromFileM(string filename, int counter)//Wczytywanie plików maczerzowych
{
	int count = counter;
	{
		if (distances != nullptr)
		{
			for (int i = 0; i < Size; i++)
			{
				if (distances[i] != nullptr)
				{
					delete distances[i];
				}
			}
			delete[] distances;
		}

		ifstream fin;
		fin.open(filename, ios::in);
		string buf = "";
		while (buf != "DIMENSION:")
		{
			fin >> buf;
		}

		fin >> this->Size;

		while (buf != "EDGE_WEIGHT_SECTION")
		{
			fin >> buf;
		}
		distances = new double*[this->Size];
		double bufor;
		for (int i = 0; i < this->Size; i++)
		{
			distances[i] = new double[this->Size];
			for (int j = 0; j < this->Size; j++)
			{
				fin >> distances[i][j];
				if (i == j)
				{
					distances[i][j] = MAX;//jezeli i==j wpisujemy MAX
				}
			}
		}
		if (count == 1)//Proste sprawdzenie za pomocą którego możemy wydrukować lub nie wydrókować maczierz do konsoli
		{
			for (int i = 0; i < this->Size; i++)
			{
				for (int j = 0; j < this->Size; j++)
				{
					cout << distances[i][j] << " " << setw(4);
				}
				cout << endl;
			}
		}
		fin.close();

	}
}

void TSP::ReadFromFileK(string filename, int counter)//Wczytywanie plików koordynatowych
{
	int count = counter;
	if (coordinates != nullptr)
	{
		for (int i = 0; i < this->Size; i++)
		{
			if (coordinates[i] != nullptr)
			{
				delete[]coordinates[i];
			}
		}
		delete[] coordinates;
	}
	if (distances != nullptr)
	{
		for (int i = 0; i < this->Size; i++)
		{
			if (distances[i] != nullptr)
			{
				delete[] distances[i];
			}
		}
		delete[] distances;
	}

	ifstream fin;
	string input;
	fin.open(filename, ios::in);
	while (input != "DIMENSION:")
	{
		fin >> input;
	}
	fin >> this->Size;
	coordinates = new double*[this->Size];

	while (input != "NODE_COORD_SECTION")
	{
		fin >> input;
	}
	for (int i = 0; i < this->Size; i++)
	{
		coordinates[i] = new double[2];
		fin >> input;
		fin >> coordinates[i][0];
		fin >> coordinates[i][1];
	}
	fin.close();

	if (count == 1)// Jak i poprzednio sprawdzenie za pomocą którego możemy wydrukować lub nie wydrókować nasze koordynaty do konsoli
	{
		for (int i = 0; i < Size; i++)
		{
			cout << "[" << i << "] " << coordinates[i][0] << " " << coordinates[i][1] << endl;
		}
	}
	this->computeDistances();
}

void TSP::computeDistances()//Funkcja która oblicza odleglosci między miastami 
{
	distances = new double*[Size];
	for (int i = 0; i < Size; i++)
	{
		distances[i] = new double[Size];
	}
	for (int i = 0; i < this->Size; i++)
	{
		for (int j = 0; j < this->Size; j++)
		{
			if (i != j)
			{
				distances[i][j] = sqrt(pow(coordinates[i][0] - coordinates[j][0], 2) + pow(coordinates[i][1] - coordinates[j][1], 2));//Obliczenie odleglosci po wzoru
			}
			else
			{
				distances[i][j] = MAX;//jezeli i==j wpisujemy MAX
			}
		}
	}
}

void TSP::RandomData(int size, int counter)//Tworzenie Randomowych danych do pracy z Tabu search
{
	int count = counter;
	if (distances != nullptr)
	{
		for (int i = 0; i < this->Size; i++)
		{
			if (distances[i] != nullptr)
			{
				delete[] distances[i];
			}
		}
		delete[] distances;
	}

	distances = new double*[this->Size = size];
	for (int i = 0; i < size; i++)
	{
		distances[i] = new double[size];
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				distances[i][j] = MAX;//jezeli i==j wpisujemy MAX
			}
			else
			{
				distances[i][j] = (rand() % 100);//jezeli nie to randujemy odleglosci miedzy miastami od 0 d0 100
			}
		}

	}

	if (count == 1)//Proste sprawdzenie za pomocą którego możemy wydrukować lub nie wydrókować maczierz do konsoli
	{
		for (int i = 0; i < this->Size; i++)
		{
			for (int j = 0; j < this->Size; j++)
			{
				cout << distances[i][j] << " " << setw(4);
			}
			cout << endl;
		}
	}
}

void TSP::Swap2(int *route, int *newRoute) const//W tej funkcji robimy swap dwóch sąsiednich elementów
{
	int second, first = rand() % (Size - 1) + 1;
	while ((second = rand() % (Size - 1) + 1) == first);
	for (int i = 0; i < Size; i++)
	{
		newRoute[i] = route[i];
	}
	if (first < second)
	{
		for (int i = first, j = second; i < j; i++, j--)
		{ 
			newRoute[i] = route[j];
			newRoute[j] = route[i];
		}
	}
	else if (first>second)
	{
		for (int i = second, j = first; i < j; i++, j--)
		{
			newRoute[i] = route[j];
			newRoute[j] = route[i];
		}
	}
}

void TSP::decrementTabu(int** tabu) const//Zmniejszamy rozmiar tablicy
{
	for (int i = 0; i < this->Size; i++)
	{
		for (int j = 0; j < this->Size; j++)
		{
			if (tabu[i][j] > 0)//jezeli tablica nie jest pusta 
			{
				tabu[i][j]--;//to zmniejszamy jej rozmiar
			}
		}
	}
}

void TSP::TabuCopyLength(int i, int j, int length, int** tab)//zamienamy długość dwóch sąsiedncih elementów
{
	tab[i][j] = length;
	tab[j][i] = length;
}

int* TSP::nearNeighbour() const
{
	int *Route = new int[this->Size];
	bool *Visited = new bool[this->Size]{ false };
	double NearDistance;
	int NearIndex = 0;
	int Start = rand() % ((this->Size - 1) + 1);//Randomowy wybieramy wierszhołek z którego startujemy
	Route[0] = Start;					   //Ustawaiamy go jako wiershołek początkowy
	Visited[Start] = true;				   //I ustawiamy że już byłi w nim
	for (int i = 1; i < this->Size; i++)
	{
		NearDistance = INFINITE;
		for (int j = 0; j<this->Size; j++)
		{
			if (Visited[j])//sprawdzamy czy wierczhołek już był odwiedzony 
			{
				continue;//jeżeli tak to kontynujemy na natępnu iteracju j
			}
			if (NearDistance > distances[Route[i - 1]][j])
			{
				NearIndex = j;
				NearDistance = distances[Route[i - 1]][j];
			}
		}
		Visited[NearIndex] = true;//Ustawiamy że już byłi w tym wierszcholku
		Route[i] = NearIndex;
	}
	return Route;
}


int * TSP::TabuSearch(int n, int defaultTabu, int crit) const//Algorytm TabuSearch
{
	int Iterations;
	int TabuLen;
	int Critical;
	if (n == -1)//W tych ifach sprawdzamy czy ustawiamy dane wpisane od urzytkownika, czy wybrane wczesniej 
	{
		Iterations = this->Size * 1000;
	}
	else
	{
		Iterations = n;
	}
	if (defaultTabu == -1)
	{
		TabuLen = 3 * (this->Size * 1000);
	}
	else
	{
		TabuLen = defaultTabu;
	}
	if (crit == -1)
	{
		Critical = this->Size;
	}
	else
	{
		Critical = crit;
	}
	int **ListTabu = new int*[this->Size];

	for (int i = 0; i < this->Size; i++)
	{
		ListTabu[i] = new int[this->Size]{ 0 };
	}

	int *OptimalRoute = nearNeighbour();
	int *LocalRoute = new int[this->Size];
	int *OptimalLocalRoute = new int[this->Size];
	int *BestMinimumRoute = new int[this->Size];
	int noImprove = 0;
	int Counter = 0;
	double LocalRouteCost = 0;
	double OptimalLocalRouteCost = 0;
	double BestMinimumRouteCost = 0;
	double OptimalRouteCost = BestMinimumRouteCost = GetRouteLen(OptimalRoute);
	//double routeCost = 0;

	while (++Counter < Iterations)//Wykonujemy tę algotyrm Iterations raz
	{
		OptimalLocalRouteCost = OptimalRouteCost;
		for (int i = 0; i < Size - 1; i++)
		{
			for (int j = i + 1; j < Size; j++)
			{
				CopyTable(OptimalRoute, LocalRoute, this->Size);
				LocalRoute[i] = OptimalRoute[j];
				LocalRoute[j] = OptimalRoute[i];
				LocalRouteCost = GetRouteLen(LocalRoute);
				if ((LocalRouteCost < OptimalLocalRouteCost && ListTabu[OptimalRoute[i]][OptimalRoute[j]] == 0) || LocalRouteCost < OptimalRouteCost)///////////////////////////////////////////////////////////////////
				{
					this->TabuCopyLength(OptimalRoute[i], OptimalRoute[j], TabuLen, ListTabu);//zamienamy długość dwóch sąsiedncih elementów
					OptimalLocalRouteCost = LocalRouteCost;
					CopyTable(LocalRoute, OptimalLocalRoute, this->Size);

				}
			}
		}
		this->decrementTabu(ListTabu);
		if (OptimalLocalRouteCost < OptimalRouteCost)//Jezeli nowy coszt tej iteracji jest mniejszy od poprzedniego wiadomego tej iteracji
		{
			OptimalRouteCost = OptimalLocalRouteCost;
			CopyTable(OptimalLocalRoute, OptimalRoute, this->Size);
			noImprove = 0;
			if (OptimalRouteCost < BestMinimumRouteCost)//Jezeli nowy coszt jest mniejszy od poprzedniego wiadomego najliepszego
			{
				CopyTable(OptimalRoute, BestMinimumRoute, this->Size);
				BestMinimumRouteCost = OptimalRouteCost;
				Counter = 0;
			}
		}
		if (++noImprove > Critical)//Jezeli counter jest wiekszy od warunku krytycznego 
		{
			Swap2(BestMinimumRoute, OptimalRoute);
			OptimalRouteCost = GetRouteLen(OptimalRoute);
			TabuZero(ListTabu);
			noImprove = 0;
		}
	}
	return BestMinimumRoute;

	delete[]LocalRoute;
	delete[]OptimalLocalRoute;
	delete[]OptimalRoute;
}

void TSP::TabuZero(int **tabu) const// Zerujemy nazsę tablicę 
{
	for (int i = 0; i < this->Size; i++)
	{
		for (int j = 0; j < this->Size; j++)
		{
			tabu[i][j] = 0;
		}
	}
}

double TSP::GetRouteLen(int *route) const//w tej funkcji otrzymujemy calu dlugosc przechodzenia po wszystkich miastach
{
	double distance = 0;
	for (int i = 1; i < this->Size; i++)
	{
		distance += distances[route[i - 1]][route[i]];
	}
	distance += distances[route[this->Size - 1]][route[0]];//Tu dodajemy wartość wrócenia w maisto początkowe

	return distance;
}

void TSP::Print(int *route, int optimal) const //Funkcja która drukuje calu sczieżku, dlugosc przechodzenia po wszystkich miastach i błąd, czyli różnicu między wynikiem naszym i poprawnym
{
	for (int i = 0; i < Size; i++)
	{
		cout << route[i] << " -> ";
	}
	double Blad_pomiarowy = ((GetRouteLen(route) - optimal) * 100) / optimal;
	cout << route[0] << endl;
	cout << "Calkowita dlugosc: " << GetRouteLen(route) << endl;
	cout <<"Blad:"<<Blad_pomiarowy <<"%" << endl;

}