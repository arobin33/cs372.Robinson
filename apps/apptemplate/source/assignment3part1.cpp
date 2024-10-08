//
// File:   assignment3part1.cpp
// Author: arielle robinson
// Purpose: make a list 

#include <iostream>
using namespace std;


int main() {
    // Put your code here.
    return 0;
}

#include <iostream>
using namespace std;

template <typename T>
class List {
private:
    class Node {
    public:
        T  data;
        Node* prev;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    List();
    List(T newData);
    List(List& rhs) ; 
    ~List();
    bool  empty();
    void push_front(T data);
    void push_back(T data);
    T front();
    T back();
    void pop_back();
    void pop_front();
    void traverse(void (*doIt)(T data));
};

template <typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
}

template <typename T>
List<T>::List(T newData) {
    head = new Node;
    head->data = newData;
    head->prev = nullptr;
    head->next = nullptr;
    tail = head;
}

template <typename T>
List<T>::List(List& rhs) {
    if (rhs.head == nullptr) {
        head = nullptr;
        tail = nullptr;
        return;
    }
    head = new Node;
    head->data = rhs.head->data;
    head->prev = nullptr;
    head->next = nullptr;
    Node* current = rhs.head->next;
    Node* previous = head;
    while (current != nullptr) {
        Node* newNode = new Node;
        newNode->data = current->data;
        newNode->prev = previous;
        newNode->next = nullptr;
        previous->next = newNode;
        previous = newNode;
        current = current->next;
    }
    tail = previous;
}

template <typename T>
List<T>::~List() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
bool List<T>::empty() {
    return (head == nullptr);
}

template <typename T>
void List<T>::push_front(T data) {
    if (empty()) {
        head = new Node;
        head->data = data;
        head->prev = nullptr;
        head->next = nullptr;
        tail = head;
        return;
    }
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;
    newNode->prev = nullptr;
    head->prev = newNode;
    head = newNode;
}

template <typename T>
void List<T>::push_back(T data) {
    if (empty()) {
        head = new Node;
        head->data = data;
        head->prev = nullptr;
        head->next = nullptr;
        tail = head;
        return;
    }
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

template <typename T>
T List<T>::front() {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    return head->data;
}

template <typename T>
T List<T>::back() {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    return tail->data;
}

template <typename T>
void List<T>::pop_back() {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete temp;
}

template <typename T>
void List<T>::pop_front() {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node* temp = head;
    head = head->next;
    head->prev = nullptr;
    delete temp;
}

template <typename T>
void List<T>::traverse(void (*doIt)(T data)) {
    Node* current = head;
    while (current != nullptr) {
        doIt(current->data);
        current = current->next;
    }
}

void printIt(int data) {
    cout << data << " ";
}

int main() {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_front(0);
    list1.push_back(3);
    list1.traverse(printIt);
    cout << endl;

    List<int> list2(list1);
    list2.push_back(4);
    list2.traverse(printIt);
    cout << endl;

    List<int> list3;
    list3 = list2; 
    list3.push_back(5);
    list3.traverse(printIt);
    cout << endl;

    return 0;
}
