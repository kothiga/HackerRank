#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the runningMedian function below.
 */
vector<double> runningMedian(vector<int> a) {
    
    priority_queue<int> max_heap;
    priority_queue<int, std::vector<int>, std::greater<int> > min_heap;
    vector<double> ret(a.size(), 0);

    //-- Do some initializing.
    ret[0] = a[0];
    if (a.size() == 1) {
        return ret;
    }

    //-- Two or more elements.
    if (a[0] > a[1]) {
        min_heap.push(a[0]);
        max_heap.push(a[1]);
    } else {
        min_heap.push(a[1]);
        max_heap.push(a[0]);
    }

    //-- Add this to the return list.
    ret[1] = (double)(max_heap.top() + min_heap.top()) / 2.0;


    //-- Now that both heaps have elements,
    //-- don't need to worry about accessing
    //-- elements of an empty heap.
    for (size_t idx = 2; idx < a.size(); ++idx) {

        //-- Get the next item.
        int cur = a[idx];

        if (max_heap.size() == min_heap.size()) {
            
            //-- Does the current element go left or right?
            if (cur < min_heap.top()) { 
            
                //left insert.
                max_heap.push( cur );
            
            } else { //cur >= max_heap.top()
             
                //rebalance.
                max_heap.push( min_heap.top() );
                min_heap.pop();

                //right insert.
                min_heap.push( cur );

            }

        } else { // max_heap.size() > min_heap.size()

            if (cur >= max_heap.top()) {

                //right insert.
                min_heap.push( cur );

            } else {

                //rebalance.
                min_heap.push( max_heap.top() );
                max_heap.pop();

                //left insert.
                max_heap.push( cur );

            }
        }

        //-- Get the median.
        double val;
        if (max_heap.size() > min_heap.size()) {
            val = (double) max_heap.top();
        } else {
            val = (double)(max_heap.top() + min_heap.top()) / 2.0;
        }

        ret[idx] = val;
    }

    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
