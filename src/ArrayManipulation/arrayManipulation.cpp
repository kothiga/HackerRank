#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the arrayManipulation function below.
long arrayManipulation(int n, vector<vector<int>> queries) {
    
    //-- Using 1-based. Don't segfault.
    vector<long long> arr(n+2, 0);
    
    int a, b, k;
    for (int idx = 0; idx < queries.size(); ++idx) {
        
        a = queries[idx][0];
        b = queries[idx][1];
        k = queries[idx][2];
        
        //-- Make note of where the slope begins.
        arr[a] += k;
        
        //-- If the slope ends at the end, don't worry.
        if (b == n+1) { continue; }
        
        //-- Make note where the slope ends.
        arr[b+1] -= k;
    }
    
    //-- Iterate through the array.
    //-- Keep a running tally of the current value, 
    //-- and change it based on the slopes.
    //-- Keep track of the max value at each step.
    long ret = 0, running = 0;
    for (int idx = 1; idx <= n; ++idx) {
        running += arr[idx];
        ret = max(ret, running);
    }
    
    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = arrayManipulation(n, queries);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
