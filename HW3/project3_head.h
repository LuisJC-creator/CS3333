/**************************************************************************
Class:			CSCI 3333.01 Data Structures and Algorithms
				Spring 2025
Project 3:		Finding Common Patterns from Large Text Documents
Name:			Coder Warrior
ID:             11111111
Description:	In this header file for Project 3, we define myPhraseType, 
				and several functions. 
**************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// ---------- helpers ----------

// keep only ASCII
inline bool is_ascii(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return uc <= 127;
}

// allowed inside words per spec: letters, digits, hyphen, apostrophe, underscore, plus space as separator
inline bool allowed_token_char(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '\'' || c == '_' || c == ' ';
}

// trim helpers
inline void ltrim(string& s) {
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    s.erase(0, i);
}
inline void rtrim(string& s) {
    if (s.empty()) return;
    size_t i = s.size();
    while (i > 0 && std::isspace(static_cast<unsigned char>(s[i-1]))) --i;
    s.erase(i);
}
inline void trim(string& s) { ltrim(s); rtrim(s); }

// split on single spaces (assumes input already normalized to single spaces)
inline int split_words(const string& s, vector<string>& out) {
    out.clear();
    if (s.empty()) return 0;
    std::istringstream iss(s);
    string w;
    while (iss >> w) out.push_back(w);
    return static_cast<int>(out.size());
}

// ---------- required utilities ----------

//find number of words in a string
int findNumOfWords(string str)
{
    trim(str);
    if (str.empty()) return 0;
    int cnt = 0;
    bool in_word = false;
    for (char c : str) {
        if (c == ' ') {
            if (in_word) { ++cnt; in_word = false; }
        } else {
            in_word = true;
        }
    }
    if (in_word) ++cnt;
    return cnt;
}

//take non-ASCII characters out of a string 
void takeOutStangers(string& str)
{
    string t; t.reserve(str.size());
    for (char c : str) {
        if (is_ascii(c)) t.push_back(c);
    }
    str.swap(t);
}

//convert to lower case and take off extra non-alpha or non-number characters
//(keep only letters/digits and the three allowed punctuation marks inside words: - ' _ )
//collapse multiple spaces to a single space and trim
void clean(string& str)
{
    // lowercase + replace disallowed chars with space
    for (char& c : str) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        if (!allowed_token_char(c)) c = ' ';
    }
    // collapse multiple spaces
    string t; t.reserve(str.size());
    bool prev_space = true; // start true so leading spaces get dropped
    for (char c : str) {
        bool is_space = (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
        if (is_space) {
            if (!prev_space) { t.push_back(' '); prev_space = true; }
        } else {
            t.push_back(c);
            prev_space = false;
        }
    }
    str.swap(t);
    trim(str);
}

// ---------- phrase type ----------

class myPhraseType
{
private:
    string str;         // save a phrase with spaces
    int count;          // total frequency across the two books (for ranking)
    int numOfWords;     // number of words in the phrase

public:
    bool operator<=(myPhraseType& p);
    bool operator<(myPhraseType& p);
    bool operator==(myPhraseType& p);
    void setPhrase(string s, int c);
    myPhraseType& operator=(const myPhraseType& p);
    myPhraseType();
    myPhraseType(const myPhraseType& p);
    int getNumOfWords() const { return numOfWords; }
    int getFreq() const { return count; }
    const string& getPhrase() const { return str; }
    void clear() { str.clear(); count = numOfWords = 0; }
};

// define all the methods for myPhraseType
inline myPhraseType::myPhraseType() : str(), count(0), numOfWords(0) {}
inline myPhraseType::myPhraseType(const myPhraseType& p)
    : str(p.str), count(p.count), numOfWords(p.numOfWords) {}

inline void myPhraseType::setPhrase(string s, int c) {
    str = std::move(s);
    count = c;
    numOfWords = findNumOfWords(str);
}

inline myPhraseType& myPhraseType::operator=(const myPhraseType& p) {
    if (this != &p) {
        str = p.str;
        count = p.count;
        numOfWords = p.numOfWords;
    }
    return *this;
}

// Order: higher frequency first; tie-break by fewer words (shorter phrase), then lex ascending.
inline bool myPhraseType::operator<(myPhraseType& p) {
    if (count != p.count) return count > p.count;                  // descending by count
    if (numOfWords != p.numOfWords) return numOfWords < p.numOfWords;
    return str < p.str;
}
inline bool myPhraseType::operator<=(myPhraseType& p) {
    return (*this < p) || (*this == p);
}
inline bool myPhraseType::operator==(myPhraseType& p) {
    return str == p.str;  // phrase identity
}

// Comparator where "true" means a is BETTER than b.
// Using this as the heap comparator makes a min-heap of quality: heap.front() is the WORST kept item.
struct PhraseBetter {
    bool operator()(const myPhraseType& a, const myPhraseType& b) const {
        if (a.getFreq() != b.getFreq()) return a.getFreq() > b.getFreq();            // higher freq is better
        if (a.getNumOfWords() != b.getNumOfWords()) return a.getNumOfWords() < b.getNumOfWords(); // fewer words better
        return a.getPhrase() < b.getPhrase();                                        // lexicographically earlier better
    }
};

// insert a phrase into a vector of at most 10 myPhraseType objects and keep the vector in descending order.
// Internally maintain a MIN-heap of size <= 10 where front() is the WORST kept item.
void insertPhrase(vector<myPhraseType>& list, myPhraseType& p)
{
    static PhraseBetter better;

    // de-dup inside the heap (n ≤ 10 → O(n) is fine)
    for (auto& x : list) {
        if (x.getPhrase() == p.getPhrase()) {
            // keep the better version (higher freq / tie-breaks)
            if (better(p, x)) { x = p; std::make_heap(list.begin(), list.end(), better); }
            return;
        }
    }

    if (list.size() < 10) {
        list.push_back(p);
        std::push_heap(list.begin(), list.end(), better);
        return;
    }

    // If new phrase is better than the current worst (front), replace it
    if (better(p, list.front())) {
        std::pop_heap(list.begin(), list.end(), better); // moves worst to back
        list.back() = p;
        std::push_heap(list.begin(), list.end(), better);
    }
}
