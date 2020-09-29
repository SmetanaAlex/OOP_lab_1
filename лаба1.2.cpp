
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;
int MM();
int menu();

struct book {
	unsigned id;
	char name[100];
	int pages;
	char publisher[100];
};

struct node {
	book value;
	node* next;
};

class list {
public:
	node* head;
	list() { head = nullptr; };
	list(const char* filename);
	~list();
	void show();
	void add();
	node* find_id(int id);
	node* find_name(char* name);
	void red(node* p);
	void sort_id();
	void delate(node* p);
	void save(const char* fm);
	friend ostream& operator<<(ostream& o, list& l);
};

void parse(char* s, book& b) {
	char t[250];
	int i = 0, j = 0;
	while (i < strlen(s)) {
		if (s[i] == 9) {
			// t->b.id
			t[j] = '\0';
			b.id = atoi(t);
			j = 0;
			t[0] = '\0';
			i++;
			break;
		}
		else
			t[j] = s[i];
		i++; j++;
	}

	while (i < strlen(s)) {
		if (s[i] == 9) {
			// t->b.name
			t[j] = '\0';
			strcpy_s(b.name, 100, t);
			j = 0;
			t[0] = '\0';
			i++;
			break;
		}
		else
			t[j] = s[i];
		i++; j++;
	}





	while (i < strlen(s)) {
		if (s[i] == 9) {
			// t->b.pages
			t[j] = '\0';
			b.pages = atoi(t);
			j = 0;
			t[0] = '\0';
			i++;
			break;
		}
		else
			t[j] = s[i];
		i++; j++;
	}


	while (i < strlen(s)) {

		if (s[i] == 9) {

			// t->b.publisher

			t[j] = '\0';

			strcpy_s(b.publisher, 100, t);

			j = 0;

			t[0] = '\0';

			i++;

			break;
		}
		else
			t[j] = s[i];
		i++; j++;
	}
	t[j] = '\0';
	strcpy_s(b.publisher, 100, t);
	j = 0;
	t[0] = '\0';
	i++;


}

list::list(const char* filename)
{
	char s[250];
	node* p;
	p = head;
	ifstream f(filename);
	while (!f.eof()) {
		f.getline(s, 250);
		if (strcmp(s, "") == 0) continue;
		//cout << s << endl;
		if (head == nullptr) {
			head = new node;
			p = head;
			parse(s, p->value);
			p->next = nullptr;
		}
		else {
			p->next = new node;
			p = p->next;
			parse(s, p->value);
			p->next = nullptr;
		}
	}
	f.close();
}

list::~list()
{
	node* p = head;
	while (p != nullptr) {
		p = p->next;
		delete head;
		head = p;
	}
}

void list::show()
{
	node* p = head;
	while (p != nullptr) {
		cout << p->value.id << '\t' << p->value.name << '\t' << p->value.pages << '\t' << p->value.publisher << endl;
		p = p->next;
	}
}
void list::add()
{
	book b;
	cout << "Enter name" << endl;
	cin >> b.name ;
	cout << "Enter pages" << endl;
	cin >>  b.pages ;
	cout << "Enter publisher" << endl;
	cin >> b.publisher;
	node* p = head;
	if (p != nullptr) {
		while (p->next != nullptr) {
			p = p->next;

		}
		b.id = p->value.id + 1;
		p->next = new node;
		p = p->next;
		p->value.id = b.id;
		p->value.pages = b.pages;
		strcpy_s(p->value.name, 100, b.name);
		strcpy_s(p->value.publisher, 100, b.publisher);
		p->next = nullptr;
	}
	else {
		b.id = 1;
		p = new node;
		p->value.id = b.id;
		p->value.pages = b.pages;
		strcpy_s(p->value.name, 100, b.name);
		strcpy_s(p->value.publisher, 100, b.publisher);
		head = p;
		head->next = nullptr;
	}
	
}


void list::save(const char* fm) {

	ofstream f(fm, ios_base::trunc | ios_base::out);
	node* p = head;
	while (p != nullptr) {
		f << p->value.id << '\t' << p->value.name << '\t' << p->value.pages << '\t' << p->value.publisher << endl;
		p = p->next;
	}

	f.close();
}

ostream& operator<<(ostream& o, list& l)
{
	
	return o;
}

node* list::find_id(int id) {
	node* p = head;
	while (p != nullptr) {
		if (id == p->value.id) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

node* list::find_name(char* name) {
	node* p = head;
	while (p != nullptr) {
		if (strcmp(name, p->value.name) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void list::red(node* p) {
    book b;
	cout << "***********************" << endl;
	cout << "use name ==   1" << endl;
	cout << "use pages ==   2" << endl;
	cout << "use publisher ==   3" << endl;
	cout << "***********************" << endl;
	int k;
	cin >> k;
	switch(k){
	case 1: {
		cout << "Enter new name" << endl;
		cin >> b.name;
		strcpy_s(p->value.name, 100, b.name);
		break;
	}
	case 2: {
		cout << "Enter new pages" << endl;
		cin >> b.pages;
		p->value.pages = b.pages;
		break;
	}
	case 3: {
		cout << "Enter new publisher" << endl;
		cin >> b.publisher;
		strcpy_s(p->value.publisher, 100, b.publisher);
		break;
	}
	}
	MM();
}
void list::delate(node* p) {
	list l("books.bin");
	node* q = head;
	if (q == p) {
		if (head != NULL) {
			head = head->next;
			delete p;
		}
		else {}/// empty file
	}
	else {
		while (q->next != nullptr) {
			if (q->next == p) {
				break;
			}
			q = q->next;
		}
		q->next = p->next;
		delete p;
	}
	
}

int main()
{
	MM();
}
int MM() {

	list l("books.bin");
	cout << "***********************" << endl;
	setlocale(LC_ALL, "Russian");
	int answer = menu();
	switch (answer)
	{
	case 0: {l.add();
		l.save("books.bin");
		l.~list();
		MM(); 
		break;
	}
	case 1: {	cout << "Enter name " << endl;
		char n[20];
		cin >> n;
		l.delate(l.find_name(n));
		l.save("books.bin");
		l.~list();
		MM();
		break;
	}
	case 2: {	cout << "Enter name " << endl;
		char n[20];
		cin >> n;
		l.red(l.find_name(n));
		l.save("books.bin");
		l.~list();
		MM();
		break;
	}
	case 3: {	
		l.save("books.bin");
		l.~list();
		return 0;
	  }
	
	}
	system("pause");
	return 0;
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		list l("books.bin");
		l.show();
		cout << "***********************" << endl;
		key = (key + 4) % 4;
		if (key == 0) cout << "->add" << endl;
		else  cout << "  add" << endl;
		if (key == 1) cout << "->delate" << endl;
		else  cout <<"  delate" << endl;
		if (key == 2) cout << "->Red" << endl;
		else  cout << "  Red" << endl;
		if (key == 3) cout << "->Exit" << endl;
		else  cout << "  Exit" << endl;
		
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

