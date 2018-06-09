#include <string>
#include "sha256.h"
#include "Blockchain.h"
#include "Merkle.h"
#include <iostream>
#include <vector>

using namespace std;
 
int main() {
	vector<BlockData> txList = { // 9 transactions
    {"Satoshi", "Donald","$1,000,000.00"},
    {"Donald", "Brad", "$200,000.00"},
    {"Brad", "Charlie", "$123,456.78"},
    {"Charlie", "Cohen", "$56,789.87"},
    {"Brad", "EC LLC", "$6,543.21"},
    {"EC LLC", "Cohen", "$76,543.21"},
    {"Ronald", "Fred", "$20,000.00"},
    {"Chad", "Charlie", "$33,00.00"},
    {"Charlie", "Ronald", "33,00.00"}
};
    vector<string> txHashVec;
    string txHash, blockData;
    
    Blockchain chain = Blockchain();
 
    for( auto x:txList ) { 
        txHash = sha256::hash256_hex_string(x.getData());
        blockData += "\ttxHash: " + txHash +"\n" + x.getData() ;
        txHashVec.push_back(txHash);
        if (txHashVec.size() == 3) {
            x.getData() = merkle(txHashVec);
            x.data = blockData;
            chain.AddBlock(x);
            txHashVec.clear();
            blockData.clear();
        }
    }

}
