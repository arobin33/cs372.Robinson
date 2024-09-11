//
// File:   assignment3part3.cpp
// Author: arielle robinson
// Purpose:
// circular lists
//

#include <iostream>
using namespace std;

template <typename T>
class List {
protected:
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
    List(List& rhs);
    ~List();
    bool empty();
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

template <typename T>
class CircularList : public List<T> {
public:
    CircularList() : List<T>() {}
    CircularList(T newData) : List<T>(newData) {}
    CircularList(List<T>& rhs) : List<T>(rhs) {
        if (this->tail) {
            this->tail->next = this->head;
            this->head->prev = this->tail;
        }
    }
    ~CircularList() {
        if (this->head) {
            this->tail->next = nullptr;
            this->head->prev = nullptr;
        }
    }
    void push_front(T data) override;
    void push_back(T data) override;
    void pop_back() override;
    void pop_front() override;
    void circle(void (*doIt)(T data), int start);
};

template <typename T>
void CircularList<T>::push_front(T data) {
    List<T>::push_front(data);
    this->head->prev = this->tail;
    this->tail->next = this->head;
}

template <typename T>
void CircularList<T>::push_back(T data) {
    List<T>::push_back(data);
    this->head->prev = this->tail;
    this->tail->next = this->head;
}

template <typename T>
void CircularList<T>::pop_back() {
    if (this->empty()) {
        throw runtime_error("List is empty!");
    }
    if (this->head == this->tail) {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }
    Node* temp = this->tail;
    this->tail = this->tail->prev;
    this->tail->next = this->head;
    this->head->prev = this->tail;
    delete temp;
}

template <typename T>
void CircularList<T>::pop_front() {
    if (this->empty()) {
        throw runtime_error("List is empty!");
    }
    if (this->head == this->tail) {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }
    Node* temp = this->head;
    this->head = this->head->next;
    this->head->prev = this->tail;
    this->tail->next = this->head;
    delete temp;
}

template <typename T>
void CircularList<T>::circle(void (*doIt)(T data), int start) {
    if (this->empty()) {
        throw runtime_error("List is empty!");
    }

    Node* current = this->head;
    for (int i = 0; i < start; ++i) {
        current = current->next;
    }

    do {
        doIt(current->data);
        current = current->next;
    } while (current != this->head);
}

int main() {
    CircularList<int> clist;
    clist.push_back(1);
    clist.push_back(2);
    clist.push_back(3);
    clist.push_back(4);
    clist.push_front(0);

    cout << "Traversing circular list:" << endl;
    clist.traverse(printIt);
    cout << endl;

    cout << "Circular traversal starting from position 2:" << endl;
    clist.circle(printIt, 2);
    cout << endl;

    return 0;
}