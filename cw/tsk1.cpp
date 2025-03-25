#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

char* right(char* str,const int n){
    int i = 0, len;
    while (str[i] != '\0'){
        i++;
    }
    len = i;
    if (len < n){
        return str;
    } else {
        return &str[len-n];
    }
    
}

unsigned long right(unsigned long num,const int n){
    int i=0;
    unsigned long ans = 0;
    while (num != 0 && i < n){
        ans += (num%10)*pow(10,i);
        i++;
        num /= 10;
    }
    return ans;
}



int main(){
    char name[10];
    char astr[101];
    unsigned long anum;
    int n;
    cin.getline(name,10);
    if (strcmp(name,"number") == 0){
        cin >> anum;
        cin >> n;
        cout << right(anum,n);

    } else if (strcmp(name,"string") == 0){
        cin.getline(astr, 100);
        cin >> n;
        cout << right(astr,n) << endl;
    } else{
        cin >> astr;
        cin >> n;
        cout << 0 << endl;
    }
}