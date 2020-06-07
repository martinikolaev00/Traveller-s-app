#pragma once
#include<iostream>
const int startersize = 10;
template<typename T>
/// Self-written small vector class
class Heaparr
{
    T* data;
    int maxsize;
    int currentsize;

public:

    ///Default constructor, just allocates mem
    Heaparr()
    {
        maxsize = startersize;
        data = new T[maxsize];
        currentsize = 0;
    }
    ///constructor where u can choose the size
    Heaparr(int maxsize)
    {
        this->maxsize = maxsize;
        data = new T[maxsize];
        currentsize = 0;

    }
    ///a simple copy constructor, just calls copy function
    Heaparr(const Heaparr& other)
    {
        copy(other);
    }
    ///overload of operator= , we just need to not forget to check if this and &other are the same
    Heaparr& operator=(const Heaparr& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }
        return *this;
    }
    ///destructor, just calls del() function
    ~Heaparr()
    {
        del();
    }
    ///resizes the vector with double of the current max size
    void resize()
    {
        T* temp = new T[maxsize * 2];
        for (int i = 0; i < currentsize; i++)
        {
            temp[i] = data[i];
        }
        del();
        data = temp;
        maxsize *= 2;
    }
    ///adds the given element by the user @note you can add the same element more than once
    ///if there is no place for it it calls resize()
    void addelem(const T& elem)
    {
        if (currentsize + 1 > maxsize)
        {
            resize();

        }
        data[currentsize] = elem;
        currentsize++;
    }
    ///We need this overload since we want to use data[x]
    T& operator[](int num)
    {
        if (num >maxsize)
            throw "invalid index";
        return data[num];
    }
    ///const operator[]
    const T& operator[](int num) const
    {
        if (num > maxsize)
            throw "invalid index";
        return data[num];
    }
    ///Removs the element on index n, but it checks if this index is included in the arry
    void remove(int n)
    {
        if (n<0 || n>currentsize)
            return;
        for (int i = n; i < currentsize; ++i)
        {
            data[i] = data[i + 1];
        }
        currentsize--;

    }
    ///@returns current size
    int size()
    {
        return currentsize;
    }
    /// const size()
   const int size() const
    {
        return currentsize;
    }
   ///@returns maxsize
    int getmaxsize() 
    {
        return maxsize;
    }
    /// const getmaxsize()
    const int getmaxsize() const
    {
        return maxsize;
    }
    void del()
    {
        delete[] data;
    }
    friend std::ostream& operator<<(std::ostream& out, Heaparr<T>& buff) 
    {
        std::cout << "This vector has " << buff.size() << " elements" << std::endl;
        for (int i = 0; i < buff.size(); ++i)
            out << "Element num" << i+1 << ": " << buff[i] << std::endl;
        return out;
    }
private:

    

    void copy(const Heaparr& other)
    {
       
            
            data= new T[other.maxsize];
            for (int i = 0; i < other.currentsize; i++)
            {
                data[i] = other.data[i];
            }
            maxsize = other.maxsize;
            currentsize = other.currentsize;
    }
    //void incsize() { currentsize++; }

    
    
};

