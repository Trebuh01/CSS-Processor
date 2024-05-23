#pragma once
#include "B_Node.h"

template <typename T> class Block_List {
private:
    int size;
    B_Node<T>* head;
    B_Node<T>* tail;
public:
    Block_List()
    {
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    ~Block_List()
    {
        while (head != nullptr && head->next != nullptr)
        {
            B_Node<T>* tmp = head->next;
            delete head;
            head = tmp;
        }

        if (head != nullptr) delete head;
    }
    void kasowanie(int index)
    {
        if (index > size || index < 1)
        {
            return;
        }

        B_Node<T>* nodeToDelete = nullptr;
        int iterator = 1;
        nodeToDelete = head;
        while (index >= iterator + nodeToDelete->nrZajetego)
        {
            iterator += nodeToDelete->nrZajetego;
            nodeToDelete = nodeToDelete->next;
        }
        int sectionIndex = 0;
        while (iterator <= index)
        {
            if (nodeToDelete->czyZajete[sectionIndex])
            {
                iterator++;
            }
            sectionIndex++;
        }
        sectionIndex--;
        nodeToDelete->czyZajete[sectionIndex] = 0;
        nodeToDelete->nrZajetego--;

        if (nodeToDelete->nrZajetego == 0)
        {
            usuwanieNode(nodeToDelete);
        }

        size--;
    }

    void push_back(T object)
    {
        if (tail == nullptr || tail->czyZajete[SIZE - 1])
        {
            B_Node<T>* nowy_node = new B_Node<T>;

            nowy_node->value[0] = object;
            nowy_node->czyZajete[0] = 1;
            nowy_node->nrZajetego++;
            nowy_node->next = nullptr;
            nowy_node->previous = tail;
            if (tail != nullptr)tail->next = nowy_node;

            tail = nowy_node;
            if (head == nullptr) head = nowy_node;
        }
        else
        {
            int index = SIZE - 2;
            while (index > 0 && !tail->czyZajete[index])
            {
                index--;
            }
            index++;
            tail->value[index] = object;
            tail->czyZajete[index] = true;
            tail->nrZajetego++;
        }
        size++;
    }

    int rozmiar()
    {
        return size;
    }
    void removeAtIndex(int index)
    {
        if (index > size || index < 1)
        {
            return;
        }

        B_Node<T>* nodeToDelete = nullptr;
        int iterator = 1;
        nodeToDelete = head;
        while (index >= iterator + nodeToDelete->nrZajetego)
        {
            iterator += nodeToDelete->nrZajetego;
            nodeToDelete = nodeToDelete->next;
        }
        int sectionIndex = 0;
        while (iterator <= index)
        {
            if (nodeToDelete->czyZajete[sectionIndex])
            {
                iterator++;
            }
            sectionIndex++;
        }
        sectionIndex--;
        nodeToDelete->czyZajete[sectionIndex] = 0;
        nodeToDelete->nrZajetego--;
        delete nodeToDelete->value[sectionIndex];
        if (nodeToDelete->nrZajetego == 0)
        {
            usuwanieNode(nodeToDelete);
        }

        size--;
    }
    T* getElement(int index)
    {
        if (index > size || index < 1 || head == nullptr) return nullptr;
        B_Node<T>* wsk = nullptr;

        int iterator = 1;
        wsk = head;
        while (index >= iterator + (wsk->nrZajetego))
        {
            iterator += wsk->nrZajetego;
            wsk = wsk->next;
        }
        int pom = 0;
        while (iterator <= index)
        {
            if (wsk->czyZajete[pom])
            {
                iterator++;
            }
            pom++;
        }
        return &(wsk->value[pom - 1]);


    }

    void usuwanieNode(B_Node<T>* wsk)
    {
        if (wsk->previous != nullptr)
        {
            wsk->previous->next = wsk->next;
        }
        if (wsk->next != nullptr)
        {
            wsk->next->previous = wsk->previous;
        }

        delete wsk;
    }
};
