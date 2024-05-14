#include "Poz.h"
#include <iostream>

class Queue {
private:
    struct Node {
        Poz pozycja;
        Node* next;

        Node(int x, int y) {
            pozycja.x = x;
            pozycja.y = y;
            next = nullptr;
        }
    };

    Node* frontPtr;
    Node* rearPtr;
    int size;

public:
    Queue() {
        frontPtr = nullptr;
        rearPtr = nullptr;
        size = 0;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(int x, int y) {
        Node* newNode = new Node(x, y);

        if (isEmpty()) {
            frontPtr = newNode;
            rearPtr = newNode;
        }
        else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }

        size++;
    }

    Poz dequeue() {
        if (isEmpty()) {
            std::cerr << "Kolejka jest pusta." << std::endl;
            return Poz{ -1, -1 };  // zwracamy warto?? domy?ln?
        }

        Node* temp = frontPtr;
        Poz firstPoz = temp->pozycja;
        frontPtr = frontPtr->next;
        delete temp;
        size--;

        return firstPoz;
    }

    Poz& front() const {
        if (isEmpty()) {
            std::cerr << "Kolejka jest pusta." << std::endl;
            return rearPtr->pozycja;
        }

        return frontPtr->pozycja;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};