#include "Poz.h"
#include "string.cpp"
#include <iostream>

class PQueue {
private:
    struct Node {
        Dane wartosci;
        Node* next;
        Node* prev;

        Node(int index, int odleglosc,String* name) {
            wartosci.index = index;
            wartosci.distance = odleglosc;
            wartosci.name = name;
            next = nullptr;
            prev = nullptr;
        }
    };

    Node* frontPtr;
    Node* rearPtr;
    int size;

public:
    PQueue() {
        frontPtr = nullptr;
        rearPtr = nullptr;
        size = 0;
    }

    ~PQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(int index, int odleglosc,String* name) {
        Node* newNode = new Node(index, odleglosc,name);

        if (isEmpty()) {
            frontPtr = newNode;
            rearPtr = newNode;
        }
        else {
            Node* current = frontPtr;
            Node* prevv = nullptr;

            while (current != nullptr && current->wartosci.distance <= odleglosc) {
                prevv = current;
                current = current->next;
            }

            if (prevv == nullptr) {
                newNode->next = frontPtr;
                frontPtr = newNode;
            }
            else if (current == nullptr) {
                prevv->next = newNode;
                rearPtr = newNode;
            }
            else {
                prevv->next = newNode;
                newNode->next = current;
            }
        }
        size++;
    }

    Dane dequeue() {
        if (isEmpty()) {
            std::cerr << "Kolejka jest pusta." << std::endl;
            return Dane{ -1, -1 ,0};  // zwracamy warto?? domy?ln?
        }

        Node* temp = frontPtr;
        Dane firstPoz = temp->wartosci;
        frontPtr = frontPtr->next;
        delete temp;
        size--;

        return firstPoz;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};