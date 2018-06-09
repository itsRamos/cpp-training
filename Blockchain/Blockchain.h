#ifndef _BLOCKCHAIN_H
#define _BLOCKCHAIN_H
#include <vector>
#include <iomanip>
#include <string>
#include <iostream>
#include "sha256.h"
#include "Merkle.h"

using namespace std;

struct BlockData {
    string from, to, data;
    BlockData() : from("n/a"), to("n/a"), data("Satoshi - the Creator") { }
	BlockData(std::string from, std::string to, std::string data)
		: from(from), to(to), data(data) { }
	~BlockData() {}
	string getData() 
	    { return "\tfrom: " + from + "\n\tto: " + to + "\n\tdata: " + data + "\n"; }
	void PrintData() { std::cout << getData(); }
};

class Block {
	int index;
	int nounce;
	std::time_t timestamp;
	BlockData data; // trasaction record
	std::string merkle_hash;
	std::string previous;
public:
    Block() {}
    Block(int index, BlockData data, std::string previous);
    ~Block() {}
    string toString();
    std::time_t getTimestamp() { return timestamp; }
    BlockData* getData() { return &data; }
    string getHash() { return merkle_hash; }
};

Block::Block(int index, BlockData data, std::string p=""):
    index(index), data(data), timestamp(std::time(nullptr)), previous(p)
{
    nounce = 0;
	do {
		merkle_hash = sha256::hash256_hex_string(
			std::to_string(index) +
			std::to_string(timestamp) +
			data.getData() +
			// merkle(data) +
			previous + 
			std::to_string(nounce++)
		);
// 		std::cout << merkle_hash.substr(0,1) << std::endl;
		// std::cout << hash<< std::endl;
	} while( merkle_hash.substr(0,1) != "0" );
}

string Block::toString() {
	return std::to_string(index) + "\n" +
	   "nounce: " + std::to_string(nounce) + "\n" +
	   "previous: " + previous + "\n" +
	   "timestamp: " + std::asctime(std::gmtime(&timestamp)) + 
	   "data: {\n" + data.getData() + "}\n" +
	   "merkle hash: " + merkle_hash + "\n";
}


class Blockchain {
	std::vector<Block> blocks;
	Block* current;
public:
	Blockchain() {
		blocks.push_back(Block(0, BlockData(), ""));
		current = &(blocks[0]);
	}
	~Blockchain() {}
	void AddBlock(BlockData data);
};

void Blockchain::AddBlock(BlockData data) {
    blocks.push_back( Block(blocks.size(), data, current->getHash() ));
    current = &(blocks.back());
    cout << "Added Block: " << current->toString() << endl;
}
#endif
