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
public:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    ArrayLinkedList *next = nullptr;
    ArrayLinkedList *previous = nullptr;
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
    int rowIndex = 0;

    ArrayLinkedList(int length, int rowIndex) : length(length), rowIndex(rowIndex) {}

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
        // if (!value)
        // {
        //     return;
        // }
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

template <class T>
class MatrixLinkedList
{
private:
    ArrayLinkedList<T> *head = nullptr;
    ArrayLinkedList<T> *tail = nullptr;
    int rows = 0;
    int columns = 0;
    int currentRows = 0;
    int currentColumns = 0;

    void pushFrontList(ArrayLinkedList<T> *list)
    {
        if (!this->head)
        {
            this->head = list;
            this->tail = list;
            this->currentRows++;
        }
    }

    void pushBackList(ArrayLinkedList<T> *list)
    {
        if (!this->head)
        {
            this->pushFrontList(list);
            return;
        }
        this->tail->next = list;
        list->previous = this->tail;
        this->tail = list;
        this->currentRows++;
    }

    void insertBefore(ArrayLinkedList<T> *listToInsert, ArrayLinkedList<T> *list)
    {
        if (list == this->head)
        {
            this->head = listToInsert;
        }
        else
        {
            list->previous->next = listToInsert;
        }
        listToInsert->next = list;
        listToInsert->previous = list->previous;
        list->previous = listToInsert;
        this->currentRows++;
    }

public:
    MatrixLinkedList(int rows, int columns) : rows(rows), columns(columns) {}

    ~MatrixLinkedList()
    {
        // cout << "\n=================================================\n";
        ArrayLinkedList<T> *list = this->head;
        while (list)
        {
            list = this->head->next;
            delete this->head;
            head = list;
        }
        // cout << "\nMatrix destroyed";
    }

    int getRows() const
    {
        return this->rows;
    }

    int getColumns() const
    {
        return this->columns;
    }

    void setValue(T value, int row, int column)
    {
        if (row >= this->rows || row < 0 || column >= this->columns || column < 0)
        {
            throw out_of_range("index out of range");
        }
        // if (!value)
        // {
        //     return;
        // }
        if (!this->head)
        {
            ArrayLinkedList<T> *newList = new ArrayLinkedList<T>(this->columns, row);
            newList->setValue(value, column);
            this->pushFrontList(newList);
            return;
        }
        ArrayLinkedList<T> *list = this->head;
        while (list)
        {
            if (list->rowIndex == row)
            {
                list->setValue(value, column);
                return;
            }
            else if (list->rowIndex > row)
            {
                ArrayLinkedList<T> *newList = new ArrayLinkedList<T>(this->columns, row);
                newList->setValue(value, column);
                this->insertBefore(newList, list);
                return;
            }
            list = list->next;
        }
        ArrayLinkedList<T> *newList = new ArrayLinkedList<T>(this->columns, row);
        newList->setValue(value, column);
        this->pushBackList(newList);
    }

    T getValue(int row, int column)
    {
        if (row >= this->rows || row < 0 || column >= this->columns || column < 0)
        {
            throw out_of_range("index out of range");
        }
        ArrayLinkedList<T> *list = this->head;
        while (list)
        {
            if (list->rowIndex == row)
            {
                return list->getValue(column);
            }
            list = list->next;
        }
        Node<decltype(list->previous->head->value)> *newNode = new Node<decltype(list->previous->head->value)>(column);
        return newNode->value;
    }

    void sumMatrix(MatrixLinkedList &other)
    {
        if (this->rows != other.rows || this->columns != other.columns)
        {
            throw invalid_argument("Matrix must have same size");
        }
        ArrayLinkedList<T> *thisList = this->head;
        ArrayLinkedList<T> *otherList = other.head;
        while (otherList && thisList)
        {
            if (otherList->rowIndex == thisList->rowIndex)
            {
                thisList->sumArrays(*otherList);
                otherList = otherList->next;
            }
            else if (thisList->rowIndex > otherList->rowIndex)
            {
                ArrayLinkedList<T> *newList = new ArrayLinkedList<T>(this->columns, otherList->rowIndex);
                newList->sumArrays(*otherList);
                this->insertBefore(newList, thisList);
                otherList = otherList->next;
            }
            else
            {
                thisList = thisList->next;
            }
        }
        while (otherList)
        {
            ArrayLinkedList<T> *newList = new ArrayLinkedList<T>(this->columns, otherList->rowIndex);
            newList->sumArrays(*otherList);
            this->pushBackList(newList);
            otherList = otherList->next;
        }
    }

    void printMatrixNoZero()
    {
        if (!this->head)
        {
            cout << "[]";
            return;
        }
        ArrayLinkedList<T> *list = this->head;
        while (list)
        {
            list->printArrayNoZero();
            cout << endl;
            list = list->next;
        }
    }

    void printMatrix()
    {

        ArrayLinkedList<T> *list = this->head;
        for (int i = 0; i < this->rows; i++)
        {
            if (list && list->rowIndex == i)
            {
                list->printArray();
                cout << endl;
                list = list->next;
            }
            else
            {
                cout << "[ ";
                for (int i = 0; i < this->columns; i++)
                {
                    cout << "0 ";
                }
                cout << "]" << endl;
            }
        }
    }
};

int main()
{
    return 0;
}