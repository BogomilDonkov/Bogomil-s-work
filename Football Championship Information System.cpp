#include <iostream>
#include <iomanip>
#include <conio.h> 
#include <string>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <windows.h>
using namespace std;

const int N(5);
const int M(81);
struct team { int num; char name[50]; char city[50]; int year; int lose; };

int linecounter(string fileName);  //брояч на редове във файл

//Главно меню
void mainmenu(team mas[], int br, string mas1[]);

//Подменюта
void add_submenu(team mas[], int& br, string mas1[]);
void print_submenu(team mas[], int br, string mas1[]);
void championship_submenu(team mas[], int br, string mas1[]);
void search_submenu(team mas[], int br, string mas1[]);
void inquiry_submenu(team mas[], int br, string mas1[]);

//Функции на първо подменю
void add(team mas[],int br,string mas1[]);	//добавя един отбор
void teamTextFileSave(team mas[], int &br,string mas1[]);  //добавя във файл !
void add_n(team mas[], int &br,int &n,string mas1[]);	//записва n на брой отбори
void teamsTextFileSave(team mas[], int &br,int n, string mas1[]);	//пренаписва файл !

//Функции на второ подменю
void TeamsTextFileRead(team mas[], int br, string mas1[]);	//чете от файла със отборите
void find_youngest(team mas[], int br, string mas1[]);  
void find_loosers(team mas[], int br, string mas1[]);

//Функции на трето подменю
void championship(team mas[], int br, string mas1[]);  
void read_results(team mas[], int br,string mas1[]);
void print_results(team mas[], int br,string mas1[]);

//Функции на четвърто подменю
void searchByName(team mas[], int br, string mas1[]);
void searchByNames(team mas[], int br, string mas1[]);

//Функции на пето подменю
void sort_youngest(team mas[], int br, string mas1[]);
void sort_winners(team mas[], int br, string mas1[]);
void print(team mas[], int br, string mas1[]);
void find_mostGoals(team mas[], int br, string mas1[]);
void find_BestAbs(team mas[], int br, string mas1[]);

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	system("Color 0A");
	srand(time(0));
	setlocale(LC_ALL, "BG");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	team mas[N];
	string mas1[M];
	int br = linecounter("Teams.txt") / 4;
	mainmenu(mas,br,mas1);
	return 0;
}

int linecounter(string fileName)
{
	int n(0);
	string line;
	fstream file;
	file.open(fileName, ios::in);
	if (file.is_open()) {
		while (getline(file, line))
		{
			n++;
		}
		file.close();
	}
	return n;
}

void mainmenu(team mas[], int br,string mas1[])
{	
	char choice;
	do {
		system("cls");
		cout << endl << "Информационна система за футболно първенство" << endl;
		cout << endl << "1. Добавяне на участници в първенството";
		cout << endl << "2. Извеждане на отбори от първенството на екрана ";
		cout << endl << "3. Провеждане на първенството";
		cout << endl << "4. Търсене на отбори в първенството";
		cout << endl << "5. Справки за участващите отбори";
		cout << endl << "6. Изход";
		cout << endl << endl << "Въведи избор (1,2,3,4,5,6)";
		choice = _getch();
		switch (choice)
		{
		case '1':add_submenu(mas, br, mas1); choice = 0; break;
		case '2':print_submenu(mas, br,mas1); choice = 0; break;
		case '3':championship_submenu(mas, br,mas1); choice = 0; break;
		case '4':search_submenu(mas, br, mas1); choice = 0; break;
		case '5':inquiry_submenu(mas, br, mas1); choice = 0; break;
		case '6':return;
		default:cout << "Няма такава опция. Моля въведете наново :";
		}
	} while (choice < '1' || choice>'6');
}

