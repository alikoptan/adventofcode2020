#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

using namespace std;

class day6 {
private:
    vector <string> textInput;
    unordered_set<char> trackList;
    unordered_map<char, int> trackFreq;

    void readFile() {
        freopen("input.txt", "r", stdin);
        string line, group;
        while(getline(cin, line)) {
            if (line.empty()) {
                textInput.push_back(group);
                group.clear();
            }else
                group += line + " "; // seperate lines.
        }
        textInput.push_back(group);
    }

public:
    day6() {
        readFile();
    }
    void part1() {
        int answersCount = accumulate(textInput.begin(), textInput.end(), 0,[&](int& currentCount, string& group) {
            trackList.clear();
            trackList.insert(group.begin(), group.end());
            return currentCount + trackList.size() - 1; // skipping empty spaces.
        });
        cout << "Part 1: " << answersCount << '\n';
    }
    void part2() {
        int positiveCount = accumulate(textInput.begin(), textInput.end(), 0,[&](int& currentCount, string& group) {
            trackFreq.clear();
            int groupsCount = 0;
            stringstream ss;
            string votes;
            ss << group;
            while(ss >> votes) {
                for (auto v : votes) {
                    trackFreq[v]++;
                }
                groupsCount++;
            }
            int uniqueCounts = 0;
            for (auto f : trackFreq)
                uniqueCounts += f.second == groupsCount;
            return currentCount + uniqueCounts;
        });
        cout << "Part 2: " << positiveCount << '\n';
    }
};

int main() {
    day6 solution;
    solution.part1();
    solution.part2();
    return 0;
}
