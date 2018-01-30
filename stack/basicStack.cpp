#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> mystack;
    
    for(int i = 0; i < 5; ++i){
        mystack.push_back(i);
    }
    
    cout << "Displaying elements...";
    
    while(!mystack.empty()) {
        cout << ' ' << mystack.back();
        mystack.pop_back();
    }
    
    cout << endl;
    
    return 0;
}
