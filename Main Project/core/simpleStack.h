#ifndef SIMPLESTACK_H
#define SIMPLESTACK_H
#include <iostream>
using namespace std;

template <typename T>
class SimpleStack {
private:
    struct Node {
        T data;
        Node* next;

        Node(T val) {
            data = val;
            next = nullptr;
        }
    };

    Node* top_node;

public:
    SimpleStack() {
        top_node = nullptr;
    }

    ~SimpleStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T item) {
        Node* newNode = new Node(item);
        newNode->next = top_node;
        top_node = newNode;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return T();
        }
        Node* temp = top_node;
        T data = temp->data;
        top_node = top_node->next;
        delete temp;
        return data;
    }

    T peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return T();
        }
        return top_node->data;
    }

    bool isEmpty() const {
        return top_node == nullptr;
    }
};

#endif
