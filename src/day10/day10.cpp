#include "string"
#include "vector"
#include "iostream"
#include "algorithm"
#include "map"
using namespace std;

class day10 {
private:
    vector <int> numberList;
    map <int, long long> memo;
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while (getline(cin, line)) {
            numberList.push_back(stoi(line));
        }
    }
    long long count(int lastChoice) {
        if (lastChoice == numberList.back())
            return 1;

        if (memo.find(lastChoice) != memo.end())
            return memo[lastChoice];

        long long sequenceCount = 0;
        for (size_t i = upper_bound(numberList.begin(), numberList.end(), lastChoice) - numberList.begin(); i < numberList.size(); i++) {
            if (numberList[i] - lastChoice > 3)  // No valid choices anymore, stopping.
                break;
            else sequenceCount += count(numberList[i]);
        }
        return memo[lastChoice] = sequenceCount;
    }

public:
    day10() {
        readFile();
    }
    void part1() {
        sort(numberList.begin(), numberList.end());
        int oneDiff = 1, threeDiff = 1; 
        for (size_t i = 0; i < numberList.size() - 1; i++) {
            oneDiff += abs(numberList[i] - numberList[i + 1]) == 1;
            threeDiff += abs(numberList[i] - numberList[i + 1]) == 3;
        }
        cout << "Part 1: " << oneDiff * threeDiff << '\n';
    }
    void part2() {
        cout << "Part 2: " << count(0) << '\n';
    }
};

int main() {
    day10 solution;
    solution.part1();
    solution.part2();
    return 0;
}
