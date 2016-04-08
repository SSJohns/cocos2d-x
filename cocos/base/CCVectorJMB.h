//
//  CCVectorJMB.h
//  Ref_Ptr_And_Objects
//
//  Created by Jonathan Baker on 12/3/15.
//

#ifndef Ref_Ptr_And_Objects_CCVectorJMB_h
#define Ref_Ptr_And_Objects_CCVectorJMB_h

#include <vector>
#include "Ref_Ptr.h"

template <class T>
class Vector {
    
public:
    // Typedef for our new "vector of shared_ptr's" //
    using srd_vector = std::vector<Ref_Ptr<T>>;
    using data_vector = std::vector<T>;
    
    // -------------------------------------
    //                Iterators
    // -------------------------------------
    typedef typename data_vector::iterator iterator;
    typedef typename data_vector::const_iterator const_iterator;
    typedef typename data_vector::reverse_iterator reverse_iterator;
    typedef typename data_vector::const_reverse_iterator const_reverse_iterator;
    
    iterator begin() {return _data_vec.begin(); }
    const_iterator begin() const { return _data_vec.begin(); }
    
    iterator end() { return _data_vec.end(); }
    const_iterator end() const { return _data_vec.end(); }
    
    const_iterator cbegin() const { return _data_vec.cbegin(); }
    const_iterator cend() const {return _data_vec.cend(); }
    
    reverse_iterator rbegin() { return _data_vec.rbegin(); }
    const_reverse_iterator rbegin() const { return _data_vec.rbegin(); }
    
    reverse_iterator rend() { return _data_vec.rend(); }
    const_reverse_iterator rend() const { return _data_vec.rend(); }
    
    const_reverse_iterator crbegin() const { return _data_vec.crbegin(); }
    const_reverse_iterator crend() const { return _data_vec.crend(); }
    
    // -------------------------------------
    //             Constructors
    // -------------------------------------
    Vector<T>() : _data(), _data_vec() {}
    explicit Vector<T>(ssize_t capacity) : _data(), _data_vec() {
         reserve(capacity);
    }
    
    // -------------------------------------
    //             Destructors
    // -------------------------------------
    ~Vector<T>() { clear(); }
    
    // -------------------------------------
    //           Copy Constructors
    // -------------------------------------
    Vector<T>(const Vector<T>& other) { _data = other._data;
                                        _data_vec = other._data_vec;}
    
    Vector<T>(Vector<T>&& other) { _data = std::move(other._data);
                                   _data_vec = std::move(other._data_vec); }
    
    Vector<T>& operator=(const Vector<T>& other) {
        if(this != &other) {
            clear();
            _data = other._data;
            _data_vec = other._data_vec;
        }
        return *this;
    }
    Vector<T>& operator=(Vector<T>&& other) {
        if(this != &other) {
            clear();
            _data = std::move(other._data);
            _data_vec = std::move(other._data_vec);
        }
        return *this;
    }
    
    // -------------------------------------
    //            Access Operators
    // -------------------------------------
    T& operator[](int index) { return _data_vec.at(index); }
    const T& operator[](int index) const { return _data_vec.at(index); }
    ssize_t getIndex(T object) const {
        auto iter = std::find(_data_vec.begin(), _data_vec.end(), object);
        if(iter != _data_vec.end()) return iter - _data_vec.begin();
        return -1;
    }
    const_iterator find(T object) const {
        return std::find(_data_vec.begin(), _data_vec.end(), object);
    }
    iterator find(T object) {
        return std::find(_data_vec.begin(), _data_vec.end(), object);
    }
    T at(ssize_t index) const {
        return _data_vec.at(index);
    }
    T front() const { return _data_vec.front(); }
    T back() const { return _data_vec.back(); }
    T getRandomObject() const {
        if(!_data_vec.empty()) {
            ssize_t randIdx = rand() % _data_vec.size();
            return *(_data_vec.begin() + randIdx);
        }
        return nullptr;
    }
    bool contains(T object) const {
        return (std::find(_data_vec.begin(), _data_vec.end(), object) != _data_vec.end() );
    }

