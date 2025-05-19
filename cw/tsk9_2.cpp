#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;

void processCommand(list<int>& lst, const string& cmd, const string& arg1, const string& arg2) {
    try {
        if (cmd == "-af") {
            int num = stoi(arg1);
            lst.push_front(num);
        } else if (cmd == "-ae") {
            int num = stoi(arg1);
            lst.push_back(num);
        } else if (cmd == "-ib") {
            int num1 = stoi(arg1);
            int num2 = stoi(arg2);
            auto it = find(lst.begin(), lst.end(), num2);
            if (it != lst.end()) {
                lst.insert(it, num1);
            }
        } else if (cmd == "-ia") {
            int num1 = stoi(arg1);
            int num2 = stoi(arg2);
            auto it = find(lst.begin(), lst.end(), num2);
            if (it != lst.end()) {
                lst.insert(++it, num1);
            }
        } else if (cmd == "-d") {
            int num = stoi(arg1);
            auto it = find(lst.begin(), lst.end(), num);
            if (it != lst.end()) {
                lst.erase(it);
            }
        } else if (cmd == "-sa") {
            lst.sort();
        } else if (cmd == "-sd") {
            lst.sort(greater<int>());
        } else if (cmd == "-mf") {
            if (!lst.empty()) {
                auto max_it = max_element(lst.begin(), lst.end());
                int max_val = *max_it;
                lst.erase(max_it);
                lst.push_front(max_val);
            }
        } else if (cmd == "-me") {
            if (!lst.empty()) {
                auto max_it = max_element(lst.begin(), lst.end());
                int max_val = *max_it;
                lst.erase(max_it);
                lst.push_back(max_val);
            }
        }
    } catch (const invalid_argument& e) {
        // Если преобразование строки в число не удалось, просто игнорируем команду
    } catch (const out_of_range& e) {
        // Если число выходит за пределы диапазона int, игнорируем команду
    }
}

int main(int argc, char* argv[]) {
    list<int> lst;
    string line;
    
    // Чтение списка чисел из stdin
    getline(cin, line);
    istringstream iss(line);
    int num;
    while (iss >> num) {
        lst.push_back(num);
    }
    
    // Обработка команд из командной строки
    if (argc >= 2) {
        string cmd = argv[1];
        string arg1, arg2;
        
        if (cmd == "-af" || cmd == "-ae" || cmd == "-d") {
            if (argc >= 3) {
                arg1 = argv[2];
                processCommand(lst, cmd, arg1, "");
            }
        } else if (cmd == "-ib" || cmd == "-ia") {
            if (argc >= 4) {
                arg1 = argv[2];
                arg2 = argv[3];
                processCommand(lst, cmd, arg1, arg2);
            }
        } else if (cmd == "-sa" || cmd == "-sd" || cmd == "-mf" || cmd == "-me") {
            processCommand(lst, cmd, "", "");
        }
    }
    
    // Вывод результата
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (it != lst.begin()) {
            cout << " ";
        }
        cout << *it;
    }
    cout << endl;
    
    return 0;
}