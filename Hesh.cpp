#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <map>
#include <stdlib.h>
#include <cctype>
#include <set>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

//Director(1) Manager(2) Analyst(3) Engineer(4) Designer(5)

ifstream in("input.txt");
ofstream out("output.txt");

//дата
struct date {
    int dd, mm, yy;
};

//данные о человеке
struct people {
    string Surname; //фамилия
    int post; // должность
    date DateOfBirth; //дата рождения
    int experience; // опыт работы
    int Salary; //зарплата
};

//из строки в дату
date Str_to_Date(string str) {
    date x;
    string temp = str.substr(0, 2);//день
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2);//месяц
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4);//год
    x.yy = atoi(temp.c_str());
    return x;
}

//Director(1) Manager(2) Analyst(3) Engineer(4) Designer(5)

//ввод из файла
vector<people> inFile() {
    //Если надо чтобы были деректоры сверху - надо задать им цифру "5"
    map<string, int> posts = { {"Director", 5}, {"Manager", 4}, {"Analyst", 3}, {"Engineer", 2}, {"Designer", 1} };

    vector<people> x;
    people temp;
    while (in.peek() != EOF) {
        in >> temp.Surname;//фамилия
        string str;
        in >> str;
        temp.post = posts[str]; //должность
        string tmp;//дата рождения
        in >> tmp;
        temp.DateOfBirth = Str_to_Date(tmp);
        in >> temp.experience; // опыт работы
        in >> temp.Salary;//зарплата

        x.push_back(temp);
    }
    return x;
}

//вывод в файл
void print(people x) {
    map<int, string> posts = { {5, "Director"}, {4, "Manager"}, {3, "Analyst"}, {2, "Engineer"}, {1, "Designer",} };

    out << setw(12) << left << x.Surname;//по левому краю, 10 позиций для фамилии
    out << setw(10) << left << posts[x.post];//по левому краю, 10 позиций для должности

    if (x.DateOfBirth.dd < 10) out << left << '0' << x.DateOfBirth.dd << '.';//добавляем 0
    else out << left << x.DateOfBirth.dd << '.';

    if (x.DateOfBirth.mm < 10) out << '0' << x.DateOfBirth.mm << '.';
    else out << x.DateOfBirth.mm << '.';

    out << left << setw(6) << x.DateOfBirth.yy;//на год 6 позиций

    out << setw(10) << left << x.experience;//по левому краю, 10 позиций для опыта работы

    out << left << setw(10) << x.Salary << endl;//запрлата
}
//------------------------------------------------------------------------------------------------
struct dvus {
    int inf;
    dvus* next;
    dvus* prev;
};

void push(dvus*& h, dvus*& t, int x) { //вставка элемента в конец списка
    dvus* r = new dvus; //создаем новый элемент
    r->inf = x;
    r->next = NULL; //всегда последний
    if (!h && !t) { //если список пуст
        r->prev = NULL; //первый элемент
        h = r; //это голова
    }
    else {
        t->next = r; //r - следующий для хвоста
        r->prev = t; //хвост - предыдущий для r
    }
    t = r; //r теперь хвост
}

void print(dvus* h, dvus* t) { //печать элементов списка
    dvus* p = h; //укзатель на голову
    while (p) { //пока не дошли до конца списка
        cout << p->inf << " ";
        p = p->next; //переход к следующему элементу
    }
}

dvus* find(dvus* h, dvus* t, int x) { //печать элементов списка
    dvus* p = h; //укзатель на голову
    while (p) { //пока не дошли до конца списка
        if (p->inf == x) break; // если нашли, прекращаем цикл
        p = p->next; //переход к следующему элементу
    }
    return p; //возвращаем указатель
}

void insert_after(dvus*& h, dvus*& t, dvus* r, int y) { //вставляем после r
    dvus* p = new dvus; //создаем новый элемент
    p->inf = y;
    if (r == t) { //если вставляем после хвоста
        p->next = NULL; //вставляемый эл-т - последний
        p->prev = r; //вставляем после r
        r->next = p;
        t = p; //теперь хвост - p
    }
    else { //вставляем в середину списка
        r->next->prev = p; //для следующего за r эл-та предыдущий - p
        p->next = r->next; //следующий за p - следующий за r
        p->prev = r; //p вставляем после r
        r->next = p;
    }
}

void del_node(dvus*& h, dvus*& t, dvus* r) { //удаляем r
    if (r == h && r == t) //единственный элемент списка
        h = t = NULL;
    else if (r == h) { //удаляем голову списка
        h = h->next; //сдвигаем голову
        h->prev = NULL;
    }
    else if (r == t) { //удаляем хвост списка
        t = t->prev; //сдвигаем хвост
        t->next = NULL;
    }
    else {
        r->next->prev = r->prev; //для следующего от r предыдущим становится r->prev;
        r->prev->next = r->next; //для предыдущего от r следующим становится r->next;
    }
    //delete r; //удаляем r
}

void del_dvus(dvus*& h, dvus*& t) { //удаляем список
    while (h) { //пока список не пуст
        dvus* p = h; //указатель на голову
        h = h->next; //переносим голову
        h->prev = NULL; //обнуляем
        delete p; //удаляем p
    }
}

int hesh(int x) {
    return x % 7;
}


int main() {
    setlocale(0, "ru");

    int m = 7;
    int n = 20;

    vector<vector<int>> task1(m);
    vector<people> dannie;
    dannie = inFile();

    int k;
    for (int i = 0; i < dannie.size(); ++i) {
        k = hesh(dannie[i].Salary);
        task1[k].push_back(dannie[i].Salary);
    }

    for (int i = 0; i < task1.size(); ++i, cout << endl) {
        cout << i << ": ";
        for (int j = 0; j < task1[i].size(); ++j)
            cout << task1[i][j] << ", ";
    }

    int x;
    cout << "Какой элемент надо найти: ";
    cin >> x;

    int HeshOfX = hesh(x);
    for (int i = 0; i < task1[HeshOfX].size(); ++i) {
        if (task1[HeshOfX][i] == x) {
            cout << "Мы нашли х";
            task1[HeshOfX].erase(task1[HeshOfX].begin() + i);
        }
    }

    cout << endl;
    for (int i = 0; i < task1.size(); ++i, cout << endl) {
        cout << i << ": ";
        for (int j = 0; j < task1[i].size(); ++j)
            cout << task1[i][j] << ", ";
    }

    return 0;
}
