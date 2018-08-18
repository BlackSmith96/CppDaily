#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    vector<int> v1 = {1,2,3,4,5}, v2 = {1,2,3,4,5};
    cout << (v1 == v2) << endl;
    return 0;
}