#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

typedef pair<int,int> pii;

// Complete the luckBalance function below.
int luckBalance(int k, vector<vector<int>> contests) {

    int n = contests.size(), count = 0;

    vector<pii> vec;
    for (int idx = 0; idx < n; ++idx) {

        int luck = contests[idx][0];
        int imp  = contests[idx][1] ? 0 : 1;
        count += contests[idx][1];
        
        //-- imp = 0 : important contest
        //-- imp = 1 : not important
        vec.push_back(make_pair(imp,luck));
    }

    //-- Sort the vec of pairs. Important contests with 
    //-- least luck requirements will be at the front.
    sort(vec.begin(), vec.end());

    //-- Figure out the min number we have to win.
    int lose_n = count - k;

    int luck = 0;
    for (int idx = 0; idx < n; ++idx) {

        //-- Win the least luck required contests,
        //-- and lose all the rest. Never win unimportant.
        int mult = (idx < lose_n && vec[idx].first == 0) ? -1 : 1;

        luck += (mult * vec[idx].second);
    }
    
    return luck;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    vector<vector<int>> contests(n);
    for (int i = 0; i < n; i++) {
        contests[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> contests[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = luckBalance(k, contests);

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
