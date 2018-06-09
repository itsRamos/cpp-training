#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	string ORIGINAL("The Original!");
	string MIRRORED("MIRRORED");
	string ROTATION("ROTATION");
	stringstream ss;
	// int counter;
	bool isMirrored = false;
	
	// Add an original solution to solutions file
	// int size = 6; vector<int> position = {4,2,0,5,3,1};
	int size = 5; 
	vector<int> position = {0,2,4,1,3};
	vector<int> temp = position;
	map<string, string>  solutions;
	ss.str(""); ss.clear(); // empty and clear flags
	
	for (int i = 0; i < size; i++) ss << position[i];
	cout <<  "m[" << ss.str() << "] = " << ORIGINAL << endl;;
	
	isMirrored = false;

// 	Solution: P(x) = 0 2 4 1 3 
//      y
//      ^ 
// 		*|0|1|2|3|4|*P(y)
// 		4|_|_|X|_|_|   2
// 		3|_|_|_|_|X|   4
// 		2|_|X|_|_|_|   1
// 		1|_|_|_|X|_|   3
// 		0|X|_|_|_|_|   0
// 		*|0|1|2|3|4|* > x
// 	P(x)= 0 2 4 1 3
//  P(y)= 0 3 1 4 2

		
// 	The above posision can be represented as a 2-D or 1-D vector:
// 	vector<ini,int> position { {0,0}, {1,2}, {2,4}, {3,1}, {4,3} };
// 	vector<int> P(x') = {0,2,4,1,3}, P'(N-x') = {3,1,4,2,0};
// 	vector<int> P(y') = {0,3,1,4,2}; P'(N-y') = {2,4,1,3,0};

// pos' ---LR---> pos, i.e. p()
// x = y'; y = N-x';
//                                                       y': 4-3-2-1-0
//	   x': 0-1-2-3-4	     y': 0-1-2-3-4		          x: 0-1-2-3-4
//  P(x'): 0,2,4,1,3 -tr->P(y'): 0,3,1,4,2 ->reverse-> P(x): 3,1,4,2,0
//  ( x': start w/0)	(y=N-x': start w/4)

// pos'  ---RR--->   pos // pos' as prev pos, i.e. p()
// y = x'; x = N-y'; ditto

// Here is a rotation:
    vector<int> next;
    ss.str(""); ss.clear();
    for(int y=size-1; y>=0; y-- ) {
        for(int x = 0; x<size; x++) {
            if(position[x] == y) {
                ss << x;
                next.push_back(x);
                break;
            }
        }
    }
    cout << "m[" << ss.str() << "] = " << ROTATION << endl;
	position = next;
	
	// To mirror by reversing the index
	vector<int> mirror;
	ss.str(""); ss.clear();
	for( int i=size-1; i>=0; i--) {
	   mirror.push_back(temp[i]);
	   ss << temp[i]; 
	}
	cout << "m[" << ss.str() << "] = " << MIRRORED << endl;

}
