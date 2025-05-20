#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <vector>
#include <cctype>

using namespace std;

// Абстрактный класс Figure
class Figure {
public:
    virtual ~Figure() = default;
    virtual bool move(int startX, int startY, int targetX, int targetY) const = 0;
};

// Классы для конкретных фигур
class King : public Figure {
public:
    bool move(int startX, int startY, int targetX, int targetY) const override {
        int dx = abs(targetX - startX);
        int dy = abs(targetY - startY);
        return (dx <= 1 && dy <= 1);
    }
};

class Queen : public Figure {
public:
    bool move(int startX, int startY, int targetX, int targetY) const override {
        int dx = abs(targetX - startX);
        int dy = abs(targetY - startY);
        return (dx == dy) || (startX == targetX || startY == targetY);
    }
};

class Rook : public Figure {
public:
    bool move(int startX, int startY, int targetX, int targetY) const override {
        return (startX == targetX || startY == targetY);
    }
};

class Bishop : public Figure {
public:
    bool move(int startX, int startY, int targetX, int targetY) const override {
        int dx = abs(targetX - startX);
        int dy = abs(targetY - startY);
        return (dx == dy);
    }
};

class Knight : public Figure {
public:
    bool move(int startX, int startY, int targetX, int targetY) const override {
        int dx = abs(targetX - startX);
        int dy = abs(targetY - startY);
        return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
    }
};

// Класс Parser для разбора входных данных
class Parser {
public:
    static bool parse(const string& input, char& piece, int& startX, int& startY, int& targetX, int& targetY) {
        if (input.length() < 5) return false;
        
        piece = toupper(input[0]);
        if (piece != 'K' && piece != 'Q' && piece != 'R' && piece != 'B' && piece != 'N') {
            return false;
        }
        
        if (input[1] != ' ') return false;
        
        if (!isalpha(input[2]) || !isdigit(input[3])) return false;
        startX = tolower(input[2]) - 'a';
        startY = input[3] - '1';
        
        if (input[4] != ' ') return false;
        
        if (!isalpha(input[5]) || !isdigit(input[6])) return false;
        targetX = tolower(input[5]) - 'a';
        targetY = input[6] - '1';
        
        // Проверка, что координаты в пределах доски
        if (startX < 0 || startX > 7 || startY < 0 || startY > 7 ||
            targetX < 0 || targetX > 7 || targetY < 0 || targetY > 7) {
            return false;
        }
        
        return true;
    }
};

// Основной класс ChessChecker
class ChessChecker {
private:
    vector<unique_ptr<Figure>> figures;
    
public:
    ChessChecker() {
        // Инициализация фигур
        figures['K' - 'K'] = make_unique<King>();
        figures['Q' - 'K'] = make_unique<Queen>();
        figures['R' - 'K'] = make_unique<Rook>();
        figures['B' - 'K'] = make_unique<Bishop>();
        figures['N' - 'K'] = make_unique<Knight>();
    }
    
    string checkMove(const string& input) {
        char piece;
        int startX, startY, targetX, targetY;
        
        if (!Parser::parse(input, piece, startX, startY, targetX, targetY)) {
            return "NO";
        }
        
        // Проверка, что начальная и целевая клетки разные
        if (startX == targetX && startY == targetY) {
            return "NO";
        }
        
        // Получаем соответствующую фигуру
        int index;
        switch(piece) {
            case 'K': index = 0; break;
            case 'Q': index = 1; break;
            case 'R': index = 2; break;
            case 'B': index = 3; break;
            case 'N': index = 4; break;
            default: return "NO";
        }
        
        if (figures[index]->move(startX, startY, targetX, targetY)) {
            return "YES";
        } else {
            return "NO";
        }
    }
};

int main() {
    ChessChecker checker;
    string input;
    
    cin >> input;
    
    cout << checker.checkMove(input) << endl;
    
    return 0;
}