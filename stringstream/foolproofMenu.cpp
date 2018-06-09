#include <iostream>
#include <sstream> // stringstream
#include <string>
 
using namespace std;

void menu() {
    cout << "________Fool_Proof_Menu_________\n"
         << "   1 - Enter a line of text\n"
         << "   2 - Enter a word of text\n"
         << "   3 - Enter an integer number\n"
         << "   4 - Enter a floating point number\n"
         << "   q - quit\n"
         << "   Enter your choice: ";
}

int main() 
{
    int i;
    double d;
    string input, choice, text;
    bool stay = true;
    while(stay) 
    {
        menu();

        cin>> choice;
        cin.ignore(1000, 10);
        
        if(choice.size() == 1 ) {
            char ch = choice[0];
            switch(ch) {
                case '1': // line of text 
                {
                    cout << "   Enter a line of text: ";
                    while(true) {
                        getline(cin, input); 
                        stringstream ss(input);
                        text = ss.str();
                        if(!ss.fail()) break;
                        cout << "   Error in converting the string you entered. \n   Try again:";
                    }
                    cout << "\t" << text << endl << endl;
                    break;
                }
                case '2': // one word
                {
                    cout << "   Enter a word of text: ";
                    while(true) {
                        getline(cin, input); // delimiter
                        //cin.ignore(1000, 10);
                        stringstream ss(input);
                        ss >> text;
                        if(!ss.fail()) break;
                        cout << "   Error in converting the string you entered. \n   Try again:";
                    }
                    cout << "\t" << text << endl << endl;
                    break;
                }
                
                case '3': // integer
                {
                    cout << "   Enter an integer: ";
                    while(true) {
                        getline(cin, input);
                        stringstream ss(input);
                        ss >> i;
                        if(!ss.fail()) break; //it is an integer!
                        cout << "   Error in converting the string you entered. \n   Try again:";
                    }
                    cout << "\t" << i << endl << endl;
                    break;
                }
                
                case '4': // floating number
                {
                    cout << "   Enter a floating number: ";
                    while(true) {
                        getline(cin, input);
                        stringstream ss(input);
                        ss >> d;
                        if(!ss.fail()) break; //it is an integer!
                        cout << "   Error in converting the string you entered. \n   Try again:";
                    }
                    cout << "\t" << d << endl << endl;
                    break;
                }
                
                case '5': // one word
                // {
                //     cout << "   Enter a word of text: ";
                //     while(true) {
                //         getline(cin, input, ' '); // delimiter
                //         // cin.ignore(1000, 10);
                //         stringstream ss(input);
                //         text = ss.str();
                //         if(!ss.fail()) break;
                //         cout << "   Error in converting the string you entered. \n   Try again:";
                //     }
                //     cout << "\t" << text << endl << endl;
                //     break;
                // }
                
                case 'q':
                case 'Q':
                    stay = false;
                    break;
                    
                default:
                    cout << "   Commands not supported.\n";
            }
        }
        else 
            cout << "   Only single character command please.\n\n";
            // or implement word command command below
    }
}
