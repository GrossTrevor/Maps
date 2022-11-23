#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;

mt19937 random_mt;
map<int, int> rolls;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int nR, int nS) {
	int rand = 0;
	for (int x = 0; x < nR; x++) {
		rand = Random(1, nS);
		rolls[rand] += 1;
	}
}

struct State {
	string name = "";
	int capInc = 0;
	int population = 0;
	int houseInc = 0;
	int households = 0;
};

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
		int numRolls;
		cin >> numRolls;

		cout << "Number of sides on this die: ";
		int numSides;
		cin >> numSides;
		cout << endl;

		RollDice(numRolls, numSides);

		for (int x = 1; x <= numSides; x++) {
			cout << x << ": " << rolls[x] << endl;
		}
	}
	else if (option == 2)
	{
		map<string, State> states;
		ifstream file("states.csv");
		string line = "";
		getline(file, line);
		State state;

		while (!file.eof()) {
			getline(file, state.name, ',');

			getline(file, line, ',');
			state.capInc = stoi(line);

			getline(file, line, ',');
			state.population = stoi(line);

			getline(file, line, ',');
			state.houseInc = stoi(line);

			getline(file, line);
			state.households = stoi(line);

			states.insert(pair<string, State>(state.name, state));
		}
			cout << "1. Print all states" << endl;
			cout << "2. Search for a state" << endl;
			cin >> option;

			if (option == 1) {
				map<string, State>::iterator itr;
				int wait = 0;
				for (itr = states.begin(); itr != states.end(); itr++) {
					if (wait != 0) {
						cout << itr->first << endl;
						cout << "Population: " << itr->second.population << endl;
						cout << "Per Capita Income: " << itr->second.capInc << endl;
						cout << "Median Household Income: " << itr->second.houseInc << endl;
						cout << "Number of Households: " << itr->second.households << endl << endl;
					}
					wait = 1;
				}
			}
			else if (option == 2) {

				string stateName;
				cin >> stateName;

				map<string, State>::iterator itr;
				itr = states.find(stateName);

				if (itr != states.end()) {
					cout << itr->first << endl;
					cout << "Population: " << itr->second.population << endl;
					cout << "Per Capita Income: " << itr->second.capInc << endl;
					cout << "Median Household Income: " << itr->second.houseInc << endl;
					cout << "Number of Households: " << itr->second.households << endl << endl;
				}
				else
					cout << "No match found for " << stateName;
			}
			file.close();
	}
	return 0;
}