    // -------------------------------------
    //            Size Operators
    // -------------------------------------
    
    // reserves a number of elements for the class //
    void reserve(ssize_t n) { _data_vec.reserve(n); _data.reserve(n); }
    
    // returns the total number of elements allowed //
    ssize_t capacity() const { return _data_vec.capacity(); }
    
    // returns the number of elements in the vector //
    ssize_t size() const { return _data_vec.size(); }
    
    // returns whether the vector has any elements //
    bool empty() const { return _data_vec.empty(); }
    
    // returns the maximum size of the vector //
    ssize_t max_size() const { return _data_vec.max_size(); }
    
    // -------------------------------------
    //            Add New Objects
    // -------------------------------------
    
    // Pushes back new object using stl syntax //
    // Allows the addition of existing vectors to the back //
    void push_back(T object) { Ref_Ptr<T> temp(object); _data.push_back(temp); _data_vec.push_back(object); }
    void pushBack(T object) { push_back(object); }
    void pushBack(std::vector<T>& other) { push_back(other); }
    void push_back(std::vector<T>& other) {
        for(const auto &obj : other) {
            Ref_Ptr<T> temp(obj);
            _data.push_back(temp);
            _data_vec.push_back(obj);
        }
    }
    
    // stl insert feature //
    void insert(ssize_t index, T object) {
        if(index >= 0 && index <= size()) {
            Ref_Ptr<T> temp(object);
            _data.insert((std::begin(_data) + index), temp);
            _data_vec.insert((std::begin(_data_vec) + index), object);
        }
    }
    
    // C++11 Features enabled //
    // constructs a new element at an iterator position //
    iterator emplace(iterator location, const T& object) {
        Ref_Ptr<T> temp(object);
        _data.emplace(location, temp);
        return _data_vec.emplace(location, object);
    }
    
    //constructs a new element at the back //
    void emplace_back(const T& object) {
        Ref_Ptr<T> temp(object);
        _data.emplace_back(temp);
        _data_vec.emplace_back(object);
    }
    
    // -------------------------------------
    //            Object Removal
    // -------------------------------------
    void popBack() { pop_back(); }
    void pop_back() { _data.pop_back(); _data_vec.pop_back(); }
    void eraseObject(T object, bool removeAll = false) {
        if(removeAll) {
            for(auto iter = _data.begin(); iter != _data.end(); ) {
                if((**iter) == object) {
                    iter = _data.erase(iter);
                } else {
                    ++iter;
                }
            }
        } else {
            auto iter = std::find(_data.begin(), _data.end(), object);
            if(iter != _data.end()) {
                _data.erase(iter);
            }
        }
    }
    iterator erase(iterator position) { _data.erase(position); return _data_vec.erase(position); }
    iterator erase(iterator first, iterator last) { _data.erase(first, last); return _data_vec.erase(first, last); }
    iterator erase(ssize_t index) { _data.erase(_data.begin() + index); return _data_vec.earse(_data_vec.begin() + index);  }
    void clear() { _data.clear(); _data_vec.clear(); }
    
    // -------------------------------------
    //           Object Exchange
    // -------------------------------------
    void swap(T object1, T object2) { std::swap(_data.at(getIndex(object1)), _data.at(getIndex(object2)));
                                      std::swap(_data_vec.at(getIndex(object1)), _data_vec.at(getIndex(object2))); }
    void swap(ssize_t index1, ssize_t index2) { std::swap( _data.at(index1), _data.at(index2));
                                                std::swap(_data_vec.at(index1), _data_vec.at(index2)); }
    void replace(ssize_t index, T object) {
        Ref_Ptr<T> temp(object);
        _data.at(index) = temp;
        _data_vec.at(index) = object;
    }
    
