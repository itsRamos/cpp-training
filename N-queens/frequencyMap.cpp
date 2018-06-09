#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

template<typename A, typename B>
pair<B,A> flip_pair(const pair<A,B> &p) {
	return pair<B,A>(p.second, p.first);
}
int main() {
    string input;
    cout << "Enter a text string, no spaces: ";
    cin >> input;
    map<char,int> frequencyMap;
    map<char,int>::iterator it;
    for(int i=0; i<input.length(); i++) {
        char ch = input.at(i);
        it = frequencyMap.find(ch);
        if( it==frequencyMap.end() )
            frequencyMap.insert(make_pair(ch, 1));
        else
            it->second++;
    }
    cout << "The frequency table\n";
    for( it = frequencyMap.begin(); it!=frequencyMap.end(); ++it ) {
        cout << "[" << it->first << "]->" << it->second << endl;
    }
    // flip the map
    multimap<int, char> flipMap;
    multimap<int, char>::iterator iter;
    transform(frequencyMap.begin(), frequencyMap.end(),
              inserter(flipMap, flipMap.begin()),
              flip_pair<int,char>);
    cout << "\nThe occurance table\n";
    for( iter=flipMap.begin(); iter!= flipMap.end(); ++iter ) {
        cout << "[" << iter->first << "]->" << iter->second << endl;
    }
}
