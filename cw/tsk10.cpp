#include <iostream>
#include <cstring>

using namespace std;

class Flower
{
    int petal;
    int color; // 0 - белый 1 - розовый
    // static int total_petals;
    static int pink_cnt;
    static int white_cnt;
public:
    Flower(const char* color, const int petal_num);
    Flower();
    ~Flower();
    static void Print_flowers();
};
// int Flower::total_petals = 0;
int Flower::pink_cnt = 0;
int Flower::white_cnt = 0;

Flower::Flower()
{
    petal = 10;
    if (pink_cnt < white_cnt)
    {
        color = 1;
        pink_cnt += 1;
    } 
    else if (pink_cnt == white_cnt)
    {
        // if (total_petals % 2)
        if (petal % 2)
        {
            color = 0;
            white_cnt += 1;   
        }
        else
        {
            color = 1;
            pink_cnt += 1;
        }
    }
    else 
    {
        color = 0;
        white_cnt += 1;   
    } 
    // total_petals += 10;
    
}

Flower::Flower(const char* clr , const int petal_num = 10)
{
    petal = petal_num;
    if (strcmp(clr,"white") == 0)
    {
        color = 0;
        white_cnt += 1;
    }
    else if (strcmp(clr,"pink") == 0)
    {
        color = 1;
        pink_cnt += 1;
    } else {
        if (pink_cnt < white_cnt)
        {
            color = 1;
            pink_cnt += 1;
        } 
        else if (pink_cnt == white_cnt)
        {
            // if (total_petals % 2)
            if (petal % 2)
            {
                color = 0;
                white_cnt += 1;   
            }
            else
            {
                color = 1;
                pink_cnt += 1;
            }
        }
        else 
        {
            color = 0;
            white_cnt += 1;   
        } 
    }
    // total_petals += petal_num;
}


Flower::~Flower()
{
    if (color == 1){
        pink_cnt -= 1;
    } else {
        white_cnt -=1;
    }
    // total_petals -= petal;
}

void Flower::Print_flowers()
{
    cout << "White: " << white_cnt << " Pink: " << pink_cnt <<  endl;
}
