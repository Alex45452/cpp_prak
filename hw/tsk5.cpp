#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

struct MoveSheet{
    char name;
    int x1,y1;
    int x2,y2;
};

class Figure{
public:
    virtual bool move(int x1,int y1,int x2,int y2) const = 0;
};

class Knight: public Figure{
public:
    virtual bool move(int x1,int y1,int x2,int y2) const;
};

class King: public Figure{
public:
    virtual bool move(int x1,int y1,int x2,int y2) const;
};

class Queen: public Figure{
public:
    virtual bool move(int x1,int y1,int x2,int y2) const;
};

class Bishop: public Figure{
public:
    virtual bool move(int x1,int y1,int x2,int y2) const;
};

class Rook: public Figure{
public:
    virtual bool move(int x1,int y1,int x2,int y2) const;
};

bool King::move(int x1,int y1,int x2,int y2) const{
    if (x2 <= 8 && x2 >= 1 && y2 <= 8 && y2 >= 1){
        if (x1 <= 8 && x1 >= 1 && y1 >= 1 && y1 <= 8){
            return (abs(x1-x2) <= 1 && abs(y1-y2) <=1 && (y1 != y2 || x1 != x2));
        }
    }
    return false;
}
bool Knight::move(int x1,int y1,int x2,int y2) const{
    if (x2 <= 8 && x2 >= 1 && y2 <= 8 && y2 >= 1){
        if (x1 <= 8 && x1 >= 1 && y1 >= 1 && y1 <= 8){
            return (abs(x1-x2) == 2 && abs(y1-y2) == 1)||(abs(x1-x2) == 1 && abs(y1-y2) == 2);
        }
    }
    return false;
}
bool Queen::move(int x1,int y1,int x2,int y2) const{
    if (x2 <= 8 && x2 >= 1 && y2 <= 8 && y2 >= 1){
        if (x1 <= 8 && x1 >= 1 && y1 >= 1 && y1 <= 8){
            return ((x1==x2 || y1==y2)||(abs(x1-x2) == abs(y1-y2)))&&(x1 != x2 || y1 != y2);
        }
    }
    return false;
}
bool Bishop::move(int x1,int y1,int x2,int y2) const{
    // printf("%d %d %d %d",x1,y1,x2,y2);
    if (x2 <= 8 && x2 >= 1 && y2 <= 8 && y2 >= 1){
        if (x1 <= 8 && x1 >= 1 && y1 >= 1 && y1 <= 8){
            return (abs(x1-x2) == abs(y1-y2))&& (x1 != x2 || y1 != y2);
        }
    }
    return false;
}
bool Rook::move(int x1,int y1,int x2,int y2) const{
    if (x2 <= 8 && x2 >= 1 && y2 <= 8 && y2 >= 1){
        if (x1 <= 8 && x1 >= 1 && y1 >= 1 && y1 <= 8){
            return (x1==x2 || y1==y2)&&(x1 != x2 || y1 != y2);
        }
    }
    return false;
}



class Parser{
public:
    MoveSheet parse(const string str){
        MoveSheet res;
        res.name = str[0];
        res.x1 = (int)(str[2]-'a'+1);
        res.y1 = (int)(str[3]-'1'+1);
        res.x2 = (int)(str[5]-'a'+1);
        res.y2 = (int)(str[6]-'1'+1);
        return res;
    }
};

class ChessChecker{
    Figure* pieces;
public:
    bool check_move(const string line);
};

bool ChessChecker::check_move(const string line){
    Parser parser;
    MoveSheet move;
    move = parser.parse(line);
    if (move.name == 'Q'){
        Queen q;
        return q.move(move.x1,move.y1,move.x2,move.y2);
    }
    if (move.name == 'K'){
        King k;
        return k.move(move.x1,move.y1,move.x2,move.y2);
    }
    if (move.name == 'N'){
        Knight n;
        return n.move(move.x1,move.y1,move.x2,move.y2);
    }
    if (move.name == 'B'){
        Bishop b;
        return b.move(move.x1,move.y1,move.x2,move.y2);
    }
    if (move.name == 'R'){
        Rook r;
        return r.move(move.x1,move.y1,move.x2,move.y2);
    }
    // printf("shit");
    return false;
}

int main(){
    string query;
    ChessChecker checker;
    getline(cin,query);
    if (checker.check_move(query)){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

}