void add_submenu(team mas[], int &br,string mas1[])
{
	char choice;
	do 
	{
		system("cls");
		cout <<endl<< "Добавяне на участници в първенството ";
		cout << endl << endl << "Регистрирани отбори до момента : " << br;
		cout << endl << endl << "1. Добавяне на един отбор ";
		cout << endl << "2. Запис на списък от n на брой отбори (Първенството може да се състои с от 3 до 5 отбора)";
		cout << endl << "3. Назад";
		cout << endl << endl << "Въведи избор (1,2,3):";
		choice = _getch();
		switch (choice)
		{
		case '1':add(mas, br, mas1); teamTextFileSave(mas, br, mas1); choice = 0; break;
		case '2':int n; add_n(mas, br, n,mas1); teamsTextFileSave(mas, br, n,mas1); choice=0; break;
		case '3':return; break;
		default:cout << "Няма такава опция. Моля въведете наново :";
		}
    }while (choice < '1' || choice>'3');
}
void print_submenu(team mas[], int br,string mas1[])
{	
	char choice;
	do
	{
		system("cls");
		cout <<endl<< "Извеждане на участниците от първенството "<<endl;
		cout << endl << endl << "1. Извеждане на отбори с най-ранна година на основаване ";
		cout << endl << "2. Извеждане на отбори с най-малко загуби ";
		cout << endl << "3. Назад";
		cout << endl << endl << "Въведи избор (1,2,3):";
		choice = _getch();
		switch (choice)
		{
		case '1':TeamsTextFileRead(mas, br, mas1); find_youngest(mas, br, mas1); choice = 0; break;
		case '2':TeamsTextFileRead(mas, br, mas1); find_loosers(mas, br, mas1); choice = 0; break;
		case '3':return; break;
		default:cout << "Няма такава опция. Моля въведете наново :";
		}
	} while (choice < '1' || choice>'3');
}
void championship_submenu(team mas[], int br,string mas1[])
{	
	char choice;
	do
	{
		system("cls");
		cout << endl << "Провеждане на турнира " << endl;
		cout << endl << endl << "1. Провеждане на турнир ";
		cout << endl << "2. Извеждане на таблица с резултатите ";
		cout << endl << "3. Назад";
		cout << endl << endl << "Въведи избор (1,2,3):";
		choice = _getch();
		switch (choice)
		{
		case '1':TeamsTextFileRead(mas, br, mas1); championship(mas, br, mas1); choice=0; break;
		case '2':read_results(mas, br, mas1); print_results(mas, br, mas1); choice = 0;  break;
		case '3':return; break;
		default:cout << "Няма такава опция. Моля въведете наново :";
		}
	} while (choice < '1' || choice>'3');
}
void search_submenu(team mas[], int br, string mas1[])
{	
	char choice;
	do
	{
		system("cls");
		cout << endl << "Търсене на отбори в първенството" << endl;
		cout << endl << endl << "1. Извеждане на отбора със всички изиграни мачове по въведено име на отбор";
		cout << endl << "2. Извеждане на резултатите от изиграните мачове за два отбора по въведени имена";
		cout << endl << "3. Назад";
		cout << endl << endl << "Въведи избор (1,2,3):";
		choice = _getch();
		switch (choice)
		{
		case '1': TeamsTextFileRead(mas, br, mas1); searchByName(mas, br, mas1); choice=0; break;
		case '2': searchByNames(mas, br, mas1); choice=0; break;
		case '3':return; break;
		default:cout << "Няма такава опция. Моля въведете наново :";
		}
	} while (choice < '1' || choice>'3');
}
void inquiry_submenu(team mas[], int br, string mas1[])
{
	char choice;
	do
	{
		system("cls");
		cout <<endl<< "Справки за участващите отбори."<<endl;
		cout << endl << endl << "1. Извеждане на всички участниците в подреден ред по година на основаване.";
		cout << endl << "2. Извеждане на всички участниците в подреден ред по спечелени точки.";
		cout << endl << "3. Извеждане на отбора, отбелязал най-много попадения.";
		cout << endl << "4. Извеждане на отбора с най-добра голова разлика.";
		cout << endl << "5. Назад.";
		cout << endl << endl << "Въведи избор (1,2,3,4,5):";
		choice = _getch();
		switch (choice)
		{
		case '1':TeamsTextFileRead(mas, br, mas1); sort_youngest(mas, br, mas1); print(mas, br, mas1); choice=0; break;
		case '2':TeamsTextFileRead(mas, br, mas1); sort_winners(mas, br, mas1); print(mas, br, mas1); choice=0; break;
		case '3':TeamsTextFileRead(mas, br, mas1); read_results(mas,br,mas1); find_mostGoals(mas, br, mas1); choice=0; break;
		case '4':TeamsTextFileRead(mas, br, mas1); read_results(mas, br, mas1); find_BestAbs(mas, br, mas1); choice=0; break;
		case '5': return; break;
		default:cout << "Няма такава опция. Моля въведете наново :";
		}
	} while (choice < '1' || choice>'5');
}

