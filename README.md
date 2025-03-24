# Trie Dictionary Spell Checker

## Overview

This program implements a dictionary using a Trie data structure for efficient word storage and retrieval. It provides spell-checking capabilities and suggestions for misspelled words based on edit distance (insertions, deletions, substitutions, transpositions) and prefix matching.
Programming language used is C++.

## Setup
Clone this repository. Run the code on VSCode by pressing `CTRL+ALT+N`. Then you are good to go.

## Data Structures

### TrieNode

**Purpose**: Represents a node in the Trie.

**Structure**:
- `unordered_map<char, TrieNode*> children`: Maps characters to child nodes for O(1) average access.
- `bool isEndOfWord`: Flag indicating if the node marks the end of a valid word.

**Time Complexity**:
- Access/Insertion in children: O(1) average (hash table operations)

### Dictionary

**Purpose**: Manages the Trie and provides dictionary operations.

**Structure**:
- `TrieNode* root`: Root of the Trie
- Private helper methods for Trie deletion, suggestions, and edit generation

## Core Methods

### `Dictionary::insert(string& word)`

**Logic**:
- Traverses the Trie, creating new nodes as needed for each character in the word
- Marks the end node as `isEndOfWord = true`

**Time Complexity**: O(L), where L is the word length

### `Dictionary::search(string& word)`

**Logic**:
- Traverses the Trie to check if the word exists
- Returns true only if the final node is marked as the end of a word

**Time Complexity**: O(L), where L is the word length

### `Dictionary::suggestCorrections(string& word)`

**Logic**:
1. Generate Edits: Create all possible single-edit variations of the input word
2. Check Valid Edits: Search the Trie for valid words among the edits
3. Fallback to Prefix Suggestions: If no valid edits are found, suggest words sharing the longest prefix with the input
4. Sort and Deduplicate: Ensure suggestions are unique and ordered

**Time Complexity**:
- Edit Generation: O(L²) for a word of length L
- Edit Validation: O(L² * K), where K is the average length of edits
- Prefix Suggestions: O(M), where M is the number of nodes under the longest prefix
- Sorting/Deduplication: O(S log S), where S is the number of suggestions

## Helper Methods

### `generateEdits(string& word, vector<string>& edits)`

**Logic**:
- Insertions: Add each possible character (a-z) at every position
- Deletions: Remove each character once
- Substitutions: Replace each character with every possible letter
- Transpositions: Swap adjacent characters

**Time Complexity**: O(L²) for generating up to 4 * 26 * L possible edits

### `getSuggestions(TrieNode* node, string prefix, vector<string>& suggestions)`

**Logic**:
- Recursively collect all words starting from node with the given prefix

**Time Complexity**: O(N), where N is the number of nodes in the subtree

## Helper Functions

### `toLower(string& str)`

**Purpose**: Converts a string to lowercase for case-insensitive comparisons

**Time Complexity**: O(L), where L is the string length

### `loadDictionary(Dictionary& dict, const string& filename)`

**Purpose**: Reads words from a file and inserts them into the Trie

**Time Complexity**: O(N * L), where N is the number of words and L is the average word length

## Main Function

**Logic**:
- Loads the dictionary from a file
- Provides an interactive loop for users to search words or exit
- Handles input case insensitively and provides spell-check suggestions

**Usage Example**:
```bash
Enter a word to search (or 'exit' to quit): helo
Word not found. Suggestions:
hello
help
```

## Time Complexity Summary

| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| insert | O(L) | Insert a word of length L |
| search | O(L) | Search for a word of length L |
| generateEdits | O(L²) | Generate edits for a word of length L |
| suggestCorrections | O(L² + S log S) | Generate and process suggestions |
| loadDictionary | O(N * L) | Load N words of average length L |

## Key Design Choices

- **Trie Structure**: Optimized for prefix-based operations and memory efficiency
- **Edit Distance**: Generates all single-edit variations to mimic common typos
- **Case Insensitivity**: All words are stored and compared in lowercase
- **Fallback Suggestions**: Prefix-based suggestions ensure useful results even when no edits match
