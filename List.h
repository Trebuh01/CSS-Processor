#pragma once
#include "Node.h"
template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node(T v, Node* n = nullptr, Node* p = nullptr)
            : value(v), next(n), prev(p) {}
    };

    size_t size;
    Node* head;
    Node* tail;
public:
    List() : size(0), head(nullptr), tail(nullptr) {}

    ~List() {
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value, head, nullptr);
        if (head) {
            head->prev = newNode;
        }
        else {
            tail = newNode;
        }
        head = newNode;
        ++size;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value, nullptr, tail);
        if (tail) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        ++size;
    }

    void insertAfter(const T& value, size_t index) {
        if (index >= size) {
            push_back(value);
            return;
        }
        Node* cur = head;
        while (index--) {
            cur = cur->next;
        }
        Node* newNode = new Node(value, cur->next, cur);
        if (cur->next) {
            cur->next->prev = newNode;
        }
        else {
            tail = newNode;
        }
        cur->next = newNode;
        ++size;
    }

    size_t getSize() const {
        return size;
    }

    T* getElement(size_t index) const {
        if (index >= size) {
            return nullptr;
        }
        Node* cur = head;
        while (index--) {
            cur = cur->next;
        }
        return &cur->value;
    }
};