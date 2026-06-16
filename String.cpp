#include "String.h"

int String::sizeOfArray(const char *_str) const
{
    int size = 0;
    for (; _str[size] != '\0'; size++);
    return size;
}

void String::copyArrayToOther(const char *s, char *d)
{
    int i = 0;
    for (; s[i] != '\0'; i++)
        d[i] = s[i];
    d[i] = '\0';
}

String::String()
{
    str = new char[1];
    str[0] = '\0';
}

String::String(const char *_str)
{
    int size = sizeOfArray(_str);
    str = new char[size + 1];
    copyArrayToOther(_str, str);
}

String::String(const String &other)
{
    int size = sizeOfArray(other.str);
    str = new char[size + 1];
    copyArrayToOther(other.str, str);
}

String::String(char ch)
{
    str = new char[2];
    str[0] = ch;
    str[1] = '\0';
}

String::String(int n, char ch)
{
    str = new char[n + 1];
    for (int i = 0; i < n; i++)
        str[i] = ch;
    str[n] = '\0';
}

String::String(int n)
{
    int size = 0;
    int temp = n;
    if (temp == 0)
        size = 1;
    while (temp != 0)
    {
        temp /= 10;
        size++;
    }
    str = new char[size + 1];
    for (int i = size - 1; i >= 0; i--)
    {
        str[i] = (n % 10) + '0';
        n /= 10;
    }
    str[size] = '\0';
}

String::~String()
{
    delete[] str;
}

int String::size() const
{
    return sizeOfArray(str);
}

void String::increaseCapacity(int &c, int s, int *&substr)
{
    c *= 2;
    int *temp = new int[c];
    for (int i = 0; i < s; i++)
        temp[i] = substr[i];
    delete[] substr;
    substr = temp;
}

String &String::operator=(const String &other)
{
    if (this == &other)
        return *this;
    char *temp = new char[sizeOfArray(other.str) + 1];
    try
    {
        copyArrayToOther(other.str, temp);
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    delete[] str;
    str = temp;
    return *this;
}

char &String::at(int pos)
{
    int size = sizeOfArray(str);
    if (pos < 0 || pos >= size)
        throw out_of_range("Invalid Index entered!");
    return str[pos];
}

char &String::operator[](int pos)
{
    int size = sizeOfArray(str);
    if (pos < 0 || pos >= size)
        throw out_of_range("Invalid Index entered!");
    return str[pos];
}

const char &String::operator[](int pos) const
{
    int size = sizeOfArray(str);
    if (pos < 0 || pos >= size)
        throw out_of_range("Invalid Index entered!");
    return str[pos];
}

char &String::front()
{
    if (str[0] == '\0')
        throw underflow_error("String is empty!");
    return str[0];
}

char &String::back()
{
    int size = sizeOfArray(str);
    if (size == 0)
        throw underflow_error("String is empty!");
    return str[size - 1];
}

bool String::empty() const
{
    return sizeOfArray(str) == 0;
}

String &String::insert(int pos, char ch)
{
    int s = size();
    if (pos < 0 || pos > s)
    {
        throw std::out_of_range("Error: Insert position out of bounds!");
    }
    char *temp = new char[s + 2];
    try
    {
        for (int i = 0; i < pos; i++)
            temp[i] = str[i];
        temp[pos] = ch;
        for (int i = pos; i < s; i++)
            temp[i + 1] = str[i];
        temp[s + 1] = '\0';
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    delete[] str;
    str = temp;
    temp = nullptr;
    return *this;
}

String &String::insertRange(int pos, const char *other)
{
    int size1 = sizeOfArray(str);
    int size2 = sizeOfArray(other);
    
    if (pos < 0 || pos > size1)
    {
        throw std::out_of_range("Error: Insert position out of bounds!");
    }
    
    char *temp = new char[size1 + size2 + 1];
    
    try
    {
        int i = 0;
        for (; i < pos; i++)
            temp[i] = str[i];
        for (int j = 0; j < size2; j++)
            temp[i++] = other[j];
        for (int j = pos; j < size1; j++)
            temp[i++] = str[j];
        temp[i] = '\0';
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    
    delete[] str;
    str = temp;
    return *this;
}

String &String::operator+=(const String &other)
{
    int size1 = sizeOfArray(str);
    int size2 = sizeOfArray(other.str);
    char *temp = new char[size1 + size2 + 1];
    try
    {
        int i = 0;
        for (; i < size1; i++)
            temp[i] = str[i];
        for (int j = 0; j < size2; j++)
            temp[i++] = other.str[j];
        temp[i] = '\0';
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    delete[] str;
    str = temp;
    temp = nullptr;
    return *this;
}

String &String::operator+=(char ch)
{
    int size1 = sizeOfArray(str);
    char *temp = new char[size1 + 2];
    try
    {
        int i = 0;
        for (; i < size1; i++)
            temp[i] = str[i];
        temp[i++] = ch;
        temp[i] = '\0';
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    delete[] str;
    str = temp;
    return *this;
}


void String::replaceFirst(char c)
{
    if (str[0] != '\0')
        str[0] = c;
}

int String::length()
{
    return sizeOfArray(str);
}

int String::stoi() const
{
    if(empty())
        throw invalid_argument("Error: Cannot convert an empty string to an integer.");
    int num = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            throw invalid_argument("Error: String contains non-numeric characters.");
        num = (num * 10) + (str[i] - '0');
    }
    return num;
}

String String::itos(int n)
{
    return String(n);
}

void String::trim()
{
    int size = sizeOfArray(str);
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            for (int j = i + 1; j <= size; j++)
                str[j - 1] = str[j];
            size--;
            i--;
        }
        else
            count++;
        if (count > 0)
            break;
    }
    count = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            str[i] = '\0';
            size--;
        }
        else
            count++;
        if (count > 0)
            break;
    }
}

