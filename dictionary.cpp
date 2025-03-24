#include <cctype>
#include <bits/stdc++.h>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Dictionary {
private:
    TrieNode* root;

    void deleteTrie(TrieNode* node) {
        for (auto& pair : node->children) {
            deleteTrie(pair.second);
        }
        delete node;
    }

    void getSuggestions(TrieNode* node, string currentPrefix, vector<string>& suggestions) {
        if (node->isEndOfWord) {
            suggestions.push_back(currentPrefix);
        }
        for (auto& child : node->children) {
            getSuggestions(child.second, currentPrefix + child.first, suggestions);
        }
    }

    void generateEdits(string& word, vector<string>& edits) {
        // Insertions
        for (size_t i = 0; i <= word.size(); ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                string edit = word.substr(0, i) + c + word.substr(i);
                edits.push_back(edit);
            }
        }

        // Deletions
        for (size_t i = 0; i < word.size(); ++i) {
            string edit = word.substr(0, i) + word.substr(i + 1);
            edits.push_back(edit);
        }

        // Substitutions
        for (size_t i = 0; i < word.size(); ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                string edit = word;
                edit[i] = c;
                edits.push_back(edit);
            }
        }

        // Transpositions
        for (size_t i = 0; i < word.size() - 1; ++i) {
            string edit = word;
            swap(edit[i], edit[i + 1]);
            edits.push_back(edit);
        }
    }

public:
    Dictionary() : root(new TrieNode()) {}

    ~Dictionary() {
        deleteTrie(root);
    }

    void insert(string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    bool search(string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    vector<string> suggestCorrections(string& word) {
        vector<string> suggestions;
        vector<string> possibleEdits;
        generateEdits(word, possibleEdits);

        for (auto& edit : possibleEdits) {
            if (search(edit)) {
                suggestions.push_back(edit);
            }
        }

        if (suggestions.empty()) {
            TrieNode* current = root;
            string prefix;
            for (char c : word) {
                if (current->children.find(c) == current->children.end()) break;
                current = current->children[c];
                prefix += c;
                getSuggestions(current, prefix, suggestions);
            }
        }

        sort(suggestions.begin(), suggestions.end());
        suggestions.erase(unique(suggestions.begin(), suggestions.end()), suggestions.end());
        return suggestions;
    }
};

string toLower(string& str) {
    string lowerStr;
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
}

void loadDictionary(Dictionary& dict, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        word = toLower(word);
        dict.insert(word);
    }
    file.close();
}

int main() {
    Dictionary dict;
    loadDictionary(dict, "sd 1 list.txt");

    string input;
    while (true) {
        cout << "Enter a word to search (or 'exit' to quit): ";
        cin >> input;
        input = toLower(input);

        if (input == "exit") break;

        if (dict.search(input)) {
            cout << "Word found: " << input << endl;
        } else {
            cout << "Word not found. Suggestions:" << endl;
            auto suggestions = dict.suggestCorrections(input);
            if (suggestions.empty()) {
                cout << "No suggestions available." << endl;
            } else {
                int rate=0;
                for (auto& suggestion : suggestions) {
                    cout << suggestion << endl;
                    rate++;
                    if(rate==40){
                        break;
                    }
                }
            }
        }
    }

    return 0;
}