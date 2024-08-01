#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <Vector>
#include <Algorithm>
#include <fstream>
#include "dijkstra.h"
using namespace std;



void gotoxy(int x, int y) {
	COORD pos;   pos.X = x; pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}


class User {
public:
	string Name;
	string password;
};
int total = 0;
void Merge(vector<User*>& v, int l, int h, int mid) {
	int i, j, k;
	vector<User*> temp(h - l + 1);
	i = l;
	k = 0;
	j = mid + 1;

	while (i <= mid && j <= h) {
		if (v[i]->Name < v[j]->Name) {
			temp[k] = v[i];
			k++;
			i++;
		}
		else {
			temp[k] = v[j];
			k++;
			j++;
		}
	}

	while (i <= mid) {
		temp[k] = v[i];
		k++;
		i++;
	}

	while (j <= h) {
		temp[k] = v[j];
		k++;
		j++;
	}

	for (i = l; i <= h; i++) {
		v[i] = temp[i - l];
	}
}

void MergeSort(vector<User*>& a, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);
		Merge(a, low, high, mid);
	}
}

void insertinfile(User* u) {
	fstream file;
	vector<User*> users;
	file.open("Test1.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		return;
	}

	User* temp = new User;
	bool exists = false;
	file.clear();
	file.seekg(0, ios::beg); // Move file pointer to the beginning
	while (file >> temp->Name >> temp->password) {
		if (temp->Name == u->Name) {
			exists = true;
			break;
		}
		users.push_back(new User(*temp)); // Push a copy of the read user
	}
	if (!exists) {
		users.push_back(u);
		MergeSort(users, 0, users.size() - 1);

		file.close();
		file.open("Test1.txt", ios::out | ios::trunc);

		for (const auto& user : users) {
			file << user->Name << " " << user->password << "\n";
		}
	}

	file.close();
}

void readfromfile() {
	string line;
	ifstream file;
	file.open("Test1.txt", ios::in);
	if (!file.is_open()) {
		cout << "Error opening the file for reading!" << endl;
		return;
	}

	while (file >> line) {
		cout << line << " ";
		file >> line;
		cout << line << " ";
		cout << endl;
	}

	file.close();
}

bool searchinfile(string n,string n2,int* passsame) {
	ifstream file;
	file.open("Test1.txt", ios::in);
	if (!file.is_open()) {
        gotoxy(16,18);
		cout << "Error opening the file for reading!" << endl;
		return false;
	}

	bool found = false;
	while (!file.eof()) {
		string name, password;
		file >> name >> password;
		if (name == n && password == n2) {
			found = true;
			break;
		}
		else if (name == n && password != n2) {
			found = true;
			*passsame = 1;
		}
	}
	file.close();

	if (found)
		return true;
	else {
		return false;
	}
}

void intro() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
	cout << endl;
	for (int c = 0; c < 25; c++)cout << "*                                                                                                                   *\n";
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
	gotoxy(35, 10);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	cout << "0 0 0  0 0 0  0 0      0 0    0   0   0 0 0";
	gotoxy(35, 11);
	cout << "0   0  0      0   0    0   0  0   0  0     0";
	gotoxy(35, 12);
	cout << "0 0 0  0 0 0  0   0    0 0    0   0     0";
	gotoxy(35, 13);
	cout << "0 0    0      0   0    0   0  0   0  0     0";
	gotoxy(35, 14);
	cout << "0   0  0 0 0  0 0      0 0    0 0 0   0 0 0";
	gotoxy(35, 15);
	cout << "============================================";
	gotoxy(47, 16);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "SERVICE APPLICATION";
	gotoxy(0, 21);

}
void progcus();
void login();
void logout()
{
	system("cls");
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
	cout << endl;
	for (int c = 0; c < 25; c++)cout << "*                                                                                                                   *\n";
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
	gotoxy(37, 13);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	cout << "THANK YOU FOR USING RED BUS SERVICE APPLICATION";
	gotoxy(50, 14);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "SEE YOU NEXT TIME!";
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	gotoxy(1, 26);
}
void Admin()
{
	system("cls");
	cout << endl << "\t\t\t\t\tADMIN DASHBOARD";
	int tries = 0;
_false:
	cout << endl << endl << "\t\tPlease enter the Admin username and password: ";
	cout << endl << endl << "\t\t Username: ";
	cout << endl << "\t\t--------------------------------";
	cout << endl << "\t\t|                              |";
	cout << endl << "\t\t--------------------------------";
	string n, p;

	cout << endl << endl << "\t\t Password: ";
	cout << endl << "\t\t--------------------------------";
	cout << endl << "\t\t|                              |";
	cout << endl << "\t\t--------------------------------";
	gotoxy(17, 7);
	cin >> n;
	gotoxy(17, 12);
	cin >> p;
	tries++;
	if (n != "ADMIN" && tries < 3 && p != "fastt123")
	{
		system("cls");
		cout << endl << "\t\t INCORRECT PASSWORD! ENTER AGAIN.";
		goto _false;
	}

	else if (p != "fastt123" && tries < 3)
	{
		system("cls");
		cout << endl << "\t\t INCORRECT PASSWORD! ENTER AGAIN.";
		goto _false;
	}
	else if (n != "ADMIN" && tries < 3)
	{
		system("cls");
		cout << endl << "\t\t INCORRECT USERNAME! ENTER AGAIN.";
		goto _false;
	}
	else if (tries >= 3)
	{
		system("cls");
		cout << endl << "\t\tSUSPICIOUS ACTIVITY DETECTED. REDIRECTING IN... ";
		int counter = 3;
		while (counter > 0)
		{
			cout << counter << " ...";
			counter--;
			this_thread::sleep_for(chrono::seconds(1));
		}
		system("cls");
		login();
	}
	else
	{
		system("cls");
		cout << endl << "\t\t\t\t\tWELCOME, ADMIN !";
		cout << endl << "\t\t***TOTAL CUSTOMERS***";
		cout << endl;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		readfromfile();
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		int ticket = 100;
		cout << endl << "TICKET PER PERSON: " << ticket;
		cout << endl << "TOTAL TICKETS SOLD: " << total;
		cout << endl << "TOTAL REVENUE GENERATED: " << total * ticket;
		char c;
		cout << endl << endl << "Press any key to continue and 'e' to exit: ";
		cin >> c;
		if (c == 'e') {
			logout();
		}
		else
		{
			system("cls");
			login();
		}
	}
}


