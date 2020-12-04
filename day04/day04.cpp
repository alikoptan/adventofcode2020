#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
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
    static bool verify_byr(const string& byr) {
        size_t splitIndex = byr.find(':');
        int year = stoi(byr.substr(splitIndex + 1, byr.size() - splitIndex));
        return (year >= 1920 && year <= 2002);
    }
    static bool verify_iyr(const string& iyr) {
        size_t splitIndex = iyr.find(':');
        int year = stoi(iyr.substr(splitIndex + 1, iyr.size() - splitIndex));
        return (year >= 2010 && year <= 2020);
    }
    static bool verify_eyr(const string& eyr) {
        size_t splitIndex = eyr.find(':');
        int year = stoi(eyr.substr(splitIndex + 1, eyr.size() - splitIndex));
        return (year >= 2020 && year <= 2030);
    }
    static bool verify_hgt(const string& hgt) {
        size_t splitIndex = hgt.find(':');
        string height = hgt.substr(splitIndex + 1, hgt.size() - splitIndex);
        size_t unit = height.find("cm");
        bool validHeight = false;
        if (unit != -1) {
            int h = 0;
            for (size_t i = 0; i < unit; i++) {
                h *= 10;
                h += height[i] - '0';
            }
            validHeight |= (h >= 150 && h <= 193);
        }
        unit = height.find("in");
        if (unit != -1) {
            int h = 0;
            for (size_t i = 0; i < unit; i++) {
                h *= 10;
                h += height[i] - '0';
            }
            validHeight |= (h >= 59 && h <= 76);
        }
        return validHeight;
    }
    static bool verify_hcl(const string& hcl) {
        size_t splitIndex = hcl.find(':');
        string hairColor = hcl.substr(splitIndex + 1, hcl.size() - splitIndex);
        if (hairColor.size() != 7 || hairColor[0] != '#') return false;
        bool matchesPattern = true;
        for (size_t i = 1; i < hairColor.size(); i++) {
            matchesPattern &= (hairColor[i] >= '0' && hairColor[i] <= '9') || (hairColor[i] >= 'a' && hairColor[i] <= 'f');
        }
        return matchesPattern;
    }
    static bool verify_ecl(const string& ecl) {
        size_t splitIndex = ecl.find(':');
        string eyeColor = ecl.substr(splitIndex + 1, ecl.size() - splitIndex);
        return eyeColor == "amb" || eyeColor == "blu" || eyeColor == "brn" || eyeColor == "gry" || eyeColor == "grn" || eyeColor == "hzl" || eyeColor == "oth";
    }
    static bool verify_pid(const string& pid) {
        size_t splitIndex = pid.find(':');
        string passport = pid.substr(splitIndex + 1, pid.size() - splitIndex);
        bool allDigits = true;
        for (const auto& digit : passport) {
            allDigits &= (digit >= '0' && digit <= '9');
        }
        return passport.size() == 9 && allDigits;
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
        verifyTable["byr"] = verify_byr;
        verifyTable["iyr"] = verify_iyr;
        verifyTable["eyr"] = verify_eyr;
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
