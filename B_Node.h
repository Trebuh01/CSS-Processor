#pragma once
#define SIZE 8
using namespace std;

template <typename T> class B_Node {

public:
    int nrZajetego;
    T value[SIZE];
    bool czyZajete[SIZE];
    B_Node<T>* next;
    B_Node<T>* previous;
    B_Node() {
        nrZajetego = 0;
        next = nullptr;
        previous = nullptr;
        for (int i = 0; i < SIZE; ++i)
        {
            czyZajete[i] = 0;
        }
    }
};