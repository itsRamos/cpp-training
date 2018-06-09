//User defined deque
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

template<class T>
struct Node {
    T value;
    Node *next;
};

template<class T>
class Combo {
private:
    int count;
    Node<T> *head;

public:
    Combo() {
        head = nullptr;
        count = 0;
    }
    
    ~Combo() {
        Node<T> *p = head;
        while(p) {
            delete p;
            p = p->next;
        }
    }
    
    int size() {
        return count;
    }
    
    void insert(T);
    void remove(T);
    T front();
    T back();
    void push_front(T);
    void push_back(T);
    void pop_front();
    void pop_back();
    void display() const;
    string toString();
};

template<class T>
void Combo<T>::insert(T num) {
    Node<T> *newNode;
    Node<T> *p;
    Node<T> *prev = nullptr;
    
    newNode = new Node<T>;
    newNode->value = num;
    newNode->next = nullptr;
    
    if(!head) {
        head = newNode;
        count++;
    }
    else {
        p = head;
        while(p != nullptr && p->value < num) {
            prev = p;
            p = p->next;
        }
        if(prev == nullptr) {
            head = newNode;
            newNode->next = p;
        }
        else {
            prev->next = newNode;
            newNode->next = p;
        }
        count++;
    }
}

template<class T>
void Combo<T>::remove(T num) {
    Node<T> *p;
    Node<T> *prev = nullptr;
    
    if(!head) return;
    
    if(head->value == num) {
        p = head->next;
        delete head;
        head = p;
        count--;
    }
    else {
        p = head;
        while(p != nullptr && p->value != num) {
            prev = p;
            p = p->next;
        }
        if(p) {
            prev->next = p->next;
            delete p;
            count--;
        }
    }
}

template<class T>
T Combo<T>::front() {
    Node<T> *p = head;
    return p->value;
}

template<class T>
T Combo<T>::back() {
    Node<T> *p = head;
    Node<T> *prev = nullptr;
    
    while(p != nullptr) {
        prev = p;
        p = p->next;
    }
    
    return prev->value;
}

template<class T>
void Combo<T>::push_front(T num) {
    Node<T> *newNode;
    Node<T> *p;
    Node<T> *prev = nullptr;
    
    newNode = new Node<T>;
    newNode->value = num;
    newNode->next = nullptr;
    
    if(!head) {
        head = newNode;
        count++;
    }
    else {
        p = head;
        if(prev == nullptr) {
            head = newNode;
            newNode->next = p;
        }
        else {
            prev->next = newNode;
            newNode->next = p;
        }
        count++;
    }
}

template<class T>
void Combo<T>::push_back(T num) {
    Node<T> *newNode;
    Node<T> *p;
    Node<T> *prev = nullptr;
    
    newNode = new Node<T>;
    newNode->value = num;
    newNode->next = nullptr;
    
    if(!head) {
        head = newNode;
        count++;
    }
    else {
        p = head;
        while(p != nullptr) {
            prev = p;
            p = p->next;
        }
        
        if(prev == nullptr) {
            head = newNode;
            newNode->next = p;
        }
        else {
            prev->next = newNode;
            newNode->next = p;
        }
        count++;
    }
}

template<class T>
void Combo<T>::pop_front() {
    Node<T> *p;
    Node<T> *prev = nullptr;
    
    if(!head) return;
    
    p = head->next;
    delete head;
    head = p;
    count--;
}

template<class T>
void Combo<T>::pop_back() {
    Node<T> *p;
    Node<T> *prev = nullptr;
    
    p = head;
    while(p != nullptr && p->next != 0) {
        prev = p;
        p = p->next;
    }
    
    if(p) {
        prev->next = p->next;
        delete p;
        count--;
    }
}

template<class T>
void Combo<T>::display() const {
    Node<T> *p = head;
    while(p->next) {
        cout << p->value << ". ";
        p = p->next;
    }
    cout << p->value << endl;
}

template<class T>
string Combo<T>::toString() {
    stringstream ss;
    Node<T> *p = head;
    bool first = true;
    
    while(p) {
        if(first) {
            first = !first;
        }
        else {
            ss <<", ";
        }
        ss << p->value;
        p = p->next;
    }
    return ss.str();
}

int main() {
    Combo<double> list;
    
    list.push_front(3.3);
    list.push_front(1.1);
    list.push_back(5.5);
    list.push_back(7.7);
    list.push_back(9.9);
    list.push_back(4.4);
    list.push_back(8.8);
    
    auto showd = [](Combo<double>& x) {
    //     cout << "\nList has " << x.size() << " items: "
    //          << x.toString();
    // };
    cout << "\nlist has " << x.size() << " items\nfirst: "
         << x.front() << " last: " << x.back() << endl
         << x.toString();};
    showd(list);

    list.pop_front();
    list.pop_back();
    showd(list);

    list.pop_front(); 
    list.pop_back();
    showd(list);
         
    list.pop_front();
    list.pop_back(); 
    showd(list);
    
    Combo<string> slist;
    auto shows = [](Combo<string>& x) {
        cout << "\nlist has " << x.size() << " items; first: "
             << x.front() << " last: " << x.back() << endl
             << x.toString();
    };

    slist.push_front("fruits");
    slist.push_front("are");
    slist.push_front("delicious");
    slist.push_front("eat");
    slist.push_back("like");
    slist.push_back("apple");
    slist.push_back("apple");
    shows(slist);
         
    slist.pop_front();
    slist.pop_back();
    shows(slist);

    slist.pop_front();
    slist.pop_back();
    shows(slist);

    slist.pop_front();
    slist.pop_back();
    shows(slist);
}
