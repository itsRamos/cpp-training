// Rabbit population as a fibonaci sequence
// author: Erick Ramos
// date: January 29, 2018

#include <iostream>

using namespace std;

int rabbit(int);

int main() {
    int input;
    cout << "Enter number of months: ";
    cin >> input;
    cout << "Number of rabbits: " << rabbit(input);
}

int rabbit(int n) {
    // original math expression
    // rabbit(n) = 1 // if n is 1 or 2
    // rabbit(n) = rabbit(n-1) + rabbit(n-2) // if n > 2
    
    int rab;
    
    if(n <= 2) {
        rab = 1;
    }
    else {
       rab = rabbit(n - 1) + rabbit(n - 2); 
    }
    
    return rab;
}
