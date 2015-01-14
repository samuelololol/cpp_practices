#include <iostream>
#include <vector>
#include <cstring>

int main(){
    using std::cout;
    using std::endl;
    using std::vector;
    using std::memcpy;

    int a[] = {1,2,3,4,5,6,7,8,9,10};
    unsigned a_size = sizeof(a) / sizeof(int);
    vector<int> va;

    // method 1: copy
    // 1. easy to understand
    // 2. slow
    // -----------------------------------------------------------------------
    //copy(&a[0], &a[a_size], back_inserter(va));

    // method 2: reserve
    // 1. performance improvement to method 1, for larget arrays this _might_ 
    //    help.
    // 2. But never to use reserve unless profiling suggests you may be able to
    //    get an improvement
    // 3. But actually, method 2 proformed the slowest!
    // -----------------------------------------------------------------------
    //va.reserve(va.size() + a_size);
    //copy(&a[0], &a[a_size], back_inserter(va));

    // method 3: resize and memcpy
    // 1. old school solution
    // 2. tricky but never to use
    // -----------------------------------------------------------------------
    //va.resize(va.size() + a_size);
    //memcpy(&va[va.size() - a_size], &a[0], a_size * sizeof(int));

    // method 4: insert
    // 1. is the best way to go!
    // 2. it's meaning is clear, usually the fastest and works for any objects
    // -----------------------------------------------------------------------
    //va.insert(va.end(), &a[0], &a[a_size]);
    
    // method 5: vector + vector
    // 1. a tweak on method 4
    // 2. if a vector exists, use this, if the case is creating a vector from
    //    array, just initialize it
    // -----------------------------------------------------------------------
    vector<int> va2(&a[0], &a[a_size]);
    va.insert(va.end(), va2.begin(), va2.end());

    for(vector<int>::const_iterator i=va.begin();
        i!=va.end();
        ++i){
        cout << *i << " ";
    }
    cout << endl;
    return 0;
}


// reference from: http://stackoverflow.com/a/261607
