#include <iostream>
#include <conio.h>

using namespace std;

int const n(15);
struct link {
	char key;
	link* next;
};

link* start = NULL;

void init(link* gr[n]);
void new_graph(link* gr[n]);
void add_node(link* gr[n], char a);
void add_arc(link* gr[n]);
void delete_arc(link* gr[n]);
void delete_node(link* gr[n], int i);
int search_node(link* gr[n], char a);
bool search_arc(link* p, char a);
void display(link* gr[n]);
void count_and_display_nodes_with_one_outcoming_and_one_incoming_arc(link* gr[n]);

int main()
{
	setlocale(LC_ALL, "BG");
	char a;
	int choice;
	char answer;
	link* gr[n], * p;
	int i;

	init(gr);

	while (true)
	{
		system("cls");
		system("Color 0E");
		cout << "\n\t\t\tGraph menu" << endl;
		cout << "\n--1. Initialize (Cretate new Graph)";
		cout << "\n--2. Add Node";
		cout << "\n--3. Add Arc";
		cout << "\n--4. Delete Node";
		cout << "\n--5. Delete Arc";
		cout << "\n--6. Search Node";
		cout << "\n--7. Search Arc";
		cout << "\n--8. View existing Nodes";
		cout << "\n--9. Print Nodes with one incoming and outcoming arc";
		cout << "\n-- (E)xit"; 
		cout << "\n\n Choice (1,2,3,4,5,6,7):  ";

		answer = _getch();

		switch (answer)
		{
		case '1':
			cout << "\n\nAre you sure you initialise the Graph.\nNote that every stored information in the graph will be deleted.\nDo you want to continue ?(Y/N) :";
			while (true)
			{
				answer = _getch();
				if (answer == 'Y' || answer == 'y')
				{
					new_graph(gr);
					break;
				}
				else
					if (answer == 'n' || answer == 'N')
					{
						break;
					}
					else
						cout << "\nTry again :";
			} break;

		case '2':
			cout << "\nEnter Node name: " << endl;
			while (cin >> a && ((a >= 65 && a <= 90) || (a >= 97 && a <= 122)))
			{
				if (search_node(gr, a) == -1)
				{
					add_node(gr, a);
					cout << "\nThe Node has been succesfully added" << endl;
				}
				else
				{
					cout << "\nThe Node already exist" << endl;
				}
				cout << "\nEnter Node name: " << endl;
			}
			break;

		case '3':
			answer = 'y';
			while (answer == 'y' || answer == 'Y')
			{
				add_arc(gr);
				cout << "\nWant to add new Arc (Y/N) : ";
				answer = _getch();
			}break;

		case '4':

			cout << "\n\n Deleting Node : ";
			cout << "\nEnter Node to delete ";
			do
			{
				cin >> a;
			} while ((a < 65 || a > 90) && (a < 97 || a > 122));
			if (search_node(gr, a))
			{
				i = search_node(gr, a);
				delete_node(gr, i);
				cout << "\nThe Node has been succesfully removed" << endl;
			}
			else
			{
				cout << "\nThe Node does not exist" << endl;
			}
			system("pause");
			break;

		case '5':
			cout << "\n\n Deleting Arc : ";
			delete_arc(gr);
			system("pause");
			break;

		case '6':
			cout << "\n\n Searching Node :";
			do {
				cin >> a;
			} while ((a < 65 || a > 90) && (a < 97 || a > 122));

			if (search_node(gr, a) == -1)
			{
				cout << "\nThis Node does not exist" << endl;
			}
			else
			{
				cout << "\nThis Node exist" << endl;
			}
			system("pause");
			break;

		case '7':
			cout << "\n\n Searching Arc: ";
			cout << "\n First Node: ";
			cin >> a;
			if (search_node(gr, a) == -1) {
				cout << "\n This Node does not exist" << endl;
				system("pause");
				break;
			}

			i = search_node(gr, a);

			cout << "\n Second Node: ";
			cin >> a;
			if (search_node(gr, a) == -1) {
				cout << "\n This Node does not exist" << endl;
				system("pause");
				break;
			}

			p = gr[i];
			if (search_arc(p, a))
			{
				cout << "\n This Arc does exist" << endl;
			}
			else
			{
				cout << "\n This Arc does not exist" << endl;
			}
			system("pause");
			break;

		case '8':
			cout << "\nAll Nodes : ";
			display(gr);
			cout << endl;
			system("pause");
			break;

		case '9':count_and_display_nodes_with_one_outcoming_and_one_incoming_arc(gr); break;

		
		case 'e':
		case 'E':
			cout << "\n\nAre you sure you want to Exit (Y/N) :";
			while (true)
			{
				answer = _getch();
				if (answer == 'Y' || answer == 'y')
				{
					exit(0);
				}
				if (answer == 'n' || answer == 'N')
				{
					break;
				}
				cout << "\nTry again :";
			}
			break;
		}
	}
	return 0;
}