bool String::isEqual(const String &other) const
{
    int size1 = size();
    int size2 = other.size();
    if (size1 != size2)
        return false;
    for (int i = 0; i < size1; i++)
    {
        if (str[i] != other.str[i])
            return false;
    }
    return true;
}

bool String::isLess(const String &other) const
{
    int size1 = size();
    int size2 = other.size();
    int min_size = (size1 < size2) ? size1 : size2;
    for (int i = 0; i < min_size; i++)
    {
        if (str[i] > other.str[i])
            return false;
        if (str[i] < other.str[i])
            return true;
    }
    return size1 < size2;
}

bool String::isGreater(const String &other) const
{
    int size1 = size();
    int size2 = other.size();
    int min_size = (size1 < size2) ? size1 : size2;
    for (int i = 0; i < min_size; i++)
    {
        if (str[i] < other.str[i])
            return false;
        if (str[i] > other.str[i])
            return true;
    }
    return size1 > size2;
}

String *String::split(char delim, int &count) const
{
    count = 1;
    int size = sizeOfArray(str);
    for (int i = 0; i < size; i++)
    {
        if (str[i] == delim)
            count++;
    }
    String *temp = new String[count];
    try
    {
        int idx = 0;
        int s = 0;
        for (int i = 0; i <= size; i++)
        {
            if (str[i] == delim || str[i] == '\0')
            {
                temp[idx].str = new char[s + 1];
                int start = i - s;
                for (int j = 0; j < s; j++)
                    temp[idx].str[j] = str[start + j];
                temp[idx].str[s] = '\0';
                s = 0;
                idx++;
            }
            else
                s++;
        }
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    return temp;
}


bool String::isDelim(char ch, const char *delim) const
{
    for (int i = 0; delim[i] != '\0'; i++)
        if (ch == delim[i])
            return true;
    return false;
}

String *String::tokenize(const char *delim, int &count) const
{
    bool inToken = false;
    count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isDelim(str[i], delim) && !inToken)
        {
            inToken = true;
            count++;
        }
        else if (isDelim(str[i], delim))
            inToken = false;
    }
    String *temp = new String[count];
    try
    {
        int s = 0;
        int idx = 0;
        for (int i = 0;; i++)
        {
            if (isDelim(str[i], delim) || str[i] == '\0')
            {
                if (s > 0)
                {
                    temp[idx].str = new char[s + 1];
                    int start = i - s;
                    for (int j = 0; j < s; j++)
                        temp[idx].str[j] = str[start + j];
                    temp[idx].str[s] = '\0';
                    s = 0;
                    idx++;
                }
                if (str[i] == '\0')
                    break;
            }
            else
                s++;
        }
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    return temp;
}

String String::concat(const String &other) const
{
    String temp;
    temp = *this + other;
    return temp;
}

String &String::append(const String &other)
{
    *this += other;
    return *this;
}

