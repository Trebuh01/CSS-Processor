#pragma once
using namespace std;

template <typename T> class Node {

public:
    T value;
    Node<T>* next;
    Node<T>* previous;
    Node() {
        next = nullptr;
        previous = nullptr;
    }
    Node(T newValue) {
        value = newValue;
        next = nullptr;
        previous = nullptr;
    }
};