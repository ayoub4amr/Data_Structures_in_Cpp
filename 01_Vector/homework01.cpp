#include <iostream>
using namespace std;

class Vector
{
private:
    int size{0};
    int capacity{100};
    int lastIndx{0};
    int *arr = nullptr;

public:
    Vector(int size, int value = 0) : size(size)
    {
        capacity = (size + 1) * 2;
        arr = new int[capacity];
        for (int i = 0; i < this->size; i++)
        {
            this->arr[i] = value;
        }
    }
    ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }
    int getSize()
    {
        return this->size;
    }
    int getFront()
    {
        return this->arr[0];
    }
    int getBack()
    {
        return this->arr[size - 1];
    }
    int get(int index)
    {
        return this->arr[index];
    }
    void set(int index, int value)
    {
        this->arr[index] = value;
    }
    void print()
    {
        for (int i = 0; i < this->size; i++)
        {
            cout << this->arr[i] << " ";
        }
    }
    int find(int value)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->arr[i] == value)
            {
                return i;
            }
        }
        return -1;
    }
    int findTransposition(int value)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->arr[i] == value)
            {
                if (i != 0)
                {
                    this->arr[i] = this->arr[i - 1];
                    this->arr[i - 1] = value;
                    return (i - 1);
                }
                return i;
            }
        }
        return -1;
    }

    void expand()
    {
        this->capacity *= 2;
        int *tempArr = new int[this->capacity];
        for (int i = 0; i < this->size; i++)
        {
            tempArr[i] = this->arr[i];
        }
        swap(this->arr, tempArr);
        delete[] tempArr;
        tempArr = nullptr;
    }

    void pushBack(int value)
    {
        if (this->size == this->capacity)
        {
            this->expand();
        }
        this->arr[this->size++] = value;
    }
    int pop(int index)
    {
        int temp = this->arr[index];
        for (int i = index; i < this->size - 1; i++)
        {
            this->arr[i] = this->arr[i + 1];
        }
        this->size--;
        return temp;
    }
    void rightRotate()
    {
        int temp = this->arr[size - 1];
        for (int i = this->size - 1; i > 0; i--)
        {
            this->arr[i] = this->arr[i - 1];
        }
        this->arr[0] = temp;
    }
    void leftRotate()
    {
        int temp = this->arr[0];
        for (int i = 0; i < this->size - 1; i++)
        {
            this->arr[i] = this->arr[i + 1];
        }
        this->arr[this->size - 1] = temp;
    }
    void rightRotate(int times)
    {
        for (int i = 0; i < times % this->size; i++)
        {
            this->rightRotate();
        }
    }
    void leftRotate(int times)
    {
        for (int i = 0; i < times % this->size; i++)
        {
            this->leftRotate();
        }
    }
};

int main()
{
    return 0;
}