//add_submenu
void add(team mas[], int br,string mas1[])
{
	system("cls");
	char choice;
	do {	
		cout << endl << endl << "Регистрирани отбори до момента : " << br;
		if (br == 5) { cout << endl << "Достигнахте лимита от 5 отбора за първенството"; system("pause"); add_submenu(mas, br,mas1); }
		cout << endl <<endl<< "Добавяне на участник в първенството";
		mas[br].num = br + 1;
		cout << endl << "Регистрационен номер -  " << mas[br].num;	
		cin.ignore();
		cout << endl << "Име на отбор : "; cin.getline(mas[br].name, 50);
		cout << endl << "Град : ";	cin.getline(mas[br].city, 50);
		cout << endl << "Година на основаване : "; cin >> mas[br].year;
		mas[br].lose = 0;
		cout << endl << endl << "Искате ли да въведете още един отбор (Y/N): ";
		choice = _getch();		
		cin.ignore();
	}
	while (choice == 'y' || choice == 'Y');
}
void teamTextFileSave(team mas[], int &br,string mas1[])
{
	fstream file;
	file.open("Teams.txt", ios::app);
	file << mas[br].name << endl;
	file << mas[br].city << endl;
	file << mas[br].year << endl;
	file << mas[br].lose << endl;
	file.close();
	br++;
	cout << "Отборa беше добавен във файла Teams.txt" << endl;
	system("pause");
}
void add_n(team mas[], int &br,int &n,string mas1[])
{
	system("cls");
	cout << endl<< "Колко отбора искате да добавите ? ";
	cout << endl << "Въведете избор :";
	cin >> n;	
	cin.ignore();

		if (n<3||n > 5) { cout << endl << "Невалиден избор!\nУчастващите отбори трябва да са не по-малко от 3 и не повече от 5 на брой.\nМоля въведете наново : "; system("pause"); add_submenu(mas, br,mas1); }
		br = 0;
		cout << endl << endl << "Регистрирани отбори до момента : " << br;
		for (int i = br; i <br+n; i++)
		{	
			
			cout << endl << endl << "Добавяне на участник в първенството";
			mas[i].num = i + 1;
			cout << endl << "Регистрационен номер -  " << mas[i].num;
			cout << endl << "Име на отбор : ";	cin.getline(mas[i].name, 50);
			cout << endl << "Град : ";  cin.getline(mas[i].city, 50);
			cout << endl << "Година на основаване : ";	cin >> mas[i].year;
			mas[i].lose=0;	
			cin.ignore();
		}	
}
void teamsTextFileSave(team mas[], int &br,int n,string mas1[])
{
	
	fstream file;
	file.open("Teams.txt", ios::out);
	for (int i = 0; i < n; i++)
	{
		file << mas[i].name << endl;
		file << mas[i].city << endl;
		file << mas[i].year << endl;
		file << mas[i].lose << endl;
		br++;
	}
	file.close();
	cout << "Отборите бяха запазени във файла Teams.txt" << endl;
	system("pause");
}

