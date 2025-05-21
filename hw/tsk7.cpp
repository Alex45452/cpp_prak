#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>


using namespace std;

class PlayerError
{
    char *message;
    char *team;
    int number;
    bool hasnumber;
public:
    PlayerError(const char *msg, const char *t);
    PlayerError(const char *msg, const char *t, int num);
    ~PlayerError();

    const char *getMessage() const { return message; }
    const char *getTeam() const { return team; }
    int getNumber() const { return number; }
    bool numberGiven() const { return hasnumber; }
};

PlayerError::PlayerError(const char *msg, const char *t)
{
    number = 0;
    hasnumber = false;
    message = new char[strlen(msg) + 1];
    strcpy(message, msg);
    team = new char[strlen(t) + 1];
    strcpy(team, t);
}

PlayerError::PlayerError(const char *msg, const char *t, int num)
{
    number = num;
    hasnumber = 
    message = new char[strlen(msg) + 1];
    strcpy(message, msg);
    team = new char[strlen(t) + 1];
    strcpy(team, t);
}

PlayerError::~PlayerError()
{
    delete[] message;
    delete[] team;
}

class Player
{
    string team;
    int number;
    static map<string, vector<int>> playersInTeam;
    static map<string, set<int>> numsInTeam;

public:
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    Player(const char *t, int num);
    ~Player();

    void Print() const;
    static void Print_teams();
};

map<string, vector<int>> Player::playersInTeam;
map<string, set<int>> Player::numsInTeam;

Player::Player(const char *t, int num)
    : team(t), number(num)
{
    if (team != "Zenit" && team != "CSKA")
        throw PlayerError("Wrong name", t);
    if (number < 1)
        throw PlayerError("Wrong number", t, number);
    if (playersInTeam[team].size() >= 11)
        throw PlayerError("Too many players", t);
    if (numsInTeam[team].count(number))
        throw PlayerError("Double number", t, number);
    playersInTeam[team].push_back(number);
    numsInTeam[team].insert(number);
}

Player::~Player()
{
    numsInTeam[team].erase(number);
    auto &vec = playersInTeam[team];
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it == number) {
            vec.erase(it);
            break;
        }
    }
}

void Player::Print() const
{
    cout << team << ' ' << number << '\n';
}

void Player::Print_teams()
{
    for (const char *t : {"Zenit", "CSKA"}) {
        const auto &vec = playersInTeam[t];
        if (vec.empty()) continue;
        cout << t << ':';
        for (int n : vec)
            cout << ' ' << n;
        cout << '\n';
    }
}

void test_players();

int main()
{
    try {
        test_players();
    }
    catch (PlayerError &e) {
        if (e.numberGiven())
            cerr << "Exception: " << e.getMessage()
                 << " in team " << e.getTeam()
                 << " Error number: " << e.getNumber() << '\n';
        else
            cerr << "Exception: " << e.getMessage()
                 << " in team " << e.getTeam() << '\n';
    }
    catch (...) {
        cerr << "Exception: unknown error\n";
    }
    return 0;
}