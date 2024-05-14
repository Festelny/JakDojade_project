#pragma once
#include <iostream>

using namespace std;

class String {
public:
    // Konstruktory
    String() : str(nullptr), len(0) {}

    String(const char* s) {
        len = strlen(s);
        str = new char[len + 1];
        for (int i = 0; i < len; i++) {
            str[i] = s[i];
        }
        str[len] = '\0';
    }

    String(const char* s, int iterator) {
        len = iterator;
        str = new char[len + 1];
        for (int i = 0; i < len; i++) {
            str[i] = s[i];
        }
        str[len] = '\0';
    }

    String(const char* s, int start, int koniec) {
        int k = start;
        len = koniec - start;
        str = new char[len+1];
        for (int i = 0; i < len; i++) {
            str[i] = s[k];
            k++;
        }
        str[len] = '\0';
    }

    ~String() {
        delete[] str;
    }

    String& copy(const String& other) {
        if (this == &other) {
            return *this;
        }
        delete[] str;
        len = other.len;
        str = new char[len + 1];
        for (int i = 0; i < len; i++) {
            str[i] = other.str[i];
        }
        str[len] = '\0';
        return *this;
    }

    void print() const {
        std::cout << str;
    }

    int czytoint() {
        return atoi(str);
    }

    bool Tosamo(const String& other) {
        if (len != other.len) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (str[i] != other.str[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const String& other) const {
        if (len != other.len) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (str[i] != other.str[i]) {
                return false;
            }
        }
        return true;
    }

private:
    char* str;
    int len;
};