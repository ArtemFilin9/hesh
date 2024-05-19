#include <iostream>
#include <vector>
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

struct list {
    int inf;
    list* next;
    list* prev;
};

void push(list*& h, list*& t, int x) { //вставка элемента в конец списка
    list* r = new list; //создаем новый элемент
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

void print(list* h, list* t) { //печать элементов списка
    list* p = h; //укзатель на голову
    while (p) { //пока не дошли до конца списка
        cout << p->inf << " ";
        p = p->next; //переход к следующему элементу
    }
}

list* find(list* h, list* t, int x) { //печать элементов списка
    list* p = h; //укзатель на голову
    while (p) { //пока не дошли до конца списка
        if (p->inf == x) break; // если нашли, прекращаем цикл
        p = p->next; //переход к следующему элементу
    }
    return p; //возвращаем указатель
}

void insert_after(list*& h, list*& t, list* r, int y) { //вставляем после r
    list* p = new list; //создаем новый элемент
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

void del_node(list*& h, list*& t, list* r) { //удаляем r
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

void del_list(list*& h, list*& t) { //удаляем список
    while (h) { //пока список не пуст
        list* p = h; //указатель на голову
        h = h->next; //переносим голову
        h->prev = NULL; //обнуляем
        delete p; //удаляем p
    }
}


int main()
{



    std::cout << "Hello World!\n";
}
