#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    vector<string> lst;
    string word;
    auto iter = lst.begin();
    for(int i=0;i < 4;++i){
        cin >> word;
        lst.insert(iter, word);
    }
    cout << "zzz" << endl;
    for(auto s:lst)
        cout << s << endl;
    return 0;
}