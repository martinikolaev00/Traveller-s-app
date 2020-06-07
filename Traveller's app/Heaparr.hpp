#pragma once
#include<iostream>
const int startersize = 10;
template<typename T>
class Heaparr
{
    T* data;
    int maxsize;
    int currentsize;

public:

   
    Heaparr()
    {
        maxsize = startersize;
        data = new T[maxsize];
        currentsize = 0;
    }
  
    Heaparr(int maxsize)
    {
        this->maxsize = maxsize;
        data = new T[maxsize];
        currentsize = 0;

    }
    
    Heaparr(const Heaparr& other)
    {
        copy(other);
    }
    Heaparr& operator=(const Heaparr& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }
        return *this;
    }
    ~Heaparr()
    {
        del();
    }
   
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
    void addelem(const T& elem)
    {
        if (currentsize + 1 > maxsize)
        {
            resize();

        }
        data[currentsize] = elem;
        currentsize++;
    }
    
    T& operator[](int num)
    {
        if (num >maxsize)
            throw "invalid index";
        return data[num];
    }
   
    const T& operator[](int num) const
    {
        if (num > maxsize)
            throw "invalid index";
        return data[num];
    }

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
    int size()
    {
        return currentsize;
    }
   const int size() const
    {
        return currentsize;
    }
    int getmaxsize() 
    {
        return maxsize;
    }
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

