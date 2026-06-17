#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <stdexcept>
using namespace std;

class String
{
    char *str;

    int sizeOfArray(const char *_str) const;
    void copyArrayToOther(const char *s, char *d);

public:
    String();
    String(const char *_str);
    String(const String &other);
    String(char ch);
    String(int n, char ch);
    String(int n);

    ~String();

    friend ostream &operator<<(ostream &os, const String &s);
    friend istream &operator>>(istream &is, String &s);

    friend String operator+(const String &lhs, const String &rhs);

    friend bool operator==(const String &lhs, const String &rhs);
    friend bool operator!=(const String &lhs, const String &rhs);
    friend bool operator<(const String &lhs, const String &rhs);
    friend bool operator>(const String &lhs, const String &rhs);
    friend bool operator>=(const String &lhs, const String &rhs);
    friend bool operator<=(const String &lhs, const String &rhs);

    int size() const;

    void increaseCapacity(int &c, int s, int *&substr);

    String &operator=(const String &other);

    char &at(int pos);

    char &operator[](int pos);
    const char &operator[](int pos) const;

    char &front();
    char &back();

    bool empty() const;

    String &insert(int pos, char ch);
    String &insertRange(int pos, const char *other);

    String &operator+=(const String &other);
    String &operator+=(char ch);

    void replaceFirst(char c);

    int length();

    int stoi() const;
    float stof() const;

    String itos(int n);

    void trim();

    bool isEqual(const String &other) const;
    bool isLess(const String &other) const;
    bool isGreater(const String &other) const;

    String *split(char delim, int &count) const;

    bool isDelim(char ch, const char *delim) const;

    String *tokenize(const char *delim, int &count) const;

    String concat(const String &other) const;

    String &append(const String &other);

    bool isSubstring(int pos, const char *sub) const;

    int *allSubstrings(const char *sub, int &count);

    int find_first(char ch);
    int find_first(const String &sub);

    int find_last(char ch);
    int find_last(const String &sub);

    int *find_all(char ch, int &count);
    int *find_all(const String &sub, int &count);

    void remove_at(int pos);

    void insert_at(int pos, char ch);
    void insert_at(int pos, const String &sub);

    void remove_first(char ch);
    void remove_last(char ch);
    void remove_all(char ch);

    void clear();

    void toUpper();
    void toLower();

    istream &getline(istream &in, char delim = '\n');

    void print() const;
};

#endif