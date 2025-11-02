#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "input.h"
#include <queue>
#include <vector>
#include <deque>
#include <chrono>
#include <thread>
#include <windows.h>
#include <mutex>
#include "WarGame.h"
#include "Patient.h"
#include "PrintableItem.h"
#include "CashRegister.h"


using namespace std;

void option1();
void option2();
void option3();

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
	    case 3: option3(); break;
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






void option3()
{
	const char INDENT = '\t';
void drawParticle(PrintableItem&, const int&, const int&);
void moveParticle(PrintableItem&, const int&, const int&);
int findShortestIndex(CashRegister*, const int&);
void displayOption3Banner();
void drawRegisters(CashRegister*, int);
typedef PrintableItem Customer;
srand(static_cast<unsigned>(time(nullptr)));

// Get console dimensions
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
int customersServed = 0;

const int DEFAULT_X = 0;
const int DEFAULT_Y = 0;
int centerX = width / 2;
int centerY = height / 2;

displayOption3Banner();

int numOfSeconds = 0;
int numRegisters = 0;
int i = 0;
CashRegister* registers = nullptr;
constexpr int MAXSECONDS = 37800;

cout << "\n\n" << INDENT << "Enter number of seconds (0 < n < 37800): ";
cin >> numOfSeconds;
if (numOfSeconds > MAXSECONDS || numOfSeconds <= 0)
throw runtime_error("ERROR: Invalid seconds entered.");

cout << "\n" << INDENT << "Enter number of open cash registers (1...10): ";
cin >> numRegisters;
if (numRegisters < 1 || numRegisters > 10)
throw runtime_error("ERROR: Invalid number of registers.");

registers = new CashRegister[numRegisters];

// Arrange registers vertically (tight spacing so 10 fit)
int spacing = max(2, height / (numRegisters + 3));
int regX = 8;
const int SCREENCONST = 3;
for (int i = 0; i < numRegisters; ++i) {
    spacing = max(2, height / (numRegisters + 3));
    spacing = (numRegisters > 5) ? spacing + SCREENCONST * i : spacing * (i + 1);
    spacing += SCREENCONST;

    registers[i].setX(regX);
    registers[i].setY(spacing);
}

auto displayCostcoProg = []()->void {

    };
for (int elapsed = 0; elapsed <= numOfSeconds; ++elapsed) {

    system("cls");
    displayOption3Banner();

    cout << INDENT << "Elapsed time: " << elapsed
        << " seconds out of " << numOfSeconds << "|| Customers Served: " << customersServed << "\n\n\n\n";

    for (int i = 0; i < numRegisters; i++) {
        registers[i].drawQueue();
    }

    if (elapsed > 0) {
        if (elapsed % 1 == 0) {
            i = i % numRegisters;
            registers[i].removeCustomer();
            customersServed++;
        }
    }
    for (int spawner = 0; spawner < 3; ++spawner) {

        PrintableItem customer('*', DEFAULT_X, DEFAULT_Y);
        PrintableItem customer2('*', DEFAULT_X + 1, DEFAULT_Y + 1);
        int spawnYOffset = spawner * 2;
        drawParticle(customer, centerX, centerY + spawnYOffset);
        drawParticle(customer2, centerX, centerY + spawnYOffset + 1);

        int shortest = findShortestIndex(registers, numRegisters);

        COORD dest = registers[shortest].getNextCustomerPosition();

        registers[shortest].appendCustomer(customer);

        moveParticle(customer, dest.X, dest.Y);

        for (int i = 0; i < numRegisters; ++i) {
            registers[i].drawQueue();
        }
        shortest = findShortestIndex(registers, numRegisters);
        dest = registers[shortest].getNextCustomerPosition();

        registers[shortest].appendCustomer(customer2);

        moveParticle(customer2, dest.X, dest.Y);

        for (int i = 0; i < numRegisters; ++i) {
            registers[i].drawQueue();
        }

    }

    if (elapsed % 1 == 0) {
        i = i % numRegisters;
        registers[i].removeCustomer();
        customersServed++;
    }






    this_thread::sleep_for(chrono::milliseconds(20));
}

cout << "\nSimulation complete.\n";
delete[] registers;

}

int findShortestIndex(CashRegister* registers, const int& total) {
    int shortest = 0;
    for (int i = 1; i < total; ++i)
        if (registers[i].lineLength() < registers[shortest].lineLength())
            shortest = i;
    return shortest;
}

void drawRegisters(CashRegister* registers, int count) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < count; ++i) {
        COORD pos = { (SHORT)registers[i].getX(),
                      (SHORT)registers[i].getY() };
        SetConsoleCursorPosition(hConsole, pos);
        cout << registers[i].draw();
    }
}

void drawParticle(PrintableItem& obj, const int& x, const int& y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, pos);
    cout << obj;
    obj.setX(x);
    obj.setY(y);
}
void moveParticle(PrintableItem& obj, const int& endX, const int& endY) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (obj.getX() != endX || obj.getY() != endY) {
        COORD pos = { static_cast<SHORT>(obj.getX()), static_cast<SHORT>(obj.getY()) };
        SetConsoleCursorPosition(hConsole, pos);
        cout << obj;
        this_thread::sleep_for(chrono::milliseconds(20)); // smoother movement
        SetConsoleCursorPosition(hConsole, pos);
        cout << ' ';

        if (obj.getX() < endX) obj.setX(obj.getX() + 1);
        else if (obj.getX() > endX) obj.setX(obj.getX() - 1);
        if (obj.getY() < endY) obj.setY(obj.getY() + 1);
        else if (obj.getY() > endY) obj.setY(obj.getY() - 1);
    }

    COORD finalPos = { static_cast<SHORT>(obj.getX()), static_cast<SHORT>(obj.getY()) };
    SetConsoleCursorPosition(hConsole, finalPos);
    cout << obj;
}

void displayOption3Banner() 
{
	const char INDENT = '\t';
    cout << INDENT << (char)218 << string(60, (char)196) << (char)191 << "\n";
    cout << INDENT << '|' << " 3> Simulation of checkout lines at a CostCo warehouse store |\n";
    cout << INDENT << (char)192 << string(60, (char)196) << (char)217 << "\n";
}
