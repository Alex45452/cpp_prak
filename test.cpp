#include <iostream>
#include <cmath>

using namespace std;

char* right(char* str,int n){
    int i, len, k;
    while (str[i] != '\0'){
        i++;
    }
    len = i;
    if (len < n){
        k = len;
    } else {
        k = n;
    }
    return &str[len-k];
}

unsigned long right(unsigned long num,int n){
    int i=0;
    unsigned long ans = 0;
    while (num != 0 && i < n){
        ans += (num%10)*std::pow(10,i);
        i++;
        num /= 10;
    }
    return ans;
}


int main(){
    unsigned long num;
    int n;
    cin >> num;
    cout << num << endl;
    cin >> n;
    cout << right(num,n) << endl;
}