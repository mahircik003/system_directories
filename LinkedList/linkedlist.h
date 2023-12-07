#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private:
    Node<T> *head;
    int size;
};

template <class T>
LinkedList<T>::LinkedList()
{
    head = new Node<T>(T());
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{
    head = new Node<T>(T());
    size = 0;
    *this = rhs;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    removeAllNodes();
    delete head;
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{

    if (this != &rhs)
    {
        // must delete all the nodes first

        removeAllNodes();

        if (rhs.isEmpty())
            return *this;

        Node<T> *yeni_rhs = rhs.getFirstNode();

        for (int i = 0; i < rhs.getSize(); i++)
        {
            append(yeni_rhs->data);
            yeni_rhs = yeni_rhs->next;
        }

        size = rhs.getSize();
    }

    return *this;
}

template <class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return !size;
}

template <class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{

    if (isEmpty())
        return false;
    if (node == NULL)
        return false;

    Node<T> *yeni;

    for (yeni = head->next; yeni; yeni = yeni->next)
    {
        if (yeni == node)
            return true;
    }
    return false;
}

template <class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if (isEmpty())
        return NULL;
    return head->next;
}

template <class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if (isEmpty())
        return NULL;

    Node<T> *yeni;

    for (yeni = head->next; yeni->next; yeni = yeni->next)
        ;

    return yeni;
}

template <class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T> *yeni;
    if (size == 0)
        return NULL;

    for (yeni = head->next; yeni; yeni = yeni->next)
    {
        if (yeni->data == data)
            return yeni;
    }

    return NULL;
}

template <class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    if (index < 0 || index >= size || isEmpty())
        return NULL;

    Node<T> *current = head->next;

    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current;
}

template <class T>
void LinkedList<T>::append(const T &data)
{
    Node<T> *newNode = new Node<T>(data);

    if (isEmpty())
    {
        head->next = newNode;
        newNode->prev = head;
        newNode->next = NULL;
    }
    else
    {
        Node<T> *yeni = getLastNode();

        yeni->next = newNode;
        newNode->prev = yeni;
        newNode->next = NULL;
    }
    size++;
}

template <class T>
void LinkedList<T>::prepend(const T &data)
{
    Node<T> *newNode = new Node<T>(data);

    if (isEmpty())
    {
        head->next = newNode;
        newNode->next = NULL;
        newNode->prev = head;
    }
    else
    {
        newNode->next = head->next;
        head->next = newNode;
        newNode->prev = head;
        newNode->next->prev = newNode;
    }
    size++;
}

template <class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (isEmpty())
        return;

    Node<T> *yeni;

    for (yeni = head->next; yeni; yeni = yeni->next)
    {
        if (yeni == node)
        {

            if (!(yeni->next))
            {
                append(data);
                return;
            }

            else
            {

                Node<T> *newNode = new Node<T>(data);

                newNode->next = yeni->next;
                yeni->next = newNode;
                newNode->prev = yeni;
                newNode->next->prev = newNode;

                size++;
                return;
            }
        }
    }
}

template <class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    Node<T> *yeni;

    int counter = 0;

    if (index > size - 1 || index < 0)
        return;

    if (isEmpty())
    {
        append(data);
        return;
    }

    if (index == 0)
    {
        prepend(data);
        return;
    }

    Node<T> *newNode = new Node<T>(data);

    yeni = getNodeAtIndex(index);

    // inserting newNode prior to yeni

    newNode->prev = yeni->prev;
    newNode->next = yeni;
    yeni->prev = newNode;
    newNode->prev->next = newNode;

    size++;
}

template <class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    Node<T> *yeni;

    int counter = 0;

    for (yeni = head->next; yeni; yeni = yeni->next)
    {
        if (yeni == node)
            return counter;

        counter++;
    }

    return -1;
}

template <class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex == size - 1 && newIndex >= size - 1)
        return;

    if (currentIndex >= size)
        return;

    if (newIndex < 0 || currentIndex >= size || currentIndex < 0)
        return;

    Node<T> *yeni;

    if (newIndex > currentIndex)
    {
        yeni = getNodeAtIndex(currentIndex);

        if (newIndex >= size - 1)
        { // removing ==> adding to the end of the list

            // removal

            yeni->prev->next = yeni->next;
            yeni->next->prev = yeni->prev;

            Node<T> *ptr;

            for (ptr = head->next; ptr->next; ptr = ptr->next)
                ;

            // insertion
            ptr->next = yeni;
            yeni->prev = ptr;
            yeni->next = NULL;
        }

        else
        {

            // removing ==>adding to the mid of the list

            Node<T> *newPlace = getNodeAtIndex(newIndex);

            yeni->prev->next = yeni->next;
            yeni->next->prev = yeni->prev;
            // removing from the beginning or middle

            yeni->next = newPlace->next;
            newPlace->next = yeni;
            yeni->prev = newPlace;
            yeni->next->prev = yeni;
        }
    }

    else
    {
        yeni = getNodeAtIndex(currentIndex);

        // removing ==>adding to the mid of the list

        Node<T> *newPlace = getNodeAtIndex(newIndex);

        if (!(yeni->next))
        {
            yeni->prev->next = NULL;
        } // removing from the end
        else
        {
            yeni->prev->next = yeni->next;
            yeni->next->prev = yeni->prev;
        } // removing from the beginning or middle

        yeni->prev = newPlace->prev;
        yeni->next = newPlace;
        newPlace->prev = yeni;
        yeni->prev->next = yeni;
    }
}

template <class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    if (sourceIndex >= size || destIndex >= size || sourceIndex < 0 || destIndex < 0)
        return;

    Node<T> *sourceNode = getNodeAtIndex(sourceIndex);
    Node<T> *destNode = getNodeAtIndex(destIndex);

    destNode->data = destNode->data + sourceNode->data;

    removeNodeAtIndex(sourceIndex);
}

template <class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if (isEmpty() || node == NULL)
        return;

    Node<T> *yeni;

    for (yeni = head->next; yeni; yeni = yeni->next)
    {
        if (yeni == node && !(yeni->next))
        {
            yeni->prev->next = NULL;
            delete yeni;
            size--;
            return;
        }
        else if (yeni == node)
        {
            yeni->prev->next = yeni->next;
            yeni->next->prev = yeni->prev;
            delete yeni;
            size--;
            return;
        }
    }
}

template <class T>
void LinkedList<T>::removeNode(const T &data)
{
    if (isEmpty())
        return;

    Node<T> *yeni;
    int counter = 0;
    Node<T> *temp;
    for (yeni = head->next; yeni;)
    {
        temp = yeni->next;
        if (yeni->data == data)
        {
            removeNode(yeni);
        }

        yeni = temp;
    }
}

template <class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (isEmpty() || index < 0 || index >= size)
        return;

    Node<T> *current = head->next;

    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    if (index == size - 1)
    {
        current->prev->next = NULL;
        delete current;
        size--;
    }

    else
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        size--;
    }
}

template <class T>
void LinkedList<T>::removeAllNodes()
{
    int x = size;

    for (int i = 0; i < x; i++)
    {
        removeNodeAtIndex(0);
    }
}

template <class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty())
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while (node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

#endif // LINKEDLIST_H