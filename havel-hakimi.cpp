#include <iostream>
#include <deque>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

bool havel_hakimi(deque<int> degreeSequence) {
    //Sort the input into non-increasing order.
    sort(degreeSequence.begin(), degreeSequence.end(), greater<int>());

    //If there is a element with a value greater than the number of elements, return false.
    //Since the container is sorted, we only need to inspect the first element.
    if (degreeSequence.front() >= degreeSequence.size())
        return false;
    
    //If there is a negative element, return false.
    //Since the container is sorted, we only need to inspect the last element.
    if (degreeSequence.back() < 0)
        return false;
    
    //If the container has all 0s, return true.
    //Since the container is sorted and there is no negative values, we only need to inspect the first element.
    if (!degreeSequence.front())
        return true;
    
    int sum = accumulate(degreeSequence.begin(), degreeSequence.end(), 0);
    
    //If the sum of the elements is odd, return false.
    if (sum % 2)
        return false;

    //Remove the element from the front, decrement the first "front" number of values.
    int front = degreeSequence.front();
    degreeSequence.pop_front();
    for (int i = 0; i < front; ++i)
        --degreeSequence[i];

    //Recursive call
    return havel_hakimi(move(degreeSequence));
}

int main() {
    cout << "Enter a space-separated degree sequence.\n";
    string input;
    getline(cin, input);
    int temp;
    deque<int> degreeSequence;
    istringstream iss(input);
    while (iss >> temp)
        degreeSequence.push_back(temp);
    cout << "There ";
    cout << (havel_hakimi(degreeSequence) ? "exists " : "does not exist ");    
    cout << "a simple graph with the degree sequence [";
    for (auto it = degreeSequence.begin(); it != degreeSequence.end() - 1; ++it)
        cout << *it << ", ";
    cout << *(degreeSequence.end() - 1) << "].\n";
    return 0;
}
