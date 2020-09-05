
#include <pretty_print.h>

#include <unordered_map>


struct TEMP {


};



int main() {
    auto umap = std::unordered_map<int,int>{
            {1,2},
            {2,3},
            {3,4},
            {4,5},
            {5,6},
    };
    pretty::print(umap);
    return 0;
}
