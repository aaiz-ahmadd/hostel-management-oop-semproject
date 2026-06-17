#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Vector
{
    T *vec;
    int _capacity;
    int _size;
    void increaseCapacity()
    {
        if (_capacity == 0)
            _capacity = 1;
        else
            _capacity *= 2;

        T *temp = new T[_capacity];
        try
        {
            for (int i = 0; i < _size; i++)
            {
                if (vec != nullptr)
                    temp[i] = vec[i];
                else
                    temp[i] = T{};
            }
        }
        catch (...)
        {
            delete[] temp;
            throw;
        }
        delete[] vec;
        vec = temp;
        temp = nullptr;
    }

public:
    void reserve(int new_cap)
    {
        if (new_cap > _capacity)
        {
            T *temp = new T[new_cap];
            try
            {
                for (int i = 0; i < _size; i++)
                    temp[i] = vec[i];
            }
            catch (...)
            {
                delete[] temp;
                throw;
            }
            delete[] vec;
            vec = temp;
            temp = nullptr;
            _capacity = new_cap;
        }
    }
    Vector() : vec{nullptr}, _capacity{1}, _size{0} {}
    Vector(int _s)
    {
        _capacity = 1;
        _size = _s;
        vec = nullptr;
        while (_size > _capacity)
            increaseCapacity();
        if (vec == nullptr)
            vec = new T[_capacity];
        for (int i = 0; i < _size; i++)
            vec[i] = T{};
    }
    Vector(int count, T val)
    {
        if (count > 0)
        {
            _capacity = count;
        }
        else
        {
            _capacity = 1;
        }
        _size = count;
        vec = new T[_capacity];
        for (int i = 0; i < _size; i++)
            vec[i] = val;
    }
    Vector(const Vector &other)
    {
        this->_capacity = other._capacity;
        this->_size = other._size;
        vec = new T[_capacity];
        try
        {
            for (int i = 0; i < _size; i++)
                vec[i] = other.vec[i];
        }
        catch (...)
        {
            delete[] vec;
            throw;
        }
    }
    ~Vector()
    {
        delete[] vec;
    }

    Vector &operator=(const Vector &other)
    {
        if (this == &other)
            return *this;
        delete[] vec;
        _size = other._size;
        _capacity = other._capacity;
        vec = new T[_capacity];
        try
        {
            for (int i = 0; i < _size; i++)
                vec[i] = other.vec[i];
        }
        catch (...)
        {
            delete[] vec;
            vec = nullptr;
            throw;
        }
        return *this;
    }

    void assign(int count, T val)
    {
        if (count > _capacity)
            reserve(count);
        _size = count;
        for (int i = 0; i < _size; i++)
            vec[i] = val;
    }

    void assign_range(int count, T arr[])
    {
        if (count > _capacity)
            reserve(count);
        _size = count;
        for (int i = 0; i < _size; i++)
            vec[i] = arr[i];
    }

    T &at(int pos)
    {
        if (pos < 0 || pos >= _size)
        {
            throw out_of_range("Invalid Range!");
        }
        return *(vec + pos);
    }
    const T &at(int pos) const
    {
        if (pos < 0 || pos >= _size)
        {
            throw out_of_range("Invalid Range!");
        }
        return *(vec + pos);
    }
    T &operator[](int pos)
    {
        return *(vec + pos);
    }
    const T &operator[](int pos) const
    {
        return vec[pos];
    }
    T &front()
    {
        if (_size == 0)
        {
            throw underflow_error("Vector is empty!");
        }
        return vec[0];
    }
    const T &front() const
    {
        if (_size == 0)
        {
            throw underflow_error("Vector is empty!");
        }
        return vec[0];
    }
    T &back()
    {
        if (_size == 0)
        {
            throw underflow_error("Vector is empty!");
        }
        return vec[_size - 1];
    }
    const T &back() const
    {
        if (_size == 0)
        {
            throw underflow_error("Vector is empty!");
        }
        return vec[_size - 1];
    }
    T *data()
    {
        return vec;
    }
    const T *data() const
    {
        return vec;
    }

    bool empty() const
    {
        return _size == 0;
    }
    bool isEmpty() const
    {
        return _size == 0;
    }
    int size() const
    {
        return _size;
    }
    int capacity() const
    {
        return _capacity;
    }
    void shrink_to_fit()
    {
        if (_capacity > _size)
        {
            if (_size == 0)
            {
                delete[] vec;
                vec = nullptr;
                _capacity = 0;
            }
            else
            {
                T *temp = new T[_size];
                try
                {
                    for (int i = 0; i < _size; i++)
                        temp[i] = vec[i];
                }
                catch (...)
                {
                    delete[] temp;
                    throw;
                }
                delete[] vec;
                vec = temp;
                _capacity = _size;
            }
        }
    }

    void clear()
    {
        _size = 0;
    }
    void insert(int pos, T val)
    {
        if (pos < 0 || pos > _size)
        {
            throw out_of_range("Invalid Range!");
        }
        if (_size == _capacity)
            increaseCapacity();
        for (int i = _size - 1; i >= pos; i--)
            vec[i + 1] = vec[i];
        vec[pos] = val;
        _size++;
    }
    // void insert_range(int pos, T arr[], int s)
    // template <class T>
    // void Vector<T>::insert_range(int pos, T arr[], int s)
    // {
    //     if (pos < 0 || pos > _size)
    //     {
    //         throw out_of_range("Invalid Range!");
    //     }

    //     while (_size + s > _capacity)
    //         increaseCapacity();

    //     for (int i = _size - 1; i >= pos; i--)
    //         vec[i + s] = vec[i];

    //     for (int i = 0; i < s; i++)
    //         vec[pos + i] = arr[i];

    //     _size += s;
    //  }
    void erase(int pos)
    {
        if (pos < 0 || pos >= _size)
        {
            throw out_of_range("Invalid Range!");
        }
        if (_size == 0)
        {
            throw underflow_error("Vector is empty!");
        }
        for (int i = pos; i + 1 < _size; i++)
            vec[i] = vec[i + 1];
        _size--;
    }
    void push_back(T val)
    {
        if (vec == nullptr)
            vec = new T[_capacity];

        if (_size == _capacity)
            increaseCapacity();
        vec[_size] = val;
        _size++;
    }
    void emplace_back(T val)
    {
        push_back(val);
    }
    void emplace(int pos, T val)
    {
        insert(pos, val);
    }
    void pop_back()
    {
        if (_size == 0)
        {
            throw underflow_error("Vector is empty!");
        }
        _size--;
    }
    void append_range(T arr[], int s)
    {
        while (_size + s > _capacity)
            increaseCapacity();
        for (int i = 0; i < s; i++)
            vec[_size + i] = arr[i];
        _size += s;
    }
    void resize(int count)
    {
        resize(count, T{});
    }
    void resize(int count, T val)
    {
        if (count < _size)
        {
            _size = count;
        }
        else if (count > _size)
        {
            if (count > _capacity)
                reserve(count);
            for (int i = _size; i < count; i++)
                vec[i] = val;
            _size = count;
        }
    }
    void swap(Vector &other)
    {
        T *temp_vec = vec;
        int temp_cap = _capacity;
        int temp_size = _size;

        vec = other.vec;
        _capacity = other._capacity;
        _size = other._size;

        other.vec = temp_vec;
        other._capacity = temp_cap;
        other._size = temp_size;
    }

    void input()
    {
        cout << "Enter the size of the vector: ";
        int s;
        cin >> s;
        while (s > _capacity)
            increaseCapacity();
        if (vec == nullptr)
            vec = new T[_capacity];
        _size = s;
        cout << "Enter the elements of the vector: ";
        for (int i = 0; i < _size; i++)
            cin >> vec[i];
    }
    void display() const
    {
        cout << "{ ";
        for (int i = 0; i < _size; i++)
            cout << vec[i] << " ";
        cout << "}" << endl;
    }

    friend bool operator==(const Vector<T> &lhs, const Vector<T> &rhs);
    friend bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs);
    friend bool operator<(const Vector<T> &lhs, const Vector<T> &rhs);
    friend bool operator>(const Vector<T> &lhs, const Vector<T> &rhs);
    friend bool operator<=(const Vector<T> &lhs, const Vector<T> &rhs);
    friend bool operator>=(const Vector<T> &lhs, const Vector<T> &rhs);
    friend ostream &operator<<(ostream &os, const Vector<T> &v);
    friend istream &operator>>(istream &is, Vector<T> &v);
};

