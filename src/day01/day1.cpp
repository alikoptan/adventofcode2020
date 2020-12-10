#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class day1 {
private:
    vector<int> textFile;
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while(getline(cin, line)) {
            textFile.push_back(stoi(line));
        }
    }

public:
    day1() {
        readFile();
    }
    void part1() {
        unordered_map<int, bool> exists;
        int product = -1;
        for (auto e : textFile) {
            if (e >= 2020) {
                continue;
            }
            if (exists.find(2020 - e) != exists.end()) {
                product = e * (2020 - e);
                break;
            }
            exists[e] = true;
        }
        cout << "Part 1: " << product << '\n';
    }
    void part2() {
        int product = -1;
        for (int i = 0; i < textFile.size(); i++) {
            if (textFile[i] >= 2020) {
                continue;
            }
            for (int j = i + 1; j < textFile.size(); j++) {
                if (textFile[i] + textFile[j] >= 2020) {
                    continue;
                }
                for (int k = j + 1; k < textFile.size(); k++) {
                    if (textFile[i] + textFile[j] + textFile[k] == 2020) {
                        product = textFile[i] * textFile[j] * textFile[k];
                        break;
                    }
                }
            }
        }
        cout << "Part 2: " << product << '\n';
    }
};

int main() {
    day1 solution;
    solution.part1();
    solution.part2();
    return 0;
}