bool String::isSubstring(int pos, const char *sub) const
{
    int i = 0;
    while (sub[i] != '\0')
    {
        if (str[pos + i] != sub[i])
            return false;
        i++;
    }
    return true;
}

int *String::allSubstrings(const char *sub, int &count)
{
    count = 0;
    int c = 1;
    int s = 0;
    int *substr = new int[c];
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub[0])
        {
            if (isSubstring(i, sub))
            {
                if (s >= c)
                    increaseCapacity(c, s, substr);
                substr[s++] = i;
                count++;
            }
        }
    }
    return substr;
}

int String::find_first(char ch)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch)
            return i;
    }
    return -1;
}

int String::find_first(const String &sub)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub.str[0])
        {
            if (isSubstring(i, sub.str))
                return i;
        }
    }
    return -1;
}

int String::find_last(char ch)
{
    int size = sizeOfArray(str);
    for (int i = size - 1; i >= 0; i--)
    {
        if (str[i] == ch)
            return i;
    }
    return -1;
}

int String::find_last(const String &sub)
{
    int size = sizeOfArray(str);
    for (int i = size - 1; i >= 0; i--)
    {
        if (str[i] == sub.str[0])
        {
            if (isSubstring(i, sub.str))
                return i;
        }
    }
    return -1;
}

int *String::find_all(char ch, int &count)
{
    count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch)
            count++;
    }
    int *temp = new int[count];
    int s = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch)
            temp[s++] = i;
    }
    return temp;
}

int *String::find_all(const String &sub, int &count)
{
    count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub.str[0])
        {
            if (isSubstring(i, sub.str))
                count++;
        }
    }
    int *temp = new int[count];
    int s = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub.str[0])
        {
            if (isSubstring(i, sub.str))
                temp[s++] = i;
        }
    }
    return temp;
}

void String::remove_at(int pos)
{
    int s = sizeOfArray(str);
    if (pos < 0 || pos >= s)
        throw out_of_range("Invalid Index entered!");
    for (int i = pos; i < s - 1; i++)
        str[i] = str[i + 1];
    str[s - 1] = '\0';
}

void String::insert_at(int pos, char ch)
{
    *this = insert(pos, ch);
}

void String::insert_at(int pos, const String &sub)
{
    *this = insertRange(pos, sub.str);
}

void String::remove_first(char ch)
{
    int idx = find_first(ch);
    if (idx != -1)
        remove_at(idx);
}

void String::remove_last(char ch)
{
    int idx = find_last(ch);
    if (idx != -1)
        remove_at(idx);
}

void String::remove_all(char ch)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ch)
            remove_at(i);
        else
            i++;
    }
}

void String::clear()
{
    delete[] str;
    str = new char[1];
    str[0] = '\0';
}

void String::toUpper()
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

void String::toLower()
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

istream &String::getline(istream &in, char delim)
{
    clear();
    char c;
    while (in.get(c))
    {
        if (c == delim)
            break;
        *this += c;
    }
    return in;
}

void String::print() const
{
    cout << str << endl;
}

ostream &operator<<(ostream &os, const String &s)
{
    os << s.str;
    return os;
}

istream &operator>>(istream &is, String &s)
{
    char buffer[1024];
    is >> buffer;
    
    int size = s.sizeOfArray(buffer);
    char *temp = new char[size + 1];
    
    s.copyArrayToOther(buffer, temp);
    
    delete[] s.str;
    s.str = temp;
    
    return is;
}

String operator+(const String &lhs, const String &rhs)
{
    int size1 = lhs.size();
    int size2 = rhs.size();
    char *temp_arr = new char[size1 + size2 + 1];
    try
    {
        int i = 0;
        for (; i < size1; i++)
            temp_arr[i] = lhs.str[i];
        for (int j = 0; j < size2; j++)
            temp_arr[i++] = rhs.str[j];
        temp_arr[i] = '\0';
    }
    catch (...)
    {
        delete[] temp_arr;
        throw;
    }
    String temp;
    delete[] temp.str;
    temp.str = temp_arr;
    return temp;
}


bool operator==(const String &lhs, const String &rhs)
{
    return lhs.isEqual(rhs);
}

bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs)
{
    return lhs.isLess(rhs);
}

bool operator>(const String &lhs, const String &rhs)
{
    return lhs.isGreater(rhs);
}

bool operator>=(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}

bool operator<=(const String &lhs, const String &rhs)
{
    return !(lhs > rhs);
}
