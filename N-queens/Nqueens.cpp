
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

template<typename A, typename B>
pair<B,A> flip_pair(const pair<A,B> &p) {
	return pair<B,A>(p.second, p.first);
}

void outputBoard(vector<int>, int);
bool isSafe(int queen_number, int row_position, vector<int> position);
void solve(int k, int N, vector<int>& position);
void rotateLeft(vector<int> position, int size, map<string, string>& solutions, int counter, bool isMirrored);
void uniqueSolve(int k, int N, vector<int>& position, map<string, string>& solutions, int& counter);


const string MIRRORED = "MIRRORED";

int main() {
    int size = 8; // start up default to standard checker board size
	// The following 7 lines of code are to test the outputBoard()
	// You may choose to comment out in your submitted n_queens.cpp
	vector<int> queen8 = { 0, 4, 7, 5, 2, 6, 1, 3 };
	vector<int> queen14 = { 0, 2, 4, 6, 11, 9, 12, 3, 13, 8, 1, 5, 7, 10 };
	
	outputBoard(queen8, size);
	cout << "\nOne possible 14-Queens solution:\n";
	size = 14;
	outputBoard(queen14, size);
	
		// end of outputBoard() test
	auto menu=[]() {
	cout << "==== N-Queen Test Menu ===="
		<< "\n\tS-Checker Board Size"
		<< "\n\tD-Display solutions"
		<< "\n\tU-Display Unique solutions"
		<< "\n\tQ-Quit"
		<< "\n\tEnter your Choice: "; 
	};
	
	string choice;
	
	while(true) {
	    menu();
		cin >> choice; cin.ignore(1000,10);
		
		switch(choice[0]) {
		case 's': // change size
		case 'S':
			cout << "\nEnter Size of checker board: ";
			cin >> size;
			cin.ignore(1000, 10);
			cout << endl;
			if (size != 1 && size < 4) {
				cout << "SIZE OF BOARD MUST BE 1 OR GREATER THAN OR EQUAL TO 4\n\n";
				break;
			}
			break;

		case 'd': // display all solutions
		case 'D':
		{
			cout << "\n...........   SOLUTIONS   ...........\n\n";
			vector<int> position(size);
			solve(0, size, position);

		}
			break;

		case 'u': // display only the unique solutions
		case 'U':
		{
			cout << "\n...........UNIQUE SOLUTIONS...........\n\n";
			vector<int> position(size);
			int counter = 0;
			map<string, string> solutions;
			uniqueSolve(0,size,position,solutions,counter);
			cout << counter << " Unique Solutions.\n\n";
			for (map<string,string>::iterator it=solutions.begin(); it!=solutions.end(); ++it)
        	cout << "m[" << it->first << "]" << " => " << it->second << "  " << endl;
			
		}
			break;

		case 'q':
		case 'Q':
			return 0;
			break;

		default:
			cout << "Invalid Entry\n";
			break;
		}
		
	}
	return 0;
}

/*
 * precondition: input the n-queens\' solution array and its size
 * postcondition: output the checker board
 */
void outputBoard(vector<int> ar, int size) {
	int i, j;
	cout << "*|";
	for (i = 0; i < size; i++) cout << (i % 10) << "|";
	cout << "*\n";
	for (i = 0; i < size; i++) {
		cout << (i % 10) << "|";
		for (j = 0; j < size; j++)
    		if (j == ar[i]) cout << "X" << "|";
    		else cout << "_|";
		cout << (i % 10) << endl;
	}
	cout << "*|";
	for (i = 0; i < size; i++) cout << (i % 10) << "|";
	cout << "*\n\n";
}

// Recursively generate a tuple like [0 0 0 0], then [0 0 0 1] then etc...
void solve(int k, int N, vector<int>& position) { 
    // k-th column/queen to N queens' solution with the current "position"
    static int count = 0;
	if (k == N) // We placed N-1 queens (0 included), problem solved!
	{
		// Solution found!
		count++;
		cout << "Solution: ";
		for (int i = 0; i < N; i++)
			cout << position[i] << " ";
		cout << endl;
		outputBoard(position, N);
	}
	else
	{
		for (int i = 0; i < N; i++) // Generate ALL combinations
		{
			// Before putting a queen (the k-th queen) into a row, test it for safeness
			if (isSafe(k, i, position))
			{
				position[k] = i;
				// To Solve unique postiont[i] = k; plance new queen on k+1
				solve(k + 1, N, position);
			}
		}
	}
// 	return count;
}

bool isSafe(int queen_number, int row_position, vector<int> position)
{
	// Check each queen before this one
	for (int i = 0; i < queen_number; i++)
	{
		// Get another queen's row_position
		int other_row_pos = position[i];

		// Now check if they're in the same row or diagonals
		if (other_row_pos == row_position || // Same row
			other_row_pos == row_position - (queen_number - i) || // Same diagonal
			other_row_pos == row_position + (queen_number - i))   // Same diagonal
			return false;
	}
	return true;
}



// Solve with details of position attributes
// Checks for Unique solutions and stores them in solutions map along with output
void uniqueSolve(int k, int N, vector<int>& position, map<string, string>& solutions, int& counter)
{
	if (k == N) { // When the N-1th (0 based) queen is placed, problem solved!
		stringstream ss;
		for (int i = 0; i < N; i++) 
			ss << position[i];
		if (solutions.count(ss.str()) == 0) { // found a new position
			counter++;
			stringstream output;
			// add as a Unique solution
			output << " #" 
				<< counter << " Unique Solution";
			solutions[ss.str()] = output.str();

            // find all duplicates
			// rotate left 3 times to add more solutions, if any
            rotateLeft(position, N, solutions, counter, false);

            // Reverse the array to mirror the board
            vector<int> mirror;
			for( int i=position.size()-1; i>=0; i--) {
			  mirror.push_back(position[i]);
			}

			rotateLeft(mirror, N, solutions, counter, true);
	
			// Reverse the array to mirror the board
			vector<int> temp; // place the mirror into temp
			for( int i=mirror.size()-1; i>=0; i--) {
			  temp.push_back(mirror[i]);
			}
            // rotate left again to add more solutions
			rotateLeft(temp, N, solutions, counter, true);
		}
	} else {
		for (int i = 0; i < N; i++) { 
		    // Generate ALL combinations ... the backtracking
			// Before putting a queen (the k-th queen) into a row, 
			// test it for safeness
			if (isSafe(k, i, position)) {
				position[k] = i;
				uniqueSolve(k + 1, N, position, solutions, counter);
			}
		}
	}
}

// counter is what solution we are on and isMirrored tells us if we are outpuing a mirrored solution
void rotateLeft(vector<int> position, int size, map<string, string>& solutions, int counter, bool isMirrored)
{
	for (int rt = 0; rt < 3; rt ++) { 	// Rotate 3 times
		stringstream ss;
		vector<int> next;
		ss.str(""); ss.clear();
		// The left rotation formula: y' = x; y = N-x';
		for (int y = size - 1; y >= 0; y--) {
			for(int x = 0; x < size; x++) {
				if(position[x] == y) {
					ss << x;
					next.push_back(x);
					break;
				}
			}

		}
		if (solutions.count(ss.str()) == 0) {
			// Add output Lable for solution
			stringstream output;
			output << " #" 
				<< counter << (isMirrored ? " Mirrored +" : "") << " Rotated " 
				<< (rt == 0 ? " 90° " : rt == 1 ? "180° " : rt == 2 ? "270° " : "360° ");
			solutions[ss.str()] = output.str();
		}
		position = next;
	}
}