int customerlogin();


void Customer()
{
	system("cls");
	User* u = new User;
	int n = customerlogin();
	if (n == 1) {
		line297:
		system("cls");
		cout << endl << "\t\t\t\t\tWELCOME, ESTEEMED CUSTOMER!";

		cout << endl << endl << "\t\tPlease enter credentials: ";
		cout << endl << endl << "\t\t Username: ";
		cout << endl << "\t\t--------------------------------";
		cout << endl << "\t\t|                              |";
		cout << endl << "\t\t--------------------------------";

		cout << endl << endl << "\t\t Password: ";
		cout << endl << "\t\t--------------------------------";
		cout << endl << "\t\t|                              |";
		cout << endl << "\t\t--------------------------------";
		gotoxy(17, 7);
		cin >> u->Name;
		gotoxy(17, 12);
		cin >> u->password;
		int passsame = 0; //0 when matched with registered accounts else 1
		bool check = searchinfile(u->Name, u->password, &passsame);
		if (check) {
			cout << endl << endl << "\t\tThis username has already been taken, try different username";
			this_thread::sleep_for(chrono::seconds(3));
			goto line297;

		}
		else if (check && passsame == 1) {
			cout << endl << endl << "\t\tThis username has already been taken, try different username";
			this_thread::sleep_for(chrono::seconds(3));
			goto line297;
		}
		else if(!check){
			insertinfile(u);
		}

	}
	else if (n == 0) {
		line330:
		system("cls");
		cout << endl << "\t\t\t\t\tWELCOME, ESTEEMED CUSTOMER!";

		cout << endl << endl << "\t\tPlease enter your credentials: ";
		cout << endl << endl << "\t\t Username: ";
		cout << endl << "\t\t--------------------------------";
		cout << endl << "\t\t|                              |";
		cout << endl << "\t\t--------------------------------";

		cout << endl << endl << "\t\t Password: ";
		cout << endl << "\t\t--------------------------------";
		cout << endl << "\t\t|                              |";
		cout << endl << "\t\t--------------------------------";
		gotoxy(17, 7);
		cin >> u->Name;
		gotoxy(17, 12);
		cin >> u->password;
		int passsame = 0; //0 when matched with registered accounts else 1  
		bool check = searchinfile(u->Name, u->password, &passsame);
		if (!check) {
			cout << endl << endl << "\t\tINVALID CREDENTIALS";
			this_thread::sleep_for(chrono::seconds(3));
			goto line330;
		}else if (check && passsame == 1) {
			cout << endl << endl << "\t\tINVALID CREDENTIALS";
			this_thread::sleep_for(chrono::seconds(3));
			goto line330;
		}
	}
	system("cls");
	cout << endl << "\t\t\t\t\tWELCOME, " << u->Name << " !";
	this_thread::sleep_for(chrono::seconds(3));
	system("cls");
	total++;
	progcus();
}

