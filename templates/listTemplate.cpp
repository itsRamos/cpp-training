#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<class T>
struct Node
{
    T value; // The value in this node
    struct Node<T> *next; // To point to the next node
};

template<class T>
class NumberList
{
    private:
    
    Node<T> *head; // List head pointer
    
    public:
    // Constructor
    NumberList()
    { head = nullptr; }

    // Destructor
    // ~NumberList();
    
    // Linked list operations
    void append(T);
    void insert(T);
    void remove(T);
    void display() const;
    std::string toString() const;
};

template<class T>
void NumberList<T>::insert(T num) {
    Node<T> *newNode, *p, *prev=nullptr;
    newNode = new Node<T>;
    newNode->value = num;
    newNode->next = nullptr;

    // if(head == nullptr)
    if(!head) // empty list
        head = newNode;
    else {
        p = head;
        while( p != nullptr  && p->value < num) {
            prev = p; p = p->next; }
        // p must be pointing to the first bigger, or end
        if(prev==nullptr) { // the first one is the last one.
            head = newNode;
            newNode->next = p; } 
        else {
            prev->next = newNode;
            newNode->next = p; } } }

template<class T>
void NumberList<T>::remove(T num) {
    Node<T> *p, *prev=nullptr;
    if(!head) return;
    if(head->value == num) {
        p = head->next;
        delete head;
        head = p; }
    else {
        p = head;
        // skip all NOTs
        while( p != nullptr  && p->value != num) {
            prev = p; p = p->next; }
        if(p) {
            prev->next = p->next;
            delete p; } } }

template<class T>
void NumberList<T>::append(T num) {
    Node<T> *newNode, *p;
    newNode = new Node<T>;
    newNode->value = num;
    newNode->next = nullptr;
    
    if( !head ) head = newNode;
    else {
        p = head;
        while(p->next) p=p->next;
        p->next = newNode;
    }
}
template<class T>
void NumberList<T>::display() const {
    Node<T> *p = head;

    while(p->next) {
        std::cout << p->value << ", ";
        p=p->next;
    }
    std::cout << p->value << std::endl;
}

template<class T>
std::string NumberList<T>::toString() const {
    std::string output;
    Node<T> *p = head;

    while(p->next) {
        output += std::to_string(p->value);
        output += ", ";
        p=p->next;
    }
    output += std::to_string(p->value);
    return output;
}


int main() {
    NumberList<double> list;
    list.append(2.5);
    list.append(7.9);
    list.append(12.6);
    list.display();
    list.insert(4.3);
    list.insert(11.11);
    list.insert(13.13);
    list.display();
    list.remove(7.9);
    list.remove(2.5);
    list.remove(13.13);
    list.display();
    
    NumberList<string> slist;
    slist.append("this");
    slist.append("is");
    slist.append("a");
    slist.display();
    slist.insert("xyz");
    slist.insert("apple");
    slist.insert("test");
    slist.display();
    slist.remove("this");
    slist.remove("test");
    slist.remove("xyz");
    slist.display();
    
    NumberList<double> list2;
    vector<double> data = {1.1,2.3,3.3,4.5,5.5,6.7,7.7,8.9,9.9};
    for(auto &i : data) list2.append(data[i - 1]);
    list2.display();
    
    vector<double> data2 = {69.0,6.9,0.69};
    for(auto &i2 : data2) list2.insert(data2[i2]);
    list2.display();
    for(auto &i2 : data2) list2.remove(data2[i2]);
    list2.display();
}
