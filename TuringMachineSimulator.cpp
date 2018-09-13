//Project of Turing Machine // Ali Forghani // Sadjad University of Technology 
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;

void gotoxy(int x, int y);   //for set console curser position
void color(int colorcode);   //for change the color of output text
struct transition
{
	int source;
	int destination;
	char read;
	char write;
	char move;
};

class turing
{
private:
	int sigma;                //number of sigma 
	int number_state;         //number of state 
	int initial_state;        //initial state
	bool *accept_val;         //state accept checker
	transition *trans;        //value of transitions
	int head_position;        //index of the position of head of memory
	char *RAM;                //alloacating the Read Only Memory
	int number_transitions;   //the number of transitions
	string in;                //the input string
	bool cal;
public:
	turing(bool cal_in)
	{
		cal = cal_in;
		cin >> in;
		fstream input;
		input.open("input_file.txt", ios::in);
		input >> sigma;
		input >> number_state;
		input >> initial_state;
		input >> number_transitions;
		accept_val = new bool[number_state];
		for (int i = 0; i < number_state; i++)
			input >> accept_val[i];
		trans = new transition[number_transitions];
		for (int i = 0; i < number_transitions; i++)
		{
			input >> trans[i].source;
			input >> trans[i].read;
			input >> trans[i].write;
			input >> trans[i].move;
			input >> trans[i].destination;
		}
		int k = 0;
		RAM = new char[80];    //allocating the defult size(80) of memory;
		for (int i = 0; i < 40; i++)
			RAM[i] = '#';
		for (int i = 40; i < 40 + in.size(); i++)
			RAM[i] = in[k++];
		for (int i = 40 + in.size(); i < 80; i++)
			RAM[i] = '#';
		head_position = 40;
		gotoxy(3, 3);
		for (int i = 0; i < 80; i++)
			cout << RAM[i];
		gotoxy(head_position + 3, 4);
		cout << "+";

	}
	bool compile()
	{
		bool check = true;
		int current_state = initial_state;
		if (accept_val[current_state])
		{
			return true;
		}
		else
		{

			while (!accept_val[current_state])
			{
					if (check == false || !cal)
						return false;
					else
						check = false;
				for (int j = 0; j < number_transitions; j++)
				{
					if (trans[j].source == current_state && trans[j].read == RAM[head_position])
					{
						Sleep(1000);
						check = true;
						gotoxy(head_position + 3,4);
						cout << ' ';
						gotoxy(3, 12);
						cout << "from q" << trans[j].source << " goto q" << trans[j].destination << " with transition " << trans[j].read << "," << trans[j].write << "," << trans[j].move;
						RAM[head_position] = trans[j].write;
						if (trans[j].move == 'R')
							head_position++;
						else
							head_position--;
						current_state = trans[j].destination;
						gotoxy(3, 3);
						for (int i = 0; i < 80; i++)
							cout << RAM[i];
						gotoxy(head_position + 3 ,4);
						cout << "+";
						break;
					}
				}
			}
		}

	}


};
void gotoxy(int x, int y)
{
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		position.X = x;
		position.Y = y;

		SetConsoleCursorPosition(hConsole, position);
	}
}
//
void color(int number)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, number);
}
int main()
{
	
	bool cal_in;
	cin >> cal_in;
	turing tr(cal_in);
	bool test = tr.compile();
	gotoxy(3, 10);
	if (test)
		cout << "accepted";
	else
		cout << "rejected";
	system("pause>null");
}