    // -------------------------------------
    //            Other Operators
    // -------------------------------------
    void reverse() { std::reverse(std::begin(_data), std::end(_data));
                     std::reverse(std::begin(_data_vec), std::end(_data_vec)); }
    void shrinkToFit() { shrink_to_fit(); }
    void shrink_to_fit() { _data.shrink_to_fit(); _data_vec.shrink_to_fit(); }
    bool operator=(const Vector<T>& other) const { equals(other); }
    bool equals(const Vector<T> &other) {
        ssize_t s = this->size();
        if( s != other.size())
            return false;
        for(ssize_t i = 0; i < s; i++) {
            if(this->at(i) != other.at(i)) { return false; }
        }
        return true;
    }
    
    // -------------------------------------
    //        Speical Vector Operators
    // -------------------------------------
    // These allow comparisons with other vectors of the same type
    // or with vectors of std::shared_ptr
    
    // Compare with std::vector
    bool operator==(const std::vector<T>& other) { return _data_vec == other; }
    bool operator!=(const std::vector<T>& other) { return _data_vec != other; }
    bool operator<(const std::vector<T>& other) { return _data_vec < other; }
    bool operator>(const std::vector<T>& other) { return _data_vec > other; }
    bool operator<=(const std::vector<T>& other) { return _data_vec <= other; }
    bool operator>=(const std::vector<T>& other) { return _data_vec >= other; }
    
    // Compare with std::vector<Ref_Ptr<T>>
    bool operator==(const srd_vector& other) {
        if(other.size != this->size()) return false;
        for(ssize_t i = 0; i < other.size(); i++) {
            if(*other.at(i) != this->at(i)) return false ;
        }
        return true;
    }
    bool operator!=(const srd_vector& other) { return !(this == other); }
    
    // Compare with std::vector<shared_ptr<T>>
    // RECCOMMENDED AS MOVE TO std::vector<shared_ptr<T>> preferred
    // Uses the cast from Ref_Ptr<T> to std::shared_ptr<T>
    using srd_ptr_vec = std::vector<std::shared_ptr<T>>;
    bool operator==(const srd_ptr_vec& other) { return _data == other; }
    bool operator!=(const srd_ptr_vec& other) { return _data != other; }
    bool operator<(const srd_ptr_vec& other) { return _data < other; }
    bool operator>(const srd_ptr_vec& other) { return _data > other; }
    bool operator<=(const srd_ptr_vec& other) { return _data <= other; }
    bool operator>=(const srd_ptr_vec& other) { return _data >= other; }
    
    Vector<T> operator=(const std::vector<T>& other) {
        clear();
        for(auto itm : other) {
            Ref_Ptr<T> temp(itm);
            _data.push_back(temp);
            _data_vec.push_back(itm);
        }
        return *this;
    }
    
    // -------------------------------------
    //        Speical Cast Operators
    // -------------------------------------
    // Allows for conversion from Vector<T> to a normal std::vector
    
    // ! Warning !
    // allow for implicit casting from type Vector<T> to std::vector<T>
    // and similarly please use cautiously
    // volatile build
    operator std::vector<T>() const { return _data_vec; }
    explicit operator std::vector<std::shared_ptr<T>>() const {
        std::vector<std::shared_ptr<T>> temp;
        for(auto i : _data) {
            temp.push_back(i);
        }
        return temp;
    } // marked explicit, strangest use
    operator std::vector<Ref_Ptr<T>>() const { return _data; }
    
    // -------------------------------------
    //     Standard Comparison Operators
    // -------------------------------------
    // These operate just like the standard
    // vector comparison operators
    bool operator==(const Vector<T>& other) { return _data_vec == other._data_vec; }
    bool operator!=(const Vector<T>& other) { return _data_vec != other._data_vec; }
    bool operator<(const Vector<T>& other) { return _data_vec < other._data_vec; }
    bool operator>(const Vector<T>& other) { return _data_vec > other._data_vec; }
    bool operator<=(const Vector<T>& other) { return _data_vec <= other._data_vec; }
    bool operator>=(const Vector<T>& other) { return _data_vec >= other._data_vec; }
    
    
    
protected:
    srd_vector _data;
    data_vector _data_vec;
    
};


#endif

