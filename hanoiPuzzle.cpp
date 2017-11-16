///**********************************************************************************
/// Solution to the Tower of Hanoi using the STL Vector:
/// Author: Erick Ramos
/// Date: October 24, 2017
///***********************************************************************************
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

static vector<int> src, temp, dest;

void show_hanoi() {
    
    cout << "src: "; 
    for (vector<int>::const_iterator i = src.begin(); i != src.end(); i++)
        cout << *i << " ";
    
    cout << " | ";
    cout << "dest: ";
    for (vector<int >::const_iterator i = dest.begin(); i != dest.end(); i++)
        cout << *i << " ";
    
    cout << " | ";
    cout << "temp: ";
    for (vector<int >::const_iterator i = temp.begin(); i != temp.end(); i++)
        cout << *i << " ";
    
    cout << endl;
}

void hanoi(vector<int> &src, vector<int> &dest, vector<int> &temp, long size) {
    if (size > 0) {
        hanoi(src, temp, dest, size - 1);
        
        dest.push_back(src.back());
        src.pop_back();
        
        show_hanoi();
        
        hanoi(temp, dest, src, size - 1);
     }
}

int main() {
    int discs;
    cout << "Enter hanoi tower height: ";
    cin >> discs;
    int moves = discs;

    for (int i = 0; i < discs; i++) {
        src.push_back(moves);
    moves--;
    }

    show_hanoi();
    hanoi(src,dest,temp,discs);
}
