#include <vector>
#include <string>
#include <iostream>

using namespace std;

class day3 {
private:
    vector<string> textFile;
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while(getline(cin, line)) {
            textFile.push_back(line);
        }
    }
    int countTrees(int directionX, int directionY) {
        int rows = textFile.size(), columns = textFile[0].size(), trees = 0;
        int startX = 0, startY = 0;
        while(startX < rows) {
            trees += textFile[startX][startY] == '#';
            startX += directionX;
            startY += directionY;
            startY %= columns;
        }
        return trees;
    }

public:
    day3() {
        readFile();
    }
    void part1() {
        cout << "Part 1: " << countTrees(1, 3) << '\n';
    }
    void part2() {
        vector<pair<int, int>> instructions = {
                {1, 1},
                {1, 3},
                {1, 5},
                {1, 7},
                {2, 1}
        };
        int totalTrees = 1;
        for (auto i : instructions) {
            int encounteredTrees = countTrees(i.first, i.second);
            cout << "for slopes(" << i.second << ", " << i.first << "): " << encounteredTrees << '\n';
            totalTrees *= encounteredTrees;
        }
        cout << "Part 2: " << totalTrees << '\n';
    }
};

int main() {
    day3 solution;
    solution.part1();
    solution.part2();
    return 0;
}
