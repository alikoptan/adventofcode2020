#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class day8 {
private:
    vector <string> textInput;
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while(getline(cin, line)) {
            textInput.push_back(line);
        }
    }
    int attempt(bool checkValue = false) {
        unordered_map<int, bool> visited;
        int acc = 0, programLength = textInput.size();
        for (int i = 0; i < programLength; i++) {
            visited[i] = true;
            /*
                013456
                acc -1
                jmp +1
            */
            if (textInput[i].find("acc") != string::npos) {
                acc += stoi(textInput[i].substr(4, textInput.size() - 4));
            }else if (textInput[i].find("jmp") != string::npos) {
                int target = stoi(textInput[i].substr(4, textInput.size() - 4));
                if (visited[i + target]) {
                    return (checkValue ? acc : -1);
                }
                i += target - 1;
            }
        }
        return acc;
    }
    string modifyInstruction(string input) {
        /*
            013456
            acc -1
            jmp +1
        */
        string identifier = input.substr(0, 3);
        string operand = input.substr(4, input.size() - 4);
        if (identifier == "jmp")
            identifier = "nop";
        else if (identifier == "nop")
            identifier = "jmp";
        return identifier + " " + operand;
    }

public:
    day8() {
        readFile();
    }
    void part1() {
        cout << "Part 1: " << attempt(1) << '\n';
    }
    void part2() {
        int successVal = 0;
        for (int i = 0; i < textInput.size(); i++) {
            string originalInstruction = textInput[i];
            textInput[i] = modifyInstruction(originalInstruction);
            int returnVal = attempt();
            if (returnVal != -1)
                successVal = returnVal;
            textInput[i] = originalInstruction;
        }
        cout << "Part 2: " << successVal << '\n';
    }
};
int main() {
   day8 solution;
   solution.part1();
   solution.part2();
}
