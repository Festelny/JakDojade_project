#pragma once
#include"String.cpp"
#include <iostream>

using namespace std;


class ListS {
public:
    struct NodeS
    {
        int index;
        String* name;
        int distance;
        NodeS* prev;
        NodeS* next;
    };
    NodeS* head;
    NodeS* tail;

    ListS() {
        head = nullptr;
        tail = nullptr;
    }

    ~ListS() {
        NodeS* current = head;
        while (current != nullptr) {
            NodeS* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addToEnd(String* newName, int newDistance,int index) {
        NodeS* newElement = new NodeS;
        newElement->name = newName;
        newElement->distance = newDistance;
        newElement->index = index;
        newElement->next = nullptr;
        newElement->prev = nullptr;

        if (head == nullptr) {
            head = newElement;
            tail = newElement;
        }
        else {
            NodeS* current = tail;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newElement;
            newElement->prev = current;
            tail = newElement;
        }
    }
};

class ListN {
public:
    struct NodeN {
        int index;
        String* name;
        int x, y;
        ListS bffs;
        NodeN* prev;
        NodeN* next;
    };
    NodeN* head;
    NodeN* tail;

    ListN() {
        head = nullptr;
        tail = nullptr;
    }

    ~ListN() {
        NodeN* current = head;
        while (current != nullptr) {
            NodeN* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addToEnd(int x, int y) {
        NodeN* newElement = new NodeN;
        newElement->x = x;
        newElement->y = y;
        newElement->next = nullptr;
        newElement->prev = nullptr;

        if (head == nullptr) {
            head = newElement;
            tail = newElement;
        }
        else {
            NodeN* current = tail;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newElement;
            newElement->prev = current;
            tail = newElement;
        }
    }

    int GetLength() {
        int length = 0;
        NodeN* current = head;
        while (current->next != nullptr) {
            current = current->next;
            length++;
        }
        return length;
    }
};

class List {
public:
    struct Node {
        String* value;
        Node* next;
    };
    Node* head;

    List() : head(nullptr) {}

    void dodajNaPoczatek(String* d) {
        Node* newNode = new Node;
        newNode->next = head;
        newNode->value = d;
        head = newNode;
    }

    void usunPierwszy() {
        if (head != nullptr) {
            Node* nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
        }
    }

    void usunOstatni() {
        if (head != nullptr) {
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
            }
            else {
                Node* prev = head;
                Node* current = head->next;
                while (current->next != nullptr) {
                    prev = current;
                    current = current->next;
                }
                delete current;
                prev->next = nullptr;
            }
        }
    }

    int GetLength() {
        int length = 0;
        Node* current = head;
        while (current != nullptr) {
            current = current->next;
            length++;
        }
        return length;
    }
};


