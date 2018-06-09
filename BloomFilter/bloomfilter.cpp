#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;
using HashFunction = function<unsigned int(string const&)>;

class BloomFilter {
    unsigned int numberOfCells;
    bool *cell;
    vector<HashFunction> hashFunctions;

public:
    BloomFilter(unsigned int n, vector<HashFunction> const &f) : numberOfCells(n), hashFunctions(f) {
        cell = new bool[n]();
    }
    ~BloomFilter() {
        free(cell);
        cell = nullptr;
    }
    
    void addX(string const& str) {
        for(auto x:hashFunctions)
            cell[(x)(str) % numberOfCells] = true;
    }
    
    bool searchX(string const &str) {
        bool strInSet = true;
        for(auto x:hashFunctions) {
            if(cell[(x)(str) % numberOfCells] == false) {
                strInSet = false;
                break;
            }
        }
        return strInSet;
    }
};

unsigned int djb2(string str) {
    unsigned int hash = 5381;
    for(auto x:str)
        hash = ((hash << 5) + hash) + x;
    return hash;
}

unsigned int sdbm(string str) {
    unsigned int hash = 0;
    for(auto x:str)
        hash = x + (hash << 6) + (hash << 16) - hash;
    return hash;
}

unsigned int fnv(string str) {
    unsigned int hash = 2166136261;
    for(auto x:str)
        hash = (hash * 16777619) ^ x;
    return hash;
}

unsigned int sax(string str) {
    unsigned int h = 0;
    for(auto x:str)
        h ^= (h << 5) + (h >> 2) + x;
    return h;
}

unsigned int elf(string str) {
    unsigned h = 0, g;
    for(auto x:str) {
        h = (h << 4) + x;
        g = h & 0xf0000000L;
        if (g != 0) h ^= g >> 24;
        h &= ~g;
    }
    return h;
}

unsigned int loselose(string str) {
	unsigned int hash = 0;
	for(auto x:str)
	    hash += x;
	return hash;
}

unsigned int xorh(string str)
{
    unsigned int hash = 0;
    for(auto x:str)
        hash ^= x;
    return hash;
        
}

unsigned oat(string str)
{
    unsigned int hash = 0;
    for(auto x:str) {
        hash += x;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

unsigned rot(string str)
{
    unsigned int h = 0;
    for (auto x:str)
        h = (h << 4) ^ (h >> 28) ^ x;

    return h;
}

unsigned djb(string str)
{
    unsigned int h = 0;
    for (auto x:str){
        h = 33 * h + x;
    }
    return h;
}

int main() {
    vector<HashFunction> hashFunctions;
    // hashFunctions.push_back(djb2);
    // hashFunctions.push_back(sdbm);
    // hashFunctions.push_back(fnv);
    // hashFunctions.push_back(sax);
    // hashFunctions.push_back(elf);
    // hashFunctions.push_back(loselose);
    // hashFunctions.push_back(xorh);
    // hashFunctions.push_back(oat);
    hashFunctions.push_back(rot);
    hashFunctions.push_back(djb);
    BloomFilter bf(1024, hashFunctions);
    
    cout << "Building a Bloom Filter to censor the following words:\n";
    
    unordered_set<string> censors ( {
       "armed", "cruel", "cruelty", "hate", "oppressions", "troops", "tupple" 
    });
    
    for(auto x:censors) {
        bf.addX(x);
        cout << "\t" << x << endl;
    }
    cout << "Run the article 'Independent Declaration' through the filter.\n";
    
    ifstream file;
    // file.open("DeclarationOfIndependence.txt");
    file.open("gettysburg-address.txt");
    if(file.fail()) {
        cout<<"\n\n ERROR - file not found...\n"; exit(1);
    }
    
    string line, word;
    vector<string> inputWords;
    
    cout << "Red flags:\n";
	int true_pos=0, false_pos=0;
	while(!file.eof()) {
	    while (getline(file, line)) {
            stringstream ss(line);
            while (ss >> word) {
                word.erase(std::remove_if(word.begin(), word.end(), 
                        [](char& c){return !isalnum(c);}), word.end());
                if (word != "") {
                    
                    for(auto &x:word) x = tolower(x);
                    inputWords.push_back(word);
                                // pv.push_back(v);
                    	for(int i = 0; i < inputWords.size() - 1; i++) {
                        	if(word == inputWords[i]) {
                        		inputWords.pop_back();
                        		break;
                        	}
                    	}
                    if(bf.searchX(word)) { // all positive cases
                        if(censors.find(word) != censors.end()) 
                            {cout << word << " X\n"; true_pos++; }
                        else 
                            {cout << word << endl; false_pos++; }
                    }}}}}
    cout << censors.size() <<" out of " << inputWords.size() << endl;
    cout << true_pos << " true positives\n" << false_pos << " false positives\n";
}
