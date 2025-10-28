#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "input.h"
#include <queue>
#include <vector>
#include <deque>
#include "WarGame.h"
#include "Patient.h"


using namespace std;

void option1();
void option2();
//void option3();

int main()
{
	do
	{
		system("cls");
		cout << "\n\t\t CMPR131 Chapter 8: Applications using Queues Anthony Herrera";
		cout << "\n\t\t" << string(70, char(205));
		cout << "\n\t\t1> Simulation of War (card game) using deque STL";
		cout << "\n\t\t2> Simulation of an emergency room (ER) using priority queue STL (DONE)";
		cout << "\n\t\t3> Simulation of checkout lines at CostCo using multiple queues STL";
		cout << "\n\t\t" << string(70, char(196));
		cout << "\n\t\t0> Exit";
		cout << "\n\t\t" << string(70, char(205)) << '\n';
		switch (inputInteger("\t\t  Option: ", 0, 3))
		{
		case 0: exit(1);
		case 1: option1(); break;
		case 2: option2(); break;
			//			case 3: option3(); break;
		default: cout << "\n\tERROR: invalud option.\n";
		}

		cout << '\n';
		system("pause");

	} while (true);

	return 0;
}

void option1()
{

	system("cls");
	cout << "\n\t1> Simulation of War (card game) using deque STL";
	int cardsInSuit = inputInteger("\n\tEnter a number of cards per suite: ", 1, 13);

	WarGame game(cardsInSuit);
	game.play();
	
}

void option2()
{

	system("cls");
	cout << "\n\t2> Simulation of an emergency room (ER) using priority queue STL\n";

	priority_queue<Patient> pq2; //key
	vector<Patient> submit;

	do
	{
		system("cls");
		cout << "\n\t2> Simulation of an emergency room (ER) using priority queue STL";
		cout << "\n\t" << string(60, char(205));
		cout << "\n\t\tA> Register a patient";
		cout << "\n\t\tB> Transfer patient(s) to the designation";
		cout << "\n\t\tC> Display transferred patients";
		cout << "\n\t" << string(60, char(196));
		cout << "\n\t\t0> return\n";
		cout << "\n\t" << string(60, char(205));

		switch (toupper(inputChar("\n\t\tOption: ", static_cast<string>("ABC0"))))
		{
		case '0': return;
		case 'A':
		{
			Patient patient;
			string name;
			cout << "\n\t\tEnter the patient's name: ";
			getline(cin, name);
			patient.setName(name);
			patient.setAge(inputInteger("\t\tEnter the patient's age: ", true));
			patient.setCheckedInTime(time(0));
			patient.setGender(toupper(inputChar("\t\tChoose the patient's gender (F-female or M-male): ", 'F', 'M')));
			patient.setPriority(inputInteger("\t\tChoose the ER level 1)Non-urgent, 2)Less Urgent, 3)Urgent, 4)Emergent, or 5)Resuscitation: ", 1, 5));

			pq2.push(patient); // enqueue
			cout << "\n\t\tPatient information has been registered.\n\n";
		}
		break;
		case 'B':
		{
			if (!pq2.empty())
			{
				if (pq2.top().getPriority() == 5)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to ICU...\n\n";
					pq2.pop(); // dequeue
					break;
				}
				else if (pq2.top().getPriority() == 4)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to surgery room...\n\n";
					pq2.pop();
					break;
				}
				else if (pq2.top().getPriority() == 3)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to emergency room...\n\n";
					pq2.pop();
					break;
				}
				else if (pq2.top().getPriority() == 2)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to x-ray lab...\n\n";
					pq2.pop();
					break;
				}
				else if (pq2.top().getPriority() == 1)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - examines and gives prescription...\n";
					pq2.pop();
					break;
				}
			}
		}
		break;
		case 'C':
		{
			if (!submit.empty())
			{

				sort(submit.begin(), submit.end());
				reverse(submit.begin(), submit.end());
				cout << '\n';
				for (int i = 0; i < submit.size(); i++)
					cout << "\t\t" << i + 1 << " - " << submit[i] << '\n';
			}
			else
				cout << "\n\t\tNo patient has been transferred.\n\n";
		}
		break;
		}

		cout << "\n";
		system("pause");
	} while (true);
}

