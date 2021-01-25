#include <bits/stdc++.h>

using namespace std;

class UnionFind {
    private: 
        std::vector<int> p, rank, count;

    public:
        UnionFind(int N) { 
            
            rank.assign(N, 0);
            p.assign(N, 0); 
            count.assign(N, 1);
            
            for (int i = 0; i < N; i++) {
                p[i] = i; 
            }
        }

        int findSet(int i) { 
            return (p[i] == i) ? i : (p[i] = findSet(p[i])); 
        }

        int findRank(int i) {
            return rank[findSet(i)];
        }

        int findSize(int i) {
            return count[findSet(i)];
        }

        bool isSameSet(int i, int j) { 
            return findSet(i) == findSet(j); 
        }

        void unionSet(int i, int j) {

            if (!isSameSet(i, j)) {
                // if from different set
                int x = findSet(i), y = findSet(j);
                if (rank[x] > rank[y]) {
                    p[y] = x;
                    count[x] += count[y];
                } else { // rank keeps the tree short
                    p[x] = y;
                    count[y] += count[x];
                    if (rank[x] == rank[y]) rank[y]++;
                }
            } 
        } 
};


// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> queries) {

    int run_max= 0, cur_size, itr=0;
    vector<int> ret;
    map<int,int> hash; 
    UnionFind uf( ((int)2e5) + 1 );

    for (size_t idx = 0; idx < queries.size(); ++idx) {

        int a=queries[idx][0], b=queries[idx][1], x, y;

        //-- Hash the value to something more manageable.
        if (hash.find(a) == hash.end()) {
            hash[a] = itr++;
        } 
        if (hash.find(b) == hash.end()) {
            hash[b] = itr++;
        }

        x = hash[a];
        y = hash[b];

        //-- Create a union between these two vals.
        uf.unionSet(x, y);

        //-- Get the size of their union.
        cur_size = uf.findSize(x);

        //-- Update max if this new union was larger.
        if (cur_size > run_max) {
            run_max = cur_size;
        }
        ret.push_back(run_max);
    }

    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> queries(q);
    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> ans = maxCircle(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
