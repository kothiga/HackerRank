#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct state {
    int x, y, len;
    state(int X, int Y, int L) : x(X), y(Y), len(L) {}
};

// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {

    const int dr[4] = { -1,  1,  0,  0 };
    const int dc[4] = {  0,  0, -1,  1 };

    const int N = grid.size();

    vector<vector<bool>> seen(N, vector<bool>(N,false));
    
    queue<state> bfs;
    bfs.push(state(startX, startY, 0));

    while (!bfs.empty()) {

        //-- Get the current step.
        state cur = bfs.front();

        //-- Get rid of it.
        bfs.pop();

        //-- Is this the goal?
        if (cur.x == goalX && cur.y == goalY) {
            return cur.len;
        }

        //-- Only visit this once.
        if (seen[cur.x][cur.y]) {
            continue;
        }
        seen[cur.x][cur.y] = true;

        //-- Else take a step in each direction. 
        for (int idx = 0; idx < 4; ++idx) {
            
            int multi_step = 1;
            while (true) {

                //-- Get the next indices.
                int nextX = cur.x + (multi_step * dr[idx]);
                int nextY = cur.y + (multi_step * dc[idx]);
                multi_step++;

                //-- Check if we've hit the end of a single step.
                if (nextX < 0 || nextX >= N)   { break; }
                if (nextY < 0 || nextY >= N)   { break; }
                if (grid[nextX][nextY] == 'X') { break; }

                //-- Add this to the search.
                bfs.push(state(nextX, nextY, cur.len+1));
            }
        }
    }

    return -1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string startXStartY_temp;
    getline(cin, startXStartY_temp);

    vector<string> startXStartY = split_string(startXStartY_temp);

    int startX = stoi(startXStartY[0]);

    int startY = stoi(startXStartY[1]);

    int goalX = stoi(startXStartY[2]);

    int goalY = stoi(startXStartY[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

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
