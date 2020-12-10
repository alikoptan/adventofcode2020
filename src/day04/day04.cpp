#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
using namespace std;

class day4 {
private:
    unordered_map<string, function<bool(string&)>> verifyTable;
    int totalPassports = 0, nonMissingPassports = 0, validPassports = 0;
    vector <string> fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
    vector <string> textInput;
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line, inputLine;
        while(getline(cin, line)) {
            if (line.empty()) {
                textInput.push_back(inputLine);
                inputLine = "";
            }
            else inputLine += line + " "; // seperateLineASeperateLineB -> seperateLineA seperateLineB
        }
        textInput.push_back(inputLine);
    }
    static bool verify_year(const string& yearToken) {
        size_t splitIndex = yearToken.find(':');
        int year = stoi(yearToken.substr(splitIndex + 1, yearToken.size() - splitIndex));
        string id = yearToken.substr(0, 3);
        if (id == "byr")
            return (year >= 1920 && year <= 2002);
        if (id == "iyr")
            return (year >= 2010 && year <= 2020);
        if (id == "eyr")
            return (year >= 2020 && year <= 2030);
    }
    static bool verify_hgt(const string& hgt) {
        size_t splitIndex = hgt.find(':');
        string height = hgt.substr(splitIndex + 1, hgt.size() - splitIndex);
        return regex_match(height, regex("(1[5-8][0-9]|19[0-3])cm")) or regex_match(height, regex("(59|6[0-9]|7[0-6])in"));
    }
    static bool verify_hcl(const string& hcl) {
        size_t splitIndex = hcl.find(':');
        string hairColor = hcl.substr(splitIndex + 1, hcl.size() - splitIndex);
        return regex_match(hairColor, regex("#([0-9]|[a-f]){6}"));
    }
    static bool verify_ecl(const string& ecl) {
        size_t splitIndex = ecl.find(':');
        string eyeColor = ecl.substr(splitIndex + 1, ecl.size() - splitIndex);
        return eyeColor == "amb" || eyeColor == "blu" || eyeColor == "brn" || eyeColor == "gry" || eyeColor == "grn" || eyeColor == "hzl" || eyeColor == "oth";
    }
    static bool verify_pid(const string& pid) {
        size_t splitIndex = pid.find(':');
        string passport = pid.substr(splitIndex + 1, pid.size() - splitIndex);
        return regex_match(passport, regex("[0-9]{9}"));
    }
    static bool verify_cid(const string& cid) {
        return true; // :)
    }
    bool verify(const string& line) {
        stringstream ss;
        ss << line;
        string item;
        bool valid = true;
        while(ss >> item) {
            string id = item.substr(0, 3);
            valid &= verifyTable[id](item);
        }
        return valid;
    }
    void reduceAndCount() {
        unordered_map<string, bool> exists;
        for (const auto& line : textInput) {
            stringstream ss;
            ss << line;
            string item;
            while(ss >> item) {
                string parse = item.substr(0, 3);
                exists[parse] = true;
            }
            int missing = 0; string missingField;
            for (const auto& f : fields) {
                if (!exists[f]) {
                    missing++;
                    missingField = f;
                }
            }
            if (!missing or (missing == 1 && missingField == "cid")) {
                nonMissingPassports++;
                if (verify(line)) {
                    validPassports++;
                }
            }
            totalPassports++;
            exists.clear();
        }
    }
    void mapFunctions() {
        verifyTable["byr"] = verify_year;
        verifyTable["iyr"] = verify_year;
        verifyTable["eyr"] = verify_year;
        verifyTable["hgt"] = verify_hgt;
        verifyTable["hcl"] = verify_hcl;
        verifyTable["ecl"] = verify_ecl;
        verifyTable["pid"] = verify_pid;
        verifyTable["cid"] = verify_cid;
    }
public:
    day4() {
        readFile();
    }
    void part1() {
        mapFunctions();
        reduceAndCount();
        cout << totalPassports << " total passports.\n";
        cout << "Part 1: " << nonMissingPassports << " don't contain more than 1 missing field.\n";
    }
    void part2() {
        cout << "Part 2: " << validPassports << " are valid.\n";
    }
};

int main() {
    day4 solution;
    solution.part1();
    solution.part2();
    return 0;
}
