#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

class SequenceManager {
private:
    unordered_map<int, vector<int>> sequences;

public:
    void newSequence(int id) {
        if (id < 10000) {
            sequences[id] = vector<int>();
        } else {
            cout << "Invalid id." << endl;
        }
    }

    void addToSequence(int id, int num) {
        if (sequences.find(id)!= sequences.end()) {
            sequences[id].push_back(num);
        } else {
            cout << "Invalid id." << endl;
        }
    }

    void mergeSequences(int id1, int id2) {
        if (id1!= id2 && sequences.find(id1)!= sequences.end() && sequences.find(id2)!= sequences.end()) {
            sequences[id1].insert(sequences[id1].end(), sequences[id2].begin(), sequences[id2].end());
            sequences[id2].clear();
        }
    }

    void removeDuplicates(int id) {
        if (sequences.find(id)!= sequences.end()) {
            unordered_set<int> uniqueElements(sequences[id].begin(), sequences[id].end());
            sequences[id].assign(uniqueElements.begin(), uniqueElements.end());
        } else {
            cout << "Invalid id." << endl;
        }
    }

    void outputSequence(int id) {
        if (sequences.find(id)!= sequences.end()) {
            sort(sequences[id].begin(), sequences[id].end());
            for (int num : sequences[id]) {
                cout << num << " ";
            }
            cout << endl;
        } else {
            cout << "Invalid id." << endl;
        }
    }
};

int main() {
    SequenceManager manager;
    string command;
    while (cin >> command) {
        if (command == "new") {
            int id;
            cin >> id;
            manager.newSequence(id);
        } else if (command == "add") {
            int id, num;
            cin >> id >> num;
            manager.addToSequence(id, num);
        } else if (command == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            manager.mergeSequences(id1, id2);
        } else if (command == "unique") {
            int id;
            cin >> id;
            manager.removeDuplicates(id);
        } else if (command == "out") {
            int id;
            cin >> id;
            manager.outputSequence(id);
        }
    }
    return 0;
}