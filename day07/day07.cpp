#include "string"
#include "map"
#include "vector"
#include "iostream"
#include "sstream"
using namespace std;

class day7 {
private:
    class component {
    public:
        string identifier;
        short requiredQty;
        component(string id, short qty): identifier(id), requiredQty(qty) {}
        const bool operator<(const component& other) {  // map comparison.
            return this->requiredQty < other.requiredQty;
        }
    };
    map <string, vector<component>> requiredBags;
    component parseComponent(const string& child) {
        // [4 wavy green bags]
        string id;
        short qty = 0;
        stringstream ss(child);
        string p1, p2;
        ss >> qty >> p1 >> p2;
        id = p1 + " " + p2;
        component newComponent(id, qty);
        return newComponent;
    }
    void process (string& line) {
        // plaid bronze bags contain 4 wavy green bags, 4 mirrored blue bags, 4 faded magenta bags, 5 plaid olive bags.
        size_t split = line.find("contain") + 8;
        string root = line.substr(0, line.find("bag") - 1);  // [plaid bronze]
        string childrenLine = line.substr(split, line.size() - split);  // [4 wavy green bags, 4 mirrored blue bags, 4 faded magenta bags, 5 plaid olive bags]
        vector <component> childrenList;
        stringstream ss(childrenLine);
        string token;
        while (getline(ss, token, ',')) {
            component newComponent = parseComponent(token);
            if (!newComponent.requiredQty) continue;
            childrenList.push_back(newComponent);
        }
        requiredBags[root] = childrenList;
    }
    void readFile() {
        freopen("input.txt", "r", stdin);
        string line;
        while (getline(cin, line)) {
            process(line);
        }
    }
    bool exists(string node) {
        if (node == "shiny gold")
            return true;
        bool search = false;
        for (auto child : requiredBags[node])
            search |= exists(child.identifier);
        return search;
    }
    int simulate(string bag) {
        if (requiredBags.find(bag) == requiredBags.end())
            return 0;
        int totalBags = 0;
        for (auto child : requiredBags[bag]) {
            totalBags += child.requiredQty * simulate(child.identifier) + child.requiredQty;
        }
        return totalBags;
    }
public:
    day7() {
        readFile();
    }
    void part1() {
        int validBags = 0;
        for (auto n : requiredBags) {
            if (n.first != "shiny gold") {
                validBags += exists(n.first);
            }
        }
        cout << "Part 1: " << validBags << '\n';
    }
    void part2() {
        cout << "Part 2: " << simulate("shiny gold");
    }
};

int main() {
    day7 solution;
    solution.part1();
    solution.part2();
}
