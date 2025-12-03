#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    const std::string& in, 
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string& curr,
    int pos,
    std::map<char, int>& remaining,
    std::set<std::string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    std::string curr = in;

    std::map<char, int> remaining;
    for (char c : floating) {
        remaining[c]++;
    }

    wordleHelper(in, floating, dict, curr, 0, remaining, results);

    return results;
}

// Define any helper functions here
void wordleHelper(
    const std::string& in, 
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string& curr,
    int pos,
    std::map<char, int>& remaining,
    std::set<std::string>& results) 
{
    if (pos == (int)in.length()) {
        if (remaining.empty() && dict.find(curr) != dict.end()) {
            results.insert(curr);
        }
        return;
    }

    if (in[pos] != '-') {
        wordleHelper(in, floating, dict, curr, pos+1, remaining, results);
        return;
    }

    int blanks = 0;
    for (int i = pos; i < (int)in.length(); ++i) {
        if (in[i] == '-') {
            blanks++;
        }
    }
    
    int floatingLeft = 0;
    for (const auto& p : remaining) {
        floatingLeft += p.second;
    }

    if (blanks < floatingLeft) {
        return;
    }

    for(char c = 'a'; c <= 'z'; c++) {
        curr[pos] = c;

        bool floatingUsed = false;
        if (remaining.find(c) != remaining.end()) {
            remaining[c]--;
            if (remaining[c] == 0) {
                remaining.erase(c);
            }
            floatingUsed = true;
        }

        wordleHelper(in, floating, dict, curr, pos+1, remaining, results);

        if (floatingUsed) {
            remaining[c]++;
        }
    }

    curr[pos] = '-';
}

