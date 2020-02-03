#include <algorithm>
#include <iterator>
#include <vector>   
#include <iostream>

int solution(std::vector<int> &v) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::nth_element(v.begin()+i, v.begin()+i, v.end());
        if (v[i] != i+1) return i+1;
    }
    return v.size()+1;
}

int solution_2(std::vector<int> &v) {
    sort(v.begin(), v.end());
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (v[i] != i+1) return i+1;
    }
    return v.size()+1;
}

int solution_3(std::vector<int> &v) {
    sort(v.begin(), v.end());
    auto missing_element = std::find_if( 
        v.begin(), v.end(), 
        [index=1](auto& element) mutable { 
            if (element != index++) {
                return true;
            } else {
                return false;
            }
        });
    if (missing_element == v.end()) {
        return v.size() + 1;
    } else {
        return *missing_element - 1;
    }
}


int main(int argc, char** argv) {
    auto v = std::vector<int>{1,3,5,2};
    std::cout << solution_3(v);
}
