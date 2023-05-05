#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<string> findRepeatedDnaSequences(string s) {
    map<string, int> sequence_counts;
    vector<string> sequences;

    if (s.size() < 10){
        return sequences;
    }

    for (size_t i = 0; i < s.size() - 9; i++){
        string subs = s.substr(i, 10);
        sequence_counts[subs]++;
    }

    for(auto it = sequence_counts.begin(); it != sequence_counts.end(); it++){
        if (it->second >= 2){
            sequences.push_back(it->first);
        }
    }
    return sequences;
}