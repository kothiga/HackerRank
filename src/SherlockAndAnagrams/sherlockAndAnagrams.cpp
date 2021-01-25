#include <bits/stdc++.h>

using namespace std;

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {

    int counter = 0;

    //-- For length of string between 1 and N-1.
    for (size_t len = 1; len < s.length(); ++len) {
        
        //-- Create each possible substring of length len.
        for (size_t pos1 = 0; pos1 < s.length()-len; ++pos1) {
            
            //-- Get the first comparing string.
            string str1 = s.substr(pos1, len);
            
            //-- Create the next string of length len at the
            //-- possible positions to the right of pos1.
            for (size_t pos2 = pos1+1; pos2 <= s.length()-len; ++pos2) {

                string str2 = s.substr(pos2, len);

                sort(str1.begin(), str1.end());
                sort(str2.begin(), str2.end());

                if (str1.compare(str2) == 0) { counter++; }                
            }
        }
    }

    return counter;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
