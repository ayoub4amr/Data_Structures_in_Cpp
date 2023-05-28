#include <iostream>
using namespace std;

template <class T>
struct Node
{
    T value;
    Node *next = nullptr;
    Node *previous = nullptr;
    Node(T value) : value(value) {}
    ~Node()
    {
        // cout << "\nnode with value: " << this->value << " destroyed";
    }
};

template <class T>
class DoublyLinkedList
{
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int length{0};

public:
    ~DoublyLinkedList()
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
        if (this->head)
            return this->head->value;
        throw exception();
    }

    T getBack() const
    {
        if (this->tail)
            return this->tail->value;
        throw exception();
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

    void printList()
    {
        Node<T> *node = this->head;
        cout << "[";
        while (node)
        {
            cout << node->value;
            node = node->next;
            if (node)
            {
                cout << " ";
            }
        }
        cout << "]";
    }

    void printListReversed()
    {
        Node<T> *node = this->tail;
        cout << "[";
        while (node)
        {
            cout << node->value;
            node = node->previous;
            if (node)
            {
                cout << " ";
            }
        }
        cout << "]";
    }

    void pushFront(T value)
    {
        Node<T> *node = new Node(value);
        if (!this->head)
        {
            this->head = this->tail = node;
        }
        else
        {
            node->next = this->head;
            this->head->previous = node;
            this->head = node;
        }
        this->length++;
    }

    void pushBack(T value)
    {
        Node<T> *node = new Node(value);
        if (!this->head)
        {
            pushFront(value);
        }
        else
        {
            node->previous = this->tail;
            this->tail->next = node;
            this->tail = node;
            this->length++;
        }
    }

    void deleteFront()
    {
        if (!this->head)
        {
            return;
        }
        if (this->head == this->tail)
        {
            delete this->head;
            this->head = this->tail = nullptr;
            this->length--;
            return;
        }
        Node<T> *next = this->head->next;
        delete this->head;
        this->head = next;
        this->head->previous = nullptr;
        this->length--;
    }

    void deleteBack()
    {
        if (this->length <= 1)
        {
            this->deleteFront();
            return;
        }
        Node<T> *previous = this->tail->previous;
        delete this->tail;
        this->tail = previous;
        this->tail->next = nullptr;
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
        node->next->previous = previous;
        delete node;
        node = nullptr;
        this->length--;
    }

    void deleteValue(T value)
    {
        if (!this->length)
        {
            return;
        }
        Node<T> *node = this->head;
        Node<T> *previous = this->head;
        while (node)
        {
            if (node->value == value)
            {
                if (node == this->tail)
                {
                    this->deleteBack();
                    return;
                }
                if (node == this->head)
                {
                    this->deleteFront();
                    return;
                }
                previous->next = node->next;
                node->next->previous = previous;
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

    void deleteAllValue(T value)
    {
        if (!this->length)
        {
            return;
        }
        Node<T> *node = this->head;
        Node<T> *previous = this->head;
        while (node)
        {
            if (node->value == value)
            {
                if (node == this->tail)
                {
                    this->deleteBack();
                    return;
                }
                if (node == this->head)
                {
                    this->deleteFront();
                    node = this->head;
                    continue;
                }
                previous->next = node->next;
                node->next->previous = previous;
                delete node;
                node = previous->next;
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

    void deleteEvenPositions()
    {
        if (this->length <= 1)
        {
            return;
        }
        Node<T> *node = this->head;
        while (node && node->next)
        {
            if (node->next == this->tail)
            {
                this->tail = node;
            }
            Node<T> *newNext = node->next->next;
            delete node->next;
            node->next = newNext;
            if (newNext)
            {
                newNext->previous = node;
            }
            this->length--;
            node = node->next;
        }
    }

    void deleteOddPositions()
    {
        if (!this->length)
        {
            return;
        }
        if (this->length == 1)
        {
            this->deleteFront();
            return;
        }
        Node<T> *node = this->head;
        while (node)
        {
            if (node == this->head)
            {
                this->head = node->next;
            }
            if (node == this->tail)
            {
                this->tail = node->previous;
            }
            Node<T> *next = node->next;
            Node<T> *previous = node->previous;
            delete node;
            this->length--;
            if (previous)
            {
                previous->next = next;
            }
            if (next)
            {
                next->previous = previous;
                node = next->next;
            }
            else
            {
                node = nullptr;
            }
        }
    }

    bool isPalindrome()
    {
        if (this->length <= 1)
        {
            return true;
        }
        Node<T> *front = this->head;
        Node<T> *back = this->tail;
        for (int i = 0; i < this->length / 2; i++)
        {
            if (front->value != back->value)
            {
                return false;
            }
            front = front->next;
            back = back->previous;
        }
        return true;
    }

    T findMiddle()
    {
        if (!this->length)
        {
            throw exception();
        }
        if (this->length <= 2)
        {
            return this->getBack();
        }
        Node<T> *front = this->head;
        Node<T> *back = this->tail;
        while (front)
        {
            if (front == back || front->next == back)
            {
                return back->value;
            }
            front = front->next;
            back = back->previous;
        }
        throw exception();
    }

    Node<T> *findMiddleNode()
    {
        if (!this->length)
        {
            throw exception();
        }
        if (this->length <= 2)
        {
            return this->tail;
        }
        Node<T> *front = this->head;
        Node<T> *back = this->tail;
        while (front)
        {
            if (front == back || front->next == back)
            {
                return back;
            }
            front = front->next;
            back = back->previous;
        }
        throw exception();
    }

    void swap(int position)
    {
        if (this->length <= 1 || position < 1 || position > this->length)
        {
            return;
        }
        if (position > this->length / 2)
        {
            position = this->length - position + 1;
        }
        Node<T> *front = this->head;
        Node<T> *back = this->tail;
        for (int i = 0; i < position - 1; i++)
        {
            front = front->next;
            back = back->previous;
        }
        Node<T> *tempNext = front->next;
        Node<T> *tempPre = front->previous;
        if (back == this->findMiddleNode())
        {
            if (this->length % 2 == 1)
            {
                return;
            }
            Node<T> *tempNext = back->next;
            if (position != 1)
            {
                front->previous->next = back;
                tempNext->previous = front;
            }
            front->next = back->next;
            back->next = front;
            back->previous = front->previous;
            front->previous = back;
            if (position == 1)
            {
                Node<T> *tempH = this->head;
                Node<T> *tempT = this->tail;
                this->head = tempT;
                this->tail = tempH;
            }
            return;
        }
        if (position != 1)
        {
            front->previous->next = back;
            back->next->previous = front;
        }
        front->next->previous = back;
        back->previous->next = front;
        front->next = back->next;
        front->previous = back->previous;
        back->next = tempNext;
        back->previous = tempPre;
        if (position == 1)
        {
            Node<T> *tempH = this->head;
            Node<T> *tempT = this->tail;
            this->head = tempT;
            this->tail = tempH;
        }
    }

    void reverse()
    {
        if (this->length <= 1)
        {
            return;
        }
        Node<T> *node = this->head;
        while (node)
        {
            std::swap(node->next, node->previous);
            node = node->previous;
        }
        std::swap(this->head, this->tail);
    }

    void merge2SortedLists(DoublyLinkedList &other)
    {
        if (!other.length)
        {
            return;
        }
        Node<T> *node = this->head;
        Node<T> *otherNode = other.head;
        while (node && otherNode)
        {
            if (otherNode->value < node->value)
            {
                Node<T> *newNode = new Node(otherNode->value);
                if (node->previous)
                {
                    node->previous->next = newNode;
                }
                else
                {
                    this->head = newNode;
                }
                newNode->previous = node->previous;
                newNode->next = node;
                node->previous = newNode;
                otherNode = otherNode->next;
                this->length++;
            }
            else
            {
                node = node->next;
            }
        }
        while (otherNode)
        {
            this->pushBack(otherNode->value);
            otherNode = otherNode->next;
        }
    }
};

int main()
{
    return 0;
}