template <typename T>
bool operator==(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs._size != rhs._size)
        return false;
    for (int i = 0; i < lhs._size; i++)
    {
        if (lhs.vec[i] != rhs.vec[i])
            return false;
    }
    return true;
}
template <typename T>
bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs._size != rhs._size)
        return true;
    for (int i = 0; i < lhs._size; i++)
    {
        if (lhs.vec[i] != rhs.vec[i])
            return true;
    }
    return false;
}
template <typename T>
bool operator<(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs._size > rhs._size)
        return false;
    if (lhs._size < rhs._size)
        return true;
    for (int i = 0; i < lhs._size; i++)
    {
        if (lhs.vec[i] > rhs.vec[i])
            return false;
        if (lhs.vec[i] < rhs.vec[i])
            return true;
    }
    return false;
}
template <typename T>
bool operator>(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs._size > rhs._size) return true;
    if (lhs._size < rhs._size) return false;
    for (int i = 0; i < lhs._size; i++)
    {
        if (lhs.vec[i] > rhs.vec[i]) return true;
        if (lhs.vec[i] < rhs.vec[i]) return false;
    }
    return false;
}
template <typename T>
bool operator<=(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs._size < rhs._size)
        return true;
    if (lhs._size > rhs._size)
        return false;
    for (int i = 0; i < lhs._size; i++)
    {
        if (lhs.vec[i] < rhs.vec[i])
            return true;
        if (lhs.vec[i] > rhs.vec[i])
            return false;
    }
    return true;
}

template <typename T>
bool operator>=(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs._size > rhs._size)
        return true;
    if (lhs._size < rhs._size)
        return false;
    for (int i = 0; i < lhs._size; i++)
    {
        if (lhs.vec[i] > rhs.vec[i])
            return true;
        if (lhs.vec[i] < rhs.vec[i])
            return false;
    }
    return true;
}

template <typename T>
ostream &operator<<(ostream &os, const Vector<T> &v)
{
    for (int i = 0; i < v._size; i++)
    {
        os << v.vec[i];
        if (i < v._size - 1)
            os << " ";
    }
    return os;
}

template <typename T>
istream &operator>>(istream &is, Vector<T> &v)
{
    int s;
    is >> s;
    while (s > v._capacity)
        v.increaseCapacity();
    if (v.vec == nullptr)
        v.vec = new T[v._capacity];
    v._size = s;
    for (int i = 0; i < v._size; i++)
        is >> v.vec[i];
    return is;
}

#endif