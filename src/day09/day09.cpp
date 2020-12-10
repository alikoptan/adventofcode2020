#include "string"
#include "deque"
#include "vector"
#include "iostream"
#include "climits"
#include "unordered_map"
using namespace std;

class day9 {
private:
    const int PERMABLE = 25;
    long long anomaly = 0;
    vector <long long> numberList, prefixSum;
    deque <long long> window;

    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while (getline(cin, line)) {
            numberList.push_back(stol(line));
        }
    }
    bool exists(deque<long long> currentWindow, long long target) {
        unordered_map <long long, bool> table;
        while (!currentWindow.empty()) {
            if (table[target - currentWindow.front()])
                return true;
            table[currentWindow.front()] = true;
            currentWindow.pop_front();
        }
        return false;
    }
    void initSum() {
        long long currentSum = 0;
        for (auto element : numberList) {
            currentSum += element;
            prefixSum.push_back(currentSum);
        }
    }
    long long getSum(int& i, int& j) {
        if (!j)
            return prefixSum[j];
        return prefixSum[j] - prefixSum[i - 1];
    }
public:
    day9() {
        readFile();
    }
    void part1() {
        for (int i = 0; i < PERMABLE; i++)
            window.push_back(numberList[i]);

        for (int i = PERMABLE; i < numberList.size(); i++) {
            if (exists(window, numberList[i])) {
                window.pop_front();
                window.push_back(numberList[i]);
            }else {
                this->anomaly = numberList[i];
                break;
            }
        }
        cout << "Part 1: " << this->anomaly << '\n';
    }
    void part2() {
        initSum();
        long long borderSum = 0, minimum = LONG_MAX, maximum = 0;
        for (int i = 0; i < numberList.size(); i++) {
            for (int j = i + 1; j < numberList.size(); j++) {
                if (getSum(i, j) == anomaly) {
                    for (int k = i; k <= j; k++) {
                        minimum = min(minimum, numberList[k]);
                        maximum = max(maximum, numberList[k]);
                    }
                    borderSum = minimum + maximum;
                    break;
                }
            }
        }
        cout << "Part 2: " << borderSum << '\n';
    }
};

int main() {
    day9 solution;
    solution.part1();
    solution.part2();
    return 0;
}
