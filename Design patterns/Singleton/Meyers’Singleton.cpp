#include<iostream>
using namespace std;

class Singleton {
    Singleton() { 
        cout << "Singleton Constructor Called!" << endl; 
    }
public:
    static Singleton& getInstance() {
        static Singleton instance; 
        return instance;
    }
};


int main() {
    Singleton s1 = Singleton::getInstance();
    Singleton s2 = Singleton::getInstance();
}
