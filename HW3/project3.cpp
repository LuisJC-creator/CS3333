/**************************************************************************
Class:			CSCI 3333.01 Data Structures and Algorithms
				Spring 2025
Project 3:		Finding Common Patterns from Large Text Documents
Name:			Coder Warrior
ID:             11111111
Description: use some combination of hash maps, lists, and sorting techniques 
	to discover the most common phrases and common paragraphs between two 
	large text documents: The King James version of the bible and 
	the Complete Works of William Shakespeare. 
Input file: bible.txt, WilliamShakespeare.txt
Output file: topPhrases.txt
Example format of output file:
	top 10 most frequent phrases of length 1
	phrase  		frequency in Bible		frequency in William Shakespeare
	trout			100						150
	snapper 		600						95	
	......
	top 10 most frequent phrases of length 2
	phrase  		frequency in Bible		frequency in William Shakespeare
	speckled trout	100						150
	red snapper 	600						95
	......
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	time used: xxx seconds
**************************************************************************/

#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <utility>
#include <time.h>

#include "project3_head.h"

using namespace std;

// helper: process one already-collected sentence into phrase counts map
static void process_sentence_into_map(const string& raw_sentence, unordered_map<string,int>& m) {
    string s = raw_sentence;
    takeOutStangers(s);     // remove non-ASCII
    clean(s);               // lowercase, keep allowed token chars, collapse spaces
    if (s.empty()) return;

    // tokenize
    vector<string> words;
    split_words(s, words);
    if (words.empty()) return;

    // sliding window for n = 1..10
    const int W = static_cast<int>(words.size());
    for (int n = 1; n <= 10; ++n) {
        if (W < n) break;
        for (int i = 0; i + n <= W; ++i) {
            // join words[i..i+n)
            string phrase;
            phrase.reserve(n * 6); // rough heuristic
            for (int k = 0; k < n; ++k) {
                if (k) phrase.push_back(' ');
                phrase += words[i + k];
            }
            ++m[phrase];
        }
    }
}

int main()
{
    ifstream myfile;  // input file variable
    istringstream ss; // string stream input
    ofstream outfile; // (not used; kept to match skeleton)

    unordered_map<string, int> bk1, bk2; // hash maps to store all phrases with frequencies
    vector<myPhraseType> topPhrases[10]; // top 10 lists of phrase of length 1 to 10
    string str;
    myPhraseType p; // this is defined in the header file
    time_t start, end; // to record timing

    // record the start time
    start = time(NULL);

    // ---------- load phrases into bk1 (Bible) ----------
    cout << "loading the Bible ...... " << endl;
    myfile.open("bible.txt");
    bk1.clear();
    {
        string buffer;
        char ch;
        while (myfile.get(ch)) {
            // treat . ! ? ; : as sentence terminators
            if (ch == '.' || ch == '!' || ch == '?' || ch == ';' || ch == ':') {
                process_sentence_into_map(buffer, bk1);
                buffer.clear();
            } else {
                buffer.push_back(ch);
            }
        }
        // tail
        if (!buffer.empty()) process_sentence_into_map(buffer, bk1);
    }
    myfile.close();
    cout << "finished loading the Bible. " << endl;

    // ---------- load phrases into bk2 (Shakespeare) ----------
    cout << "loading the Complet Work of William Shakespeare ...... " << endl;
    myfile.open("WilliamShakespeare.txt");
    bk2.clear();
    {
        string buffer;
        char ch;
        while (myfile.get(ch)) {
            if (ch == '.' || ch == '!' || ch == '?' || ch == ';' || ch == ':') {
                process_sentence_into_map(buffer, bk2);
                buffer.clear();
            } else {
                buffer.push_back(ch);
            }
        }
        if (!buffer.empty()) process_sentence_into_map(buffer, bk2);
    }
    myfile.close();
    cout << " finished loading William Shakepeare " << endl;

    // ---------- Use the two maps to find top phrases with 1 to 10 words ----------
    cout << "finding top phrases ......" << endl;

    // Merge keys from both maps and rank by total frequency (Bible + WS), bucket by phrase length
    auto consider_phrase = [&](const string& phrase) {
        int f1 = 0, f2 = 0;
        auto it1 = bk1.find(phrase); if (it1 != bk1.end()) f1 = it1->second;
        auto it2 = bk2.find(phrase); if (it2 != bk2.end()) f2 = it2->second;
        int total = f1 + f2;
        if (total <= 0) return;
        myPhraseType mp;
        mp.setPhrase(phrase, total);
        int n = mp.getNumOfWords();
        if (n >= 1 && n <= 10) insertPhrase(topPhrases[n - 1], mp);
    };

    for (const auto& kv : bk1) consider_phrase(kv.first);
    for (const auto& kv : bk2) consider_phrase(kv.first);

    // ---------- Output the top phrases ----------
    ofstream out("topPhrases.txt");
    PhraseBetter better;

    for (int n = 1; n <= 10; ++n) {
        out << "top 10 most frequent phrases of length " << n << "\n";
        out << left << setw(40) << "phrase"
            << right << setw(22) << "frequency in Bible"
            << right << setw(32) << "frequency in William Shakespeare" << "\n";

        // Copy heap → vector and sort best→worst using PhraseBetter
        auto vec = topPhrases[n - 1];
        std::sort(vec.begin(), vec.end(), better);

        for (const auto& mp : vec) {
            const string& phrase = mp.getPhrase();
            int f1 = 0, f2 = 0;
            auto it1 = bk1.find(phrase); if (it1 != bk1.end()) f1 = it1->second;
            auto it2 = bk2.find(phrase); if (it2 != bk2.end()) f2 = it2->second;

            out << left << setw(40) << phrase
                << right << setw(22) << f1
                << right << setw(32) << f2 << "\n";
        }
        out << "\n";
    }

    // record the end time
    end = time(NULL);
    // record the time to complete the work
    out << endl << "+++++++++++++++++++++" << endl;
    out << "time used: " << difftime(end, start) << " seconds" << endl;
    out.close();

    // Complete the work
    return 1;
}

