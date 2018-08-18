#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    list<int> l{1,2,3,4};
    vector<int> v{1,2,3,5};
    vector<int> t;
    t.assign(l.begin(),l.end());
    cout << (v == t?"true":"false") << endl;
    return 0;
}