void init(link* gr[n])
{
	for (int i = 0; i < n; i++)
	{
		gr[i] = NULL;
	}
}

void new_graph(link* gr[n])
{
	system("cls");
	link* p = new link();
	for (int i = 0; i < n; i++)
	{
		while (gr[i])
		{
			p = gr[i];
			gr[i] = gr[i]->next;
			delete p;
		}
	}
	cout << "\n\nThe Graph was Initialised!" << endl;
	system("pause");
}

void add_node(link* gr[n], char a)
{
	for (int i = 0; i < n; i++)
		if (!gr[i])
		{
			link* p = new link();
			p->key = a;
			p->next = gr[i];
			gr[i] = p;
			break;
		}
}


void add_arc(link* gr[n])
{
	char c1, c2;

	cout << "\n The arc is created like this : Arc1( NODE1->NODE2) , Arc2(NODE2->NODE1).....";
	cout << "\n\n Use the folowing nodes: ";
	display(gr);
	cout << "\nFirst Node: ";
	do
	{
		c1 = getchar();
	} while ((c1 < 65 || c1 > 90) && (c1 < 97 || c1 > 122));

	cout << "\nSecond Node: ";
	do
	{
		cin >> c2;
	} while ((c2 < 65 || c2 > 90) && (c2 < 97 || c2 > 122));

	//Proverqvame dali vuzlite sushtestvuvat, ako ne gi suzdavame
	if (search_node(gr, c1) == -1)
	{
		add_node(gr, c1);
		cout << "\nThe Node " << c1 << " was added in order to create Arc";
	}

	if (search_node(gr, c2) == -1)
	{
		add_node(gr, c2);
		cout << "\nThe Node " << c2 << " was added in order to create Arc";
	}

	int i = search_node(gr, c1);
	link* p = gr[i]->next;
	if (!search_arc(p, c1))
	{
		if (c1 != c2)
		{
			link* t = new link();
			t->next = gr[i]->next;
			t->key = c2;
			gr[i]->next = t;
			cout << "\nThe Arc has been succesfully added in following order: " << c1 << " -> " << c2 << endl;
		}
		else
		{
			cout << "\nYou can't create arc with one Node!";
		}
	}
	else
	{
		cout << "\nThe Arc already exist" << endl;
	}
}

void delete_arc(link* gr[n])
{
	system("cls");
	char c1, c2;
	cout << "\n -Deleting Arc-";
	cout << "\n\n Existing Nodes:";
	display(gr);

	cout << "\nEnter first Node: ";
	while (true)
	{
		cin >> c1;
		if (search_node(gr, c1) == -1)
			cout << "\nThis Node does not exist in the graph. Please try again: ";
		else
			break;

	}

	cout << "\nEnter second Node: ";
	while (true)
	{
		cin >> c2;
		if (search_node(gr, c2) == -1)
			cout << "\nThis Node does not exist in the graph. Please try again: ";
		else
			break;
	}

	int i = search_node(gr, c1);
	link* p = gr[i], * q = p;
	if (search_arc(p, c2))
	{
		while (p)
		{
			if (p->key == c2)
			{
				q->next = p->next;
				delete p;
				cout << "\nThe Arc has been succesfully removed" << endl;
				break;
			}
			q = p;
			p = p->next;
		}
	}
	else
	{
		cout << "\nThe Arc does not exist" << endl;
	}
}

void  delete_node(link* gr[n], int i)
{
	while (gr[i])
	{
		link* p = new link();
		p = gr[i];
		gr[i] = gr[i]->next;
		delete p;
	}
}

int search_node(link* gr[n], char a)
{
	for (int i = 0; i < n; i++)
	{
		if (gr[i])
			if (gr[i]->key == a)
			{
				return i;
			}
	}
	return -1;
}

bool search_arc(link* p, char a)
{
	while (p)
	{
		if (p->key == a)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}

void display(link* gr[n])
{
	int br(0);
	for (int i = 0; i < n; i++)
	{
		if (gr[i])
			cout << gr[i]->key << " ";
		else br++;
	}
	if (br == n)
		cout << "\nThe graph is empty" << endl;
}

void count_and_display_nodes_with_one_outcoming_and_one_incoming_arc(link* gr[n])
{
	char a;
	bool b;
	int br(0);
	for (int i = 0; i < n; i++)
	{
		if (!gr[i] || !gr[i]->next)
		{
			continue;
		}
		a = gr[i]->key;
		b = false;
		for (int j = 0; j < n; j++)
		{
			if (b)
			{
				break;
			}
			if (gr[j] && a == gr[j]->key)
			{
				continue;
			}
			link* p = gr[j];
			while (p)
			{
				if (p->key == a)
				{
					br++;
					cout << "Node - " << gr[i]->key << endl;
					b = true;
					break;
				}
				p = p->next;
			}
		}
	}
	cout << "BR = " << br << endl;
	system("pause");
}