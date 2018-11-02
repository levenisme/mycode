
#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
template<typename T>
class LinkedList
{
  class Node
  {
   public:  //need to change
    T data;
    Node * next;
    Node * prev;

    Node() : data(0), next(NULL), prev(NULL) {}
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * n) : data(d), next(n), prev(NULL) {}
    Node(const T & d, Node * ptr, Node * n) : data(d), next(ptr), prev(n) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  void addFront(const T & item) {
    head = new Node(item, head);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    bool find = 0;
    Node * current = head;
    if (current == NULL) {  //empty list
      return find;
    }
    for (int i = 0; i < size; i++) {
      if (item == current->data) {
        find = 1;

        if (this->size == 1) {
          delete current;
          head = NULL;
          tail = NULL;
          size = 0;
        }

        else if (current->prev == NULL) {  //first one
          current->next->prev = NULL;
          head = current->next;
          size--;
          delete current;
        }
        else if (current->next == NULL) {  //last one
          current->prev->next = NULL;
          tail = current->prev;
          size--;
          delete current;
        }
        else {
          current->prev->next = current->next;
          current->next->prev = current->prev;
          size--;
          delete current;
        }

        return find;
      }
      current = current->next;
    }
    return find;
  }
  T & operator[](int index) {
    try {
      int test = index;
      if (test >= size) {
        throw 1;
      }
      if (test < 0) {
        throw 2;
      }
    }
    catch (int x) {
      std::cout << "invalid index" << x;
    }
    int i = index;
    Node * current = head;
    while (i) {
      current = current->next;
      i--;
    }
    return current->data;
  }
  const T & operator[](int index) const {
    try {
      int test = index;
      if (test >= size) {
        throw 1;
      }
      if (test < 0) {
        throw 2;
      }
    }
    catch (int x) {
      std::cout << "invalid index" << x;
    }
    int i = index;
    Node * current = head;
    while (i) {
      current = current->next;
      i--;
    }
    return current->data;
  }
  int find(const T & item) const {
    int i = -1;
    Node * current = this->head;
    while (!i) {
      i++;

      if (item == current->data) {
        current = current->next;
        return i;
      }
    }
    return i;
  }
  LinkedList(const LinkedList & rhs) {
    size = 0;
    head = NULL;
    tail = NULL;

    for (int i = 0; i < rhs.size; i++) {
      addBack(rhs[i]);
    }
  }
  ~LinkedList() {
    Node * temp = NULL;
    while (head != NULL) {
      temp = head->next;
      delete head;
      head = temp;
    }
    size = 0;
    tail = NULL;
  }

  LinkedList<T> & operator=(LinkedList<T> & rhs) {
    if (this != &rhs) {
      Node * temp = NULL;
      while (head != NULL) {
        temp = head->next;
        delete head;
        head = temp;
      }
      size = 0;
      tail = NULL;
      for (int i; i < rhs.size; i++) {
        addBack(rhs[i]);
      }
    }
    return *this;
  }
  int getSize() const { return this->size; }
};
class myexception : public std::exception
{
 public:
  virtual const char * what() const throw() { return "My exception happened"; }
};
//YOUR CODE GOES HERE

#endif
