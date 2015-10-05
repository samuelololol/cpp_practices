#include <iostream>
#include <utility>
#include <vector>

typedef std::pair<int, int> tuple;

int main(){
    using std::cout;
    using std::endl;
    using std::vector;
    using std::pair;
    using std::make_pair;

    int a[] = {1,2,3,4,5,6,7,8,9,10};
    unsigned a_size = sizeof(a) / sizeof(int);
    vector<tuple> vt;
    for (unsigned i = 0; i < a_size; ++i)
        vt.insert(vt.end(), make_pair(i, a[i]));
    for (std::vector<tuple>::const_iterator i = vt.begin(); i != vt.end(); ++i){
        cout << "(" << i->first << ", " << i->second << ")";
        cout << endl;
    }
    return 0;
}
