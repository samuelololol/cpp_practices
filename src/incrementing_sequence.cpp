#include <iostream>
#include <algorithm>
#include <vector>

class IncrementingSequence
{
public:
    IncrementingSequence(const int from = 0, const int step = 1)
    :i_(from),
    step_(step)
    {}
    inline int operator() () {
        int tmp = i_;
        i_ += step_;
        return tmp;
    }
private:
    int i_;
    int step_;
};


int main(){
    using std::cout;
    using std::endl;
    using std::vector;

    int fixed_size = 10;
    vector<int> vec(fixed_size);
    std::generate(vec.begin(), vec.end(), IncrementingSequence());
    //std::generate_n(vec.begin(), fixed_size, IncrementingSequence());

    for(vector<int>::const_iterator i = vec.begin();
        i != vec.end();
        ++i){
        cout << *i << " ";
    }
    cout << endl;
    return 0;
}
