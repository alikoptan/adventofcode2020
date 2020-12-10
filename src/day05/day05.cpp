#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class day5 {
private:
    vector <int> seatIDs;
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while(getline(cin, line)) {
            seatIDs.push_back(getSeat(line));
        }
    }
    int getSeat(string pass) {
        int seatID = 0;
        int low = 0, high = 127;
        for_each(pass.begin(), pass.end() - 3, [&](char& item) {
            if (item == 'F')
                high = (low + high) / 2;
            else low = (low + high) / 2 + 1;
        });
        seatID += low;
        seatID *= 8;
        low = 0, high = 7;
        for_each(pass.begin() + 7, pass.end(), [&](char& item) {
            if (item == 'L')
                high = (low + high) / 2;
            else low = (low + high) / 2 + 1;
        });
        seatID += low;
        return seatID;
    }

public:
    day5() {
        readFile();
    }
    void part1() {
        sort(seatIDs.begin(), seatIDs.end());
        cout << "Part 1: " << seatIDs.back() << '\n';
    }
    void part2() {
        // Observation: seats range from 91 to 928.
        int missingSeat = 0;
        for (int seat = 91; seat <= 928; seat++) {
            if (!binary_search(seatIDs.begin(), seatIDs.end(), seat)) {
                missingSeat = seat;
                break;
            }
        }
        cout << "Part 2: " << missingSeat << '\n';
    }
};

int main() {
    day5 solution;
    solution.part1();
    solution.part2();
    return 0;
}
