#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

double median(const vector<int>& freq, int num) {

    vector<int> cumulative(freq);
    for (size_t idx = 1; idx < cumulative.size(); ++idx) {
        cumulative[idx] += cumulative[idx-1];
    }

    int mid = (num / 2) + 1;
    
    int idx = 0;
    while (cumulative[idx] < mid) {
        idx++;
    }
    
    //-- Odd.
    if (num % 2) {
        return (double) idx;
    }

    //-- Even.
    mid = (num / 2);

    int jdx = 0; 
    while (cumulative[jdx] < mid) {
        jdx++;
    }

    return (double)(idx + jdx) / 2.0;
}


// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {

    //-- Create a count for each index.
    vector<int> rolling(201, 0);
    for (int idx = 0; idx < d; ++idx) {
        int val = expenditure[idx];
        rolling[val]++;
    }

    int count = 0, oldest = 0;
    for (size_t idx = d; idx < expenditure.size(); ++idx) {

        //-- Does the days expense meet the trigger req?
        if (expenditure[idx] >= 2*median(rolling, d)) {
            count++;
        }
        
        //-- Remove the oldest from the rolling window.
        rolling[expenditure[oldest]]--;
        oldest++;

        //-- Add the current expense to the window.
        rolling[expenditure[idx]]++;
    }

    return count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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
