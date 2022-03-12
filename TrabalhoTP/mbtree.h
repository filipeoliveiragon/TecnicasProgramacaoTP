#ifndef MBTREE_H
#define MBTREE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "node.h"

template <class T, const unsigned int MIN_DEGREE>
class mbtree {
   public:
      mbtree();
      virtual ~mbtree();
      void insert(T k);
      void remove(T k);
      int search(node<T, MIN_DEGREE>* x, T k);
      void print();
   protected:
      void insertNonFull(node<T, MIN_DEGREE>* x, T k);
      void removeAux(node<T, MIN_DEGREE>* x, T k);
      T findPredecessor(node<T, MIN_DEGREE>* x);
      T findSuccessor(node<T, MIN_DEGREE>* x);
      void printAux(node<T, MIN_DEGREE>* x, vector<string> &v, unsigned int lvl);
      int searchAux(node<T, MIN_DEGREE>* x, T k);
      node<T, MIN_DEGREE>* root = NULL;
};

template <class T, const unsigned int MIN_DEGREE>
mbtree<T, MIN_DEGREE>::mbtree() {
   if (!root)
      root = new node<T, MIN_DEGREE>();
}

template <class T, const unsigned int MIN_DEGREE>
mbtree<T, MIN_DEGREE>::~mbtree() {
   delete root;
   root = NULL;
}

template <class T, const unsigned int MIN_DEGREE>
void mbtree<T, MIN_DEGREE>::insert(T k) {
   node<T, MIN_DEGREE> *r = root, *s = NULL;

   if (r->size() == node<T, MIN_DEGREE>::MAX) {
      s = new node<T, MIN_DEGREE>();
      root = s;

      s->insertChild(r);
      s->splitChild(0);
      insertNonFull(s, k);
   } else {
      insertNonFull(r, k);
   }
}

template <class T, const unsigned int MIN_DEGREE>
void mbtree<T, MIN_DEGREE>::remove(T k) {
   node<T, MIN_DEGREE>* x = root;

   removeAux(x, k);
}

template <class T, const unsigned int MIN_DEGREE>
int mbtree<T, MIN_DEGREE>::search(node<T, MIN_DEGREE>* x, T k) {
   x = root;
   return searchAux(x, k);
}

template <class T, const unsigned int MIN_DEGREE>
void mbtree<T, MIN_DEGREE>::print() {
   int lvl = 0;
   vector<string> levels(1);
   printAux(root, levels, lvl);

   for (string s : levels) {
      cout << s << endl;
   }
}

template <class T, const unsigned int MIN_DEGREE>
void mbtree<T, MIN_DEGREE>::insertNonFull(node<T, MIN_DEGREE>* x, T k) {
   int i = x->size() - 1;
   node<T, MIN_DEGREE>* y = NULL;

   if (x->isLeaf()) {
      x->insertKey(k);
   } else {
      while (i >= 0 && k < x->getKey(i)) {
         i--;
      }

      i++;
      y = x->getChild(i);

      if (y->size() == node<T, MIN_DEGREE>::MAX) {
         x->splitChild(i);

         if (k > x->getKey(i)) {
            i++;
         }
      }

      insertNonFull(x->getChild(i), k);
   }
}

template <class T, const unsigned int MIN_DEGREE>
void mbtree<T, MIN_DEGREE>::removeAux(node<T, MIN_DEGREE>* x, T k) {
   unsigned int pos = x->hasKey(k);
   T aux;

   if (x->isLeaf()) { // Case 1
      if (pos != node<T, MIN_DEGREE>::NOT_FOUND) {
         x->removeKey(pos);
      }
   } else {
      if (pos != node<T, MIN_DEGREE>::NOT_FOUND && !x->isLeaf()) { // Case 2
         if (x->getChild(pos)->size() > node<T, MIN_DEGREE>::MIN) { // Case 2a
            aux = findPredecessor(x->getChild(pos));
            removeAux(x->getChild(pos), aux);
            x->setKey(aux, pos);
         } else {
            if (x->getChild(pos + 1)->size() > node<T, MIN_DEGREE>::MIN) { // Case 2b
               aux = findSuccessor(x->getChild(pos + 1));
               removeAux(x->getChild(pos + 1), aux);
               x->setKey(aux, pos);
            } else { // 2c
               x->mergeChildren(pos);
               if (x == root && x->size() == 0) {
                  root = x->getChild(pos);
                  delete x;
                  removeAux(root, k);
               } else {
                  removeAux(x->getChild(pos), k);
               }
            }
         }
      } else { // Case 3
         pos = 0;

         while (pos <= x->size() && k > x->getKey(pos)) {
            pos++;
         }

         if (x->getChild(pos)->size() == node<T, MIN_DEGREE>::MIN) { // Case 3a
            if (pos > 0 && x->getChild(pos - 1)->size() > node<T, MIN_DEGREE>::MIN) {
               x->rotateKeys(pos - 1);
            } else {
               if (pos < x->size() && x->getChild(pos + 1)->size() > node<T, MIN_DEGREE>::MIN) {
                  x->rotateKeys(pos);
               } else { // Case 3b
                  if (pos == x->size()) {
                     x->mergeChildren(pos - 1);
                  } else {
                     x->mergeChildren(pos);
                  }

                  if (x == root && x->size() == 0) {
                     root = x->getChild(0);
                     delete x;
                     x = root;
                     pos = 0;

                     while (pos <= x->size() && k > x->getKey(pos)) {
                        pos++;
                     }
                  }
               }
            }
         }

         removeAux(x->getChild(pos), k);
      }
   }
}

template <class T, const unsigned int MIN_DEGREE>
T mbtree<T, MIN_DEGREE>::findPredecessor(node<T, MIN_DEGREE>* x) {
   if (x->isLeaf()) {
      return x->getKey(x->size() - 1);
   } else {
      return findPredecessor(x->getChild(x->size()));
   }
}

template <class T, const unsigned int MIN_DEGREE>
T mbtree<T, MIN_DEGREE>::findSuccessor(node<T, MIN_DEGREE>* x) {
   if (x->isLeaf()) {
      return x->getKey(0);
   } else {
      return findSuccessor(x->getChild(0));
   }
}

template <class T, const unsigned int MIN_DEGREE>
void mbtree<T, MIN_DEGREE>::printAux(node<T, MIN_DEGREE>* x, vector<string> &v, unsigned int lvl) {
   string aux = "[";
   unsigned int i = 0;

   if (v.size() < lvl + 1) {
      v.resize(lvl + 1);
   }

   if (!x->isLeaf()) {
      for (i = 0; i <= x->size(); i++) {
         if (x->getChild(i) != NULL)
            printAux(x->getChild(i), v, lvl + 1);
      }
   }

   for (i = 0; i < x->size(); i++) {
      aux += to_string(x->getKey(i)) + ", ";
   }

   if (aux.length() > 1) {
      aux += "\b\b] ";
   } else {
      aux += "] ";
   }

   v[lvl] += aux;
}

template <class T, const unsigned int MIN_DEGREE>
int mbtree<T, MIN_DEGREE>::searchAux(node<T, MIN_DEGREE>* x, T k) {
   unsigned int i = 0;

   while (i < x->size() && k > x->getKey(i)) {
      i++;
   }

   if (i < x->size() && k == x->getKey(i)) {
      return i;
   } else {
      if (x->isLeaf()) {
         x = NULL;
         return -1;
      } else {
         return searchAux(x->getChild(i), k);
      }
   }
}
#endif // MBTREE_H
