#include <iostream>
#include <cstring>

using namespace std;

class event{
    char* subject;
    int day;
    int month;
    int year;
    event(event& op){};
public:
    event(const char* sub, int y, int m, int d);
    virtual ~event(){delete [] subject;}
    virtual void print_res() const;
    void change_date(int ny, int nm, int nd);
    virtual void change_grade(int ng) = 0;
};

class test:public event{
    bool result;
public:
    test(const char* sub, int y, int m, int d, bool g): event(sub, y, m ,d), result(g) {}
    test(const char* sub, int y, int m, int d, int g): event(sub, y, m ,d) {g < 3 ? result = false : result = true;}

    virtual void print_res() const;
    virtual void change_grade(bool ng){result=ng;}
    virtual void change_grade(int ng){ng < 3 ? result = false : result = true;}
};

class exam: public event{
    int grade;
public:
    exam(const char* sub, int y, int m, int d, int g): event(sub,y,m,d), grade(g){}
    virtual void print_res() const;
    virtual void change_grade(int ng){grade=ng;}
};

event::event(const char* sub, int y, int m, int d){
    subject = new char [strlen(sub)];
    strcpy(subject,sub);
    day = d;
    month = m;
    year = y;
}

void event::print_res() const{
    cout << subject << ' ' << year << ' ' << month << ' ' << day;
}

void event::change_date(int ny, int nm, int nd){
    year = ny;
    month = nm;
    day = nd;
}

void test::print_res() const{
    event::print_res();
    cout << ' ' << (result ? "true" : "false") << endl;
}

void exam::print_res() const{
    event::print_res();
    cout << ' ' << "Grade" << ' ' << grade << endl;
}