//print_submenu
void TeamsTextFileRead(team mas[], int br,string mas1[])
{
	cout << "Данните бяха прочетени от файла" << endl;
	fstream file;
	file.open("Teams.txt", ios::in);
	for (int i = 0; i < br; i++)
	{		
		mas[i].num = i + 1;		
		file.getline(mas[i].name, 50);
		file.getline(mas[i].city, 50);		
		file >> mas[i].year;
		file >> mas[i].lose;	
		file.ignore();
	}
	file.close();
}
void find_youngest(team mas[], int br, string mas1[])
{
	team young=mas[0];
	for (int i = 1; i < br; i++)
	{
		if (young.year > mas[i].year)
		{
			young = mas[i];
		}
	}
	for (int i = 0; i < br; i++)
	{
		if (young.year == mas[i].year)
		{
			cout << endl << "Регистрационен номер -  " << mas[i].num;
			cout << endl << "Име на отбор : " << mas[i].name;
			cout << endl << "Град : " << mas[i].city;
			cout << endl << "Година на основаване : " << mas[i].year;
			cout << endl << "Брой загуби : " << mas[i].lose;
			cout << endl;
		}
	}
	system("pause");	
}
void find_loosers(team mas[], int br, string mas1[])
{
	team min_lost = mas[0];
	
	for (int i = 1; i < br; i++)
	{
		if (min_lost.lose > mas[i].lose)
		{
			min_lost = mas[i];
		}
	}
	for (int i = 0; i < br; i++)
	{
		if (min_lost.lose == mas[i].lose)
		{
			cout << endl << "Регистрационен номер -  " << mas[i].num;
			cout << endl << "Име на отбор : " << mas[i].name;
			cout << endl << "Град : " << mas[i].city;
			cout << endl << "Година на основаване : " << mas[i].year;
			cout << endl << "Брой загуби : " << mas[i].lose;
			cout << endl;
		}
	}
	system("pause");
}

//championship_submenu
void championship(team mas[], int br,string mas1[])
{
	fstream file,file1;
	
	system("cls");
	file.open("Results.txt", ios::out);	
	if (!file.is_open()) { cout << endl << "Файлът не е отворен"; }
	else {
		for (int i = 0; i < br; i++)
		{			
			for (int k = 0; k < br; k++)
			{
				int min=0;
				int max=7;
				if (!(i == k)) 
				{
					min = min + (rand() % (max - min + 1));//random rezultat na domakinite
					max = min + (rand() % (max - min + 1));//random rezultat na gostite
					file << mas[i].name << endl;
					file << mas[k].name << endl;
					file << min << endl;
					file << max << endl;
					if (min > max) { mas[k].lose++; }
					if (min < max) { mas[i].lose++; }					
				}
			}
			cout << endl;
		}
		file.close();
		file1.open("Teams.txt", ios::out);
		for (int i = 0; i < br; i++)
		{
			file1 << mas[i].name << endl;
			file1 << mas[i].city << endl;
			file1 << mas[i].year << endl;
			file1 << mas[i].lose << endl;
		}
		file1.close();
		cout <<endl<< "Резултати бяха записани в Results.txt"<<endl;
		system("pause");
	}
}
void read_results(team mas[], int br,string mas1[])
{
	fstream file;
	
	file.open("Results.txt",ios::in);
	int index(0);

	if (!file.is_open()) { cout << endl << "Файлът не е отворен"; }
	else {
		while(!file.eof())
		{
          getline(file, mas1[index]);
			getline(file, mas1[index + 1]);
			getline(file, mas1[index + 2]);
			getline(file, mas1[index + 3]);						
			index += 4;
		}
	}
	file.close();
}
void print_results(team mas[], int br,string mas1[])
{
	system("cls");	
	for (int i = 0; i < linecounter("Results.txt"); i += 4)
	{
		cout <<endl<< mas1[i] << " - " << mas1[i+1] << " : " << mas1[i + 2] <<" - "<< mas1[i + 3];
	}	
	system("pause");
}

//search_submenu
void searchByName(team mas[], int br, string mas1[])
{
	system("cls");
	string name;
	int index;
	cout << endl << "Въведете име на отбора който търсите :";
	getline(cin, name);
	for (int i = 0; i < br; i++)
	{
		if (name == mas[i].name)
		{
			index = i;
			for (int k = 0; k < br; k++)
			{
				if (index == k) { continue; }
				cout << endl << name << " - " << mas[k].name;
			}
			break;
		}
	}
	cout << endl;
	system("pause");
}
void searchByNames(team mas[], int br, string mas1[])
{
	system("cls");
	fstream file;
	string nameToSearch1, nameToSearch2,nameInFile1, nameInFile2;
	int score1, score2;
	cout << endl << " Въведете името на първият отбор :";
	getline(cin, nameToSearch1);
	cout << endl << " Въведете името на вторият отбор :";
	getline(cin, nameToSearch2);
	file.open("Results.txt", ios::in);
	for (int i = 0; i < linecounter("Results.txt"); i++)
	{
		getline(file, nameInFile1);
		getline(file, nameInFile2);
		if (nameToSearch1 == nameInFile1 && nameToSearch2 == nameInFile2)
		{
			file >> score1;
			file >> score2;
			cout << endl << nameToSearch1 << " - " << nameToSearch2 << " : " << score1 << " - " << score2;
	        file.ignore();
		}
		if (nameToSearch1 == nameInFile2 && nameToSearch2 == nameInFile1)
		{
			file >> score1;
			file >> score2;
			cout << endl << nameToSearch2 << " - " << nameToSearch1 << " : " << score1 << " - " << score2;
			file.ignore();
		}		
	}
	file.close();
	cout << endl;
	system("pause");
}

