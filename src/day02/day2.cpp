#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class day2 {
private:
    class record {
    public:
        int low, high;
        char targetChar;
        string password;
    };
    vector<record> database;
    static record parseText(string& row) {
        record newRecord;
        size_t splitIndex = row.find(':'), firstDash = row.find('-'), firstSpace = row.find(' ');
        newRecord.password = row.substr(splitIndex + 2, row.size() - (splitIndex + 2));
        newRecord.targetChar = row[splitIndex - 1];
        newRecord.low = stoi(row.substr(0, firstDash));
        newRecord.high = stoi(row.substr(firstDash + 1, firstSpace + 1 - firstDash));
        return newRecord;
    }
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while(getline(cin, line)) {
            database.push_back(parseText(line));
        }
    }

public:
    day2() {
        readFile();
    }
    void part1() {
        int validPasswords = 0;
        for (auto r : database) {
            int charCount = std::count(r.password.begin(), r.password.end(), r.targetChar);
            validPasswords += charCount >= r.low && charCount <= r.high;
        }
        cout << "Part 1: " << validPasswords << '\n';
    }
    void part2() {
        int validPasswords = 0;
        for (auto r : database) {
            validPasswords += ((r.password[r.low - 1] == r.targetChar) + (r.password[r.high - 1] == r.targetChar) == 1);
        }
        cout << "Part 2: " << validPasswords << '\n';
    }
};

int main() {
    day2 solution;
    solution.part1();
    solution.part2();
    return 0;
}