int customerlogin() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	cout << endl << "\t\t\t\t\t\t\tLOG IN OR SIGN UP ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
jump_to_line_341:
	int n;
	cout << endl << endl << "\t\t                                                                                         -------";
	cout << endl << "\t\tIf you are a new customer enter 1 else 0 if you have already an account or -1 for exit: |       |";
	cout << endl << "\t\t                                                                                         -------";
	gotoxy(105, 4);
	cin >> n;
	if (n == 1)
	{
		return 1;
	}
	else if (n == 0)
	{
		return 0;
	}
	else if (n == -1)
	{
		logout();
	}
	else {
		cout << endl << "\t\tError! Choose correct option: ";
		goto jump_to_line_341;
	}
}

void login() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << endl << "\t\t\t\t\tWELCOME TO RED BUS SERVICE APPLICATION!";
jump_to_line_191:
	cout << endl << endl << "\t\t                                                -------";
	cout << endl << "\t\t1 for Admin and 0 for Customer or -1 for exit: |       |";
	cout << endl << "\t\t                                                -------";
	int n;
	gotoxy(65, 4);
	cin >> n;
	if (n == 1)
	{
		Admin();
	}
	else if (n == 0)
	{
		Customer();
	}
	else if (n == -1)
	{
		logout();
	}
	else {
		cout << endl << "\t\tError! Choose correct option: ";
		goto jump_to_line_191;
	}
}


void progcus(){
	path path;
	graph a;
	a.readfromfile();
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
	cout << endl;
	for (int c = 0; c < 25; c++)cout << "*                                                                                                                   *\n";
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
	
	gotoxy(2,2);
	
	cout<<" 0. Power house";
    cout<<" 1. Liquatabad";
	cout<<" 2. Numaish   ";
	cout<<" 3. Tower";
	cout<<" 4. Docklands";
	cout<<" 5. Mirannakka lyrics";
	gotoxy(2,3);
	cout<<" 6. Shireen jinnah colony";
	
	cout<<" 7. Millenium";
	cout<<" 8. Ftc";
	cout<<" 9. Defence morr";
	cout<<" 10. Dolmen mall";
	gotoxy(2,4);
	cout<<" 11.	Indus hospital";
	cout<<" 12. Shaan chowrangi";
	
	cout<<" 13. Ibrahim hyderi";
	cout<<" 14. Bhatia town";
	cout<<" 15. Malir cantt";
	gotoxy(2,5);
	cout<<" 16. Malir";
	cout<<" 17. Model colony ";
	cout<<" 18. Malir halt";
	
	cout<<" 19. Naddi kinara";
	cout<<" 20. Quaidabad";
	gotoxy(2,6);
	cout<<" 21. Gulshen e hadeed";
	
	
	
	gotoxy(2, 11);
	cout<<"please enter your starting and ending stop. ";
	int aa,bb;
	gotoxy(2, 13);
	cout<<"start : "; cin>>aa;
	gotoxy(2, 14);
	cout<<"end   : "; cin>>bb;
	path=a.shortestpath(aa,bb);
	
	gotoxy(2, 15);
	cout<<"distance = "<<path.distance;
	gotoxy(2, 16);
	cout<<"route    = ";
	while(!path.busstops.empty()){
		cout<<path.busstops.top()<<"->";
		path.busstops.pop();
		
	}
	cout<<"end";
	
	
	gotoxy(2, 20);
	cout<<"press y to continue press n to exit. ";
	gotoxy(2, 21);
	string ans; 
	cin>>ans;
	
	while(ans=="y")
	{
	total++;
	gotoxy(10, 13);
	cout<<"     ";	
	gotoxy(10, 14);
	cout<<"     ";	
	gotoxy(2, 21);
	cout<<"         ";
	gotoxy(13, 15);
	cout<<"         ";
	gotoxy(13, 16);
	cout<<"                                                                                          ";
	
	gotoxy(10, 13);
	cin>>aa;
	gotoxy(10, 14);
	cin>>bb;
	
	path=a.shortestpath(aa,bb);
	
	gotoxy(2, 15);
	cout<<"distance = "<<path.distance;
	
	gotoxy(2, 16);
	cout<<"route    = ";
	
	while(!path.busstops.empty()){
		cout<<path.busstops.top()<<"->";
		path.busstops.pop();
		
	}
	cout<<"end";
	
	gotoxy(2, 21);
	cin>>ans;
		
	}
	system("cls");
	login();
	
	
	
	
}



int main() {
	intro();
	this_thread::sleep_for(chrono::seconds(5));
	system("cls");
	login();


}
