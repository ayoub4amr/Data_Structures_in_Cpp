#include <iostream>
using namespace std;

template <class T>
struct Node
{
    T value{};
    int index;
    Node *next = nullptr;
    Node *previous = nullptr;
    Node(int index) : index(index) {}
    Node(T value, int index) : value(value), index(index) {}
    ~Node()
    {
        // cout << "\nnode with value: " << this->value << " destroyed";
    }
};

template <class T>
class ArrayLinkedList
{
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int length = 0;
    int currentSize = 0;

    void pushFrontNode(Node<T> *node)
    {
        if (!this->head)
        {
            this->head = node;
            this->tail = node;
            this->currentSize++;
        }
        else
        {
            this->insertBefor(node, this->head);
        }
    }

    void pushBackNode(Node<T> *node)
    {
        if (!this->head)
        {
            this->pushFrontNode(node);
        }
        else
        {
            this->tail->next = node;
            node->previous = this->tail;
            this->tail = node;
            this->currentSize++;
        }
    }

    void insertBefor(Node<T> *toInsert, Node<T> *node)
    {
        if (node == this->head)
        {
            this->head = toInsert;
        }
        else
        {
            node->previous->next = toInsert;
        }
        toInsert->next = node;
        toInsert->previous = node->previous;
        node->previous = toInsert;
        this->currentSize++;
    }

public:
    ArrayLinkedList(int length) : length(length) {}

    ~ArrayLinkedList()
    {
        // cout << "\n********************************\n";
        Node<T> *node = this->head;
        while (node)
        {
            node = this->head->next;
            delete this->head;
            head = node;
        }
        // cout << "\nlist destroyed";
    }

    int size() const
    {
        return this->length;
    }

    int getNonEmptySize() const
    {
        return this->currentSize;
    }

    void setValue(T value, int index)
    {
        if (index >= this->length || index < 0)
        {
            throw out_of_range("index out of range");
        }
        if (!value)
        {
            return;
        }
        Node<T> *newNode = new Node(value, index);
        if (!this->head)
        {
            this->pushFrontNode(newNode);
            return;
        }
        Node<T> *node = this->head;
        while (node)
        {
            if (node->index > index)
            {
                insertBefor(newNode, node);
                return;
            }
            else
            {
                node = node->next;
            }
        }
        pushBackNode(newNode);
    }

    T getValue(int index)
    {
        if (index >= this->length || index < 0)
        {
            throw out_of_range("index out of range");
        }
        Node<T> *node = this->head;
        while (node && index >= node->index)
        {
            if (node->index == index)
            {
                return node->value;
            }
            node = node->next;
        }
        Node<decltype(node->previous->value)> *newNode = new Node<decltype(node->previous->value)>(index);
        return newNode->value;
    }

    void updateValue(T value, int index)
    {
        Node<T> *node = this->head;
        while (node)
        {
            if (node->index == index)
            {
                node->value = value;
                return;
            }
            node = node->next;
        }
        throw out_of_range("index out of range");
    }

    void sumArrays(ArrayLinkedList &other)
    {
        if (this->length != other.length)
        {
            throw invalid_argument("Arrays must have same size");
        }
        Node<T> *otherNode = other.head;
        while (otherNode)
        {
            T thisValue = this->getValue(otherNode->index);
            T otherValue = other.getValue(otherNode->index);
            if (thisValue)
            {
                this->updateValue(thisValue + otherValue, otherNode->index);
            }
            else
            {
                this->setValue(otherValue, otherNode->index);
            }
            otherNode = otherNode->next;
        }
    }

    void printArrayNoZero()
    {
        if (!this->head)
        {
            cout << "[]";
            return;
        }
        Node<T> *node = this->head;
        cout << "[ ";
        while (node)
        {
            cout << node->value << " ";
            node = node->next;
        }
        cout << "]";
    }

    void printArray()
    {
        if (!this->head)
        {
            cout << "[]";
            return;
        }
        Node<T> *node = this->head;
        cout << "[ ";
        for (int i = 0; i < this->length; i++)
        {
            if (node && node->index == i)
            {
                cout << node->value << " ";
                node = node->next;
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << "]";
    }
};

int main()
{
    return 0;
}