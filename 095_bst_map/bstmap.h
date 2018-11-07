#ifndef _bstMAP_H__
#define _bstMAP_H__
#include <cstdlib>
#include <exception>
#include <iostream>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V>
{
  class Node
  {
   public:
    K key;
    V value;
    Node * rnode;
    Node * lnode;
    Node() : key(0), value(0), rnode(NULL), lnode(NULL) {}
    Node(const K & k, const V & v) : key(k), value(v) {}
    Node(const K & k, const V & v, Node * r, Node * l) : key(k), value(v), rnode(r), lnode(l) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  Node * copyNode(Node * n) {
    if (n == NULL) {
      return NULL;
    }

    Node * newNode = new Node(n->key, n->value, n->rnode, n->lnode);
    if (n->rnode != NULL) {
      newNode->rnode = copyNode(n->rnode);
    }
    if (n->lnode != NULL) {
      newNode->lnode = copyNode(n->lnode);
    }

    return newNode;
  }

  BstMap(const BstMap<K, V> & rhs) : root(NULL) {
    if (rhs.root != NULL) {
      root = copyNode(rhs.root);
      // root->lnode=copynode(rhs.lnode);
      // root->rnode=copynode(rhs.rnode);
    }
  }
  void destructor(Node * n) {
    if (n != NULL) {
      /*  if (n->lnode == NULL && n->rnode == NULL)
        delete n;
	else {*/
      destructor(n->lnode);
      destructor(n->rnode);
      delete n;
    }
  }
  ~BstMap() { destructor(root); }
  BstMap & operator=(BstMap & rhs) {
    if (this != rhs) {
      destructor(this);
      root = copyNode(rhs.root);
    }
  }
  virtual void add(const K & key, const V & value) {
    Node ** temp = &root;
    /* if (temp == NULL) {
      temp = new Node(key, value);
      }*/
    while (*temp != NULL)  //key should in the right
    {
      if (key == (*temp)->key) {
        (*temp)->value = value;
        return;
      }
      else if (key > (*temp)->key) {
        temp = &(*temp)->rnode;
      }
      else {
        temp = &(*temp)->lnode;
      }
    }
    *temp = new Node(key, value, NULL, NULL);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * temp = root;

    while (temp != NULL) {
      if (key == temp->key) {
        return temp->value;
      }
      else if (key > temp->key) {
        temp = temp->rnode;
      }
      else if (key < temp->key) {
        temp = temp->lnode;
      }
    }

    throw std::invalid_argument("The key is not found.");
  }

  Node * remove_helper(Node * node, const K & key) {
    // Node * temp = node;
    if (node == NULL) {
      return node;
    }
    else if (key < node->key) {
      node->lnode = remove_helper(node->lnode, key);
    }
    else if (key > node->key) {
      node->rnode = remove_helper(node->rnode, key);
    }
    else {
      //the left one
      if ((node->lnode == NULL) && (node->rnode == NULL)) {
        // Node * temp = node;
        delete node;
        node = NULL;
      }
      else if (node->rnode == NULL) {
        Node * temp = node;
        node = node->lnode;
        delete temp;
      }
      else if (node->lnode == NULL) {
        Node * temp = node;
        node = node->rnode;
        delete temp;
      }
      else {
        // Node * temp = node;
        Node * temp = node->rnode;
        while (temp->lnode != NULL) {
          temp = temp->lnode;
        }
        node->value = temp->value;
        node->key = temp->key;
        node->rnode = remove_helper(node->rnode, temp->key);
      }
    }
    return node;
  }
  virtual void remove(const K & key) { root = remove_helper(root, key); }
  void inorder() { print_mid_order(root); }

  void print_mid_order(Node * n) {
    if (n != NULL) {
      print_mid_order(n->lnode);
      std::cout << n->key << " ";
      print_mid_order(n->rnode);
    }
    else
      std::cout << "empty";
  }
};
class myexception : public std::exception
{
 public:
  virtual const char * what() const throw() { return "My exception happened"; }
};
#endif
