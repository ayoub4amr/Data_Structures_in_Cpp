#include <iostream>
using namespace std;

template <class T>
struct Node
{
public:
    T value;
    Node *next = nullptr;
    Node(T value) : value(value) {}
    ~Node()
    {
        // cout << "\nnode with value: " << this->value << " destroyed";
    }
};

template <class T>
class LinkedList
{
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int length = 0;

public:
    ~LinkedList()
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

    T getFront() const
    {
        return head->value;
    }

    T getBack() const
    {
        return tail->value;
    }

    T getAt(int index)
    {
        if (index >= this->size() || index < 0)
            throw out_of_range("index out of range");
        Node<T> *node = this->head;
        while (index)
        {
            node = node->next;
            index--;
        }
        return node->value;
    }

    T getFromBack(int index)
    {
        return this->getAt(this->length - index);
    }

    T &operator[](int index)
    {
        if (index >= this->size() || index < 0)
            throw out_of_range("index out of range");
        Node<T> *node = this->head;
        while (index)
        {
            node = node->next;
            index--;
        }
        return node->value;
    }

    void pushFront(T value)
    {
        Node<T> *node = new Node(value);
        if (this->head == nullptr)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            node->next = this->head;
            this->head = node;
        }
        length++;
    }

    void pushBack(T value)
    {
        Node<T> *node = new Node(value);
        if (this->head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        length++;
    }

    void deleteFront()
    {
        if (!this->length)
            return;
        if (this->length == 1)
        {
            this->deleteBack();
            return;
        }
        Node<T> *node = this->head->next;
        delete this->head;
        this->head = node;
        this->length--;
    }

    void deleteBack()
    {
        if (!this->length)
            return;
        if (this->head == this->tail)
        {
            delete this->head;
            this->head = this->tail = nullptr;
            this->length--;
            return;
        }
        Node<T> *node = this->head;
        while (node->next != this->tail)
        {
            node = node->next;
        }
        delete node->next;
        node->next = nullptr;
        tail = node;
        this->length--;
    }

    void deleteAt(int index)
    {
        if (this->length <= index || this->length == 0 || index < 0)
            return;
        if (index == 0)
        {
            this->deleteFront();
            return;
        }
        if (index == (this->length - 1))
        {
            this->deleteBack();
            return;
        }
        Node<T> *node = head;
        Node<T> *previous = nullptr;
        for (int i = 0; i < index; i++)
        {
            previous = node;
            node = node->next;
        }
        previous->next = node->next;
        delete node;
        node = nullptr;
        this->length--;
    }

    void deleteValue(T value)
    {
        Node<T> *node = this->head;
        Node<T> *previous = this->head;
        while (node)
        {
            if (node->value == value)
            {
                if (node == this->tail)
                {
                    this->tail = previous;
                }
                if (node == this->head)
                {
                    this->head = node->next;
                }
                previous->next = node->next;
                delete node;
                node = nullptr;
                this->length--;
            }
            else
            {
                previous = node;
                node = node->next;
            }
        }
    }

    int find(T value)
    {
        Node<T> *node = this->head;
        for (int i = 0; i < this->size(); i++)
        {
            if (node->value == value)
            {
                return i;
            }
            else
            {
                node = node->next;
            }
        }
        return -1;
    }

    void reverse()
    {
        if (this->length <= 1)
            return;
        Node<T> *current = this->head;
        Node<T> *previous = nullptr;
        Node<T> *next = nullptr;
        while (current)
        {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        swap(this->head, this->tail);
    }

    void insertSorted(T value)
    {
        if (this->length < 1 || this->head->value >= value)
        {
            this->pushFront(value);
            return;
        }
        if (this->tail->value <= value)
        {
            this->pushBack(value);
            return;
        }
        Node<T> *node = this->head;
        while (node->next)
        {
            if (node->next->value >= value)
            {
                Node<T> *newNode = new Node(value);
                newNode->next = node->next;
                node->next = newNode;
                this->length++;
                return;
            }
            else
            {
                node = node->next;
            }
        }
    }

    void printList()
    {
        Node<T> *next = this->head;
        cout << "[";
        while (next)
        {
            cout << next->value;
            next = next->next;
            if (next)
            {
                cout << " ";
            }
        }
        cout << "]";
    }

    bool operator==(LinkedList<T> &other)
    {
        if (this->length != other.length)
        {
            return false;
        }
        Node<T> *node1 = this->head;
        Node<T> *node2 = other.head;
        while (node1)
        {
            if (node1->value != node2->value)
            {
                return false;
            }
            node1 = node1->next;
            node2 = node2->next;
        }
        return true;
    }

    void swapPairs()
    {
        if (this->length <= 1)
            return;
        Node<T> *node = this->head;
        for (int i = 0; i < this->length - 1; i += 2)
        {
            T temp = node->value;
            node->value = node->next->value;
            node->next->value = temp;
            node = node->next->next;
        }
    }

    void leftRotateByOneStep()
    {
        if (this->length <= 1)
            return;
        Node<T> *newTail = this->head;
        this->head = this->head->next;
        newTail->next = nullptr;
        this->tail->next = newTail;
        this->tail = newTail;
    }

    void leftRotateByNSteps(int steps)
    {
        for (int i = 0; i < steps % this->length; i++)
        {
            this->leftRotateByOneStep();
        }
    }

    void removeDuplicates()
    {
        if (this->length <= 1)
            return;
        Node<T> *node = this->head;
        while (node)
        {
            Node<T> *nextNodes = node->next;
            Node<T> *previous = node;
            while (nextNodes)
            {
                if (node->value == nextNodes->value)
                {
                    if (nextNodes == this->tail)
                    {
                        this->tail = previous;
                    }
                    previous->next = nextNodes->next;
                    delete nextNodes;
                    nextNodes = previous->next;
                    this->length--;
                }
                else
                {
                    previous = nextNodes;
                    nextNodes = nextNodes->next;
                }
            }
            node = node->next;
        }
    }

    void removeLastOccurrence(T value)
    {
        if (this->length == 1 && this->head->value == value)
        {
            this->deleteFront();
            return;
        }
        Node<T> *node = this->head;
        Node<T> *nodeToDelete = nullptr;
        Node<T> *previous = nullptr;
        Node<T> *previousNodeToDelete = nullptr;
        while (node)
        {
            if (node->value == value)
            {
                nodeToDelete = node;
                previousNodeToDelete = previous;
            }
            previous = node;
            node = node->next;
        }
        if (nodeToDelete)
        {
            if (nodeToDelete == this->tail)
            {
                this->tail = previousNodeToDelete;
            }
            previousNodeToDelete->next = nodeToDelete->next;
            delete nodeToDelete;
            nodeToDelete = nullptr;
            this->length--;
        }
    }

    void moveToBack(T value)
    {
        if (this->length <= 1)
            return;
        Node<T> *node = this->head;
        Node<T> *previous = nullptr;
        Node<T> *oldTail = nullptr;
        while (node && node != oldTail)
        {
            if (node->value == value)
            {
                if (node == this->tail)
                {
                    return;
                }
                if (node == this->head)
                {
                    this->head = node->next;
                }
                else
                {
                    previous->next = node->next;
                }
                this->tail->next = node;
                node->next = nullptr;
                this->tail = node;
                if (!oldTail)
                {
                    oldTail = node;
                }
                if (previous)
                {
                    node = previous->next;
                }
                else
                {
                    node = this->head;
                }
            }
            else
            {
                previous = node;
                node = node->next;
            }
        }
    }

    T max(Node<T> *head = nullptr, bool isFirstCall = true, int len = 1)
    {
        if (isFirstCall)
        {
            if (this->length < 1)
            {
                throw out_of_range("empty list");
            }
            return this->max(this->head, isFirstCall = false, this->length);
        }
        if (len == 1)
        {
            return head->value;
        }
        else
        {
            T maxV = max(head->next, false, len - 1);
            if (head->value >= maxV)
            {
                return head->value;
            }
            else
            {
                return maxV;
            }
        }
    }

    void arrangeOddEvenPosition()
    {
        if (this->length <= 2)
            return;
        Node<T> *nodeOdd = this->head;
        Node<T> *nodeEven = this->head->next;
        Node<T> *temp = this->head->next;
        bool first = true;
        for (int i = 0; i < (this->length / 2) - 1; i++)
        {
            nodeOdd->next = nodeOdd->next->next;
            nodeEven->next = nodeEven->next->next;
            nodeOdd = nodeOdd->next;
            nodeEven = nodeEven->next;
        }
        if (this->length % 2 == 1)
        {
            nodeOdd->next = this->tail;
            nodeOdd = this->tail;
        }
        nodeOdd->next = temp;
        nodeEven->next = nullptr;
        this->tail = nodeEven;
    }

    void insertAlternate(LinkedList &other)
    {
        if (!other.length)
        {
            return;
        }
        Node<T> *node1 = this->head;
        Node<T> *node2 = other.head;
        if (!this->length)
        {
            while (node2)
            {
                this->pushBack(node2->value);
                node2 = node2->next;
            }
            return;
        }
        while (node1 && node1->next && node2)
        {
            Node<T> *temp = node1->next;
            node1->next = new Node(node2->value);
            node1->next->next = temp;
            node1 = temp;
            node2 = node2->next;
        }
        if (this->length <= other.length)
        {
            while (node2)
            {
                node1->next = new Node(node2->value);
                this->tail = node1->next;
                node1 = node1->next;
                node2 = node2->next;
            }
        }
        this->length += other.length;
    }

    void AddNumber(LinkedList &other)
    {
        if (!other.length)
        {
            return;
        }
        Node<T> *node1 = this->head;
        Node<T> *node2 = other.head;
        if (!this->length)
        {
            while (node2)
            {
                this->pushBack(node2->value);
                node2 = node2->next;
            }
            return;
        }
        int remain = 0;
        while ((remain > 0) || node2)
        {
            if (node2)
            {
                if (node1)
                {
                    int newRemain = (node1->value + node2->value + remain) / 10;
                    node1->value = (node1->value + node2->value + remain) % 10;
                    remain = newRemain;
                    node1 = node1->next;
                }
                else
                {
                    this->tail->next = new Node((node2->value + remain) % 10);
                    remain = (node2->value + remain) / 10;
                    this->tail = this->tail->next;
                    this->length++;
                }
                node2 = node2->next;
            }
            else
            {
                if (node1)
                {
                    int newRemain = (node1->value + remain) / 10;
                    node1->value = (node1->value + remain) % 10;
                    remain = newRemain;
                }
                else
                {
                    this->tail->next = new Node(remain % 10);
                    remain = remain / 10;
                    this->tail = this->tail->next;
                    this->length++;
                }
            }
        }
    }

    void removeRepeated()
    {
        if (this->length <= 1)
            return;
        Node<T> *node = this->head;
        Node<T> *previous = this->head;
        while (node)
        {
            bool isRepeated = false;
            Node<T> *nextNodes = node;
            while (nextNodes->next)
            {
                if (node->value == nextNodes->next->value)
                {
                    Node<T> *temp = nextNodes->next->next;
                    delete nextNodes->next;
                    nextNodes->next = temp;
                    isRepeated = true;
                    this->length--;
                }
                else
                {
                    nextNodes = nextNodes->next;
                }
            }
            this->tail = nextNodes;
            if (!isRepeated)
            {
                previous = node;
                node = node->next;
            }
            else
            {
                Node<T> *temp = node->next;
                if (node == this->head)
                {
                    this->head = node->next;
                }
                else
                {
                    previous->next = node->next;
                }
                delete node;
                node = temp;
                this->length--;
            }
        }
    }

    // void reverseChains(int nbNodes)
    // {
    //     if (this->length <= 1 || this->length < nbNodes)
    //         return;
    //     Node<T> *node = this->head;
    //     Node<T> *previous = nullptr;
    //     bool isFirstLoop = true;
    //     while (node)
    //     {
    //         Node<T> *first = node;

    //         for (int i = 0; i < nbNodes; i++)
    //         {
    //             Node<T> *next = node->next;
    //             node->next = previous;
    //             previous = node;
    //             node = next;
    //         }
    //         if (isFirstLoop)
    //         {
    //             this->head = previous;
    //             isFirstLoop = false;
    //         }
    //     }
    // }
};

int main()
{
    return 0;
}