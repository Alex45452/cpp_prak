#include <iostream>
#include <cmath>

using namespace std;

char* right(char* str,int n){
    int i, len, k;
    char ans[100];
    while (str[i] != '\0'){
        i++;
    }
    len = i;
    k = 1;
    ans[n] = '\0';
    for (i = len-1;i>len-1-n;i--){
        ans[n-k] = str[i];
        k++;
    }
    return ans;
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
    string name[10];
    char astr[101];
    unsigned long anum;
    int n;
    cin >> name;
    printf("%s",name);
    printf("%d","number\n"==name);
    if (name == "number\n"){
        scanf("%lu\n%i",&anum,&n);
        printf("%lu %i",anum,n);
        printf("%lu",right(anum,n));

    } else {
        fgets(astr,sizeof(astr),stdin);
        scanf("%d",&n);
        printf("%s",right(astr,n));
    };
}