//inquiry_submenu
void sort_youngest(team mas[], int br,string mas1[])
{
	for (int i = 0; i < br-1; i++)
	{
		for (int k = 0; k < br -i- 1; k++)
		{
			if (mas[k].year > mas[k + 1].year)
			{
				team buffer = mas[k];
				mas[k] = mas[k + 1];
				mas[k + 1] = buffer;
			}
		}
	}
}
void sort_winners(team mas[], int br,string mas1[])
{
	for (int i = 0; i < br; i++)
	{
		for (int k = 0; k < br - i - 1; k++)
		{
			if (mas[k].lose > mas[k + 1].lose)
			{
				team buffer = mas[k];
				mas[k] = mas[k + 1];
				mas[k + 1] = buffer;
			}
		}
	}
}
void print(team mas[], int br,string mas1[])
{
	system("cls");
	cout << endl << endl << "Извеждане на участниците в първенството с най-ранна година на основаване "<<endl;
	for (int i = 0; i < br; i++)
	{
		cout << endl << "Регистрационен номер -  " << mas[i].num;
		cout << endl << "Име на отбор : "<< mas[i].name;
		cout << endl << "Град : "<< mas[i].city;
		cout << endl << "Година на основаване : "<< mas[i].year;
		cout << endl << "Брой загуби : " << mas[i].lose;
		cout << endl;
	}
	cout << endl;
	system("pause");
}
void find_mostGoals(team mas[], int br, string mas1[])
{
	fstream file;
	int goals1, goals2,mostGoals(0);
	string name1,name2,topName;
	file.open("Results.txt", ios::in);
	for (int i = 0; i < linecounter("Results.txt")/4; i++)
	{
		getline(file, name1);
		getline(file, name2);
		file >> goals1;
		file >> goals2;
		file.ignore();
		if (mostGoals < goals1)
		{
			mostGoals = goals1;			
		}
		if (mostGoals < goals2)
		{
			mostGoals = goals2;		
		}	
	}
	file.close();
	for (int i = 0; i < linecounter("Results.txt"); i++)
	{
		if (mas1[i+2] == to_string(mostGoals)&& mas1[i] != topName)
		{			
			topName = mas1[i];
			cout << endl << "Име на отбор : " << mas1[i];
			cout << endl << "Брой на вкарани голове :" << mostGoals;
			cout << endl;
		}
	}	
	cout << endl;
	system("pause");
}
void find_BestAbs(team mas[], int br, string mas1[])
{
	fstream file;
	int goals1, goals2, diff(0);
	string name1, name2, topName;
	file.open("Results.txt", ios::in);
	for (int i = 0; i < linecounter("Results.txt")/4; i++)
	{
		getline(file, name1);
		getline(file, name2);
		file >> goals1;
		file >> goals2;
		file.ignore();
		if (diff < abs(goals1 - goals2))
		{
			diff = abs(goals1 - goals2);
		}
	}
	file.close();
	for (int i = 0; i < linecounter("Results.txt"); i+=4)
	{
		if (abs(stoi(mas1[i+2])-stoi(mas1[i+3])) == diff)
		{
			if (stoi(mas1[i + 2]) > stoi(mas1[i + 3]))
			{
				topName = mas1[i];
			}
			else
			{
				topName = mas1[i+1];
			}
			cout << endl << mas1[i]<<" - "<<mas1[i+1]<<" завършват с най-голяма голова разлика за печелившия отбор "<<topName<<" :" << diff << " гола.";
			cout << endl;			
		}
	}
	system("pause");
}