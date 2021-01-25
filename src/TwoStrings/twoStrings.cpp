#include <bits/stdc++.h>

using namespace std;

// Complete the twoStrings function below.
string twoStrings(string s1, string s2) {

    //-- Create a table of letters.
    map<char,bool> hash;
    for (int c = 0; c < 26; ++c) {
        hash['a'+c] = false;
    }

    //-- Add the presence of letters in 
    //-- the first word to our hashmap.
    for (int idx = 0; idx < s1.length(); ++idx) {
        char c = s1[idx];
        hash[c] = true;
    }

    //-- Go through the second word and look 
    //-- for a char that is also in the first.
    for (int idx = 0; idx < s2.length(); ++idx) {
        char c = s2[idx];
        if (hash[c]) { return "YES"; }
    }

    return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s1;
        getline(cin, s1);

        string s2;
        getline(cin, s2);

        string result = twoStrings(s1, s2);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
