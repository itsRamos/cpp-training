//  Recursive function that accepts a string object as its argument and prints the string in reverse order
//  author: Erick Ramos
//  date: January 29, 2018
#include<iostream>
#include<string>

using namespace std;

void reverse(string, int);

int main() {
    string input;
    int size;
    
    cout << "Enter a string: ";
    
    cin >> input;
    size = input.size();
    
    cout << endl << "The reversed is ";
    
    reverse(input, size);
}

void reverse(string input, int size) {
    if(size != -1){
        cout << input[size];
        reverse(input,size - 1);
    }
    //Without recursion
    // while(size != 1){
    //     cout << input[size];
    //     size--;
    // }
}
