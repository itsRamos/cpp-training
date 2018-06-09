#include <bits/stdc++.h>
using namespace std;
void getInput(string &input);
bool TRACE=true;

class Node {
public:
	int	 freq;
	char val;
	string code;
	Node *left, *right;
	Node():left(nullptr), right(nullptr), freq(0), val('_'){} };

class Huffman {
	class cmp {
		public: bool operator() (const Node* a, const Node* b) const 
		{ return  a->freq > b->freq; } };

	Node* root=nullptr;
	priority_queue<Node*, vector<Node*>, cmp> Q;
	vector<Node> list;

public:
	Huffman(){}

	void add( int freq, char val ) {
		Node* node = new Node();
		node->freq = freq;
		node->val =val;
		Q.push(node);
	}
		
	void build() {
        while (Q.size() > 1) {
            Node* first = Q.top(); Q.pop();
            Node* second = Q.top(); Q.pop();
            Node* tmp = new Node();
            tmp->val = '_';
            tmp->freq = first->freq + second->freq;
            tmp->left = first;
            tmp->right = second;
            if(TRACE) { root=tmp; draw(); }
            Q.push(tmp);
		}
		root=Q.top();
	}
	void show() {
		if(!root) return;
		show(root, "");
	}
	void show(Node* node, string coding) {
		if (!node)  return;
		if (node->val != '_') {
			Node tmp;
			tmp.val = node->val;
			tmp.freq = node->freq;
			node->code = tmp.code = coding;
			list.push_back(tmp);
			cout << node->val <<" " << node->freq <<" "<< tmp.code << endl;
			return;
		}
		show(node->left, coding + "0");
		show(node->right, coding + "1");
	}
	void draw() const {
		if(!root) return;
		cout << endl;
		draw(root, " ", " ", "");
		cout << endl;
	}
	void draw(Node* treePtr, string lpad, string rpad, string coding) const {
        string pad = lpad.substr(0, lpad.size() - 1);
        if (treePtr == nullptr)	return;
        draw(treePtr->right, rpad + "    |", rpad + "     ", coding + "1");
        cout << pad << "+--" << setw(3) << treePtr->freq << treePtr->val << coding << endl;
        draw(treePtr->left, lpad + "     ", lpad + "    |", coding + "0");
    }
};

int main () {
    string input;
    getInput(input);
    
    map<char, int> freq;
    
    for(auto key:input){
        if (!freq[key]) freq[key] = 1;
        else freq[key]++;
    }
    // cout << "Enter a text string: "; // the ai is hot, iot is not, iota is   
    // getline(cin, input);
  
    // map<char, int> freq = { {'A', 2}, {'E', 1}, {'H', 2}, {'I', 6}, 
    // 						{'N', 1}, {'O', 4}, {'S', 3}, {'T', 5} };
    // map<char,int>freq={{'a',3},{'b',2},{'c',1},{'d',4}};
    // Instead you can process the input words here 
        
	Huffman H;
	multimap<int, char, std::less<int>> Occur;
    for (auto ch:freq) {
        Occur.insert(pair<int, char>(ch.second, ch.first));
    	H.add( ch.second, ch.first ); }
    	
    for (auto i:Occur)
        cout << "[" << i.first << "]->" << i.second << endl;
    
	H.build();
	H.show();
	return 0;
}

void getInput(string &input){
    cout << "Enter a series of key press, no space: ";
    getline(cin, input);
}
