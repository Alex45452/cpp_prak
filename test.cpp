#include <iostream>
#include <cmath>

using namespace std;

int main(){
    char buf[11] = "qwerqwerre";
    cin.getline(buf,11);

    cout << buf << endl;
    cin.getline(buf,10);
    cout << buf << endl;
}