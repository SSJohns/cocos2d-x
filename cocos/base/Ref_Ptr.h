//
//  Ref_Ptr.h
//  Ref_Ptr_And_Objects
//
//  Created by Jonathan Baker on 12/3/15.
//  Copyright (c) 2015 JMB. All rights reserved.
//

#ifndef Ref_Ptr_And_Objects_Ref_Ptr_h
#define Ref_Ptr_And_Objects_Ref_Ptr_h

#include <memory>

template<class T>
class Ref_Ptr {
public:
    
    explicit Ref_Ptr(T object) {
        _ptr = std::make_shared<T>(object); 
    }
    
    inline Ref_Ptr() : _ptr(nullptr) { }
    
    inline Ref_Ptr(Ref_Ptr<T> && other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }
    
    inline Ref_Ptr(T * ptr) : _ptr(const_cast<typename std::remove_const<T>::type*>(ptr)) { }
    
    inline Ref_Ptr(std::nullptr_t ptr) : _ptr(nullptr) { }
    
    inline Ref_Ptr(const Ref_Ptr<T> & other) : _ptr(other._ptr) { }
    
    inline ~Ref_Ptr() { }
    
    inline Ref_Ptr<T> & operator = (const Ref_Ptr<T> & other)
    {
        if (other._ptr != _ptr)
        {
            _ptr = other._ptr;
        }
        
        return *this;
    }
    
    inline Ref_Ptr<T> & operator =(Ref_Ptr<T> && other)
    {
        if (&other != this)
        {
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        return *this;
    }
    
    inline Ref_Ptr<T> & operator = (T * other)
    {
        if (other != _ptr) { _ptr = const_cast<typename std::remove_const<T>::type*>(other); }
        
        return *this;
    }
    
    inline Ref_Ptr<T> & operator = (std::nullptr_t other) { return *this; }
    
    inline operator T * () const { return reinterpret_cast<T*>(_ptr); }
    
    inline T & operator * () const { return reinterpret_cast<T&>(*_ptr); }
    
    inline T * operator->() const { return reinterpret_cast<T*>(_ptr); }
    
    inline T * get() const { return reinterpret_cast<T*>(_ptr); }

    bool operator==(Ref_Ptr<T>& other) { return _ptr == other._ptr; }
    
    inline bool operator == (const Ref_Ptr<T> & other) const { return _ptr == other._ptr; }
    
    inline bool operator == (const T * other) const { return _ptr == other; }
    
    inline bool operator == (typename std::remove_const<T>::type * other) const { return _ptr == other; }
    
    inline bool operator == (const std::nullptr_t other) const { return _ptr == other; }

    
    inline bool operator != (const Ref_Ptr<T> & other) const { return _ptr != other._ptr; }
    
    inline bool operator != (const T * other) const { return _ptr != other; }
    
    inline bool operator != (typename std::remove_const<T>::type * other) const { return _ptr != other; }
    
    inline bool operator != (const std::nullptr_t other) const { return _ptr != other; }
    
    
    inline bool operator > (const Ref_Ptr<T> & other) const { return _ptr > other._ptr; }
    
    inline bool operator > (const T * other) const { return _ptr > other; }
    
    inline bool operator > (typename std::remove_const<T>::type * other) const { return _ptr > other; }
    
    inline bool operator > (const std::nullptr_t other) const { return _ptr > other; }
    
    
    inline bool operator < (const Ref_Ptr<T> & other) const { return _ptr < other._ptr; }
    
    inline bool operator < (const T * other) const { return _ptr < other; }
    
    inline bool operator < (typename std::remove_const<T>::type * other) const { return _ptr < other; }
    
    inline bool operator < (const std::nullptr_t other) const { return _ptr < other; }
    
    
    inline bool operator >= (const Ref_Ptr<T> & other) const { return _ptr >= other._ptr; }
    
    inline bool operator >= (const T * other) const { return _ptr >= other; }
    
    inline bool operator >= (typename std::remove_const<T>::type * other) const { return _ptr >= other; }
    
    inline bool operator >= (const std::nullptr_t other) const { return _ptr >= other; }
    
    
    inline bool operator <= (const Ref_Ptr<T> & other) const { return _ptr <= other._ptr; }
    
    inline bool operator <= (const T * other) const { return _ptr <= other; }
    
    inline bool operator <= (typename std::remove_const<T>::type * other) const { return _ptr <= other; }
    
    inline bool operator <= (const std::nullptr_t other) const { return _ptr <= other; }
    
    
    // Cast Operators
    // ! Warning !
    // Please use properly
    // Volatile build
    operator std::shared_ptr<T>() { return _ptr; }
    
private:
    std::shared_ptr<T> _ptr;
};

#endif
