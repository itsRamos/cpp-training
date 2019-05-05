#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Frac;
ostream &operator << (ostream&, const Frac&);

class Frac {
    private:
    long num;
    long den;
    
    public:
    Frac() {
        num = 0; den = 1;
    };
    
    Frac(long n) {
        num = n; den =1;
    };
    
    Frac(long n, long d) {
        num = n;
        den = d;
    };
    
    Frac(const Frac &x) {
        num = x.num;
        den = x.den;
    };
    
    Frac(string s) {
        stringstream stream(s);
        stream >> num;
        char peekchar = stream.peek();
        if(stream && peekchar == '/') {
            stream.get();
            stream >> den;
        }
        else den = 1;
    }
    
    Frac &operator = (const Frac &x) {
        num = x.num;
        den = x.den;
    };
    
    Frac operator + (const Frac &x) {
        Frac temp;
        temp.num = num * x.den + x.num * den;
        temp.den = den * x.den;
        return temp;
    };
    
    Frac operator / (const Frac &x) {
        Frac temp;
        temp.num = num * x.den;
        temp.den = den * x.num;
        return temp;
    };
    
    bool operator > (const Frac &x) {
        return (num * x.den > den * x.num) ? true :  false;
    }
    
    operator double() {
        return double(num /den);
    }
    
    bool operator == (Frac &f2) {
        return (double(*this) == double(f2));
    }
    
    Frac operator ++ () {
        num += den;
        return *this;
    }
    
    Frac operator ++ (int) {
        Frac temp(*this);
        num += den;
        return temp;
    }
    
    Frac operator -- () {
        num -= den;
        return *this;
    }
    
    Frac operator -- (int) {
        Frac temp(*this);
        num -= den;
        return temp;
    }
    
    void show() {
        cout << num << "/" << den;
    }
    
    friend ostream &operator << (ostream &strm, const Frac &right){
        strm << right.num << "/" << right.den;
        return strm;
    }
    
    string toString() {
        return to_string(num) + "/" + to_string(den);
    }
    
};

int main() {
    Frac x(3,4);
    cout << "Create x: ";
    x.show();
    
    Frac y(2,3);
    cout << endl << "Create y: ";
    y.show();
    
    Frac z(x);
    cout << endl << "Create z from x: ";
    z.show();
    
    z = y;
    cout << endl << "Assign y to z: ";
    z.show();
    
    cout << endl << "x + y: " << x << " + " << y << " = " << x + y;
    cout << endl << "x / y" << x << " / " << y << " = " << x / y << endl;
    cout << x << " is " << ((x > y) ? "" : "not ") << "greater than " << y << endl;
    cout << y << " is " << ((y > x) ? "" : "not ") << "greater than " << x;

    // using method 3 toString()
    cout << endl << "x: " << x.toString() << endl << "y: " << y.toString() << endl;
    
    Frac a("1/2"); // string constructor
    Frac b("2/4");
    cout << "\na: " << a.toString() << "\nb: " << b.toString() << endl;
    
    // verify the comparism operators
    cout << a << " is " << ((a==b) ? "":"not ") << "equal to " << b;
    
    // verify the inc/decrement operators
    cout << "\nStep by Stp inc/dereament a: " << a << ", ";
    cout << a++ << ", ";
    cout << a++ << ", ";
    cout << a-- << ", ";
    cout << a-- << ", ";
    cout << a;
    cout << "\nContinuous  inc/decrement a: "
         << a << ", " << a++ << ", " << a++ << ", "
         << a-- << ", " << a-- << ", " << a << endl;
}
