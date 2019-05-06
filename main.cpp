#include <iostream>
#include <thread>
#include <sstream>
#include <cmath>
#include <mutex>
#include <set>
using namespace std;




void basic_thread() {
    std::thread th([](){
        int sum=0;
        for (int i=0;i<100;i++) {
            sum+=i;
        }
        stringstream ss;
        ss <<"Thread result="<< sum << endl;
        cout << ss.str();
    });
    for (int i=0;i<20;i++) {
        cout << i << endl;
    }
    th.join();
}


void basic_omp() {
#pragma omp parallel for
    for (int i=0;i<10;i++) {
        double sum=0;
        for (int j=0;j<100000000;j++) {
            sum += sqrt((i+1)*sqrt(j));
        }
        stringstream ss;
        ss <<i<<":"<< sum << endl;
        cout << ss.str();
    }
}



void race_condition() {
    int sum = 0;
#pragma omp parallel for
    for (int i=0;i<10000;i++) {
        sum++;
    }
    cout << sum << endl;
}

void mutexes() {
    std::mutex m;
#pragma omp parallel for
    for (int i=0;i<10;i++) {
        double sum=0;
        for (int j=0;j<100;j++) {
            sum += sqrt((i+1)*sqrt(j));
        }
        m.lock();
        cout <<i<<":"<< sum << endl;
        m.unlock();
    }
    
}

void mutexes2() {
    std::mutex m;
#pragma omp parallel for
    for (int i=0;i<10;i++) {
        double sum=0;
        for (int j=0;j<100;j++) {
            sum += sqrt((i+1)*sqrt(j));
        }
        lock_guard<mutex> guard(m);
        cout <<i<<":"<< sum << endl;
    }
    
}


template <typename T>
struct safe_set {
    set<T> s;
    std::mutex mx;
    void insert(T data) {
        mx.lock();
        s.insert(data);
        mx.unlock();
    }
    int size() const {return s.size();}
};

void thread_safe_type_example() {
    set<int> st;
    safe_set<int> sft;
#pragma omp parallel for
    for (int i=0;i<100;i++) {
        sft.insert(i);
    }
    cout << sft.size() << endl;
#pragma omp parallel for
    for (int i=0;i<100;i++) {
        st.insert(i); 
    }
    cout << st.size() << endl;
}

int main()
{
    cout <<"thread count:"<< thread::hardware_concurrency() << endl;
//    basic_thread();
//    basic_omp();
//    race_condition();
//    mutexes();
//    mutexes2();
    thread_safe_type_example();
    return 0;
}
