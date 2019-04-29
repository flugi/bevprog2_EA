#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

// BevProg2 9. Előadás
// STL konténerek, iterátorok


void f() {
    cout << "f" << endl;
}

template <typename T>
void csinal(T t) {
    t();
}

void templatepelda() {
    csinal(f);
    csinal([](){cout <<"lambda" << endl;});
}

void primtomb() {
    int * primt = new int[10];
    for (int i=0;i<10;i++)
        primt[i]=i+1;
    // mutatók
    for (int * a = primt; a != primt+10; a++) {
        cout << *a << " ";
    }
    cout << endl;
}

void vektoros() {
    vector<int> v(10,42);
    int * v1 = &(v[0]);
    for (int * a = v1; a != v1+10; a++) {
        cout << *a << " ";
    }
    cout << endl;
    for (vector<int>::iterator it = v.begin(); it!= v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

}

void listas() {
    list<int> l;
    for (int i=0;i<10;i++) {
        l.push_back(i+1);
    }
    for (list<int>::iterator it = l.begin(); it!= l.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    for (int a : l) {
        cout << a << " ";
    }
    cout << endl;
}


void halmaz() {
    set<int> s;
    s.insert(5);
    s.insert(1);
    s.insert(15);
    set<int>::iterator hol = s.find(15);
    if (hol == s.end()) {
        cout << "nincs" << endl;
    } else {
        cout << "van" << endl;

    }
    for (int a : s) {
        cout << a << " ";
    }
    cout << endl;
    map<string, int> m;
    m["januar"]=31;
    m["februar"]=28;
//    cout << m["januarx"] << endl;
    map<string, int>::iterator holm = m.find("januar");
    if (holm == m.end()) {
        cout << "nincs" << endl;
    } else {
        cout << "van: " << holm->second << endl;
    }
    for (pair<string, int> p : m) {
        cout << p.first << "->" << p.second << endl;
    }
}


// STL+funktorok

void kiir(int a) {
    cout << a << "_";
}

struct funktor {
    char sep = ':';
    funktor(char s) : sep(s) {}
    void operator()(int a) {
        cout << a << sep;
    }
};

void algo() {
    vector<int> v;
    for (int i=0;i<10;i++) {
        v.push_back(rand()%200);
    }
    for (int a : v) {
        cout << a << " ";
    }
    cout << endl;
    sort(v.begin(), v.end());
    for (int a : v) {
        cout << a << " ";
    }
    cout << endl;
    for_each(v.begin(), v.end(), kiir);
    cout << endl;
    for_each(v.begin(), v.end(), funktor('.'));
    cout << endl;
    char separator = '-';
    for_each(v.begin(), v.end(), [separator](int a){ cout << a << separator;} );


    cout << endl << endl;
    sort(v.begin(), v.end(), [](int a, int b)->bool{ return a>b; });
    for (int a : v) {
        cout << a << " ";
    }
    cout << endl << endl;

}

int main()
{
//    templatepelda();

//    primtomb();
//    vektoros();
 //   listas();
 //   halmaz();

    algo();

    return 0;
}
